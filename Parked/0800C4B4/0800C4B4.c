#include "ffta.h"
#include "control_flags.h"

// Complete [0x0800C4B4, 0x0800C5F4), 320 bytes.
// Target bytes:
// f0b54f464646c0b400270d4bb800c0180468002c33d0a1890220084000282ed12268002a2bd0
// 05200840002827d0054b181c0840a081e089002805d1e06904e048910002feff0000a069051c
// 208a0021002800d06169081c291c35f19dfe628ad1016918500109185208281c35f1a4f90021
// e089002800d10121e1811a4b0137032fc3dd00271848814601214942884678004946103146180022
// b05e404501d0f4f71cfcb80048440468002c3bd0a18902200840002836d1e1898900201c1830
// 40180568608a28186168a268f4f714fa308000040014404525d061688020c004814205d10149
// 1ce04891000240090003064a88184b280dd8054b98180b18628a5208281c191c35f157f90ce0
// f8fffffb42090003fb231b06c9180748814202d80649288808800137032fb1dd18bc9846a146
// f0bc01bc0047ff03000060380003

typedef void (*ScanlineCallback)(void *state, u8 *buffer);

typedef struct ScanlineTask {
    ScanlineCallback callback;
    u16 *destination;
    u32 control;
    u16 flags;
    u16 front;
    u16 payload_bytes;
    u16 element_size;
    u8 *payload;
    u8 *buffers[2];
} ScanlineTask;

typedef struct {
    ScanlineTask *objects[4];
    s16 handles[4];
} ObjectSlots;

extern ObjectSlots data_02009148;
extern u8 data_03000942[];
extern u16 data_03003860[];

extern void func_08000D90(s32 handle);
extern s32 func_080009AC(const void *source, void *destination, u32 control);
extern void func_0814186C(const void *source, void *destination, u32 control);

static inline u8 *back_buffer(const ScanlineTask *task)
{
    return task->front == 0 ? task->buffers[1] : task->buffers[0];
}

void func_0800C4B4(void)
{
    s32 i;
    ScanlineTask *task;
    u8 *buffer;
    u32 shadow;

    for (i = 0; i < 4; i++) {
        task = data_02009148.objects[i];
        if (task == 0 || (task->flags & 2) || task->callback == 0
            || !(task->flags & 5))
            continue;
        task->flags &= ~1;
        buffer = back_buffer(task);
        task->callback(task->payload_bytes ? task->payload : 0, buffer);
        func_0814186C(buffer,
                      buffer + (task->element_size << 7)
                          + (task->element_size << 5),
                      task->element_size >> 1);
        task->front = task->front == 0;
    }

    for (i = 0; i < 4; i++) {
        if (data_02009148.handles[i] != -1)
            func_08000D90(data_02009148.handles[i]);
        task = data_02009148.objects[i];
        if (task == 0 || (task->flags & 2))
            continue;
        buffer = task->buffers[task->front];
        data_02009148.handles[i] = func_080009AC(buffer + task->element_size,
                                                 task->destination,
                                                 task->control);
        if (data_02009148.handles[i] == -1)
            continue;
        if ((u32)task->destination == 0x04000000) {
            g_control_flags_03000940.display = *(u16 *)buffer;
        } else if ((u32)task->destination - 0x04000008 <= 0x4B) {
            shadow = (u32)data_03000942;
            shadow += (u32)task->destination - 0x04000008;
            func_0814186C(buffer, (void *)shadow, task->element_size >> 1);
        } else if ((u32)task->destination - 0x05000000 <= 0x3FF) {
            data_03003860[0] = *(u16 *)buffer;
        }
    }
}
