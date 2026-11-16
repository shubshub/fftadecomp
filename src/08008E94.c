#include "ffta.h"

/* Complete [0x08008E94, 0x08008F94): 256 bytes, 109 instructions,
 * two alignment bytes and four literal words.
 * Target bytes:
 * f0b557464e464546e0b484b0184e30688446b127bf006744ad24a4006444bc25
 * ad006544c4229200624490468c21c9006144bb7c9946fb7c053b1b061b0e9a46
 * e0896246528880180004000c0090a0880190381c4a460cf0d1fe00206883281c
 * 0ef02cfe316821310870002407e00000889100022004001400f042f801343068
 * 213000788442f5db281c0ef0dbfd281c00210b220ef0e4fd1649174a381c0cf0
 * 11ff404600210ff039f8002000f068fa12480268906940690221009120210191
 * 9a235b00191c528889180904090c02910c21039104210f2216230cf01bfc381c
 * 0df05ef904b038bc9846a146aa46f0bc01bc0047817e0108057f010888910002
 */

typedef struct {
    u8 unknown_00[0x14];
    u16 *tiles;
} Display;

typedef struct {
    u8 unknown_00[4];
    u16 setting;
    u8 unknown_06[8];
    u16 tile;
} Descriptor;

typedef struct {
    u8 unknown_00[0x12];
    u8 width;
    u8 height;
    u8 unknown_14[0x18];
} Window;

typedef struct {
    u8 unknown_00[0x1A];
    u16 selection;
    u8 unknown_1C[4];
} List;

typedef struct {
    u16 unknown_00;
    u16 row;
    u8 unknown_04[0x14];
    Display *display;
    u8 unknown_1C[5];
    u8 count;
    u8 unknown_22[0x292];
    Descriptor descriptor;
    Window window;
    List list;
    u8 cursor[0x28];
    u8 unknown_338[0x128];
    u8 text[1];
} State;

typedef void (*Callback)(void *);

extern State *data_02009188;

extern void func_08015C90(void *object, const void *content, u8 width,
                          u8 height, u16 first, u16 second);
extern u16 func_08017B50(List *list);
extern void func_08008F94(s16 index);
extern void func_08017AD8(List *list);
extern void func_08017AF4(List *list, u8 row, u8 value);
extern void func_08015D58(void *window, Callback first, Callback second);
extern void func_08017E80(void *);
extern void func_08017F04(void *);
extern void func_08017FB0(void *cursor, u8 row);
extern void func_08009414(u8 index);
extern void func_080157A8(u16 *tilemap, u8 column, u8 row, u8 width,
                          u8 height, u8 stride, u16 tile, u8 palette);
extern void func_08016234(void *window);

void func_08008E94(void)
{
    Window *window = &data_02009188->window;
    Descriptor *descriptor = &data_02009188->descriptor;
    List *list = &data_02009188->list;
    u8 *cursor = data_02009188->cursor;
    s32 index;

    func_08015C90(window, data_02009188->text, window->width,
                  window->height - 5,
                  data_02009188->row + descriptor->tile,
                  descriptor->setting);
    list->selection = 0;
    data_02009188->count = func_08017B50(list);
    for (index = 0; index < data_02009188->count; index++)
        func_08008F94(index);
    func_08017AD8(list);
    func_08017AF4(list, 0, 11);
    func_08015D58(window, func_08017E80, func_08017F04);
    func_08017FB0(cursor, 0);
    func_08009414(0);
    func_080157A8(data_02009188->display->tiles, 4, 15, 22, 2, 32,
                  0x134 + data_02009188->row, 12);
    func_08016234(window);
}
