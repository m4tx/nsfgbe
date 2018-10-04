#include "InstructionInstance.hpp"

#include <sstream>
#include <iomanip>
#include <regex>

namespace gb {

InstructionInstance::InstructionInstance(
        Address address, const Instruction &instruction, Operand operand) :
        address(address),
        instruction(instruction),
        operand(operand) {}

void InstructionInstance::execute(Emulator &emulator) {
    instruction.executor(emulator, operand);
}

std::ostream &
operator<<(std::ostream &os, const InstructionInstance &instance) {
    std::ostringstream hexStringStream;
    hexStringStream << "$$"; // $$ as this will be passed to regex_replace
    if (instance.instruction.operandLength == OPERAND_LEN_ONE) {
        hexStringStream << std::setw(2);
    } else {
        hexStringStream << std::setw(4);
    }
    hexStringStream
            << std::hex << std::setfill('0') << std::uppercase
            << instance.operand;

    std::ios_base::fmtflags f(os.flags());

    auto instructionStr = std::regex_replace(
            instance.instruction.format,
            std::regex("\\%x"),
            hexStringStream.str());

    os << "$"
       << std::hex << std::setw(4) << std::setfill('0') << std::uppercase
       << instance.address;

    os.flags(f);

    os << ": " << instructionStr;

    return os;
}

}
