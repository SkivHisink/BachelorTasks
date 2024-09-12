/*http://opk.afti.ru/tasks/kolichestvo-edinichnyh-bit
Условие:
*Реализовать функцию, подсчитывающую количество бит, установленных в 1, в переданном аргументе типа int.
*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int BitFounder(int a, int counter);

int main(int argc, char* argv[])
{
	srand(time(NULL));
	int a, counter = 0;
	printf("Enter number:");
	scanf_s("%d", &a);
	printf(" %d bit", BitFounder(a, counter));
	getchar();
	getchar();
	return 0;
}

int BitFounder(int a, int counter)
{
	
	for (int d = 31; d >= 0; d--) {
		int b = (((1 << d) & a) ? '1' : '0')-48;
		printf("%d", b);
		if (b == 1)
		{
			counter++;
		}
	}
	return counter;
}