//
//  Gameboy.cpp
//  gabboy
//
//  Created by Gabriel Lumbi on 2023-03-10.
//

#include "Gameboy.hpp"

#include "Debug.hpp"

void Gameboy::run(int cycles)
{
    bool stop = false;
    while (!stop) {
        cpu.run_cycle(memory);
        stop = cycles > 0 && cpu.cycle >= cycles;
    }
}

void Gameboy::print_lcd()
{
    auto lcd = memory.lcd();
    const int size_x = 160;
    const int size_y = 144;
    printf(" "); for (int i = 0; i < size_x; i++) { printf("-"); } printf("\n");
    for (int y = 0; y < size_y; y++) {
        printf("|");
        for (int x = 0; x < size_x; x++) {
            // TODO: Use 0xFF47 (BGP) for palette
            switch (lcd[x + y * 256]) {
                case 0: printf(" "); break;
                case 1: case 2: case 3: printf("#"); break;
                default: assert(false);
            }
        }
        printf("|\n");
    }
    printf(" "); for (int i = 0; i < size_x; i++) { printf("-"); } printf("\n");
}

// DEBUG

void Gameboy::debug_print_bg_map()
{
    auto bg_map = memory.bg_map();
    debug_print_buffer_2D<32, 32>(bg_map);
}

void Gameboy::debug_print_tile_data(Address address)
{
    auto tile_data = memory.tile_data(address);
    debug_print_buffer_2D<2, 8>(tile_data);
}

void Gameboy::debug_print_tile_pixels(Address address)
{
    auto tile = memory.tile_pixels(address);
    debug_print_buffer_2D<8, 8>(tile);
}
