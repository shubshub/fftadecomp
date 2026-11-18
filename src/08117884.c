#include "ffta.h"

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    void *object;
    u8 unknown_08[0xE];
    u16 origin;
} Descriptor08117884;

typedef struct {
    u8 unknown_00[4];
    u8 origin;
    u8 ready;
    u8 unknown_06[2];
    void *scheduled_a;
    void *scheduled_b;
    void *actor;
    void *object;
    u8 unknown_18[4];
    void *movement_task;
    void *record_task;
} Payload08117884;

extern const u8 data_083A50DC[];
extern const u8 data_083A50E4[];
extern void *func_080DD47C(void *);
extern void func_080DBDA0(void *, s16 *, s16 *, s16 *);
extern void func_080D8B28(s16, s16);
extern void func_080D38B4(void);
extern u8 func_080D8B4C(void);
extern void func_080DE10C(void *, u16);
extern void *func_080DE4B0(void *, u8 *, u8, u8, u32, u32, u32, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_08005B6C(void *, u16, void *, void *);
extern void *func_080E051C(void *);
extern u8 func_080DE1F0(void *);
extern u32 func_081175D4(void *, void *, void *);
extern u32 func_08117784(void *, void *, void *);

// Complete [0x08117884, 0x081179B2), 302 bytes.
// Target:
// f0b58db0071c0e1c151c31888020400081422cd0814204dc00290bd0012923d080e00348
// 814245d00130814266d079e001010000f08a287170686861c5f7dcfd28616c46123405ab
// 04a9221cc4f766fa04a800887838000400142188603909040914c1f71ff95de0bbf7e2ff
// 5ae0c1f72bf90006040e002c54d128693c21c6f703fc2869691d0094282201920294039701
// 220223c6f7cafde86105480097012104220023c8f730fa28623088013038e0dc503a08
// 6879002834d00d4806ac3021221c3b1ceef610f9a8600a482421221c3b1ceef609f9e860
// 07480097012104220023c8f711fa28623088013019e00000d575110885771108e4503a08
// a868c8f7cbfda86000280dd1e868c8f7c5fde860002807d12869c6f729fc0006002801d0
// 0220308000200db0f0bc02bc0847
u32 func_08117884(void *task, Descriptor08117884 *descriptor,
                  Payload08117884 *payload)
{
    switch (descriptor->phase) {
    case 0: {
        s16 x, y, z;

        void *object;

        payload->origin = descriptor->origin;
        object = descriptor->object;
        payload->object = object;
        payload->actor = func_080DD47C(object);
        func_080DBDA0(payload->actor, &x, &y, &z);
        func_080D8B28(x - 0x78, y - 0x60);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100: {
        u8 busy = func_080D8B4C();

        if (busy == 0) {
            func_080DE10C(payload->actor, 0x3C);
            payload->movement_task = func_080DE4B0(payload->actor,
                &payload->ready, 1, 2, 0, 0x28, 0, task);
            payload->record_task = func_080DFD8C(data_083A50DC, 1, 4, 0, task);
            descriptor->phase = descriptor->phase + 1;
        }
        break;
    }
    case 0x101:
        if (payload->ready != 0) {
            u8 buffer[0x1C];

            payload->scheduled_a = func_08005B6C(func_081175D4, 0x30, buffer,
                                                 task);
            payload->scheduled_b = func_08005B6C(func_08117784, 0x24, buffer,
                                                 task);
            payload->record_task = func_080DFD8C(data_083A50E4, 1, 4, 0, task);
            descriptor->phase = descriptor->phase + 1;
        }
        break;
    case 0x102:
        payload->scheduled_a = func_080E051C(payload->scheduled_a);
        if (payload->scheduled_a == 0) {
            payload->scheduled_b = func_080E051C(payload->scheduled_b);
            if (payload->scheduled_b == 0) {
                if (func_080DE1F0(payload->actor) != 0)
                    descriptor->phase = 2;
            }
        }
        break;
    }
    return 0;
}
