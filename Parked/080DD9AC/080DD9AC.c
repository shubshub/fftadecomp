/* Target 0x080DD9AC, 230 bytes:
 * 70b50e1c141c3188012968d0012902dc002908d063e08020400081420cd00130
 * 814248d05be070682060b068a060b08ae071f08aa08052e0a2880420215e0120
 * 4042814202d0002906d03de0206800f0f9fb0006002842d0a079a168c0004218
 * 537801215156012040422568814200d1eb7f1078002806d151881a061216281c
 * 00f07efb06e0518892881b061b16281c00f094fba079a168c0004018c088a080
 * a0790130a0710006000ee479a04216d13088013012e0a2880420215e01204042
 * 814204d0002908d0501ea08007e0206800f0b8fb0006002801d0022030800020
 * 70bc02bc0847
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1F];
    u8 variant;
} SequenceObject;

typedef struct {
    u8 kind;
    s8 variant;
    u16 action;
    u16 option;
    s16 delay;
} SequenceRecord;

typedef struct {
    u16 state;
    u16 unknown_02;
    SequenceObject *object;
    SequenceRecord *sequence;
    u8 unknown_0c[8];
    u16 count;
    s16 delay;
} SequenceDescriptor;

typedef struct {
    SequenceObject *object;
    s16 delay;
    u8 index;
    u8 count;
    SequenceRecord *sequence;
} SequencePayload;

u8 func_080DE1F0(SequenceObject *object);
void func_080DE12C(SequenceObject *object, u16 action, s8 variant);
void func_080DE168(SequenceObject *object, u16 action, u16 option, s8 variant);

u32 func_080DD9AC(void *task, void *descriptor_data, void *payload_data)
{
    SequenceDescriptor *descriptor = descriptor_data;
    SequencePayload *payload = payload_data;

    (void)task;
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
        {
            SequenceRecord *record = &payload->sequence[payload->index];
            s8 variant = record->variant;

            if (variant == -1)
                variant = payload->object->variant;
            if (record->kind == 0)
                func_080DE12C(payload->object, record->action, variant);
            else
                func_080DE168(payload->object, record->action, record->option, variant);
        }
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
