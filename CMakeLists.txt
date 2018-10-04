cmake_minimum_required(VERSION 3.9)
project(gameboy_emulator)

set(CMAKE_CXX_STANDARD 17)

#
# Library
#

add_library(gameboy_emulator_lib
        src/application/Application.cpp src/application/Application.hpp
        src/rom/ROM.cpp src/rom/ROM.hpp
        src/emulator/Emulator.cpp src/emulator/Emulator.hpp
        src/emulator/cpu/CPU.cpp src/emulator/cpu/CPU.hpp
        src/emulator/mmu/MMU.cpp src/emulator/mmu/MMU.hpp
        src/emulator/Constants.hpp
        src/Types.hpp
        src/emulator/cpu/instructions/Instruction.cpp src/emulator/cpu/instructions/Instruction.hpp
        src/emulator/cpu/instructions/InstructionInstance.cpp src/emulator/cpu/instructions/InstructionInstance.hpp
        src/emulator/cpu/instructions/InstructionList.cpp src/emulator/cpu/instructions/InstructionList.hpp
        src/emulator/cpu/instructions/ExtendedInstructionList.cpp src/emulator/cpu/instructions/ExtendedInstructionList.hpp
        src/emulator/cpu/instructions/InstructionDecoder.cpp src/emulator/cpu/instructions/InstructionDecoder.hpp
        src/emulator/cpu/instructions/InstructionImpl.hpp
        src/emulator/gpu/GPU.cpp src/emulator/gpu/GPU.hpp
        src/emulator/cpu/instructions/ByteValue.cpp src/emulator/cpu/instructions/ByteValue.hpp
        src/emulator/cpu/instructions/WordValue.cpp src/emulator/cpu/instructions/WordValue.hpp
        src/emulator/gpu/Fetcher.cpp src/emulator/gpu/Fetcher.hpp
        src/emulator/gpu/PixelFIFO.cpp src/emulator/gpu/PixelFIFO.hpp
        src/frontends/sdl/SDLFrontend.cpp src/frontends/sdl/SDLFrontend.hpp
        src/frontends/sdl/SDLError.cpp src/frontends/sdl/SDLError.hpp
        src/emulator/gpu/modes/GPUMode.cpp src/emulator/gpu/modes/GPUMode.hpp
        src/emulator/gpu/modes/OAMSearchMode.cpp src/emulator/gpu/modes/OAMSearchMode.hpp
        src/emulator/gpu/modes/PixelTransferMode.cpp src/emulator/gpu/modes/PixelTransferMode.hpp
        src/emulator/gpu/modes/HBlankMode.cpp src/emulator/gpu/modes/HBlankMode.hpp
        src/emulator/gpu/modes/VBlankMode.cpp src/emulator/gpu/modes/VBlankMode.hpp
        src/emulator/mmu/MMIOHandler.hpp
        src/emulator/mmu/BaseMMIORegister.hpp
        src/emulator/mmu/MMIORegisterStore.hpp
        src/emulator/gpu/registers/GPURegisters.cpp src/emulator/gpu/registers/GPURegisters.hpp
        src/emulator/interrupt/InterruptManager.cpp src/emulator/interrupt/InterruptManager.hpp
        src/emulator/gpu/GPUTypes.hpp
        src/emulator/cpu/instructions/impl/Arithmetic.cpp src/emulator/cpu/instructions/impl/Arithmetic.hpp
        src/emulator/cpu/instructions/impl/Bit.hpp
        src/emulator/cpu/instructions/impl/Calls.cpp src/emulator/cpu/instructions/impl/Calls.hpp
        src/emulator/cpu/instructions/impl/Jumps.cpp src/emulator/cpu/instructions/impl/Jumps.hpp
        src/emulator/cpu/instructions/impl/Loads.cpp src/emulator/cpu/instructions/impl/Loads.hpp
        src/emulator/cpu/instructions/impl/Miscellaneous.cpp src/emulator/cpu/instructions/impl/Miscellaneous.hpp
        src/emulator/cpu/instructions/impl/Shifts.cpp src/emulator/cpu/instructions/impl/Shifts.hpp
        src/emulator/gpu/OAMEntry.hpp src/emulator/gpu/OAMEntry.cpp
        src/emulator/mmu/MMIORegister.hpp
        src/emulator/dma/DMA.cpp src/emulator/dma/DMA.hpp
        src/emulator/dma/DMARegister.cpp src/emulator/dma/DMARegister.hpp
        src/emulator/joypad/JoypadRegister.cpp src/emulator/joypad/JoypadRegister.hpp
        src/frontends/InputHandler.hpp
        src/emulator/timer/Timer.cpp src/emulator/timer/Timer.hpp
        src/emulator/timer/DividerRegister.cpp src/emulator/timer/DividerRegister.hpp
        src/emulator/timer/TimerControlRegister.cpp src/emulator/timer/TimerControlRegister.hpp
        src/emulator/gpu/registers/PaletteRegister.cpp src/emulator/gpu/registers/PaletteRegister.hpp
        src/emulator/gpu/RGBPixel.hpp src/emulator/gpu/RGBPixel.cpp
        src/emulator/gpu/registers/LCDCRegister.cpp src/emulator/gpu/registers/LCDCRegister.hpp
        src/emulator/mmu/mbc/MemoryBankController.cpp src/emulator/mmu/mbc/MemoryBankController.hpp
        src/emulator/mmu/mbc/DummyMBC.cpp src/emulator/mmu/mbc/DummyMBC.hpp
        src/emulator/mmu/mbc/MBC1.cpp src/emulator/mmu/mbc/MBC1.hpp
        src/emulator/gpu/registers/STATRegister.cpp src/emulator/gpu/registers/STATRegister.hpp
        src/frontends/headless/HeadlessFrontend.cpp src/frontends/headless/HeadlessFrontend.hpp
        src/emulator/serial/SerialLinkManager.cpp src/emulator/serial/SerialLinkManager.hpp
        src/emulator/serial/SIODataRegister.cpp src/emulator/serial/SIODataRegister.hpp
        src/emulator/serial/SIOControlRegister.cpp src/emulator/serial/SIOControlRegister.hpp)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftrapv -fsanitize=undefined -fsanitize=address")

target_include_directories(gameboy_emulator_lib PUBLIC src)

# SDL2
find_package(SDL2)
if (SDL2_FOUND)
    target_include_directories(gameboy_emulator_lib PUBLIC SDL2::SDL2)
    target_link_libraries(gameboy_emulator_lib SDL2::SDL2)
else ()
    INCLUDE(FindPkgConfig)

    PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

    INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
    TARGET_LINK_LIBRARIES(gameboy_emulator_lib ${SDL2_LIBRARIES})
endif ()

# Boost
find_package(Boost REQUIRED COMPONENTS program_options)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(gameboy_emulator_lib ${Boost_LIBRARIES})

#
# Main executable
#

add_executable(gameboy_emulator src/application/main.cpp src/frontends/Frontend.hpp)
target_link_libraries(gameboy_emulator gameboy_emulator_lib)


#
# Testing
#

enable_testing()
include(GoogleTest)
find_package(GTest REQUIRED)

add_executable(gameboy_emulator_test
        test/BlarggCpuInstrsTests.cpp
        "test/blargg/cpu_instrs/01-special.hpp"
        "test/blargg/cpu_instrs/02-interrupts.hpp"
        "test/blargg/cpu_instrs/03-op-sp,hl.hpp"
        "test/blargg/cpu_instrs/04-op-r,imm.hpp"
        "test/blargg/cpu_instrs/05-op-rp.hpp"
        "test/blargg/cpu_instrs/06-ld-r,r.hpp"
        "test/blargg/cpu_instrs/07-jr,jp,call,ret,rst.hpp"
        "test/blargg/cpu_instrs/08-misc-instrs.hpp"
        "test/blargg/cpu_instrs/09-op-r,r.hpp"
        "test/blargg/cpu_instrs/10-bit-ops.hpp"
        "test/blargg/cpu_instrs/11-op-a,(hl).hpp")
target_include_directories(gameboy_emulator_test PUBLIC src)
target_link_libraries(gameboy_emulator_test
        gameboy_emulator_lib
        GTest::GTest GTest::Main)

gtest_add_tests(TARGET gameboy_emulator_test)
