#pragma once

// TODO; includes

// It took a quite time to calculate and rebuild each function.
// All mathematical/geometric operations have been simplified and accelerated as much as possible.

#include "definitions.h"

using namespace std;

/* ███╗░░░███╗░█████╗░████████╗██╗░░██╗███████╗███╗░░░███╗░█████╗░████████╗██╗░█████╗░░█████╗░██╗░░░░░
   ████╗░████║██╔══██╗╚══██╔══╝██║░░██║██╔════╝████╗░████║██╔══██╗╚══██╔══╝██║██╔══██╗██╔══██╗██║░░░░░
   ██╔████╔██║███████║░░░██║░░░███████║█████╗░░██╔████╔██║███████║░░░██║░░░██║██║░░╚═╝███████║██║░░░░░
   ██║╚██╔╝██║██╔══██║░░░██║░░░██╔══██║██╔══╝░░██║╚██╔╝██║██╔══██║░░░██║░░░██║██║░░██╗██╔══██║██║░░░░░
   ██║░╚═╝░██║██║░░██║░░░██║░░░██║░░██║███████╗██║░╚═╝░██║██║░░██║░░░██║░░░██║╚█████╔╝██║░░██║███████╗
   ╚═╝░░░░░╚═╝╚═╝░░╚═╝░░░╚═╝░░░╚═╝░░╚═╝╚══════╝╚═╝░░░░░╚═╝╚═╝░░╚═╝░░░╚═╝░░░╚═╝░╚════╝░╚═╝░░╚═╝╚══════╝

   ░█████╗░██████╗░███████╗██████╗░░█████╗░████████╗██╗░█████╗░███╗░░██╗░██████╗
   ██╔══██╗██╔══██╗██╔════╝██╔══██╗██╔══██╗╚══██╔══╝██║██╔══██╗████╗░██║██╔════╝
   ██║░░██║██████╔╝█████╗░░██████╔╝███████║░░░██║░░░██║██║░░██║██╔██╗██║╚█████╗░
   ██║░░██║██╔═══╝░██╔══╝░░██╔══██╗██╔══██║░░░██║░░░██║██║░░██║██║╚████║░╚═══██╗
   ╚█████╔╝██║░░░░░███████╗██║░░██║██║░░██║░░░██║░░░██║╚█████╔╝██║░╚███║██████╔╝
   ░╚════╝░╚═╝░░░░░╚══════╝╚═╝░░╚═╝╚═╝░░╚═╝░░░╚═╝░░░╚═╝░╚════╝░╚═╝░░╚══╝╚═════╝░ */

// feel the fs_power
extern double __fastcall rtl_pow(double x, long y);
__declspec(naked) double __fastcall rtl_pow(double x, long y) {
    __asm {
        // move y to eax register.
        MOV  EAX, ECX;

        // is calculated all bitsand adding 1 if n < 0.
        // btw abs(y).
        ;

        // get bit into all bits of edx register.
        CDQ;

        // invert bits if negative.
        XOR  EAX, EDX;

        // add 1 if negative. and write eax.
        SUB  EAX, EDX;

        // jump if n = 0.
        JZ short RETZERO;
        
        // write 1.
        FLD1;

        // loading an operand into the top of the stack.
        FLD  QWORD PTR[ESP + 4];

        // jump into l2, btw small optimization.
        JMP short L2;

    L1:;

        // square x.
        FMUL ST(0), ST(0);

    L2:;

        // use arithmetic right shift for precision.
        SAR  EAX, 1;

        JNC  L1;
        FMUL ST(1), ST(0);
        JNZ  L1;
        FSTP ST(0);
        TEST EDX, EDX;
        JNS  RETPOS;
        FLD1;
        FDIVR;

        // finish.
    RETPOS:;

        // FPU Pop2 occurs by compiler on assignment.
        RET  4;

    RETZERO:

        // return 0.0, if n was 0.
        FLDZ;
        RET  4;
    }
}

extern double inline __fastcall rtl_sqrt(double n);
double inline __declspec (naked) __fastcall rtl_sqrt(double n)
{
    __asm {
        // move n to eax register.
        MOV  EAX, ECX;

        // loading an operand into the top of the stack.
        FLD QWORD PTR[ESP + 4];

        // jump if n == zero
        JZ short RETZERO;

        // main part.
        FSQRT;

        // get bit into all bits of edx register.
        CDQ;

        // return.
        RET 8;

    RETZERO:

        // return 0.0, if n was 0.
        FLDZ;
        RET 4;
    }
}

extern double inline __fastcall rtl_cefl(double n);
double inline __fastcall rtl_cefl(double n)
{
    // int prototype.
    int i;

    // check was n == 0.
    if (n == 0) {
        return 0;
    }

    __asm
    {
        // move n to eax.
        MOV EAX, ECX;

        // loading an operand.
        FLD n;

        // NOTE rndl47:
        // converting the value in ST to a signed integer 
        // in accordance with the RC field of the control wordand 
        // transferring the result to memory.

        FISTP i;

    }

    return i;
}

extern int32_t inline __fastcall rtl_abs(int32_t x);
int32_t inline __fastcall rtl_abs(int32_t x)
{
    // result prototype.
    int32_t i;
   
    // take opposite of x value.
    i = -x;
    
    // check was result < 0.
    if (i < 0)
    {
        /* shifting result (right). :
        x is 0x80000000 => 0x7FFFFFFF */  
        i = x - (((uint32_t)x) >> 31);
    }

    return i;
}

// method in polynomial interpolation and approximation theory.
extern float inline __fastcall rtl_expf(const float x);
float inline __fastcall rtl_expf(const float x)
{
    // check was x == 0.
    if (x == 0) {
        return 0;
    }

    float y = rtl_abs(x);
    int k = rtl_cefl((y / M_LN2) - 0.5);
    float r = y - (k * M_LN2);

    // coefficient vector.
    std::vector<float> coeffs = {
        1.000000000000000,
        1.000000000000000,
        0.500000000000002,
        0.166666666666680,
        0.041666666666727,
        0.008333333333342,
        0.001388888888388,
        1.984126978734782e-4,
        2.480158866546844e-5,
        2.755734045527853e-6,
        2.755715675968011e-7,
        2.504861486483735e-8,
        2.088459690899721e-9,
        1.632461784798319e-10 };

    // number taylor.
    float pn = 1.143364767943110e-11;

    // main part.
    for (auto i = coeffs.rbegin(); i != coeffs.rend(); i++)
    {
        pn = pn * r + *i;
    }

    // exp.
    pn *= exp2(k);

    if (x < 0)
    {
        return 1 / pn;
    }

    // return result.
    return pn;
}