#include "DummyMBC.hpp"

namespace gb {

DummyMBC::DummyMBC(MMU &mmu) : MemoryBankController(mmu) {}

void DummyMBC::setByte(Address address, Byte value) {
    // No banking supported; do nothing
}

}
