#include "ffta.h"
#include "control_flags.h"

// Target: complete [0x08113918, 0x08113C68), 848 bytes, 370 instructions.

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *argument;
} Descriptor08113918;

typedef struct {
    u16 timer;
    u16 unknown_02;
    u16 unknown_04;
    u8 index;
    u8 count;
    u8 limit;
    u8 unknown_09[3];
    void *child;
    void **handle;
    void *effect;
    void *objects[17];
    void *window;
} Payload08113918;

typedef struct {
    u16 unknown_00[4];
    u16 width;
    u16 height;
} Bounds08113918;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

extern const u8 data_0894DC0C[];
extern const u8 data_083A37D8[];
extern const u8 data_088F1310[];
extern const u8 data_088F5F08[];
extern u8 data_03003920[];

extern u32 func_081137BC(void *task, void *descriptor, void *payload);
extern void func_08011138(void *handle, u32 value);
extern void func_08011100(void *handle, u32 value);
extern void func_08011428(void *handle);
extern void *func_080D3E9C(const void *resource, void *parent);
extern void func_080D3F84(void *effect, u32 a, u32 b);
extern void *func_080D3F08(void *effect);
extern void *func_080DFD8C(const void *resource, u32 a, u32 b, u32 c, void *parent);
extern void func_080D49FC(u32 a, u32 b, u32 c, u32 d, u32 e);
extern void func_0800BC90(u32 a, u32 b, u32 c);
extern void func_0800BD24(u32 a, u32 b);
extern void func_0800BC4C(u32 a, u32 b);
extern u16 func_080035A8(u8 index);
extern u8 func_080035D0(u8 index);
extern void *func_08005B6C(TaskCallback callback, u16 payload_size,
                         void *descriptor, void *parent);
extern void func_0801CAE0(Bounds08113918 *out);
extern s32 func_08141870(s32 numerator, s32 denominator);
extern u32 func_0800C148(void *object);
extern void func_0800C224(void *object);
extern void *func_0800B394(u32 a, const u8 *b, const u8 *c, u8 d, u8 e);
extern void func_0800BEDC(void *object, u32 value);
extern void func_0800BED8(void *object, u32 value);
extern void func_0800BF04(void *object, u8 a, u8 b);
extern void *func_080E051C(void *object);
extern void func_0800C1C8(u32 value);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_080D7220(const void *resource, u32 a, u32 b, u32 c, u32 d, u32 e);

u32 func_08113918(void *task, Descriptor08113918 *descriptor,
                  Payload08113918 *payload)
{
    u8 desc[0x1C];
    Bounds08113918 bounds;
    u16 clear;
    u8 i;
    u8 all;
    const u8 *header;
    s16 flags;
    u16 offset;
    u8 low;
    const u8 *body;
    void *object;

    switch (descriptor->phase) {
    case 0:
        payload->handle = descriptor->argument;
        break;
    case 1:
        break;
    case 0x100:
        func_08011138(*payload->handle, 0);
        payload->effect = func_080D3E9C(data_0894DC0C, task);
        func_080D3F84(payload->effect, 0, 0xFF);
        func_08011100(*payload->handle, 1);
        payload->window = func_080DFD8C(data_083A37D8, 1, 4, 0, task);
        payload->timer = 40;
        descriptor->phase++;
        break;
    case 0x101:
        if (--payload->timer == 0) {
            func_080D49FC(1, 3, 0, 0, 0);
            func_0800BC90(1, 0, 3);
            func_0800BD24(1, 0);
            func_0800BC4C(1, 1);
            payload->unknown_02 = 4;
            payload->unknown_04 = 0x13;
            payload->timer = 1;
            g_control_flags_03000940.display |= func_080035A8(3);
            g_control_flags_03000940.win0h_hi = 0;
            g_control_flags_03000940.win0h_lo = 0xF0;
            g_control_flags_03000940.win0v_hi = 0;
            g_control_flags_03000940.win0v_lo = 0xA0;
            g_control_flags_03000940.winin_lo = 0x3F;
            g_control_flags_03000940.winout_lo = 0x3F & ~func_080035D0(1);
            g_control_flags_03000940.display |= 0x2000;
            payload->child = func_08005B6C((TaskCallback)func_081137BC, 0x5C, desc, task);
            func_0801CAE0(&bounds);
            func_08141870((s16)((bounds.width >> 1) + bounds.unknown_00[0]), 3);
            payload->limit = ((s16)func_08141870(bounds.height >> 1, 3) + 0x30 >> 3) + 1;
            if (payload->limit > 0x11)
                payload->limit = 0x11;
            descriptor->phase++;
        }
        break;
    case 0x102:
        for (i = 0; i <= 16; i++) {
            if (payload->objects[i] != 0 && func_0800C148(payload->objects[i])) {
                func_0800C224(payload->objects[i]);
                payload->objects[i] = 0;
                payload->count++;
            }
        }
        g_control_flags_03000940.win0v_lo = -0x60 - (payload->count << 3);
        if (--payload->timer == 0) {
            payload->timer = 5;
            header = data_088F1310;
            body = header + 4;
            low = header[2];
            offset = header[3] << 8 | low;
            payload->objects[payload->index] = func_0800B394(
                1, body, header + offset,
                payload->unknown_02, payload->unknown_04);
            func_0800BEDC(payload->objects[payload->index], 7);
            func_0800BED8(payload->objects[payload->index], 0x3CC);
            object = payload->objects[payload->index];
            low = header[0];
            flags = header[1] << 8 | low;
            func_0800BF04(object, flags & 4, flags & 8);
            payload->index++;
            payload->unknown_04--;
            if (payload->index >= payload->limit)
                descriptor->phase++;
        }
        break;
    case 0x103:
        all = 1;
        for (i = 0; i <= 16; i++) {
            if (payload->objects[i] != 0) {
                if (func_0800C148(payload->objects[i])) {
                    func_0800C224(payload->objects[i]);
                    payload->objects[i] = 0;
                    payload->count++;
                } else {
                    all = 0;
                }
            }
        }
        g_control_flags_03000940.win0v_lo = -0x60 - (payload->count << 3);
        if (all) {
            payload->effect = func_080D3F08(payload->effect);
            if (payload->effect == 0) {
                payload->child = func_080E051C(payload->child);
                if (payload->child == 0) {
                    func_0800C1C8(1);
                    func_08011428(*payload->handle);
                    *payload->handle = 0;
                    g_control_flags_03000940.display &= ~func_080035A8(1);
                    g_control_flags_03000940.display &= ~func_080035A8(3);
                    g_control_flags_03000940.display &= 0xDFFF;
                    g_control_flags_03000940.bldcnt_lo = 0;
                    clear = 0;
                    func_0814186C(&clear, data_03003920, 0x01000010);
                    func_080D7220(data_088F5F08, 0, 2, 0, 0, 0);
                    descriptor->phase = 2;
                }
            }
        }
        break;
    }
    return 0;
}
