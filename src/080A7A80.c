#include "ffta.h"

/* 0x080A7A80..0x080A7C9C: 540 bytes, 252 instructions, including both
 * literal words (0x000026BD at 0x080A7AF0, g_table_08526680 at 0x080A7C98). */
typedef struct {
    u8 unknown_00[6];
    u8 race;
    u8 unknown_07[0x39];
    u8 ability_points[0xB6];
} Unit;

typedef struct {
    Unit *unit;
} Object;

typedef struct {
    Object *object;
    u8 unknown_04[8];
    u16 flags;
    u16 kind;
    u8 unknown_10[0x1C];
} Child;

typedef struct {
    Object *object;
    u8 unknown_04[0xC];
    u16 item;
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
    Object *object;
    u16 kind;
    u16 amount;
    u32 data;
} OutputEntry;

typedef struct {
    OutputEntry entries[16];
    u8 unknown_C0;
    u8 count;
} OutputList;

typedef struct {
    u8 unknown_00[7];
    u8 required_points;
} Ability;

extern const u32 g_table_08526680[];

extern u8 func_080A780C(OutputEntry *result, Group *source, Child *target, u8 mode);
extern u32 func_080CCD50(u16 index, u8 selector);
extern u8 func_080C8280(const void *object);
extern u8 func_080CD50C(Unit *unit);
extern u8 func_080C8240(void *data);
extern u16 func_081340F8(const Unit *object, u16 key);
extern const Ability *func_080CD480(u8 race, u8 ability);
extern u32 func_0812EDF0(const void *object);
extern s32 func_080CA7A4(u16 entry, u8 selector);

/* An inlined copy of func_080A880C (src/080A880C.c). */
static inline void *inlined_080A880C(void *record)
{
    return record;
}

/* An inlined copy of func_080A8810 (src/080A8810.c). */
static inline Child *inlined_080A8810(Group *group, s32 index)
{
    if (group->child_count < index)
        return 0;
    return &group->children[index];
}

void func_080A7A80(GroupList *source, OutputList *output)
{
    s32 group_count = source->count;
    s32 group_index;
    s32 child_count;
    s32 child_index;

    for (group_index = 0; group_index < group_count; ++group_index) {
        Group *group = &source->groups[group_index];
        Group *record = inlined_080A880C(group);

        if (record->item == 0x146 || record->item == 0x15A) {
            if (func_080A780C(&output->entries[output->count], record, 0, 0))
                ++output->count;
            continue;
        }

        child_count = group->child_count;
        for (child_index = 0; child_index < child_count; ++child_index) {
            Child *child = inlined_080A8810(group, child_index);

            if (child->kind == 6) {
                if (func_080A780C(&output->entries[output->count], record, child, 2))
                    ++output->count;
            }

            if (child->flags & 0x80) {
                OutputEntry *entry;

                if (func_080CCD50(record->item, 0x16)) {
                    u8 state = func_080C8280(child->object->unit);
                    u8 category = func_080CD50C(child->object->unit);

                    if (state == 0 && category == 12 &&
                        func_080C8240(record->object->unit) !=
                        func_080C8240(child->object->unit)) {
                        u16 ability = func_081340F8(child->object->unit, record->item);
                        u8 points = child->object->unit->ability_points[ability] & 0x7F;

                        if (points < func_080CD480(child->object->unit->race,
                                                   (u8)ability)->required_points) {
                            child->object->unit->ability_points[ability] = 0xE4;
                            if (func_080A780C(&output->entries[output->count],
                                               record, child, 1))
                                ++output->count;
                        }
                    }
                }

                entry = &output->entries[output->count];
                if (func_080A780C(entry, record, child, 0)) {
                    ++output->count;
                    if (entry->kind == 10) {
                        u16 identifier;

                        entry = &output->entries[output->count];
                        identifier = func_0812EDF0(child->object->unit);
                        entry->kind = 0x2A;
                        entry->object = 0;
                        entry->amount = 0;
                        entry->data = g_table_08526680[func_080CA7A4(identifier, 0)];
                        ++output->count;
                    }
                }
            }
        }
    }
}
