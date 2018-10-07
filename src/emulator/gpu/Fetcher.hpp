#ifndef GAMEBOY_EMULATOR_FETCHER_H
#define GAMEBOY_EMULATOR_FETCHER_H


#include "PixelFIFO.hpp"
#include "OAMEntry.hpp"

namespace nsfgbe {

class GPU;

class Fetcher {
private:
    enum class FetcherMode {
        /** Read tile from the memory */
        READ_TILE,
        /** Read first byte of the current tile */
        READ_DATA_0,
        /** Read second byte of the current tile */
        READ_DATA_1,
        /** Push the pixels to FIFO */
        ADD_TO_FIFO,

        READ_SPRITE_PATTERN,
        READ_SPRITE_DATA_0,
        READ_SPRITE_DATA_1,
        ADD_SPRITE_TO_FIFO,
    };

    GPU &gpu;
    PixelFIFO &pixelFIFO;

    volatile FetcherMode currentMode;
    FetcherMode lastMode;

    Word tileId;
    Byte verticalLine;
    Byte tile;
    Byte tileData0;
    Byte tileData1;

    Byte spriteId;
    PixelSource spriteSource;
    Byte spriteVerticalLine;
    Byte spritePixelsToDrop;
    Byte sprite;
    Byte spriteData0;
    Byte spriteData1;

    std::array<Pixel, 8> pixels;
    std::array<Pixel, 8> spritePixels;

    // Background
    void readTile();

    void readData0();

    void readData1();

    void buildBgPixels();

    void addToFifo();

    // Sprites
    OAMEntry &getCurrentOAMEntry() const;

    void readSpritePattern();

    void readSpriteData0();

    void readSpriteData1();

    void buildSpritePixels();

    void addSpriteToFifo();

    void reverseSpritePixels();

    void dropSpritePixels();

public:
    Fetcher(GPU &gpu, PixelFIFO &pixelFIFO);

    void fetch(Word tileId, Byte verticalLine);

    void fetchSprite(Byte spriteId, Byte verticalLine, Byte pixelsToDrop);

    void tick();

    bool isFetchingSprite() const;
};

}


#endif //GAMEBOY_EMULATOR_FETCHER_H
