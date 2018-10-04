#ifndef GAMEBOY_EMULATOR_MMIOREGISTER_H
#define GAMEBOY_EMULATOR_MMIOREGISTER_H


#include "BaseMMIORegister.hpp"

namespace gb {

enum MMIOPermissions {
    READ = 1 << 0,
    WRITE = 1 << 1,
    READ_WRITE = READ | WRITE,
};

template<MMIOPermissions P>
class MMIORegister : public BaseMMIORegister {
protected:
    Byte value;

    Byte getValue() const override {
//        if (P & READ) {
        return value;
//        } else {
//            return 0xFF;
//        }
    }

    void setValue(Byte value) override {
//        if (P & WRITE) {
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
