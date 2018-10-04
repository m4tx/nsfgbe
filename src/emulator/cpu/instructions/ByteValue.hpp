#ifndef GAMEBOY_EMULATOR_BYTEVALUE_H
#define GAMEBOY_EMULATOR_BYTEVALUE_H


#include <emulator/Emulator.hpp>

namespace gb {

enum InstrArgByte {
    ARG_REG_B,
    ARG_REG_C,
    ARG_REG_D,
    ARG_REG_E,
    ARG_REG_H,
    ARG_REG_L,
    ARG_PTR_HL,
    ARG_REG_A,
    ARG_PTR_BC,
    ARG_PTR_DE,
};

/**
 * Proxy class representing single-byte CPU register/pointer value. The value
 * can be modified - the source register/value in memory is modified in
 * such case as well.
 *
 * @see WordValue
 */
template<InstrArgByte ARG>
class ByteValue {
private:
    Emulator &emulator;

public:
    explicit ByteValue(Emulator &emulator) :
            emulator(emulator) {
    }

    operator Byte() const;

    ByteValue<ARG> &operator=(Byte value);

    template<InstrArgByte A>
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
ByteValue<ARG_REG_B>::operator Byte() const;

template<>
ByteValue<ARG_REG_B> &ByteValue<ARG_REG_B>::operator=(Byte value);


template<>
ByteValue<ARG_REG_C>::operator Byte() const;

template<>
ByteValue<ARG_REG_C> &ByteValue<ARG_REG_C>::operator=(Byte value);


template<>
ByteValue<ARG_REG_D>::operator Byte() const;

template<>
ByteValue<ARG_REG_D> &ByteValue<ARG_REG_D>::operator=(Byte value);


template<>
ByteValue<ARG_REG_E>::operator Byte() const;

template<>
ByteValue<ARG_REG_E> &ByteValue<ARG_REG_E>::operator=(Byte value);


template<>
ByteValue<ARG_REG_H>::operator Byte() const;

template<>
ByteValue<ARG_REG_H> &ByteValue<ARG_REG_H>::operator=(Byte value);


template<>
ByteValue<ARG_REG_L>::operator Byte() const;

template<>
ByteValue<ARG_REG_L> &ByteValue<ARG_REG_L>::operator=(Byte value);


template<>
ByteValue<ARG_PTR_HL>::operator Byte() const;

template<>
ByteValue<ARG_PTR_HL> &ByteValue<ARG_PTR_HL>::operator=(Byte value);


template<>
ByteValue<ARG_REG_A>::operator Byte() const;

template<>
ByteValue<ARG_REG_A> &ByteValue<ARG_REG_A>::operator=(Byte value);


template<>
ByteValue<ARG_PTR_BC>::operator Byte() const;

template<>
ByteValue<ARG_PTR_BC> &ByteValue<ARG_PTR_BC>::operator=(Byte value);


template<>
ByteValue<ARG_PTR_DE>::operator Byte() const;

template<>
ByteValue<ARG_PTR_DE> &ByteValue<ARG_PTR_DE>::operator=(Byte value);

}


#endif //GAMEBOY_EMULATOR_BYTEVALUE_H
