#include "ffta.h"

typedef struct {
    u8 unknown_00[0x30];
} SourceRecord;

typedef struct {
    u16 count;
    u8 unknown_02[2];
    SourceRecord *records;
} InitializationHeader;

typedef struct {
    u8 unknown_00[0x108];
} SceneRecord;

void func_080C9644(void *destination, void *source, u8 levelOverride);

s32 func_080CA744(InitializationHeader *header, void *destination, s32 maximum)
{
    SceneRecord *record = destination;
    SourceRecord *source = header->records;
    s32 index = 0;
    s32 initialized = 0;

    while (index < header->count && initialized < maximum) {
        while (record->unknown_00[4] != 0)
            record++;
        func_080C9644(record, source, 0);
        index++;
        source++;
        initialized++;
    }
    return initialized;
}
