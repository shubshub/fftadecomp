#include "ffta.h"

typedef struct TransferEvent {
    u16 state;
    u8 unknown_02[2];
    const void *records;
    u8 unknown_08[12];
    u16 count;
} TransferEvent;

typedef struct TransferPayload {
    u16 count;
    u16 cursor;
    u16 size;
    u8 unknown_06[2];
    u8 *buffer;
    u16 transparent;
    u16 fill;
    u16 progress;
    u8 unknown_12[2];
} TransferPayload;

typedef struct TransferShape {
    u8 width;
    u8 height;
    u16 size;
} TransferShape;

typedef struct TileDescriptor {
    void *data;
    u8 width;
    u8 height;
    u16 flags;
} TileDescriptor;

struct ExtendedRequestNode;
struct TransferRecord;
extern const TransferShape g_table_0836D498[];

void *func_081443FC(void *destination, const void *source, u32 size);
void func_08005B40(void *object);
void *func_08005B28(u32 size);
void func_08005FC4(const void *source, u8 palette, u16 offset,
                   u16 transparent, u16 fill, const void *destination);
void func_08000BAC(struct ExtendedRequestNode *entry, u32 first, u32 second,
                   u16 count, u16 field_10, u16 field_12, u16 field_14);
void func_08000A98(struct TransferRecord *entry, const void *source,
                   void *destination, u16 count);

u32 func_0800620C(void *task, void *event_data, void *payload_data)
{
    TransferEvent *event = event_data;
    TransferPayload *payload = payload_data;
    const TransferShape *shapes = g_table_0836D498;
    u8 *record;
    u32 shape;
    u8 flags;
    u8 mode;

    switch (event->state) {
    case 0:
        {
            const u8 *records = event->records;
            u16 index;

            payload->count = event->count;
            for (index = 0; index < payload->count; index++)
                func_081443FC((u8 *)payload_data + 0x30 + index * 16,
                              records + index * 16, 16);
            payload->transparent = 0x3FF;
            payload->fill = 0x3FF;
        }
        break;
    case 1:
        if (payload->buffer != 0) {
            func_08005B40(payload->buffer);
            payload->buffer = 0;
        }
        break;
    case 0x100:
        if (payload->cursor >= payload->count) {
            event->state = 2;
            break;
        }
        record = (u8 *)payload_data + 0x30 + payload->cursor * 16;
        flags = record[12];
        shape = ((flags & 0x30) >> 2) + (flags & 3);
        if (payload->size != shapes[shape].size) {
            payload->size = shapes[shape].size;
            if (payload->buffer != 0) {
                func_08005B40(payload->buffer);
                payload->buffer = 0;
            }
            payload->buffer = func_08005B28(payload->size);
        }
        mode = record[12] & 0x30;
        if (mode == 0) {
            u16 remaining = payload->size >> 1;
            u16 *output = (u16 *)payload->buffer;

            do {
                *output++ = payload->fill;
            } while (--remaining != 0);
        } else if (mode == 0x10) {
            u16 remaining = payload->size;
            u8 *output = payload->buffer;

            do {
                *output++ = payload->fill;
            } while (--remaining != 0);
        }
        flags = record[12];
        if ((flags & 0xC0) == 0x40) {
            mode = flags & 0x30;
            if (mode == 0) {
                u16 remaining = payload->size >> 1;
                u16 *output = (u16 *)payload->buffer;

                do {
                    *output++ = record[0] | (record[1] << 8);
                } while (--remaining != 0);
            } else if (mode == 0x10) {
                u16 remaining = payload->size;
                u8 *output = payload->buffer;

                do {
                    *output++ = record[0];
                } while (--remaining != 0);
            }
        } else {
            TileDescriptor source;
            TileDescriptor destination;

            source.flags = record[6] | (record[7] << 8);
            if ((flags & 0x30) == 0x10)
                source.flags |= 0x8000;
            source.width = record[4];
            source.height = record[5];
            source.data = (void *)((u32)record[0] | ((u32)record[1] << 8) |
                                  ((u32)record[2] << 16) | ((u32)record[3] << 24));
            destination.flags = source.flags & 0x8000;
            destination.width = shapes[shape].width;
            destination.height = shapes[shape].height;
            destination.data = payload->buffer;
            func_08005FC4(&source, record[13], record[14] | (record[15] << 8),
                          payload->transparent, payload->fill, &destination);
        }
        (*(void (**)(void *, s32))0x0836D4B8)(&payload->progress, 4);
        event->state = 0x101;
        break;
    }

    if (event->state == 0x101) {
        u32 complete = 0;

        record = (u8 *)payload_data + 0x30 + payload->cursor * 16;
        flags = record[12];
        mode = flags & 0x30;
        shape = (mode >> 2) + (flags & 3);
        if (mode == 0) {
            u32 source = 0;
            u32 destination = 0;

            switch (flags & 3) {
            case 0:
                source = (u32)payload->buffer;
                destination = (u32)record[8] | ((u32)record[9] << 8) |
                              ((u32)record[10] << 16) | ((u32)record[11] << 24);
                complete = 1;
                break;
            case 1:
                if (payload->progress == 0) {
                    source = (u32)payload->buffer;
                    destination = (u32)record[8] | ((u32)record[9] << 8) |
                                  ((u32)record[10] << 16) | ((u32)record[11] << 24);
                } else if (payload->progress == 1) {
                    source = (u32)(payload->buffer + 0x40);
                    destination = ((u32)record[8] | ((u32)record[9] << 8) |
                                   ((u32)record[10] << 16) | ((u32)record[11] << 24)) + 0x800;
                    complete = 1;
                }
                break;
            case 2:
                if (payload->progress == 0) {
                    source = (u32)payload->buffer;
                    destination = (u32)record[8] | ((u32)record[9] << 8) |
                                  ((u32)record[10] << 16) | ((u32)record[11] << 24);
                } else if (payload->progress == 1) {
                    source = (u32)(payload->buffer + 0x800);
                    destination = ((u32)record[8] | ((u32)record[9] << 8) |
                                   ((u32)record[10] << 16) | ((u32)record[11] << 24)) + 0x800;
                    complete = 1;
                }
                break;
            case 3:
                switch (payload->progress) {
                case 0:
                    source = (u32)payload->buffer;
                    destination = (u32)record[8] | ((u32)record[9] << 8) |
                                  ((u32)record[10] << 16) | ((u32)record[11] << 24);
                    break;
                case 1:
                    source = (u32)(payload->buffer + 0x40);
                    destination = ((u32)record[8] | ((u32)record[9] << 8) |
                                   ((u32)record[10] << 16) | ((u32)record[11] << 24)) + 0x800;
                    break;
                case 2:
                    source = (u32)(payload->buffer + 0x1000);
                    destination = ((u32)record[8] | ((u32)record[9] << 8) |
                                   ((u32)record[10] << 16) | ((u32)record[11] << 24)) + 0x1000;
                    break;
                case 3:
                    source = (u32)(payload->buffer + 0x1040);
                    destination = ((u32)record[8] | ((u32)record[9] << 8) |
                                   ((u32)record[10] << 16) | ((u32)record[11] << 24)) + 0x1800;
                    break;
                }
                break;
            }
            payload->progress++;
            func_08000BAC((void *)((u8 *)payload_data + 0x14), source, destination,
                          0x20, 0x20, shapes[shape].width * 2, 0x40);
        } else if (mode == 0x10) {
            u16 amount = payload->size - payload->progress;
            u16 progress;
            u32 destination;

            if (amount > 0x800)
                amount = 0x800;
            progress = payload->progress;
            destination = (u32)record[8] | ((u32)record[9] << 8) |
                          ((u32)record[10] << 16) | ((u32)record[11] << 24);
            func_08000A98((void *)((u8 *)payload_data + 0x14),
                          payload->buffer + progress, (void *)(destination + progress),
                          amount >> 1);
            payload->progress += amount;
            if (payload->progress >= payload->size)
                complete = 1;
        }
        if (complete) {
            payload->cursor++;
            event->state = 0x100;
        }
    }
    return 0;
}
