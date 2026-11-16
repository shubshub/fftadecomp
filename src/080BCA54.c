#include "ffta.h"

/* Complete [0x080BCA54, 0x080BCA74): 32 bytes, 14 instructions:
 * 30b5041c251ce06b002803d065f7f8fe0020e063281c65f7f3fe30bc01bc0047
 */

/* The 0x88-byte state func_080BCA24 allocates and src/080BC4BC.c fills. */
typedef struct {
    void *record;
} Entry080BC4BC;

typedef struct Context080BC4BC Context080BC4BC;

typedef struct {
    Context080BC4BC *context;
    Entry080BC4BC *entries[13];
    u8 unknown_38;
    u8 count;
    u8 unknown_3A[2];
    void *workspace;
    u16 current;
    u16 history_count;
    u16 history[34];
} State080BC4BC;

extern void func_08022854(void *object);

void func_080BCA54(void *context)
{
    /* A typed view of the untyped parameter (func_080BCA40 also takes this
     * object as void *).  The ROM holds the pointer twice: r4 from r0 at
     * 0x080BCA56 for the field accesses, r5 copied from r4 at 0x080BCA58
     * for the final release at 0x080BCA68. */
    State080BC4BC *state = context;

    if (state->workspace) {
        func_08022854(state->workspace);
        state->workspace = 0;
    }
    func_08022854(state);
}
