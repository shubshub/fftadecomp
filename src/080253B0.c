#include "ffta.h"

typedef struct {
    s16 status;
    u8 unknown_02[2];
    u8 mode;
    u8 unknown_05[0x1B];
    void *manager;
} MenuState;

typedef struct TaskEvent {
    u16 state;
    u8 unknown_02[0x12];
    u16 argument;
    u8 unknown_16[6];
} TaskEvent;

typedef struct NavigationState NavigationState;
typedef u32 (*TaskCallback)(void *, TaskEvent *, NavigationState *);
typedef void (*Copy)(void *, const void *, u32);

extern MenuState *data_0200F438;
extern Copy const data_0836D4BC;
extern u8 data_030039F8[];
extern void *func_08005954(void *manager, TaskCallback callback, u16 size,
                           TaskEvent *descriptor, void *parent);
extern void func_08022B24(void);
extern u8 *func_080CBA84(u32 index);
extern u32 func_08028FF4(void *task, TaskEvent *event, NavigationState *state);
extern u32 func_08028DE0(void *task, TaskEvent *event, NavigationState *state);

void func_080253B0(u8 mode, void *parent)
{
    TaskEvent descriptor;

    data_0200F438->mode = mode;
    data_0200F438->status = 0;
    if (mode == 17) {
        func_08005954(data_0200F438->manager, func_08028FF4, 0xA4, &descriptor, parent);
    } else {
        descriptor.argument = mode - 1;
        func_08022B24();
        data_0836D4BC(data_030039F8, func_080CBA84(12) + 0x18, 2);
        func_08005954(data_0200F438->manager, func_08028DE0, 0xA4, &descriptor, parent);
    }
}
