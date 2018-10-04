#include "gtest/gtest.h"

#include <rom/ROM.hpp>
#include <emulator/Emulator.hpp>
#include <frontends/headless/HeadlessFrontend.hpp>

#include "blargg/cpu_instrs/01-special.hpp"
#include "blargg/cpu_instrs/02-interrupts.hpp"
#include "blargg/cpu_instrs/03-op-sp,hl.hpp"
#include "blargg/cpu_instrs/04-op-r,imm.hpp"
#include "blargg/cpu_instrs/05-op-rp.hpp"
#include "blargg/cpu_instrs/06-ld-r,r.hpp"
#include "blargg/cpu_instrs/07-jr,jp,call,ret,rst.hpp"
#include "blargg/cpu_instrs/08-misc-instrs.hpp"
#include "blargg/cpu_instrs/09-op-r,r.hpp"
#include "blargg/cpu_instrs/10-bit-ops.hpp"
#include "blargg/cpu_instrs/11-op-a,(hl).hpp"


namespace nsfgbe {
namespace test {


void runTestOnRom(const Byte *romData, size_t length,
                  const std::string testName, size_t framesToGenerate) {
    ROM rom = ROM(romData, length);

    HeadlessFrontend frontend;
    Emulator emulator(rom, frontend);
    for (int j = 0; j < framesToGenerate; ++j) {
        emulator.runToNextFrame();
    }

    const auto &serialData = emulator.serialLinkManager.getDataSent();
    const auto &str = std::string(serialData.begin(), serialData.end());

    ASSERT_EQ(testName + "\n\n\nPassed\n", str);
}

TEST(BlarggCpuInstrs, 01Special) {
    runTestOnRom(blargg::cpu_instrs::SPECIAL_ROM,
                 blargg::cpu_instrs::SPECIAL_ROM_LEN,
                 "01-special", 200);
}

TEST(BlarggCpuInstrs, 02Interrupts) {
    runTestOnRom(blargg::cpu_instrs::INTERRUPTS_ROM,
                 blargg::cpu_instrs::INTERRUPTS_ROM_LEN,
                 "02-interrupts", 60);
}


TEST(BlarggCpuInstrs, 03OpSpHl) {
    runTestOnRom(blargg::cpu_instrs::OP_SP_HL_ROM,
                 blargg::cpu_instrs::OP_SP_HL_ROM_LEN,
                 "03-op sp,hl", 240);
}


TEST(BlarggCpuInstrs, 04OpRImm) {
    runTestOnRom(blargg::cpu_instrs::OP_R_IMM_ROM,
                 blargg::cpu_instrs::OP_R_IMM_ROM_LEN,
                 "04-op r,imm", 200);
}


TEST(BlarggCpuInstrs, 05OpRp) {
    runTestOnRom(blargg::cpu_instrs::OP_RP_ROM,
                 blargg::cpu_instrs::OP_RP_ROM_LEN,
                 "05-op rp", 260);
}


TEST(BlarggCpuInstrs, 06LdRR) {
    runTestOnRom(blargg::cpu_instrs::LD_R_R_ROM,
                 blargg::cpu_instrs::LD_R_R_ROM_LEN,
                 "06-ld r,r", 60);
}


TEST(BlarggCpuInstrs, 07JrJpCallRetRst) {
    runTestOnRom(blargg::cpu_instrs::JR_JP_CALL_RET_RST_ROM,
                 blargg::cpu_instrs::JR_JP_CALL_RET_RST_ROM_LEN,
                 "07-jr,jp,call,ret,rst", 60);
}


TEST(BlarggCpuInstrs, 08MiscInstrs) {
    runTestOnRom(blargg::cpu_instrs::MISC_INSTRS_ROM,
                 blargg::cpu_instrs::MISC_INSTRS_ROM_LEN,
                 "08-misc instrs", 60);
}


TEST(BlarggCpuInstrs, 09OpRR) {
    runTestOnRom(blargg::cpu_instrs::OP_R_R_ROM,
                 blargg::cpu_instrs::OP_R_R_ROM_LEN,
                 "09-op r,r", 660);
}


TEST(BlarggCpuInstrs, 10BitOps) {
    runTestOnRom(blargg::cpu_instrs::BIT_OPS_ROM,
                 blargg::cpu_instrs::BIT_OPS_ROM_LEN,
                 "10-bit ops", 900);
}


TEST(BlarggCpuInstrs, 11OpAHl) {
    runTestOnRom(blargg::cpu_instrs::OP_A_HL_ROM,
                 blargg::cpu_instrs::OP_A_HL_ROM_LEN,
                 "11-op a,(hl)", 1150);
}


}
}
