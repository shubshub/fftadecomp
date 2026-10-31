#include "ffta.h"

/* Complete target [0x080DEDFC, 0x080DEF90), 404 bytes, 182 instructions:
 * f0b50f1c141c398801291ad0012902dc002908d0bae080204000814216d0013081425fd0b2e07968086820600879a072
 * 4879e072c888a0810889e081b88a2082a4e021680020c88108829fe0208a002805d0013820820004002800d096e02068
 * fcf714ff0006020ea07a05282ed88000014940180068874678ee0d0890ee0d08a0ee0d08b0ee0d08b6ee0d08baee0d08
 * c2ee0d0810060016002801d0022809d1e07a12e010060016002803d0022801d0e07a0ae0e07ae08008e0e07a05e0e07a
 * e080404201e0e07ae0802081201c14300e21635e0021802201f098fb38880130388053e02668251c1435281c01f0b0fb
 * 281c01f0cffb000600281ed000212079002800d1012121710e22a35e281c0021802201f07bfba2890c20215e01204042
 * 81420ad0501ea08100040014002804d1f08130820220388028e0207d28f788fd000400140622a15e48430002030ca07a
 * 042803d118044042020c00e01a1c2079002805d018044042030c10044042020c0e20315e18040014814205d11020315e
 * 10040014814201d0f38132820020f0bc02bc0847
 * These offset views do not establish original object types or extents.
 * Incoming R0 is unused; R1 and R2 carry the descriptor and payload.
 */

typedef struct {
    u8 unknown_00[0xE];
    s16 field_0E;
    s16 field_10;
    u8 unknown_12[0xD];
    u8 value;
} ObjectState;

typedef struct {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} InterpolationState;

typedef struct {
    ObjectState *object;
    u8 selector;
    u8 magnitude;
    s16 cycles;
    s16 duration;
} InitialRecord;

typedef struct {
    u16 state;
    u16 unknown_02;
    InitialRecord *record;
    u8 unknown_08[0xC];
    u16 countdown;
} Descriptor;

typedef struct {
    ObjectState *object;
    u8 toggle;
    u8 unknown_05;
    s16 component_06;
    s16 component_08;
    u8 selector;
    u8 magnitude;
    s16 cycles;
    s16 duration;
    u16 countdown;
    u8 unknown_12[2];
    InterpolationState interpolation;
} Payload;

extern s8 func_080DBC88(const ObjectState *state);
extern void func_080E0608(InterpolationState *state, s16 start, s16 end,
                         s16 duration);
extern void func_080E064C(InterpolationState *state);
extern u8 func_080E0690(InterpolationState *state);
extern s32 func_08007A4C(u8 index);

u32 func_080DEDFC(void *context, Descriptor *descriptor, Payload *payload)
{
    switch (descriptor->state) {
    case 0: {
        InitialRecord *record = descriptor->record;
        payload->object = record->object;
        payload->selector = record->selector;
        payload->magnitude = record->magnitude;
        payload->cycles = record->cycles;
        payload->duration = record->duration;
        payload->countdown = descriptor->countdown;
        break;
    }
    case 1:
        payload->object->field_0E = 0;
        payload->object->field_10 = 0;
        break;
    case 0x100: {
        u8 value;
        if (payload->countdown != 0 && --payload->countdown != 0)
            break;
        value = (u8)func_080DBC88(payload->object);
        switch (payload->selector) {
        case 0:
            if ((s8)value == 0 || (s8)value == 2)
                payload->component_08 = payload->magnitude;
            else
                payload->component_06 = payload->magnitude;
            break;
        case 1:
            if ((s8)value == 0 || (s8)value == 2)
                payload->component_06 = payload->magnitude;
            else
                payload->component_08 = payload->magnitude;
            break;
        case 2:
            payload->component_06 = payload->magnitude;
            break;
        case 3:
            payload->component_08 = payload->magnitude;
            break;
        case 4:
            payload->component_06 = payload->magnitude;
            payload->component_08 = -payload->magnitude;
            break;
        case 5:
            payload->component_06 = payload->magnitude;
            payload->component_08 = payload->magnitude;
            break;
        }
        func_080E0608(&payload->interpolation, 0, 128, payload->duration);
        descriptor->state++;
        break;
    }
    case 0x101: {
        ObjectState *object = payload->object;
        InterpolationState *interpolation = &payload->interpolation;
        s16 first;
        s16 second;
        func_080E064C(interpolation);
        if (func_080E0690(interpolation) != 0) {
            payload->toggle = !payload->toggle;
            func_080E0608(interpolation, 0, 128, payload->duration);
            if (payload->cycles != -1 && --payload->cycles == 0) {
                object->field_0E = 0;
                object->field_10 = 0;
                descriptor->state = 2;
                break;
            }
        }
        first = ((s16)func_08007A4C((u8)payload->interpolation.current) *
                 payload->component_06) >> 8;
        if (payload->selector == 4)
            second = -first;
        else
            second = first;
        if (payload->toggle != 0) {
            first = -first;
            second = -second;
        }
        if (object->field_0E != first || object->field_10 != second) {
            object->field_0E = first;
            object->field_10 = second;
        }
        break;
    }
    }
    return 0;
}
