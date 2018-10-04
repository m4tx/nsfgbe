#ifndef GAMEBOY_EMULATOR_INPUTHANDLER_H
#define GAMEBOY_EMULATOR_INPUTHANDLER_H


namespace gb {

class InputHandler {
public:
    enum Key {
        RIGHT,
        LEFT,
        UP,
        DOWN,
        A,
        B,
        SELECT,
        START,
    };

    virtual bool isPressed(Key key) const = 0;
};

}


#endif //GAMEBOY_EMULATOR_INPUTHANDLER_H
