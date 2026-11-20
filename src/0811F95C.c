#include "ffta.h"
#include "control_flags.h"

/* Complete [0x0811F95C, 0x0811FD74): 1048 bytes including literal pools.
 * func_081204A8 registers this callback with payload size 0x103C. */

typedef struct {
    u16 state;
    u16 unknown_02;
    u8 *output;
    u8 unknown_08[0xC];
    u16 category;
} Script0811F95C;

typedef struct {
    u8 first;
    u8 second;
    u8 unknown_02[2];
} Size0811F95C;

typedef struct {
    u16 flags;
    u16 counter;
    u8 unknown_04[4];
    u8 index;
    u8 unknown_09[3];
    u8 *output;
    u16 remaining;
    u8 unknown_12[2];
    u8 *destination;
    u8 *source;
    void *object;
    void *sprite;
    void *fade;
    void *tasks[4];
    u16 buffer[0x800];
} Payload0811F95C;

extern u16 data_03003920[];
extern u8 data_06008000[];
extern u8 data_06007000[];
extern u16 data_06006000[];
extern const u8 data_0894D17C[];
extern const u8 data_0894D18C[];
extern const u8 data_0894D3B0[];
extern const u8 data_0894D69C[];
extern const u8 data_088F3D90[];
extern const u8 data_0850903C[];
extern const u8 *const data_083A775C[];
extern const u8 *const data_083A7770[];
extern const u8 *const data_083A7784[];
extern const u8 *const data_083A7798[];
extern const u16 data_083A77AC[];
extern const u16 *const data_083A77B8[];
extern const Size0811F95C data_083A77CC[];
extern const s16 data_083A77E0[];

typedef struct TransferRecord TransferRecord;

extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_080D74E0(u8 first, u8 second, u8 third, s16 x, s16 y,
                          void *first_buffer, void *second_buffer);
extern u16 func_080035A8(u8 index);
extern void *func_080D4704(const void *resource, void *parent);
extern void *func_080D3E9C(const void *resource, void *parent);
extern void func_080D3F84(void *task, u8 first, u8 second);
extern void *func_080D3F08(void *task);
extern void *func_080D4774(void *task);
extern void func_080D4A28(u8 first, u8 second, u16 third, s16 fourth, s16 fifth, u32 mode);
extern void *func_080D4B64(u8, const void *, u16, u8);
extern void func_0800BD7C(void *sprite);
extern void func_0800BDF8(void *sprite, u16 value);
extern TransferRecord *func_080D3AF8(void);
extern void func_08000ADC(TransferRecord *entry, const void *source,
                          void *destination, u16 words);
extern void func_08000A98(TransferRecord *entry, const void *source,
                          void *destination, u16 count);
extern void *func_080D5CC0(const void *, u16, s16, s16, u16, u8, u8, u32);
extern void func_080110F8(void *object, u8 enabled);
extern void func_080112CC(void *object, s16 x, s16 y, u16 value);
extern void func_08011428(void *object);
extern void func_080D4D14(void *sprite, u8 mode);

u32 func_0811F95C(void *task, Script0811F95C *script, Payload0811F95C *payload)
{
    u16 zero;
    u16 fill;
    u16 *fill_source;
    u16 count;
    u8 done;
    u16 k;
    u8 row;
    u8 col;
    u16 value;

    if (payload->flags & 0x8000)
        return 0;

    switch (script->state) {
    case 0:
        payload->index = script->category;
        payload->output = script->output;
        *payload->output = 0;
        /* CpuFill16(0, data_03003920, 0x20) */
        zero = 0;
        func_0814186C(&zero, data_03003920, 0x01000010);
        /* CpuFill16(0x7FFF, data_03003920 + 0x220, 0x20): the SDK's vu16
         * temporary, spelled through a pointer until fftadecomp-kit#164.
         * The ROM loads 0x7FFF into r2 and copies it to r1 before the
         * store (0x0811F9F4-0x0811F9F8). */
        fill_source = &fill;
        *fill_source = 0x7FFF;
        func_0814186C(fill_source, data_03003920 + 0x110, 0x01000010);
        break;
    case 1:
        break;
    case 0x100:
        func_080D74E0(1, 0, 0, 0, 0, data_06008000, data_06007000);
        g_control_flags_03000940.display |= func_080035A8(1);
        payload->tasks[0] = func_080D4704(data_0894D17C, task);
        payload->fade = func_080D3E9C(data_0894D69C, task);
        func_080D3F84(payload->fade, 2, 0x3F);
        script->state++;
        break;
    case 0x101:
        payload->fade = func_080D3F08(payload->fade);
        if (payload->fade != 0)
            break;
        *payload->output = 1;
        payload->tasks[0] = func_080D4774(payload->tasks[0]);
        if (payload->tasks[0] != 0)
            break;
        if (payload->index != 0) {
            func_080D4A28(0, 2, 0, 0, 0, 1);
            payload->sprite = func_080D4B64(0, data_088F3D90, 0x19C, 8);
            func_0800BD7C(payload->sprite);
            func_0800BDF8(payload->sprite, payload->index - 1);
            g_control_flags_03000940.display |= func_080035A8(2);
        }
        payload->source = (u8 *)data_083A7798[payload->index];
        payload->destination = (u8 *)0x06000000;
        payload->remaining = data_083A77AC[payload->index];
        script->state++;
        break;
    case 0x102:
        done = 0;
        if (payload->remaining > 0x1000) {
            count = 0x1000;
        } else {
            count = payload->remaining;
            done = 1;
        }
        func_08000ADC(func_080D3AF8(), payload->source, payload->destination,
                      count >> 2);
        payload->destination += count;
        payload->source += count;
        payload->remaining -= count;
        if (done)
            script->state++;
        break;
    case 0x103:
        /* CpuFill16(0, payload->buffer, 0x1000) */
        fill = 0;
        func_0814186C(&fill, payload->buffer, 0x01000800);
        k = 0;
        for (row = 0; row < data_083A77CC[payload->index].second; row++) {
            for (col = 0; col < data_083A77CC[payload->index].first; col++) {
                value = data_083A77B8[payload->index][k];
                if (value == 0x3FF)
                    value = 0;
                if (col < 32)
                    payload->buffer[row * 32 + col] = value;
                else
                    payload->buffer[0x400 + row * 32 + (col & 31)] = value;
                k++;
            }
        }
        func_08000A98(func_080D3AF8(), payload->buffer, data_06006000, 0x800);
        script->state++;
        break;
    case 0x104:
        payload->tasks[0] = func_080D4704(data_0894D18C, task);
        payload->tasks[1] = func_080D4704(data_083A7770[payload->index], task);
        payload->tasks[2] = func_080D4704(data_083A7784[payload->index], task);
        payload->tasks[3] = func_080D4704(data_0894D3B0, task);
        payload->fade = func_080D3E9C(data_083A775C[payload->index], task);
        func_080D3F84(payload->fade, 2, 0x3F);
        payload->object = func_080D5CC0(data_0850903C, payload->index, 0x78, 0x50,
                                        0x37F, 7, 0, 0);
        func_080110F8(payload->object, 1);
        script->state++;
        break;
    case 0x105:
        if (payload->counter < 0x54) {
            func_080112CC(payload->object, data_083A77E0[payload->counter],
                          data_083A77E0[payload->counter], 0);
            payload->counter++;
        }
        payload->fade = func_080D3F08(payload->fade);
        if (payload->fade != 0)
            break;
        payload->tasks[0] = func_080D4774(payload->tasks[0]);
        if (payload->tasks[0] != 0)
            break;
        payload->tasks[1] = func_080D4774(payload->tasks[1]);
        if (payload->tasks[1] != 0)
            break;
        payload->tasks[2] = func_080D4774(payload->tasks[2]);
        if (payload->tasks[2] != 0)
            break;
        payload->tasks[3] = func_080D4774(payload->tasks[3]);
        if (payload->tasks[3] != 0)
            break;
        g_control_flags_03000940.display &= ~func_080035A8(1);
        func_08011428(payload->object);
        payload->object = 0;
        if (payload->sprite != 0) {
            func_080D4D14(payload->sprite, 0);
            payload->sprite = 0;
        }
        payload->counter = 0x14;
        script->state++;
        break;
    case 0x106:
        if (--payload->counter == 0)
            script->state = 2;
        break;
    }
    return 0;
}
