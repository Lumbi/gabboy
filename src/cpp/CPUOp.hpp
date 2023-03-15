//
//  CPUOp.hpp
//  gabboy
//
//  Created by Gabriel Lumbi on 2023-03-14.
//

#ifndef CPUOp_hpp
#define CPUOp_hpp

#include "Data.hpp"

class CPU;
class Memory;

namespace CPUOp {

struct Base {
    virtual bool execute(CPU& cpu, Memory&) = 0;
    virtual ~Base() {};
    int cycle = -1;
};

struct Nullary: public Base {};
#define CPU_OP_NULLARY(Name) \
struct Name: public Nullary { bool execute(CPU& cpu, Memory&) override; };

struct Unary8: public Base { Unary8(Byte& r): r(r) {}; Byte& r; };
#define CPU_OP_UNARY_8(Name) \
struct Name: public Unary8 { using Unary8::Unary8; bool execute(CPU& cpu, Memory&) override; };

struct Unary16: public Base { Unary16(Byte& r1, Byte& r2): r1(r1), r2(r2) {}; Byte& r1; Byte& r2; };
#define CPU_OP_UNARY_16(Name) \
struct Name: public Unary16 { using Unary16::Unary16; bool execute(CPU& cpu, Memory& memory) override; };

struct Binary8: public Base { Binary8(Byte& r1, Byte& r2): r1(r1), r2(r2) {}; Byte& r1; Byte& r2; };
#define CPU_OP_BINARY_8(Name) \
struct Name: public Binary8 { using Binary8::Binary8; bool execute(CPU& cpu, Memory& memory) override; };

CPU_OP_NULLARY(NOP);

// 8-bit arithmetic instructions

CPU_OP_UNARY_8(INC_r);
CPU_OP_UNARY_8(DEC_r);
CPU_OP_UNARY_8(XOR_r);
CPU_OP_UNARY_8(SUB_r);
CPU_OP_NULLARY(CP_n);

// 8-bit load instructions

CPU_OP_UNARY_8(LD_r_n);
CPU_OP_UNARY_8(LDH_r_in);
CPU_OP_BINARY_8(LD_r_r);

// 16-bit arithmetic instructions

CPU_OP_UNARY_16(INC_rr);

// 16-bit load instructions

CPU_OP_NULLARY(LD_SP_HL);
CPU_OP_NULLARY(LD_SP_nn);
CPU_OP_UNARY_16(LD_rr_nn);

}

#endif /* Operation_hpp */
