#include "ffta.h"
#include "control_flags.h"

typedef void (*ScanlineCallback)(void *state, u16 *buffer);

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

extern void func_08000D90(u32 handle);
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
        task->callback(task->payload_bytes ? task->payload : 0, (u16 *)buffer);
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
