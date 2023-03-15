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
    { 0xF0, new CPUOp::LDH_r_in(register_A) },
    { 0x7B, new CPUOp::LD_r_r(register_A, register_E) },
    { 0x7C, new CPUOp::LD_r_r(register_A, register_H) },
    { 0x06, new CPUOp::LD_r_n(register_B) },
    { 0x0E, new CPUOp::LD_r_n(register_C) },
    { 0x57, new CPUOp::LD_r_r(register_D, register_A) },
    { 0x1E, new CPUOp::LD_r_n(register_E) },
    { 0x67, new CPUOp::LD_r_r(register_H, register_A) },
    { 0x2E, new CPUOp::LD_r_n(register_L) },

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

    // 16-bit arithmetic instructions

    { 0x13, new CPUOp::INC_rr(register_D, register_E) },
    { 0x23, new CPUOp::INC_rr(register_H, register_L) },

    // 16-bit load instructions

    { 0xF9, new CPUOp::LD_SP_HL() },
    { 0x31, new CPUOp::LD_SP_nn() },
    { 0x11, new CPUOp::LD_rr_nn(register_D, register_E) },
    { 0x21, new CPUOp::LD_rr_nn(register_H, register_L) }
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
    if (current_operation) {
        bool done = current_operation->execute(*this, memory);
        if (done) { current_operation = nullptr; }
    }

    if (!current_operation) {
        fetch(memory);
        execute(memory);
    }

    cycle++;
}

void CPU::fetch(Memory& memory) {
    opcode = memory.read(program_counter++);
}

void CPU::execute(Memory& memory) {
    if (auto pair = operations.find(opcode); pair != operations.end()) {
        current_operation = pair->second;
        return;
    }

    // TODO: Refactor to CPUOp
    switch (opcode) {
        case 0x1A: // LD A, (DE)
            register_A = read(memory, word(register_E, register_D));
            break;

        case 0x08: { // LD (nn), SP
            Byte nn_lsb = read(memory, program_counter++);
            Byte nn_msb = read(memory, program_counter++);
            Address write_location = word(nn_lsb, nn_msb);
            write(memory, write_location, lsb(stack_pointer));
            write(memory, write_location + 1, msb(stack_pointer));
            break;
        }

        case 0x36: { // LD (HL), n
            Byte n = read(memory, program_counter++);
            write(memory, word(register_L, register_H), n);
            break;
        }

        case 0x77: { // LD (HL), A
            write(memory, word(register_L, register_H), register_A);
            break;
        }

        case 0x22: { // LD (HL+), A
            Address register_HL = word(register_L, register_H);
            write(memory, register_HL, register_A);
            register_HL++;
            register_H = msb(register_HL);
            register_L = lsb(register_HL);
            break;
        }

        case 0x32: { // LD (HL-), A
            Word register_HL = word(register_L, register_H);
            write(memory, register_HL, register_A);
            register_HL--;
            register_H = msb(register_HL);
            register_L = lsb(register_HL);
            break;
        }

        case 0xE2: { // LD (C), A
            Address address = word(register_C, 0xFF);
            write(memory, address, register_A);
            break;
        }

        case 0xE0: { // LDH (n), A
            Byte n = read(memory, program_counter++);
            Address address = word(n, 0xFF);
            write(memory, address, register_A);
            break;
        }

        case 0xEA: { // LD (nn), A
            Byte nn_lsb = read(memory, program_counter++);
            Byte nn_msb = read(memory, program_counter++);
            Address address = word(nn_lsb, nn_msb);
            write(memory, address, register_A);
            break;
        }

        case 0x18: { // JR, n
            Byte n = read(memory, program_counter++);
            jump(program_counter + int8_t(n));
            break;
        }

        case 0x28: { // JR Z, n
            Byte n = read(memory, program_counter++);
            if (flag_Z) { jump(program_counter + int8_t(n)); }
            break;
        }

        case 0x20: { // JR NZ, n
            Byte n = read(memory, program_counter++);
            if (!flag_Z) { jump(program_counter + int8_t(n)); }
            break;
        }

        case 0xCD: { // CALL nn
            Byte nn_lsb = read(memory, program_counter++);
            Byte nn_msb = read(memory, program_counter++);
            Address nn = word(nn_lsb, nn_msb);
            cycle++;
            write(memory, --stack_pointer, msb(program_counter));
            write(memory, --stack_pointer, lsb(program_counter));
            program_counter = nn;
            break;
        }

        case 0xCB: { // CB-prefixed instructions
            fetch(memory);
            switch (opcode) {
                case 0x7C: { // BIT 7, H
                    flag_Z = (register_H & (1 << 7)) == 0;
                    flag_N = 0;
                    flag_H = 1;
                    break;
                }
            }
        }

        default:
            break;
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
