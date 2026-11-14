#include "ffta.h"

// Complete [0x081171CC, 0x0811731E): 338 bytes, 169 instructions.
// Target:
// f0b557464e464546e0b489b082460f1c161c3988012900d192e0012902dc002908d08de0
// 80204000814213d00130814278d085e0b88a3070f88a013070807868f060b968b161311d
// b21d0023c6f796fab06075e0194904a804222df0e9f805ac1749201c04222df0e3f87088
// 013870800004002864d1b06906ad1a2169448946291c4a46c1f784fcb06807ac6a461e32
// 08ab9846211cc4f789fd0020295e0022a05e814210d14b460024195f42460023d05e8142
// 06da00200be000006c9f1408709f1408022004e0814201dd012000e00320707011487178
// 6944103109780424325f0624335f0e4c009406240194012402940394bef7fefc30617178
// 694414310978f9f623fff068022100225346c8f783fb70613888013011e0000060255008
// ae0300003069faf6c7f83061002807d17069c4f7adfb7061002801d102203880002009b0
// 38bc9846a146aa46f0bc02bc0847

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    void *actor;
    void *source;
    u8 unknown_0C[8];
    u16 kind;
    u16 delay;
} Descriptor081171CC;

typedef struct {
    u8 kind;
    u8 direction;
    u16 counter;
    s16 x;
    s16 y;
    void *target;
    void *actor;
    void *sprite;
    void *task;
    void *source;
} Payload081171CC;

extern const u8 data_08502560[];
extern void *func_080DD748(void *target, s16 *x, s16 *y, s16 *z);
extern void func_080D8B5C(void *object, s16 *x, s16 *y);
extern void func_080DBD78(void *source, s16 *tile_x, s16 *tile_y, s16 *tile_z);
extern void *func_080D5CC0(const void *, u16, s16, s16, u16, u8, u8, u32);
extern void func_08011118(void *object, u8 enabled);
extern void *func_080DF9E4(void *, u16, u16, void *);
extern void *func_08011484(void *);
extern void *func_080DBA5C(void *);

u32 func_081171CC(void *task, Descriptor081171CC *descriptor,
                  Payload081171CC *payload)
{
    switch (descriptor->phase) {
    case 0:
        payload->kind = descriptor->kind;
        payload->counter = descriptor->delay + 1;
        payload->actor = descriptor->actor;
        payload->source = descriptor->source;
        payload->target = func_080DD748(payload->actor, &payload->x,
                                        &payload->y, 0);
        break;
    case 1:
        break;
    case 0x100: {
        u8 frames[4] = {1, 1, 0, 0};
        u8 flags[4] = {1, 0, 1, 0};

        if (--payload->counter == 0) {
            s16 x, y;
            s16 tile_x, tile_y, tile_z;

            func_080D8B5C(payload->source, &x, &y);
            func_080DBD78(payload->target, &tile_x, &tile_y, &tile_z);
            if (x == tile_x) {
                if (y < tile_z)
                    payload->direction = 0;
                else
                    payload->direction = 2;
            } else if (x > tile_x) {
                payload->direction = 1;
            } else {
                payload->direction = 3;
            }
            payload->sprite = func_080D5CC0(data_08502560,
                                            frames[payload->direction],
                                            payload->x, payload->y,
                                            0x3AE, 6, 1, 1);
            func_08011118(payload->sprite, flags[payload->direction]);
            payload->task = func_080DF9E4(payload->actor, 2, 0, task);
            descriptor->phase++;
        }
        break;
    }
    case 0x101:
        if (!(payload->sprite = func_08011484(payload->sprite)) &&
            !(payload->task = func_080DBA5C(payload->task)))
            descriptor->phase = 2;
        break;
    }
    return 0;
}
