#include "ffta.h"

// 0x080A780C..0x080A7A80: 628 bytes, including the 19-entry switch table.

typedef struct {
    u8 unknown_00;
    u8 kind;
    u8 unknown_02;
    u8 variant;
} Record080A780C;

typedef struct {
    u32 *first;
    u32 *second;
    u32 field_08;
    u8 unknown_0c[0x24];
    const Record080A780C *record;
} State080A780C;

typedef struct {
    u8 unknown_00[0x18];
    u8 type;
    u8 unknown_19[3];
} Item080A780C;

typedef struct {
    u32 *data;
} Object080A780C;

typedef struct {
    Object080A780C *object;
    u8 unknown_04[0x0c];
    u16 item;
    u16 parameter;
} Source080A780C;

typedef struct {
    Object080A780C *object;
    u8 unknown_04[8];
    u16 flags;
    u8 unknown_0e[0x14];
    s16 value_22;
    s16 value_24;
    s16 value_26;
    u8 unknown_28[2];
    u16 entry;
} Target080A780C;

typedef struct {
    Object080A780C *object;
    u16 kind;
    u16 amount;
    u32 data;
} Result080A780C;

extern State080A780C data_0200F3F0;
extern const Item080A780C data_0855187C[];
extern const u32 g_table_08526680[];
extern const u32 g_table_085567F0[];

extern s32 func_080CA7A4(u16 entry, u8 selector);
extern u32 func_080CCD50(u16 entry, u8 selector);
extern u8 func_080C9540(u16 flag);
extern void func_0812F2A4(u16 first, u16 second, u8 kind);
extern void func_0812F34C(u32 value);
extern void func_0812F328(u8 index);

static inline s32 abs080A780C(s32 value)
{
    if (value < 0)
        value = -value;
    return value;
}

static inline void prepare080A780C(u32 *first, u32 *second)
{
    data_0200F3F0.first = first;
    data_0200F3F0.second = second;
}

u8 func_080A780C(Result080A780C *result, Source080A780C *source, Target080A780C *target, u8 mode)
{
    const Item080A780C *item;
    u16 amount;

    if (source->object == 0)
        return 0;
    if (source->item == 0)
        return 0;

    item = &data_0855187C[source->item];
    switch (mode) {
    case 1:
        result->kind = 0x12;
        result->object = target->object;
        result->amount = 0;
        result->data = g_table_085567F0[func_080CCD50(source->item, 0)];
        return 1;
    case 2:
        result->kind = 0x187;
        result->object = target->object;
        result->amount = 0;
        result->data = g_table_08526680[func_080CA7A4(target->entry, 0)];
        return 1;
    case 3:
        if (func_080C9540(0x42))
            result->kind = 0x31;
        else
            result->kind = 0x32;
        result->object = 0;
        result->amount = 0;
        result->data = 0;
        return 1;
    }

    if (item->type == 0)
        return 0;
    result->kind = item->type;
    switch (item->type) {
    case 1:
    case 8:
    case 9:
        if (target->flags & 4) {
            result->object = source->object;
            result->amount = abs080A780C(target->value_22);
            result->data = 0;
            return 1;
        }
        if (target->flags & 0x1000) {
            result->object = source->object;
            result->amount = abs080A780C(target->entry - 1);
            result->data = 0;
            return 1;
        }
        return 0;
    case 2:
    case 6:
    case 12:
    case 14:
        if (target->flags & 8) {
            result->object = source->object;
            result->amount = abs080A780C(target->value_24);
            result->data = 0;
            return 1;
        }
        if (target->flags & 0x1000) {
            result->object = source->object;
            result->amount = abs080A780C(target->entry - 1);
            result->data = 0;
            return 1;
        }
        return 0;
    case 13:
        result->object = source->object;
        result->amount = 0;
        result->data = g_table_08526680[func_080CA7A4(target->entry, 0)];
        return 1;
    case 3:
        result->object = source->object;
        result->amount = 0;
        if (target->entry == 0)
            result->kind = 0x20;
        else
            result->data = g_table_08526680[func_080CA7A4(target->entry, 0)];
        return 1;
    case 4:
    case 10:
    case 19:
        result->object = source->object;
        result->amount = 0;
        result->data = *target->object->data;
        return 1;
    case 5: {
        if (!(target->flags & 0x1000))
            return 0;
        func_0812F2A4(source->item, source->parameter, 0);
        prepare080A780C(source->object->data, target->object->data);
        amount = 0;
        func_0812F34C(0);
        func_0812F328(0);
        if (data_0200F3F0.record->variant == 8)
            goto battle;
        result->object = source->object;
        result->amount = amount;
        result->data = g_table_08526680[func_080CA7A4(target->entry, 0)];
        return 1;
    }
    case 7:
        if (target->flags & 0x2000) {
            result->object = source->object;
            result->amount = abs080A780C(target->value_26);
            result->data = 0;
            return 1;
        }
        if (target->flags & 0x1000) {
            result->object = source->object;
            result->amount = abs080A780C(target->entry - 1);
            result->data = 0;
            return 1;
        }
        return 0;
    case 16:
    case 17:
        return 1;
    case 15:
        result->object = source->object;
        result->amount = 0;
        result->data = *target->object->data;
        return 1;
    battle:
        result->object = source->object;
        result->amount = amount;
        result->data = g_table_085567F0[func_080CCD50(target->entry, 0)];
        return 1;
    }
    return 0;
}
