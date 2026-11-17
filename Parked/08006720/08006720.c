#include "control_flags.h"

/* Complete [0x08006720, 0x08006878): 344 bytes, 164 instructions, with the
 * literal words at 0x080067CC and 0x0800685C (both 0x03000940) and the zero
 * halfwords at 0x080067CA and 0x0800685A. */

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
    s16 cursor;
} InterpolationPayload;

/* A record's time is a little-endian halfword read a byte at a time, the
 * same reading as read_le16_0801075C (src/0801075C.c). */
static inline u32 record_time(const InterpolationRecord *record)
{
    u32 low = record->time[0];

    return (record->time[1] << 8) | low;
}

u32 func_08006720(void *task, InterpolationEvent *event,
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
        s32 index;
        const InterpolationRecord *current;
        const InterpolationRecord *next;

        for (index = 0; ; index++) {
            current = &payload->records[index];
            next = index + 1 < payload->count ? &payload->records[index + 1] : 0;
            if (next == 0)
                break;
            if (payload->cursor >= (s16)record_time(current)
                && payload->cursor < (s16)record_time(next))
                break;
        }
        if (current != 0) {
            if (next == 0) {
                g_control_flags_03000940.bldalpha_lo = current->first;
                g_control_flags_03000940.bldalpha_hi = current->second;
            } else {
                s32 start = (s16)record_time(current);
                s16 elapsed = payload->cursor - start;
                s32 end = (s16)record_time(next);
                s16 duration = end - start;
                s16 first_delta = next->first - current->first;
                s16 second_delta = next->second - current->second;

                g_control_flags_03000940.bldalpha_lo =
                    current->first + first_delta * elapsed / duration;
                g_control_flags_03000940.bldalpha_hi =
                    current->second + second_delta * elapsed / duration;
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
