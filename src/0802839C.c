#include "ffta.h"

/* Target: complete [0x0802839C, 0x08028434), 152 bytes. */
typedef struct {
    u8 unknown_00[0x28];
} TileRegion;

typedef struct {
    u8 unknown_00[9];
    u8 flags;
} WindowOptions;

typedef struct {
    u32 unknown_00;
    void *task;
    u32 unknown_08;
    TileRegion region;
    u8 unknown_34[0x4c];
    WindowOptions options;
} WindowState;

typedef struct {
    s16 status;
    u8 unknown_02[2];
    u8 mode;
} MenuControl;

extern MenuControl *data_0200F438;
extern u8 func_08017180(TileRegion *region);
extern void func_08005BA8(void *task, u16 state);
extern void *func_0802D72C(u32 value);
extern void func_0802B894(void *dialog, u32 value, u32 mode);

u32 func_0802839C(WindowState *window)
{
    WindowOptions *options = &window->options;

    if (func_08017180(&window->region)) {
        void *task = window->task;

        if (task) {
            if (data_0200F438->status > 0)
                func_08005BA8(task, 0x103);
            else if (data_0200F438->status == -1)
                func_08005BA8(task, 0x107);
        } else if (data_0200F438->status == -1) {
            data_0200F438->mode = 0;
        }
        return 1;
    }
    if ((options->flags & 0x10) && data_0200F438->status <= 0)
        func_0802B894(func_0802D72C(1), 1, 0);
    return 0;
}
