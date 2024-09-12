/*http://opk.afti.ru/tasks/tselsiy-i-farengeyt
Условие:
*Написать программу, которая переводит градусы Цельсия в градусы Фаренгейта и обратно.
*Пользователь указывает режим перевода и вводит значение, программа переводит его в другую систему.
*Формула: C = (F - 32) * 5/9
*/

#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

void FoolTest(int argc, char* argv[], _Bool checker[]);

int main(int argc, char* argv[])
{

	_Bool checker[3] = { 0, 0, 0 };
	printf("%s ", argv[1]);//For test
	printf("%s\n", argv[2]);//For test
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
	float temp = atof(argv[2]);
	if (argv[1][0] == 'C') {
		temp = temp * 9 / 5 + 32;
		printf("%f temperature in Fahrenheit", temp);
	}
	else if (argv[1][0] == 'F') {
		temp = (temp - 32) * 5 / 9;
		printf("%f temperature in Celsius", temp);
	}
	else {
		return 4;
	}
	getchar();
	getchar();
	return 0;
}

void FoolTest(int argc, char* argv[], _Bool checker[])
{
	if (argc != 3) {
		checker[0] = 0;
	}
	int i = 0;
	while (argv[2][i] != '\0') {
		if (((argv[2][i] > 47) && (argv[2][i] < 58)) || (argv[2][i] == 46)) {
			if (argv[2][0] == 46)
				checker[1] = 0;
			i++;
		}
		else {
			checker[2] = 0;
			break;
		}
	}
}