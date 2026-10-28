#include "ffta.h"

typedef struct Layout08013B50 {
    u16 unknown_00;
    u8 width;
    u8 height;
    u16 unknown_04;
    u16 flags;
} Layout08013B50;

extern u8 func_08013AAC(u8 width, u16 flags);
extern u8 func_08013ACC(u8 height, u16 flags);
extern u16 func_08013B08(u8 width, u8 height, u16 flags);

/* Complete [0x08013B50, 0x08013B7C): 44 bytes, 19 instructions. */
u16 func_08013B50(Layout08013B50 *layout)
{
    layout->width = func_08013AAC(layout->width, layout->flags);
    layout->height = func_08013ACC(layout->height, layout->flags);
    return func_08013B08(layout->width, layout->height, layout->flags);
}
