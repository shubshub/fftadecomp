#include "ffta.h"

typedef struct {
    u8 first;
    u8 second;
    u8 unknown_02[2];
} Record080BDA30;

extern void *func_081443FC(void *destination, const void *source, u32 size);

/* Complete target: [0x080BDA30, 0x080BDAFA), 202 bytes.
 * Target bytes: f0b557464e464546e0b486b0019002911206100e1b061b0e03930139049100258d424ada000600160590a8000199441820780599431a002b00da5b426278039801060816101a8a46002800da40421a1a0135a846029988452bdaa146a800019d4419261c40460f1a20780599431a002b00da5b42617855462816081a002800da40421d1aaa420fda68464946042286f09dfc4846311c042286f098fc301c6946042286f093fc2a1c04340436013f002fdad1454604988542b7db06b038bc9846a146aa46f0bc01bc0047
 */
void func_080BDA30(Record080BDA30 *records, s32 count, u8 first, u8 second)
{
    s32 index;

    for (index = 0; index < count - 1; index++) {
        s32 first_difference = records[index].first - (s8)first;
        s32 second_difference = records[index].second - (s8)second;
        s32 score;
        s32 later;

        if (first_difference < 0)
            first_difference = -first_difference;
        if (second_difference < 0)
            second_difference = -second_difference;
        score = first_difference - second_difference;

        for (later = index + 1; later < count; later++) {
            s32 next_first = records[later].first - (s8)first;
            s32 next_second = records[later].second - (s8)second;
            s32 next_score;

            if (next_first < 0)
                next_first = -next_first;
            if (next_second < 0)
                next_second = -next_second;
            next_score = next_first - next_second;

            if (score < next_score) {
                Record080BDA30 temporary;

                func_081443FC(&temporary, &records[index], sizeof(temporary));
                func_081443FC(&records[index], &records[later], sizeof(temporary));
                func_081443FC(&records[later], &temporary, sizeof(temporary));
                score = next_score;
            }
        }
    }
}
