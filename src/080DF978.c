#include "ffta.h"

typedef struct Payload080DF978 {
    u16 selector;
    u16 value;
    void *object;
    u32 unknown_08;
} Payload080DF978;

typedef struct Descriptor080DF978 {
    u8 unknown_00[4];
    Payload080DF978 *payload;
    u8 unknown_08[12];
    u16 flags;
    u8 unknown_16[6];
} Descriptor080DF978;

typedef u32 (*Callback080DF978)(void *task, void *descriptor, void *payload);

u32 func_080DEF90(void *task, void *descriptor, void *payload);
void *func_08005B6C(Callback080DF978 callback, u16 payload_size,
                    void *descriptor, void *parent);

/* 0x080DF978: 52 target bytes, including padding and both literals.
 * 30b58ab00904090c07ad084c2c806860698068468282019505481c216a4626f7e9f8
 * 0ab030bc02bc08470000ffff000091ef0d08
 */
void *func_080DF978(void *object, u16 value, u16 flags, void *parent)
{
    Descriptor080DF978 descriptor;
    Payload080DF978 payload;

    payload.selector = 0xFFFF;
    payload.object = object;
    payload.value = value;
    descriptor.flags = flags;
    descriptor.payload = &payload;
    return func_08005B6C(func_080DEF90, 0x1C, &descriptor, parent);
}
