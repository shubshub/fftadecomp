#include "ffta.h"

typedef struct SchedulerPayload080DCAD4 {
    void *unknown_00;
    u8 unknown_04;
    u8 unknown_05;
    u16 unknown_06;
    u16 unknown_08;
} SchedulerPayload080DCAD4;

typedef struct SchedulerDescriptor080DCAD4 {
    u8 unknown_00[4];
    SchedulerPayload080DCAD4 *payload;
    u8 unknown_08[12];
    u16 unknown_14;
    u8 unknown_16[6];
} SchedulerDescriptor080DCAD4;

typedef struct SchedulerFrame080DCAD4 {
    SchedulerDescriptor080DCAD4 descriptor;
    SchedulerPayload080DCAD4 payload;
} SchedulerFrame080DCAD4;

typedef u32 (*SchedulerCallback080DCAD4)(void *task, void *descriptor,
                                         void *payload);

u32 func_080DCAD4(void *task, SchedulerDescriptor080DCAD4 *descriptor,
                  void *payload);
void *func_08005B6C(SchedulerCallback080DCAD4 callback, u16 payload_size,
                    void *descriptor, void *parent);

/* 0x080DD1E0: 52 target bytes, including the callback literal.
 * 70b58ab00e9e1e25079007ac00202171e0806571238168468282019404480c216a46331c
 * 28f7b2fc0ab070bc02bc0847d5ca0d08
 */
/* The two constants are kept in locals; this likely reflects an inlined helper's arguments (an inference, not evidenced). */
void *func_080DD1E0(void *value, u8 index, u16 count, u16 amount, void *parent)
{
    SchedulerFrame080DCAD4 frame;
    u8 delay = 0x1E;
    SchedulerPayload080DCAD4 *payload;

    frame.payload.unknown_00 = value;
    payload = &frame.payload;
    payload->unknown_04 = index;
    payload->unknown_06 = 0;
    payload->unknown_05 = delay;
    payload->unknown_08 = amount;
    frame.descriptor.unknown_14 = count;
    frame.descriptor.payload = payload;
    return func_08005B6C((SchedulerCallback080DCAD4)func_080DCAD4, 12,
                         &frame.descriptor, parent);
}
