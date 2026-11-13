#include "ffta.h"

// Target: complete [0x080EE4FC, 0x080EE6E2), 486 bytes.

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *primary;
    u8 unknown_08[14];
    u16 flag;
} Descriptor080EE4FC;

typedef struct {
    u16 unknown_00;
    s16 x;
    s16 y;
    u8 unknown_06;
    u8 flag;
    void *entity;
    void *auxiliary;
    u8 unknown_10[16];
    void *effect;
    u8 unknown_24[12];
    void *extra_effect;
    void *stage;
    void *variant;
    void *primary;
    void *animation;
    void *result;
} Payload080EE4FC;

typedef struct {
    u8 unknown_00[20];
} AnimationEntry080EE4FC;

extern const u8 data_083996FC[], data_0839972C[], data_0839978C[];
extern const AnimationEntry080EE4FC data_083997D4[];
extern const u8 data_083997FC[];
extern const u8 data_08149D08[];
extern void *func_081443FC(void *destination, const void *source, u32 bytes);
extern void *func_080E03F8(void *, const void *, u8, u8, const s16 *, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, s16 *);
extern void *func_080EEEF0(u8, void *, void *);
extern void *func_080EEE50(void *, u8, void *);
extern u8 func_080DD494(const void *);
extern void *func_080EEF6C(void *);
extern u8 func_080EEF30(void *);
extern u8 func_080DD5EC(void *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, s16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

u32 func_080EE4FC(void *task, Descriptor080EE4FC *descriptor,
                  Payload080EE4FC *payload)
{
    void *primary;
    u8 mode;
    u8 delays[2];
    u8 variant;
    u8 count;

    switch (descriptor->phase) {
    case 0:
        payload->flag = descriptor->flag;
        primary = descriptor->primary;
        payload->primary = primary;
        mode = 4;
        if (payload->flag)
            mode = 0;
        payload->stage = func_080E03F8(primary, data_083996FC, mode, 1, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->stage = func_080E05DC(payload->stage);
        if (payload->stage)
            break;
        payload->entity = func_080DD4A4(payload->primary, 0);
        payload->auxiliary = func_080DD748(payload->entity,
                                         &payload->x, &payload->y, 0);
        if (payload->flag) {
            descriptor->phase = 0x102;
        } else {
            payload->stage = func_080EEEF0(4, payload->primary, task);
            descriptor->phase++;
        }
        break;
    case 0x101:
        payload->stage = func_080E05DC(payload->stage);
        if (payload->stage)
            break;
        payload->variant = func_080EEE50(payload->primary, 4, task);
        descriptor->phase++;
        break;
    case 0x102:
        func_081443FC(delays, data_08149D08, sizeof(delays));
        if (!func_080DD494(payload->primary)) {
            payload->variant = func_080EEF6C(payload->variant);
            if (!payload->variant)
                descriptor->phase = 2;
        } else if (payload->flag || func_080EEF30(payload->variant)) {
            payload->effect = func_080D6098(payload->x, payload->y, 0, 1, 4,
                payload->unknown_10, data_0839972C, task);
            variant = 0;
            if (func_080DD5EC(payload->entity)) {
                payload->extra_effect = func_080D6098(payload->x, payload->y, 0, 1, 3,
                    payload->unknown_24, data_0839978C, task);
                variant = 1;
            }
            payload->animation = func_080DCFE4(payload->entity, &data_083997D4[variant],
                                               12, delays[variant], 10, task, 40);
            count = 1;
            if (variant)
                count = 2;
            payload->result = func_080DFD8C(data_083997FC, count, 4, 0, task);
            descriptor->phase++;
        }
        break;
    case 0x103:
        payload->variant = func_080EEF6C(payload->variant);
        if (payload->variant)
            break;
        payload->effect = func_080D6134(payload->effect);
        if (payload->effect)
            break;
        payload->extra_effect = func_080D6134(payload->extra_effect);
        if (payload->extra_effect)
            break;
        payload->animation = func_080DBA5C(payload->animation);
        if (!payload->animation)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
