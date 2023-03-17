//
//  Gameboy.hpp
//  gabboy
//
//  Created by Gabriel Lumbi on 2023-03-10.
//

#ifndef Gameboy_hpp
#define Gameboy_hpp

#include "Memory.hpp"
#include "CPU.hpp"

class Gameboy {
public:
    void run(int cycles = 0);
    void print_lcd();

    // DEBUG

public:
    void debug_print_bg_map();
    void debug_print_tile_data(Address);
    void debug_print_tile_pixels(Address);

public:
    CPU cpu;
    Memory memory;
};

#endif /* Gameboy_hpp */
