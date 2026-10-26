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
} Descriptor;

typedef struct {
    u16 counter;
    u8 unknown_02[4];
    s16 x;
    s16 y;
    u8 unknown_0A[2];
    void *object;
    Motion vertical;
    Motion y_motion;
    void *record_task;
} Payload;

extern u8 data_06008000[];
extern u8 data_06007000[];
extern u16 g_control_flags_03000940;
extern const u8 data_083A33D4[];
extern const u8 data_08504D8C[];

void func_080E0608(Motion *motion, s16 start, s16 end, s16 duration);
void func_080E064C(Motion *motion);
u8 func_080E0690(Motion *motion);
void func_080D74E0(u8 first, u8 second, u8 third, s16 x, s16 y,
                   void *first_buffer, void *second_buffer);
u32 func_080035A8(u8 layer);
void func_08003558(s16 position, u8 layer);
void *func_080DFD8C(const void *record, u8 mode, u16 first,
                    u16 second, void *task);
void *func_080D5CC0(const void *resource, u16 mode, s16 x, s16 y,
                    u16 attributes, u8 first, u8 second, u32 flags);
void func_080107D4(void *object, s16 x, s16 y, u8 flags);
void func_08011428(void *object);

/* Complete target: [0x08112594, 0x08112734), 416 bytes. */
u32 func_08112594(void *task, Descriptor *descriptor, Payload *payload)
{
    switch (descriptor->phase) {
    case 0: {
        u32 mask;
        u16 flags;

        payload->x = descriptor->x;
        payload->y = descriptor->y;
        func_080E0608(&payload->vertical, 224, 106, 60);
        func_080D74E0(1, 2, 1, (s16)(payload->x - 120),
                       (s16)(payload->y - payload->vertical.current),
                       data_06008000, data_06007000);
        mask = func_080035A8(1);
        flags = g_control_flags_03000940;
        flags |= mask;
        g_control_flags_03000940 = flags;
        payload->record_task = func_080DFD8C(data_083A33D4, 1, 4, 0, task);
        payload->counter = 52;
        break;
    }
    case 1:
        break;
    case 0x100:
        if (!func_080E0690(&payload->vertical)) {
            func_080E064C(&payload->vertical);
            func_08003558((s16)(payload->y - payload->vertical.current), 1);
        }
        if (--payload->counter == 0) {
            func_080E0608(&payload->y_motion, 12, 104, 8);
            payload->object = func_080D5CC0(data_08504D8C, 3, 120,
                                            payload->y_motion.current,
                                            0x30B, 8, 0, 0);
            descriptor->phase++;
        }
        break;
    case 0x101: {
        u8 complete = 1;

        if (!func_080E0690(&payload->vertical)) {
            func_080E064C(&payload->vertical);
            func_08003558((s16)(payload->y - payload->vertical.current), 1);
            complete = 0;
        }
        if (!func_080E0690(&payload->y_motion)) {
            u32 cycle;
            s16 x = 120;
            s16 y;

            func_080E064C(&payload->y_motion);
            cycle = payload->counter & 3;
            y = payload->y_motion.current;
            if (cycle == 1)
                y += 2;
            else if (cycle == 3)
                y -= 2;
            payload->counter++;
            func_080107D4(payload->object, x, y, 0);
            complete = 0;
        }
        if (complete) {
            func_08011428(payload->object);
            payload->object = 0;
            descriptor->phase = 2;
        }
        break;
    }
    }
    return 0;
}
