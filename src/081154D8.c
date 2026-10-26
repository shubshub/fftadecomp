#include "ffta.h"

/* Target: complete [0x081154D8, 0x08115560), 136 bytes.
 * Offset views only; the complete descriptor and payload extents are unknown. */
typedef struct {
    u16 phase;
} Descriptor081154D8;

typedef struct {
    u16 remaining;
    u8 unknown_02[6];
    void *timeline;
} Payload081154D8;

extern const u8 data_0894DC2C[];
extern u16 g_control_flags_03000940;
extern void *func_080D3E9C(const void *resource, void *parent);
extern void *func_080D3F08(void *task);
extern u32 func_080035A8(u8 index);

u32 func_081154D8(void *task, Descriptor081154D8 *descriptor,
                  Payload081154D8 *payload)
{
    switch (descriptor->phase) {
    case 0:
        payload->remaining = 30;
        break;
    case 0x100:
        payload->remaining--;
        if (payload->remaining == 0) {
            payload->timeline = func_080D3E9C(data_0894DC2C, task);
            descriptor->phase++;
        }
        break;
    case 0x101:
        payload->timeline = func_080D3F08(payload->timeline);
        if (payload->timeline == 0) {
            u32 mask = func_080035A8(3);
            g_control_flags_03000940 &= ~mask;
            descriptor->phase++;
        }
        break;
    case 0x102:
        descriptor->phase = 2;
        break;
    }
    return 0;
}
