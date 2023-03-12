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
    XCTAssertEqual(gameboy.cpu.cycle, 1);
}

-(void)test_LD_A_n {
    Gameboy gameboy;
    std::array<Byte, 2> program = { 0x3E, 0xAB };
    gameboy.memory.load_rom(program);
    gameboy.run(2);
    XCTAssertEqual(gameboy.cpu.register_A, 0xAB);
    XCTAssertEqual(gameboy.cpu.cycle, 2);
}

-(void)test_LD_C_n {
    Gameboy gameboy;
    std::array<Byte, 2> program = { 0x0E, 0xAB };
    gameboy.memory.load_rom(program);
    gameboy.run(2);
    XCTAssertEqual(gameboy.cpu.register_C, 0xAB);
    XCTAssertEqual(gameboy.cpu.cycle, 2);
}

-(void)test_LD_SP_HL {
    Gameboy gameboy;
    std::array<Byte, 1> program = { 0xF9 };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_H = 0xFF;
    gameboy.cpu.register_L = 0x11;
    gameboy.run(2);
    XCTAssertEqual(gameboy.cpu.stack_pointer, 0xFF11);
    XCTAssertEqual(gameboy.cpu.cycle, 2);
}

-(void)test_LD_SP_nn {
    Gameboy gameboy;
    std::array<Byte, 3> program = { 0x31, 0x22, 0xC1 };
    gameboy.memory.load_rom(program);
    gameboy.run(3);
    XCTAssertEqual(gameboy.cpu.stack_pointer, 0xC122);
    XCTAssertEqual(gameboy.cpu.cycle, 3);
}

-(void)test_LD_HL_nn {
    Gameboy gameboy;
    std::array<Byte, 3> program = { 0x21, 0xBB, 0xAA };
    gameboy.memory.load_rom(program);
    gameboy.run(3);
    XCTAssertEqual(gameboy.cpu.register_HL(), 0xAABB);
    XCTAssertEqual(gameboy.cpu.cycle, 3);
}

-(void)test_LD_nn_SP {
    Gameboy gameboy;
    std::array<Byte, 3> program { 0x08, 0x11, 0xFF };
    gameboy.memory.load_rom(program);
    gameboy.cpu.stack_pointer = 0xAABB;
    gameboy.run(5);
    XCTAssertEqual(gameboy.memory.read(0xFF11), 0xBB);
    XCTAssertEqual(gameboy.memory.read(0xFF12), 0xAA);
    XCTAssertEqual(gameboy.cpu.cycle, 5);
}

-(void)test_XOR_A {
    Gameboy gameboy;
    std::array<Byte, 1> program { 0xAF };
    gameboy.memory.load_rom(program);
    gameboy.run(1);
    XCTAssertEqual(gameboy.cpu.register_A, 0x00);
    XCTAssertEqual(gameboy.cpu.flag_Z, 1);
    XCTAssertEqual(gameboy.cpu.flag_N, 0);
    XCTAssertEqual(gameboy.cpu.flag_H, 0);
    XCTAssertEqual(gameboy.cpu.flag_C, 0);
    XCTAssertEqual(gameboy.cpu.cycle, 1);
}

-(void)test_LD_HL_n {
    Gameboy gameboy;
    std::array<Byte, 2> program { 0x36, 0xAB };
    gameboy.memory.load_rom(program);
    gameboy.cpu.set_register_HL(0xC000);
    gameboy.run(3);
    XCTAssertEqual(gameboy.memory.read(0xC000), 0xAB);
    XCTAssertEqual(gameboy.cpu.cycle, 3);
}

-(void)test_LD_HLd_A {
    Gameboy gameboy;
    std::array<Byte, 1> program { 0x32 };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_A = 0xAB;
    gameboy.cpu.set_register_HL(0xC001);
    gameboy.run(2);
    XCTAssertEqual(gameboy.memory.read(0xC001), 0xAB);
    XCTAssertEqual(gameboy.cpu.register_HL(), 0xC000);
    XCTAssertEqual(gameboy.cpu.cycle, 2);
}

-(void)test_LDH_C_A {
    Gameboy gameboy;
    std::array<Byte, 1> program { 0xE2 };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_A = 0xAB;
    gameboy.cpu.register_C = 0xCD;
    gameboy.run(2);
    XCTAssertEqual(gameboy.memory.read(0xFFCD), 0xAB);
    XCTAssertEqual(gameboy.cpu.cycle, 2);
}

-(void)test_JP_NZ_n__Z0_negative {
    Gameboy gameboy;
    std::array<Byte, 2> program { 0x20, 0xFF };
    gameboy.memory.load_rom(program);
    gameboy.cpu.flag_Z = 0;
    gameboy.run(3);
    XCTAssertEqual(gameboy.cpu.program_counter, 0x01);
    XCTAssertEqual(gameboy.cpu.cycle, 3);
}

-(void)test_JP_NZ_n__Z0_positive {
    Gameboy gameboy;
    std::array<Byte, 2> program { 0x20, 0x01 };
    gameboy.memory.load_rom(program);
    gameboy.cpu.flag_Z = 0;
    gameboy.run(3);
    XCTAssertEqual(gameboy.cpu.program_counter, 0x03);
    XCTAssertEqual(gameboy.cpu.cycle, 3);
}

-(void)test_JP_NZ_n__Z0_zero {
    Gameboy gameboy;
    std::array<Byte, 2> program { 0x20, 0x00 };
    gameboy.memory.load_rom(program);
    gameboy.cpu.flag_Z = 0;
    gameboy.run(3);
    XCTAssertEqual(gameboy.cpu.program_counter, 0x02);
    XCTAssertEqual(gameboy.cpu.cycle, 3);
}

-(void)test_JP_NZ_n__Z1 {
    Gameboy gameboy;
    std::array<Byte, 2> program { 0x20, 0xAA };
    gameboy.memory.load_rom(program);
    gameboy.cpu.flag_Z = 1;
    gameboy.run(2);
    XCTAssertEqual(gameboy.cpu.program_counter, 0x02);
    XCTAssertEqual(gameboy.cpu.cycle, 2);
}

-(void)test_BIT_7_H__Z0 {
    Gameboy gameboy;
    std::array<Byte, 2> program { 0xCB, 0x7C };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_H = 0x80;
    gameboy.run(2);
    XCTAssertEqual(gameboy.cpu.flag_Z, 0);
    XCTAssertEqual(gameboy.cpu.flag_N, 0);
    XCTAssertEqual(gameboy.cpu.flag_H, 1);
    XCTAssertEqual(gameboy.cpu.flag_C, 0);
    XCTAssertEqual(gameboy.cpu.cycle, 2);
}

-(void)test_BIT_7_H__Z1 {
    Gameboy gameboy;
    std::array<Byte, 2> program { 0xCB, 0x7C };
    gameboy.memory.load_rom(program);
    gameboy.cpu.register_H = 0x7F;
    gameboy.run(2);
    XCTAssertEqual(gameboy.cpu.flag_Z, 1);
    XCTAssertEqual(gameboy.cpu.flag_N, 0);
    XCTAssertEqual(gameboy.cpu.flag_H, 1);
    XCTAssertEqual(gameboy.cpu.flag_C, 0);
    XCTAssertEqual(gameboy.cpu.cycle, 2);
}

@end
