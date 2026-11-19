#include "ffta.h"

/* Complete [0x08147830, 0x081478DC): 172 bytes, 86 instructions. */
u16 func_08147830(u16 color, u16 reference, u8 amount, u8 mode)
{
    /* The channels are unsigned: every scale is muls then lsrs #4
       (0x08147880-0x081478A2), not the asrs of a signed quotient. */
    u32 reference_red;
    u32 reference_green;
    u32 reference_blue;
    u32 color_red;
    u32 color_green;
    u32 color_blue;
    u16 scaled_reference_red;
    u16 scaled_reference_green;
    u16 scaled_reference_blue;

    /* Green and blue are each masked, then shifted, as two statements: the
       ands/lsrs pairs at 0x0814785C, 0x08147866, 0x08147872 and 0x0814787A,
       in a frame that saves r8 and sb and reserves 4 bytes
       (0x08147832-0x08147838).  The function is byte for byte the palette
       library's copy in Tactics Ogre: The Knight of Lodis (totkol
       sub_08138B00); other functions of that shared library, such as
       src/081478DC.c, extract a channel in one expression. */
    reference_red = reference & 0x1F;
    reference_green = reference & 0x3E0;
    reference_green >>= 5;
    reference_blue = reference & 0x7C00;
    reference_blue >>= 10;
    color_red = color & 0x1F;
    color_green = color & 0x3E0;
    color_green >>= 5;
    color_blue = color & 0x7C00;
    color_blue >>= 10;

    scaled_reference_red = reference_red * amount / 16;
    scaled_reference_green = reference_green * amount / 16;
    scaled_reference_blue = reference_blue * amount / 16;
    color_red = color_red * mode / 16;
    color_green = color_green * mode / 16;
    color_blue = color_blue * mode / 16;

    color_red += scaled_reference_red;
    color_green += scaled_reference_green;
    color_blue += scaled_reference_blue;
    if (color_red > 31)
        color_red = 31;
    if (color_green > 31)
        color_green = 31;
    if (color_blue > 31)
        color_blue = 31;
    return color_red | (color_green << 5) | (color_blue << 10);
}
