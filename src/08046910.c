#include "ffta.h"

/* Complete [0x08046910, 0x080469F6): 230 bytes, 104 instructions, including
 * the five-word literal pool at 0x080469AC.
 * f0b557464e464546e0b485b00090234882460125002600218c4688465146086849680390
 * 049101900291002081461c4f4f4401982840029931400843002817d10023184908789c46
 * 3979884210d31648164942183c1d0120844602320133072b06dce118107809788842f4d2
 * 00218c46604600281cd1eb0f7200191c114368000e1c051c0c2189440120804441463f29
 * cddd61460098017000201ce0082c000256825208b621000200000002b621000001200021
 * 4246fbf021fc039a0243049b0b43504602604360f878009908707978b8780002084305b0
 * 38bc9846a146aa46f0bc02bc0847
 *
 * Finds the first of the 64 twelve-byte records at data_08528256 whose bit
 * in the 64-bit word at g_state_02000000 + 0x2C08 is clear and whose eight
 * required values are each at most slots[1..8][0]. It sets that bit, stores
 * the record's result byte through result and returns its id; when no record
 * qualifies it stores 0 and returns 0.
 */

typedef unsigned long long u64;

typedef struct {
    u8 unknown_00;
    u16 id;
    u8 result;
    u8 required[8];
} __attribute__((packed)) UnlockEntry08046910;

typedef struct {
    u8 unknown_0000[0x21B4];
    u8 slots[16][2];
    u8 unknown_21D4[0xA34];
    u64 unlocked;
} State08046910;

extern const UnlockEntry08046910 data_08528256[64];
extern State08046910 g_state_02000000;

u16 func_08046910(u8 *result)
{
    u64 *flags = &g_state_02000000.unlocked;
    u64 mask = 1;
    s32 found = 0;
    s32 i = 0;
    const UnlockEntry08046910 *entry;
    s32 j;
    u64 bit;

    for (; i < 64; i++) {
        entry = &data_08528256[i];
        if ((*flags & mask) == 0) {
            for (j = 0; j < 8; j++) {
                if (g_state_02000000.slots[j + 1][0] < entry->required[j]) {
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
    bit = (u64)1 << i;
    *flags |= bit;
    *result = entry->result;
    return entry->id;
}
