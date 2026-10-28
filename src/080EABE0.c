#include "ffta.h"

/* Target 0x080EABE0, complete [0x080EABE0, 0x080EAD88), 424 bytes:
 * f0b54f464646c0b484b0161c098801290cd0012902dc002905d0b0e080204000814209d0abe00220f080a8e0301c08301e21ebf7aff9a2e070881d284cd80027082080198046524989465248f9000d186888338898423ad140461e21ebf7b2f9041c2404240c297804202a5e06202b5e494800900620019001200290002003904648ebf72df824042414a2004346991808601419a400803433190832b2181a600421685e000258600621685e000298606878800048440021405ed8606878800048440221405e1861708801307080781c0006070e1d2fb8d930791cf7c7fe000400150004000c8046b0793379c01830710027b06800283fd0b8008446c0198000803033185a68d86812185a6099681869091899601202120c09020c0c3088000a10180004020c0014ef2802dd1c4858601c4a200400149f2802dd19489860194c351c08356146681800681104091443461a04121489180904091422041214002325f748fd781c0006070e1d2f04d8b800281800680028bfd1308801303080002004b018bc9846a146f0bc02bc08470000688d3908788c3908f903000074714f0800f8fffff8ff0000
 */

typedef struct {
    u16 phase;
} Descriptor080EABE0;

typedef struct {
    u8 kind;
    u8 velocity;
    u16 time;
    s16 x;
    s16 y;
} Event080EABE0;

typedef struct {
    s16 x;
    s16 y;
} Velocity080EABE0;

typedef struct {
    void **slot;
    u32 position_x;
    u32 position_y;
    s32 velocity_x;
    s32 velocity_y;
} Motion080EABE0;

typedef struct {
    u16 counter;
    u16 created;
    u8 angle;
    u8 unknown_05;
    u16 step;
    void *slots[30];
    Motion080EABE0 motion[30];
} Payload080EABE0;

extern void func_080D5F74(void **slots, u16 count);
extern s16 func_080D5FA4(void **slots, u16 count);
extern void *func_080D5CC0(const void *resource, u16 kind, s16 x, s16 y,
                          s16 value, u8 first, u8 second, u8 third);
extern s32 func_08007A4C(u8 angle);
extern void func_080107D4(void *object, s16 x, s16 y, s16 z);
extern const Event080EABE0 g_table_08398C78[];
extern const Velocity080EABE0 g_table_08398D68[];

u32 func_080EABE0(void *task, Descriptor080EABE0 *descriptor,
                  Payload080EABE0 *payload)
{
    const Event080EABE0 *event;
    const Event080EABE0 *events;
    const Velocity080EABE0 *velocity;
    Motion080EABE0 *motion;
    u8 index;
    u16 slot;
    u16 trig_offset;
    u16 x;
    u16 y;
    void *object;
    s32 screen_x;

    switch (descriptor->phase) {
    case 0:
        payload->step = 2;
        break;
    case 1:
        func_080D5F74(payload->slots, 30);
        break;
    case 0x100:
        if (payload->created < 30) {
            index = 0;
            do {
                events = g_table_08398C78;
                event = &events[index];
                if (event->time == payload->counter) {
                    slot = func_080D5FA4(payload->slots, 30);
                    payload->slots[(s16)slot] = func_080D5CC0(
                        (const void *)0x084F7174, event->kind, event->x,
                        event->y, 0x3F9, 6, 1, 0);
                    motion = &payload->motion[(s16)slot];
                    motion->slot = &payload->slots[(s16)slot];
                    motion->position_x = event->x * 256;
                    motion->position_y = event->y * 256;
                    velocity = &g_table_08398D68[event->velocity];
                    motion->velocity_x = velocity->x;
                    velocity = &g_table_08398D68[event->velocity];
                    motion->velocity_y = velocity->y;
                    payload->created++;
                }
                index++;
            } while (index < 30);
        }
        trig_offset = (s16)func_08007A4C(payload->angle) >> 4;
        payload->angle += payload->step;
        for (index = 0; index < 30 && payload->slots[index] != 0; index++) {
            motion = &payload->motion[index];
            motion->position_x += motion->velocity_x;
            motion->position_y += motion->velocity_y;
            x = motion->position_x >> 8;
            y = motion->position_y >> 8;
            x += payload->counter >> 8;
            if ((s16)x > 239) {
                motion->position_x = -2048;
                x = -8;
            }
            if ((s16)y > 159) {
                motion->position_y = -2048;
                y = -8;
            }
            object = payload->slots[index];
            screen_x = (s16)x + (s16)trig_offset;
            func_080107D4(object, screen_x, (s16)y, 0);
        }
        payload->counter++;
        break;
    }
    return 0;
}
