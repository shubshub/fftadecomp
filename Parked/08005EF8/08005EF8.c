#include "ffta.h"

// Target: complete [0x08005EF8, 0x08005FC4), 204 bytes, 93 instructions.
// 70b5151c0a88012a26d0012a02dc002a05d054e080204000824225d04fe04e68
// 888a28800004002400280ed06100091989006818891934300c223ef163fa601c
// 0004040c28888442f0d380200001a880fff7eefda86032e0a86800282fd0fff7
// f3fd0020a8602ae0002368882a88904202d30220088022e0688841000918890034
// 316918887a0f220240002a02d00f2a04d008e0281cfff761fe02e0281cfff771ff
// 0006030e002b09d06888013068800549281c0c300a680c213cf14bf9002070bc02
// bc08470000b8d43608

typedef struct RequestNode {
    u8 status;
    u8 kind;
    u8 unknown_02[2];
    u32 first;
    u32 second;
    u32 control;
    u8 unknown_10[8];
    struct RequestNode *next;
} RequestNode;

typedef struct __attribute__((packed)) {
    u32 source;
    u32 destination;
    u16 size;
} TransferDescriptor;

typedef struct __attribute__((packed)) TransferEntry {
    TransferDescriptor descriptor;
    u8 kind;
    u8 value;
} TransferEntry;

typedef struct TransferEvent {
    u16 state;
    u8 unknown_02[2];
    const TransferEntry *entries;
    u8 unknown_08[12];
    u16 count;
    u8 unknown_16[6];
} TransferEvent;

typedef struct TransferPayload {
    u16 count;
    u16 current;
    u16 limit;
    u8 unknown_06[2];
    void *buffer;
    u16 progress;
    u8 unknown_0E[0x0A];
    RequestNode request;
    TransferEntry entries[0];
} TransferPayload;

typedef void (*BufferInitializer)(void *, u32);

extern BufferInitializer const g_callbacks_0836D4B8[];

void *func_08005B28(u32 byte_count);
void func_08005B40(void *object);
u8 func_08005C54(TransferPayload *state, const TransferEntry *entry);
u8 func_08005E7C(TransferPayload *state, const TransferDescriptor *descriptor);

u32 func_08005EF8(void *task, TransferEvent *event, TransferPayload *payload)
{
    switch (event->state) {
    case 0:
    {
        const TransferEntry *entries = event->entries;
        u16 index;

        payload->count = event->count;
        for (index = 0; index < payload->count; index++)
            payload->entries[index] = entries[index];
        payload->limit = 0x800;
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
        u8 done = 0;

        if (payload->current >= payload->count) {
            event->state = 2;
        } else {
            const TransferEntry *entry = &payload->entries[payload->current];

            switch (entry->kind & 0xF) {
            case 0:
                done = func_08005C54(payload, entry);
                break;
            case 0xF:
                done = func_08005E7C(payload, &entry->descriptor);
                break;
            }
            if (done) {
                payload->current++;
                g_callbacks_0836D4B8[0](&payload->progress, 12);
            }
        }
        break;
    }
    }
    return 0;
}
