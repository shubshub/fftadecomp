#include "ffta.h"

typedef struct {
    u8 unknown_00[0x20];
} List0805093C;

typedef struct {
    u8 unknown_00[0x11];
    u8 index;
} Cursor0805093C;

typedef struct {
    u8 unknown_00[6];
    u16 status;
    u8 mode;
    u8 unknown_09;
    u8 count;
    u8 unknown_0B[0x3D];
    List0805093C list;
    Cursor0805093C cursor;
} Menu0805093C;

extern u8 data_03000000[];
extern void func_080023D0(void *state);
extern void func_08050AF4(Menu0805093C *menu, u16 direction);
extern u16 func_08017B68(List0805093C *list, u32 index);
extern s16 func_08017BE8(List0805093C *list);
extern u16 func_08017B50(List0805093C *list);
extern u8 func_08017A90(List0805093C *list, u16 direction);
extern void func_08050BF0(Menu0805093C *menu, u8 index);
extern void func_08050A8C(Menu0805093C *menu, u16 direction, s8 index, s32 wrap);
extern void func_08141540(s32 sound);

/* 0x0805093C..0x08050A8C: 336 bytes, including literal pools. */
u8 func_0805093C(Menu0805093C *menu, u16 pressed, u16 held)
{
    List0805093C *list = &menu->list;
    Cursor0805093C *cursor = &menu->cursor;
    s8 current;
    s8 next;

    if (pressed & 0x80) {
        func_080023D0(data_03000000);
        if ((held & 0x200) && menu->mode != 1) {
            func_08050AF4(menu, 0x80);
            return 0;
        } else {
            current = cursor->index;

            if (func_08017B68(list, current) < func_08017BE8(list))
                func_08050BF0(menu, current);
            next = current + 1;
            if (next < func_08017B50(list)) {
                if (menu->count > 1)
                    func_08141540(0x6D);
                func_08050A8C(menu, 0x80, next, 0);
                return 0;
            } else if (func_08017A90(list, 0x80)) {
                func_08141540(0x6D);
                func_08050A8C(menu, 0x80, next, 1);
                menu->status = 0xFFFD;
                return 1;
            }
        }
    } else if (pressed & 0x40) {
        func_080023D0(data_03000000);
        if (held & 0x200) {
            func_08050AF4(menu, 0x40);
            return 0;
        } else {
            current = cursor->index;

            if (func_08017B68(list, current) != 0)
                func_08050BF0(menu, current);
            next = current - 1;
            if (next >= 0) {
                if (menu->count > 1)
                    func_08141540(0x6D);
                func_08050A8C(menu, 0x40, next, 0);
                return 0;
            } else if (func_08017A90(list, 0x40)) {
                func_08141540(0x6D);
                func_08050A8C(menu, 0x40, next, 1);
                menu->status = 0xFFFD;
                return 1;
            }
        }
    }
    return 0;
}
