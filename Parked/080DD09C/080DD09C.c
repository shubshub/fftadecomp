#include "ffta.h"

typedef struct Object080DD09C {
    void *value;
    u8 unknown_04[8];
    u16 flags;
} Object080DD09C;

typedef struct Parameters080DD09C {
    void *first_value;
    u8 kind;
    u8 unknown_05;
    u8 unknown_06;
    u8 unknown_07;
    void *second_value;
} Parameters080DD09C;

typedef struct Payload080DD09C {
    void *unknown_00;
    u8 unknown_04;
    u8 unknown_05;
    u16 unknown_06;
    u16 unknown_08;
} Payload080DD09C;

typedef struct Descriptor080DD09C {
    u8 unknown_00[4];
    void *data;
    u8 unknown_08[12];
    u16 first;
    u16 second;
    u8 unknown_18[4];
} Descriptor080DD09C;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

u32 func_080DC55C(void *task, void *descriptor, void *payload);
struct SchedulerDescriptor080DCAD4;
u32 func_080DCAD4(void *task, struct SchedulerDescriptor080DCAD4 *descriptor, void *payload);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                    void *descriptor, void *parent);

static inline u8 object_flag(const Object080DD09C *object)
{
    return (object->flags >> 7) & 1;
}

static inline u8 object_enabled(const Object080DD09C *object)
{
    s8 temp = object_flag(object);
    u8 result = 0;

    if (temp == 1)
        result = 1;
    return result;
}

typedef struct Frame080DD09C {
    Descriptor080DD09C descriptor;
    Payload080DD09C payload;
} Frame080DD09C;

static inline void *start_task(Parameters080DD09C *parameters, u16 first,
                               u16 second, void *parent)
{
    Descriptor080DD09C descriptor;

    descriptor.first = first;
    descriptor.second = second;
    descriptor.data = parameters;
    return func_08005B6C(func_080DC55C, 0x38, &descriptor, parent);
}

static inline void *start_delay(void *value, u8 index, u16 count, u16 amount,
                                void *parent)
{
    Frame080DD09C frame;
    u8 delay = 0x1E;
    Payload080DD09C *payload;

    frame.payload.unknown_00 = value;
    payload = &frame.payload;
    payload->unknown_04 = index;
    payload->unknown_06 = 0;
    payload->unknown_05 = delay;
    payload->unknown_08 = amount;
    frame.descriptor.first = count;
    frame.descriptor.data = payload;
    return func_08005B6C((TaskCallback)func_080DCAD4, 0xC, &frame.descriptor, parent);
}

void *func_080DD09C(Object080DD09C *object, void *second_value, u8 kind,
                    u16 override_05, u16 override_06, u16 override_07, s16 first,
                    u16 second, void *parent, u16 amount)
{
    Parameters080DD09C parameters;
    u8 flagged = object_enabled(object);

    if (flagged) {
        if (second_value == 0)
            return 0;
        parameters.first_value = object;
        parameters.kind = kind;
        parameters.unknown_05 = 6;
        parameters.unknown_06 = 4;
        parameters.unknown_07 = 6;
        if ((s16)override_05 != -1)
            parameters.unknown_05 = override_05;
        if ((s16)override_06 != -1)
            parameters.unknown_06 = override_06;
        if ((s16)override_07 != -1)
            parameters.unknown_07 = override_07;
        parameters.second_value = second_value;
        return start_task(&parameters, first, second, parent);
    } else {
        s16 delay_amount = amount;

        if (delay_amount == -1)
            return 0;
        return start_delay(object->value, 0x15, second, delay_amount, parent);
    }
}
