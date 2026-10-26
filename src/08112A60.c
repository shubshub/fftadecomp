#include "ffta.h"

/* Target: complete [0x08112A60, 0x08112AEA), 138 bytes including literals. */
typedef struct {
    u16 phase;
    u16 unknown_02;
    u8 *value;
} Descriptor08112A60;

typedef struct {
    u32 unknown_00[2];
    u8 *value;
    void *effect_task;
    void *record_task;
} Payload08112A60;

extern const u8 data_083A33DC[];
extern void *func_08116480(u8, s16, s16, u8, u8, u16, u16, u8 *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_081164E8(void *);

u32 func_08112A60(void *task, Descriptor08112A60 *descriptor,
                  Payload08112A60 *payload)
{
    switch (descriptor->phase) {
    case 0:
        payload->value = descriptor->value;
        *payload->value = 0;
        break;
    case 1:
        break;
    case 0x100:
        payload->effect_task = func_08116480(1, 120, 104, 6, 7,
                                            894, 893, payload->value, task);
        payload->record_task = func_080DFD8C(data_083A33DC, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        payload->effect_task = func_081164E8(payload->effect_task);
        if (payload->effect_task == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
