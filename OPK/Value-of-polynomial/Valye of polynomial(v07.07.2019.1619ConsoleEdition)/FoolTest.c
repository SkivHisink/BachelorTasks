#include <stdio.h>
#include "FoolTest.h"
#define TRUE 1
#define FALSE 0

_Bool DigitChecker(char* argv[], int index)
{
	int i = 0;
	while (argv[index][i] != '\0') {
		if ((argv[index][i] > 47) && (argv[index][i] < 58)) {
			i++;
		}
		else {
			return FALSE;
		}
	}
	return TRUE;
}

_Bool FloatChecker(char* argv[], int index)
{
	int i = 0;
	while (argv[index][i] != '\0') {
		if (((argv[index][i] > 47) && (argv[index][i] < 58)) || (argv[index][i] == 46)) {
			if (argv[index][0] == 46)
				return 0;
			i++;
		}
		else {
			return 0;
			break;
		}
	}
}

_Bool ClearFloatChecker(char* argv[], int index)
{
	int i = 0;
	while (argv[index][i] != '\0') {
		if (((argv[index][i] > 47) && (argv[index][i] < 58)) && (argv[index][i] == 46)) {
			if (argv[index][0] == 46)
				return 0;
			i++;
		}
		else {
			return 0;
			break;
		}
	}
}

_Bool ArgcChecher(int argc) 
{
	if (argc <= 1) {
		return 0;
	}
}

double DigitOrFloatAssign(double x, char* argv[], int i) {
	if (ClearFloatChecker(argv, i) == TRUE) {
		return atof(argv[i]);
	}
	else if (DigitChecker(argv, i) == TRUE) {
		return atoi(argv[i]);
	}
}