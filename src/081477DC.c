/* Convert a packed RGB555 color to weighted grayscale. Target: 82 bytes. */
typedef unsigned short u16;

u16 func_081477DC(u16 color)
{
    u16 red = color & 0x1f;
    u16 green = (color & 0x3e0) >> 5;
    u16 blue = (color & 0x7c00) >> 10;
    u16 gray;
    int weighted_blue;

    red *= 30;
    green *= 59;
    weighted_blue = blue * 11;
    gray = (red + green + weighted_blue) / 100;
    return gray | (gray << 5) | (gray << 10);
}
