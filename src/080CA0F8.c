#include "ffta.h"

/* 0x080CA0F8..0x080CA150: 88 bytes, 39 instructions, including pools. */
typedef struct {
    u32 key;
    u8 unknown_04[0x102];
    u8 table;
} KeyedObject;

extern const u32 g_table_085680DC[];
extern const u32 g_table_085516D0[];

u32 func_080CA0F8(const KeyedObject *object)
{
    u32 i;
    switch (object->table) {
    case 0:
        for (i = 0; i < 725; i++) {
            if (g_table_085680DC[i] == object->key) {
                return i;
            }
        }
        /* An unmatched primary entry also searches the secondary table. */
    case 1:
        for (i = 0; i < 107; i++) {
            if (g_table_085516D0[i] == object->key) {
                return i;
            }
        }
        break;
    }
    return 0;
}
