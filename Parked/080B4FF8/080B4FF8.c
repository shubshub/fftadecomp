typedef unsigned char u8;
typedef unsigned short u16;

struct PaletteAnimation {
    u8 unknown_00[0x45];
    u8 directions[16];
};

extern u16 data_03003A64[];

/* Target: 080B4FF8..080B50EE, 246 bytes. */
void func_080B4FF8(struct PaletteAnimation *animation, int palette)
{
    u16 *colors = data_03003A64 + palette * 16;
    int i;

    for (i = 2; i <= 15; i++) {
        u8 *direction = &animation->directions[i];
        u16 red = colors[i - 2] & 0x1F;
        u16 green = (colors[i - 2] & 0x3E0) >> 5;
        u16 blue = (colors[i - 2] & 0x7C00) >> 10;

        if (*direction & 1) {
            red++;
            if (red > 31) {
                red = 30;
                *direction &= ~1;
            }
        } else if (red <= 15) {
            red++;
            *direction |= 1;
        } else {
            red--;
        }

        if (*direction & 2) {
            green++;
            if (green > 31) {
                green = 30;
                *direction &= ~2;
            }
        } else if (green <= 15) {
            green++;
            *direction |= 2;
        } else {
            green--;
        }

        if (*direction & 4) {
            blue++;
            if (blue > 31) {
                blue = 30;
                *direction &= ~4;
            }
        } else if (blue <= 15) {
            blue++;
            *direction |= 4;
        } else {
            blue--;
        }

        colors[i - 2] = red | (green << 5) | (blue << 10);
    }
}
