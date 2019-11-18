#ifndef _bitwise_h
#define _bitwise_h

#include <stddef.h>

#define NO_OF_BITS (sizeof(int) * 8)
#define TWO 2
#define SIX 32
#define UNUSED(var) (void)(var)
#define m1 0xFFFF0000
#define m2 0x0000FFFF
#define m3 0xFF00FF00
#define m4 0x00FF00FF
#define m5 0xF0F0F0F0
#define m6 0x0F0F0F0F
#define m7 0xCCCCCCCC
#define m8 0x33333333
#define m9 0xAAAAAAAA
#define m10 0x55555555

#define GRN  "\x1B[32m"
#define RED  "\x1B[31m"
#define RESET "\x1B[0m"


long Pow2(unsigned int x, unsigned int y);
int LoopIsPow2(unsigned int n);
int IsPow2(unsigned int n);
int PlusOne(int x);
void Print3BitsInt(unsigned int *arr, int size);
unsigned int ByteMirrorLoop(unsigned int x);
unsigned int ByteMirror(unsigned int x);
int Check2n6(unsigned char c);
int Check2or6(unsigned char c);
int Swap3n5(unsigned char c);
unsigned int ClosestSmaller(unsigned int x);
void Swap(unsigned int *px, unsigned int *py);
int LoopBitsOnNum(unsigned int x);
int BitsNum(unsigned int x);
int *FloatAnalysis(float f);

#endif
