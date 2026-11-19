#include "ffta.h"

typedef struct Owner0805C594 Owner0805C594;
typedef struct Object0805C594 Object0805C594;
typedef void (*BufferInitializer)(void *destination, u32 size);

typedef struct {
    u8 *heap;
    Owner0805C594 *owner;
    void *items[2];
    Object0805C594 *objects[2];
    u8 buffer[0x2000];
    u8 count;
    u8 from_roster;
    u8 field_201A[2];
    u8 unknown_201C[2];
    u8 members[2];
    u8 field_2020[2];
    u8 field_2022[2];
    u8 field_2024[2];
    u8 field_2026[2];
    u8 field_2028[2];
    u8 field_202A[2];
    u8 unknown_202C[4];
    s16 x[2];
    s16 y[2];
} State0805C594;

typedef struct {
    u8 count;
    const u8 *members;
} MemberChoices;

/* The 16-byte roster record at 0x02002E78, laid out as src/080CC510.c has it. */
typedef struct __attribute__((packed)) {
    u32 name;
    u8 unknown_04;
    u8 appearance;
    u8 field_06;
    u8 identifier;
    u16 field_08;
    u16 field_0A;
    u16 field_0C;
    u16 field_0E;
} UnitRecord;

typedef struct {
    u8 unknown_0000[0x2E78];
    UnitRecord records[256];
} GameState;

typedef struct {
    u8 unknown_0000[0xCD8];
    Table runner;
} MenuContext0805C594;

extern State0805C594 *data_0200F42C;
extern MenuContext0805C594 *data_0200F428;
extern GameState g_state_02000000;
extern const MemberChoices data_0839383C[];
extern const u8 data_0839387C[][2];
extern const u8 data_08393880[];
extern BufferInitializer const g_callbacks_0836D4B8[];

extern void *func_08022840(u32 size);
extern void func_08022854(void *allocation);
extern u32 func_08002804(void);
extern u8 func_080CCB94(void);
extern u8 func_080CCB08(u8 index);
extern u32 func_080CCB28(u8 index);
extern void func_0805CF3C(u8 first, u8 second, s16 *sum, s16 *difference);
extern u8 *func_080070C8(u8 *storage, u32 byte_count);
extern Owner0805C594 *func_08021A3C(void *, u16, u16, u16, u16);
extern Object0805C594 *func_08021B1C(Owner0805C594 *);
extern void func_08021BD4(Object0805C594 *, void *);
extern void *func_08021618(Object0805C594 *, void *, u32, u32, u32, u32, u32);
extern void func_08021DF8(Object0805C594 *, u16, u16);
extern void func_08021E7C(Owner0805C594 *);
extern void func_0805CA7C(u8 index);
extern void func_08021F18(Object0805C594 *, s32, s32, u8, u8, u8, u8, u8, u8, u8);
extern void func_08001F34(const u8 *source, s32 x, s32 y, u8 variant,
                          u8 flip_x, u8 flip_y, u8 flag_28, u8 flag_29,
                          u32 value, u8 mode, const void *transform);
extern void func_08006B8C(Table *, u8);

/* Complete [0x0805C594, 0x0805CA7C): 1256 bytes, 520 instructions. */
void func_0805C594(u8 index, u8 *phase)
{
    u8 i;
    u8 found;
    u8 candidates[20];

    switch (*phase) {
    case 0:
        data_0200F42C = func_08022840(sizeof(State0805C594));
        g_callbacks_0836D4B8[0](data_0200F42C, sizeof(State0805C594));
        data_0200F42C->count = (s16)func_08002804() % 2 + 1;
        if (func_080CCB94() == 0) {
            data_0200F42C->from_roster = 0;
            for (i = 0; i < data_0200F42C->count; i++) {
                data_0200F42C->field_201A[i] = 20;
                data_0200F42C->members[i] = data_0839383C[i].members[
                    (s16)func_08002804() % data_0839383C[i].count];
            }
        } else {
            data_0200F42C->from_roster = 1;
            for (i = 0, found = 0; i < 20; i++) {
                if (g_state_02000000.records[i].name != 0) {
                    candidates[found] = i;
                    found++;
                }
            }
            /* The clamped count is held in r6, the loop counter's register,
             * from 0x0805C6CC to the remainder call at 0x0805C6DC. */
            i = found > 2 ? 2 : found;
            data_0200F42C->count = (s16)func_08002804() % i + 1;
            i = 0;
            do {
                u8 pick = (s16)func_08002804() % found;

                if (candidates[pick] != 0xFF) {
                    data_0200F42C->members[i] = candidates[pick];
                    candidates[pick] = 0xFF;
                    i++;
                }
            } while (data_0200F42C->count != i);
        }
        for (i = 0; i < data_0200F42C->count; i++) {
            data_0200F42C->field_2020[i] = func_080CCB08(data_0200F42C->members[i]);
            data_0200F42C->field_2022[i] = func_080CCB28(data_0200F42C->members[i]);
        }
        *phase = 1;
        break;
    case 1:
        for (i = 0; i < data_0200F42C->count; i++) {
            data_0200F42C->field_2028[i] = data_0839387C[i][0];
            data_0200F42C->field_202A[i] = data_0839387C[i][1];
            func_0805CF3C(data_0200F42C->field_2028[i], data_0200F42C->field_202A[i],
                          &data_0200F42C->x[i], &data_0200F42C->y[i]);
            data_0200F42C->field_2026[i] = (s16)func_08002804() % 4;
            data_0200F42C->field_2024[i] = 0;
        }
        data_0200F42C->heap = func_080070C8(data_0200F42C->buffer,
                                            sizeof(data_0200F42C->buffer));
        data_0200F42C->owner = func_08021A3C(data_0200F42C->heap, 736, 799, 0, 0);
        g_callbacks_0836D4B8[0](data_0200F42C->items, sizeof(data_0200F42C->items));
        for (i = 0; i < data_0200F42C->count; i++) {
            data_0200F42C->objects[i] = func_08021B1C(data_0200F42C->owner);
            if (data_0200F42C->items[i] != 0)
                func_08021BD4(data_0200F42C->objects[i], data_0200F42C->items[i]);
            data_0200F42C->items[i] = func_08021618(data_0200F42C->objects[i], 0, 0, 20,
                                                    data_0200F42C->field_2020[i],
                                                    data_0200F42C->field_2026[i] + 4, 0);
            func_08021DF8(data_0200F42C->objects[i], 0, 2);
        }
        *phase = 2;
        break;
    case 2:
        func_08021E7C(data_0200F42C->owner);
        for (i = 0; i < data_0200F42C->count; i++) {
            if (data_0200F42C->from_roster != 0)
                data_0200F42C->field_201A[i] =
                    (g_state_02000000.records[data_0200F42C->members[i]].identifier >> 1) + 20;
            func_0805CA7C(i);
            func_08021F18(data_0200F42C->objects[i], data_0200F42C->x[i],
                          data_0200F42C->y[i], 0, 0, 0, 0, 0,
                          data_0200F42C->field_2022[i], 1);
            func_08001F34(data_08393880, data_0200F42C->x[i], data_0200F42C->y[i],
                          0, 0, 0, 1, 0, 0, 0, 0);
        }
        break;
    case 0xFF:
        if (data_0200F42C != 0) {
            func_08022854(data_0200F42C);
            data_0200F42C = 0;
        }
        func_08006B8C(&data_0200F428->runner, index);
        break;
    }
}
