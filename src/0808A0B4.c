/* Complete [0x0808A0B4,0x0808A158): 164 bytes. */
#include "ffta.h"

typedef struct {
    s32 key;
    s32 value;
} SortEntry0808A0B4;

void func_0808A0B4(SortEntry0808A0B4 *entries, s32 left, s32 right)
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
            SortEntry0808A0B4 tmp = entries[i];
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
