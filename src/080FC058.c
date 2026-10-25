#include "ffta.h"

/* Target 0x080FC058, complete [0x080FC058, 0x080FC13A), 226 bytes. */

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    u32 unknown_08;
    u32 unknown_0C;
    u32 unknown_10;
    u16 selector;
} Descriptor080FC058;

typedef struct {
    u8 selector;
    u8 unknown_01;
    s16 x;
    s16 y;
    u16 unknown_06;
    void *object;
    void *coordinate_result;
    u32 unknown_10;
    u32 unknown_14;
    void *coordinate_child;
    void *effect_child;
    void *record_child;
} Payload080FC058;

struct Data080FC058;
extern const struct Data080FC058 data_0839D288;
extern const struct Data080FC058 data_0839D2B8;
extern const struct Data080FC058 data_0839D2E0;
extern void *func_080DD748(void *, s16 *, s16 *, u32);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, s16, s16, void *, s16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

u32 func_080FC058(void *task, Descriptor080FC058 *descriptor,
                  Payload080FC058 *payload)
{
    u16 flags;

    switch (descriptor->phase) {
    case 0:
        payload->selector = descriptor->selector;
        payload->object = descriptor->object;
        payload->coordinate_result = func_080DD748(payload->object,
            &payload->x, &payload->y, 0);
        break;
    case 1:
        break;
    case 0x100:
        payload->coordinate_child = func_080D6098(payload->x, payload->y,
            0, 1, 2, &payload->unknown_10, &data_0839D288, task);
        flags = (payload->selector & 1) ? 4 : 2;
        payload->effect_child = func_080DCFE4(payload->object,
            &data_0839D2B8, 12, 20, flags, task, 20);
        flags = (payload->selector & 1) ? 16 : 8;
        payload->record_child = func_080DFD8C(&data_0839D2E0,
            1, flags | 4, 0, task);
        descriptor->phase++;
        break;
    case 0x101:
        payload->coordinate_child = func_080D6134(payload->coordinate_child);
        if (payload->coordinate_child != 0)
            break;
        payload->effect_child = func_080DBA5C(payload->effect_child);
        if (payload->effect_child != 0)
            break;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
