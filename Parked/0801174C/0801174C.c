// func_0801174C: 0x0801174C-0x08011860, 276 bytes
#include "ffta.h"

typedef void (*BufferInitializer)(void *destination, u32 size);

typedef struct {
    u8 unknown_00[0x10];
    u8 *tiles;
} WindowParent;

typedef struct {
    WindowParent *parent;
    u32 unknown_04;
    u8 state;
    u8 unknown_09;
    u8 field_0a;
    u8 unknown_0b;
    u8 unknown_0c[2];
    u8 field_0e;
    u8 field_0f;
    u8 unknown_10;
    u8 field_11;
    u16 field_12;
    u8 unknown_14[2];
    u16 field_16;
    u16 field_18;
    u8 field_1a;
    u8 unknown_1b;
    u8 field_1c;
    u8 field_1d;
    u8 field_1e;
    u8 field_1f;
    u16 field_20;
    u8 unknown_22[6];
    u8 field_28;
    u8 unknown_29[0x2d7];
    u8 *tile_ptr;
} WindowObject;

extern BufferInitializer const g_callbacks_0836D4B8[];
extern WindowObject *data_0200918C;
extern void func_0814224C(void *destination, u32 size,
                          BufferInitializer callback);
extern u8 func_080C9540(u16 flag);
extern u32 func_08018028(WindowObject *, u8, u16 *, u8 *);
extern void func_08011CD0(u32, u8 *, u16);

void func_0801174C(WindowObject *object, u8 kind, u16 entry, WindowParent *parent,
                   u32 value, u16 a, u16 b, u8 c, u8 d, u16 e)
{
    u8 flag[4];
    u16 slot;
    u8 *flag_ptr = 0;
    u16 *entry_ptr = &slot;
    u32 result;
    BufferInitializer const *callbacks;

    slot = entry;

    data_0200918C = object;
    callbacks = g_callbacks_0836D4B8;
    func_0814224C(data_0200918C, 0x794, callbacks[0]);
    data_0200918C->field_0e = a;
    data_0200918C->field_0f = b;
    data_0200918C->parent = parent;
    data_0200918C->unknown_04 = value;
    data_0200918C->field_1f = 12;
    data_0200918C->field_1d = 5;
    data_0200918C->field_1e = 1;
    data_0200918C->field_0a = kind;
    data_0200918C->field_16 = 0x1000;
    data_0200918C->field_18 = 0x8000;
    data_0200918C->field_1a = c;
    data_0200918C->field_11 = d;
    data_0200918C->field_12 = e;
    data_0200918C->tile_ptr = data_0200918C->parent->tiles + e * 32;
    data_0200918C->unknown_0b = 1;
    data_0200918C->field_20 = 1;
    data_0200918C->field_28 = 1;
    data_0200918C->field_1c = func_080C9540(0x252);
    result = func_08018028(data_0200918C, kind, entry_ptr, flag);
    if (flag[0])
        flag_ptr = flag;
    func_08011CD0(result, flag_ptr, *entry_ptr);
    data_0200918C->state = 0;
}
