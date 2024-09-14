void Radix_Sort(int* arr, size_t count, size_t size, int (*cmp)(const void*, const void*))
{
	int* result;
	if ((result = (int*)malloc(count * sizeof(int))) == NULL)
		return NULL;
	for (int i = 0; i < count; i++)
		result[i] = arr[i];
	for (int i = 0; i < sizeof(int); i++) {
		for (int i = 0; i < count; i++)
			arr[i] = result[i];
		int byte[256] = { 0 };
		for (int j = 0; j < count; j++)
			byte[((arr[j] >> (i * sizeof(int)))& (255))]++;
		int bytes_value[256] = { 0 };
		for (int f = 1; f < 256; f++)
			bytes_value[f] = bytes_value[f - 1] + byte[f - 1];
		for (int k = 0; k < count; k++)
			result[(bytes_value[((arr[k] >> (i * sizeof(int)))& (255))]++)] = arr[k];
	}
	int k = 0;
	for (int i = 0; i < count; i++) {
		if (result[i] < 0) {
			arr[k] = result[i];
			k++;
		}
	}
}
