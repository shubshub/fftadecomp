typedef unsigned char u8;
typedef unsigned short u16;

struct Appearance {
    u8 bytes[0x10];
};

struct Unit {
    u8 unknown_00[0xB];
    u8 flags;
    u8 attributes[9];
    u8 unknown_15[0x15];
    u16 values[5];
    u8 unknown_34[0xD4];
};

struct Owner {
    u8 unknown_00[0x40];
    struct Unit units[2];
    struct Appearance appearances[1];
};

struct Context {
    struct Unit *unit;
    u8 unknown_04[0x5A];
    u16 saved_values[5];
    u8 saved_bytes[10];
    u8 unknown_72[0xE];
    struct Owner *owner;
};

extern struct Appearance data_02002E78[];
extern u8 func_080C95A8(int option);
extern void func_0809906C(struct Unit *unit, struct Appearance *appearance);
extern void func_080CA2E8(struct Unit *unit);

static inline u8 owns_unit(struct Owner *owner, struct Unit *unit)
{
    int index;

    for (index = 0; index < 2; index++) {
        if (&owner->units[index] == unit)
            return 1;
    }

    return 0;
}

void func_0809915C(struct Context *context, u16 appearance)
{
    struct Appearance *table = data_02002E78;
    struct Unit *unit;
    u8 *saved;
    int index;
    u8 byte;

    if (func_080C95A8(13)) {
        if (owns_unit(context->owner, context->unit))
            table = context->owner->appearances;
    }

    func_0809906C(context->unit, &table[appearance]);

    unit = context->unit;
    saved = context->saved_bytes;
    byte = *saved;
    *saved = unit->flags;
    unit->flags = byte;

    index = 0;
    saved++;
    for (; index < 9; saved++, index++) {
        byte = *saved;

        *saved = unit->attributes[index];
        unit->attributes[index] = byte;
    }

    for (index = 0; index < 5; index++) {
        u16 value = context->saved_values[index];

        context->saved_values[index] = context->unit->values[index];
        context->unit->values[index] = value;
    }

    func_080CA2E8(context->unit);
}
