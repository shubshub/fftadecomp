#include "ffta.h"

/* Complete target [0x081386BC, 0x08138A3C), 896 bytes, 368 instructions. */

typedef struct {
    u8 unknown_00[0x11];
    u8 flags;
    u8 unknown_12[8];
    u8 unknown_1a[0x14];
    u8 unknown_2e;
    u8 unknown_2f;
    u16 unknown_30_low : 10;
    u16 unknown_30_high : 6;
    u8 unknown_32[0x20];
    u8 unknown_52[0x22];
    u16 unknown_74;
    u16 unknown_76;
} Record081386BC;

extern u8 *data_030027D8;
extern const u8 *const data_085668B0[];

extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_08015110(void *context, void *destination, const u8 *text,
                          u8 mode, u8 reset);
/* As src/08025B54.c declares it: the callee narrows r1 with lsls/lsrs #16
 * (0x080142E6). */
extern void func_080142DC(void *destination, u16 value, u32 digits);
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern void func_0808B7C0(u32 index, u16 *destination, u16 tile, u16 count,
                          u16 flags);
extern void func_08035678(u16 value, u16 *destination, u32 count, u16 step);
extern void func_08035A68(u16 *destination, u32 digits, u32 value,
                          u16 attributes);

void func_081386BC(u32 index, Record081386BC *record, u8 *tiles, u32 present,
                   u16 mode, u16 empty_mode)
{
    u8 buffer[32];
    u16 zero;
    s32 value;
    s32 offset;
    u32 one_digit;
    const u8 *text;

    zero = 0;
    func_0814186C(&zero, tiles, 0x01000600);
    if (present) {
        /* Every string pointer is loaded before the text context
         * (0x081386F2, 0x08138766, 0x081387FA, 0x08138816, 0x08138A04). */
        text = record->unknown_1a;
        func_08015110(data_030027D8 + 0xF9C, tiles, text, mode, 1);

        value = record->unknown_30_high;
        if (value > 9) {
            offset = 0;
            func_080142DC(buffer, value, 2);
        } else {
            offset = 1;
            func_080142DC(buffer, value, 1);
        }
        func_08015110(data_030027D8 + 0xF9C, tiles + (offset + 17) * 64,
                      buffer, mode, 1);
        text = data_085668B0[56];
        func_08015110(data_030027D8 + 0xF9C, tiles + 19 * 64, text, mode, 1);

        if (record->unknown_30_high <= 9)
            one_digit = 1;
        else
            one_digit = 0;
        value = record->unknown_30_low;
        if (value > 99) {
            offset = 0;
            func_080142DC(buffer, value, 3);
        } else if (value > 9) {
            offset = 1;
            func_080142DC(buffer, value, 2);
        } else {
            offset = 2;
            func_080142DC(buffer, value, 1);
        }
        func_08015110(data_030027D8 + 0xF9C,
                      tiles + (offset + 11 + one_digit) * 64, buffer, mode, 1);
        text = data_085668B0[55];
        func_08015110(data_030027D8 + 0xF9C, tiles + (one_digit + 14) * 64,
                      text, mode, 1);
        text = record->unknown_52;
        func_08015110(data_030027D8 + 0xF9C, tiles + 22 * 64, text, mode, 1);

        if (!(record->flags & 2)) {
            value = record->unknown_76;
            if (value > 99)
                func_080142DC(buffer, value, 3);
            else if (value > 9)
                func_080142DC(buffer, value, 2);
            else
                func_080142DC(buffer, value, 1);
            func_08015110(data_030027D8 + 0xF9C, tiles + 33 * 64, buffer,
                          mode, 1);
        } else {
            func_0808B7C0(index, func_0808B8E4(index, 1, 8, 11), 0x1A5, 3,
                          0xE000);
        }

        if (mode == 1) {
            func_08035678(0x905E, func_0808B8E4(index, 1, 0, 2), 2, 1);
            func_08035678(0x905E, func_0808B8E4(index, 1, 0, 7), 2, 1);
            value = record->unknown_2e;
            func_08035A68(func_0808B8E4(index, 1, 2, 2), 2, value, 0x9000);
            value = record->unknown_74;
            func_08035A68(func_0808B8E4(index, 1, 2, 7), 2, value, 0x9000);
        } else {
            func_08035678(0xF05E, func_0808B8E4(index, 1, 0, 2), 2, 1);
            func_08035678(0xF05E, func_0808B8E4(index, 1, 0, 7), 2, 1);
            value = record->unknown_2e;
            func_08035A68(func_0808B8E4(index, 1, 2, 2), 2, value, 0xF000);
            value = record->unknown_74;
            func_08035A68(func_0808B8E4(index, 1, 2, 7), 2, value, 0xF000);
        }
        func_08035678(0xD177, func_0808B8E4(index, 1, 3, 11), 5, 1);
        func_08035678(0xD17C, func_0808B8E4(index, 1, 3, 12), 5, 1);
        if (record->flags & 1)
            *func_0808B8E4(index, 1, 5, 2) = 0xD090;
    } else {
        text = data_085668B0[57];
        func_08015110(data_030027D8 + 0xF9C, tiles, text, empty_mode, 1);
    }
}
