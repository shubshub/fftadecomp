#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1A];
    u16 field_1A;
    u8 unknown_1C[4];
} MenuList;

typedef struct {
    u8 unknown_00[0x11];
    s8 row;
    u8 unknown_12[2];
} MenuControls;

typedef struct {
    u8 unknown_0000[0xD20];
    MenuList list;
    MenuControls controls;
    u8 unknown_0D54[0x1BBA - 0xD54];
    u8 unknown_1BBA;
    u8 unknown_1BBB[3];
    u8 unknown_1BBE;
    u8 unknown_1BBF;
    u8 unknown_1BC0[0x2CA0 - 0x1BC0];
    u8 timer;
} MenuContext;

extern MenuContext *data_0200F428;
extern void func_08141540(u16 song_id);
extern u16 func_08017B68(MenuList *list, u32 index);

/* Complete target: [0x0805BFC0, 0x0805C02C), 108 bytes, 41 instructions.
 * 10b5041c6420e5f0bbfa78202070124c206812494018282101702068104a81180988104b
 * c0180170206806328118497c0133c018017020688218d2210901401811215156bbf7b0fd
 * 2168074a8918087010bc01bc0047000028f40002a02c00003a0d0000be1b0000ba1b0000
 */
void func_0805BFC0(u8 *state)
{
    func_08141540(100);
    *state = 0x78;
    data_0200F428->timer = 0x28;
    data_0200F428->unknown_1BBE = data_0200F428->list.field_1A;
    /* Each row read goes through &controls: the ROM forms base + 0xD40 at
     * 0x0805BFEC and reads row with ldrb #0x11, then reloads data_0200F428
     * and forms base + 0xD40 again at 0x0805BFF8 for the ldrsb at 0x0805C002.
     * Merged src/0805AAA8.c (saved_selection) and src/0805AB34.c (the
     * func_08017B68 call) read the row through the same block-scoped local. */
    {
        MenuControls *controls = &data_0200F428->controls;

        data_0200F428->unknown_1BBF = controls->row;
    }
    {
        MenuControls *controls = &data_0200F428->controls;

        data_0200F428->unknown_1BBA =
            func_08017B68(&data_0200F428->list, controls->row);
    }
}
