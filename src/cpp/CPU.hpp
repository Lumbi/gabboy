//
//  CPU.hpp
//  gabboy
//
//  Created by Gabriel Lumbi on 2023-03-10.
//

#ifndef CPU_hpp
#define CPU_hpp

#include "Data.hpp"
#include "Memory.hpp"
#include "CPUOp.hpp"

#include <memory>
#include <unordered_map>

class CPU {

public:
    using Flag = bool;
    using Opcode = Byte;
    using Operations = std::unordered_map<Opcode, CPUOp::Base*>;

public:
    CPU();
    ~CPU();

public:
    // Execution

    int cycle = 0;
    Opcode opcode = 0x00;

    // Registers

    Address program_counter = 0x0000;
    Address stack_pointer = 0xFFFE; // Default SP location
    Byte register_A = 0x00;
    Byte register_B = 0x00;
    Byte register_C = 0x00;
    Byte register_D = 0x00;
    Byte register_E = 0x00;
    Byte register_F = 0x00;
    Byte register_H = 0x00;
    Byte register_L = 0x00;

    Flag flag_Z = 0;
    Flag flag_N = 0;
    Flag flag_H = 0;
    Flag flag_C = 0;

private:
    Operations operations;
    Operations bit_operations;
    CPUOp::Base* current_operation = nullptr;

public:
    void run_cycle(Memory&);

private:
    void fetch(Memory&);
    void execute(Memory&);

private:
    // TODO: Deprecate
    Byte read(Memory&, Address);
    void write(Memory&, Address, Byte);
    void jump(Address);

};

#endif /* CPU_hpp */
