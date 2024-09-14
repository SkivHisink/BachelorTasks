#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <stdbool.h>
#include <assert.h>

int Icmp(void* x, void* y);
int Dcmp(void* x, void* y);
bool Test(size_t size, int (*cmp)(const void*, const void*), int (*dcmp)(const void*, const void*));

int main(void)
{
	int (*cmp)(void* x, void* y) = Icmp;
	int (*dcp)(void* x, void* y) = Dcmp;
	assert(SpecTest(cmp, dcp));
	assert(Test(111, cmp, dcp));
	for (int i = 100000; i < 1000000000; i += 100000)
		assert(Test(i, cmp, dcp));
	return 0;
}

/*if x>y it will return 1, elif x<y will return -1, else will return 0*/
int Icmp(const void* x, const void* y)
{
	int a = *(int*)x;
	int b = *(int*)y;
	return (a > b) - (a < b);
}

/*if x>y it will return 1, elif x<y will return -1, else will return 0*/
int Dcmp(const void* x, const void* y)
{
	double a = *(double*)x;
	double b = *(double*)y;
	return (a > b) - (a < b);
}

void Swapper(void* x, void* y, size_t size)
{
	for (size_t i = 0; i < size; i++) {
		char tmp = ((char*)x)[i];
		((char*)x)[i] = ((char*)y)[i];
		((char*)y)[i] = tmp;
	}
}

void Rand_Sort(const void* ptr, size_t count, size_t size)
{
	for (size_t i = 0; i < count; i++)
		Swapper((char*)ptr + i * size, (char*)ptr + rand() % count * size, size);
}

void Quick_Sort(const void* ptr, int low, int high, size_t size, int (*cmp)(const void*, const void*))
{
	int i = low;
	int j = high;
	char* pivot = (char*)ptr + low * size;
	while (i <= j)
	{
		while (i < high && (cmp((char*)ptr + i * size, pivot) == -1))
			i++;
		while (j > low&& cmp((char*)ptr + j * size, pivot) == 1)
			j--;
		if (i <= j) {
			Swapper((char*)ptr + i * size, (char*)ptr + j * size, size);
			i++;
			j--;
		}
	}
	if (j > low)
		Quick_Sort(ptr, low, j, size, cmp);
	if (i < high)
		Quick_Sort(ptr, i, high, size, cmp);
}

/*Summon it Function for sort*/
void my_qsort(const void* ptr, size_t count, size_t size, int (*cmp)(const void*, const void*))
{
	Rand_Sort(ptr, count - 1, size);
	Quick_Sort(ptr, 0, count - 1, size, cmp);
}

/*Just for test on random numbers*/
bool Test(size_t size, int (*cmp)(const void*, const void*), int (*dcp)(const void*, const void*))
{
	int* parrayInt = NULL;
	double* parrayDouble = NULL;
	srand(time(NULL));
	clock_t start, end;
	parrayInt = RandSprayInt((size_t)size);
	parrayDouble = RandSprayDouble((size_t)size);
	if ((parrayInt == NULL) && (parrayDouble == NULL))
		return false;
	start = clock();
	my_qsort(parrayInt, size, sizeof(parrayInt[0]), cmp);
	my_qsort(parrayDouble, size, sizeof(parrayDouble[0]), dcp);
	end = clock();
	if (!checksortInt(parrayInt, size, cmp) || !checksortDouble(parrayDouble, size, dcp))
		return false;
	printf("Size=%ld | Time:%lf\n", size, (double)(end - start) / CLOCKS_PER_SEC);
	free(parrayInt);
	free(parrayDouble);
	return true;
}
