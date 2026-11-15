#include "ffta.h"

/* Complete [0x080DE918, 0x080DE9DE): 198 bytes, 87 instructions, three literal
 * words in three pools.
 * 70b581b0061c0d1c141c2988012955d0012902dc002908d050e08020400081420bd0
 * 0130814223d048e06868a060a88a01306080e88a207140e060880138608000040028
 * 3ad1a068fef7e6fe0006002807d1a0680549009602220023fff7b4fbe06008202080
 * 2888013026e0f8553908208800281ad001382080000400281dd12179ff291ad00020
 * 002900d0081c002806d0024962f0e0fd10e0000013010000014862f0b1fd09e01301
 * 0000e068fdf749f8e060002801d102202880002001b070bc02bc0847
 */

typedef struct {
    u16 state;
    u16 unknown_02;
    void *object;
    u8 unknown_08[12];
    u16 delay;
    u16 player;
} TaskDescriptor080DE918;

typedef struct {
    u16 countdown;
    u16 delay;
    u8 player;
    u8 unknown_05[3];
    void *object;
    void *effect;
} TaskPayload080DE918;

/* Two 8-byte records in the layout src/080DD9AC.c reads; that is the callback
 * func_080DE0E0 installs, and the count passed below is 2. */
extern const u8 data_083955F8[];

extern u8 func_080DD730(void *object);
extern void *func_080DE0E0(void *, const void *, u8, u16, void *);
extern void func_08141570(s32 player_id, u16 song_id);
extern void func_08141520(u16 value);
extern void *func_080DBA5C(void *task);

u32 func_080DE918(void *task, TaskDescriptor080DE918 *event,
                  TaskPayload080DE918 *state)
{
    switch (event->state) {
    case 0:
        state->object = event->object;
        state->delay = event->delay + 1;
        state->player = event->player;
        break;
    case 1:
        break;
    case 0x100:
        if (--state->delay == 0) {
            if (!func_080DD730(state->object))
                state->effect = func_080DE0E0(state->object, data_083955F8,
                                              2, 0, task);
            state->countdown = 8;
            event->state++;
        }
        break;
    case 0x101:
        if (state->countdown != 0) {
            if (--state->countdown == 0 && state->player != 0xFF) {
                /* The ROM builds the value it tests and passes apart from the
                 * byte it loaded: movs r0, #0; cmp r1, #0; beq; adds r0, r1,
                 * #0; cmp r0, #0 at 0x080DE99E.  The declaration, the test
                 * and the two calls are those of play_completion_sound in
                 * src/080DDC18.c. */
                u8 mode = 0;

                if (state->player != 0)
                    mode = state->player;
                if (mode)
                    func_08141570(mode, 0x113);
                else
                    func_08141520(0x113);
            }
        } else {
            state->effect = func_080DBA5C(state->effect);
            if (state->effect == 0)
                event->state = 2;
        }
        break;
    }
    return 0;
}
