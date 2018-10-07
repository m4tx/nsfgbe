#ifndef GAMEBOY_EMULATOR_BYTEVALUE_H
#define GAMEBOY_EMULATOR_BYTEVALUE_H


#include <emulator/Emulator.hpp>

namespace nsfgbe {

enum class ByteArg {
    REG_B,
    REG_C,
    REG_D,
    REG_E,
    REG_H,
    REG_L,
    PTR_HL,
    REG_A,
    PTR_BC,
    PTR_DE,
};

/**
 * Proxy class representing single-byte CPU register/pointer value. The value
 * can be modified - the source register/value in memory is modified in
 * such case as well.
 *
 * @see WordValue
 */
template<ByteArg ARG>
class ByteValue {
private:
    Emulator &emulator;

public:
    explicit ByteValue(Emulator &emulator) :
            emulator(emulator) {
    }

    operator Byte() const;

    ByteValue<ARG> &operator=(Byte value);

    template<ByteArg A>
    ByteValue<ARG> &operator=(ByteValue<A> const &value) {
        *this = static_cast<Byte>(value);
        return *this;
    }

    ByteValue<ARG> &operator--() {
        *this = *this - 1;
        return *this;
    }

    ByteValue<ARG> &operator++() {
        *this = *this + 1;
        return *this;
    }

    ByteValue<ARG> &operator&=(Byte value) {
        *this = *this & value;
        return *this;
    }

    ByteValue<ARG> &operator|=(Byte value) {
        *this = *this | value;
        return *this;
    }

    ByteValue<ARG> &operator<<=(int shift) {
        *this = *this << shift;
        return *this;
    }

    ByteValue<ARG> &operator>>=(int shift) {
        *this = *this >> shift;
        return *this;
    }
};

template<>
ByteValue<ByteArg::REG_B>::operator Byte() const;

template<>
ByteValue<ByteArg::REG_B> &ByteValue<ByteArg::REG_B>::operator=(Byte value);


template<>
ByteValue<ByteArg::REG_C>::operator Byte() const;

template<>
ByteValue<ByteArg::REG_C> &ByteValue<ByteArg::REG_C>::operator=(Byte value);


template<>
ByteValue<ByteArg::REG_D>::operator Byte() const;

template<>
ByteValue<ByteArg::REG_D> &ByteValue<ByteArg::REG_D>::operator=(Byte value);


template<>
ByteValue<ByteArg::REG_E>::operator Byte() const;

template<>
ByteValue<ByteArg::REG_E> &ByteValue<ByteArg::REG_E>::operator=(Byte value);


template<>
ByteValue<ByteArg::REG_H>::operator Byte() const;

template<>
ByteValue<ByteArg::REG_H> &ByteValue<ByteArg::REG_H>::operator=(Byte value);


template<>
ByteValue<ByteArg::REG_L>::operator Byte() const;

template<>
ByteValue<ByteArg::REG_L> &ByteValue<ByteArg::REG_L>::operator=(Byte value);


template<>
ByteValue<ByteArg::PTR_HL>::operator Byte() const;

template<>
ByteValue<ByteArg::PTR_HL> &ByteValue<ByteArg::PTR_HL>::operator=(Byte value);


template<>
ByteValue<ByteArg::REG_A>::operator Byte() const;

template<>
ByteValue<ByteArg::REG_A> &ByteValue<ByteArg::REG_A>::operator=(Byte value);


template<>
ByteValue<ByteArg::PTR_BC>::operator Byte() const;

template<>
ByteValue<ByteArg::PTR_BC> &ByteValue<ByteArg::PTR_BC>::operator=(Byte value);


template<>
ByteValue<ByteArg::PTR_DE>::operator Byte() const;

template<>
ByteValue<ByteArg::PTR_DE> &ByteValue<ByteArg::PTR_DE>::operator=(Byte value);

}


#endif //GAMEBOY_EMULATOR_BYTEVALUE_H
