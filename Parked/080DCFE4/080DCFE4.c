// 0x080DCFE4: complete 184-byte caller, including both callback literals.
// f0b54f464646c0b494b0041c8c461b981d991206170e1b041b0c98460004060cb14609040b0ca089c009012100220840012800d10122151c002d19d06046002832d0009468460771062242716946042088716846c2716146029103aa40469082d682694604910148382117e05dc50d081b04191401204042814215d01b0c206815211e22119011a80171c580427103810aaa49469182506002480c211c9b28f773fd02e0d5ca0d08002014b018bc9846a146f0bc02bc0847
#include "ffta.h"

typedef struct Object080DCFE4 {
    u8 unknown_00[0xC];
    u16 flags;
} Object080DCFE4;

typedef struct Parameters080DCFE4 {
    void *first_value;
    u8 kind;
    u8 unknown_05;
    u8 unknown_06;
    u8 unknown_07;
    void *second_value;
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

void *func_080DCFE4(Object080DCFE4 *object, void *second_value, u8 kind,
                    u16 first, u16 second, void *parent, u16 amount)
{
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
        return start_delay(*(void **)object, 0x15, second, delay_amount, parent);
    }
}
