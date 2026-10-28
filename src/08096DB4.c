typedef unsigned char u8;
typedef unsigned int u32;

typedef struct {
    u8 unknown_00[0xD0];
    u32 flags;
} FlagState;

extern FlagState *data_0200F4A8;

/* 0x08096DB4..0x08096DCC: 24 bytes, 9 instructions. */
void func_08096DB4(void)
{
    data_0200F4A8->flags |= 0x8800;
}
