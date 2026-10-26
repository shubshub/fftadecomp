#include "ffta.h"

/* Target: complete [0x0813AF98, 0x0813B060), 200 bytes. */
typedef struct {
    u16 count;
    u8 indices[32];
} IndexList;

extern u16 data_03000EB4;
extern u16 data_030027B0[16];

u8 func_0813AF98(u8 group, IndexList *output, IndexList *matches)
{
    u16 count = 0;
    u16 index;
    u16 cursor;

    for (index = 0; index < 16; index++) {
        if ((data_030027B0[index] >> 8) == group)
            matches->indices[count++] = index;
    }
    matches->count = count;

    cursor = data_03000EB4 & 15;
    count = 0;
    for (index = 0; index < 16; index++) {
        if (data_030027B0[cursor] == 0xffff)
            output->indices[count++] = cursor;
        if (cursor < 15)
            cursor++;
        else
            cursor = 0;
    }

    for (index = 0; index < matches->count; index++)
        output->indices[count++] = matches->indices[index];
    output->count = count;
    return count;
}
