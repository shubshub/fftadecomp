#include "ffta.h"

/* Complete [0x0806D428, 0x0806D58E): 358 bytes, 142 instructions.
 * f0b5474680b480463b4f3868a72676018119a62252018018
 * 497c09060916aaf78ffb3968354d49190870386841190978
 * 89004118324bc9180a88183bc1180a80304c001901f0bafd
 * 3a680006000e2e4bd11809182d4812181088087038680019
 * 01f0acfd3a680006000e294bd11809189219507c08703868
 * 011909789822d201801801703868001901f098fd3968214b
 * c91808703a6855192878800010181e4bc1180133c0180978
 * 0078814238d9101901f084fd3968194a8918087038680019
 * 01f07cfd3a680006000e114bd11809180e48121810880870
 * 3868001901f06efd3a680006000e0a4bd11809189219507c
 * 0870282418e0000028f40002ee4400000445000070440000
 * f1440000da140000f7440000014c000006450000f0440000
 * 6420d3f0f9ff7824084d28680849401802f05cfc0006000e
 * 01280dd13e20424610702868034bc01807e0000028f40002
 * 881a00006c4400004046047008bc9846f0bc01bc0047
 */

typedef struct {
    u8 unknown_00[0x1a];
    u16 item;
    u8 unknown_1c[0x15];
    s8 selection;
} Panel0806D428;

typedef struct {
    u8 count;
    u8 unknown_01[0x7b];
} Menu0806D428;

typedef struct {
    u16 item;
    u8 quantity;
    u8 unknown_03;
} Item0806D428;

/* Layout as src/0806B4C4.c through saved_count (0x4BFF).  0x4C00 takes
 * menu.count here (0x0806D4A4) as 0x4BFF does there (0x0806B544), and
 * 0x4C01 takes the menu entry (0x0806D4B6). */
typedef struct {
    u8 unknown_0000[0x14c0];
    Panel0806D428 panel;
    u8 unknown_14f4[0x594];
    u8 context[0x29e4];
    u8 next;
    u8 unknown_446d[3];
    Menu0806D428 menu;
    u16 item;
    u8 selection;
    u8 unknown_44ef;
    u8 menu_index;
    u8 values[6];
    u8 choices[6];
    u8 unknown_44fd[7];
    Item0806D428 items[0x178];
    u16 error;
    u8 unknown_4ae6[0x115];
    u8 type;
    u8 unknown_4bfc[3];
    u8 saved_count;
    u8 saved_menu_count;
    u8 saved_menu_entry;
} State0806D428;

typedef struct {
    u8 unknown_00[0x11];
    s8 selection;
} Selection0806D428;

typedef struct {
    u8 current;
} Command0806D428;

/* The selection byte is read through a 0x14E0 base: movs #0xa7; lsls #5 at
 * 0x0806D434, then ldrb [base, #0x11] at 0x0806D440, 0x0806D49A and
 * 0x0806D516, while panel.item (0x14DA) is a whole pool constant.  The plain
 * panel.selection, or a Selection member nested in Panel, folds to one
 * 0x14F1 constant instead.  Same accessor, character for character, as
 * src/0806B4C4.c, which reads this byte the same way. */
#define selection_panel(state) \
    ((Selection0806D428 *)((u8 *)(state) + 0x14e0))

extern State0806D428 *data_0200F428;
extern u16 func_08017B68(Panel0806D428 *, s8);
extern u8 func_0806EFE4(Menu0806D428 *);
extern void func_08141540(u16);
extern u8 func_0806FE14(void *);

void func_0806D428(Command0806D428 *command)
{
    u32 next;
    s8 panel_selection = selection_panel(data_0200F428)->selection;

    data_0200F428->selection = func_08017B68(&data_0200F428->panel, panel_selection);
    data_0200F428->item = data_0200F428->items[data_0200F428->selection].item;
    data_0200F428->values[func_0806EFE4(&data_0200F428->menu)] =
        data_0200F428->panel.item;
    data_0200F428->choices[func_0806EFE4(&data_0200F428->menu)] =
        selection_panel(data_0200F428)->selection;
    data_0200F428->saved_menu_count = data_0200F428->menu.count;
    data_0200F428->saved_menu_entry = func_0806EFE4(&data_0200F428->menu);

    if (data_0200F428->items[data_0200F428->selection].quantity >
        data_0200F428->items[data_0200F428->selection].unknown_03) {
        data_0200F428->menu_index = func_0806EFE4(&data_0200F428->menu);
        data_0200F428->choices[func_0806EFE4(&data_0200F428->menu)] =
            data_0200F428->panel.item;
        data_0200F428->choices[func_0806EFE4(&data_0200F428->menu)] =
            selection_panel(data_0200F428)->selection;
        next = 40;
    } else {
        func_08141540(100);
        next = 120;
    }

    if (func_0806FE14(data_0200F428->context) == 1) {
        command->current = 62;
        data_0200F428->next = next;
    } else {
        command->current = next;
    }
}
