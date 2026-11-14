#include "ffta.h"

typedef struct Owner0802995C Owner0802995C;
typedef struct Object0802995C Object0802995C;
typedef void (*BufferInitializer)(void *destination, u32 size);

typedef struct {
    u8 unknown_00[0x10];
    u8 x;
    u8 y;
    u8 unknown_12[0x62];
    u8 *storage;
    Owner0802995C *owner;
    void *item;
    Object0802995C *object;
    u8 buffer[0x1000];
    u8 unknown_1084;
    u8 unknown_1085;
    u8 unknown_1086;
    u8 unknown_1087;
    u8 unknown_1088;
    u8 unknown_1089;
    u8 unknown_108A;
    u8 unknown_108B;
} State0802995C;

extern const u8 data_0839169C[];
extern const u8 data_083916AA[];
extern u8 data_0200F43C;
extern BufferInitializer const g_callbacks_0836D4B8[];

extern u8 func_08017180(void *region);
extern void func_08017508(void *window, u8 appearance);
extern u8 *func_080070C8(u8 *storage, u32 byte_count);
extern Owner0802995C *func_08021A3C(void *, u16, u16, u16, u16);
extern Object0802995C *func_08021B1C(Owner0802995C *);
extern void func_08021BD4(Object0802995C *, void *);
extern void *func_08021618(Object0802995C *, void *, u32, u32, u32, u32, u32);
extern void func_08021E28(void *item, u32 value);
extern void func_08021DF8(Object0802995C *, u16, u16);
extern void func_08021E7C(Owner0802995C *);
extern u16 func_08021054(u32 index);
extern void func_08021F18(Object0802995C *, s32, s32, u8, u8, u8, u8, u8, u8, u8);
extern void func_08001F34(const u8 *source, s32 x, s32 y, u8 variant,
                          u8 flip_x, u8 flip_y, u8 flag_28, u8 flag_29,
                          u32 value, u8 mode, const void *transform);
extern void func_08029D48(u8 x, u8 y, u8 value, u8 mode);

/* Complete [0x0802995C, 0x08029C34): 728 bytes, 281 instructions. */
u8 func_0802995C(State0802995C *state)
{
    u8 offset;

    switch (state->unknown_1089) {
    case 0:
        if (!func_08017180(state))
            break;
        state->storage = func_080070C8(state->buffer, sizeof(state->buffer));
        state->owner = func_08021A3C(state->storage, 704, 725, 0, 0);
        g_callbacks_0836D4B8[0](&state->item, 4);
        state->object = func_08021B1C(state->owner);
        if (state->item != 0)
            func_08021BD4(state->object, state->item);
        state->item = func_08021618(state->object, 0, 0, 20,
                                    state->unknown_1085, state->unknown_1086, 0);
        if (state->unknown_1088 == 1) {
            func_08021DF8(state->object, 0, 2);
            state->unknown_1088 = 3;
        } else if (state->unknown_1088 == 0) {
            func_08021E28(state->item, 1);
            func_08021DF8(state->object, 2, 0x100);
            state->unknown_1088 = 3;
        } else if (state->unknown_1088 == 4) {
            func_08021DF8(state->object, 2, 1);
        }
        offset = state->unknown_108B - 7;
        func_08029D48(state->x, (u8)(offset + state->y), state->unknown_108A, 13);
        state->unknown_1089 = 1;
        data_0200F43C = 0;
        break;
    case 1: {
        s8 d;
        s32 px;
        s32 py;

        if (state->unknown_1088 == 1) {
            func_08021DF8(state->object, 0, 2);
            state->unknown_1088 = 3;
        } else if (state->unknown_1088 == 0) {
            func_08021E28(state->item, 1);
            func_08021DF8(state->object, 2, 0x100);
            state->unknown_1088 = 3;
        } else if (state->unknown_1088 == 4) {
            func_08021DF8(state->object, 2, 1);
        }
        func_08021E7C(state->owner);
        d = state->unknown_108B - 7;
        px = state->x * 8 + 24;
        py = (state->y + d) * 8 + 36 - d * 4;
        if (state->unknown_1084 == 2) {
            if (func_08021054(state->unknown_1085) == 16)
                func_08001F34(data_0839169C, px, py, 0, 0, 0, 1, 0, 0, 0, 0);
            else
                func_08001F34(data_083916AA, px, py, 0, 0, 0, 1, 0, 0, 0, 0);
        } else {
            func_08021F18(state->object, px, py, 0, 0, 0, 0, 0,
                          state->unknown_1087, 0);
            if (state->unknown_1084 == 1 && state->unknown_1086 != 0
                && state->unknown_1086 != 12 && state->unknown_1086 != 16) {
                if (func_08021054(state->unknown_1085) == 16)
                    func_08001F34(data_0839169C, px, py, 0, 0, 0, 1, 0, 0, 0, 0);
                else
                    func_08001F34(data_083916AA, px, py, 0, 0, 0, 1, 0, 0, 0, 0);
            }
        }
        break;
    }
    case 2:
        func_08017508(state, 1);
        state->unknown_1089 = 3;
        break;
    case 3:
        if (func_08017180(state))
            state->unknown_1089 = 4;
        break;
    case 4:
        break;
    }
    return state->unknown_1089;
}
