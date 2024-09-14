#pragma once
#define TRUE 1
#define FALSE 0

_Bool DigitChecker(char* argv[], int index);
_Bool FloatChecker(char* argv[], int index);
_Bool ClearFloatChecker(char* argv[], int index);
_Bool ArgcChecher(int argc);
double DigitOrFloatAssign(double x, char* argv[], int i);