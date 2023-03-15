//
//  OpcodeTests.m
//  gabboyTests
//
//  Created by Gabriel Lumbi on 2023-03-10.
//

#import <XCTest/XCTest.h>

#import "Gameboy.hpp"
#import <memory>

@interface OpcodeTests : XCTestCase

@end

@implementation OpcodeTests

-(void)test_NOP {
    Gameboy gameboy;
    std::array<Byte, 1> program = { 0x00 };
    gameboy.memory.load_rom(program);
    gameboy.run(1);
    XCTAssertEqual(gameboy.cpu.program_counter, 1);
}

-(void)test_LD_A_n {
    Gameboy gameboy;
    std::array<Byte, 2> program = { 0x3E, 0xAB };
    gameboy.memory.load_rom(program);
    gameboy.run(3);
    XCTAssertEqual(gameboy.cpu.register_A, 0xAB);
    XCTAssertEqual(gameboy.cpu.program_counter, 3);
}

-(void)test_LD_D_n {
    Gameboy gameboy;
    std::array<Byte, 2> program = { 0x16, 0xAB };
    gameboy.memory.load_rom(program);
    gameboy.run(3);
    XCTAssertEqual(gameboy.cpu.register_D, 0xAB);
    XCTAssertEqual(gameboy.cpu.program_counter, 3);
}

-(void)test_LDH_A_in {
    Gameboy gameboy;
    std::array<Byte, 3> program = { 0xF0, 0xAB };
    gameboy.memory.load_rom(program);
    gameboy.memory.write(0xFFAB, 0xCD);
    gameboy.run(4);
    XCTAssertEqual(gameboy.cpu.register_A, 0xCD);
    XCTAssertEqual(gameboy.cpu.program_counter, 3);
}

-(void)test_LD_A_E {
    Gameboy gameboy;
    std::array<Byte, 1> program = { 0x7B };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_E = 0xAB;
    gameboy.run(2);
    XCTAssertEqual(gameboy.cpu.register_A, 0xAB);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_LD_A_H {
    Gameboy gameboy;
    std::array<Byte, 1> program = { 0x7C };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_H = 0xAB;
    gameboy.run(2);
    XCTAssertEqual(gameboy.cpu.register_A, 0xAB);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_LD_A_iDE {
    Gameboy gameboy;
    std::array<Byte, 1> program = { 0x1A };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_D = 0xC0;
    gameboy.cpu.register_E = 0x11;
    gameboy.memory.write(0xC011, 0xAB);
    gameboy.run(3);
    XCTAssertEqual(gameboy.cpu.register_A, 0xAB);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_LD_B_n {
    Gameboy gameboy;
    std::array<Byte, 2> program = { 0x06, 0xAB };
    gameboy.memory.load_rom(program);
    gameboy.run(3);
    XCTAssertEqual(gameboy.cpu.register_B, 0xAB);
    XCTAssertEqual(gameboy.cpu.program_counter, 3);
}

-(void)test_LD_C_n {
    Gameboy gameboy;
    std::array<Byte, 2> program = { 0x0E, 0xAB };
    gameboy.memory.load_rom(program);
    gameboy.run(3);
    XCTAssertEqual(gameboy.cpu.register_C, 0xAB);
    XCTAssertEqual(gameboy.cpu.program_counter, 3);
}

-(void)test_LD_C_A {
    Gameboy gameboy;
    std::array<Byte, 1> program = { 0x4F };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_A = 0xAB;
    gameboy.run(2);
    XCTAssertEqual(gameboy.cpu.register_C, 0xAB);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_LD_D_A {
    Gameboy gameboy;
    std::array<Byte, 1> program = { 0x57 };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_A = 0xAB;
    gameboy.run(2);
    XCTAssertEqual(gameboy.cpu.register_D, 0xAB);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_LD_E_n {
    Gameboy gameboy;
    std::array<Byte, 2> program = { 0x1E, 0xAB };
    gameboy.memory.load_rom(program);
    gameboy.run(3);
    XCTAssertEqual(gameboy.cpu.register_E, 0xAB);
    XCTAssertEqual(gameboy.cpu.program_counter, 3);
}

-(void)test_LD_H_A {
    Gameboy gameboy;
    std::array<Byte, 1> program = { 0x67 };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_A = 0xAB;
    gameboy.run(2);
    XCTAssertEqual(gameboy.cpu.register_H, 0xAB);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_LD_L_n {
    Gameboy gameboy;
    std::array<Byte, 2> program = { 0x2E, 0xAB };
    gameboy.memory.load_rom(program);
    gameboy.run(3);
    XCTAssertEqual(gameboy.cpu.register_L, 0xAB);
    XCTAssertEqual(gameboy.cpu.program_counter, 3);
}

-(void)test_XOR_A {
    Gameboy gameboy;
    std::array<Byte, 1> program { 0xAF };
    gameboy.memory.load_rom(program);
    gameboy.run(2);
    XCTAssertEqual(gameboy.cpu.register_A, 0x00);
    XCTAssertEqual(gameboy.cpu.flag_Z, 1);
    XCTAssertEqual(gameboy.cpu.flag_N, 0);
    XCTAssertEqual(gameboy.cpu.flag_H, 0);
    XCTAssertEqual(gameboy.cpu.flag_C, 0);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_INC_B_Z0 {
    Gameboy gameboy;
    std::array<Byte, 1> program = { 0x04 };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_B = 0x00;
    gameboy.run(2);
    XCTAssertEqual(gameboy.cpu.register_B, 0x01);
    XCTAssertEqual(gameboy.cpu.flag_Z, 0);
    XCTAssertEqual(gameboy.cpu.flag_N, 0);
    XCTAssertEqual(gameboy.cpu.flag_H, 0);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_INC_B_Z1 {
    Gameboy gameboy;
    std::array<Byte, 1> program = { 0x04 };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_B = 0xFF;
    gameboy.run(2);
    XCTAssertEqual(gameboy.cpu.register_B, 0x00);
    XCTAssertEqual(gameboy.cpu.flag_Z, 1);
    XCTAssertEqual(gameboy.cpu.flag_N, 0);
    XCTAssertEqual(gameboy.cpu.flag_H, 0);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_INC_B_carry {
    Gameboy gameboy;
    std::array<Byte, 1> program = { 0x04 };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_B = 0x07;
    gameboy.run(2);
    XCTAssertEqual(gameboy.cpu.register_B, 0x08);
    XCTAssertEqual(gameboy.cpu.flag_Z, 0);
    XCTAssertEqual(gameboy.cpu.flag_N, 0);
    XCTAssertEqual(gameboy.cpu.flag_H, 1);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_INC_B_overflow {
    Gameboy gameboy;
    std::array<Byte, 1> program = { 0x04 };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_B = 0xFF;
    gameboy.run(2);
    XCTAssertEqual(gameboy.cpu.register_B, 0x00);
    XCTAssertEqual(gameboy.cpu.flag_Z, 1);
    XCTAssertEqual(gameboy.cpu.flag_N, 0);
    XCTAssertEqual(gameboy.cpu.flag_H, 0);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_INC_C_Z0 {
    Gameboy gameboy;
    std::array<Byte, 1> program = { 0x0C };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_C = 0x00;
    gameboy.run(2);
    XCTAssertEqual(gameboy.cpu.register_C, 0x01);
    XCTAssertEqual(gameboy.cpu.flag_Z, 0);
    XCTAssertEqual(gameboy.cpu.flag_N, 0);
    XCTAssertEqual(gameboy.cpu.flag_H, 0);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_INC_C_Z1 {
    Gameboy gameboy;
    std::array<Byte, 1> program = { 0x0C };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_C = 0xFF;
    gameboy.run(2);
    XCTAssertEqual(gameboy.cpu.register_C, 0x00);
    XCTAssertEqual(gameboy.cpu.flag_Z, 1);
    XCTAssertEqual(gameboy.cpu.flag_N, 0);
    XCTAssertEqual(gameboy.cpu.flag_H, 0);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_INC_C_carry {
    Gameboy gameboy;
    std::array<Byte, 1> program = { 0x0C };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_C = 0x07;
    gameboy.run(2);
    XCTAssertEqual(gameboy.cpu.register_C, 0x08);
    XCTAssertEqual(gameboy.cpu.flag_Z, 0);
    XCTAssertEqual(gameboy.cpu.flag_N, 0);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_INC_C_overflow {
    Gameboy gameboy;
    std::array<Byte, 1> program = { 0x0C };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_C = 0xFF;
    gameboy.run(2);
    XCTAssertEqual(gameboy.cpu.register_C, 0x00);
    XCTAssertEqual(gameboy.cpu.flag_Z, 1);
    XCTAssertEqual(gameboy.cpu.flag_N, 0);
    XCTAssertEqual(gameboy.cpu.flag_H, 0);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_INC_H_Z0 {
    Gameboy gameboy;
    std::array<Byte, 1> program = { 0x24 };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_H = 0x00;
    gameboy.run(2);
    XCTAssertEqual(gameboy.cpu.register_H, 0x01);
    XCTAssertEqual(gameboy.cpu.flag_Z, 0);
    XCTAssertEqual(gameboy.cpu.flag_N, 0);
    XCTAssertEqual(gameboy.cpu.flag_H, 0);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_INC_H_Z1 {
    Gameboy gameboy;
    std::array<Byte, 1> program = { 0x24 };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_H = 0xFF;
    gameboy.run(2);
    XCTAssertEqual(gameboy.cpu.register_H, 0x00);
    XCTAssertEqual(gameboy.cpu.flag_Z, 1);
    XCTAssertEqual(gameboy.cpu.flag_N, 0);
    XCTAssertEqual(gameboy.cpu.flag_H, 0);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_DEC_A_Z0 {
    Gameboy gameboy;
    std::array<Byte, 1> program = { 0x3D };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_A = 0x08;
    gameboy.run(2);
    XCTAssertEqual(gameboy.cpu.register_A, 0x07);
    XCTAssertEqual(gameboy.cpu.flag_Z, 0);
    XCTAssertEqual(gameboy.cpu.flag_N, 1);
    XCTAssertEqual(gameboy.cpu.flag_H, 0);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_DEC_A_Z1 {
    Gameboy gameboy;
    std::array<Byte, 1> program = { 0x3D };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_A = 0x01;
    gameboy.run(2);
    XCTAssertEqual(gameboy.cpu.register_A, 0x00);
    XCTAssertEqual(gameboy.cpu.flag_Z, 1);
    XCTAssertEqual(gameboy.cpu.flag_N, 1);
    XCTAssertEqual(gameboy.cpu.flag_H, 0);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_DEC_A_carry {
    Gameboy gameboy;
    std::array<Byte, 1> program = { 0x3D };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_A = 0xAB;
    gameboy.run(2);
    XCTAssertEqual(gameboy.cpu.register_A, 0xAA);
    XCTAssertEqual(gameboy.cpu.flag_Z, 0);
    XCTAssertEqual(gameboy.cpu.flag_N, 1);
    XCTAssertEqual(gameboy.cpu.flag_H, 1);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_DEC_A_underflow {
    Gameboy gameboy;
    std::array<Byte, 1> program = { 0x3D };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_A = 0x00;
    gameboy.run(2);
    XCTAssertEqual(gameboy.cpu.register_A, 0xFF);
    XCTAssertEqual(gameboy.cpu.flag_Z, 0);
    XCTAssertEqual(gameboy.cpu.flag_N, 1);
    XCTAssertEqual(gameboy.cpu.flag_H, 1);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_DEC_B_Z0 {
    Gameboy gameboy;
    std::array<Byte, 1> program = { 0x05 };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_B = 0x08;
    gameboy.run(2);
    XCTAssertEqual(gameboy.cpu.register_B, 0x07);
    XCTAssertEqual(gameboy.cpu.flag_Z, 0);
    XCTAssertEqual(gameboy.cpu.flag_N, 1);
    XCTAssertEqual(gameboy.cpu.flag_H, 0);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_DEC_B_Z1 {
    Gameboy gameboy;
    std::array<Byte, 1> program = { 0x05 };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_B = 0x01;
    gameboy.run(2);
    XCTAssertEqual(gameboy.cpu.register_B, 0x00);
    XCTAssertEqual(gameboy.cpu.flag_Z, 1);
    XCTAssertEqual(gameboy.cpu.flag_N, 1);
    XCTAssertEqual(gameboy.cpu.flag_H, 0);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_DEC_B_carry {
    Gameboy gameboy;
    std::array<Byte, 1> program = { 0x05 };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_B = 0xAB;
    gameboy.run(2);
    XCTAssertEqual(gameboy.cpu.register_B, 0xAA);
    XCTAssertEqual(gameboy.cpu.flag_Z, 0);
    XCTAssertEqual(gameboy.cpu.flag_N, 1);
    XCTAssertEqual(gameboy.cpu.flag_H, 1);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_DEC_B_underflow {
    Gameboy gameboy;
    std::array<Byte, 1> program = { 0x05 };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_B = 0x00;
    gameboy.run(2);
    XCTAssertEqual(gameboy.cpu.register_B, 0xFF);
    XCTAssertEqual(gameboy.cpu.flag_Z, 0);
    XCTAssertEqual(gameboy.cpu.flag_N, 1);
    XCTAssertEqual(gameboy.cpu.flag_H, 1);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_DEC_C_Z0 {
    Gameboy gameboy;
    std::array<Byte, 1> program = { 0x0D };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_C = 0x08;
    gameboy.run(2);
    XCTAssertEqual(gameboy.cpu.register_C, 0x07);
    XCTAssertEqual(gameboy.cpu.flag_Z, 0);
    XCTAssertEqual(gameboy.cpu.flag_N, 1);
    XCTAssertEqual(gameboy.cpu.flag_H, 0);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_DEC_C_Z1 {
    Gameboy gameboy;
    std::array<Byte, 1> program = { 0x0D };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_C = 0x01;
    gameboy.run(2);
    XCTAssertEqual(gameboy.cpu.register_C, 0x00);
    XCTAssertEqual(gameboy.cpu.flag_Z, 1);
    XCTAssertEqual(gameboy.cpu.flag_N, 1);
    XCTAssertEqual(gameboy.cpu.flag_H, 0);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_DEC_C_carry {
    Gameboy gameboy;
    std::array<Byte, 1> program = { 0x0D };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_C = 0xAB;
    gameboy.run(2);
    XCTAssertEqual(gameboy.cpu.register_C, 0xAA);
    XCTAssertEqual(gameboy.cpu.flag_Z, 0);
    XCTAssertEqual(gameboy.cpu.flag_N, 1);
    XCTAssertEqual(gameboy.cpu.flag_H, 1);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_DEC_C_underflow {
    Gameboy gameboy;
    std::array<Byte, 1> program = { 0x0D };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_C = 0x00;
    gameboy.run(2);
    XCTAssertEqual(gameboy.cpu.register_C, 0xFF);
    XCTAssertEqual(gameboy.cpu.flag_Z, 0);
    XCTAssertEqual(gameboy.cpu.flag_N, 1);
    XCTAssertEqual(gameboy.cpu.flag_H, 1);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_DEC_D_Z0 {
    Gameboy gameboy;
    std::array<Byte, 1> program = { 0x15 };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_D = 0xFF;
    gameboy.run(2);
    XCTAssertEqual(gameboy.cpu.register_D, 0xFE);
    XCTAssertEqual(gameboy.cpu.flag_Z, 0);
    XCTAssertEqual(gameboy.cpu.flag_N, 1);
    XCTAssertEqual(gameboy.cpu.flag_H, 1);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_DEC_D_Z1 {
    Gameboy gameboy;
    std::array<Byte, 1> program = { 0x15 };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_D = 0x01;
    gameboy.run(2);
    XCTAssertEqual(gameboy.cpu.register_D, 0x00);
    XCTAssertEqual(gameboy.cpu.flag_Z, 1);
    XCTAssertEqual(gameboy.cpu.flag_N, 1);
    XCTAssertEqual(gameboy.cpu.flag_H, 0);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_DEC_E_Z0 {
    Gameboy gameboy;
    std::array<Byte, 1> program = { 0x1D };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_E = 0x08;
    gameboy.run(2);
    XCTAssertEqual(gameboy.cpu.register_E, 0x07);
    XCTAssertEqual(gameboy.cpu.flag_Z, 0);
    XCTAssertEqual(gameboy.cpu.flag_N, 1);
    XCTAssertEqual(gameboy.cpu.flag_H, 0);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_DEC_E_Z1 {
    Gameboy gameboy;
    std::array<Byte, 1> program = { 0x1D };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_E = 0x01;
    gameboy.run(2);
    XCTAssertEqual(gameboy.cpu.register_E, 0x00);
    XCTAssertEqual(gameboy.cpu.flag_Z, 1);
    XCTAssertEqual(gameboy.cpu.flag_N, 1);
    XCTAssertEqual(gameboy.cpu.flag_H, 0);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_SUB_B_Z0 {
    Gameboy gameboy;
    std::array<Byte, 1> program = { 0x90 };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_A = 0xFF;
    gameboy.cpu.register_B = 0x06;
    gameboy.run(2);
    XCTAssertEqual(gameboy.cpu.register_A, 0xF9);
    XCTAssertEqual(gameboy.cpu.flag_Z, 0);
    XCTAssertEqual(gameboy.cpu.flag_N, 1);
    XCTAssertEqual(gameboy.cpu.flag_H, 1);
    XCTAssertEqual(gameboy.cpu.flag_C, 1);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_SUB_B_Z1 {
    Gameboy gameboy;
    std::array<Byte, 1> program = { 0x90 };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_A = 0xAB;
    gameboy.cpu.register_B = 0xAB;
    gameboy.run(2);
    XCTAssertEqual(gameboy.cpu.register_A, 0x00);
    XCTAssertEqual(gameboy.cpu.flag_Z, 1);
    XCTAssertEqual(gameboy.cpu.flag_N, 1);
    XCTAssertEqual(gameboy.cpu.flag_H, 0);
    XCTAssertEqual(gameboy.cpu.flag_C, 0);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_INC_DE {
    Gameboy gameboy;
    std::array<Byte, 1> program = { 0x13 };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_D = 0xC0;
    gameboy.cpu.register_E = 0xFF;
    gameboy.run(3);
    XCTAssertEqual(gameboy.cpu.register_D, 0xC1);
    XCTAssertEqual(gameboy.cpu.register_E, 0x00);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_INC_DE_overflow {
    Gameboy gameboy;
    std::array<Byte, 1> program = { 0x13 };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_D = 0xFF;
    gameboy.cpu.register_E = 0xFF;
    gameboy.run(3);
    XCTAssertEqual(gameboy.cpu.register_D, 0x00);
    XCTAssertEqual(gameboy.cpu.register_E, 0x00);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_INC_HL {
    Gameboy gameboy;
    std::array<Byte, 1> program = { 0x23 };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_H = 0xC0;
    gameboy.cpu.register_L = 0xFF;
    gameboy.run(3);
    XCTAssertEqual(gameboy.cpu.register_H, 0xC1);
    XCTAssertEqual(gameboy.cpu.register_L, 0x00);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_INC_HL_overflow {
    Gameboy gameboy;
    std::array<Byte, 1> program = { 0x23 };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_H = 0xFF;
    gameboy.cpu.register_L = 0xFF;
    gameboy.run(3);
    XCTAssertEqual(gameboy.cpu.register_H, 0x00);
    XCTAssertEqual(gameboy.cpu.register_L, 0x00);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_CP_n__Z0 {
    Gameboy gameboy;
    std::array<Byte, 2> program = { 0xFE, 0x08 };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_A = 0x10;
    gameboy.run(3);
    XCTAssertEqual(gameboy.cpu.flag_Z, 0);
    XCTAssertEqual(gameboy.cpu.flag_N, 1);
    XCTAssertEqual(gameboy.cpu.flag_H, 1);
    XCTAssertEqual(gameboy.cpu.flag_C, 0);
    XCTAssertEqual(gameboy.cpu.program_counter, 3);
}

-(void)test_CP_n__Z1 {
    Gameboy gameboy;
    std::array<Byte, 2> program = { 0xFE, 0xAB };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_A = 0xAB;
    gameboy.run(3);
    XCTAssertEqual(gameboy.cpu.flag_Z, 1);
    XCTAssertEqual(gameboy.cpu.flag_N, 1);
    XCTAssertEqual(gameboy.cpu.flag_H, 0);
    XCTAssertEqual(gameboy.cpu.flag_C, 0);
    XCTAssertEqual(gameboy.cpu.program_counter, 3);
}

-(void)test_CP_n__underflow {
    Gameboy gameboy;
    std::array<Byte, 2> program = { 0xFE, 0x01 };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_A = 0x00;
    gameboy.run(3);
    XCTAssertEqual(gameboy.cpu.flag_Z, 0);
    XCTAssertEqual(gameboy.cpu.flag_N, 1);
    XCTAssertEqual(gameboy.cpu.flag_H, 1);
    XCTAssertEqual(gameboy.cpu.flag_C, 1);
    XCTAssertEqual(gameboy.cpu.program_counter, 3);
}

-(void)test_LD_SP_HL {
    Gameboy gameboy;
    std::array<Byte, 1> program = { 0xF9 };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_H = 0xFF;
    gameboy.cpu.register_L = 0x11;
    gameboy.run(3);
    XCTAssertEqual(gameboy.cpu.stack_pointer, 0xFF11);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_LD_SP_nn {
    Gameboy gameboy;
    std::array<Byte, 3> program = { 0x31, 0x22, 0xC1 };
    gameboy.memory.load_rom(program);
    gameboy.run(4);
    XCTAssertEqual(gameboy.cpu.stack_pointer, 0xC122);
    XCTAssertEqual(gameboy.cpu.program_counter, 4);
}

-(void)test_LD_DE_nn {
    Gameboy gameboy;
    std::array<Byte, 3> program = { 0x11, 0xBB, 0xAA };
    gameboy.memory.load_rom(program);
    gameboy.run(4);
    XCTAssertEqual(gameboy.cpu.register_D, 0xAA);
    XCTAssertEqual(gameboy.cpu.register_E, 0xBB);
    XCTAssertEqual(gameboy.cpu.program_counter, 4);
}

-(void)test_LD_HL_nn {
    Gameboy gameboy;
    std::array<Byte, 3> program = { 0x21, 0xBB, 0xAA };
    gameboy.memory.load_rom(program);
    gameboy.run(4);
    XCTAssertEqual(gameboy.cpu.register_H, 0xAA);
    XCTAssertEqual(gameboy.cpu.register_L, 0xBB);
    XCTAssertEqual(gameboy.cpu.program_counter, 4);
}

-(void)test_LD_iHL_A {
    Gameboy gameboy;
    std::array<Byte, 1> program = { 0x77 };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_H = 0xC0;
    gameboy.cpu.register_L = 0x00;
    gameboy.cpu.register_A = 0xAB;
    gameboy.run(3);
    XCTAssertEqual(gameboy.memory.read(0xC000), 0xAB);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_LD_inn_SP {
    Gameboy gameboy;
    std::array<Byte, 3> program { 0x08, 0x11, 0xFF };
    gameboy.memory.load_rom(program);
    gameboy.cpu.stack_pointer = 0xAABB;
    gameboy.run(6);
    XCTAssertEqual(gameboy.memory.read(0xFF11), 0xBB);
    XCTAssertEqual(gameboy.memory.read(0xFF12), 0xAA);
    XCTAssertEqual(gameboy.cpu.program_counter, 4);
}

-(void)test_LD_iHL_n {
    Gameboy gameboy;
    std::array<Byte, 2> program { 0x36, 0xAB };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_H = 0xC0;
    gameboy.cpu.register_L = 0x00;
    gameboy.run(4);
    XCTAssertEqual(gameboy.memory.read(0xC000), 0xAB);
    XCTAssertEqual(gameboy.cpu.program_counter, 3);
}

-(void)test_LD_iHLI_A {
    Gameboy gameboy;
    std::array<Byte, 1> program { 0x22 };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_A = 0xAB;
    gameboy.cpu.register_H = 0xC0;
    gameboy.cpu.register_L = 0x00;
    gameboy.run(3);
    XCTAssertEqual(gameboy.memory.read(0xC000), 0xAB);
    XCTAssertEqual(gameboy.cpu.register_H, 0xC0);
    XCTAssertEqual(gameboy.cpu.register_L, 0x01);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_LD_iHLD_A {
    Gameboy gameboy;
    std::array<Byte, 1> program { 0x32 };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_A = 0xAB;
    gameboy.cpu.register_H = 0xC0;
    gameboy.cpu.register_L = 0x01;
    gameboy.run(3);
    XCTAssertEqual(gameboy.memory.read(0xC001), 0xAB);
    XCTAssertEqual(gameboy.cpu.register_H, 0xC0);
    XCTAssertEqual(gameboy.cpu.register_L, 0x00);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_LD_iC_A {
    Gameboy gameboy;
    std::array<Byte, 1> program { 0xE2 };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_A = 0xAB;
    gameboy.cpu.register_C = 0xCD;
    gameboy.run(3);
    XCTAssertEqual(gameboy.memory.read(0xFFCD), 0xAB);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_LDH_in_A {
    Gameboy gameboy;
    std::array<Byte, 2> program = { 0xE0, 0xAA };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_A = 0xBB;
    gameboy.run(4);
    XCTAssertEqual(gameboy.memory.read(0xFFAA), 0xBB);
    XCTAssertEqual(gameboy.cpu.program_counter, 3);
}

-(void)test_LD_inn_A {
    Gameboy gameboy;
    std::array<Byte, 3> program = { 0xEA, 0x01, 0xC0 };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_A = 0xAB;
    gameboy.run(5);
    XCTAssertEqual(gameboy.memory.read(0xC001), 0xAB);
    XCTAssertEqual(gameboy.cpu.program_counter, 4);
}

-(void)test_PUSH_BC {
    Gameboy gameboy;
    std::array<Byte, 3> program = { 0xC5 };
    gameboy.memory.load_rom(program);
    gameboy.cpu.stack_pointer = 0xE000;
    gameboy.cpu.register_B = 0xBA;
    gameboy.cpu.register_C = 0xAB;
    gameboy.run(5);
    XCTAssertEqual(gameboy.memory.read(0xE000 - 1), 0xBA);
    XCTAssertEqual(gameboy.memory.read(0xE000 - 2), 0xAB);
    XCTAssertEqual(gameboy.cpu.stack_pointer, 0xE000 - 2);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_JR_n_positive {
    Gameboy gameboy;
    std::array<Byte, 2> program { 0x18, 0x02 };
    gameboy.memory.load_rom(program);
    gameboy.run(4);
    XCTAssertEqual(gameboy.cpu.program_counter, 5);
}

-(void)test_JR_n_negative {
    Gameboy gameboy;
    std::array<Byte, 2> program { 0x18, 0xFF };
    gameboy.memory.load_rom(program);
    gameboy.run(4);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_JR_n_zero {
    Gameboy gameboy;
    std::array<Byte, 2> program { 0x18, 0x00 };
    gameboy.memory.load_rom(program);
    gameboy.run(4);
    XCTAssertEqual(gameboy.cpu.program_counter, 3);
}

-(void)test_JR_Z_n__Z0 {
    Gameboy gameboy;
    std::array<Byte, 2> program { 0x28, 0xFF };
    gameboy.memory.load_rom(program);
    gameboy.cpu.flag_Z = 0;
    gameboy.run(3);
    XCTAssertEqual(gameboy.cpu.program_counter, 3);
}

-(void)test_JR_Z_n__Z1_negative {
    Gameboy gameboy;
    std::array<Byte, 2> program { 0x28, 0xFF };
    gameboy.memory.load_rom(program);
    gameboy.cpu.flag_Z = 1;
    gameboy.run(4);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_JR_Z_n__Z1_positive {
    Gameboy gameboy;
    std::array<Byte, 2> program { 0x28, 0x01 };
    gameboy.memory.load_rom(program);
    gameboy.cpu.flag_Z = 1;
    gameboy.run(4);
    XCTAssertEqual(gameboy.cpu.program_counter, 4);
}

-(void)test_JR_Z_n__Z1_zero {
    Gameboy gameboy;
    std::array<Byte, 2> program { 0x28, 0x00 };
    gameboy.memory.load_rom(program);
    gameboy.cpu.flag_Z = 1;
    gameboy.run(4);
    XCTAssertEqual(gameboy.cpu.program_counter, 3);
}

-(void)test_JR_NZ_n__Z0_negative {
    Gameboy gameboy;
    std::array<Byte, 2> program { 0x20, 0xFF };
    gameboy.memory.load_rom(program);
    gameboy.cpu.flag_Z = 0;
    gameboy.run(4);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_JR_NZ_n__Z0_positive {
    Gameboy gameboy;
    std::array<Byte, 2> program { 0x20, 0x01 };
    gameboy.memory.load_rom(program);
    gameboy.cpu.flag_Z = 0;
    gameboy.run(4);
    XCTAssertEqual(gameboy.cpu.program_counter, 4);
}

-(void)test_JR_NZ_n__Z0_zero {
    Gameboy gameboy;
    std::array<Byte, 2> program { 0x20, 0x00 };
    gameboy.memory.load_rom(program);
    gameboy.cpu.flag_Z = 0;
    gameboy.run(4);
    XCTAssertEqual(gameboy.cpu.program_counter, 3);
}

-(void)test_JR_NZ_n__Z1 {
    Gameboy gameboy;
    std::array<Byte, 2> program { 0x20, 0xAA };
    gameboy.memory.load_rom(program);
    gameboy.cpu.flag_Z = 1;
    gameboy.run(3);
    XCTAssertEqual(gameboy.cpu.program_counter, 3);
}

-(void)test_RLA_C0 {
    Gameboy gameboy;
    std::array<Byte, 2> program { 0x17 };
    gameboy.memory.load_rom(program);
    gameboy.cpu.flag_Z = 1;
    gameboy.cpu.flag_N = 1;
    gameboy.cpu.flag_H = 1;
    gameboy.cpu.flag_C = 1;
    gameboy.cpu.register_A = 1 << 6;
    gameboy.run(2);
    XCTAssertEqual(gameboy.cpu.register_A, (1 << 7) | 1);
    XCTAssertEqual(gameboy.cpu.flag_Z, 1);
    XCTAssertEqual(gameboy.cpu.flag_N, 0);
    XCTAssertEqual(gameboy.cpu.flag_H, 0);
    XCTAssertEqual(gameboy.cpu.flag_C, 0);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_RLA_C1 {
    Gameboy gameboy;
    std::array<Byte, 2> program { 0x17 };
    gameboy.memory.load_rom(program);
    gameboy.cpu.flag_Z = 1;
    gameboy.cpu.flag_N = 1;
    gameboy.cpu.flag_H = 1;
    gameboy.cpu.flag_C = 0;
    gameboy.cpu.register_A = 1 << 7;
    gameboy.run(2);
    XCTAssertEqual(gameboy.cpu.register_A, 0);
    XCTAssertEqual(gameboy.cpu.flag_Z, 1);
    XCTAssertEqual(gameboy.cpu.flag_N, 0);
    XCTAssertEqual(gameboy.cpu.flag_H, 0);
    XCTAssertEqual(gameboy.cpu.flag_C, 1);
    XCTAssertEqual(gameboy.cpu.program_counter, 2);
}

-(void)test_RL_C__Z0_C0 {
    Gameboy gameboy;
    std::array<Byte, 2> program { 0xCB, 0x11 };
    gameboy.memory.load_rom(program);
    gameboy.cpu.flag_Z = 1;
    gameboy.cpu.flag_N = 1;
    gameboy.cpu.flag_H = 1;
    gameboy.cpu.flag_C = 1;
    gameboy.cpu.register_C = 1 << 6;
    gameboy.run(3);
    XCTAssertEqual(gameboy.cpu.register_C, (1 << 7) | 1);
    XCTAssertEqual(gameboy.cpu.flag_Z, 0);
    XCTAssertEqual(gameboy.cpu.flag_N, 0);
    XCTAssertEqual(gameboy.cpu.flag_H, 0);
    XCTAssertEqual(gameboy.cpu.flag_C, 0);
    XCTAssertEqual(gameboy.cpu.program_counter, 3);
}

-(void)test_RL_C__Z1_C1 {
    Gameboy gameboy;
    std::array<Byte, 2> program { 0xCB, 0x11 };
    gameboy.memory.load_rom(program);
    gameboy.cpu.flag_Z = 0;
    gameboy.cpu.flag_N = 1;
    gameboy.cpu.flag_H = 1;
    gameboy.cpu.flag_C = 0;
    gameboy.cpu.register_C = 1 << 7;
    gameboy.run(3);
    XCTAssertEqual(gameboy.cpu.register_C, 0);
    XCTAssertEqual(gameboy.cpu.flag_Z, 1);
    XCTAssertEqual(gameboy.cpu.flag_N, 0);
    XCTAssertEqual(gameboy.cpu.flag_H, 0);
    XCTAssertEqual(gameboy.cpu.flag_C, 1);
    XCTAssertEqual(gameboy.cpu.program_counter, 3);
}

-(void)test_BIT_7_H__Z0 {
    Gameboy gameboy;
    std::array<Byte, 2> program { 0xCB, 0x7C };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_H = 0x80;
    gameboy.run(3);
    XCTAssertEqual(gameboy.cpu.flag_Z, 0);
    XCTAssertEqual(gameboy.cpu.flag_N, 0);
    XCTAssertEqual(gameboy.cpu.flag_H, 1);
    XCTAssertEqual(gameboy.cpu.flag_C, 0);
    XCTAssertEqual(gameboy.cpu.program_counter, 3);
}

-(void)test_BIT_7_H__Z1 {
    Gameboy gameboy;
    std::array<Byte, 2> program { 0xCB, 0x7C };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_H = 0x7F;
    gameboy.run(3);
    XCTAssertEqual(gameboy.cpu.flag_Z, 1);
    XCTAssertEqual(gameboy.cpu.flag_N, 0);
    XCTAssertEqual(gameboy.cpu.flag_H, 1);
    XCTAssertEqual(gameboy.cpu.flag_C, 0);
    XCTAssertEqual(gameboy.cpu.program_counter, 3);
}

-(void)test_CALL_nn {
    Gameboy gameboy;
    std::array<Byte, 6> program { 0x00, 0x00, 0x00, 0xCD, 0x11, 0x40 }; // extra padding to start PC with offset
    gameboy.memory.load_rom(program);
    gameboy.cpu.program_counter = 0x03;
    gameboy.cpu.stack_pointer = 0xE000;
    gameboy.run(7);
    XCTAssertEqual(gameboy.cpu.program_counter, 0x4012);
    XCTAssertEqual(gameboy.memory.read(0xE000 - 1), 0x00);
    XCTAssertEqual(gameboy.memory.read(0xE000 - 2), 0x06);
    XCTAssertEqual(gameboy.cpu.stack_pointer, 0xE000 - 2); // return address takes 2 bytes
}

@end
