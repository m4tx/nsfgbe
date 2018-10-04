#ifndef GAMEBOY_EMULATOR_EMULATOR_H
#define GAMEBOY_EMULATOR_EMULATOR_H


#include <rom/ROM.hpp>
#include <emulator/cpu/CPU.hpp>
#include <emulator/cpu/instructions/InstructionDecoder.hpp>
#include <emulator/interrupt/InterruptManager.hpp>
#include <emulator/mmu/MMU.hpp>
#include <frontends/Frontend.hpp>
#include <emulator/joypad/JoypadRegister.hpp>
#include <emulator/timer/Timer.hpp>

namespace nsfgbe {

class Emulator {
private:
    InstructionDecoder instructionDecoder;
    size_t totalTicks = 0;
    bool printInstructions = false;

    void generateFrame();

public:
    Frontend &frontend;
    CPU cpu;
    InterruptManager interruptManager;
    SerialLinkManager serialLinkManager;
    DMA dma;
    GPU gpu;
    JoypadRegister joypadRegister;
    Timer timer;
    MMU mmu;

    explicit Emulator(const ROM &rom, Frontend &frontend);

    void runGame();

    void runToNextFrame();

    /**
     * Debug utility function that prints the state of all CPU registers.
     */
    void printRegisters() const;
};

}


#endif //GAMEBOY_EMULATOR_EMULATOR_H
