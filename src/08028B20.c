#include "ffta.h"

typedef struct {
    s16 top;
    s16 row;
} SavedPosition;

typedef struct {
    u8 unknown_00[3];
    u8 active;
    u8 unknown_04[0x440];
    SavedPosition positions[1];
} MenuControl;

typedef struct {
    u8 unknown_00[0x10];
    s16 selection;
    u8 mode;
} WindowOptions;

typedef struct {
    void *task;
    u8 unknown_04[4];
    u8 index;
    u8 unknown_09[3];
    u8 region[0x28];
    u8 unknown_34[0x1E];
    s16 top;
    u8 unknown_54[0x15];
    u8 row;
    u8 unknown_6A[0x16];
    WindowOptions options;
} WindowState;

extern MenuControl *data_0200F438;
extern void func_08017508(void *region, u8 appearance);
extern void func_080253B0(u8 mode, void *task);

/* Complete [0x08028B20, 0x08028B92): 114 bytes, 50 instructions. */
u32 func_08028B20(WindowState *window)
{
    if (data_0200F438->active != 0) {
        SavedPosition *position = &data_0200F438->positions[window->index];
        WindowOptions *options = &window->options;
        u16 selection = position->row + 1;

        if (options->mode != 0 && options->selection == selection) {
            window->top = position->top;
            window->row = position->row;
            func_08017508(window->region, 0x10);
            func_080253B0(window->options.mode, window->task);
            return 1;
        }
        data_0200F438->active = 0;
    }
    return 0;
}
