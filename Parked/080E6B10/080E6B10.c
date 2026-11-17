#include "ffta.h"

// Target 0x080E6B10, complete [0x080E6B10, 0x080E6D54): 580 bytes,
// 290 instructions.
typedef struct {
    u16 state;
    u16 unknown_02;
    void *source;
    void *target;
    u8 unknown_0C[8];
    u16 variant;
} Command080E6B10;

typedef struct {
    u8 variant;
    u8 unknown_01;
    s16 step;
    s16 timer;
    s16 xs[60];
    s16 ys[60];
    u8 unknown_F6[2];
    void *path;
    void *source;
    void *target;
    void *beam;
    void *sparks[3];
    void *overlay;
} Work080E6B10;

typedef struct {
    s16 x;
    s16 y;
} Point080E6B10;

extern const u8 data_084FBA40[];
extern const u8 data_08949764[];
extern const u8 data_0894A384[];
extern const u8 data_08149CA0[];

extern void *func_080DD4C4(void *object);
extern void func_080DBDA0(void *entity, s16 *x, s16 *y, s16 *z);
extern void *func_080D62CC(void **beam, Point080E6B10 *from,
                           Point080E6B10 *to, s32 first, s32 second,
                           u32 length, s16 *xs, s16 *ys,
                           u32 flags, void *parent);
extern void *func_080D5DD4(const void *descriptor, u32 mode, s16 x, s16 y,
                           u32 id, u32 priority, u32 flags);
extern void func_0801121C(void *object, s16 value);
extern void *func_080D4704(const void *descriptor, void *parent);
extern u16 func_0801BB0C(s16 x, s16 y, u16 duration);
extern void func_080D5C20(void *path);
extern void *func_080D6530(void *path);
extern void func_08011428(void *object);
extern u8 func_080D5F24(void **objects, u16 count);
extern void *func_080D4774(void *overlay);
extern void *func_081443FC(void *destination, const void *source, u32 bytes);

u32 func_080E6B10(void *parent, Command080E6B10 *command,
                  Work080E6B10 *work)
{
    s16 depths[2];
    s16 x;
    s16 y;
    s16 z;
    Point080E6B10 from;
    Point080E6B10 to;

    switch (command->state) {
    case 0:
        work->variant = command->variant;
        work->source = func_080DD4C4(command->source);
        work->target = func_080DD4C4(command->target);
        break;
    case 1:
        break;
    case 0x100:
        func_080DBDA0(work->source, &from.x, &from.y, &depths[0]);
        func_080DBDA0(work->target, &to.x, &to.y, &depths[1]);
        work->path = func_080D62CC(&work->beam, &from, &to, -28, -28, 0x3C,
                                   work->xs, work->ys, 0, parent);
        work->timer = 0x3E;
        command->state++;
        break;
    case 0x101:
        if (work->timer != 0)
            break;
        work->beam = func_080D5DD4(data_084FBA40, 2, work->xs[0], work->ys[0],
                                   0x3E2, 6, 0);
        func_0801121C(work->beam, 1);
        if (work->variant == 0)
            work->overlay = func_080D4704(data_08949764, parent);
        else
            work->overlay = func_080D4704(data_0894A384, parent);
        func_080DBDA0(work->target, &x, &y, &z);
        func_0801BB0C(x - 0x78, y - 0x60, 0x3C);
        func_080D5C20(work->path);
        work->step = 0;
        command->state++;
        break;
    case 0x102: {
        u8 steps[3];
        u8 i;

        func_081443FC(steps, data_08149CA0, sizeof(steps));
        for (i = 0; i <= 2; i++) {
            if (work->step == steps[i])
                work->sparks[i] = func_080D5DD4(data_084FBA40, 3,
                                                work->xs[work->step],
                                                work->ys[work->step],
                                                0x3E2, 6, 0);
        }
        work->step++;
        work->path = func_080D6530(work->path);
        if (work->path == 0) {
            func_08011428(work->beam);
            work->beam = 0;
            command->state++;
        }
        break;
    }
    case 0x103:
        if (func_080D5F24(work->sparks, 3)) {
            work->overlay = func_080D4774(work->overlay);
            if (work->overlay == 0)
                command->state = 2;
        }
        break;
    }
    if (work->timer != 0)
        work->timer--;
    return 0;
}
