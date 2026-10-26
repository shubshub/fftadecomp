#include "ffta.h"

/* 0x080D7674..0x080D7796: 290 bytes. */
typedef struct {
    u8 kind;
    u8 flags;
} Format;

typedef struct {
    const Format *format;
    u8 first;
    u8 second;
} Descriptor;

typedef struct {
    u16 unknown_00;
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
    u8 *destination;
    const u8 *source;
} Transfer;

extern void func_080D702C(void *destination, u16 count, const void *source, u8 first, u8 second);
extern void func_080D7080(void *destination, u16 count, const void *source, u8 second);
extern void func_080D70D8(void *destination, u16 count, const void *source, u8 second);
extern void func_080D7150(void *destination, u16 count, const void *source, u8 second);
extern void func_080D6EEC(void *destination, u16 count, const void *source, u8 first);
extern void func_080D6F64(void *destination, u16 count, const void *source);
extern void func_080D6FBC(void *destination, u16 count, const void *source);
extern void func_0814186C(void *destination, const void *source, u32 count);

u8 func_080D7674(Transfer *transfer)
{
    u8 finished = 0;
    const Descriptor *descriptor = transfer->entries[transfer->index].descriptor;
    const Format *format;
    u8 flags;

    if (transfer->remaining <= transfer->chunk) {
        transfer->chunk = transfer->remaining;
        finished = 1;
    }

    format = descriptor->format;
    flags = format->flags;
    if (flags & 1) {
        if (format->kind == 1)
            func_080D702C(transfer->destination, transfer->chunk, transfer->source, descriptor->first, descriptor->second);
        else if (format->kind == 2)
            func_080D7080(transfer->destination, transfer->chunk, transfer->source, descriptor->second);
        else if (format->kind == 3)
            func_080D70D8(transfer->destination, transfer->chunk, transfer->source, descriptor->second);
        else if (format->kind == 4)
            func_080D7150(transfer->destination, transfer->chunk, transfer->source, descriptor->second);
        else if (format->kind == 8 && !(flags & 2))
            func_0814186C(transfer->destination, transfer->source, transfer->entries[transfer->index].size >> 1);
    } else {
        if (format->kind == 1)
            func_080D6EEC(transfer->destination, transfer->chunk, transfer->source, descriptor->first);
        else if (format->kind == 2)
            func_080D6F64(transfer->destination, transfer->chunk, transfer->source);
        else if (format->kind == 3)
            func_080D6FBC(transfer->destination, transfer->chunk, transfer->source);
        else if (format->kind == 4 && !(flags & 2))
            func_0814186C(transfer->destination, transfer->source, transfer->entries[transfer->index].size >> 1);
    }

    if (!finished) {
        transfer->destination += transfer->chunk;
        transfer->source += 0x400;
        transfer->remaining -= transfer->chunk;
    }
    return finished;
}
