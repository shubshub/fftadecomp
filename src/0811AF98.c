// Target: complete [0x0811AF98, 0x0811B1C8), 560 bytes, 218 instructions.
#include "ffta.h"
#include "control_flags.h"

typedef struct {
    u16 phase;
    u8 unknown_02[0x12];
    u8 kind;
} Descriptor0811AF98;

typedef struct {
    u8 unknown_00[2];
    u8 index;
    u8 unknown_03;
    s16 x;
    s16 y;
    void *sprite;
    void *window;
    u8 window_state[0x20];
    void *timeline;
    void *first_overlay;
    void *second_overlay;
    void *startup;
    void *record_task;
} Payload0811AF98;

typedef struct {
    s16 x;
    s16 y;
} Point0811AF98;

typedef struct {
    u8 unknown_00[12];
} Rectangle0811AF98;

extern u16 data_03003860[][16];
extern const u8 data_083A688C[];
extern const u8 data_088F46CC[];
extern const u8 data_083A6988[];
extern const u8 data_0894C744[];
extern const Point0811AF98 data_083A69A4[];
extern const u8 data_083A68C8[];
extern const u8 data_08507828[];
extern const u8 data_083A69B4[];
extern const u8 data_083A699C[];
extern const Rectangle0811AF98 data_083A69B8[];
extern const u8 data_083A6992[];
extern const u8 data_08949F18[];

extern void *func_080D7A70(const void *, u8, void *);
extern void func_080D35D8(void);
extern void *func_080D7ABC(void *);
extern void func_080D7220(const void *, u8, u8, s16, s16, u16);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D4704(const void *, void *);
extern void func_0801C960(s16, s16, s16 *, s16 *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080D5CC0(const void *, u16, s16, s16, u16, u8, u8, u32);
extern void func_08011100(void *, u8);
extern u16 func_080035D0(u8);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D3F08(void *);
extern void func_0801B798(const Rectangle0811AF98 *, u8);
extern void func_0801B878(void);
extern void *func_08011484(void *);
extern void *func_080D4774(void *);
extern void *func_080D6134(void *);
extern u32 func_080035A8(u8);

u32 func_0811AF98(void *task, Descriptor0811AF98 *descriptor,
                  Payload0811AF98 *payload)
{
    switch (descriptor->phase) {
    case 0:
        payload->index = descriptor->kind - 0x6B;
        payload->startup = func_080D7A70(data_083A688C, 5, task);
        data_03003860[6][1] = 0x7FFF;
        break;
    case 1:
        func_080D35D8();
        break;
    case 0x100:
        payload->startup = func_080D7ABC(payload->startup);
        if (payload->startup != 0)
            break;
        func_080D7220(data_088F46CC, 0, 2, 0, 0, 0);
        payload->timeline = func_080D3E9C(data_083A6988, task);
        payload->first_overlay = func_080D4704(data_0894C744, task);
        func_0801C960(data_083A69A4[payload->index].x,
                      data_083A69A4[payload->index].y,
                      &payload->x, &payload->y);
        payload->window = func_080D6098(payload->x, payload->y, 0, 1, 8,
                                        payload->window_state,
                                        data_083A68C8, task);
        payload->sprite = func_080D5CC0(data_08507828,
                                        data_083A69B4[payload->index],
                                        payload->x, payload->y, 0x34C,
                                        0, 0, 0);
        func_08011100(payload->sprite, 2);
        g_control_flags_03000940.winout_lo = 0x3F & ~func_080035D0(2);
        g_control_flags_03000940.winout_hi = 0x3F;
        g_control_flags_03000940.display |= 0x8000;
        payload->record_task = func_080DFD8C(data_083A699C, 1, 4, 0x40, task);
        descriptor->phase++;
        break;
    case 0x101:
        payload->timeline = func_080D3F08(payload->timeline);
        if (payload->timeline != 0)
            break;
        func_0801B798(&data_083A69B8[payload->index], 0);
        func_0801B878();
        payload->timeline = func_080D3E9C(data_083A6992, task);
        payload->second_overlay = func_080D4704(data_08949F18, task);
        descriptor->phase++;
        break;
    case 0x102:
        payload->timeline = func_080D3F08(payload->timeline);
        if (payload->timeline != 0)
            break;
        payload->sprite = func_08011484(payload->sprite);
        if (payload->sprite != 0)
            break;
        payload->first_overlay = func_080D4774(payload->first_overlay);
        if (payload->first_overlay != 0)
            break;
        payload->second_overlay = func_080D4774(payload->second_overlay);
        if (payload->second_overlay != 0)
            break;
        payload->window = func_080D6134(payload->window);
        if (payload->window != 0)
            break;
        g_control_flags_03000940.display &= ~func_080035A8(2);
        g_control_flags_03000940.display &= 0x7FFF;
        g_control_flags_03000940.bldcnt_lo = 0;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
