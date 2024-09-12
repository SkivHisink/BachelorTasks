/*http://opk.afti.ru/tasks/fizzbuzz
Условие: 
Написать программу, которая будет печатать все числа от 1 до 100. При этом:
*Если число делится на 3, вместо числа напечатать Fizz
*Если число делится на 5, вместо числа напечатать Buzz
*Если число делится и на 3 и на 5, вместо числа напечатать FizzBuzz*/
#include <stdio.h>

int main()
{
	for (int i = 1; i < 101; i++) {
		if ((i % 3 == 0) && (i % 5 == 0))
			printf("FizzBuzz ");
		else if (i % 3 == 0)
			printf("Fizz ");
		else if (i % 5 == 0)
			printf("Buzz ");
		else
			printf("%d ", i);
	}
	getchar();
	return 0;
}