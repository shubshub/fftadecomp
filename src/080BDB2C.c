#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
} PoolItem;

typedef struct {
    u8 unknown_00[0x500];
    PoolItem items[0x800];
    s16 count;
} ItemPool;

/* 0x080BDB2C..0x080BDB46: 26 bytes. */
PoolItem *func_080BDB2C(ItemPool *pool)
{
    return &pool->items[pool->count++];
}
