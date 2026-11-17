// Target 0x080DF14C, 462 bytes:
// f0b557464e464546e0b489b082460e1c171c318880204000814221d0814202dc00290cd0cae081204000
// 814200d1a7e0814252db0130814200d1b7e0bee07068f860b168f980f1683971b18a3970f18a7970318b
// 01317981fef78ef93861ade07889013878810004050c002d00d0a5e038696a46123205ac04a9231cfcf7
// d6fd3869fcf75bfdb87004a801783878401a0006001622787978891a09060916bef767fa021c38691206
// 12163c21fef798ff38690121fff730f93869f91c01235b4200953c2201920295524603920122fff749f9
// b861308801306fe006a880462449042265f0e5f807a9894622494846042265f0def8f878002860d03869
// 08ac6d462235211c2a1cfcf7b9fd3869fcf716fd194a9446000600164246111800228a562488121912
// 04121448440023c3562d885b191b041b14f888009038790190002002900120039060460021f6f713fd78
// 6138691121fef712f808485146009101210422002300f06cfdf8613088013024e0779b14087b9b1408
// 54f64f0824563908786932f7d9f87861002817d1b869fcf7bffbb861002811d1f86802217956fef759fd
// 0a2038813088013006e03889013838810004002801d102203080002009b038bc9846a146aa46f0bc02bc
// 0847 (literal pool: 08149B77 08149B7B 084FF654 08395624)
#include "ffta.h"

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    u32 palette;
    u32 priority;
    u8 unknown_10[4];
    u16 x;
    u16 y;
    u16 delay;
} Descriptor080DF14C;

typedef struct {
    u8 x;
    u8 y;
    s8 direction;
    u8 flag;
    u8 priority;
    u8 unknown_05;
    u16 palette;
    u16 timer;
    u16 delay;
    void *object;
    void *state;
    void *marker;
    void *child;
    void *effect;
} Payload080DF14C;

extern const s8 data_08149B77[];
extern const s8 data_08149B7B[];
extern const u8 data_084FF654[];
extern const u8 data_08395624[];

extern void *func_081443FC(void *destination, const void *source, u32 bytes);
extern void *func_080DD4C4(void *);
extern void func_080DBD78(void *, s16 *, s16 *, s16 *);
extern void func_080DBDC8(void *, u16 *, u16 *);
extern s8 func_080DBC88(void *);
extern s32 func_0809D6BC(s8 x, s8 y);
extern void func_080DE12C(void *, u16, s8);
extern void func_080DE464(void *, u8);
extern void *func_080DE4B0(void *object, u8 *result, u8 mode, s8 event,
                           s8 repeat_count, u8 delay, u16 initial_delay, void *parent);
extern void *func_080D5CC0(const void *, int, int, int, int, int, int, int);
extern void func_080DD2C8(void *, u8);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_08011484(void *);
extern void *func_080DBA5C(void *);
extern void func_080DDDA0(void *, s8);

u32 func_080DF14C(void *task, Descriptor080DF14C *descriptor, Payload080DF14C *payload)
{

    switch (descriptor->phase) {
    case 0: {
        void *object = descriptor->object;

        payload->object = object;
        payload->palette = descriptor->palette;
        payload->priority = descriptor->priority;
        payload->x = descriptor->x;
        payload->y = descriptor->y;
        payload->delay = descriptor->delay + 1;
        payload->state = func_080DD4C4(object);
        break;
    }
    case 1:
        break;
    case 0x100:
        {
            s16 tile_x, tile_y, tile_z;
            s32 direction;

            payload->delay--;
            if (payload->delay != 0)
                break;
            func_080DBD78(payload->state, &tile_x, &tile_y, &tile_z);
            payload->direction = func_080DBC88(payload->state);
            direction = func_0809D6BC((s8)(payload->x - (u8)tile_x),
                                      (s8)(payload->y - (u8)tile_z));
            func_080DE12C(payload->state, 0x3c, direction);
            func_080DE464(payload->state, 1);
            payload->child = func_080DE4B0(payload->state, &payload->flag, 1, -1,
                                           0, 0x3c, 0, task);
            descriptor->phase++;
        }
        break;
    case 0x101:
        {
            s8 dx[4];
            s8 dy[4];
            u16 sx, sy;
            s8 direction;

            func_081443FC(dx, data_08149B77, 4);
            func_081443FC(dy, data_08149B7B, 4);
            if (payload->flag == 0)
                break;
            func_080DBDC8(payload->state, &sx, &sy);
            direction = func_080DBC88(payload->state);
            payload->marker = func_080D5CC0(data_084FF654, 0,
                                            (s16)(dx[direction] + sx),
                                            (s16)(dy[direction] + sy),
                                            payload->palette, payload->priority, 0, 1);
            func_080DD2C8(payload->state, 0x11);
            payload->effect = func_080DFD8C(data_08395624, 1, 4, 0, task);
            descriptor->phase++;
        }
        break;
    case 0x102:
        payload->marker = func_08011484(payload->marker);
        if (payload->marker != 0)
            break;
        payload->child = func_080DBA5C(payload->child);
        if (payload->child != 0)
            break;
        func_080DDDA0(payload->object, payload->direction);
        payload->timer = 10;
        descriptor->phase++;
        break;
    case 0x103:
        payload->timer--;
        if (payload->timer == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
