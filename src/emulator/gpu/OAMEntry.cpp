#include "OAMEntry.hpp"

namespace gb {

bool OAMEntry::getFlag(Flags flag) const {
    return (flags & static_cast<Byte>(flag)) != 0;
}

}
