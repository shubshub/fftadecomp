#include "ffta.h"

typedef struct {
    u8 unknown_00[0x13];
    u8 field_13;
    u8 field_14;
    u8 field_15;
    u8 unknown_16;
    u8 field_17;
    s16 field_18;
} MenuList;

typedef struct MenuCursor MenuCursor;
typedef void (*CursorCallback)(MenuCursor *cursor);

struct MenuCursor {
    CursorCallback callback;
    MenuList *list;
    u16 x;
    u16 y;
    u16 field_0C;
    u16 field_0E;
    u8 flags;
    u8 field_11;
    u8 field_12;
};

typedef struct {
    u32 unknown_00;
    const void *subject;
    u16 x;
    u16 y;
    u16 counter;
    u8 unknown_0E[2];
    u8 flags;
    u8 displacement;
} DisplayState;

typedef struct {
    u8 unknown_00[0x2C];
    MenuList list;
    u8 unknown_48[0x14];
    u8 unknown_5C;
    u8 row;
    u8 unknown_5E[2];
    MenuCursor cursor;
} Object;

typedef struct {
    u8 unknown_00[0x2C];
    u8 list[0x30];
    u8 unknown_5C;
    u8 row;
    u8 unknown_5E[2];
    u8 settings[1];
} Object0806E4E0;

typedef struct {
    u8 state;
} State0806FE14;

typedef struct {
    u8 unknown_00[0x1A88];
    State0806FE14 mode;
} RootState;

extern RootState *data_0200F428;
extern u8 func_0806FE14(const State0806FE14 *object);
extern void func_08017DB4(MenuCursor *cursor, MenuList *list,
                        CursorCallback callback, u8 flags);
extern void func_08017F04(DisplayState *state);
extern void func_0806E4E0(Object0806E4E0 *object);

/* Complete target [0x0806E48C, 0x0806E4E0), 84 bytes.
 * Target: 10b5041c433000780138211c44310022895e884214da0c4800680c49401801f0b3fc0006000e04280ad1201c6030211c2c31074a0023a9f777fc201c00f00af810bc01bc0047000028f40002881a0000057f0108.
 */
void func_0806E48C(Object *object)
{
    if (object->list.field_17 - 1 < object->list.field_18 &&
        func_0806FE14(&data_0200F428->mode) == 4) {
        func_08017DB4(&object->cursor, &object->list,
                     (CursorCallback)func_08017F04, 0);
        func_0806E4E0((Object0806E4E0 *)object);
    }
}
