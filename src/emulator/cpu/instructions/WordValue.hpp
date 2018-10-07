#ifndef GAMEBOY_EMULATOR_WORDVALUE_H
#define GAMEBOY_EMULATOR_WORDVALUE_H


#include <emulator/Emulator.hpp>

namespace nsfgbe {

enum class WordArg {
    REG_AF,
    REG_BC,
    REG_DE,
    REG_HL,
    REG_SP,
};

/**
 * Proxy class representing double-byte CPU register value. The value can be
 * modified - the source register is modified in such case as well.
 *
 * @see ByteValue
 */
template<WordArg ARG>
class WordValue {
private:
    Emulator &emulator;

public:
    explicit WordValue(Emulator &emulator) :
            emulator(emulator) {
    }

    operator Word() const;

    WordValue<ARG> &operator=(Word value);

    template<WordArg A>
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
WordValue<WordArg::REG_AF>::operator Word() const;

template<>
WordValue<WordArg::REG_AF> &WordValue<WordArg::REG_AF>::operator=(Word value);


template<>
WordValue<WordArg::REG_BC>::operator Word() const;

template<>
WordValue<WordArg::REG_BC> &WordValue<WordArg::REG_BC>::operator=(Word value);


template<>
WordValue<WordArg::REG_DE>::operator Word() const;

template<>
WordValue<WordArg::REG_DE> &WordValue<WordArg::REG_DE>::operator=(Word value);


template<>
WordValue<WordArg::REG_HL>::operator Word() const;

template<>
WordValue<WordArg::REG_HL> &WordValue<WordArg::REG_HL>::operator=(Word value);


template<>
WordValue<WordArg::REG_SP>::operator Word() const;

template<>
WordValue<WordArg::REG_SP> &WordValue<WordArg::REG_SP>::operator=(Word value);

}


#endif //GAMEBOY_EMULATOR_WORDVALUE_H
