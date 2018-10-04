#include "OAMEntry.hpp"

namespace nsfgbe {

bool OAMEntry::getFlag(Flags flag) const {
    return (flags & static_cast<Byte>(flag)) != 0;
}

}
