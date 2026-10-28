typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u8 unknown_000[0xC1C];
    u8 mode;
    u8 unknown_c1d[0x3F];
    u16 entries[6];
} MenuState;

extern MenuState *data_03002818;

/* 0x08080E80..0x08080EB8: 56 bytes, 21 instructions. */
void func_08080E80(u8 mode)
{
    int i;

    data_03002818->mode = mode;
    for (i = 0; i < 6; i++)
        data_03002818->entries[i] = 0;
}
