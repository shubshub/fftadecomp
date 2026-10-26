#include "ffta.h"

/* 0x080A88FC..0x080A892E: 50 bytes, 25 instructions. */
typedef struct {
    void *object;
    u8 unknown_04[0x28];
} ObjectRecord;

typedef struct {
    u8 unknown_00[0x20];
    ObjectRecord records[15];
    u8 unknown_2B4[0x0C];
    u8 count;
} ObjectRecordList;

ObjectRecord *func_080A88FC(ObjectRecordList *list, void *object)
{
    s32 i;

    for (i = 0; i < list->count; i++) {
        ObjectRecord *record = &list->records[i];
        if (record->object == object) {
            return record;
        }
    }
    return 0;
}
