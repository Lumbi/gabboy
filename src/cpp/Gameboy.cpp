//
//  Gameboy.cpp
//  gabboy
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

void Gameboy::print_lcd()
{
    auto lcd = memory.lcd();
    const int size = 128;
    const int subsample = 256 / size;
    printf(" "); for (int i = 0; i < size; i++) { printf("-"); } printf("\n");
    for (int y = 0; y < size; y++) {
        if (y % subsample != 0) { continue; }
        printf("|");
        for (int x = 0; x < size; x++) {
            if (y % subsample != 0) { continue; }
            switch (lcd[x + y * 256]) {
                case 0: printf(" "); break;
                case 1: printf("."); break;
                case 2: printf("0"); break;
                case 3: printf("#"); break;
                default: assert(false);
            }
        }
        printf("|\n");
    }
    printf(" "); for (int i = 0; i < size; i++) { printf("-"); } printf("\n");
}
