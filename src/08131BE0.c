#include "ffta.h"

typedef struct {
    u8 unknown_00[0xFD];
    u8 heightMode;
} SceneRecord;

u8 func_0801CC18(u8 column, u8 row);
u8 func_0801CD08(u8 column, u8 row);

s32 func_08131BE0(void *record, s8 x, s8 y)
{
    SceneRecord *sceneRecord = record;
    u8 column = x;
    u8 row = y;
    u8 height = func_0801CC18(column, row);
    u8 flags = func_0801CD08(column, row);

    if (!(flags & 2) || sceneRecord->heightMode != 2)
        return height;
    return height - 1;
}
