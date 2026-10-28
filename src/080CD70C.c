typedef unsigned char u8;
typedef unsigned short u16;

extern u8 func_080CD6A8(const void *object);

static inline u8 flag_e9_10(const void *object)
{
    const u8 *flags = (const u8 *)object + 0xE9;
    u8 mask = 0x10;

    if (*flags & mask)
        return 1;
    return 0;
}

static inline u8 flag_e9_40(const void *object)
{
    const u8 *flags = (const u8 *)object + 0xE9;
    u8 mask = 0x40;

    if (*flags & mask)
        return 1;
    return 0;
}

static inline void clear_e9_10(void *object)
{
    u8 *flags = (u8 *)object + 0xE9;
    u8 mask = 0x10;

    *flags &= ~mask;
}

static inline void clear_e9_40(void *object)
{
    u8 *flags = (u8 *)object + 0xE9;
    u8 mask = 0x40;

    *flags &= ~mask;
}

/* Target: 080CD70C..080CD774, 104 bytes. */
u8 func_080CD70C(void *object, u16 id)
{
    if (id == 0xDD || id == 0xAC)
        return 0;
    if (func_080CD6A8(object))
        return 0;

    if (flag_e9_10(object))
        clear_e9_10(object);
    if (flag_e9_40(object))
        clear_e9_40(object);
    return 1;
}
