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
    CYCLE_GUARD(1);
    r1 = Byte(r2);
    return true;
}

bool CPUOp::LD_r_irr::execute(CPU &cpu, Memory &memory) {
    CYCLE_GUARD(2);
    r1 = memory.read(word(r3, r2));
    return true;
}

bool CPUOp::LD_iHL_r::execute(CPU &cpu, Memory &memory) {
    CYCLE_GUARD(2);
    memory.write(word(cpu.register_L, cpu.register_H), r);
    return true;
}

bool CPUOp::LD_iHL_n::execute(CPU &cpu, Memory &memory) {
    CYCLE_GUARD(3);
    Byte n = memory.read(cpu.program_counter++);
    memory.write(word(cpu.register_L, cpu.register_H), n);
    return true;
}

bool CPUOp::LD_iHLI_A::execute(CPU &cpu, Memory &memory) {
    CYCLE_GUARD(2);
    Address register_HL = word(cpu.register_L, cpu.register_H);
    memory.write(register_HL, cpu.register_A);
    register_HL++;
    cpu.register_H = msb(register_HL);
    cpu.register_L = lsb(register_HL);
    return true;
}

bool CPUOp::LD_iHLD_A::execute(CPU &cpu, Memory &memory) {
    CYCLE_GUARD(2);
    Word register_HL = word(cpu.register_L, cpu.register_H);
    memory.write(register_HL, cpu.register_A);
    register_HL--;
    cpu.register_H = msb(register_HL);
    cpu.register_L = lsb(register_HL);
    return true;
}

bool CPUOp::LD_iC_A::execute(CPU &cpu, Memory &memory) {
    CYCLE_GUARD(2);
    memory.write(word(cpu.register_C, 0xFF), cpu.register_A);
    return true;
}

bool CPUOp::LDH_in_A::execute(CPU &cpu, Memory &memory) {
    CYCLE_GUARD(3);
    Byte n = memory.read(cpu.program_counter++);
    memory.write(word(n, 0xFF), cpu.register_A);
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

bool CPUOp::LD_inn_SP::execute(CPU &cpu, Memory &memory) {
    CYCLE_GUARD(5);
    Byte nn_lsb = memory.read(cpu.program_counter++);
    Byte nn_msb = memory.read(cpu.program_counter++);
    Address write_location = word(nn_lsb, nn_msb);
    memory.write(write_location, lsb(cpu.stack_pointer));
    memory.write(write_location + 1, msb(cpu.stack_pointer));
    return true;
}

bool CPUOp::LD_inn_A::execute(CPU &cpu, Memory &memory) {
    CYCLE_GUARD(4);
    Byte nn_lsb = memory.read(cpu.program_counter++);
    Byte nn_msb = memory.read(cpu.program_counter++);
    memory.write(word(nn_lsb, nn_msb), cpu.register_A);
    return true;
}

bool CPUOp::PUSH_rr::execute(CPU &cpu, Memory &memory) {
    CYCLE_GUARD(4);
    memory.write(--cpu.stack_pointer, r1);
    memory.write(--cpu.stack_pointer, r2);
    return true;
}

bool CPUOp::POP_rr::execute(CPU &cpu, Memory &memory) {
    CYCLE_GUARD(3);
    r2 = memory.read(cpu.stack_pointer++);
    r1 = memory.read(cpu.stack_pointer++);
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

// Jump / calls

bool CPUOp::JR_n::execute(CPU &cpu, Memory &memory) {
    CYCLE_GUARD(3);
    Byte n = memory.read(cpu.program_counter++);
    cpu.program_counter += int8_t(n);
    return true;
}

bool CPUOp::JR_Z_n::execute(CPU &cpu, Memory &memory) {
    if (cpu.flag_Z) {
        CYCLE_GUARD(3);
        Byte n = memory.read(cpu.program_counter++);
        cpu.program_counter += int8_t(n);
    } else {
        CYCLE_GUARD(2);
        cpu.program_counter++; // dummy read
    }
    return true;
}

bool CPUOp::JR_NZ_n::execute(CPU &cpu, Memory &memory) {
    if (!cpu.flag_Z) {
        CYCLE_GUARD(3);
        Byte n = memory.read(cpu.program_counter++);
        cpu.program_counter += int8_t(n);
    } else {
        CYCLE_GUARD(2);
        cpu.program_counter++; // dummy read
    }
    return true;
}

bool CPUOp::CALL_nn::execute(CPU &cpu, Memory &memory) {
    CYCLE_GUARD(6);
    Byte nn_lsb = memory.read(cpu.program_counter++);
    Byte nn_msb = memory.read(cpu.program_counter++);
    Address nn = word(nn_lsb, nn_msb);
    memory.write(--cpu.stack_pointer, msb(cpu.program_counter));
    memory.write(--cpu.stack_pointer, lsb(cpu.program_counter));
    cpu.program_counter = nn;
    return true;
}

// 8-bit shift, rotate, bit instructions

bool CPUOp::RLA::execute(CPU &cpu, Memory &memory) {
    CYCLE_GUARD(1);
    bool carry = cpu.register_A & (1 << 7);
    Byte result = (cpu.register_A << 1) | cpu.flag_C;
    cpu.register_A = result;
    cpu.flag_N = 0;
    cpu.flag_H = 0;
    cpu.flag_C = carry;
    return true;
}


bool CPUOp::RL_r::execute(CPU &cpu, Memory &memory) {
    CYCLE_GUARD(2);
    bool carry = r & (1 << 7);
    Byte result = (r << 1) | cpu.flag_C;
    r = result;
    cpu.flag_Z = r == 0;
    cpu.flag_N = 0;
    cpu.flag_H = 0;
    cpu.flag_C = carry;
    return true;
}

bool CPUOp::BIT::execute(CPU &cpu, Memory &memory) {
    CYCLE_GUARD(2);
    cpu.flag_Z = (r & (1 << bit)) == 0;
    cpu.flag_N = 0;
    cpu.flag_H = 1;
    return true;
}
