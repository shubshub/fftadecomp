typedef unsigned char u8;
typedef unsigned short u16;

struct State {
    u8 unknown_00[0xAC];
    u8 mode;
    u8 unknown_AD;
    u8 flags;
};

struct Status {
    u8 unknown_00[2];
    u8 mode;
    u8 unknown_03[0x11D];
    u16 active;
    u16 duration;
};

extern struct State data_02015738;
extern struct Status data_030028A0;
extern int func_08004D68(void);

/* Target: 080C72F8..080C7376, 126 bytes. */
int func_080C72F8(void)
{
    if (data_02015738.flags & 0x40) {
        if (data_02015738.flags & 0x80)
            return func_08004D68() != 1;
        return 0;
    }
    if ((data_02015738.flags & 0x20) || data_02015738.mode > 13) {
        if (data_030028A0.active
            || (data_030028A0.mode != 3 && data_030028A0.duration > 16))
            return 1;
    }
    if (data_02015738.flags & 8)
        return 1;
    return 0;
}
