#ifndef FFTA_080D1C94_H
#define FFTA_080D1C94_H

#include "ffta.h"

typedef struct Node {
    u8 *data;
    struct Node *previous;
    struct Node *next;
} Node;

typedef struct {
    u8 unknown_00[0x28C8];
    Node *head;
    u8 unknown_28CC[0x135F];
    u8 step;
} CountdownState;

extern u8 g_state_02000000[];
extern const u8 g_table_0855AE4C[][70];

u8 func_080C9540(u16 bitIndex);

static inline u8 identifier_in_excluded_range(u16 identifier)
{
    return (u16)(identifier - 0x150) <= 0x16;
}

static inline u8 record_countdown(const u8 *data)
{
    return (data[1] >> 2) | ((data[2] & 3) << 6);
}

static inline void set_record_countdown(u8 *data, u16 remaining)
{
    data[1] = (data[1] & 3) | ((remaining & 0x3F) << 2);
    data[2] = (data[2] & 0xFC) | ((remaining >> 6) & 3);
}

static inline u8 advance_countdown(u8 *data, u8 mode, u8 advance)
{
    switch (mode) {
    case 1:
        if (advance != 0 && record_countdown(data) != 0) {
            set_record_countdown(data, record_countdown(data) - 1);
            if (record_countdown(data) == 0)
                return 1;
        }
        break;
    case 2:
        if (func_080C9540(0x45) != 0 && record_countdown(data) != 0) {
            set_record_countdown(data, record_countdown(data) - 1);
            if (record_countdown(data) == 0)
                return 1;
        }
        break;
    case 3:
        if (func_080C9540(0x45) != 0 && record_countdown(data) != 0) {
            u8 remaining = record_countdown(data);
            u8 step = ((CountdownState *)g_state_02000000)->step;

            if (remaining <= step) {
                set_record_countdown(data, 0);
                return 1;
            }
            set_record_countdown(data, remaining - step);
        }
        break;
    }
    return 0;
}

#endif
