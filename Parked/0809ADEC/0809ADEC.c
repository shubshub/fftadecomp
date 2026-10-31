#include "ffta.h"

typedef struct {
    u16 start_x;
    u16 start_y;
    u16 end_x;
    u16 end_y;
    s16 delta_x;
    s16 delta_y;
    u16 magnitude_x;
    u16 magnitude_y;
    s16 half_maximum;
    s16 maximum;
    u16 field_14;
} Record0809ADEC;

extern s32 func_081426B8(s32 numerator, s32 denominator);

/* Complete [0x0809ADEC, 0x0809AE82): 150 bytes, 73 instructions.
 * Target: 70b5051c0498059c0904090c1204120c1b041b0c0004000c29806a80ab80e880
 * ac821b041b14090409145b1a2b810004001412041214801a688108202e5e002e00da
 * 76420a216c5e002c00da6442a64201dd6e8200e06c82688a0004401428820821685e
 * 002806d0011c002900da4942a7f02cfc28810a21685e002806d0011c002900da4942
 * a7f021fc6881ae81ec8170bc01bc0047
 */
void func_0809ADEC(Record0809ADEC *record, u16 start_x, u16 start_y,
                   u16 end_x, u16 end_y, u16 value)
{
    s32 magnitude_x;
    s32 magnitude_y;

    record->start_x = start_x;
    record->start_y = start_y;
    record->end_x = end_x;
    record->end_y = end_y;
    record->field_14 = value;
    record->delta_x = (s16)end_x - (s16)start_x;
    record->delta_y = (s16)end_y - (s16)start_y;

    magnitude_x = record->delta_x;
    if (magnitude_x < 0)
        magnitude_x = -magnitude_x;
    magnitude_y = record->delta_y;
    if (magnitude_y < 0)
        magnitude_y = -magnitude_y;

    if (magnitude_x > magnitude_y)
        record->maximum = magnitude_x;
    else
        record->maximum = magnitude_y;
    record->half_maximum = record->maximum >> 1;

    if (record->delta_x != 0)
        record->delta_x = func_081426B8(record->delta_x,
            record->delta_x < 0 ? -record->delta_x : record->delta_x);
    if (record->delta_y != 0)
        record->delta_y = func_081426B8(record->delta_y,
            record->delta_y < 0 ? -record->delta_y : record->delta_y);

    record->magnitude_x = magnitude_x;
    record->magnitude_y = magnitude_y;
}
