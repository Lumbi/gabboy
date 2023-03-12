//
//  Memory.hpp
//  gabboy
//
//  Created by Gabriel Lumbi on 2023-03-10.
//

#ifndef Memory_hpp
#define Memory_hpp

#include <memory>
#include <array>

class Memory {
public:
    using Address = uint16_t;
    using Byte = uint8_t;
    using Word = uint16_t;

    static const Memory::Address ROM_BEGIN = 0x0000;
    static const Memory::Address ROM_END = 0x8000;
    static const Memory::Address INTERNAL_RAM_BEGIN = 0xC000;
    static const Memory::Address INTERNAL_RAM_END = 0xE000;

public:
    Memory(): data(new Byte[0xFFFF]) {} ;

    Byte read(Address) const;
    bool write(Address, Byte);

    template<std::size_t N>
    void load_rom(std::array<Byte, N>& program) {
        assert(N < ROM_END);
        std::copy(program.begin(), program.end(), data.get());
    };

private:
    std::unique_ptr<Byte[]> data;
};

inline Memory::Byte lsb(Memory::Word word) { return word & 0xFF; }
inline Memory::Byte msb(Memory::Word word) { return word >> 8; }
inline Memory::Word word(Memory::Byte lsb, Memory::Byte msb) { return msb << 8 | lsb; };

#endif /* Memory_hpp */
