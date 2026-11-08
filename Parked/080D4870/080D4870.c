#include "ffta.h"

typedef struct SchedulerDescriptor080D4870 {
    u8 unknown_00[4];
    u32 value;
    u8 unknown_08[12];
    u16 unknown_14;
    u8 unknown_16[6];
} SchedulerDescriptor080D4870;

typedef struct SchedulerEntry080D4870 {
    u32 value;
    u16 state;
} SchedulerEntry080D4870;

typedef struct TaskState080D4870 {
    u8 unknown_00[8];
    u16 state;
} TaskState080D4870;

typedef u32 (*SchedulerCallback080D4870)(void *task, void *descriptor,
                                       void *payload);

u32 func_080D449C(void *task, SchedulerDescriptor080D4870 *descriptor,
                  void *payload);
void *func_08005B6C(SchedulerCallback080D4870 callback, u16 payload_size,
                    void *descriptor, void *parent);
TaskState080D4870 *func_08005BFC(void *task);

/* 0x080D4870: 108 target bytes, including the callback literal.
 * f0b54f464646c0b487b0814688461f1c1204160c0025b5421ed2e80049464418
 * 226869460020888201920f4818216a463b1c31f763f9011ca800404401
 * 60a088002804d0041c081c31f7a0f90481681c0004050cb542e0d307b018bc98
 * 46a146f0bc01bc004700009d440d08
 */
void func_080D4870(SchedulerEntry080D4870 *entries, void **tasks, u16 count,
                   void *parent)
{
    SchedulerDescriptor080D4870 descriptor;
    u16 i;

    for (i = 0; i < count; i++) {
        u32 value = entries[i].value;
        void *task;

        descriptor.unknown_14 = 0;
        descriptor.value = value;
        task = func_08005B6C((SchedulerCallback080D4870)func_080D449C, 0x18,
                             &descriptor, parent);
        tasks[i] = task;
        if (entries[i].state != 0) {
            u16 state = entries[i].state;

            func_08005BFC(task)->state = state;
        }
    }
}
