/*http://opk.afti.ru/tasks/udalenie-probelov-v-nachale-i-kontse-stroki
Условие:
*Реализовать функцию, убирающую пробельные символы в начале и конце переданной строки.
*Не допускается использование дополнительных строк (дополнительной памяти).
*Для определения пробельности символов использовать функцию isspace() из ctype.h.
///void strtrim(char *string)
///{
///
///}
//*Пример использования :
//*	char buf[] = " abc ";
//*	printf("<%s>\n", buf); // < abc >
//*	strtrim(buf);
//*	printf("<%s>\n", buf); // <abc>
*/
///Error types:
///1 - your enter wrong number of characters or you enter characters
///2 - memory is not allocate
#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#define TRUE 1
#define FALSE 0

void strtrim(char* string, int strSize);
_Bool DigitChecker(char* argv);
_Bool MemoryTest(char* string);
int main()
{
	char* arr = NULL;
	int c = 0;
	int n = 4;
	arr = (char*)malloc(3 * sizeof(char));
	int strSize;
	if (!MemoryTest(arr)) {
		return 2;
	}
	printf("Enter number of characters(in the end write #):");
	while (TRUE)
	{
		*(arr + c) = getchar();
		if (c == n - 2)
		{
			char* b;
			b = (char*)malloc((2 * (n)) * sizeof(char));
			for (int i = 0; i < (n - 1); i++)
			{
				*(b + i) = *(arr + i);
			}
			free(arr);
			arr = b;
			n = 2 * n;
		}
		if (*(arr + c) == '#')
			break;
		c++;
	}
	*(arr + c) = '\0';
	getchar();
	if (!DigitChecker(arr)) {
		return 1;
	}
	strSize = atoi(arr);
	printf("Enter characters:");
	arr = (char*)malloc(strSize * sizeof(char));
	for (int i = 0; i < strSize; i++) {
		scanf_s("%c", &arr[i]);
	}
	strtrim(arr, strSize);
	printf("%s", arr);
	free(arr);
	return 0;
}

void strtrim(char* string, int strSize)
{

	if (isspace(string[0])) {
		for (int i = 0; i < strSize; i++) {
			string[i] = string[i + 1];
		}
		strSize -= 1;
	}
	int b = 0;
	if (b=isspace(string[strSize - 2]))
	{
		string[strSize - 2] = '\0';
	}
}

_Bool DigitChecker(char* argv)
{
	int i = 0;
	while (TRUE) {
		if ((argv[i] > 47) && (argv[i] < 58)) {
			i++;
		}
		else if ((argv[i] != '\0') || (argv[i] != '\n')) {
			break;
		}
		else {
			return FALSE;
		}
	}
	return TRUE;
}

_Bool MemoryTest(char* string)
{
	if (string == NULL) {
		return FALSE;
	}
	return TRUE;
}