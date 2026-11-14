// Target: complete [0x080F5710, 0x080F5862), 338 bytes: 318 code,
// 16 literal and four internal zero alignment bytes.
#include "ffta.h"

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    void *anchor;
    u32 unknown_0c[2];
    u16 mode;
    u16 delay;
} Descriptor080F5710;

typedef struct {
    u8 mode;
    u8 direction;
    u16 timer;
    s16 x;
    s16 y;
    void *position;
    void *object;
    void *sprite;
    void *script;
    void *anchor;
} Payload080F5710;

extern const u8 data_08502560[];

extern void *func_080DD748(void *object, s16 *x, s16 *y, s16 *z);
extern void func_080D8B5C(void *object, s16 *x, s16 *y);
extern void func_080DBD78(void *source, s16 *x, s16 *y, s16 *z);
extern void *func_080D5CC0(const void *data, u8 id, s16 x, s16 y,
                           u16 priority, u8 layer, u8 first, u8 second);
extern void func_08011118(void *sprite, u8 flip);
extern void *func_080DF9E4(void *object, u16 flags, u16 delay, void *parent);
extern void *func_08011484(void *sprite);
extern void *func_080DBA5C(void *script);

u32 func_080F5710(void *task, Descriptor080F5710 *descriptor,
                  Payload080F5710 *payload)
{
    switch (descriptor->phase) {
    case 0:
        payload->mode = descriptor->mode;
        payload->timer = descriptor->delay + 1;
        payload->object = descriptor->object;
        payload->anchor = descriptor->anchor;
        payload->position = func_080DD748(payload->object, &payload->x,
                                          &payload->y, 0);
        break;
    case 1:
        break;
    case 0x100: {
        u8 ids[4] = {1, 0, 0, 1};
        u8 flips[4] = {1, 0, 1, 0};
        s16 anchor_x, anchor_y;
        s16 target_x, target_y, target_z;

        if (--payload->timer != 0)
            break;
        func_080D8B5C(payload->anchor, &anchor_x, &anchor_y);
        func_080DBD78(payload->position, &target_x, &target_y, &target_z);
        if (anchor_x == target_x) {
            if (anchor_y < target_z)
                payload->direction = 0;
            else
                payload->direction = 2;
        } else if (anchor_x > target_x) {
            payload->direction = 1;
        } else {
            payload->direction = 3;
        }
        payload->sprite = func_080D5CC0(data_08502560, ids[payload->direction],
                                        payload->x, payload->y, 0x3BB, 6, 1, 1);
        func_08011118(payload->sprite, flips[payload->direction]);
        payload->script = func_080DF9E4(payload->object, 2, 0, task);
        descriptor->phase++;
        break;
    }
    case 0x101:
        payload->sprite = func_08011484(payload->sprite);
        if (payload->sprite)
            break;
        payload->script = func_080DBA5C(payload->script);
        if (payload->script)
            break;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
