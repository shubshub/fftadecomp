#include "ffta.h"

// func_0811872C: complete target [0x0811872C, 0x0811896C), 576 bytes.

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[14];
    u16 mode;
} Event0811872C;

typedef struct {
    u8 unknown_00[6];
    u8 count;
    u8 timer;
    u8 index;
    u8 mode;
    u8 unknown_0A[2];
    u8 ready[12];
    void *children[5];
    void *glow;
    void *banner;
    void *actor;
    void *loading;
    void *objects[5];
    void *overlay;
} State0811872C;

typedef struct {
    u32 unknown_00;
    void *actor;
    u8 *ready;
    u32 unknown_0C[2];
    u16 slot;
    u16 unknown_16;
    u32 unknown_18;
} Request0811872C;

typedef struct {
    u32 unknown_00;
    void *actor;
    u8 *ready;
    u32 unknown_0C[4];
} Banner0811872C;

typedef u32 TaskCallback0811872C(void *, void *, void *);

extern u8 data_083A6068[], data_083A60A4[], data_083A60B8[];
extern u16 data_03003860[];
extern TaskCallback0811872C func_0811836C, func_08118500, func_08118590;
extern void *func_08005B6C(TaskCallback0811872C *, u16, void *, void *);
extern void *func_080E03F8(void *, void *, int, int, int, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080DD494(void *);
extern void func_080D8924(void *, int, int, void *);
extern void *func_080DFD8C(void *, int, int, int, void *);
extern void func_080E0540(void **, int);
extern u8 func_080DBAB8(void **, int);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DCFE4(void *, void *, int, int, int, void *, int);
extern void *func_080E051C(void *);

u32 func_0811872C(void *task, Event0811872C *event, State0811872C *s)
{
    Request0811872C request;
    Banner0811872C banner;
    u8 i;
    int flags;
    void *actor;

    switch (event->phase) {
    case 0:
        s->mode = event->mode;
        actor = event->actor;
        s->actor = actor;
        flags = 5;
        if (s->mode)
            flags = 0;
        s->loading = func_080E03F8(actor, data_083A6068, flags, 1, 0, task);
        data_03003860[0xE2 / 2] = 0x39CE;
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        s->loading = func_080E05DC(s->loading);
        if (s->loading)
            break;
        s->count = func_080DD494(s->actor);
        if (s->mode) {
            s->timer = 1;
            func_080D8924(s->actor, 0, 0x14, task);
            s->timer = 1;
            if (s->count == 0)
                event->phase = 0x105;
            else
                event->phase = 0x104;
        } else {
            event->phase++;
        }
        break;
    case 0x101:
        request.actor = s->actor;
        for (i = 0; i < s->count; i++) {
            request.ready = &s->ready[i];
            request.slot = i;
            s->children[i] = func_08005B6C(func_0811836C, 0x1C, &request, task);
        }
        event->phase++;
        break;
    case 0x102:
        if (s->ready[s->count - 1]) {
            banner.actor = s->actor;
            banner.ready = s->ready;
            s->banner = func_08005B6C(func_08118500, 0x14, &banner, task);
            s->glow = func_08005B6C(func_08118590, 0x3C, &banner, task);
            s->overlay = func_080DFD8C(data_083A60B8, 2, 4, 0, task);
            event->phase++;
        }
        break;
    case 0x103:
        if (s->ready[0]) {
            func_080E0540(s->children, 5);
            s->timer = 30;
            event->phase++;
        }
        break;
    case 0x104:
        func_080DBAB8(s->objects, 5);
        if (--s->timer == 0) {
            void *child = func_080DD4A4(s->actor, s->index);

            flags = (s->index & 1) ? 4 : 2;
            s->objects[s->index] = func_080DCFE4(child, data_083A60A4, 0xC, 0,
                                                 flags | 8, task, 0);
            s->index++;
            if (s->index < s->count)
                s->timer = 40;
            else
                event->phase++;
        }
        break;
    case 0x105:
        s->banner = func_080E051C(s->banner);
        if (s->banner)
            break;
        s->glow = func_080E051C(s->glow);
        if (s->glow)
            break;
        if (func_080DBAB8(s->objects, 5))
            event->phase = 2;
        break;
    }
    return 0;
}
