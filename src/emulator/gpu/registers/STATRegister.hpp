#ifndef GAMEBOY_EMULATOR_STATREGISTER_H
#define GAMEBOY_EMULATOR_STATREGISTER_H


#include <emulator/mmu/MMIORegister.hpp>
#include <emulator/gpu/GPUTypes.hpp>

namespace gb {

class STATRegister : public MMIORegister<MMIOPermissions::READ_WRITE> {
private:
    friend class GPU;

    bool isInterruptEnabledForMode(GPUModeId modeId) const;

    bool isCoincidenceInterruptEnabled() const;

    void setCoincidenceFlag(bool flag);

    void setMode(GPUModeId modeId);

public:
    STATRegister();

    STATRegister &operator=(Byte value) override;

protected:
    void setValue(Byte value) override;
};

}


#endif //GAMEBOY_EMULATOR_STATREGISTER_H
