// 0x0807D8EC - 128 bytes: 108 of code and a 20-byte literal pool
// (data_03002818 and the offsets 0x1C1A, 0x1BE4, 0x1BEC, 0x1D0C).
//
// Mode 1 is always available.  Otherwise the mode is written into the
// record's mode-2 override, the record's entity is refreshed, and the
// mode-2 range of the record is scanned for a set flag.
#include "ffta.h"

typedef struct {
    u8 unknown_00[6];
    u8 table_index;      /* +0x06 */
    u8 unknown_07;
    u8 entity;           /* +0x08 */
    u8 unknown_09[0x2C];
    u8 override_1;       /* +0x35 */
    u8 override_2;       /* +0x36 */
    u8 override_3;       /* +0x37 */
} Record080CCE60;

typedef struct {
    u8 unknown_00[0x40];
    u8 flags[1];         /* +0x40 */
} Flags0807D8EC;

typedef struct {
    u8 unknown_0000[0x1BE4];
    Record080CCE60 record;        /* +0x1BE4 */
    u8 unknown_1C1C[0xF0];
    Flags0807D8EC *flags;         /* +0x1D0C */
} Context0807D8EC;

extern Context0807D8EC *data_03002818;
u8 func_080C9078(const void *data);
const u8 *func_080CCE60(Record080CCE60 *record, u8 mode, u8 *first, u8 *second);

u32 func_0807D8EC(u8 mode)
{
    u8 first;
    u8 last;
    int index;

    if (mode == 1)
        return 1;

    data_03002818->record.override_2 = mode;
    data_03002818->record.entity = func_080C9078(&data_03002818->record);
    func_080CCE60(&data_03002818->record, 2, &first, &last);

    for (index = first; index <= last; index++) {
        if (data_03002818->flags->flags[index] != 0)
            return 1;
    }
    return 0;
}
