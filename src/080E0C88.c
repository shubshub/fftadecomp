#include "ffta.h"

/* Target bytes: 00b50b88012b16d0012b02dc002b05d011e080204000834203d00ce08868108009e01088002804d0013810800004002801d102200880002002bc0847 */

typedef struct CountdownDescriptor {
    u16 phase;
    u8 unknown_02[6];
    u32 duration;
} CountdownDescriptor;

typedef struct CountdownPayload {
    u16 remaining;
    u8 unknown_02[2];
} CountdownPayload;

u32 func_080E0C88(void *task, void *descriptor_data, void *payload_data)
{
    CountdownDescriptor *descriptor = descriptor_data;
    CountdownPayload *payload = payload_data;

    switch (descriptor->phase) {
    case 0:
        payload->remaining = descriptor->duration;
        break;
    case 1:
        break;
    case 0x100:
        if (payload->remaining != 0)
            payload->remaining--;
        if (payload->remaining == 0)
            descriptor->phase = 2;
        break;
    }

    return 0;
}
