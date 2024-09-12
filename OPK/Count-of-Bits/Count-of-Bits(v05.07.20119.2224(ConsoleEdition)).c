/*http://opk.afti.ru/tasks/kolichestvo-edinichnyh-bit
Условие:
*Реализовать функцию, подсчитывающую количество бит, установленных в 1, в переданном аргументе типа int.
*/
///if returned: 
///1 - not enough arguments;
///2 - firts argument have a symbols that not the digits; 
///3 - second argument have a symbols that not the digits.
#include <stdio.h>
#define TRUE 0
#define FALSE 1

int BitFounder(int number, int counter);

void FoolTest(int argc, char* argv[], _Bool checker[]);

int main(int argc, char* argv[])
{
	_Bool checker[3] = { 0, 0, 0 };
	int counter = 0;
	FoolTest(argc, argv, checker);
	if (checker[0] == FALSE) {
		return 1;
	}
	else if (checker[1] == FALSE) {
		return 2;
	}
	else if (checker[2] == FALSE) {
		return 3;
	}
	printf(" %d bit", BitFounder(atoi(argv[1]), counter));
	getchar();
	getchar();
	return 0;
}

int BitFounder(int number, int counter)
{
	for (int d = 31; d >= 0; d--) {
		int b = (((1 << d) & number) ? '1' : '0') - 48;
		printf("%d", b);
		if (b == 1) {
			counter++;
		}
	}
	return counter;
}

_Bool DigitChecker(char argv[])
{
	int i = 0;
	while (argv[i] != '\0') {
		if ((argv[i] > 47) && (argv[i] < 58)) {
			i++;
		}
		else {
			return FALSE;
		}
	}
	return TRUE;
}

void FoolTest(int argc, char* argv[], _Bool checker[])
{
	if (argc != 2) {
		checker[0] = FALSE;
	}
	checker[1] = DigitChecker(argv[1]);
}