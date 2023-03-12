//
//  OpcodeTests.m
//  gameboy-cpuTests
//
//  Created by Gabriel Lumbi on 2023-03-10.
//

#import <XCTest/XCTest.h>

#import "Gameboy.hpp"
#import <memory>

@interface OpcodeTests : XCTestCase

@end

@implementation OpcodeTests

- (void)test_NOP {
    Gameboy gameboy;
    std::array<Byte, 1> program = { 0x00 };
    gameboy.memory.load_rom(program);
    gameboy.run(1);
    XCTAssertEqual(gameboy.cpu.cycle, 1);
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

-(void)test_LD_SP_NN {
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

-(void)test_LD_HL_NN {
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

@end
