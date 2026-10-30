#include "ffta.h"

/* Complete [0x0800C3CC, 0x0800C4B4), 232 bytes.
 * Target bytes:
 * f0b557464e464546e0b481b08246994609040e0c1204120c90460023004905e04891000204310133
 * 032b02dc08680028f8d1042b01d1002043e00322301c1040002804d023480640301d0004060c371c
 * 20374146c8014901401844460519281c1040002803d0042040420540043568003f1819480068391c
 * 0093faf777fe041c16480268201c391c35f1fafe50462060494661602682424662820120a081201c
 * 203060618019a0614019e0610c49424650080843a0600b49009b980040180460201c01b038bc9846
 * a146aa46f0bc02bc08470000fcff000040910002b8d436080000602248910002
 */

typedef void (*ObjectCallback)(void *state, u16 *destination);
typedef void (*BufferInitializer)(void *destination, u32 size);

typedef struct ScanlineTask {
    ObjectCallback callback;
    u16 *destination;
    u32 control;
    u16 enabled;
    u16 unknown_0E;
    u16 payload_bytes;
    u16 element_size;
    u8 *payload;
    u8 *first_buffer;
    u8 *second_buffer;
} ScanlineTask;

typedef struct {
    ScanlineTask *objects[4];
    s16 handles[4];
} ObjectSlots;

extern ObjectSlots data_02009148;
extern void *data_02009140;
extern BufferInitializer const g_callbacks_0836D4B8[];
extern void *func_08007138(void *owner, u32 bytes);

ScanlineTask *func_0800C3CC(ObjectCallback callback, u16 payload_bytes,
                          u16 element_size, u16 *destination)
{
    s32 slot;
    u32 total_bytes;
    u32 buffer_bytes;
    ScanlineTask *task;

    for (slot = 0; slot < 4; slot++) {
        if (data_02009148.objects[slot] == 0)
            break;
    }
    if (slot == 4)
        return 0;
    if (payload_bytes & 3)
        payload_bytes = (payload_bytes & ~3) + 4;
    total_bytes = payload_bytes + sizeof(ScanlineTask);
    buffer_bytes = element_size * 160;
    buffer_bytes += element_size;
    if (buffer_bytes & 3) {
        buffer_bytes &= ~3;
        buffer_bytes += 4;
    }
    total_bytes += buffer_bytes * 2;

    task = func_08007138(data_02009140, total_bytes);
    g_callbacks_0836D4B8[0](task, total_bytes);
    task->callback = callback;
    task->destination = destination;
    task->payload_bytes = payload_bytes;
    task->element_size = element_size;
    task->enabled = 1;
    task->payload = (u8 *)(task + 1);
    task->first_buffer = task->payload + payload_bytes;
    task->second_buffer = task->first_buffer + buffer_bytes;
    task->control = 0x22600000 | (element_size >> 1);
    data_02009148.objects[slot] = task;
    return task;
}
