typedef unsigned char u8;

struct Unit;
struct Collection;

struct Owner {
    struct Unit *unit;
    u8 unknown_04[0x7C];
    struct Collection *collection;
};

extern u8 data_030028A0;
extern u8 func_080C95A8(int mode);
extern u8 func_0809AA10(struct Owner *owner);
extern u8 func_08133BC4(struct Unit *unit);
extern struct Owner *func_080970E8(struct Collection *collection, struct Unit *unit);

/* Target: 080C1B2C..080C1B8C, 96 bytes. */
int func_080C1B2C(struct Owner *owner)
{
    struct Owner *related;

    if (!func_080C95A8(13) || func_0809AA10(owner))
        return 0;

    if (func_08133BC4(owner->unit))
        return 1;

    related = func_080970E8(owner->collection, owner->unit);
    if (related != 0) {
        if (func_0809AA10(related))
            return 0;
        return 1;
    }

    if (data_030028A0 & 8)
        return 1;
    return 0;
}
