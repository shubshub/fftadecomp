#include "ffta.h"

/* 0x080D7674..0x080D7796: 290 bytes, 136 instructions. */
typedef struct {
    u8 kind;
    u8 flags;
} Format;

typedef struct {
    const Format *format;
    u8 color;
    u8 palette;
} Descriptor;

typedef struct {
    u8 kind;
    u8 unknown_01;
    u16 size;
    const Descriptor *descriptor;
    u32 unknown_08;
} TransferEntry;

typedef struct {
    const TransferEntry *entries;
    u8 unknown_04[3];
    u8 index;
    u8 unknown_08[8];
    u16 chunk;
    u8 unknown_12[2];
    u32 remaining;
    const u8 *source;
    u8 *destination;
} Transfer;

extern void func_080D702C(const u8 *source, u16 count, u8 *destination, u8 foreground, u8 palette);
extern void func_080D7080(const u8 *source, u16 count, u8 *destination, u8 palette);
extern void func_080D70D8(const u8 *source, u16 count, u8 *destination, u8 palette);
extern void func_080D7150(const u8 *source, u16 count, u8 *destination, u8 palette);
extern void func_080D6EEC(const u8 *source, u16 count, u8 *destination, u8 color);
extern void func_080D6F64(const u8 *source, u16 count, u8 *destination);
extern void func_080D6FBC(const u8 *source, u16 count, u8 *destination);
extern void func_0814186C(const void *source, void *destination, u32 control);

u8 func_080D7674(Transfer *transfer)
{
    u8 finished = 0;
    const Descriptor *descriptor = transfer->entries[transfer->index].descriptor;
    const Format *format = descriptor->format;

    if (transfer->remaining <= transfer->chunk) {
        transfer->chunk = transfer->remaining;
        finished = 1;
    }

    if (format->flags & 1) {
        if (format->kind == 1) {
            func_080D702C(transfer->source, transfer->chunk, transfer->destination,
                          descriptor->color, descriptor->palette);
        } else if (format->kind == 2) {
            func_080D7080(transfer->source, transfer->chunk, transfer->destination,
                          descriptor->palette);
        } else if (format->kind == 3) {
            func_080D70D8(transfer->source, transfer->chunk, transfer->destination,
                          descriptor->palette);
        } else if (format->kind == 4) {
            func_080D7150(transfer->source, transfer->chunk, transfer->destination,
                          descriptor->palette);
        } else if (format->kind == 8) {
            if (!(format->flags & 2))
                func_0814186C(transfer->source, transfer->destination,
                              transfer->entries[transfer->index].size >> 1);
        }
    } else {
        if (format->kind == 1) {
            func_080D6EEC(transfer->source, transfer->chunk, transfer->destination,
                          descriptor->color);
        } else if (format->kind == 2) {
            func_080D6F64(transfer->source, transfer->chunk, transfer->destination);
        } else if (format->kind == 3) {
            func_080D6FBC(transfer->source, transfer->chunk, transfer->destination);
        } else if (format->kind == 4) {
            if (!(format->flags & 2))
                func_0814186C(transfer->source, transfer->destination,
                              transfer->entries[transfer->index].size >> 1);
        }
    }

    if (!finished) {
        transfer->source += transfer->chunk;
        transfer->destination += 0x400;
        transfer->remaining -= transfer->chunk;
    }
    return finished;
}
