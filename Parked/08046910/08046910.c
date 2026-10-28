#include "ffta.h"

/* 0x08046910..0x080469F6: 230 bytes. */
typedef unsigned long long UnlockBits;

typedef struct __attribute__((packed)) {
    u8 unknown_00;
    u16 id;
    u8 result;
    u8 required[8];
} UnlockEntry;

typedef struct __attribute__((packed)) {
    u8 value;
    u8 unknown_01;
} UnlockStat;

typedef struct {
    u8 unknown_00[0x21B6];
    UnlockStat stats[8];
    u8 unknown_21C6[0xA42];
    UnlockBits unlocked;
} UnlockStats;

extern const UnlockEntry data_08528256[64];
extern UnlockStats g_state_02000000;

u16 func_08046910(u8 *result)
{
    UnlockBits *flags = &g_state_02000000.unlocked;
    UnlockBits mask = 1;
    s32 i = 0;
    s32 found = 0;
    UnlockBits checked = *flags;
    UnlockBits unlocked = *flags;
    const UnlockEntry *entry;

    for (; i < 64; i++) {
        entry = &data_08528256[i];
        if ((checked & mask) == 0) {
            s32 j = 0;

            found = 0;
            for (; j < 8; j++) {
                if (g_state_02000000.stats[j].value < entry->required[j]) {
                    found = 0;
                    break;
                }
                found = 1;
            }
        }
        if (found)
            break;
        mask <<= 1;
    }
    if (!found) {
        *result = 0;
        return 0;
    }
    *flags = unlocked | ((UnlockBits)1 << i);
    *result = entry->result;
    return entry->id;
}
