#include "ffta.h"

/* 0x080DD9AC: complete [0x080DD9AC, 0x080DDA92), 230 bytes, no literal pool.
 * The two zero bytes that follow are alignment outside the function.
 * Target: 70b50e1c141c3188012968d0012902dc002908d063e08020400081420cd00130
 *         814248d05be070682060b068a060b08ae071f08aa08052e0a2880420215e0120
 *         4042814202d0002906d03de0206800f0f9fb0006002842d0a079a168c0004218
 *         537801215156012040422568814200d1eb7f1078002806d151881a061216281c
 *         00f07efb06e0518892881b061b16281c00f094fba079a168c0004018c088a080
 *         a0790130a0710006000ee479a04216d13088013012e0a2880420215e01204042
 *         814204d0002908d0501ea08007e0206800f0b8fb0006002801d0022030800020
 *         70bc02bc0847
 */
/* The object, as src/080DD900.c declares it. */
typedef struct {
    u8 unknown_00[0x1F];
    s8 value;
} Object080DD900;

typedef struct {
    u8 kind;
    s8 value;
    u16 action;
    u16 option;
    s16 delay;
} SequenceRecord;

typedef struct {
    u16 state;
    u8 unknown_02[2];
    Object080DD900 *object;
    const SequenceRecord *sequence;
    u8 unknown_0C[8];
    u16 count;
    s16 delay;
} SequenceDescriptor;

/* The 12-byte payload func_080DE0E0 asks the scheduler for. */
typedef struct {
    Object080DD900 *object;
    s16 delay;
    u8 index;
    u8 count;
    const SequenceRecord *sequence;
} SequencePayload;

extern void func_080DE12C(void *object, u16 action, s8 value);
extern void func_080DE168(void *object, u16 action, u16 option, s8 value);
extern u8 func_080DE1F0(void *object);

u32 func_080DD9AC(void *task, SequenceDescriptor *descriptor,
                  SequencePayload *payload)
{
    s8 value;

    switch (descriptor->state) {
    case 0:
        payload->object = descriptor->object;
        payload->sequence = descriptor->sequence;
        payload->count = descriptor->count;
        payload->delay = descriptor->delay;
        break;
    case 1:
        break;
    case 0x100:
        if (payload->delay == -1) {
            if (!func_080DE1F0(payload->object))
                break;
        } else if (payload->delay != 0) {
            payload->delay--;
            break;
        }
        value = payload->sequence[payload->index].value;
        if (value == -1)
            value = payload->object->value;
        if (payload->sequence[payload->index].kind == 0)
            func_080DE12C(payload->object,
                          payload->sequence[payload->index].action, value);
        else
            func_080DE168(payload->object,
                          payload->sequence[payload->index].action,
                          payload->sequence[payload->index].option, value);
        payload->delay = payload->sequence[payload->index].delay;
        if (++payload->index == payload->count)
            descriptor->state++;
        break;
    case 0x101:
        if (payload->delay == -1) {
            if (!func_080DE1F0(payload->object))
                break;
        } else if (payload->delay != 0) {
            payload->delay--;
            break;
        }
        descriptor->state = 2;
        break;
    }
    return 0;
}
