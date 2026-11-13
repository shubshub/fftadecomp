#include "ffta.h"

// func_08092638: complete [0x08092638, 0x08092784), 332 bytes, 125 instructions,
// including a five-entry jump table and literal pools.

typedef struct Unit08092638 Unit08092638;
typedef struct SearchOwner08092638 SearchOwner08092638;

typedef struct {
    Unit08092638 *unit;
} Owner08092638;

typedef struct {
    u16 current;
    u16 depth;
    u16 stack[1];
} Phase08092638;

typedef struct {
    Owner08092638 *owner;
    u8 x;
    u8 z;
    u8 unknown_06[2];
    void *task;
    Phase08092638 phase;
} State08092638;

extern State08092638 data_0200F6A0;

extern Owner08092638 *func_0809961C(SearchOwner08092638 *owner, s8 x, s8 z);
extern void *func_0802D72C(u8 first);
extern void func_0802D704(void *task);
extern void *func_0802B70C(Unit08092638 *unit, u32 flags);
extern u8 func_0802B880(void *task);

static inline u16 CurrentPhase08092638(Phase08092638 *phase)
{
    return phase->current;
}

/* The stack base is read through the global, not the pointer; the ROM
   builds that base as its own value before adding the index. */
static inline void PopPhase08092638(Phase08092638 *phase)
{
    phase->current = data_0200F6A0.phase.stack[--phase->depth];
}

void func_08092638(SearchOwner08092638 *search, u8 x, u8 z)
{
    Owner08092638 *owner;

    switch (CurrentPhase08092638(&data_0200F6A0.phase)) {
    case 0:
        if (x == data_0200F6A0.x && z == data_0200F6A0.z)
            break;
        owner = func_0809961C(search, x, z);
        if (data_0200F6A0.owner == owner)
            break;
        if (owner == 0 && data_0200F6A0.owner != 0) {
            if (data_0200F6A0.task == 0)
                data_0200F6A0.task = func_0802D72C(1);
            func_0802D704(data_0200F6A0.task);
            data_0200F6A0.owner = owner;
        } else {
            data_0200F6A0.owner = owner;
            data_0200F6A0.task = func_0802B70C(owner->unit, 0);
        }
        break;
    case 1:
        if (data_0200F6A0.task == 0)
            data_0200F6A0.task = func_0802D72C(1);
        func_0802D704(data_0200F6A0.task);
        data_0200F6A0.phase.current = 2;
        return;
    case 2:
        if ((func_0802B880(func_0802D72C(1)) & ~0x10) == 3)
            PopPhase08092638(&data_0200F6A0.phase);
        return;
    case 3:
        data_0200F6A0.task = func_0802B70C(data_0200F6A0.owner->unit, 0);
        data_0200F6A0.phase.current = 4;
        return;
    case 4:
        if ((func_0802B880(data_0200F6A0.task) & ~0x10) == 2)
            PopPhase08092638(&data_0200F6A0.phase);
        return;
    }
    data_0200F6A0.x = x;
    data_0200F6A0.z = z;
}
