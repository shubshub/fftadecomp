#include "ffta.h"

/* 0x080A7A80..0x080A7C9C: 540 bytes. */
typedef struct {
    u8 unknown_00[6];
    u8 class_id;
    u8 unknown_07[0x39];
    u8 values[0];
} Unit;

typedef struct {
    Unit *unit;
} UnitOwner;

typedef struct {
    UnitOwner *owner;
    u8 unknown_04[8];
    u16 flags;
    u16 kind;
    u8 unknown_10[0x1C];
} Child;

typedef struct {
    UnitOwner *owner;
    u8 unknown_04[0xC];
    u16 identifier;
    u8 unknown_12[0xE];
    Child children[15];
    u8 unknown_2B4[0xC];
    u8 child_count;
    u8 unknown_2C1[3];
} Group;

typedef struct {
    Group groups[14];
    u8 unknown_26B8[5];
    u8 count;
} GroupList;

typedef struct {
    u32 reference;
    u16 kind;
    u16 flags;
    u32 payload;
} OutputEntry;

typedef struct {
    OutputEntry entries[16];
    u8 unknown_C0;
    u8 count;
} OutputList;

typedef struct {
    u8 unknown_00[7];
    u8 limit;
} ValueInfo;

u8 func_080A780C(OutputEntry *output, Group *group, Child *child, u32 mode);
u32 func_080CCD50(u16 identifier, u32 selector);
u8 func_080C8280(Unit *unit);
u8 func_080CD50C(Unit *unit);
u8 func_080C8240(Unit *unit);
u16 func_081340F8(Unit *unit, u16 identifier);
ValueInfo *func_080CD480(u8 class_id, u8 index);
u16 func_0812EDF0(Unit *unit);
u32 func_080CA7A4(u16 identifier, u32 selector);
extern const u32 g_table_08526680[];

static inline Child *get_child(Group *group, s32 index)
{
    if (group->child_count < index)
        return 0;
    return &group->children[index];
}

void func_080A7A80(GroupList *source, OutputList *output)
{
    s32 group_count = source->count;
    s32 group_index;

    for (group_index = 0; group_index < group_count; ++group_index) {
        Group *group = &source->groups[group_index];
        s32 child_count;
        s32 child_index;

        if (group->identifier == 0x146 || group->identifier == 0x15A) {
            if (func_080A780C(&output->entries[output->count], group, 0, 0))
                ++output->count;
            continue;
        }

        child_count = group->child_count;
        for (child_index = 0; child_index < child_count; ++child_index) {
            Child *child = get_child(group, child_index);

            if (child->kind == 6) {
                if (func_080A780C(&output->entries[output->count], group, child, 2))
                    ++output->count;
            }

            if (child->flags & 0x80) {
                OutputEntry *entry;

                if (func_080CCD50(group->identifier, 0x16)) {
                    u8 state = func_080C8280(child->owner->unit);
                    u8 category = func_080CD50C(child->owner->unit);

                    if (state == 0 && category == 12 &&
                        func_080C8240(group->owner->unit) !=
                        func_080C8240(child->owner->unit)) {
                        u16 index = func_081340F8(child->owner->unit, group->identifier);
                        u32 value = child->owner->unit->values[index] & 0x7F;

                        if (value < func_080CD480(child->owner->unit->class_id,
                                                 (u8)index)->limit) {
                            child->owner->unit->values[index] = 0xE4;
                            if (func_080A780C(&output->entries[output->count],
                                               group, child, 1))
                                ++output->count;
                        }
                    }
                }

                entry = &output->entries[output->count];
                if (func_080A780C(entry, group, child, 0)) {
                    ++output->count;
                    if (entry->kind == 10) {
                        u16 identifier;

                        entry = &output->entries[output->count];
                        identifier = func_0812EDF0(child->owner->unit);
                        entry->kind = 0x2A;
                        entry->reference = 0;
                        entry->flags = 0;
                        entry->payload = g_table_08526680[func_080CA7A4(identifier, 0)];
                        ++output->count;
                    }
                }
            }
        }
    }
}
