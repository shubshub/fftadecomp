#include "ffta.h"

/* 080A92E4..080A93FC, 280 bytes. */
typedef struct {
    u8 unknown_00[0x1D];
    u8 playing;
    u8 unknown_1E[2];
    s16 x, height, z;
    u8 unknown_26[6];
} Effect;

typedef struct {
    u16 active;
    u16 count;
} Counter;

typedef struct {
    u8 unknown_00[0x50];
    void *list;
    Effect effects[32];
    Counter counters[2];
} EffectManager;

extern EffectManager data_0200F9E8;
extern void func_080A8BC4(void *list, Effect *slot, s16 mode, s16 x, s16 height,
                          s16 z, s32 effect, Counter *counters, EffectManager *manager);

static inline Effect *next_at(EffectManager *manager, s16 x, s16 z, int *cursor)
{
    int i;
    for (i = *cursor; i < 32; i++) {
        if (manager->effects[i].playing && manager->effects[i].x == x &&
            manager->effects[i].z == z) {
            *cursor = i + 1;
            return &manager->effects[i];
        }
    }
    return 0;
}

static inline Effect *first_free(void)
{
    EffectManager *manager = &data_0200F9E8;
    int i;
    for (i = 0; i < 32; i++)
        if (!manager->effects[i].playing)
            return &manager->effects[i];
    return 0;
}

void func_080A92E4(s16 mode, s16 x, s16 height, s16 z, s32 effect)
{
    EffectManager *manager = &data_0200F9E8;
    Effect *slot;
    int cursor = 0;
    int i;
    Counter *counter;

    do {
        slot = next_at(manager, x, z, &cursor);
        if (slot)
            height += 8;
    } while (slot);
    slot = first_free();
    if (slot) {
        func_080A8BC4(manager->list, slot, mode, x, height, z, effect,
                      manager->counters, manager);
        counter = manager->counters;
        for (i = 1; i >= 0; i--) {
            if (counter->active)
                counter->count++;
            counter++;
        }
    }
}
