#include "ffta.h"

/* Target: complete [0x08132EA0, 0x08132EE6), 70 bytes.
 * 70b581b0061c0c1c8020c000eff6c8fc051c211c00f008ff021c1204120c301c
 * 291c6b46fff7b2ff041c2404240c281ceff6c0fc002c01d1002000e0012001b0
 * 70bc02bc0847
 */
typedef struct {
    u8 unknown_00[6];
    u8 category;
    u8 unknown_07[0x39];
    u8 values[256];
} State08132E2C;

typedef struct {
    u32 unknown_00;
    u16 id;
} Item08132E2C;

typedef struct {
    u8 unknown_00[6];
    u8 type;
    u8 unknown_07[0x2d];
    u8 limit;
    u8 unknown_35[11];
    u8 progress[256];
} ProgressRecord;

extern void *func_08022840(u32 size);
extern void func_08022854(u8 *object);
extern u16 func_08132E2C(State08132E2C *state,
                         const Item08132E2C *const *items,
                         s32 count, s32 *selected_index);
extern u16 func_08133CC8(const u8 **output, const ProgressRecord *object);

u8 func_08132EA0(State08132E2C *state, const ProgressRecord *object)
{
    s32 selected_index;
    void *buffer = func_08022840(0x400);
    u16 count = func_08133CC8(buffer, object);
    u16 slot = func_08132E2C(state, buffer, count, &selected_index);

    func_08022854(buffer);
    if (slot != 0)
        return 1;
    return 0;
}
