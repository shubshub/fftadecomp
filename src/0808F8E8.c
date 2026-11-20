#include "control_flags.h"

// func_0808F8E8 - complete [0x0808F8E8, 0x0808FA98): 432 bytes, 174 instructions,
// including the literal pool.

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

typedef struct ExtendedRequestNode {
    u8 status;
    u8 kind;
    u8 unknown_02[2];
    u32 first;
    u32 second;
    u32 control;
    u16 field_10;
    u16 field_12;
    u16 field_14;
    u8 unknown_16[2];
    struct ExtendedRequestNode *next;
} ExtendedRequestNode;

typedef struct {
    u8 unknown_00[14];
} WindowTemplate;

typedef struct {
    u8 unknown_00[0x22];
    u8 kind;
} Owner;

typedef struct {
    u16 lines[161];
    u8 unknown_142[0x14E];
    void *resource;
    TransferRecord transfer;
    ExtendedRequestNode request;
    Owner *owner;
    void *context;
    u16 bg2hofs;
    u16 bg2vofs;
    u8 blend_control_low;
    u8 blend_control_high;
    u8 blend_alpha_low;
    u8 blend_alpha_high;
    const WindowTemplate *window;
    u8 unknown_2E0[0x48];
} OverlayState;

typedef struct {
    u8 unknown_00[0x14];
    u8 *destination;
} TransferState;

typedef void (*BufferInitializer)(void *, u32);
typedef void (*BufferCopier)(void *, const void *, u32);

extern BufferInitializer g_callbacks_0836D4B8[];
extern BufferCopier data_0836D4BC;
extern const WindowTemplate data_08394088;
extern const WindowTemplate data_08394096;
extern const u8 data_083C1834[];
extern u32 data_08394058[];
extern u32 data_08394070[];
extern u8 data_06009C00[];
extern TransferState data_030008B0;
extern u8 data_03003920[];

extern void *func_08022840(u32 size);
extern s32 func_08005318(const void *data, u8 *output, u16 start, u16 count);
extern void func_08000ADC(TransferRecord *entry, const void *source,
                          void *destination, u16 words);
extern void func_08000BAC(ExtendedRequestNode *, u32, u32, u16, u16, u16, u16);
extern u8 *func_080CBABC(u32 index);
extern void func_08000D48(u32 channel, const void *source, void *destination,
                          u32 control);

OverlayState *func_0808F8E8(Owner *owner)
{
    OverlayState *state;
    s32 i;
    u8 kind;

    state = func_08022840(sizeof(OverlayState));
    g_callbacks_0836D4B8[0](state, sizeof(OverlayState));
    state->blend_control_low = g_control_flags_03000940.bldcnt_lo;
    state->blend_control_high = g_control_flags_03000940.bldcnt_hi;
    state->blend_alpha_low = g_control_flags_03000940.bldalpha_lo;
    state->blend_alpha_high = g_control_flags_03000940.bldalpha_hi;
    state->bg2hofs = g_control_flags_03000940.bg2hofs;
    state->bg2vofs = g_control_flags_03000940.bg2vofs;
    state->window = &data_08394088;
    if (owner->kind == 5)
        state->window = &data_08394096;
    state->owner = owner;
    g_control_flags_03000940.bldcnt_lo = 0x44;
    g_control_flags_03000940.bldcnt_hi = 0x3B;
    g_control_flags_03000940.bldalpha_lo = 0;
    g_control_flags_03000940.bldalpha_hi = 0x10;
    g_control_flags_03000940.bg2hofs = 0;
    g_control_flags_03000940.bg2vofs = 0;
    state->resource = func_08022840(0x5C0);
    kind = owner->kind;
    func_08005318(data_083C1834, state->resource, kind, 1);
    func_08000ADC(&state->transfer, state->resource, data_06009C00, 0x170);
    func_08000BAC(&state->request, data_08394058[kind],
                  (u32)(data_030008B0.destination + 0x306),
                  data_08394070[kind] >> 3, 4,
                  data_08394070[kind] >> 2, 0x40);
    data_0836D4BC(data_03003920, func_080CBABC(12), 32);
    data_0836D4BC(data_03003920 + 0x200, func_080CBABC(11), 32);
    for (i = 0; i < 161; i++)
        state->lines[i] = 0;
    func_08000D48(3, state, (void *)0x04000018, 0x20400001);
    return state;
}
