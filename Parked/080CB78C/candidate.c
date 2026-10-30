#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u8 index;
} Object080CB78C;

typedef struct {
    u8 unknown_00[0xB];
    u8 field_0b;
} RecordView080CB78C;

extern const u8 g_table_085273D8[][14];
extern u8 func_080C817C(void *data);
extern u32 func_080C92F0(void *data, u32 selector);

/* Complete target: [0x080CB78C, 0x080CB7C0), 52 bytes. */
u32 func_080CB78C(void *data)
{
    Object080CB78C *object = data;
    u32 result;

    if (!func_080C817C(data))
        result = (u8)func_080C92F0(data, 9);
    else
        result = ((const RecordView080CB78C *)g_table_085273D8[object->index])->field_0b;
    return result;
}
