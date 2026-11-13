/* 0x08089BA4: 168 bytes. Sort bytes by their low seven bits. */
void func_08089BA4(unsigned char *values, int first, int last)
{
    int left = first;
    int right = last;
    int pivot = values[(right + left) / 2] & 0x7f;
    unsigned char temporary;

    do {
        while ((values[left] & 0x7f) < pivot)
            left++;
        while (pivot < (values[right] & 0x7f))
            right--;
        if (left <= right) {
            temporary = values[left];
            values[left] = values[right];
            values[right] = temporary;
            left++;
            right--;
        }
    } while (left <= right);

    if (first < right)
        func_08089BA4(values, first, right);
    if (left < last)
        func_08089BA4(values, left, last);
}
