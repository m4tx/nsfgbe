#ifndef GAMEBOY_EMULATOR_SIODATAREGISTER_H
#define GAMEBOY_EMULATOR_SIODATAREGISTER_H


#include <emulator/mmu/MMIORegister.hpp>

namespace gb {

class SerialLinkManager;

class SIODataRegister : public MMIORegister<MMIOPermissions::READ_WRITE> {
private:
    SerialLinkManager &serialLinkManager;

protected:
    Byte getValue() const override;

    void setValue(Byte value) override;

public:
    explicit SIODataRegister(SerialLinkManager &serialLinkManager);

    SIODataRegister &operator=(Byte value) override;
};

}


#endif //GAMEBOY_EMULATOR_SIODATAREGISTER_H
