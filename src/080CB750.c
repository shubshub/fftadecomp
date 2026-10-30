#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u8 index;
} Object080CB750;

typedef struct {
    u8 unknown_00[6];
    u16 value;
    u8 unknown_08[6];
} __attribute__((packed)) TableEntry080CB750;

extern const u8 g_table_085273D8[][14];
extern u8 func_080C817C(void *object);
extern u32 func_080C92F0(void *object, u32 selector);

/* 080CB750..080CB78C: 60 bytes, including the packed-record table literal. */
u32 func_080CB750(void *data)
{
    Object080CB750 *object = data;
    u32 result;

    if (!func_080C817C(data))
        result = (u16)func_080C92F0(data, 5);
    else
        result = ((const TableEntry080CB750 *)g_table_085273D8[object->index])->value;
    return result;
}
