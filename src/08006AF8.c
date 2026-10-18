#include "ffta.h"

void func_08006AF8(Table *table, u8 index, u32 value, u8 flags)
{
    table->words[index] = value;
    table->flags[index] = flags;
}
