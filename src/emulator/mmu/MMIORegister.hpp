#ifndef GAMEBOY_EMULATOR_MMIOREGISTER_H
#define GAMEBOY_EMULATOR_MMIOREGISTER_H


#include "BaseMMIORegister.hpp"

namespace nsfgbe {

enum class MMIOPermissions {
    NONE = 0,
    READ = 1 << 0,
    WRITE = 1 << 1,
    READ_WRITE = READ | WRITE,
};

MMIOPermissions operator&(MMIOPermissions a, MMIOPermissions b);

template<MMIOPermissions P>
class MMIORegister : public BaseMMIORegister {
protected:
    Byte value;

    Byte getValue() const override {
//        if ((P & MMIOPermissions::READ) == MMIOPermissions::READ) {
            return value;
//        } else {
//            return 0xFF;
//        }
    }

    void setValue(Byte value) override {
//        if ((P & MMIOPermissions::WRITE) == MMIOPermissions::WRITE) {
            this->value = value;
//        }
    }

public:
    explicit MMIORegister(Byte value) : value(value) {}

    MMIORegister<P> &operator=(Byte value) override {
        setValue(value);
        return *this;
    }
};

}


#endif //GAMEBOY_EMULATOR_MMIOREGISTER_H
