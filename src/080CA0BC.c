#include "ffta.h"

typedef struct {
    u32 key;
    u8 unknown_04[0x102];
    u8 table;
} KeyedObject080CA0BC;

extern u8 data_02001F1C[];
extern const u32 g_table_085516D0[];

/* Complete [0x080CA0BC, 0x080CA0F8): 60 bytes, 25 instructions. */
void func_080CA0BC(KeyedObject080CA0BC *object, u8 index)
{
    if (index == 2) {
        object->key = (u32)data_02001F1C;
        object->table = 2;
    } else {
        object->key = g_table_085516D0[index];
        object->table = 1;
    }
}
