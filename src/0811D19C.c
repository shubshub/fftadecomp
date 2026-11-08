#include "ffta.h"

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    void *value;
} Descriptor0811D19C;

typedef struct {
    void *value;
    void *child_task;
} Payload0811D19C;

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    void *value;
    u8 unknown_08[12];
    s16 field_14;
    u16 field_16;
    u8 unknown_18[4];
} TaskDescriptor0811D19C;

extern void *func_08005B6C(TaskCallback, u16, void *, void *);
extern void *func_080E051C(void *);
extern void func_080D35D8(void);
extern u32 func_08115D74(void *, void *, void *);

/* Complete [0x0811D19C, 0x0811D216), 122 bytes.
 * Target:
 * 30b587b0031c0d1c141c298801290fd0012902dc002908d02ae0802040008142
 * 09d0013081421bd022e0686820601fe0b6f704fa1ce069460022074888826846
 * c2822068019005483c216a46e8f6c0fc6060288801300ae087010000755d1108
 * 6068c3f78df96060002801d102202880002007b030bc02bc0847
 */
u32 func_0811D19C(void *task, Descriptor0811D19C *descriptor,
                  Payload0811D19C *payload)
{
    switch (descriptor->phase) {
    case 0:
        payload->value = descriptor->value;
        break;
    case 1:
        func_080D35D8();
        break;
    case 0x100: {
        TaskDescriptor0811D19C child_descriptor;

        child_descriptor.field_14 = 0x187;
        child_descriptor.field_16 = 0;
        child_descriptor.value = payload->value;
        payload->child_task = func_08005B6C(func_08115D74, 0x3c,
                                           &child_descriptor, task);
        descriptor->phase++;
        break;
    }
    case 0x101:
        payload->child_task = func_080E051C(payload->child_task);
        if (payload->child_task == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
