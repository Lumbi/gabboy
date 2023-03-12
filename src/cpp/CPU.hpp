//
//  CPU.hpp
//  gabboy
//
//  Created by Gabriel Lumbi on 2023-03-10.
//

#ifndef CPU_hpp
#define CPU_hpp

#include "Memory.hpp"

class CPU {

public:
    using Flag = bool;
    using CycleCount = unsigned int;

public:
    // Execution

    CycleCount cycle = 0;
    Memory::Byte opcode = 0x00;

    // Registers

    Memory::Address program_counter = 0x0000;
    Memory::Address stack_pointer = 0xFFFE; // Default SP location
    Memory::Byte register_A = 0x00;
    Memory::Byte register_B = 0x00;
    Memory::Byte register_C = 0x00;
    Memory::Byte register_D = 0x00;
    Memory::Byte register_E = 0x00;
    Memory::Byte register_F = 0x00;
    Memory::Byte register_H = 0x00;
    Memory::Byte register_L = 0x00;

    Memory::Word register_HL() const { return register_H << 8 | register_L; }
    void set_register_HL(Memory::Word data) { register_H = data >> 8; register_L = data & 0xFF; };

    Flag flag_Z = 0;
    Flag flag_N = 0;
    Flag flag_H = 0;
    Flag flag_C = 0;

public:
    void fetch(Memory&);
    void execute(Memory&);

private:
    Memory::Byte read(Memory&, Memory::Address);
    void write(Memory&, Memory::Address, Memory::Byte);
    void jump(Memory::Address);

};

#endif /* CPU_hpp */
