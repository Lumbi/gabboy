//
//  CPU.cpp
//  gabboy
//
//  Created by Gabriel Lumbi on 2023-03-10.
//

#include "CPU.hpp"

void CPU::fetch(Memory& memory) {
    opcode = read(memory, program_counter++);
}

void CPU::execute(Memory& memory) {
    switch (opcode) {
        case 0x00: // NOP
            break;

        case 0x3E: { // LD A, n
            register_A = read(memory, program_counter++);
            break;
        }

        case 0xF0: { // LDH A, (n)
            Memory::Address address = word(read(memory, program_counter++), 0xFF);
            register_A = read(memory, address);
            break;
        }

        case 0x7B: { // LD A, E
            register_A = register_E;
            break;
        }

        case 0x1A: { // LD A, (DE)
            register_A = read(memory, word(register_E, register_D));
            break;
        }

        case 0x06: { // LD B, n
            register_B = read(memory, program_counter++);
            break;
        }

        case 0x0E: { // LD C, n
            register_C = read(memory, program_counter++);
            break;
        }

        case 0x57: { // LD D, A
            register_D = register_A;
            break;
        }

        case 0x1E: { // LD E, n
            register_E = read(memory, program_counter++);
            break;
        }

        case 0x67: { // LD H, A
            register_H = register_A;
            break;
        }

        case 0x2E: { // LD L, n
            register_L = read(memory, program_counter++);
            break;
        }

        case 0x04: { // INC B
            register_B++;
            flag_Z = register_B == 0;
            flag_N = 0;
            flag_H = (register_B & (1 << 3)) != 0;
            break;
        }

        case 0x0C: { // INC C
            register_C++;
            flag_Z = register_C == 0;
            flag_N = 0;
            flag_H = (register_C & (1 << 3)) != 0;
            break;
        }

        case 0x3D: { // DEC A
            register_A--;
            flag_Z = register_A == 0;
            flag_N = 1;
            flag_H = (register_A & (1 << 3)) != 0;
            break;
        }

        case 0x05: { // DEC B
            register_B--;
            flag_Z = register_B == 0;
            flag_N = 1;
            flag_H = (register_B & (1 << 3)) != 0;
            break;
        }

        case 0x0D: { // DEC C
            register_C--;
            flag_Z = register_C == 0;
            flag_N = 1;
            flag_H = (register_C & (1 << 3)) != 0;
            break;
        }

        case 0x1D: { // DEC E
            register_E--;
            flag_Z = register_E == 0;
            flag_N = 1;
            flag_H = (register_E & (1 << 3)) != 0;
            break;
        }

        case 0x13: { // INC DE
            Memory::Word register_DE = word(register_E, register_D);
            register_DE++;
            register_D = msb(register_DE);
            register_E = lsb(register_DE);
            break;
        }

        case 0x23: { // INC HL
            Memory::Word register_HL = word(register_L, register_H);
            register_HL++;
            register_H = msb(register_HL);
            register_L = lsb(register_HL);
            break;
        }

        case 0xAF: { // XOR A
            register_A = 0x00;
            flag_Z = 1;
            flag_N = 0;
            flag_H = 0;
            flag_C = 0;
            break;
        }

        case 0xFE: { // CP n
            Memory::Byte n = read(memory, program_counter++);
            Memory::Byte result = register_A - n;
            flag_Z = result == 0;
            flag_N = 1;
            flag_H = (result & (1 << 3)) != 0;
            flag_C = (result & (1 << 7)) != 0;
            break;
        }

        case 0xF9: { // LD SP, (HL)
            stack_pointer = word(register_L, register_H);
            cycle++;
            break;
        }

        case 0x31: { // LD SP, nn
            Memory::Byte nn_lsb = read(memory, program_counter++);
            Memory::Byte nn_msb = read(memory, program_counter++);
            stack_pointer = word(nn_lsb, nn_msb);
            break;
        }

        case 0x11: { // LD DE, nn
            register_E = read(memory, program_counter++);
            register_D = read(memory, program_counter++);
            break;
        }

        case 0x21: { // LD HL, nn
            register_L = read(memory, program_counter++);
            register_H = read(memory, program_counter++);
            break;
        }

        case 0x08: { // LD (nn), SP
            Memory::Byte nn_lsb = read(memory, program_counter++);
            Memory::Byte nn_msb = read(memory, program_counter++);
            Memory::Address write_location = word(nn_lsb, nn_msb);
            write(memory, write_location, lsb(stack_pointer));
            write(memory, write_location + 1, msb(stack_pointer));
            break;
        }

        case 0x36: { // LD (HL), n
            Memory::Byte n = read(memory, program_counter++);
            write(memory, word(register_L, register_H), n);
            break;
        }

        case 0x77: { // LD (HL), A
            write(memory, word(register_L, register_H), register_A);
            break;
        }

        case 0x22: { // LD (HL+), A
            Memory::Address register_HL = word(register_L, register_H);
            write(memory, register_HL, register_A);
            register_HL++;
            register_H = msb(register_HL);
            register_L = lsb(register_HL);
            break;
        }

        case 0x32: { // LD (HL-), A
            Memory::Word register_HL = word(register_L, register_H);
            write(memory, register_HL, register_A);
            register_HL--;
            register_H = msb(register_HL);
            register_L = lsb(register_HL);
            break;
        }

        case 0xE2: { // LD (C), A
            Memory::Address address = word(register_C, 0xFF);
            write(memory, address, register_A);
            break;
        }

        case 0xE0: { // LDH (n), A
            Memory::Byte n = read(memory, program_counter++);
            Memory::Address address = word(n, 0xFF);
            write(memory, address, register_A);
            break;
        }

        case 0xEA: { // LD (nn), A
            Memory::Byte nn_lsb = read(memory, program_counter++);
            Memory::Byte nn_msb = read(memory, program_counter++);
            Memory::Address address = word(nn_lsb, nn_msb);
            write(memory, address, register_A);
            break;
        }

        case 0x18: { // JR, n
            Memory::Byte n = read(memory, program_counter++);
            jump(program_counter + int8_t(n));
            break;
        }

        case 0x28: { // JR Z, n
            Memory::Byte n = read(memory, program_counter++);
            if (flag_Z) { jump(program_counter + int8_t(n)); }
            break;
        }

        case 0x20: { // JR NZ, n
            Memory::Byte n = read(memory, program_counter++);
            if (!flag_Z) { jump(program_counter + int8_t(n)); }
            break;
        }

        case 0xCD: { // CALL nn
            Memory::Byte nn_lsb = read(memory, program_counter++);
            Memory::Byte nn_msb = read(memory, program_counter++);
            Memory::Address nn = word(nn_lsb, nn_msb);
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

Memory::Byte CPU::read(Memory& memory, Memory::Address address) {
    Memory::Byte data = memory.read(address);
    cycle++;
    return data;
}

void CPU::write(Memory& memory, Memory::Address address, Memory::Byte data) {
    memory.write(address, data);
    cycle++;
}

void CPU::jump(Memory::Address address)
{
    program_counter = address;
    cycle++;
}
