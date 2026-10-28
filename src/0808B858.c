typedef unsigned char u8;
typedef unsigned short u16;

struct Window {
    u8 unknown_00[0x28];
    u8 width;
    u8 unknown_29[0x23];
};

extern struct Window data_030009E0[];

void func_0808B858(int index, u16 *destination, u16 tile, u16 count)
{
    int stride = data_030009E0[index].width;
    int column;

    for (column = 0; column < count; column++, destination++) {
        *destination = tile;
        destination[stride] = tile;
    }
}
