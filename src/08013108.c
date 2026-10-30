typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct Context {
    u8 unknown_00[0xB];
    u8 flags_0B;
    u16 flags_0C;
    u8 unknown_0E[0x1D];
    u8 flags_2B;
    u32 selection;
    u32 value;
    u8 unknown_34[6];
    u16 flags_3A;
    u8 unknown_3C[0x718];
    void *resource;
};

extern struct Context *data_0200918C;
extern void *func_080CB968(u8 key);

/* Complete [0x08013108, 0x080131A4): 156 bytes, including literal pools. */
void func_08013108(u8 key, u8 selection, u8 enabled, u32 value)
{
    data_0200918C->flags_3A &= 0xFF7F;
    data_0200918C->selection = (key << 8) | selection;
    data_0200918C->value = value;
    data_0200918C->resource = func_080CB968(key);
    if (enabled) {
        data_0200918C->flags_2B &= 0xFE;
        data_0200918C->flags_2B |= 2;
        data_0200918C->flags_0C |= 0x10;
        data_0200918C->flags_0B |= 2;
    } else {
        data_0200918C->flags_2B &= 0xFD;
        data_0200918C->flags_2B |= 1;
        data_0200918C->flags_0C &= 0xFFEF;
        data_0200918C->flags_0B &= 0xFD;
    }
}
