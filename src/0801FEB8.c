#include "ffta.h"
#include "control_flags.h"

typedef struct {
    u8 active;
    u8 mode;
    u8 phase;
    u8 unknown_03;
    const u32 *table;
    const u32 *resources;
    u8 unknown_0C[4];
    void *secondary_destination;
    void *primary_destination;
    s16 tile_x;
    s16 tile_y;
    u8 unknown_1C[4];
    u8 first;
    u8 last;
    u16 index;
} LayerRequest;

typedef struct {
    u8 unknown_00[0x168];
    void *pending_resource;
    void *pending_stream;
    u8 unknown_170[0x14];
    LayerRequest request;
} ResourceState;

extern ResourceState g_state_02007F40;

extern void func_0801E6F0(u16 *x, u16 *y);
extern u32 func_0801E6A8(void);
extern void func_0801E458(u8 layer, u8 format, u8 mode, s16 x, s16 y,
                          void *source, void *destination);
extern u8 func_0801E648(void);
extern u16 func_080035A8(u8 layer);
extern u32 func_0801F80C(void);

/* The two readiness predicates also occur at 0x08020490 and 0x080204B0. */
static inline u8 transfer_idle(void)
{
    return g_state_02007F40.pending_resource == 0;
}

static inline u32 stream_idle(void)
{
    u32 idle = 0;
    if (g_state_02007F40.pending_stream == 0)
        idle = 1;
    return idle;
}

/* Complete 0x0801FEB8..0x08020008, 336 bytes. */
u8 func_0801FEB8(const u32 *table, const u32 *resources, u16 index,
                 void *secondary_destination, void *primary_destination,
                 u16 first, u16 last)
{
    LayerRequest *request = &g_state_02007F40.request;
    u16 camera_x, camera_y;
    s32 origin_x, origin_y;
    s16 offset_x, offset_y;
    void *source;

    if (!transfer_idle() || !stream_idle())
        return 0;
    func_0801E6F0(&camera_x, &camera_y);
    origin_x = (camera_x - 8) & ~7;
    origin_x = (s16)origin_x;
    offset_x = camera_x - origin_x;
    origin_y = (camera_y - 48) & ~7;
    origin_y = (s16)origin_y;
    offset_y = camera_y - origin_y;
    source = (void *)func_0801E6A8();
    func_0801E458(3, 0, 0, offset_x, offset_y, source, primary_destination);
    if (func_0801E648())
        func_0801E458(2, 0, 0, offset_x, offset_y, source, secondary_destination);
    request->active = 1;
    request->mode = 6;
    request->table = table;
    request->resources = resources;
    request->secondary_destination = secondary_destination;
    request->primary_destination = primary_destination;
    request->tile_x = origin_x >> 3;
    request->tile_y = origin_y >> 3;
    request->first = first;
    request->last = last;
    request->index = index;
    request->phase = 0;
    g_control_flags_03000940.display &= ~func_080035A8(3);
    if (func_0801E648()) {
        g_control_flags_03000940.display &= ~func_080035A8(2);
    }
    func_0801F80C();
    return 1;
}
