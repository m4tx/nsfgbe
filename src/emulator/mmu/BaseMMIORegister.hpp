#ifndef GAMEBOY_EMULATOR_BASEMMIOREGISTER_H
#define GAMEBOY_EMULATOR_BASEMMIOREGISTER_H


#include <Types.hpp>

namespace gb {

class BaseMMIORegister {
protected:
    virtual Byte getValue() const = 0;

    virtual void setValue(Byte value) = 0;

public:
    operator Byte() const {
        return getValue();
    }

    virtual BaseMMIORegister &operator=(Byte value) {
        setValue(value);
        return *this;
    }

    BaseMMIORegister &operator++() {
        setValue(static_cast<Byte>(getValue() + 1));
        return *this;
    }

    BaseMMIORegister &operator--() {
        setValue(static_cast<Byte>(getValue() - 1));
        return *this;
    }

    BaseMMIORegister &operator&=(Byte value) {
        setValue(getValue() & value);
        return *this;
    }

    BaseMMIORegister &operator|=(Byte value) {
        setValue(getValue() | value);
        return *this;
    }
};

}


#endif //GAMEBOY_EMULATOR_BASEMMIOREGISTER_H
