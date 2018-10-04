# nsfgbe

(Not So Fast Game Boy Emulator)

Nintendo Game Boy emulator written in modern C++17.

## Building

### Requirements
 
* C++17-capable compiler
* SDL2
* Boost program_options
* Google Test

### Running

```bash
mkdir build
cd build
cmake ..
make
./gameboy_emulator path-to-rom.gb
```

## Keymap

* `←`/`↑`/`→`/`↓` - D-Pad
* `X` - A
* `Z` - B
* `Right Shift` - Select
* `Return` - Start
