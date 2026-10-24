/* Target 0x080E0CC4, 468 bytes:
 * f0b5474680b4071c0e1c141c31888020400081421ed0814202dc00290cd0d3e00448814200d183e00130814200d1bde0cae0000001010000b08aa0707068a060211da21dfbf75ef8e0882838e08022202080b9e020880138002520800004002800d0b1e0314b191c4a310878bf200870043108780c2008701a1c423210781f211170013210783f201070181c443002780170191c3b3108780d70013908780d70053108780d700139ff200870013908780d70181c3c3001780570191c413108780d70013908780120404208701888c022d201111c08431880201c0c30002150222423fff72ffc201c1830002150221c23fff728fc082020800120002100223b1cf9f7defe60620020002100223b1cf9f7d7fea062606a0121f8f7e4fea06a0121f8f7e0fe308801304de0000040090003271c0c37381cfff727fc606a0423e15e0623e25ea389f9f719ff20888046002802d00138208037e0251c1835281cfff713fca06a0422a15e0623e25e238bf9f705ff381cfff72afc0006002824d0281cfff724fc000600281ed006490a1c4a321078404610700a880348104008803088013010e040090003ff9f0000606af8f777fe6062002807d1a06af8f771fea062002801d102203080002008bc9846f0bc02bc0847
 */

#include "ffta.h"

typedef struct InterpolationState {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} InterpolationState;

typedef struct TransitionDescriptor {
    u16 phase;
    u16 unknown_02;
    void *object;
    u8 unknown_08[0xC];
    u16 selector;
} TransitionDescriptor;

typedef struct TransitionPayload {
    u16 countdown;
    u8 selector;
    u8 unknown_03;
    s16 x;
    s16 y;
    void *object;
    InterpolationState first;
    InterpolationState second;
    void *first_task;
    void *second_task;
} TransitionPayload;

typedef struct TransitionShadow {
    u16 flags;
    u8 unknown_02[0x38];
    u8 byte_3a;
    u8 byte_3b;
    u8 byte_3c;
    u8 byte_3d;
    u8 byte_3e;
    u8 byte_3f;
    u8 byte_40;
    u8 byte_41;
    u8 byte_42;
    u8 byte_43;
    u8 byte_44;
    u8 unknown_45[5];
    u8 byte_4a;
    u8 unknown_4b[3];
    u8 byte_4e;
} TransitionShadow;

void func_080DBDC8(void *object, s16 *x, s16 *y);
void func_080E0608(InterpolationState *state, s16 start, s16 end, s16 duration);
void func_080E064C(InterpolationState *state);
u8 func_080E0690(InterpolationState *state);
void *func_080DAB84(u8 first, u8 second, u8 third, void *parent);
void func_080D9BA8(void *task, u8 selector);
void func_080DAC40(void *task, s16 x, s16 y, u16 value);
void *func_080D9B64(void *task);

u32 func_080E0CC4(void *task, void *descriptor_pointer, void *payload_pointer)
{
    TransitionDescriptor *descriptor = descriptor_pointer;
    TransitionPayload *payload = payload_pointer;
    TransitionShadow *shadow = (TransitionShadow *)0x03000940;

    switch (descriptor->phase) {
    case 0:
        payload->selector = descriptor->selector;
        payload->object = descriptor->object;
        func_080DBDC8(payload->object, &payload->x, &payload->y);
        payload->y -= 40;
        payload->countdown = 34;
        break;
    case 0x100:
        payload->countdown--;
        if (payload->countdown == 0) {
            shadow->byte_4a = 0xBF;
            shadow->byte_4e = 0x0C;
            shadow->byte_42 = 0x1F;
            shadow->byte_43 = 0x3F;
            shadow->byte_44 = 0x1F;
            shadow->byte_3b = 0;
            shadow->byte_3a = 0;
            shadow->byte_3f = 0;
            shadow->byte_3e = 0xFF;
            shadow->byte_3d = 0;
            shadow->byte_3c = 0;
            shadow->byte_41 = 0;
            shadow->byte_40 = 0xFF;
            shadow->flags |= 0x6000;
            func_080E0608(&payload->first, 0, 80, 36);
            func_080E0608(&payload->second, 0, 80, 28);
            payload->countdown = 8;
            payload->first_task = func_080DAB84(1, 0, 0, task);
            payload->second_task = func_080DAB84(0, 0, 0, task);
            func_080D9BA8(payload->first_task, 1);
            func_080D9BA8(payload->second_task, 1);
            descriptor->phase++;
        }
        break;
    case 0x101:
        func_080E064C(&payload->first);
        func_080DAC40(payload->first_task, payload->x, payload->y, payload->first.current);
        if (payload->countdown != 0) {
            payload->countdown--;
            break;
        }
        func_080E064C(&payload->second);
        func_080DAC40(payload->second_task, payload->x, payload->y, payload->second.current);
        if (func_080E0690(&payload->first) && func_080E0690(&payload->second)) {
            shadow->byte_4a = 0;
            shadow->flags &= 0x9FFF;
            descriptor->phase++;
        }
        break;
    case 0x102:
        payload->first_task = func_080D9B64(payload->first_task);
        if (payload->first_task == 0) {
            payload->second_task = func_080D9B64(payload->second_task);
            if (payload->second_task == 0)
                descriptor->phase = 2;
        }
        break;
    }
    return 0;
}
