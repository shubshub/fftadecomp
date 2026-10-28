#include "ffta.h"

/* 0x080293DC..0x080294B0: 212 bytes. */
typedef struct {
    u16 mode;
    u8 unknown_02[0x12];
    u16 selection;
} MenuEvent;

typedef struct {
    void *owner;
    u32 timer;
    u8 selection;
    u8 unknown_09[0x4F];
    u8 animation;
} MenuWork;

typedef struct {
    u8 unknown_00[2];
    u8 ready;
} MenuState;

extern u8 data_02003CB0[];
extern const u8 data_08418F14[];
extern MenuState *data_0200F438;
extern void func_0800543C(void *, const void *);
extern void func_080280F4(MenuWork *);
extern void func_08141540(u32);
extern u8 func_080292A0(MenuWork *);
extern void func_080292E0(MenuWork *);
extern u8 func_08029350(MenuWork *);
extern void func_08017C68(void *);

int func_080293DC(void *owner, MenuEvent *event, MenuWork *work)
{
    switch (event->mode) {
    case 0:
        work->owner = owner;
        work->timer = 0;
        work->selection = event->selection;
        func_0800543C(data_02003CB0, data_08418F14);
        break;
    case 1:
        break;
    case 0x100:
        func_080280F4(work);
        func_08141540(0x65);
        event->mode = 0x101;
        break;
    case 0x104:
        data_0200F438->ready = 1;
        event->mode = 3;
        break;
    case 0x101:
        if (func_080292A0(work))
            event->mode = 0x102;
        func_080292E0(work);
        break;
    case 0x103:
        func_080292E0(work);
        event->mode = 0x104;
        break;
    case 0x102:
        if (func_08029350(work))
            event->mode = 0x103;
        func_08017C68(&work->animation);
        func_080292E0(work);
        break;
    }
    return 0;
}
