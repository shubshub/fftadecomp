#include "ffta.h"

typedef struct {
    u8 unknown_00[0x11];
    u8 active;
    u8 unknown_12[2];
    void *owner;
    void *data;
} PoolEntry;

typedef struct {
    PoolEntry entries[16];
    u8 unknown_1C0[4];
    u16 next;
} EntryPool;

/* 0x080BCA74..0x080BCB2C: 184 bytes. */
PoolEntry *func_080BCA74(EntryPool *pool)
{
    s32 remaining = 16 - pool->next;
    PoolEntry *entry;
    PoolEntry *initial = &pool->entries[pool->next];
    s32 i;
    s32 search_result;
    s16 offset;

    for (i = 0; i < remaining; i++, initial++) {
        if (initial->active == 0 && initial->data == 0 && initial->owner == 0) {
            search_result = i;
            goto initial_search_complete;
        }
    }
    search_result = -1;

initial_search_complete:
    offset = search_result;
    if (offset >= 0) {
        pool->next += offset;
    } else {
        PoolEntry *wrapped = pool->entries;
        s32 j;

        for (j = 0; j < 16; j++, wrapped++) {
            if (wrapped->active == 0 && wrapped->data == 0 && wrapped->owner == 0) {
                search_result = j;
                goto wrapped_search_complete;
            }
        }
        search_result = -1;

wrapped_search_complete:
        offset = search_result;
        if (offset < 0)
            return 0;
        pool->next = offset;
    }
    entry = &pool->entries[pool->next];
    pool->next++;
    if (pool->next > 15)
        pool->next = 0;
    return entry;
}
