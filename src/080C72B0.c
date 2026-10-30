#include "ffta.h"

typedef struct {
    u8 frame;
    u8 flags;
    u8 index;
    u8 requested_index;
    s16 x;
    s16 y;
    s16 offset_x;
    s16 offset_y;
    u8 unknown_0C[0x3C];
    u16 state;
    u8 unknown_4A[0x46];
} Record080C72B0;

typedef struct {
    u8 unknown_00[0xC];
    Record080C72B0 record;
    u8 unknown_9C[0x10];
    u8 mode;
    u8 unknown_AD;
    u8 flags;
    u8 unknown_AF;
    u16 phase;
    u8 unknown_B2[0x46];
} State080C72B0;

extern State080C72B0 data_02015738;
extern void func_080C5908(State080C72B0 *state);
extern u8 func_080C95A8(u16 index);
extern void func_080C586C(Record080C72B0 *record);
extern void func_080C5448(const Record080C72B0 *record);

/* Target [0x080C72B0, 0x080C72E4), 52 complete bytes:
 * 10b50b4c201cfef727fb0d2002f074f90006002809d0a07b0028
 * 06d00c34201cfef7ccfa201cfef7b7f810bc01bc004738570102
 */
void func_080C72B0(void)
{
    State080C72B0 *state = &data_02015738;

    func_080C5908(state);
    if (func_080C95A8(13) && state->record.index != 0) {
        Record080C72B0 *record = &state->record;

        func_080C586C(record);
        func_080C5448(record);
    }
}
