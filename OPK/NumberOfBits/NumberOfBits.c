#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
int NumbOfBit(int i);

int main(int argc, char* argv[])
{
	assert(NumbOfBit(256) == 1);
	assert(NumbOfBit(-1) == 32);
	assert(NumbOfBit(254) == 7);
	assert(NumbOfBit(1) == 1);
	assert(NumbOfBit(255) == 8);
	assert(NumbOfBit(-255) == 25);
	assert(NumbOfBit(10) == 2);
	assert(NumbOfBit(-5) == 31);
	assert(NumbOfBit(0) == 0);
	return 0;
}

int NumbOfBit(int number)
{
	int c = 0;
	for (int i = 0; i < sizeof(int) * 8; i++, number >>= 1) {
		number & 1 == 1 ? c++ : 1;
	}
	__asm { mov eax, c}
}
