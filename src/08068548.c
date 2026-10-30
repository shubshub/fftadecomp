#include "ffta.h"

typedef struct {
    u16 identifier;
} Entry08068548;

typedef struct {
    u8 unknown_000[0x424];
    Entry08068548 *entries[0];
} Root08068548;

typedef struct {
    u8 unknown_00[0x18];
    u16 field_18;
    u16 field_1A;
} MenuList08068548;

typedef struct {
    Root08068548 *root;
    u8 unknown_04[0xC];
    void *task;
    u8 unknown_14[0x3C];
    MenuList08068548 list;
    u8 unknown_6C[0x15];
    u8 row;
} Object08068548;

typedef struct {
    u8 unknown_00[0x10];
    s8 value10;
    s8 value11;
    s8 value12;
    s8 value13;
    s8 value14;
    s8 value15;
    s8 value16;
    s8 value17;
    u8 unknown_18[8];
} Equipment08068548;

typedef struct {
    u8 unknown_00[9];
    u8 flags;
} Payload08068548;

extern const Equipment08068548 g_table_0851D180[];
extern u16 func_08017B68(MenuList08068548 *list, u32 index);
extern void func_080684B4(u16 x, u16 y, u8 digits, u16 value);
extern void *func_08005BFC(void *task);

/* Target bytes [08068548, 08068620):
 * 30 B5 05 1C 2C 68 50 30 29 1C 81 31 09 78 09 06
 * 09 16 AF F7 05 FB 00 04 80 0B 2D 49 64 18 24 18
 * 20 68 00 88 40 01 2B 49 44 18 10 23 E3 56 1B 04
 * 1B 0C 58 20 5C 21 03 22 FF F7 98 FF 11 23 E3 56
 * 1B 04 1B 0C 58 20 68 21 03 22 FF F7 8F FF 12 23
 * E3 56 1B 04 1B 0C 58 20 74 21 03 22 FF F7 86 FF
 * 13 23 E3 56 1B 04 1B 0C 58 20 80 21 03 22 FF F7
 * 7D FF 14 23 E3 56 1B 04 1B 0C 58 20 8C 21 03 22
 * FF F7 74 FF 28 69 9D F7 15 FB 41 7A 01 20 08 40
 * 00 28 1A D1 16 23 E3 56 1B 04 1B 0C A8 20 58 21
 * 01 22 FF F7 63 FF 17 23 E3 56 1B 04 1B 0C A8 20
 * 64 21 01 22 FF F7 5A FF 15 23 E3 56 1B 04 1B 0C
 * D8 20 64 21 02 22 FF F7 51 FF 30 BC 01 BC 00 47
 * 24 04 00 00 80 D1 51 08.
 */
void func_08068548(Object08068548 *object)
{
    Root08068548 *root = object->root;
    u16 selected = func_08017B68(&object->list, (s8)object->row);
    const Equipment08068548 *equipment =
        &g_table_0851D180[root->entries[selected]->identifier];
    Payload08068548 *payload;

    func_080684B4(0x58, 0x5C, 3, equipment->value10);
    func_080684B4(0x58, 0x68, 3, equipment->value11);
    func_080684B4(0x58, 0x74, 3, equipment->value12);
    func_080684B4(0x58, 0x80, 3, equipment->value13);
    func_080684B4(0x58, 0x8C, 3, equipment->value14);
    payload = func_08005BFC(object->task);
    if (!(payload->flags & 1)) {
        func_080684B4(0xA8, 0x58, 1, equipment->value16);
        func_080684B4(0xA8, 0x64, 1, equipment->value17);
        func_080684B4(0xD8, 0x64, 2, equipment->value15);
    }
}
