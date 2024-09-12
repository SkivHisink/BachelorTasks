/*http://opk.afti.ru/tasks/schastlivye-bilety
Условие:
*На каждом билете автобуса напечатан 6-значный номер. Билет считается счастливым, если сумма первых 3 цифр совпадает с суммой последних 3 цифр.
*Написать программу, которая подчитывает общее количество счастливых билетов и процент относительно общего количества билетов.
*/
#include <stdio.h>


int main(int argc, char* argv[])
{
	int counter = 0, source[6];
	for (int i = 0; i < 1000000; i++) {
		source[0] = (i % 1000000 - i % 100000) / 100000;
		source[1] = (i % 100000 - i % 10000) / 10000;
		source[2] = (i % 10000 - i % 1000) / 1000;
		source[3] = (i % 1000 - i % 100) / 100;
		source[4] = (i % 100 - i % 10) / 10;
		source[5] = i % 10 - i % 1;
		if ((source[0] + source[1] + source[2]) == (source[3] + source[4] + source[5]))
			counter++;
	}
	printf("%d", counter);
	return 0;
}