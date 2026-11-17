#include "ffta.h"

// Target: [0x08011CD0, 0x08011D9C), 204 bytes, 96 instructions.
// Copy a prefix string into the window's text buffer, expand the table
// entry after it, then size the window and rewind its text cursor.

typedef struct {
    u8 unknown_00[0x11];
    u8 height;
    u8 unknown_12[8];
    u8 base_width;
    u8 unknown_1b[0x25];
    u8 cursor;
    u8 unknown_41[0x2bf];
    u8 *pixels;
    u8 *current_pixels;
    u8 *current_data;
    u8 text[0x200];
    u8 scratch[0];
} WindowObject;

extern WindowObject *data_0200918C;
extern u16 func_08013E9C(u8 *destination, const u8 *table, u8 *workspace,
                         u16 index, u8 *status, u8 *mode);
extern u16 func_080144F4(const u8 *text, u8 mode);

void func_08011CD0(const u8 *table, const u8 *prefix, u16 entry)
{
    u8 length = 0;
    u8 lines;
    const u8 *p;

    if (prefix) {
        for (p = prefix; *p; p++)
            data_0200918C->text[length++] = *p;
    }
    func_08013E9C(&data_0200918C->text[length], table,
                  data_0200918C->scratch, entry, 0, &lines);
    if (data_0200918C->base_width == 0)
        data_0200918C->base_width = func_080144F4(data_0200918C->text, 1) >> 3;
    if (data_0200918C->height == 0 || data_0200918C->height < lines * 2)
        data_0200918C->height = lines * 2;
    data_0200918C->current_data = data_0200918C->text;
    data_0200918C->current_pixels = data_0200918C->pixels;
    data_0200918C->cursor = 0;
}
