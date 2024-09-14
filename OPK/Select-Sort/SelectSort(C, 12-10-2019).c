void Swapper(void* x, void* y, size_t size)
{
	for (size_t i = 0; i < size; i++) {
		char tmp = ((char*)x)[i];
		((char*)x)[i] = ((char*)y)[i];
		((char*)y)[i] = tmp;
	}
}

void Select_Sort(const void* parray, size_t count, size_t size, int (*cmp)(const void*, const void*))
{
	if (count > 1) {
		for (size_t i = 0; i < count; i++) {
			int num = i;
			for (size_t j = i + 1; j < count; j++) {
				if (cmp((char*)parray + j * size, (char*)parray + num * size) == -1)
					num = j;
			}
			if (num != i)
				Swapper((char*)parray + i * size, (char*)parray + num * size, size);
		}
	}
}