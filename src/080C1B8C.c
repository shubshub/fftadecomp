typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Unit Unit;

typedef struct {
    Unit *unit;
} Owner;

typedef struct {
    Owner *owner;
    u8 unknown_04[0x324];
} GroupEntry;

typedef struct {
    GroupEntry entries[13];
    u16 count;
} Group;

extern u8 func_080C8298(const Unit *unit);
extern u8 func_080CD50C(const Unit *unit);
extern u8 func_080C8240(const Unit *unit);
extern u8 func_080CD9BC(const Unit *unit);
extern u8 func_080CDCEC(const Unit *unit);

/* 0x080C1B8C..0x080C1C38: 172 bytes, 78 instructions. */
void func_080C1B8C(Owner *source, Group *group, Owner **candidates, int count)
{
    u8 kind;
    int i;

    if (func_080C8298(source->unit))
        kind = 14;
    else
        kind = func_080CD50C(source->unit);

    group->count = 0;
    for (i = 0; i < count; i++) {
        if ((func_080C8240(source->unit) == func_080C8240((*candidates)->unit)
             || kind == 14 || !func_080CD9BC((*candidates)->unit))
            && !func_080CDCEC((*candidates)->unit)) {
            group->entries[group->count].owner = *candidates;
            group->count++;
        }
        candidates++;
    }
}
