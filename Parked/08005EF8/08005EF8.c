#include "ffta.h"

typedef struct TransferEntry {
    u8 unknown_00[10];
    u8 kind;
    u8 value;
} TransferEntry;

typedef struct TransferEvent {
    u16 state;
    u8 unknown_02[2];
    const TransferEntry *entries;
    u8 unknown_08[12];
    u16 count;
} TransferEvent;

typedef struct TransferPayload {
    u16 count;
    u16 cursor;
    u16 capacity;
    u8 unknown_06[2];
    void *buffer;
    u8 scratch[12];
    u8 unknown_18[0x1C];
    TransferEntry entries[0];
} TransferPayload;

void *func_081443FC(void *destination, const void *source, u32 byte_count);
void *func_08005B28(u32 byte_count);
void func_08005B40(void *object);
u32 func_08005C54(void *state, const void *input);
u8 func_08005E7C(void *object, const void *descriptor);

u32 func_08005EF8(void *task, TransferEvent *event, TransferPayload *payload)
{
    switch (event->state) {
    case 0:
    {
        const TransferEntry *entries = event->entries;
        u16 index;

        payload->count = event->count;
        for (index = 0; index < payload->count; index++) {
            u32 offset = index * sizeof(TransferEntry);

            func_081443FC((u8 *)payload + offset + sizeof(TransferPayload),
                          (const u8 *)entries + offset, sizeof(TransferEntry));
        }
        payload->capacity = 0x800;
        payload->buffer = func_08005B28(0x800);
        break;
    }
    case 1:
        if (payload->buffer != 0) {
            func_08005B40(payload->buffer);
            payload->buffer = 0;
        }
        break;
    case 0x100:
    {
        u8 completed = 0;

        if (payload->cursor >= payload->count) {
            event->state = 2;
        } else {
            const TransferEntry *entry = &payload->entries[payload->cursor];

            switch (entry->kind & 0xF) {
            case 0:
                completed = func_08005C54(payload, entry);
                break;
            case 0xF:
                completed = func_08005E7C(payload, entry);
                break;
            }
            if (completed) {
                payload->cursor++;
                (*(void (**)(void *, u32))0x0836D4B8)(payload->scratch, sizeof(payload->scratch));
            }
        }
        break;
    }
    }
    return 0;
}
