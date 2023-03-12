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

        case 0x0E: { // LD C, n
            register_C = read(memory, program_counter++);
            break;
        }

        case 0x0C: { // INC C
            register_C++;
            flag_Z = (register_C & 1) == 0;
            flag_N = 0;
            flag_H = (register_C & (1 << 3)) != 0;
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

        case 0xF9: { // LD SP, (HL)
            stack_pointer = register_HL();
            cycle++;
            break;
        }

        case 0x31: { // LD SP, nn
            Memory::Byte nn_lsb = read(memory, program_counter++);
            Memory::Byte nn_msb = read(memory, program_counter++);
            stack_pointer = word(nn_lsb, nn_msb);
            break;
        }

        case 0x21: { // LD HL, nn
            Memory::Byte nn_lsb = read(memory, program_counter++);
            Memory::Byte nn_msb = read(memory, program_counter++);
            set_register_HL(word(nn_lsb, nn_msb));
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
            write(memory, register_HL(), n);
            break;
        }

        case 0x77: { // LD (HL), A
            write(memory, register_HL(), register_A);
            break;
        }

        case 0x32: { // LD (HL-), A
            write(memory, register_HL(), register_A);
            set_register_HL(register_HL()-1);
            break;
        }

        case 0xE2: { // LD (C), A
            Memory::Address address = word(register_C, 0xFF);
            write(memory, address, register_A);
            break;
        }

        case 0x20: { // JP NZ, n
            Memory::Byte n = read(memory, program_counter++);
            if (!flag_Z) { jump(program_counter + int8_t(n)); }
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
