void Insert_Sort(int* ptr, size_t count)
{
	for (size_t i = 1; i < count; i++) {
		int buf = ptr[i];
		int j = i;
		while ((j > 0) && (ptr[j - 1] > buf)) {
			ptr[j] = ptr[j - 1];
			j--;
		}
		ptr[j] = buf;
	}
}