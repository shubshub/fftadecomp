#include "ffta.h"
#include "control_flags.h"

/* Complete 0x0801F80C..0x0801FEB6: 1706 bytes, 733 instructions.
 * The per-frame step of the layer request that func_0801FEB8 starts: scroll
 * the camera to the request's target, rebuild the two tilemap layers in
 * data_02006CB0, fade the new graphics in and queue the tilemap copies. */

typedef struct TransferRecord {
    u8 status;
    u8 kind;
    u8 unknown_02[2];
    const void *source;
    void *destination;
    u32 control;
    u8 unknown_10[8];
    struct TransferRecord *next;
} TransferRecord;

typedef struct LineState {
    s32 x;
    s32 y;
    s32 endX;
    s32 endY;
    s32 stepX;
    s32 stepY;
    s32 deltaX;
    s32 deltaY;
    s32 accumulator;
    s32 error;
    s32 remaining;
} LineState;

typedef struct {
    u8 active;
    u8 mode;
    u8 phase;
    u8 unknown_03;
    const u32 *table;
    const u32 *resources;
    const u32 *layers;
    u16 *secondary_destination;
    u16 *primary_destination;
    s16 tile_x;
    s16 tile_y;
    s16 offset_x;
    s16 offset_y;
    u8 first;
    u8 last;
    u16 fade_frames;
    s16 target_x;
    s16 target_y;
    s16 timer;
    u8 unknown_2A[2];
    u16 *buffer;
    TransferRecord primary_transfer;
    TransferRecord secondary_transfer;
    LineState fade;
} LayerRequest;

typedef struct {
    u8 unknown_00[0x1E];
    u16 fill_color;
    u8 unknown_20[4];
    s16 camera_x;
    s16 camera_y;
    u8 unknown_28[4];
    u16 flags;
    u8 unknown_2E[0x13A];
    void *pending_resource;
    void *pending_stream;
    u8 unknown_170[0x14];
    LayerRequest request;
} ResourceState;

extern ResourceState g_state_02007F40;
extern u16 data_02006CB0[];
extern u8 data_02003CB0[];

extern void func_0801E6F0(u16 *x, u16 *y);
extern u16 func_0801BA20(s16 x, s16 y, u16 speed);
extern u8 func_0801BDB0(void);
extern void func_0801E0DC(s16 x, s16 y);
extern u32 func_0801E6A8(void);
extern void func_0801E458(u8 layer, u8 format, u8 mode, s16 x, s16 y,
                          void *source, void *destination);
extern u8 func_0801E648(void);
extern void func_08141868(const void *source, void *destination, u32 control);
extern void func_08141890(const void *source, void *destination);
extern void func_0801B630(int x, int y, int layer, u16 *first, u16 *second);
extern void func_0801F6C0(const u32 *resource, u16 index, s16 x, s16 y,
                          void *first, void *second, u8 clear);
extern u16 func_0801B814(u8 layer, u16 x, u16 y);
extern void func_0801B848(u8 layer, u16 x, u16 y, u16 value);
extern void func_0801B878(void);
extern void func_08000ADC(TransferRecord *entry, const void *source,
                          void *destination, u16 words);
extern void func_08000B68(TransferRecord *entry, u32 value,
                          void *destination, u16 count);
extern u32 func_0801F548(const u32 *resource, u16 index);
extern s32 func_0801F62C(const u32 *table, u16 index);
extern void func_0801E610(u8 *first, u8 *second);
extern u16 func_080035F8(u8 layer);
extern u16 func_080035A8(u8 layer);
extern void func_080075CC(LineState *state, s32 x, s32 y, s32 endX, s32 endY);
extern void func_080076A0(LineState *state);
extern u32 func_08007880(const LineState *state);
extern void func_0801F098(const u8 *data, const u8 *end);

/* An inlined copy of func_08020490 (src/08020490.c). */
static inline u8 transfer_idle(void)
{
    return g_state_02007F40.pending_resource == 0;
}

/* An inlined copy of func_080204B0 (src/080204B0.c). */
static inline u32 stream_idle(void)
{
    u32 idle = 0;

    if (g_state_02007F40.pending_stream == 0)
        idle = 1;
    return idle;
}

/* An inlined copy of func_080204D0 (src/080204D0.c). */
static inline void apply_layer(const u32 *table, u16 index)
{
    const u32 *entry = table;
    u16 last;
    u32 last_offset;
    const u8 *end;
    u32 offset;

    while (!*entry)
        entry++;
    last = (*entry - 4) / 4;
    end = 0;
    last_offset = table[last];
    if (last_offset != (u32)-1)
        end = (const u8 *)table + last_offset;
    offset = table[index];
    if (offset) {
        const u8 *payload = (const u8 *)table + offset;

        if (*payload) {
            func_08141890(payload, data_02003CB0);
            payload = data_02003CB0;
        } else {
            payload += 4;
        }
        func_0801F098(payload, end);
    }
}

/* Whether the camera is away from the request's target (an axis set to
 * -0x8000 keeps the camera's own coordinate).  The ROM keeps the answer as a
 * value: movs r0, #1 / movs r0, #0 / cmp r0, #0 at 0x0801F8A0..0x0801F8AA. */
static inline u8 scroll_needed(LayerRequest *request)
{
    u16 x, y;
    u16 target_x, target_y;

    func_0801E6F0(&x, &y);
    target_x = x;
    target_y = y;
    if (request->target_x != -0x8000)
        target_x = request->target_x;
    if (request->target_y != -0x8000)
        target_y = request->target_y;
    if (x != target_x || y != target_y)
        return 1;
    return 0;
}

u32 func_0801F80C(void)
{
    LayerRequest *request = &g_state_02007F40.request;

    switch (request->mode) {
    case 0:
        if (scroll_needed(request)) {
            request->timer = 0x20;
            request->mode++;
        } else {
            request->timer = -1;
            request->mode = 2;
        }
        break;
    case 1: {
        s16 x, y;
        s16 target_x, target_y;

        if (--request->timer)
            break;
        func_0801E6F0(&x, &y);
        target_x = x;
        target_y = y;
        if (request->target_x != -0x8000)
            target_x = request->target_x;
        if (request->target_y != -0x8000)
            target_y = request->target_y;
        if (x != target_x || y != target_y)
            func_0801BA20(target_x, target_y, 4);
        request->mode++;
        break;
    }
    case 2:
        if (func_0801BDB0())
            break;
        if (request->timer != -1) {
            request->timer = 0x20;
            request->mode++;
        } else {
            request->mode = 4;
        }
        break;
    case 3:
        if (--request->timer)
            break;
        request->mode++;
        break;
    case 4:
        func_0801E0DC(g_state_02007F40.camera_x, g_state_02007F40.camera_y);
        request->mode++;
        break;
    case 5: {
        u16 camera_x, camera_y;
        s32 origin_x, origin_y;
        void *source;

        func_0801E6F0(&camera_x, &camera_y);
        origin_x = (camera_x - 8) & ~7;
        origin_x = (s16)origin_x;
        request->offset_x = camera_x - origin_x;
        origin_y = (camera_y - 48) & ~7;
        origin_y = (s16)origin_y;
        request->offset_y = camera_y - origin_y;
        source = (void *)func_0801E6A8();
        func_0801E458(3, 0, 0, request->offset_x, request->offset_y, source,
                      request->primary_destination);
        if (func_0801E648())
            func_0801E458(2, 0, 0, request->offset_x, request->offset_y, source,
                          request->secondary_destination);
        request->tile_x = origin_x >> 3;
        request->tile_y = origin_y >> 3;
        request->mode++;
        break;
    }
    case 6:
        request->buffer = data_02006CB0;
        {
            /* The SDK's CpuFastFill (pret include/gba/macro.h, as
             * src/0801A15C.c defines it), written out.  The temporary's
             * slot, sp+0x18 (0x0801F9F2), lies below case 11's byte pair
             * at sp+0x1C (0x0801FC86): the frame gives it a slot at its
             * declaration. */
            volatile u32 fill = 0;

            func_08141868((const void *)&fill, data_02006CB0, 0x01000400);
        }
        if (func_0801E648()) {
            func_0801B630(request->tile_x, request->tile_y, 0, request->buffer, 0);
            request->mode++;
        }
        break;
    case 7:
        if (func_0801E648())
            func_0801F6C0(request->table, request->first, request->tile_x,
                          request->tile_y, request->buffer, 0, 0);
        request->mode++;
        break;
    case 8:
        func_0801F6C0(request->table, request->first, request->tile_x,
                      request->tile_y, 0, request->buffer + 0x400, 1);
        request->mode++;
        break;
    case 9: {
        u16 *primary = request->buffer + 0x400;
        u16 *secondary = request->buffer;
        s16 x, y;

        if (func_0801E648()) {
            for (y = request->tile_y; y < request->tile_y + 32; y++) {
                for (x = request->tile_x; x < request->tile_x + 32; x++, secondary++, primary++) {
                    if (secondary >= request->secondary_destination + 0x400) {
                        y = request->tile_y + 32;
                        break;
                    }
                    if (primary >= request->primary_destination + 0x400) {
                        y = request->tile_y + 32;
                        break;
                    }
                    if (x >= 0 && x < 64 && y >= 0 && y < 64) {
                        if (func_0801B814(0, x, y) != g_state_02007F40.fill_color
                            && *secondary == g_state_02007F40.fill_color
                            && *primary == g_state_02007F40.fill_color)
                            *primary = func_0801B814(1, x, y);
                        if (*secondary != g_state_02007F40.fill_color
                            && *primary != g_state_02007F40.fill_color) {
                            if (g_state_02007F40.flags & 0x800) {
                                if (func_0801B814(0, x, y) == g_state_02007F40.fill_color
                                    && secondary - 32 >= request->buffer
                                    && secondary[-32] != g_state_02007F40.fill_color) {
                                    /* Two stores in the ROM: 0x0801FB86, 0x0801FB92. */
                                    if (secondary - 64 >= request->buffer) {
                                        if (secondary[-64] == g_state_02007F40.fill_color)
                                            *primary = g_state_02007F40.fill_color;
                                    } else {
                                        *primary = g_state_02007F40.fill_color;
                                    }
                                }
                            } else if (func_0801B814(0, x, y) == g_state_02007F40.fill_color) {
                                func_0801B848(0, x, y, func_0801B814(1, x, y));
                                func_0801B848(1, x, y, g_state_02007F40.fill_color);
                                func_0801B878();
                            } else if (func_0801B814(0, x, y) != *secondary) {
                                *primary = g_state_02007F40.fill_color;
                            }
                        }
                    }
                }
            }
        }
        func_08000ADC(&request->primary_transfer, request->buffer + 0x400,
                      request->primary_destination, 0x200);
        if (func_0801E648())
            func_08000ADC(&request->secondary_transfer, request->buffer,
                          request->secondary_destination, 0x200);
        request->mode++;
        break;
    }
    case 10:
        request->mode++;
        break;
    case 11: {
        u8 first_layer, second_layer;

        func_0801F548(request->table, request->first);
        func_0801E610(&first_layer, &second_layer);
        g_control_flags_03000940.bldcnt_lo = func_080035F8(3) | 0x40;
        if (func_0801E648())
            g_control_flags_03000940.bldcnt_lo |= func_080035F8(2);
        g_control_flags_03000940.bldcnt_hi = func_080035F8(second_layer) | 0x20;
        if (func_0801E648())
            g_control_flags_03000940.bldcnt_hi |= func_080035F8(first_layer);
        g_control_flags_03000940.bldalpha_lo = 0;
        g_control_flags_03000940.bldalpha_hi = 16;
        func_080075CC(&request->fade, 0, 0, 16, request->fade_frames);
        g_control_flags_03000940.display |= func_080035A8(3);
        if (func_0801E648())
            g_control_flags_03000940.display |= func_080035A8(2);
        request->mode++;
        break;
    }
    case 12:
        func_080076A0(&request->fade);
        g_control_flags_03000940.bldalpha_lo = request->fade.x;
        g_control_flags_03000940.bldalpha_hi = 16 - request->fade.x;
        if (!func_08007880(&request->fade))
            break;
        if (!transfer_idle())
            break;
        g_control_flags_03000940.bldcnt_lo = 0;
        g_control_flags_03000940.display &= ~func_080035A8(3);
        if (func_0801E648())
            g_control_flags_03000940.display &= ~func_080035A8(2);
        func_0801B878();
        if (request->first == request->last) {
            func_0801F62C(request->resources, request->phase);
            func_08000B68(&request->primary_transfer, 0,
                          request->primary_destination, 0x200);
            request->mode++;
        } else {
            request->first++;
            request->mode = 6;
        }
        break;
    case 13:
        if (!stream_idle())
            break;
        apply_layer(request->layers, request->phase);
        g_state_02007F40.flags &= ~0x800;
        if (func_0801E648())
            func_08000B68(&request->secondary_transfer, 0,
                          request->secondary_destination, 0x200);
        return 1;
    }
    return 0;
}
