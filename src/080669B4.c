#include "ffta.h"

/* Complete target 0x080669B4..0x08066A8C, 216 bytes, 88 instructions
 * (the 0x01000020 pool word at 0x08066A88 belongs to this function).
 * Addressed unsigned runtime calls and a halfword BIOS fill source, as in
 * func_0804F28C. */
typedef struct {
    u8 unknown_00[0xE];
    u8 value;
} Value080669B4;

typedef struct {
    Value080669B4 *input;
    u8 unknown_04[4];
    u8 mode;
} Display080669B4;

extern u8 data_02003CB0[];
extern const u8 data_083A9CA4[];
extern u8 data_06012840[];
extern u32 func_08005318(const void *resource, void *destination,
                        u16 first, u16 count);
extern u32 func_08142AB0(u32 value, u32 divisor);
extern u32 func_08142B28(u32 value, u32 divisor);
extern void func_0814186C(const void *source, void *destination, u32 control);

static inline void copy_digit(const u8 *tiles, u8 digit, u8 *destination)
{
    func_0814186C(tiles + 0x240 + (digit << 6), destination, 0x20);
}

void func_080669B4(Display080669B4 *display)
{
    u8 *tiles = data_02003CB0;
    u8 *destination;
    u8 value;
    u32 maximum;
    u8 tens;
    u16 blank;

    func_08005318(data_083A9CA4, tiles, 0, 0);
    maximum = display->mode == 5 ? 64 : 20;
    destination = data_06012840;
    value = display->input->value;
    tens = (u8)func_08142AB0(value, 10);
    if (tens != 0) {
        copy_digit(tiles, tens, destination);
    } else {
        blank = 0;
        func_0814186C(&blank, destination, 0x01000020);
    }
    destination += 0x40;
    copy_digit(tiles, (u8)func_08142B28(value, 10), destination);
    destination += 0x40;
    func_0814186C(tiles + 0x7E0, destination, 0x10);
    destination += 0x20;
    copy_digit(tiles, (u8)func_08142AB0(maximum, 10), destination);
    destination += 0x40;
    copy_digit(tiles, (u8)func_08142B28(maximum, 10), destination);
}
