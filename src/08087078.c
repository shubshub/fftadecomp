typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u8 unknown_00[0x2A];
    u16 counts[5];
} CountRecord;

typedef struct {
    u8 unknown_000[0x1D0C];
    CountRecord *record;
} CountState;

extern CountState *data_03002818;

/* 0x08087078..0x080870A8: 48 bytes, 19 instructions. */
int func_08087078(void)
{
    int sum = 0;
    const u16 *counts = data_03002818->record->counts;
    int i;

    for (i = 0; i < 5; i++)
        sum += counts[i];
    return sum;
}
