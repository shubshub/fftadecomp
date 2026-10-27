#include "ffta.h"

/* 0x08025F8C..0x08025FDA: 78 bytes, 34 instructions. */
typedef struct {
    u8 unknown_00[0x18];
    void *user;
} AbilityContext;

extern AbilityContext *data_0200F438;
extern u8 func_080CDBB4(void *user);
extern u8 func_080CD95C(void *user);
extern u8 func_080CD560(void *user, u32 status);

u8 func_08025F8C(u8 kind)
{
    if (func_080CDBB4(data_0200F438->user)) {
        return 0;
    }
    if (func_080CD95C(data_0200F438->user)) {
        switch (kind) {
        case 1:
            break;
        case 21:
            return func_080CD560(data_0200F438->user, 26);
        default:
            return 0;
        }
    }
    return 1;
}
