#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include <malloc.h>
#define SIMPLE_NUMBER 175993
#define BIG_NUMBER 256
char* my_strstr(char* haystack, const char* needle);
void Test_str(void);
bool check_str(char* haystack, const char* needle);

int main(void)
{
	Test_str();
	return 0;
}

bool check_str(char* haystack, const char* needle)
{
	char* str = strdup(needle);
	char* result = my_strstr(haystack, needle);
	if (result != NULL) {
		for (int i = 0; i < strlen(needle); i++)
			str[i] = result[i];
		bool res = (strcmp(str, needle) == 0);
		if (strlen(str) != 0)
			free(str);
		return res;
	}
	else
		return false;
}
//�������� � check_str
void Test_str(void)
{
	assert(check_str("", ""));
	assert(check_str("abc", "abc"));
	assert(check_str("pupalupati kalitka", "tka"));
	assert(check_str("qwerty", "rty"));
	assert(check_str("qweqwe", "qwe"));
	assert(check_str("jaisdjiaslcxlzjchsjoaerofnqsjaiosdjaojdioasjcozjxci", "jao"));
	assert(check_str("123321", "33"));
	assert(check_str("27+(-15)=124", "-1"));
	assert(check_str("footoof", "toof"));
    //assert(check_str("qwerty", "qwertyqwerty"));
	//assert(check_str("a_c", "a c"));
	//assert(check_str("a__c", "a  c"));
	//assert(check_str("a_c", "a\tc"));
	//assert(check_str("_a_c_", " a\tc "));
	//char h[] = { -5, -3, 2, 1 };
	//char n[] = { -3, 2, 1 };
	//assert(another_check_str(h, sizeof(h), n, sizeof(n)));
	//assert(check_str(h, n));
}

char* my_strstr(char* haystack, const char* needle)
{
	int m = strlen(needle);
	int n = strlen(haystack);
	int j;
	long long hashN = 0;
	long long hashH = 0;
	long long hashT = 1;
	for (int i = 0; i < m - 1; i++) {
		hashT = (BIG_NUMBER * hashT) % SIMPLE_NUMBER;
	}
	for (int i = 0; i < m; i++) {
		hashN = (BIG_NUMBER * hashN + (unsigned char)needle[i]) % SIMPLE_NUMBER;
		hashH = (BIG_NUMBER * hashH + (unsigned char)haystack[i]) % SIMPLE_NUMBER;
	}
	for (int i = 0; i <= n - m; i++) {
		if (hashH == hashN) {
			for (j = 0; j < m; j++) {
				if (haystack[i + j] != needle[j])
					break;
			}
			if (j == m)
				return &haystack[i];
		}
		if (i < n - m) {
			hashH = (BIG_NUMBER * (hashH - (unsigned char)haystack[i] * hashT) + (unsigned char)haystack[i + m]) % SIMPLE_NUMBER;
			if (hashH < 0)
				hashH = (hashH + SIMPLE_NUMBER);
		}
	}
	return NULL;
}

bool another_check_str(char* haystack, size_t haystack_length, char* needle, size_t needle_length)
{
	if ((haystack_length < 0) && (needle_length < 0))
		return false;
	char* new_haystack = (char*)malloc((haystack_length + 1) * sizeof(char));
	char* new_needle = (char*)malloc((needle_length + 1) * sizeof(char));
	for (int i = 0; i < haystack_length; i++) {
		new_haystack[i] = haystack[i];
	}
	new_haystack[haystack_length] = '\0';
	for (int i = 0; i < needle_length; i++)
		new_needle[i] = needle[i];
	new_needle[needle_length] = '\0';
	char* str = (char*)malloc((needle_length + 1) * sizeof(char));
	//size_t size = _msize(str);
	char* result = my_strstr(new_haystack, new_needle);
	if (result != NULL) {
		for (int i = 0; i < needle_length + 1; i++)
			str[i] = result[i];
		bool res = (strstr(str, needle) == 0);
		if (strlen(str) != 0)
			free(str);
		if (new_haystack != 0)
			free(new_haystack);
		return res;
	}
	else
		return false;
}