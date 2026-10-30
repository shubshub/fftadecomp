#include "ffta.h"

typedef struct State080BB7AC State080BB7AC;

extern State080BB7AC data_02010130;
extern s32 func_080BB7AC(State080BB7AC *state);

/* 080BC900..080BC914: 00 B5 03 48 FE F7 52 FF 00 06 00 0E 02 BC 08 47 30 01 01 02. */
u8 func_080BC900(void)
{
    return func_080BB7AC(&data_02010130);
}
