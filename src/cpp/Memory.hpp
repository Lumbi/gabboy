//
//  Memory.hpp
//  gabboy
//
//  Created by Gabriel Lumbi on 2023-03-10.
//

#ifndef Memory_hpp
#define Memory_hpp

#include "Data.hpp"

#include <memory>
#include <array>

class Memory {
public:
    static const Address ROM_BEGIN = 0x0000;
    static const Address ROM_END = 0x8000;
    static const Address INTERNAL_RAM_BEGIN = 0xC000;
    static const Address INTERNAL_RAM_END = 0xE000;

public:
    Memory(): data(new Byte[0xFFFF]) {} ;

    Byte read(Address) const;
    bool write(Address, Byte);

    void reset();

    template<std::size_t N>
    void load_rom(std::array<Byte, N>& program) {
        assert(N < ROM_END);
        std::copy(program.begin(), program.end(), data.get());
    };

    std::array<Byte, 256 * 256> lcd();
    std::array<Byte, 32 * 32> bg_map();
    std::array<Byte, 2 * 8> tile_data(Address);
    std::array<Byte, 8 * 8> tile_pixels(Address);

private:
    std::unique_ptr<Byte[]> data;
};

#endif /* Memory_hpp */
