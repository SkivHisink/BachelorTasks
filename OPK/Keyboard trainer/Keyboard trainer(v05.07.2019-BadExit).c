/*http://opk.afti.ru/tasks/klaviaturnyy-trenazher
Условие:
*Программа выводит на экран случайно сгенерированную строку печатных символов.
*Пользователь должен набрать с клавиатуры идентичную строку.
*Неправильно набранные символы не принимаются и игнорируются программой.
*Пользователь должен ввести остаток строки, начиная с первого неправильно введенного символа.
*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void RandomString(char* a, int difficult);

void FoolTest(int difficult, char* a, char* b);

int main(int argc, char* argv[])
{
	srand(time(NULL));
	char* a, * b;
	int difficult, counter = 0;
	printf("Enter number of characters:");
	scanf_s("%d", &difficult);
	getchar();
	a = (char*)malloc(difficult * sizeof(char));
	b = (char*)malloc(difficult * sizeof(char));
	FoolTest(difficult, a, b);
	RandomString(a, difficult);
	printf("%s\n", a);
	while (difficult != counter) {
		b[counter] = _getch();
		if (b[counter] != a[counter]) {
			printf("\nWrong charcter! Continue entering characters froom this \n");
			b[counter] = '\0';
			printf("%s", b);
		}
		else {
			b[counter + 1] = '\0';
			counter++;
			printf("%c", b[counter - 1]);
		}
	}
}

void RandomString(char* a, int difficult)
{
	int b;
	for (int i = 0; i < difficult; i++) {
		b = rand() % 60 + 64;
		if (((b > 64) && (b < 91)) || ((b > 96) && (b, 123)))
			a[i] = b;
		else
			i--;
	}
	a[difficult] = '\0';
}

void FoolTest(int different, char* a, char* b)
{
	if (different <= 0) {
		printf("Wrong difficult");
		getchar();
		exit(1);
	}
	if (a == NULL || b == NULL) {
		printf("Error! Memory isn't allocate.)");
		exit(1);
	}
}