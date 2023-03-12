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
    void run(CPU::CycleCount cycles = 0);

public:
    CPU cpu;
    Memory memory;
};

#endif /* Gameboy_hpp */
