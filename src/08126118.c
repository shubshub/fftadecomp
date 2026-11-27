#include "ffta.h"
#include "control_flags.h"

// Target: complete [0x08126118, 0x0812638C), 628 bytes, 247 instructions.
// These local views describe accessed fields, not complete object extents.

typedef struct RequestNode08126118 {
    u8 status;
    u8 kind;
    u8 unknown_02[2];
    u32 first;
    u32 second;
    u32 control;
    u8 unknown_10[8];
    struct RequestNode08126118 *next;
} RequestNode08126118;

typedef struct {
    u16 *control;
    u16 *horizontal_offset;
    u16 *vertical_offset;
    u8 width;
    u8 height;
    u8 *tiles;
    void *destination;
} DisplayRecord08126118;

typedef struct {
    u16 unknown_00;
    u8 count;
    u8 index;
} TableSlot08126118;

typedef struct {
    u8 unknown_00[6];
    u8 active;
} Owner08126118;

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    Owner08126118 *owner;
    u8 unknown_08[12];
    u16 first;
    u16 second;
} Task08126118;

typedef struct {
    Owner08126118 *owner;
    u8 unknown_04[4];
    void *window;
    u8 timer;
    u8 first;
    u8 second;
    u8 unknown_0F;
    RequestNode08126118 clear_main;
    RequestNode08126118 clear_sub;
    RequestNode08126118 fill_sub;
} State08126118;

typedef void (*BufferInitializer08126118)(void *destination, u32 size);

extern BufferInitializer08126118 const g_callbacks_0836D4B8[];
extern u8 data_030039A0[];
extern DisplayRecord08126118 data_030008B0;
extern DisplayRecord08126118 data_03000990;
extern TableSlot08126118 data_03002710;
extern TableSlot08126118 data_030027E0;
extern u8 data_06005000[];
extern u8 data_06005800[];
extern u8 data_06008000[];

extern void func_08000B20(RequestNode08126118 *entry, u16 first, void *second, u16 count);
extern void func_08000B68(RequestNode08126118 *entry, u32 first, void *second, u16 count);
extern void func_08006BE0(TableSlot08126118 *table, u8 index);
extern void func_0801174C(void *, u32, u32, void *, void *, u32, u32,
                          u32, u32, u32);
extern u16 func_08011860(void);
extern void func_0801339C(u16 value);
extern void func_0801DB78(void);
extern void func_0801E458(u8, u8, u8, s16, s16, void *, void *);
extern void func_0802292C(u32 value);
extern void func_080231C0(void);
extern void *func_08121B64(u32 size);
extern void func_08121B78(void *object);
extern void func_0814224C(void *destination, u32 size,
                          BufferInitializer08126118 initializer);
extern void func_081452F4(void);
extern void func_08145798(void);
extern void func_08148540(void);

s32 func_08126118(void *context, Task08126118 *task, State08126118 *state)
{
    BufferInitializer08126118 const *callbacks;

    switch (task->phase) {
    case 1:
        if (state->window) {
            func_08121B78(state->window);
            state->window = 0;
        }
        break;
    case 0:
        state->owner = task->owner;
        state->first = task->first;
        state->second = task->second;
        func_0801DB78();
        func_081452F4();
        func_08148540();
        func_0802292C(2);
        callbacks = g_callbacks_0836D4B8;
        func_0814224C(data_030039A0, 0x20, callbacks[0]);
        func_08000B68(&state->fill_sub, 0x11111111, data_03000990.tiles + 0x20, 8);
        func_08000B20(&state->clear_sub, 0, data_03000990.destination, 0x280);
        g_control_flags_03000940.bldcnt_lo |= 0xff;
        g_control_flags_03000940.bldcnt_hi = 0;
        g_control_flags_03000940.bldy_lo = 0x10;
        break;
    case 0x100:
        func_08000B20(&state->clear_main, 0, data_030008B0.destination, 0x280);
        state->timer = 8;
        g_control_flags_03000940.display |= 0xC00;
        g_control_flags_03000940.display &= 0x8CFF;
        g_control_flags_03000940.bldcnt_lo = 0;
        g_control_flags_03000940.bldcnt_hi = 0;
        g_control_flags_03000940.bldy_lo = 0;
        func_08006BE0(&data_03002710, 0);
        func_08006BE0(&data_03002710, 3);
        func_08006BE0(&data_03002710, 4);
        func_08006BE0(&data_03002710, 2);
        func_08006BE0(&data_03002710, 5);
        func_08006BE0(&data_03002710, 6);
        func_08006BE0(&data_03002710, 7);
        data_030027E0.index = 0;
        func_08006BE0(&data_030027E0, 0);
        func_0801E458(2, 0, 0, 0, 0, data_06008000, data_06005800);
        func_0801E458(3, 0, 0, 0, 0, data_06008000, data_06005000);
        task->phase = 0x101;
        break;
    case 0x101:
        if (state->timer == 0 || --state->timer == 0)
            task->phase = 0x102;
        break;
    case 0x102:
        state->window = func_08121B64(0xA04);
        func_0801174C(state->window, 1, 0x24, &data_030008B0, &data_03000990,
                      2, 2, 0x18, 4, 0x3a0);
        func_0801339C(2);
        task->phase = 0x103;
        break;
    case 0x103:
        if (func_08011860()) {
            func_08145798();
            func_081452F4();
            state->timer = 0x40;
            task->phase = 0x104;
        }
        break;
    case 0x104:
        if (state->timer == 0 || --state->timer == 0) {
            func_08121B78(state->window);
            state->window = 0;
            task->phase = 0x105;
        }
        break;
    case 0x105:
        func_080231C0();
        state->owner->active = 1;
        task->phase = 3;
        break;
    }
    return 0;
}
