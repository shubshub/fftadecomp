/* 0x08006878: 52 bytes, including the scheduler callback literal. */
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
    u8 unknown_16[6];
} TransferEvent;

typedef struct TransferPayload TransferPayload;
typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

u32 func_08005EF8(void *task, TransferEvent *event, TransferPayload *payload);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

void *func_08006878(const TransferEntry *entries, u16 count, void *parent)
{
    u16 entry_bytes = count * sizeof(TransferEntry);
    TransferEvent descriptor;

    descriptor.entries = entries;
    descriptor.count = count;
    return func_08005B6C((TaskCallback)func_08005EF8,
                         entry_bytes + 0x40,
                         &descriptor, parent);
}
