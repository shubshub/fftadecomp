#include "ffta.h"

typedef struct {
    u8 option_1 : 1;
    u8 option_2 : 2;
    u8 option_3 : 2;
    u8 unknown_05 : 1;
    u8 option_4 : 1;
    u8 option_6 : 1;
    u8 option_5 : 1;
    u8 option_7 : 1;
    u8 option_8 : 3;
    u8 unknown_0D : 3;
    u8 option_0 : 2;
    u8 unknown_12 : 6;
    u8 unknown_03;
} Settings;

typedef struct {
    u8 unknown_00[0x18];
    u16 field_18;
    u16 field_1A;
} ClampState08017B68;

u16 func_08017B68(ClampState08017B68 *state, u32 index);
int func_080096B0(const void *first, const void *second, int size);
void func_08009920(u8 value);
void *memcpy(void *destination, const void *source, unsigned long size);

/* Target: 0x080094BC, 500 bytes including literals and two switch tables. */
u8 func_080094BC(u8 option, u8 read)
{
    u8 **active = (u8 **)0x02009188;
    u8 *state = *active;
    Settings *settings = (Settings *)(state + 0x1BCC);
    const u8 *defaults = (const u8 *)0x0851BA4E;
    s16 index;
    u8 value;

    if (read) {
        switch (option) {
        case 0:
            return settings->option_0;
        case 1:
            return settings->option_1;
        case 2:
            return settings->option_2;
        case 3:
            return settings->option_3 != 0;
        case 4:
            return settings->option_4;
        case 5:
            return settings->option_5;
        case 6:
            return settings->option_6;
        case 7:
            return settings->option_7;
        case 8:
            return settings->option_8;
        case 9:
            return func_080096B0(settings, defaults, 4) == 0;
        }
    } else {
        index = func_08017B68((ClampState08017B68 *)(state + 0x2F0),
                               *(s8 *)(state + 0x321));
        value = (*active)[0x338 + index * 4];
        switch (option) {
        case 0:
            settings->option_0 = value;
            break;
        case 1:
            settings->option_1 = value;
            break;
        case 2:
            settings->option_2 = value;
            func_08009920(settings->option_2);
            break;
        case 3:
            settings->option_3 = value != 0;
            break;
        case 4:
            settings->option_4 = value != 0;
            break;
        case 5:
            settings->option_5 = value != 0;
            break;
        case 6:
            settings->option_6 = value != 0;
            break;
        case 7:
            settings->option_7 = value != 0;
            break;
        case 8:
            settings->option_8 = value;
            break;
        case 9:
            if (!value)
                return 1;
            memcpy((Settings *)(*active + 0x1BCC), defaults, 4);
            break;
        }
    }
    return 0;
}
