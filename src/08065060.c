#include "ffta.h"

/* Complete [0x08065060, 0x0806514C): 236 bytes, 82 instructions, including
 * the switch table and literal pools.
 * Target:
 *   30b5a0f7cbfd051ce88801380004020c287a0338042865d88000024940180068
 *   87460000885006089c500608c4500608dc500608f85006081451060828681204
 *   9213054bc11889180968044a044c0019136810223be0000024040000bcd43608
 *   3c0a0000296810048013034a891809180868008837e000002404000029681004
 *   8013044bc91809180868007880214902084328e024040000296810048013044a
 *   8918091808888021890208431be0000024040000286812049213074bc1188918
 *   0968064b064c0019842252001b68ddf08ff82868001906e024040000bcd43608
 *   4c0a0000002030bc02bc0847
 */

typedef struct {
    u8 unknown_00[0x424];
    void *entries[0];
} PointerContainer;

typedef struct {
    PointerContainer *container;
    u8 unknown_04[2];
    u16 count;
    u8 kind;
} TaskPayload;

typedef void (*BufferCopier)(void *destination, const void *source, u32 size);

extern BufferCopier data_0836D4BC;
void *func_08005BFC(void *task);

u32 func_08065060(void *task)
{
    const TaskPayload *payload = func_08005BFC(task);
    u16 index = payload->count - 1;

    switch (payload->kind) {
    case 3: {
        /* The ROM loads the slot (0x080650A8) before the copier and the
           destination (0x080650AA-0x080650B0). */
        void *source = payload->container->entries[(s16)index];

        data_0836D4BC((u8 *)payload->container + 0xA3C, source, 0x10);
        return (u32)((u8 *)payload->container + 0xA3C);
    }
    case 4:
        return *(u16 *)payload->container->entries[(s16)index];
    case 5:
        return *(u8 *)payload->container->entries[(s16)index] | 0x10000;
    case 6:
        /* The slot value itself, truncated: 0x080650F8-0x08065102 form
           (container + 0x424) + index * 4 as for the pointer loads, and
           0x08065104 reads the low half with ldrh. */
        return (u16)(u32)payload->container->entries[(s16)index] | 0x20000;
    case 7: {
        /* As case 3: the slot (0x08065120) before the copier and the
           destination (0x08065122-0x0806512C). */
        void *source = payload->container->entries[(s16)index];

        data_0836D4BC((u8 *)payload->container + 0xA4C, source, 0x108);
        return (u32)((u8 *)payload->container + 0xA4C);
    }
    default:
        return 0;
    }
}
