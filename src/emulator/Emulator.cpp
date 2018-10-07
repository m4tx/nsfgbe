#include <iostream>
#include <emulator/cpu/instructions/InstructionList.hpp>
#include <emulator/cpu/instructions/ExtendedInstructionList.hpp>
#include <emulator/cpu/instructions/impl/Calls.hpp>
#include "Emulator.hpp"

namespace nsfgbe {

Emulator::Emulator(const ROM &rom, Frontend &frontend) :
        frontend(frontend),
        gpu(interruptManager, dma, frontend.getPixelBuffer()),
        dma(mmu),
        joypadRegister(frontend),
        timer(interruptManager),
        mmu(rom, interruptManager, serialLinkManager, gpu, joypadRegister,
            timer),
        instructionDecoder(cpu, mmu) {}

void Emulator::runGame() {
    while (frontend.isRunning()) {
        runToNextFrame();
    }
}

void Emulator::runToNextFrame() {
    frontend.update();
    frontend.beforeSurfaceUpdate();

    generateFrame();

    frontend.afterSurfaceUpdate();
    frontend.render();
    frontend.postRender();
}

void Emulator::generateFrame() {
    bool generatedFrame = false;
    while (!generatedFrame) {
        size_t ticks;
        if (cpu.halted) {
            ticks = 4;
        } else {
            auto instructionInstance = instructionDecoder.retrieveInstruction();
            if (printInstructions) {
                std::cout << instructionInstance << std::endl;
            }
            instructionInstance.execute(*this);
            ticks = instructionInstance.instruction.ticks;
        }

        dma.tick(ticks);
        timer.tick(ticks);
        generatedFrame = gpu.tick(ticks);

        Address interruptAddress = interruptManager.tick();
        if (interruptManager.checkInterruptFired()) {
            cpu.halted = false;
        }
        if (interruptAddress != InterruptManager::NO_INTERRUPT) {
            interruptManager.disableInterrupts();
            nsfgbe::instr::callImm16(*this, interruptAddress);
        }

        totalTicks += ticks;
    }
}

void Emulator::printRegisters() const {
    printf("A: %02X, F: %02X, AF: %04X\n",
           cpu.registers.a, cpu.registers.f, cpu.registers.af);
    printf("B: %02X, C: %02X, BC: %04X\n",
           cpu.registers.b, cpu.registers.c, cpu.registers.bc);
    printf("D: %02X, E: %02X, DE: %04X\n",
           cpu.registers.d, cpu.registers.e, cpu.registers.de);
    printf("H: %02X, L: %02X, HL: %04X\n",
           cpu.registers.h, cpu.registers.l, cpu.registers.hl);
    printf("PC: %04X, SP: %04X\n",
           cpu.registers.pc, cpu.registers.sp);
    printf("[AF]: %04X, [BC]: %04X\n",
           mmu.getWord(cpu.registers.af), mmu.getWord(cpu.registers.bc));
    printf("[DE]: %04X, [HL]: %04X\n",
           mmu.getWord(cpu.registers.de), mmu.getWord(cpu.registers.hl));
    printf("Z: %d, N: %d, H: %d, C: %d\n",
           cpu.getFlag(CPUFlags::ZERO), cpu.getFlag(CPUFlags::SUBTRACT),
           cpu.getFlag(CPUFlags::HALF_CARRY), cpu.getFlag(CPUFlags::CARRY));
}

}
