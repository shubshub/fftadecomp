#include "ffta.h"

typedef struct {
    u8 *buffer;
    u32 source;
    u16 format;
    u16 size;
    u8 width;
    u8 height;
    u16 byte_count;
    u16 field_10;
    u16 unknown_12;
    u32 field_14;
    s16 x;
    s16 y;
    u8 field_1C;
    u8 unknown_1D;
    u16 field_1E;
    u16 field_20;
    u8 unknown_22[6];
} Record02009000;

extern Record02009000 g_records_02009000[];
extern void *data_02008FF8;

void func_0800C1C8(u8 index);
void func_08007170(void *owner, u8 *object);
void *func_08007138(void *owner, u32 bytes);

/* Complete target: [0x0800AFAC, 0x0800B0AC), 256 bytes. */
u32 func_0800AFAC(u32 source, u32 format_arg, u32 size_arg, u32 index_arg,
                  u32 field_14)
{
    u16 format = format_arg;
    u16 size = size_arg;
    u8 index = index_arg;
    Record02009000 *record;

    func_0800C1C8(index);
    if (size == 0xC000) {
        func_0800C1C8(1);
    }

    record = &g_records_02009000[index];
    record->format = format;
    record->size = size;
    if (format == 0) {
        switch (size) {
        case 0:
            record->width = 32;
            record->height = 32;
            break;
        case 0x4000:
            record->width = 64;
            record->height = 32;
            break;
        case 0x8000:
            record->width = 32;
            record->height = 64;
            break;
        case 0xC000:
            record->width = 64;
            record->height = 64;
            break;
        }
        record->byte_count = record->width * record->height * 2;
    } else {
        switch (size) {
        case 0:
            record->width = 16;
            record->height = 16;
            break;
        case 0x4000:
            record->width = 32;
            record->height = 32;
            break;
        case 0x8000:
            record->width = 64;
            record->height = 64;
            break;
        }
        record->byte_count = record->width * record->height;
    }
    record->field_14 = field_14;
    record->source = source;
    if (record->buffer != 0) {
        func_08007170(data_02008FF8, record->buffer);
    }
    record->buffer = func_08007138(data_02008FF8, record->byte_count);
    record->field_10 = 0;
    record->x = 0;
    record->y = 0;
    record->field_1C = 0xFF;
    record->field_1E = 0;
    record->field_20 = 0;
    return 1;
}
