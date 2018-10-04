#ifndef GAMEBOY_EMULATOR_SIOCONTROLREGISTER_H
#define GAMEBOY_EMULATOR_SIOCONTROLREGISTER_H


#include <emulator/mmu/MMIORegister.hpp>

namespace gb {

class SerialLinkManager;

class SIOControlRegister : public MMIORegister<MMIOPermissions::READ_WRITE> {
private:
    SerialLinkManager &serialLinkManager;

protected:
    Byte getValue() const override;

    void setValue(Byte value) override;

public:
    explicit SIOControlRegister(SerialLinkManager &serialLinkManager);

    SIOControlRegister &operator=(Byte value) override;
};

}


#endif //GAMEBOY_EMULATOR_SIOCONTROLREGISTER_H
