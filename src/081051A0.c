#include "ffta.h"

/* Complete [0x081051A0, 0x0810522A): 138 bytes, including literal pool. */
typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    u32 code;
    u32 unknown_0C[2];
    u16 unknown_14;
    u16 option;
    u32 unknown_18;
} Event;

typedef struct {
    u8 kind;
    u8 unknown_01;
    u16 code;
    u8 option;
    u8 unknown_05[3];
    void *child;
    void *object;
} Work;

typedef struct {
    u32 unknown_00;
    void *object;
    u32 first;
    u32 second;
    u32 unknown_10;
    u16 kind;
    u16 option;
    u32 unknown_18;
} ChildRequest;

typedef int (*TaskCallback)(void *, void *, void *);
extern int func_080F082C(void *, void *, void *);
extern void *func_08005B6C(TaskCallback, u16, void *, void *);
extern void func_080D38B4(void);
extern void *func_080E051C(void *);

u32 func_081051A0(void *parent, Event *event, Work *work)
{
    switch (event->phase) {
    case 0:
        work->code = event->code;
        work->kind = event->code - 0x42;
        work->option = event->option;
        work->object = event->object;
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100: {
        ChildRequest request;

        request.kind = work->code;
        request.option = work->option;
        request.object = work->object;
        request.first = 0;
        request.second = 0;
        work->child = func_08005B6C(func_080F082C, 0x34, &request, parent);
        event->phase++;
        break;
    }
    case 0x101:
        work->child = func_080E051C(work->child);
        if (work->child == 0)
            event->phase = 2;
        break;
    }
    return 0;
}
