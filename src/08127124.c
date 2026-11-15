#include "ffta.h"

typedef struct {
    u8 unknown_00[6];
    u8 complete;
} Output08127124;

typedef struct {
    u8 x;
    u8 y;
    u8 map_value;
    u8 unknown_03;
} Coordinate08127124;

typedef struct {
    u16 phase;
    u16 unknown_02;
    Output08127124 *output;
    u32 reverse;
    u32 unknown_0C;
    u32 unknown_10;
    u8 selector;
    u8 unknown_15;
    u16 path;
    u16 setting;
} Descriptor08127124;

typedef struct {
    Output08127124 *output;
    void *object;
    Coordinate08127124 *coordinates;
    u8 count;
    u8 setting;
    u8 unknown_0E;
    u8 reverse;
} Payload08127124;

typedef struct PathState08127124 PathState08127124;
typedef void (*BufferInitializer08127124)(void *, u32);

extern BufferInitializer08127124 g_callbacks_0836D4B8[];
extern void *func_08125578(u8 selector);
extern void *func_08096D7C(void);
extern void *func_08099560(void *context, void *record);
extern u8 func_08124DF0(u16 path, u8 selection);
extern void *func_08121B64(u32 size);
extern void func_08121B78(u8 *object);
extern void func_08126ED8(Coordinate08127124 *, u8, u8, u8);
extern u32 func_08121BE8(void);
extern void func_0809D128(PathState08127124 *, void *,
                          const Coordinate08127124 *, s32);
extern void func_0809D98C(PathState08127124 *, void *, u16, u16, u16, u16);
extern void func_0809D9D8(PathState08127124 *, void *, u8);
extern s32 func_0809D96C(const PathState08127124 *, const void *);

/* Complete [0x08127124, 0x08127228): 260 bytes. */
u32 func_08127124(void *task, Descriptor08127124 *descriptor,
                  Payload08127124 *payload)
{
    switch (descriptor->phase) {
    case 1:
        if (payload->coordinates) {
            func_08121B78((u8 *)payload->coordinates);
            payload->coordinates = 0;
        }
        break;
    case 0: {
        void *record;

        payload->output = descriptor->output;
        record = func_08125578(descriptor->selector);
        payload->object = func_08099560(func_08096D7C(), record);
        payload->reverse = descriptor->reverse;
        payload->count = func_08124DF0(descriptor->path, 15);
        payload->coordinates = func_08121B64(payload->count * 4);
        g_callbacks_0836D4B8[0](payload->coordinates, payload->count * 4);
        func_08126ED8(payload->coordinates, 15, 1, payload->reverse);
        payload->setting = descriptor->setting;
        break;
    }
    case 0x100: {
        PathState08127124 *state = (PathState08127124 *)func_08121BE8();

        func_0809D128(state, payload->object, payload->coordinates,
                      payload->count);
        func_0809D98C(state, payload->object, payload->setting,
                      3, 4, payload->setting);
        if (payload->setting == 1)
            func_0809D9D8(state, payload->object, 2);
        else
            func_0809D9D8(state, payload->object, 0);
        descriptor->phase = 0x101;
    }
    case 0x101:
        if ((u8)func_0809D96C((PathState08127124 *)func_08121BE8(),
                              payload->object))
            break;
    case 0x103:
        payload->output->complete = 1;
        descriptor->phase = 3;
        break;
    }
    return 0;
}
