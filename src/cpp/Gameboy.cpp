//
//  Gameboy.cpp
//  gameboy-cpu
//
//  Created by Gabriel Lumbi on 2023-03-10.
//

#include "Gameboy.hpp"


void Gameboy::run(CPU::CycleCount cycles)
{
    bool stop = false;
    while (!stop) {
        cpu.fetch(memory);
        cpu.execute(memory);
        stop = cycles > 0 && cpu.cycle >= cycles;
    }
}
