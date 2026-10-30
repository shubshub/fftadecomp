#include "ffta.h"

typedef struct {
    const void *source;
    s16 x;
    s16 y;
    s16 offset_x;
    s16 offset_y;
    u8 value;
    u8 extra;
    s16 timer;
} DrawState0805D948;

typedef struct {
    u8 unknown_00[0x119F];
    u8 enabled;
    u8 unknown_11A0[0x2B0];
    const void *identifier;
    u8 unknown_1454[0x28];
    DrawState0805D948 first;
    DrawState0805D948 second;
} State0805D948;

typedef struct {
    u8 unknown_00[0x12];
    u8 mode;
} Context0805D948;

extern State0805D948 *data_0200F448;
extern Context0805D948 g_state_020020D0;
extern void func_08017FE8(const DrawState0805D948 *state);
extern s32 func_080D2E78(const void *identifier);
extern void func_0805D91C(void);

/* 0x0805D948..0x0805DA10 - 200 bytes including literal pools. */
void func_0805D948(void)
{
    if (data_0200F448->enabled != 0) {
        if (++data_0200F448->first.timer > 5) {
            data_0200F448->first.timer = 0;
            if (++data_0200F448->first.offset_x > 2)
                data_0200F448->first.offset_x = 0;
            if (--data_0200F448->second.offset_x <= -3)
                data_0200F448->second.offset_x = 0;
        }
        func_08017FE8(&data_0200F448->first);
        func_08017FE8(&data_0200F448->second);
        if (g_state_020020D0.mode == 1 &&
            func_080D2E78(data_0200F448->identifier) != 0)
            func_0805D91C();
    } else {
        data_0200F448->first.timer = 0;
        data_0200F448->first.offset_x = 0;
        data_0200F448->second.offset_x = 0;
    }
}
