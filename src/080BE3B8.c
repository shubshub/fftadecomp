typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;

struct Unit {
    u8 unknown_00[0xF6];
    u8 x;
    u8 y;
};

struct Owner {
    struct Unit *unit;
};

struct Entry {
    struct Owner *owner;
    u8 unknown_04[0x324];
};

struct Group {
    struct Entry entries[13];
    u16 count;
};

struct Context {
    struct Owner *owner;
    u8 unknown_04[8];
    struct Group *groups[2];
    u8 unknown_14[0x14];
    u8 side;
};

extern int abs(int value);

/* Target: 080BE3B8..080BE494, 220 bytes. */
int func_080BE3B8(struct Context *context, s8 x, s8 y)
{
    int result = 0;
    s8 group_index;

    for (group_index = 0; group_index <= 1; group_index++) {
        struct Group *group = context->groups[group_index];
        s8 entry_index;

        for (entry_index = 0; entry_index < group->count; entry_index++) {
            struct Owner *owner = group->entries[entry_index].owner;

            if (owner != context->owner) {
                struct Unit *unit = owner->unit;
                int score = 32 - (abs(unit->x - x) + abs(unit->y - y));

                if (context->side) {
                    if (group_index != 0)
                        score = -score;
                } else if (group_index == 0) {
                    score = -score;
                }
                result += score;
            }
        }
    }

    return result;
}
