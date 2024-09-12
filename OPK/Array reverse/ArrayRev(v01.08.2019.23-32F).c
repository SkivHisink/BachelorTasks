/*http://opk.afti.ru/tasks/oborachivanie-massiva
Условие:
*Дан массив целых чисел. 
*Реализовать функцию, переставляющую элементы массива в обратном порядке, не используя других массивов.
///void reverse(int arr[], size_t count) {
///	
///}
*/
#include <stdio.h>
#include <malloc.h>
void reverse(int arr[], size_t count);

int main()
{
	int count=0;
	int* digArray=NULL;
	printf("Enter number of digits:");
	scanf_s("%d", &count);
	digArray = (int*)malloc(count * sizeof(int));
	printf("Enter digits with a space:");
	for (int i = 0; i < count; i++)
	{
		scanf_s("%d", &digArray[i]);
	}
	reverse(digArray, (size_t)count);
	for (int i = 0; i < count; i++)
	{
		printf("%d ", digArray[i]);
	}
	free(digArray);
	return 0;
}

void reverse(int arr[], size_t count)
{
	int temp = 0;
	for (int i = 0; i < count / 2; i++) {
		temp = arr[i];
		arr[i] = arr[count - i - 1];
		arr[count - i-1] = temp;
	}
}
