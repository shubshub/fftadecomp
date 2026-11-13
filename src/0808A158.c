// Target: 0x0808A158-0x0808A1E8, 144 complete bytes.
typedef unsigned short u16;

void func_0808A158(u16 *a, int lo, int hi)
{
    int i = lo;
    int j = hi;
    int pivot = a[(j + i) / 2];

    do {
        while (a[i] < pivot)
            i++;
        while (pivot < a[j])
            j--;
        if (i <= j) {
            u16 t = a[i];
            a[i] = a[j];
            a[j] = t;
            i++;
            j--;
        }
    } while (i <= j);
    if (lo < j)
        func_0808A158(a, lo, j);
    if (i < hi)
        func_0808A158(a, i, hi);
}
