#include "ffta.h"

typedef struct ActiveObject08096D88 ActiveObject08096D88;

typedef struct {
    void *context;
    ActiveObject08096D88 *active;
} State08096D88;

extern State08096D88 *data_0200F4A8;

/* Complete [0x08096D88, 0x08096D94): 12 bytes, 4 instructions. */
ActiveObject08096D88 *func_08096D88(void)
{
    return data_0200F4A8->active;
}
