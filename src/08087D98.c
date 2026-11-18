#include "ffta.h"

typedef struct {
    s32 key;
    s32 value;
} SortEntry;

extern void func_0808A0B4(SortEntry *entries, s32 left, s32 right);

static inline void partition(SortEntry *entries, s32 left, s32 right)
{
    s32 i = left;
    s32 j = right;
    s32 pivot = entries[(right + left) / 2].key;

    do {
        while (entries[i].key < pivot)
            i++;
        while (pivot < entries[j].key)
            j--;
        if (i <= j) {
            SortEntry tmp = entries[i];
            entries[i] = entries[j];
            entries[j] = tmp;
            i++;
            j--;
        }
    } while (i <= j);

    if (left < j)
        func_0808A0B4(entries, left, j);
    if (i < right)
        func_0808A0B4(entries, i, right);
}

void func_08087D98(SortEntry *entries, s32 left, s32 right, s32 descending)
{
    if (descending) {
        SortEntry copy[24];
        s32 i;

        for (i = 0; i < 24; i++)
            copy[i] = entries[i];
        partition(copy, left, right);
        for (i = 0; i < right + 1; i++)
            entries[i] = copy[right - i];
    } else {
        partition(entries, left, right);
    }
}
