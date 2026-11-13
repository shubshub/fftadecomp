#include "control_flags.h"

typedef struct {
    u16 phase;
} Descriptor08114F1C;

typedef struct {
    u8 frame;
    u8 width;
    s16 x;
    s16 y;
    u16 unknown_06;
} GeometryStage08114F1C;

typedef struct {
    u16 timer;
    s16 x;
    s16 y;
    s16 width;
    s16 extent;
    u8 stage;
    u8 unknown_0B;
    void *coordinate_output;
    void *coordinate_task;
    void *sequence_task;
    void *window_task;
    void *palette_task;
    void *record_task;
} Payload08114F1C;

extern const u8 data_083A38D8[], data_0894DC38[], data_088F46CC[];
extern const u8 data_083A3978[];
extern const GeometryStage08114F1C data_083A38F0[];
extern struct {
    u8 unknown_00[0xE2];
    u16 color;
} data_03003860;

extern void *func_080D6098(u16 x, u16 y, u16 depth, u8 mode, u16 count,
                          void **outputs, const void *entries, void *parent);
extern void *func_080D3E9C(const void *record, void *parent);
extern void func_080D3F84(void *task, u8 first_targets, u8 second_targets);
extern void func_080D7220(const void *record, u8 bank, u8 layer,
                         s16 x, s16 y, u16 flags);
extern void *func_080DAB84(u8 first, u8 second, u8 third, void *parent);
extern u16 func_080035D0(u8 layer);
extern u16 func_080035A8(u8 layer);
extern void *func_080DFD8C(const void *record, u8 count, u16 flags,
                          u16 delay, void *parent);
extern void *func_08147A7C(u16 start, u16 count, u16 duration);
extern void *func_080DABB4(void *task);
extern void func_080DADFC(void *task);
extern void func_080DABC4(void *task, s16 x, s16 y, s16 width,
                         s16 height, u8 mode);
extern void func_080D9B98(void *task);
extern void *func_081484CC(void *handle);
extern void *func_080D3F08(void *task);
extern void *func_080D6134(void *task);
extern void *func_080D9B64(void *task);

/* Complete target: [0x08114F1C, 0x081151A0), 644 bytes. */
u32 func_08114F1C(void *task, Descriptor08114F1C *descriptor,
                  Payload08114F1C *payload)
{
    switch (descriptor->phase) {
    case 0:
        payload->timer = 10;
        break;
    case 1:
        break;
    case 0x100:
        if (--payload->timer == 0) {
            payload->coordinate_task = func_080D6098(120, 96, 0, 1, 1,
                &payload->coordinate_output, data_083A38D8, task);
            payload->sequence_task = func_080D3E9C(data_0894DC38, task);
            func_080D3F84(payload->sequence_task, 24, 255);
            func_080D7220(data_088F46CC, 1, 3, 0, 0, 0);
            payload->window_task = func_080DAB84(0, 0, 0, task);
            g_control_flags_03000940.winin_lo = 63;
            g_control_flags_03000940.winout_lo = 63 & ~func_080035D0(3);
            g_control_flags_03000940.win0h_hi = 0;
            g_control_flags_03000940.win0h_lo = 0;
            g_control_flags_03000940.win0v_hi = 0;
            g_control_flags_03000940.win0v_lo = 255;
            g_control_flags_03000940.display |= 0x2000;
            payload->record_task = func_080DFD8C(data_083A3978, 1, 4, 0, task);
            ++descriptor->phase;
        }
        break;
    case 0x101:
    {
        u8 index;

        for (index = 0; index < 13; index++) {
            if (payload->timer == data_083A38F0[index].frame)
                break;
        }
        payload->timer++;
        if (index == 13)
            break;
        data_03003860.color = 0x7F18;
        payload->palette_task = func_08147A7C(0x71, 1, 5);
        payload->x = data_083A38F0[payload->stage].x;
        payload->y = data_083A38F0[payload->stage].y;
        payload->width = data_083A38F0[payload->stage].width - 1;
        payload->extent = data_083A38F0[payload->stage].y;
        func_080DABB4(payload->window_task);
        func_080DADFC(payload->window_task);
        func_080DABC4(payload->window_task, payload->x, payload->y,
            (u16)payload->x + (u16)payload->extent, 0, 0);
        func_080DABC4(payload->window_task,
            (u16)payload->x + (u16)payload->width, payload->y,
            (u16)payload->extent + ((u16)payload->x + (u16)payload->width),
            0, 1);
        func_080D9B98(payload->window_task);
        ++descriptor->phase;
        break;
    }
    case 0x102:
        payload->timer++;
        payload->palette_task = func_081484CC(payload->palette_task);
        if (payload->palette_task != 0)
            break;
        payload->stage++;
        if (payload->stage < 13) {
            descriptor->phase = 0x101;
        } else {
            g_control_flags_03000940.display &= ~func_080035A8(3);
            g_control_flags_03000940.display &= 0xDFFF;
            ++descriptor->phase;
        }
        break;
    case 0x103:
        payload->sequence_task = func_080D3F08(payload->sequence_task);
        if (payload->sequence_task != 0)
            break;
        payload->coordinate_task = func_080D6134(payload->coordinate_task);
        if (payload->coordinate_task != 0)
            break;
        payload->window_task = func_080D9B64(payload->window_task);
        if (payload->window_task == 0) {
            g_control_flags_03000940.bldcnt_lo = 0;
            descriptor->phase = 2;
        }
        break;
    }
    return 0;
}
