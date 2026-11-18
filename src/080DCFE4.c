#include "ffta.h"
#include "effect_task.h"

typedef struct Object080DCFE4 {
    void *value;
    u8 unknown_04[8];
    u16 flags;
} Object080DCFE4;

typedef struct Parameters080DCFE4 {
    void *first_value;
    u8 kind;
    u8 unknown_05;
    u8 unknown_06;
    u8 unknown_07;
    const void *second_value;
} Parameters080DCFE4;

typedef struct Payload080DCFE4 {
    void *unknown_00;
    u8 unknown_04;
    u8 unknown_05;
    u16 unknown_06;
    u16 unknown_08;
} Payload080DCFE4;

typedef struct Descriptor080DCFE4 {
    u8 unknown_00[4];
    void *data;
    u8 unknown_08[12];
    u16 first;
    u16 second;
    u8 unknown_18[4];
} Descriptor080DCFE4;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

u32 func_080DC55C(void *task, void *descriptor, void *payload);
u32 func_080DCAD4(void *task, void *descriptor, void *payload);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                    void *descriptor, void *parent);

static inline u8 object_flag(const Object080DCFE4 *object)
{
    return (object->flags >> 7) & 1;
}

static inline u8 object_enabled(const Object080DCFE4 *object)
{
    s8 temp = object_flag(object);
    u8 result = 0;

    if (temp == 1)
        result = 1;
    return result;
}

typedef struct Frame080DCFE4 {
    Descriptor080DCFE4 descriptor;
    Payload080DCFE4 payload;
} Frame080DCFE4;

static inline void *start_task(Parameters080DCFE4 *parameters, u16 first,
                               u16 second, void *parent)
{
    Descriptor080DCFE4 descriptor;

    descriptor.first = first;
    descriptor.second = second;
    descriptor.data = parameters;
    return func_08005B6C(func_080DC55C, 0x38, &descriptor, parent);
}

static inline void *start_delay(void *value, u8 index, u16 count, u16 amount,
                                void *parent)
{
    Frame080DCFE4 frame;
    u8 delay = 0x1E;
    Payload080DCFE4 *payload;

    frame.payload.unknown_00 = value;
    payload = &frame.payload;
    payload->unknown_04 = index;
    payload->unknown_06 = 0;
    payload->unknown_05 = delay;
    payload->unknown_08 = amount;
    frame.descriptor.first = count;
    frame.descriptor.data = payload;
    return func_08005B6C(func_080DCAD4, 0xC, &frame.descriptor, parent);
}

void *func_080DCFE4(void *owner, const void *second_value, u8 kind,
                    u16 first, u16 second, void *parent, s16 amount)
{
    Object080DCFE4 *object = owner;
    Parameters080DCFE4 parameters;
    u8 flagged = object_enabled(object);

    if (flagged) {
        if (second_value == 0)
            return 0;
        parameters.first_value = object;
        parameters.kind = kind;
        parameters.unknown_05 = 6;
        parameters.unknown_06 = 4;
        parameters.unknown_07 = 6;
        parameters.second_value = second_value;
        return start_task(&parameters, first, second, parent);
    } else {
        s16 delay_amount = amount;

        if (delay_amount == -1)
            return 0;
        return start_delay(object->value, 0x15, second, delay_amount, parent);
    }
}
