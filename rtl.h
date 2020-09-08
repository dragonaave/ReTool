#pragma once

// TODO; includes

// It took a quite time to calculate and rebuild each function.
// All mathematical/geometric operations have been simplified and accelerated as much as possible.

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

extern double inline __fastcall rtl_ceil(double n);
double inline __fastcall rtl_ceil(double n)
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

int maybe_addition_float(float a, float b) {

}

int maybe_subtraction_float(float a, float b) {

}
