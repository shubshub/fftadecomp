#include "ffta.h"

struct Group0803CDAC {
    u8 unknown_00;
    u8 first;
    u8 second;
    u8 third;
    u8 fourth;
    u8 fifth;
    u8 unknown_06[2];
};

struct Value0803CDAC {
    u8 unknown_00[4];
    u16 value;
    u8 unknown_06[2];
};

struct Value36_0803CDAC {
    u8 unknown_00[4];
    u16 value;
    u8 unknown_06[30];
};

struct Entry0803CDAC {
    u16 index;
    u16 state;
    u16 order;
    u16 unknown_06;
    const void *resource;
    u16 value;
    u8 kind;
    u8 unknown_0f;
    u16 id;
    u16 unknown_12;
};

extern const struct Group0803CDAC data_08391D1C[];
extern const void *const data_085668B0[];
extern const struct Value0803CDAC data_08391B20[];
extern const struct Value36_0803CDAC data_08391A6C[];
extern const struct Value0803CDAC data_08391B48[];
extern const struct Value0803CDAC data_08391B50[];
extern const struct Value0803CDAC data_08391B58[];
extern u32 func_080C9540(u32);

/* Target: [0x0803CDAC, 0x0803CEF8), 332 bytes, 150 instructions. */
void func_0803CDAC(s32 *count, s32 group, struct Entry0803CDAC *entries)
{
    s32 n = *count;
    s32 id;

    id = data_08391D1C[group - 2].first;
    if (id) {
        id--;
        entries[n].index = n;
        entries[n].state = 1;
        entries[n].order = n;
        entries[n].resource = data_085668B0[2];
        entries[n].value = data_08391B20[id].value;
        entries[n].kind = 3;
        entries[n].id = id;
        n++;
    }
    id = data_08391D1C[group - 2].second;
    if (id) {
        id--;
        entries[n].index = n;
        entries[n].state = 1;
        entries[n].order = n;
        entries[n].resource = data_085668B0[3];
        entries[n].value = data_08391A6C[id].value;
        entries[n].kind = 4;
        entries[n].id = id;
        n++;
    }
    id = data_08391D1C[group - 2].third;
    if (id) {
        id--;
        entries[n].index = n;
        entries[n].state = 1;
        entries[n].order = n;
        entries[n].resource = data_085668B0[4];
        entries[n].value = data_08391B48[id].value;
        entries[n].kind = 5;
        entries[n].id = id;
        n++;
    }
    id = data_08391D1C[group - 2].fourth;
    if (id && (u8)func_080C9540(0x5a8)) {
        id--;
        entries[n].index = n;
        entries[n].state = 1;
        entries[n].order = n;
        entries[n].resource = data_085668B0[5];
        entries[n].value = data_08391B50[id].value;
        entries[n].kind = 6;
        entries[n].id = id;
        n++;
    }
    id = data_08391D1C[group - 2].fifth;
    if (id) {
        id--;
        entries[n].index = n;
        entries[n].state = 1;
        entries[n].order = n;
        entries[n].resource = data_085668B0[6];
        entries[n].value = data_08391B58[id].value;
        entries[n].kind = 7;
        entries[n].id = id;
        n++;
    }
    *count = n;
}
