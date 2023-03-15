//
//  CPU.cpp
//  gabboy
//
//  Created by Gabriel Lumbi on 2023-03-10.
//

#include "CPU.hpp"

CPU::CPU()
:
operations {
    { 0x00, new CPUOp::NOP() },

    // 8-bit load instructions

    { 0x3E, new CPUOp::LD_r_n(register_A) },
    { 0x16, new CPUOp::LD_r_n(register_D) },
    { 0xF0, new CPUOp::LDH_r_in(register_A) },
    { 0x7B, new CPUOp::LD_r_r(register_A, register_E) },
    { 0x7C, new CPUOp::LD_r_r(register_A, register_H) },
    { 0x06, new CPUOp::LD_r_n(register_B) },
    { 0x0E, new CPUOp::LD_r_n(register_C) },
    { 0x4F, new CPUOp::LD_r_r(register_C, register_A) },
    { 0x57, new CPUOp::LD_r_r(register_D, register_A) },
    { 0x1E, new CPUOp::LD_r_n(register_E) },
    { 0x67, new CPUOp::LD_r_r(register_H, register_A) },
    { 0x2E, new CPUOp::LD_r_n(register_L) },
    { 0x1A, new CPUOp::LD_r_irr(register_A, register_D, register_E) },
    { 0x36, new CPUOp::LD_iHL_n },
    { 0x77, new CPUOp::LD_iHL_r(register_A) },
    { 0x22, new CPUOp::LD_iHLI_A() },
    { 0x32, new CPUOp::LD_iHLD_A() },
    { 0xE2, new CPUOp::LD_iC_A() },
    { 0xE0, new CPUOp::LDH_in_A() },

    // 8-bit arithmetic instructions

    { 0x04, new CPUOp::INC_r(register_B) },
    { 0x0C, new CPUOp::INC_r(register_C) },
    { 0x24, new CPUOp::INC_r(register_H) },
    { 0x3D, new CPUOp::DEC_r(register_A) },
    { 0x05, new CPUOp::DEC_r(register_B) },
    { 0x0D, new CPUOp::DEC_r(register_C) },
    { 0x15, new CPUOp::DEC_r(register_D) },
    { 0x1D, new CPUOp::DEC_r(register_E) },
    { 0x90, new CPUOp::SUB_r(register_B) },
    { 0xAF, new CPUOp::XOR_r(register_A) },
    { 0xFE, new CPUOp::CP_n() },

    // 16-bit load instructions

    { 0xF9, new CPUOp::LD_SP_HL() },
    { 0x31, new CPUOp::LD_SP_nn() },
    { 0x11, new CPUOp::LD_rr_nn(register_D, register_E) },
    { 0x21, new CPUOp::LD_rr_nn(register_H, register_L) },
    { 0x08, new CPUOp::LD_inn_SP() },
    { 0xEA, new CPUOp::LD_inn_A() },
    { 0xC5, new CPUOp::PUSH_rr(register_B, register_C) },
    { 0xC1, new CPUOp::POP_rr(register_B, register_C) },

    // 16-bit arithmetic instructions

    { 0x13, new CPUOp::INC_rr(register_D, register_E) },
    { 0x23, new CPUOp::INC_rr(register_H, register_L) },

    // Jump / calls

    { 0x18, new CPUOp::JR_n() },
    { 0x28, new CPUOp::JR_Z_n() },
    { 0x20, new CPUOp::JR_NZ_n() },
    { 0xCD, new CPUOp::CALL_nn() },

    // Bit arithmetic instructions (0xCB shortcuts)

    { 0x17, new CPUOp::RLA() }
},
bit_operations {
    { 0x11, new CPUOp::RL_r(register_C) },
    { 0x7C, new CPUOp::BIT(7, register_H) }
}
{}

CPU::~CPU()
{
    for (auto&& operation : operations) {
        delete operation.second;
        operation.second = nullptr;
    }
}

void CPU::run_cycle(Memory& memory)
{
    execute(memory);
    fetch(memory);
    cycle++;
}

void CPU::fetch(Memory& memory) {
    if (current_operation) { return; }

    opcode = memory.read(program_counter++);

    if (opcode == 0xCB) {
        opcode = memory.read(program_counter++); // NOTE: This shortens bit operations by 1 cycle
        if (auto pair = bit_operations.find(opcode); pair != bit_operations.end()) {
            current_operation = pair->second;
        }
    } else {
        if (auto pair = operations.find(opcode); pair != operations.end()) {
            current_operation = pair->second;
        }
    }
}

void CPU::execute(Memory& memory) {
    if (current_operation) {
        bool done = current_operation->execute(*this, memory);
        if (done) { current_operation = nullptr; }
    }
}

Byte CPU::read(Memory& memory, Address address) {
    Byte data = memory.read(address);
    cycle++;
    return data;
}

void CPU::write(Memory& memory, Address address, Byte data) {
    memory.write(address, data);
    cycle++;
}

void CPU::jump(Address address)
{
    program_counter = address;
    cycle++;
}
