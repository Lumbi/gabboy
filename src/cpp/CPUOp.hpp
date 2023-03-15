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

protected:
    int cycle = -1;
};

// Instruction templates

struct Nullary: public Base {};
#define CPU_OP_NULLARY(Name) \
struct Name: public Nullary { bool execute(CPU& cpu, Memory& memory) override; };

struct Unary: public Base { Unary(Byte& r): r(r) {}; Byte& r; };
#define CPU_OP_UNARY(Name) \
struct Name: public Unary { using Unary::Unary; bool execute(CPU& cpu, Memory& memory) override; };

struct Binary: public Base { Binary(Byte& r1, Byte& r2): r1(r1), r2(r2) {}; Byte& r1; Byte& r2; };
#define CPU_OP_BINARY(Name) \
struct Name: public Binary { using Binary::Binary; bool execute(CPU& cpu, Memory& memory) override; };

struct Ternary: public Base { Ternary(Byte& r1, Byte& r2, Byte& r3): r1(r1), r2(r2), r3(r3) {}; Byte& r1; Byte& r2; Byte& r3; };
#define CPU_OP_TERNARY(Name) \
struct Name: public Ternary { using Ternary::Ternary; bool execute(CPU& cpu, Memory& memory) override; };

struct Bit: public Base { Bit(uint8_t bit, Byte& r): bit(bit), r(r) {}; uint8_t bit; Byte& r; };
#define CPU_OP_BIT(Name) \
struct Name: public Bit { using Bit::Bit; bool execute(CPU& cpu, Memory& memory) override; };

// Instruction declarations

CPU_OP_NULLARY(NOP);

// 8-bit load instructions

CPU_OP_UNARY(LD_r_n);
CPU_OP_UNARY(LDH_r_in);
CPU_OP_BINARY(LD_r_r);
CPU_OP_TERNARY(LD_r_irr);
CPU_OP_UNARY(LD_iHL_r);
CPU_OP_NULLARY(LD_iHL_n);
CPU_OP_NULLARY(LD_iHLI_A);
CPU_OP_NULLARY(LD_iHLD_A);
CPU_OP_NULLARY(LD_iC_A);
CPU_OP_NULLARY(LDH_in_A);

// 8-bit arithmetic instructions

CPU_OP_UNARY(INC_r);
CPU_OP_UNARY(DEC_r);
CPU_OP_UNARY(XOR_r);
CPU_OP_UNARY(SUB_r);
CPU_OP_NULLARY(CP_n);

// 16-bit load instructions

CPU_OP_NULLARY(LD_SP_HL);
CPU_OP_NULLARY(LD_SP_nn);
CPU_OP_BINARY(LD_rr_nn);
CPU_OP_NULLARY(LD_inn_SP);
CPU_OP_NULLARY(LD_inn_A);
CPU_OP_BINARY(PUSH_rr);
CPU_OP_BINARY(POP_rr);

// 16-bit arithmetic instructions

CPU_OP_BINARY(INC_rr);

// Jump / calls

CPU_OP_NULLARY(JR_n);
CPU_OP_NULLARY(JR_Z_n);
CPU_OP_NULLARY(JR_NZ_n);
CPU_OP_NULLARY(CALL_nn);
CPU_OP_NULLARY(RET);

// 8-bit shift, rotate, bit instructions

CPU_OP_NULLARY(RLA);
CPU_OP_UNARY(RL_r);
CPU_OP_BIT(BIT);

}

#endif /* Operation_hpp */
