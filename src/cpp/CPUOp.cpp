//
//  CPUOp.cpp
//  gabboy
//
//  Created by Gabriel Lumbi on 2023-03-14.
//

#include "CPUOp.hpp"

#include "CPU.hpp"
#include "Memory.hpp"

#define CYCLE_GUARD(n) \
if (cycle < 0) cycle = n; \
cycle--; \
if (cycle > 0) return false; \
cycle = -1;

bool CPUOp::NOP::execute(CPU&, Memory&) {
    CYCLE_GUARD(1);
    return true;
}

// 8-bit arithmetic instructions

bool CPUOp::INC_r::execute(CPU &cpu, Memory &memory) {
    CYCLE_GUARD(1);
    r++;
    cpu.flag_Z = r == 0;
    cpu.flag_N = 0;
    cpu.flag_H = (r & (1 << 3)) != 0;
    return true;
}

bool CPUOp::DEC_r::execute(CPU &cpu, Memory &memory) {
    CYCLE_GUARD(1);
    r--;
    cpu.flag_Z = r == 0;
    cpu.flag_N = 1;
    cpu.flag_H = (r & (1 << 3)) != 0;
    return true;
}

bool CPUOp::XOR_r::execute(CPU &cpu, Memory &memory) {
    CYCLE_GUARD(1);
    cpu.register_A ^= r;
    cpu.flag_Z = cpu.register_A == 0;
    cpu.flag_N = 0;
    cpu.flag_H = 0;
    cpu.flag_C = 0;
    return true;
}

bool CPUOp::SUB_r::execute(CPU &cpu, Memory &memory) {
    CYCLE_GUARD(1);
    cpu.register_A -= r;
    cpu.flag_Z = cpu.register_A == 0;
    cpu.flag_N = 1;
    cpu.flag_H = (cpu.register_A & (1 << 3)) != 0;
    cpu.flag_C = (cpu.register_A & (1 << 7)) != 0;
    return true;
}

bool CPUOp::CP_n::execute(CPU &cpu, Memory &memory) {
    CYCLE_GUARD(2);
    Byte n = memory.read(cpu.program_counter++);
    Byte result = cpu.register_A - n;
    cpu.flag_Z = result == 0;
    cpu.flag_N = 1;
    cpu.flag_H = (result & (1 << 3)) != 0;
    cpu.flag_C = (result & (1 << 7)) != 0;
    return true;
}

// 8-bit load instructions

bool CPUOp::LD_r_n::execute(CPU& cpu, Memory& memory) {
    CYCLE_GUARD(2);
    r = memory.read(cpu.program_counter++);
    return true;
}

bool CPUOp::LDH_r_in::execute(CPU &cpu, Memory &memory) {
    CYCLE_GUARD(3);
    Address address = word(memory.read(cpu.program_counter++), 0xFF);
    r = memory.read(address);
    return true;
}

bool CPUOp::LD_r_r::execute(CPU& cpu, Memory& memory) {
    r1 = Byte(r2);
    return true;
}

// 16-bit arithmetic instructions

bool CPUOp::INC_rr::execute(CPU &cpu, Memory &memory) {
    CYCLE_GUARD(2);
    Word register_RR = word(r2, r1);
    register_RR++;
    r1 = msb(register_RR);
    r2 = lsb(register_RR);
    return true;
}

// 16-bit load instructions

bool CPUOp::LD_SP_HL::execute(CPU &cpu, Memory &memory) {
    CYCLE_GUARD(2);
    cpu.stack_pointer = word(cpu.register_L, cpu.register_H);
    return true;
}

bool CPUOp::LD_SP_nn::execute(CPU &cpu, Memory &memory) {
    CYCLE_GUARD(3);
    Byte nn_lsb = memory.read(cpu.program_counter++);
    Byte nn_msb = memory.read(cpu.program_counter++);
    cpu.stack_pointer = word(nn_lsb, nn_msb);
    return true;
}

bool CPUOp::LD_rr_nn::execute(CPU &cpu, Memory &memory) {
    CYCLE_GUARD(3);
    r2 = memory.read(cpu.program_counter++);
    r1 = memory.read(cpu.program_counter++);
    return true;
}
