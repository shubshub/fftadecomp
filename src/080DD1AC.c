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

typedef u32 (*SchedulerCallback080DCAD4)(void *task, void *descriptor,
                                         void *payload);

u32 func_080DCAD4(void *task, SchedulerDescriptor080DCAD4 *descriptor,
                  void *payload);
void *func_08005B6C(SchedulerCallback080DCAD4 callback, u16 payload_size,
                    void *descriptor, void *parent);

/* 0x080DD1AC: 52 target bytes, including the callback literal.
 * f0b58ab00f9e109d119f07ac07902171e2806371258168468682019404480c216a463b1c28f7ccfc0ab0f0bc02bc0847d5ca0d08
 */
void *func_080DD1AC(void *value, u8 first, u16 third, u8 second, u16 fifth,
                    u16 fourth, void *parent)
{
    SchedulerDescriptor080DCAD4 descriptor;
    SchedulerPayload080DCAD4 payload;

    payload.unknown_00 = value;
    payload.unknown_04 = first;
    payload.unknown_06 = third;
    payload.unknown_05 = second;
    payload.unknown_08 = fourth;
    descriptor.unknown_14 = fifth;
    descriptor.payload = &payload;
    return func_08005B6C((SchedulerCallback080DCAD4)func_080DCAD4, 0xC,
                         &descriptor, parent);
}
