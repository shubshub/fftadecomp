#include "ffta.h"

/* Complete target [0x08084DA0, 0x08085370): 1488 bytes, 594 instructions. */

typedef struct {
    u32 field_00;
    u32 field_04;
    u32 field_08;
    u32 field_0C;
    u8 field_10;
    u8 field_11;
    u8 field_12;
    u8 field_13;
    u16 field_14;
    u8 field_16;
    u8 field_17;
    u16 field_18;
    u16 field_1A;
    u8 field_1C;
    u8 field_1D;
    u8 field_1E;
    u8 field_1F;
    u16 field_20;
    u16 field_22;
    u16 field_24;
    u16 field_26;
    u16 field_28;
    u16 field_2A;
} State08017424;

typedef struct {
    u8 x;
    u8 y;
    u8 width;
    u8 height;
    u32 unknown_04;
    u16 flags;
    u8 mode;
    u8 unknown_0B;
} Descriptor08084DA0;

typedef struct {
    u8 unknown_00[8];
    u16 index;
    u8 unknown_0A[10];
} Entry08084DA0;

typedef struct {
    s32 count;
    u32 *values;
    u8 unknown_08[4];
    Descriptor08084DA0 descriptor;
    Entry08084DA0 *entries;
} Table08084DA0;

typedef struct {
    u8 unknown_00[8];
    u16 *destination;
    u8 unknown_0C[9];
    u8 width;
    u8 rows;
    u8 unknown_17[7];
    u8 destination_stride;
    u8 unknown_1F;
} List08084DA0;

typedef struct {
    u8 unknown_00[0x11];
    u8 row;
    u8 unknown_12[2];
} Cursor08084DA0;

typedef struct {
    State08017424 panel;
    List08084DA0 list;
    Cursor08084DA0 cursor;
    u8 settings[0x14];
} Menu08084DA0;

typedef struct {
    u8 unknown_00[0x14];
    u32 field_14;
    u8 unknown_18[0x14];
    u32 field_2C;
    u16 object_id;
    u8 state;
    u8 unknown_33[3];
    u8 cancel;
    u8 unknown_37;
    u16 value;
    u8 flag;
    u8 unknown_3B[0xD];
    Table08084DA0 *table;
    Menu08084DA0 menu;
    u8 unknown_C0[4];
    u32 *output;
    u8 unknown_C8[4];
} Record08084DA0;

typedef struct {
    u8 unknown_0000[0x42A];
    u8 unknown_042A;
    u8 delay;
    u8 unknown_042C[0xE];
    u8 unknown_043A;
    u8 unknown_043B;
    u8 unknown_043C[0x7D0];
    u16 unknown_0C0C;
    u8 unknown_0C0E[0x10F6];
    u8 unknown_1D04;
    u8 unknown_1D05[0xF83];
    Record08084DA0 records[0];
} State08084DA0;

typedef struct {
    u8 unknown_00[0x28];
    u8 field_28;
    u8 unknown_29[0x23];
} Resource08084DA0;

typedef struct {
    u16 held;
    u16 pressed;
    u16 repeated;
} InputState;

extern State08084DA0 *data_03002818;
extern Resource08084DA0 data_030009E0[];
extern InputState data_03000000;
extern u8 data_02003CB0[];
extern u8 data_03000990[];
extern u8 data_03000E80[];

extern u8 func_080846B0(u32 index, u16 mask);
/* The ROM tests the whole return register (cmp r0, #0 at 0x080850A8 and
   0x080850E6, no narrowing), so the result is a full word here. */
extern s32 func_08084C98(s32 index, u32 refresh);
extern void func_080812E8(u32 context, void *control, s32 enabled);
extern void func_08017424(State08017424 *state, u32 value_00, u32 value_04,
                         u8 value_10, u8 value_11, u8 value_12, u8 value_13,
                         u16 value_14, u8 value_16, u16 value_18,
                         u16 value_1A, u8 value_17);
extern void func_08016C90(State08017424 *state, u8 mode);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern u16 func_08017B68(List08084DA0 *list, u32 row);
extern u16 func_08017B50(List08084DA0 *list);
extern void func_08017AF4(List08084DA0 *list, s8 row, u8 mode);
extern void func_08017508(State08017424 *panel, u8 mode);
extern void func_08017D18(void *control, u8 flags);
extern void func_08017E28(void *control);
extern u8 func_08017180(State08017424 *panel);
extern void func_08019A8C(void *data, u16 index, void *first, void *second);
extern u16 func_08011860(void);

/* An inlined copy of func_08085450 (src/08085450.c) that walks the output
   with a cursor; this text compiles func_08085450 byte for byte as well.
   Both inlined copies load the list (0x08084E30, 0x08084F54) before the
   output (0x08084E32, 0x08084F56); stepping the output parameter itself,
   as src/08085450.c does, loads the output first. */
static inline void inlined_08085450(u32 index, u32 *output, Table08084DA0 *list)
{
    u32 *value = output;
    u16 i;

    for (i = 0; i < list->count; i++)
        *value++ = list->values[list->entries[i].index];
}

/* An inlined copy of func_080430CC (src/080430CC.c). */
static inline void inlined_080430CC(List08084DA0 *state)
{
    u16 *destination = state->destination;
    u32 size = state->width * 2;
    s32 row;

    for (row = 0; row < state->rows * 2; row++) {
        u16 fill;
        u16 *source = &fill;
        *source = 0;
        func_0814186C(source, destination, 0x01000000 | (size >> 1));
        destination += state->destination_stride;
    }
}

/* An inlined copy of func_0808537C (src/0808537C.c). */
static inline void inlined_0808537C(u16 context, Menu08084DA0 *object, s32 enabled)
{
    func_080812E8(context, &object->cursor, enabled);
    if (enabled)
        func_080812E8(context, object->settings, enabled);
}

/* An inlined copy of func_080853A0 (src/080853A0.c). */
static inline void inlined_080853A0(u32 index, State08017424 *state,
                                    const Table08084DA0 *configuration, u8 x, u8 y)
{
    Descriptor08084DA0 descriptor = configuration->descriptor;
    u16 selection = data_03002818->records[index].object_id;
    u16 enabled;

    if (x != 0xFF) {
        descriptor.x = x;
        descriptor.y = y;
    }
    enabled = 1;
    func_08017424(state, data_03002818->records[index].field_14,
                 data_03002818->records[index].field_2C,
                 descriptor.x, descriptor.y, descriptor.width, descriptor.height,
                 descriptor.flags, data_030009E0[selection].field_28, 5, enabled, 12);
    func_08016C90(state, descriptor.mode);
}

int func_08084DA0(u32 index, u16 mask)
{
    switch (data_03002818->records[index].state) {
    case 0:
        inlined_08085450(index, data_03002818->records[index].output,
                         data_03002818->records[index].table);
        data_03002818->records[index].state = 2;
        break;
    case 2:
        data_03002818->delay += 3;
        inlined_080853A0(index, &data_03002818->records[index].menu.panel,
                         data_03002818->records[index].table, 0xFF, 0xFF);
        data_03002818->records[index].state = 3;
        break;
    case 4: {
        u16 count;
        s32 row;

        data_03002818->delay = 0;
        inlined_08085450(index, data_03002818->records[index].output,
                         data_03002818->records[index].table);
        inlined_080430CC(&data_03002818->records[index].menu.list);
        func_08084C98(index, 1);
        func_08017B68(&data_03002818->records[index].menu.list,
                      (s8)(&data_03002818->records[index].menu.cursor)->row);
        count = func_08017B50(&data_03002818->records[index].menu.list);
        for (row = 0; row < count; row++)
            func_08017AF4(&data_03002818->records[index].menu.list, row, 12);
        func_08017AF4(&data_03002818->records[index].menu.list,
                      (&data_03002818->records[index].menu.cursor)->row, 11);
        inlined_0808537C(data_03002818->records[index].object_id,
                         &data_03002818->records[index].menu, 1);
        data_03002818->records[index].state = 6;
        break;
    }
    case 3:
        if (func_08084C98(index, 0))
            func_08017AF4(&data_03002818->records[index].menu.list,
                          (&data_03002818->records[index].menu.cursor)->row, 11);
        data_03002818->records[index].state = 6;
        break;
    case 1:
        data_03002818->delay += 3;
        if (func_08084C98(index, 1))
            func_08017AF4(&data_03002818->records[index].menu.list,
                          (&data_03002818->records[index].menu.cursor)->row, 11);
        data_03002818->records[index].state = 6;
        break;
    case 6:
        data_03002818->records[index].state = func_080846B0(index, mask);
        inlined_0808537C(data_03002818->records[index].object_id,
                         &data_03002818->records[index].menu, 1);
        break;
    case 7:
        func_08017E28(data_03002818->records[index].menu.settings);
        if (!data_03002818->delay)
            inlined_0808537C(data_03002818->records[index].object_id,
                             &data_03002818->records[index].menu, 1);
        data_03002818->records[index].state = 6;
        break;
    case 8:
        data_03002818->records[index].cancel = 0xFF;
        func_08017508(&data_03002818->records[index].menu.panel, 16);
        func_08017D18(&data_03002818->records[index].menu.cursor, 0);
        func_08017D18(data_03002818->records[index].menu.settings, 0);
        data_03002818->records[index].flag = 0;
        data_03002818->records[index].state = 9;
        /* fall through: case 9's block (0x0808521A) follows this store
           (0x08085216) with no branch. */
    case 9:
        if (func_08017180(&data_03002818->records[index].menu.panel))
            data_03002818->records[index].state = 0xFF;
        break;
    case 10:
        data_03002818->unknown_042A = data_03002818->unknown_1D04;
        data_03002818->unknown_1D04 = 0;
        data_03002818->unknown_043B = data_03002818->unknown_043A;
        data_03002818->unknown_0C0C = 0;
        data_03002818->unknown_043A = 3;
        func_08019A8C(data_02003CB0, data_03002818->records[index].value,
                      data_03000990, data_03000E80);
        data_03002818->records[index].state = 11;
        break;
    case 11:
        if (func_08011860()) {
            data_03002818->delay = 10;
            data_03002818->unknown_043A = data_03002818->unknown_043B;
            data_03002818->unknown_1D04 = data_03002818->unknown_042A;
            data_03002818->records[index].state = 6;
        }
        data_03000000.held = 0;
        data_03000000.pressed = 0;
        return 11;
    /* The closed state case 9 stores (0x0808523E).  A twelfth case is what
       makes the dispatch a compare tree (0x08084DC8-0x08084E22) rather than
       a jump table; its empty body shares the exit, so its test folds into
       the branch at 0x08084E22.  The ROM does not give the value (121 and up
       all produce these bytes); 0xFF is the one this function stores, as in
       src/08135890.c and src/08043120.c. */
    case 0xFF:
        break;
    }
    return data_03002818->records[index].state;
}
