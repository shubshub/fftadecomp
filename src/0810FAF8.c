// 0x0810FAF8: complete 256-byte function, including the literal pool.
// 70b581b0051c0c1c161c21888020400081422fd0814202dc002909d069e00348814240d0
// 013081424ed062e001010000a08a7080e08ab0806068f0600ef7b6fb6d4601356846291c
// 0ef766fd68460078f3f62efd064c2188014321802878f3f627fd2188014321801e203080
// 41e00000400900033088013830800004002838d10221705e0422b15e0ef72efd0bf778fe
// f06805f09fffc3f7b9fec0300ef790f82088013024e00748291cc4f77bf9b06000201e21
// 2a1cd0f7dbf870612088013016e00000f42d3a087069d0f789f9706100280ed1b068c4f7
// 9bf9b060002808d10320f3f6e5fc054a11888143118002202080002001b070bc02bc0847
// 40090003
#include "control_flags.h"

typedef struct Effect {
    u16 timer;
    s16 x;
    s16 y;
    u16 unknown_06;
    void *sequence_task;
    void *unknown_0c_owner;
    u32 unknown_10;
    void *fade_task;
} Effect;

typedef struct EffectEvent {
    u16 phase;
    u16 unknown_02;
    void *object;
    u8 unknown_08[0xc];
    u16 x;
    u16 y;
} EffectEvent;

extern const u8 data_083A2DF4[];
extern void func_0801E2A4(void);
extern void func_0801E610(u8 *first, u8 *second);
extern u16 func_080035A8(u8 index);
extern void func_0801E5E0(s16 x, s16 y);
extern void func_0801B878(void);
extern void func_08115ACC(void *object);
extern void *func_080D3904(void);
extern void func_0801DCB8(u32);
extern void *func_080D3E9C(const void *sequence, void *parent);
extern void *func_080DFD68(u8 direction, s16 duration, void *parent);
extern void *func_080DFED8(void *task);
extern void *func_080D3F08(void *object);

int func_0810FAF8(void *owner, EffectEvent *event, Effect *effect)
{
    u8 first;
    u8 second;

    switch (event->phase) {
    case 0:
        effect->x = event->x;
        effect->y = event->y;
        effect->unknown_0c_owner = event->object;
        func_0801E2A4();
        func_0801E610(&first, &second);
        g_control_flags_03000940.display |= func_080035A8(first);
        g_control_flags_03000940.display |= func_080035A8(second);
        effect->timer = 30;
        break;
    case 0x100:
        effect->timer--;
        if (effect->timer == 0) {
            func_0801E5E0(effect->x, effect->y);
            func_0801B878();
            func_08115ACC(effect->unknown_0c_owner);
            func_0801DCB8((u32)func_080D3904() + 0xc0);
            event->phase++;
        }
        break;
    case 0x101:
        effect->sequence_task = func_080D3E9C(data_083A2DF4, owner);
        effect->fade_task = func_080DFD68(0, 30, owner);
        event->phase++;
        break;
    case 0x102:
        effect->fade_task = func_080DFED8(effect->fade_task);
        if (effect->fade_task == 0) {
            effect->sequence_task = func_080D3F08(effect->sequence_task);
            if (effect->sequence_task == 0) {
                g_control_flags_03000940.display &= ~func_080035A8(3);
                event->phase = 2;
            }
        }
        break;
    }
    return 0;
}
