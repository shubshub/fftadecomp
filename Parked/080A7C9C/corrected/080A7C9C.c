#include "ffta.h"

struct Child080A7C9C {
    u8 unknown_00[0x1F];
    s8 value_1F;
};

struct Task080A7C9C {
    struct Child080A7C9C *child;
    u8 timer;
    u8 unknown_05[3];
    u16 state;
    u16 depth;
    u16 history[0];
};

extern void func_0809836C(void *object, u16 action, s8 value, u16 option);
extern void func_08141520(u16 value);

/* Complete [0x080A7C9C, 0x080A7D5E): 194 bytes, 78 instructions.
 * Target: 10b5041c2089042857d880000149401800688746b47c0a08c87c0a08de7c0a083e7d0a08527d0a08187d0a0820681f22825604210023f0f74bfb0820207101220ce00d4899f01efc20681f22825603210023f0f73dfb16202071022222816189481c60810904c90b201c0c30401802800420208121e00000130100002079013820710006002818dc002020716089013860810004c00b211c0c310918088820810be020681f22825600210023f0f710fb0320208101e0002000e0012010bc02bc0847
 */
u8 func_080A7C9C(void *task)
{
    struct Task080A7C9C *state = task;

    switch (state->state) {
    case 0:
        func_0809836C(state->child, 4, state->child->value_1F, 0);
        state->timer = 8;
        state->state = 1;
        state->history[state->depth++] = 1;
        state->state = 4;
        break;
    case 1:
        func_08141520(0x113);
        func_0809836C(state->child, 3, state->child->value_1F, 0);
        state->timer = 22;
        state->state = 2;
        state->history[state->depth++] = 2;
        state->state = 4;
        break;
    case 2:
        func_0809836C(state->child, 0, state->child->value_1F, 0);
        state->state = 3;
        break;
    case 3:
        return 0;
    case 4:
        state->timer--;
        if ((s8)state->timer <= 0) {
            state->timer = 0;
            state->depth--;
            state->state = state->history[state->depth];
        }
        break;
    }
    return 1;
}
