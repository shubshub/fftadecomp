#include "ffta.h"

typedef struct InterpolationRecord {
    u8 time[2];
    u8 first;
    u8 second;
} InterpolationRecord;

typedef struct InterpolationEvent {
    u16 state;
    u8 unknown_02[2];
    const InterpolationRecord *records;
    u8 unknown_08[0xC];
    s16 count;
} InterpolationEvent;

typedef struct InterpolationPayload {
    const InterpolationRecord *records;
    s32 count;
    u8 loop;
    u8 unknown_09;
    u16 cursor;
} InterpolationPayload;

typedef struct TransitionOutput {
    u8 unknown_00[0x4C];
    u8 first;
    u8 second;
} TransitionOutput;

u32 func_08006720(void *unused, InterpolationEvent *event,
                  InterpolationPayload *payload)
{
    switch (event->state) {
    case 0:
        payload->records = event->records;
        payload->count = event->count;
        break;
    case 1:
        break;
    case 0x100:
    {
        const InterpolationRecord *records = payload->records;
        s32 count = payload->count;
        s32 index = 0;
        const InterpolationRecord *current;
        const InterpolationRecord *next;

        for (;;) {
            current = &records[index];
            next = index + 1 < count ? &records[index + 1] : 0;
            if (next == 0)
                break;
            if ((s16)payload->cursor >= (s16)(current->time[0] | current->time[1] << 8)
                && (s16)payload->cursor < (s16)(next->time[0] | next->time[1] << 8))
                break;
            index++;
        }
        if (current != 0) {
            TransitionOutput *output = (TransitionOutput *)0x03000940;

            if (next == 0) {
                output->first = current->first;
                output->second = current->second;
            } else {
                s16 start = current->time[0] | current->time[1] << 8;
                s16 elapsed = payload->cursor - start;
                s16 duration = (s16)(next->time[0] | next->time[1] << 8) - start;
                u8 first = current->first;
                s32 first_delta = next->first - first;
                s16 second_delta = next->second - current->second;

                output->first = first + first_delta * elapsed / duration;
                output->second = current->second + second_delta * elapsed / duration;
            }
        }
        payload->cursor++;
        if (next == 0) {
            if (payload->loop)
                payload->cursor = 0;
            else
                event->state = 2;
        }
        break;
    }
    }
    return 0;
}
