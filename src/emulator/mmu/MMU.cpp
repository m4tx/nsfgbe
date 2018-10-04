#include "MMU.hpp"
#include "emulator/Constants.hpp"

#include <iostream>
#include <cassert>
#include <emulator/mmu/mbc/DummyMBC.hpp>
#include <emulator/serial/SerialLinkManager.hpp>

namespace gb {

MMU::MMU(const ROM &rom, InterruptManager &interruptManager,
         SerialLinkManager &serialLinkManager, GPU &gpu,
         JoypadRegister &joypadRegister, Timer &timer) :
        ram(RAM_SIZE, 0),
        highRam(HIGH_RAM_SIZE, 0),
        externalRam(0x20000, 0),
        rom(rom.getBuffer()),
        mbc(MemoryBankController::getMBC(rom.getROMType(), *this)),
        interruptManager(interruptManager),
        serialLinkManager(serialLinkManager),
        gpu(gpu),
        joypadRegister(joypadRegister),
        timer(timer) {}

Byte MMU::getByte(Address address) const {
    if (address >= 0x0000 && address < 0x4000) {
        return rom[address];
    } else if (address >= 0x4000 && address < 0x8000) {
        return rom[romBankOffset | (address - 0x4000)];
    } else if (address >= 0x8000 && address < 0xA000) {
        return gpu.vram[address - 0x8000];
    } else if (address >= 0xA000 && address < 0xC000) {
        return externalRam[address - 0xA000 + externalRamOffset];
    } else if (address >= 0xC000 && address < 0xE000) {
        return ram[address - 0xC000];
    } else if (address >= 0xE000 && address < 0xFE00) {
        return ram[address - 0xE000];
    } else if (address >= 0xFE00 && address < 0xFEA0) {
        return reinterpret_cast<Byte *>(gpu.oamRam.data())[address - 0xFE00];
    } else if (address >= 0xFEA0 && address < 0xFF00) {
        // Empty but unusable for I/O
        return 0xFF;
    } else if (address >= 0xFF00 && address < 0xFF40) {
        if (address == 0xFF00) {
            return joypadRegister;
        } else if (address == 0xFF01 || address == 0xFF02) {
            return serialLinkManager.getMMIOByte(address);
        } else if (address == 0xFF0F) {
            return interruptManager.ifReg;
        } else if (address == 0xFF04) {
            return timer.dividerRegister;
        } else if (address == 0xFF05) {
            return timer.timerCounterRegister;
        } else if (address == 0xFF06) {
            return timer.timerModuloRegister;
        } else if (address == 0xFF07) {
            return timer.timerControlRegister;
        }
//        std::cerr << "I/O ports are not implemented" << std::endl;
        return 0x00;
    } else if (address >= 0xFF40 && address < 0xFF4C) {
        return gpu.registers.getMMIOByte(address);
    } else if (address >= 0xFF4C && address < 0xFF80) {
        // Empty but unusable for I/O
        return 0xFF;
    } else if (address >= 0xFF80 && address < 0xFFFF) {
        return highRam[address - 0xFF80];
    } else {
        assert(address == 0xFFFF);
        return interruptManager.ieReg;
    }
}

Word MMU::getWord(Address address) const {
    return getByte(address) + (getByte(address + 1_adr) << 8);
}

void MMU::setByte(Address address, Byte value) {
    if (address >= 0x0000 && address < 0x8000) {
        mbc->setByte(address, value);
    } else if (address >= 0x8000 && address < 0xA000) {
        gpu.vram[address - 0x8000] = value;
    } else if (address >= 0xA000 && address < 0xC000) {
        externalRam[address - 0xA000 + externalRamOffset] = value;
    } else if (address >= 0xC000 && address < 0xE000) {
        ram[address - 0xC000] = value;
    } else if (address >= 0xE000 && address < 0xFE00) {
        ram[address - 0xE000] = value;
    } else if (address >= 0xFE00 && address < 0xFEA0) {
        reinterpret_cast<Byte *>(gpu.oamRam.data())[address - 0xFE00] = value;
    } else if (address >= 0xFEA0 && address < 0xFF00) {
        // Empty but unusable for I/O
    } else if (address >= 0xFF00 && address < 0xFF40) {
        if (address == 0xFF00) {
            joypadRegister = value;
        } else if (address == 0xFF01 || address == 0xFF02) {
            serialLinkManager.setMMIOByte(address, value);
        } else if (address == 0xFF0F) {
            interruptManager.ifReg = value;
        } else if (address == 0xFF04) {
            timer.dividerRegister = value;
        } else if (address == 0xFF05) {
            timer.timerCounterRegister = value;
        } else if (address == 0xFF06) {
            timer.timerModuloRegister = value;
        } else if (address == 0xFF07) {
            timer.timerControlRegister = value;
        }
//        std::cerr << "I/O ports are not implemented" << std::endl;
    } else if (address >= 0xFF40 && address < 0xFF4C) {
        gpu.registers.setMMIOByte(address, value);
    } else if (address >= 0xFF4C && address < 0xFF80) {
        // Empty but unusable for I/O
    } else if (address >= 0xFF80 && address < 0xFFFF) {
        highRam[address - 0xFF80] = value;
    } else {
        assert(address == 0xFFFF);
        interruptManager.ieReg = value;
    }
}

void MMU::setWord(Address address, Word value) {
    setByte(address, static_cast<Byte>(value & 0x00FF));
    setByte(address + 1_adr, static_cast<Byte>((value >> 8) & 0x00FF));
}

const uint8_t MMU::operator[](Address address) const {
    return getByte(address);
}

MMU::Reference MMU::operator[](Address address) {
    return MMU::Reference(*this, address);
}

MMU::Reference::Reference(MMU &mmu, Address address) :
        mmu(mmu), address(address) {}

MMU::Reference::operator Byte() const {
    return mmu.getByte(address);
}

MMU::Reference &MMU::Reference::operator=(Byte value) {
    mmu.setByte(address, value);
    return *this;
}

MMU::Reference &MMU::Reference::operator=(const MMU::Reference &value) {
    *this = (Byte) value;
    return *this;
}

}
