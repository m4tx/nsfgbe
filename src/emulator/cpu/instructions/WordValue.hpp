#ifndef GAMEBOY_EMULATOR_WORDVALUE_H
#define GAMEBOY_EMULATOR_WORDVALUE_H


#include <emulator/Emulator.hpp>

namespace gb {

enum InstrArgWord {
    ARG_REG_AF,
    ARG_REG_BC,
    ARG_REG_DE,
    ARG_REG_HL,
    ARG_REG_SP,
};

/**
 * Proxy class representing double-byte CPU register value. The value can be
 * modified - the source register is modified in such case as well.
 *
 * @see ByteValue
 */
template<InstrArgWord ARG>
class WordValue {
private:
    Emulator &emulator;

public:
    explicit WordValue(Emulator &emulator) :
            emulator(emulator) {
    }

    operator Word() const;

    WordValue<ARG> &operator=(Word value);

    template<InstrArgWord A>
    WordValue<ARG> &operator=(WordValue<A> const &value) {
        *this = static_cast<Word>(value);
        return *this;
    }

    WordValue<ARG> &operator--() {
        *this = *this - 1;
        return *this;
    }

    WordValue<ARG> &operator++() {
        *this = *this + 1;
        return *this;
    }

    WordValue<ARG> &operator&=(Word value) {
        *this = *this & value;
        return *this;
    }

    WordValue<ARG> &operator|=(Word value) {
        *this = *this | value;
        return *this;
    }

    WordValue<ARG> &operator<<=(int shift) {
        *this = *this << shift;
        return *this;
    }

    WordValue<ARG> &operator>>=(int shift) {
        *this = *this >> shift;
        return *this;
    }
};

template<>
WordValue<ARG_REG_AF>::operator Word() const;

template<>
WordValue<ARG_REG_AF> &WordValue<ARG_REG_AF>::operator=(Word value);


template<>
WordValue<ARG_REG_BC>::operator Word() const;

template<>
WordValue<ARG_REG_BC> &WordValue<ARG_REG_BC>::operator=(Word value);


template<>
WordValue<ARG_REG_DE>::operator Word() const;

template<>
WordValue<ARG_REG_DE> &WordValue<ARG_REG_DE>::operator=(Word value);


template<>
WordValue<ARG_REG_HL>::operator Word() const;

template<>
WordValue<ARG_REG_HL> &WordValue<ARG_REG_HL>::operator=(Word value);


template<>
WordValue<ARG_REG_SP>::operator Word() const;

template<>
WordValue<ARG_REG_SP> &WordValue<ARG_REG_SP>::operator=(Word value);

}


#endif //GAMEBOY_EMULATOR_WORDVALUE_H
