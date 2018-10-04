#include <iostream>
#include <algorithm>
#include <cassert>

#include "Fetcher.hpp"
#include "GPUTypes.hpp"
#include "GPU.hpp"

namespace gb {

Fetcher::Fetcher(GPU &gpu, PixelFIFO &pixelFIFO) :
        gpu(gpu), pixelFIFO(pixelFIFO) {}

void Fetcher::fetch(Word tileId, Byte verticalLine) {
    this->tileId = tileId;
    this->verticalLine = verticalLine;
    this->currentMode = READ_TILE;
}

void Fetcher::tick() {
    switch (currentMode) {
        // Background
        case READ_TILE:
            readTile();
            break;
        case READ_DATA_0:
            readData0();
            break;
        case READ_DATA_1:
            readData1();
            buildBgPixels();
            // falls through
        case ADD_TO_FIFO:
            addToFifo();
            break;

            // Sprites
        case READ_SPRITE_PATTERN:
            readSpritePattern();
            break;
        case READ_SPRITE_DATA_0:
            readSpriteData0();
            break;
        case READ_SPRITE_DATA_1:
            readSpriteData1();
            buildSpritePixels();
            break;
        case ADD_SPRITE_TO_FIFO:
            addSpriteToFifo();
            break;
    }
}

// ####################################
// Background
// ####################################

void Fetcher::readTile() {
    tile = gpu.vram[gpu.registers.lcdc.getBgTileMapAddress() + tileId];

    currentMode = READ_DATA_0;
}

void Fetcher::readData0() {
    Address tileAddress = gpu.registers.lcdc.getBgTileAddress(tile);
    tileData0 = gpu.vram[tileAddress + 2 * verticalLine];

    currentMode = READ_DATA_1;
}

void Fetcher::readData1() {
    Address tileAddress = gpu.registers.lcdc.getBgTileAddress(tile);
    tileData1 = gpu.vram[tileAddress + 2 * verticalLine + 1];

    currentMode = ADD_TO_FIFO;
}

void Fetcher::buildBgPixels() {
    for (int i = 0; i < 8; ++i) {
        pixels[i].source = PIXEL_SOURCE_BG;
        pixels[i].value = static_cast<Byte>(
                ((tileData0 >> (7 - i)) & 1) |
                (((tileData1 >> (7 - i)) & 1) << 1));
    }
}

void Fetcher::addToFifo() {
    if (pixelFIFO.canAddEightPixels()) {
        pixelFIFO.addEightPixels(pixels);

        ++tileId;
        if (tileId % 32 == 0) {
            // Wrap tiles horizontally
            tileId -= 32;
        }
        currentMode = READ_TILE;
    }
}

// ####################################
// Sprites
// ####################################

void Fetcher::fetchSprite(Byte spriteId, Byte verticalLine, Byte pixelsToDrop) {
    assert(!isFetchingSprite());

    this->spriteId = spriteId;

    if (getCurrentOAMEntry().getFlag(OAMEntry::Flags::Y_FLIP)) {
        verticalLine =
                gpu.registers.lcdc.getSpriteHeight() - verticalLine - 1_b;
    }
    this->spriteVerticalLine = verticalLine;
    this->spritePixelsToDrop = pixelsToDrop;

    this->lastMode = currentMode;
    this->currentMode = READ_SPRITE_PATTERN;
}

OAMEntry &Fetcher::getCurrentOAMEntry() const {
    return gpu.oamRam[spriteId];
}

void Fetcher::readSpritePattern() {
    sprite = getCurrentOAMEntry().pattern;
    spriteSource =
            getCurrentOAMEntry().getFlag(OAMEntry::Flags::PALETTE) ?
            PIXEL_SOURCE_OB1 :
            PIXEL_SOURCE_OB0;

    currentMode = READ_SPRITE_DATA_0;
}

void Fetcher::readSpriteData0() {
    spriteData0 = gpu.vram[0x0000 + 16 * sprite + 2 * spriteVerticalLine];

    currentMode = READ_SPRITE_DATA_1;
}

void Fetcher::readSpriteData1() {
    spriteData1 = gpu.vram[0x0000 + 16 * sprite + 2 * spriteVerticalLine + 1];

    currentMode = ADD_SPRITE_TO_FIFO;
}

void Fetcher::buildSpritePixels() {
    for (int i = 0; i < 8; ++i) {
        spritePixels[i].source = spriteSource;
        spritePixels[i].value = static_cast<Byte>(
                ((spriteData0 >> (7 - i)) & 1) |
                (((spriteData1 >> (7 - i)) & 1) << 1));
    }
}

void Fetcher::addSpriteToFifo() {
    reverseSpritePixels();
    dropSpritePixels();

    pixelFIFO.addSpritePixels(spritePixels);

    currentMode = lastMode;
}

void Fetcher::reverseSpritePixels() {
    if (getCurrentOAMEntry().getFlag(OAMEntry::Flags::X_FLIP)) {
        std::reverse(spritePixels.begin(), spritePixels.end());
    }
}

void Fetcher::dropSpritePixels() {
    std::copy(spritePixels.begin() + spritePixelsToDrop,
              spritePixels.end(),
              spritePixels.begin());
    for (Byte i = 8_b - spritePixelsToDrop; i < 8; ++i) {
        spritePixels[i].value = 0;
    }
}

bool Fetcher::isFetchingSprite() const {
    return currentMode == READ_SPRITE_PATTERN ||
           currentMode == READ_SPRITE_DATA_0 ||
           currentMode == READ_SPRITE_DATA_1 ||
           currentMode == ADD_SPRITE_TO_FIFO;
}

}
