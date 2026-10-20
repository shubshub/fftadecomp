#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u8 index;
} ScriptData;

typedef struct {
    u8 unknown_00[4];
    u16 value;
    u8 unknown_06[8];
} __attribute__((packed)) TableEntry;

extern const u8 g_table_085273D8[][14];

u8 func_080C817C(void *data);
u16 func_080C92F0(void *data, u32 selector);

u32 func_080CB714(void *data)
{
    ScriptData *object = data;
    u32 result;

    if (!func_080C817C(data))
        result = func_080C92F0(data, 4);
    else
        result = ((const TableEntry *)g_table_085273D8[object->index])->value;
    return result;
}
