#include "ffta.h"

/* Complete target [0x08126FCC, 0x08127124), 344 bytes:
 * 70b582b00e1c151c31888020400081426cd0814204dc00291cd001290cd094e0044
 * 8814200d183e00230814200d187e08be00000010100000e202856012803dce87b
 * 002800d180e0a868faf7affd0020a8607ae070682860307dfef7a7fa041c6ff7
 * a6fe211c72f795fa6860b068a873f068e873e889012807d1b07dfaf706fea860
 * 8030006828732ae0b07d0e242c57faf7fcfd021c0023201c83420ada011c101c
 * 8030006818180006030e013984320029f5d1611e18060016401a2873287b8000
 * faf769fda860074a297b890012681bf0d6f8a868b17daa7beb7bfff716ff308b
 * 687331e00000b8d43608faf796fd041c6968aa682b7b76f730f869686a7b0420
 * 0090101c0190201c032376f758fc687b012805d16968201c022276f776fc04e0
 * 6968201c002276f770fc09483080faf774fd696876f733fc0006002804d12868
 * 0121817103203080002002b070bc02bc084701010000
 */

typedef struct {
    u8 unknown_00[6];
    u8 complete;
} Output08126FCC;

typedef struct {
    u8 x;
    u8 y;
    u8 map_value;
    u8 unknown_03;
} Coordinate08126FCC;

typedef struct {
    Coordinate08126FCC entries[32];
    s32 count;
} CoordinateList08126FCC;

typedef struct {
    u16 phase;
    u16 unknown_02;
    Output08126FCC *output;
    u32 list_count;
    u32 reverse;
    u32 unknown_10;
    u8 selector;
    u8 unknown_15;
    u8 list_selector;
    u8 unknown_17;
    u16 setting;
} Descriptor08126FCC;

typedef struct {
    Output08126FCC *output;
    void *object;
    Coordinate08126FCC *coordinates;
    u8 count;
    u8 setting;
    s8 list_count;
    u8 reverse;
} Payload08126FCC;

typedef struct PathState08126FCC PathState08126FCC;
typedef void (*BufferInitializer08126FCC)(void *, u32);

extern BufferInitializer08126FCC g_callbacks_0836D4B8[];
extern void *func_08125578(u8 selector);
extern void *func_08096D7C(void);
extern void *func_08099560(void *context, void *record);
extern CoordinateList08126FCC *func_08121C58(u8 selector);
extern void *func_08121B64(u32 size);
extern void func_08121B78(u8 *object);
extern void func_08126ED8(Coordinate08126FCC *, u8, u8, u8);
extern u32 func_08121BE8(void);
extern void func_0809D128(PathState08126FCC *, void *,
                          const Coordinate08126FCC *, s32);
extern void func_0809D98C(PathState08126FCC *, void *, u16, u16, u16, u16);
extern void func_0809D9D8(PathState08126FCC *, void *, u8);
extern s32 func_0809D96C(const PathState08126FCC *, const void *);

/* The entries func_08126ED8 writes for list_count consecutive lists: every
 * list but the last contributes one entry fewer than its count. */
static inline u8 joined_count(u8 first_selector, s8 list_count)
{
    CoordinateList08126FCC *list = func_08121C58(first_selector);
    u8 total = 0;
    s32 i;

    for (i = 0; i < list_count; i++, list++)
        total += list->count;
    return total - (list_count - 1);
}

u32 func_08126FCC(void *task, Descriptor08126FCC *descriptor,
                  Payload08126FCC *payload)
{
    switch (descriptor->phase) {
    case 1:
        if (payload->list_count > 1 || payload->reverse) {
            func_08121B78((u8 *)payload->coordinates);
            payload->coordinates = 0;
        }
        break;
    case 0: {
        void *record;

        payload->output = descriptor->output;
        record = func_08125578(descriptor->selector);
        payload->object = func_08099560(func_08096D7C(), record);
        payload->list_count = descriptor->list_count;
        payload->reverse = descriptor->reverse;
        if (payload->list_count == 1 && payload->reverse == 0) {
            CoordinateList08126FCC *list =
                func_08121C58(descriptor->list_selector);

            payload->coordinates = list->entries;
            payload->count = list->count;
        } else {
            payload->count = joined_count(descriptor->list_selector,
                                          payload->list_count);
            payload->coordinates = func_08121B64(payload->count * 4);
            g_callbacks_0836D4B8[0](payload->coordinates, payload->count * 4);
            func_08126ED8(payload->coordinates, descriptor->list_selector,
                          payload->list_count, payload->reverse);
        }
        payload->setting = descriptor->setting;
        break;
    }
    case 0x100: {
        PathState08126FCC *state = (PathState08126FCC *)func_08121BE8();

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
        if ((u8)func_0809D96C((PathState08126FCC *)func_08121BE8(),
                              payload->object))
            break;
    case 0x103:
        payload->output->complete = 1;
        descriptor->phase = 3;
        break;
    }
    return 0;
}
