#include "ffta.h"

typedef struct ListOwner0802B9B4 ListOwner0802B9B4;
typedef struct ListObject0802B9B4 ListObject0802B9B4;

typedef struct {
    u8 *storage;
    u8 *allocator;
    ListOwner0802B9B4 *owner;
    void *instance;
    ListObject0802B9B4 *resource;
    u8 palette_index;
} DisplayRecord0802B9B4;

typedef struct {
    u8 unknown_000[0x394];
    DisplayRecord0802B9B4 display;
    u8 unknown_3AC[0x1C50];
    u8 setup[0x80];
} State0802B9B4;

extern State0802B9B4 *data_0200F440;
extern void func_0802C72C(void *destination, u16 value, u8 mode);
extern void func_08021BD4(ListObject0802B9B4 *resource, void *instance);
extern void func_08021B54(ListObject0802B9B4 *resource);
extern void func_0800718C(void *object);
extern void func_08022854(u8 *object);

/* Target bytes [0802B9B4, 0802BA08):
 * 10 B5 12 4C 20 68 12 49 40 18 90 21 49 00 00 22
 * 00 F0 B2 FE 20 68 E5 21 89 00 44 18 E1 68 00 29
 * 04 D0 20 69 F6 F7 FC F8 00 20 E0 60 20 69 00 28
 * 03 D0 F6 F7 B5 F8 00 20 20 61 60 68 DB F7 CC FB
 * 20 68 F6 F7 2D FF 10 BC 01 BC 00 47 40 F4 00 02
 * FC 1F 00 00.
 */
void func_0802B9B4(void)
{
    DisplayRecord0802B9B4 *display;

    func_0802C72C(data_0200F440->setup, 0x120, 0);
    display = &data_0200F440->display;
    if (display->instance != 0) {
        func_08021BD4(display->resource, display->instance);
        display->instance = 0;
    }
    if (display->resource != 0) {
        func_08021B54(display->resource);
        display->resource = 0;
    }
    func_0800718C(display->allocator);
    func_08022854(display->storage);
}
