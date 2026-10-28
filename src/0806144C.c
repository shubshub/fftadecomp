/* Target: 80 bytes / 31 instructions, 0x0806144C..0x0806149C. */
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u8 unknown_00[0x14];
    u16 *tilemap;
} DisplayState;

extern DisplayState data_030008B0;
extern void func_08016A98(u16 *destination, u8 width, u8 height,
                           u16 value, u16 stride);

void func_0806144C(u8 enabled)
{
    u16 *destination;

    if (enabled) {
        destination = data_030008B0.tilemap + 0x58;
        func_08016A98(destination, 3, 2, 0, 32);
    } else {
        destination = data_030008B0.tilemap + 0x153;
        func_08016A98(destination, 5, 2, 0, 32);
    }
}
