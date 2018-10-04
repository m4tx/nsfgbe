# nsfgbe [![Build Status](https://travis-ci.com/m4tx/nsfgbe.svg?branch=master)](https://travis-ci.com/m4tx/nsfgbe)

(Not So Fast Game Boy Emulator)

Nintendo Game Boy emulator written in modern C++17.

## Building

### Requirements
 
* CMake
* C++17-capable compiler (recommended: G++ 8.0+)
* SDL2
* Boost program_options
* Google Test

### Running

```bash
mkdir build
cd build
cmake ..
make
./nsfgbe path-to-rom.gb
```

## Keymap

* `←`/`↑`/`→`/`↓` - D-Pad
* `X` - A
* `Z` - B
* `Right Shift` - Select
* `Return` - Start
