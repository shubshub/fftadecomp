#include "ffta.h"

typedef struct {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} Motion;

typedef struct {
    u16 phase;
    u8 unknown_02[0x12];
    s16 x;
    s16 y;
    u8 unknown_18[4];
} Descriptor;

typedef struct {
    u16 counter;
    s16 x;
    s16 y;
    u16 unknown_06;
    void *child;
    Motion motion;
} Payload;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

extern u8 data_06008000[];
extern u8 data_06007000[];
extern u16 g_control_flags_03000940;
extern u32 func_08112CCC(void *task, void *descriptor, void *payload);
extern void *func_08005B6C(TaskCallback callback, u16 payload_size,
                         void *descriptor, void *parent);
extern void func_080D74E0(u8 first, u8 second, u8 third, s16 x, s16 y,
                        void *first_buffer, void *second_buffer);
extern u32 func_080035A8(u8 layer);
extern void func_08003558(s16 position, u8 layer);
extern void func_080E0608(Motion *motion, s16 start, s16 end, s16 duration);
extern void func_080E064C(Motion *motion);
extern u8 func_080E0690(Motion *motion);
extern void *func_080E051C(void *object);

u32 func_08112E88(void *task, Descriptor *descriptor, Payload *payload)
{
    Descriptor request;

    switch (descriptor->phase) {
    case 0:
        payload->x = descriptor->x;
        payload->y = descriptor->y;
        break;
    case 0x100:
        payload->child = func_08005B6C(func_08112CCC, 32, &request, task);
        payload->counter = 30;
        descriptor->phase++;
        break;
    case 0x101:
        if (--payload->counter == 0) {
            u32 mask;
            u16 flags;

            func_080D74E0(1, 2, 1, (s16)(payload->x - 120),
                         (s16)(payload->y - 248),
                         data_06008000, data_06007000);
            mask = func_080035A8(1);
            flags = g_control_flags_03000940;
            flags |= mask;
            g_control_flags_03000940 = flags;
            func_080E0608(&payload->motion, 248, 112, 40);
            descriptor->phase++;
        }
        break;
    case 0x102:
        if (!func_080E0690(&payload->motion)) {
            func_080E064C(&payload->motion);
            func_08003558((s16)(payload->y - payload->motion.current), 1);
        } else {
            payload->child = func_080E051C(payload->child);
            if (payload->child == 0)
                descriptor->phase = 2;
        }
        break;
    }
    return 0;
}
