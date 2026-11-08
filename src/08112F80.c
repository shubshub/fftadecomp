#include "ffta.h"

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    void **result;
} Descriptor08112F80;

typedef struct {
    u16 countdown;
    u8 unknown_02[6];
    void **result;
    void *child;
    void *animation;
    void *second_animation;
    void *other;
} Payload08112F80;

extern const u8 data_08505D4C[];
extern const u8 data_083A37A8[];
extern const u8 data_085055D0[];
extern const u8 data_0894BD68[];
extern const u8 data_08949F18[];

extern void *func_080D5CC0(const u8 *, u16, u16, u16, u16, u8, u8, u8);
extern void *func_080DFD8C(const u8 *, u8, u16, u16, void *);
extern void *func_08011484(void *);
extern void *func_080D4704(const u8 *, void *);
extern void *func_080D4724(const u8 *, void *, u16);
extern void *func_080D4774(void *);

u32 func_08112F80(void *task, Descriptor08112F80 *descriptor,
                  Payload08112F80 *payload)
{
    switch (descriptor->phase) {
    case 0:
        payload->result = descriptor->result;
        payload->countdown = 10;
        break;
    case 1:
        break;
    case 0x100:
        if (--payload->countdown == 0) {
            payload->child = func_080D5CC0(data_08505D4C, 1, 120, 112,
                                          0x292, 8, 1, 0);
            payload->other = func_080DFD8C(data_083A37A8, 3, 4, 0, task);
            descriptor->phase++;
        }
        break;
    case 0x101:
        payload->child = func_08011484(payload->child);
        if (payload->child == 0) {
            payload->countdown = 10;
            descriptor->phase++;
        }
        break;
    case 0x102:
        if (--payload->countdown == 0) {
            *payload->result = func_080D5CC0(data_085055D0, 0, 120, 112,
                                            0x298, 6, 1, 0);
            payload->animation = func_080D4704(data_0894BD68, task);
            payload->second_animation = func_080D4724(data_08949F18, task, 70);
            descriptor->phase++;
        }
        break;
    case 0x103:
        payload->animation = func_080D4774(payload->animation);
        if (payload->animation == 0) {
            payload->second_animation = func_080D4774(payload->second_animation);
            if (payload->second_animation == 0)
                descriptor->phase++;
        }
        break;
    case 0x104:
        descriptor->phase = 2;
        break;
    }
    return 0;
}
