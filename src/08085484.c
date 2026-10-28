#include "ffta.h"

typedef struct {
    u8 unknown_00[0x10];
    u8 flags;
    u8 unknown_11[3];
} Control08085484;

typedef struct {
    u8 unknown_00[0x98];
    Control08085484 first;
    Control08085484 second;
    u8 unknown_c0[0x0c];
} Record08085484;

typedef struct {
    u8 unknown_0000[0x2c88];
    Record08085484 records[0];
} State08085484;

extern State08085484 *data_03002818;
extern void func_08017D18(Control08085484 *control, u8 flags);
extern void func_08017E28(Control08085484 *control);

/* 0x08085484 .. 0x08085508: 132 bytes, including literal pools. */
u8 func_08085484(u32 index, u8 flags)
{
    u8 previous = data_03002818->records[index].first.flags;

    func_08017D18(&data_03002818->records[index].first, flags);
    switch (flags) {
    case 0:
    case 1:
        func_08017D18(&data_03002818->records[index].second, 0);
        break;
    case 3: {
        Control08085484 *second;
        u32 record_address;
        u8 current;
        func_08017E28(&data_03002818->records[index].second);
        record_address = index * sizeof(Record08085484) + (u32)data_03002818;
        second = (Control08085484 *)(record_address + 0x2d34);
        current = second->flags;
        func_08017D18(&data_03002818->records[index].second, current);
        break;
    }
    }
    return previous;
}
