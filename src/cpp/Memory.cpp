//
//  Memory.cpp
//  gabboy
//
//  Created by Gabriel Lumbi on 2023-03-10.
//

#include "Memory.hpp"

void Memory::reset()
{
    data[0xFF40] = 0x91; // LCDC
    data[0xFF41] = 0x00; // STAT
}

Byte Memory::read(Address address) const
{
    return data[address];
}

bool Memory::write(Address address, Byte byte)
{
    if (address < ROM_END) { return false; }
    data[address] = byte;
    return true;
}

std::array<Byte, 256 * 256> Memory::lcd()
{
    /*
     Resolve the pixel data from the tile maps and tile data and return the pixel buffer.
     */

    std::array<Byte, 256 * 256> lcd_pixels;

    /*
     Resolve background:

     1. Map each tile in the background map the corresponding tile data in VRAM
     2. Unpack the tile bytes to pixel data to resolve the pixel color
     3. Assign the pixel color to the correct location in the pixel buffer

     Reference: https://gbdev.gg8.se/wiki/articles/Video_Display#LCDC.4_-_BG_.26_Window_Tile_Data_Select
     */

    // Switch between the two BG tile maps
    const bool bg_tile_map_display_select = (data[0xF40] >> 3) & 1; // LCDC bit 3
    const Address bg_tile_map_start = bg_tile_map_display_select ? 0x9C00 : 0x9800;

    // For each tile index in the background map
    for (int bg_index = 0; bg_index < 32 * 32; bg_index++) {

        // Select the tile map addressing mode
        const bool bg_tile_data_select = (data[0xF40] >> 4 & 1); // LCDC bit 4
        const Address bg_tile_data_start = bg_tile_data_select ? 0x8000 : 0x8800;
        const Byte bg_tile_data_offset = bg_tile_data_select
        ? uint8_t(data[bg_tile_map_start + bg_index])
        : int8_t(data[bg_tile_map_start + bg_index]);

        // Get the tile address
        const Address bg_tile_address = bg_tile_data_start + bg_tile_data_offset;

        // For each row in the tile data (2 bytes per row)
        for (int bg_tile_row = 0; bg_tile_row < 8; bg_tile_row++) {

            // Unpack the row
            const Byte lsb = data[bg_tile_address + (bg_tile_row * 2)];
            const Byte msb = data[bg_tile_address + (bg_tile_row * 2) + 1];

            // For each bit (8 bits per row)
            for (int bg_tile_col = 0; bg_tile_col < 8; bg_tile_col++) {

                // Get the two-bits pixel color
                const int shift = 7 - bg_tile_row;
                const uint8_t low_bit = (lsb >> shift) & 1;
                const uint8_t high_bit = (msb >> shift) & 2;
                const Byte pixel = low_bit | high_bit;

                // Assign the pixel color back to the pixel buffer
                const int x = (bg_index % 32) * 8 + bg_tile_col;
                const int y = (bg_index / 32) * 8 + bg_tile_row;
                lcd_pixels[x + y * 256] = pixel;
            }
        }
    }

    // TODO: Extract sprite data

    return lcd_pixels;
}

std::array<Byte, 32 * 32> Memory::bg_map()
{
    std::array<Byte, 32 * 32> bg_map;

    const bool bg_tile_map_display_select = (data[0xF40] >> 3) & 1; // LCDC bit 3
//    const Address bg_tile_map_start = bg_tile_map_display_select ? 0x9C00 : 0x9800;
    const Address bg_tile_map_start = 0x9800;

    for (int bg_index = 0; bg_index < 32 * 32; bg_index++) {
        bg_map[bg_index] = data[bg_tile_map_start + bg_index];
    }

    return bg_map;
}

std::array<Byte, 2 * 8> Memory::tile_data(Address address) {
    std::array<Byte, 2 * 8> tile_data;
    for (int i = 0; i < 16; i++) {
        tile_data[i] = data[address + i];
    }
    return tile_data;
}

std::array<Byte, 8 * 8> Memory::tile_pixels(Address address)
{
    std::array<Byte, 8 * 8> tile_pixels;

    for (int bg_tile_row = 0; bg_tile_row < 8; bg_tile_row++) {

        // Unpack the row
        const Byte lsb = data[address + (bg_tile_row * 2)];
        const Byte msb = data[address + (bg_tile_row * 2) + 1];

        // For each bit (8 bits per row)
        for (int bg_tile_col = 0; bg_tile_col < 8; bg_tile_col++) {
            // Get the two-bits pixel color
            const int shift = 7 - bg_tile_col;
            const uint8_t low_bit = (lsb >> shift) & 1;
            const uint8_t high_bit = (msb >> shift) & 2;
            const Byte pixel = low_bit | high_bit;
            tile_pixels[bg_tile_col + bg_tile_row * 8] = pixel;
        }
    }

    return tile_pixels;
}
