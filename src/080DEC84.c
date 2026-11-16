#include "ffta.h"

/* Complete target [0x080DEC84, 0x080DEDFA), 374 bytes, 168 instructions:
 * 70b50e1c141c318880204000814224d0814204dc00290dd0012919d0a7e00448814260d00130814200d196e09fe00000
 * 0101000071680868206008792073487960738879a07308892082b08a60828ee021680020c881088289e0608a002805d0
 * 013860820004002800d080e02068fcf7c9ff0006020e207b05282fd880000249401800688746000010ed0d0828ed0d08
 * 38ed0d0848ed0d084eed0d0852ed0d085aed0d0810060016002801d0022809d1607b12e010060016002803d0022801d0
 * 607b0ae0607b208108e0607b05e0607b2081404201e0607b20816081a07be0803088013042e0e0880138e08000040028
 * 07d100212079002800d101212171a07be080238965892079002805d018044042030c28044042050c22680e20115e1804
 * 0014814205d11020115e28040014814201d0d3811582238a1020215e01204042814214d0581e20820004001400280ed1
 * d08110823088013008e0a08a002804d00138a0820004002801d102203080002070bc02bc0847
 * Sibling of func_080DEDFC (src/080DEDFC.c), which shares the descriptor,
 * the six-way selector switch and the object +0x0E/+0x10 halfwords.
 * These offset views do not establish original object types or extents.
 * Incoming R0 is unused; R1 and R2 carry the descriptor and payload.
 */

typedef struct {
    u8 unknown_00[0xE];
    s16 field_0E;
    s16 field_10;
} ObjectState;

typedef struct {
    ObjectState *object;
    u8 selector;
    u8 magnitude;
    u8 period;
    u8 unknown_07;
    s16 cycles;
} InitialRecord;

typedef struct {
    u16 state;
    u16 unknown_02;
    InitialRecord *parameters;
    u8 unknown_08[0xC];
    u16 delay;
} Descriptor;

typedef struct {
    ObjectState *object;
    u8 toggle;
    u8 unknown_05;
    u16 period_countdown;
    s16 component_08;
    s16 component_0A;
    u8 selector;
    u8 magnitude;
    u8 period;
    u8 unknown_0F;
    s16 cycles;
    u16 countdown;
    u16 final_countdown;
} Payload;

extern s8 func_080DBC88(void *object);

u32 func_080DEC84(void *task, Descriptor *descriptor, Payload *payload)
{
    switch (descriptor->state) {
    case 0: {
        InitialRecord *parameters = descriptor->parameters;
        payload->object = parameters->object;
        payload->selector = parameters->selector;
        payload->magnitude = parameters->magnitude;
        payload->period = parameters->period;
        payload->cycles = parameters->cycles;
        payload->countdown = descriptor->delay;
        break;
    }
    case 1: {
        ObjectState *object = payload->object;
        object->field_0E = 0;
        object->field_10 = 0;
        break;
    }
    case 0x100: {
        s8 value;
        if (payload->countdown != 0 && --payload->countdown != 0)
            break;
        value = func_080DBC88(payload->object);
        switch (payload->selector) {
        case 0:
            if (value == 0 || value == 2)
                payload->component_0A = payload->magnitude;
            else
                payload->component_08 = payload->magnitude;
            break;
        case 1:
            if (value == 0 || value == 2)
                payload->component_08 = payload->magnitude;
            else
                payload->component_0A = payload->magnitude;
            break;
        case 2:
            payload->component_08 = payload->magnitude;
            break;
        case 3:
            payload->component_0A = payload->magnitude;
            break;
        case 4:
            payload->component_08 = payload->magnitude;
            payload->component_0A = -payload->magnitude;
            break;
        case 5:
            payload->component_08 = payload->magnitude;
            payload->component_0A = payload->magnitude;
            break;
        }
        payload->period_countdown = payload->period;
        descriptor->state++;
        break;
    }
    case 0x101: {
        ObjectState *object;
        s16 first;
        s16 second;
        if (--payload->period_countdown == 0) {
            payload->toggle = !payload->toggle;
            payload->period_countdown = payload->period;
        }
        first = payload->component_08;
        second = payload->component_0A;
        if (payload->toggle != 0) {
            first = -first;
            second = -second;
        }
        object = payload->object;
        if (object->field_0E != first || object->field_10 != second) {
            object->field_0E = first;
            object->field_10 = second;
        }
        if (payload->cycles != -1 && --payload->cycles == 0) {
            object->field_0E = 0;
            object->field_10 = 0;
            descriptor->state++;
        }
        break;
    }
    case 0x102:
        if (payload->final_countdown != 0 && --payload->final_countdown != 0)
            break;
        descriptor->state = 2;
        break;
    }
    return 0;
}
