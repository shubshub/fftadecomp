#include "ffta.h"

struct Task;
struct Scheduler;

struct Data {
    u8 kind;
    u8 flags;
    u16 size;
    const void *data;
    const void *source;
};

struct Request {
    u16 state;
    u8 unknown_02[2];
    const struct Data *data;
    u8 unknown_08[12];
    u16 count;
    u8 unknown_16[6];
};

struct Effect {
    const struct Data *entries;
    u16 delay;
    u8 count;
    u8 index;
    u8 unknown_08[16];
    const void *source;
    void *destination;
    void *buffer;
    void *output;
};

extern struct Scheduler *data_0200F430;
extern void *func_08005B00(struct Scheduler *scheduler, u32 size);
extern void func_08005B0C(struct Scheduler *scheduler, void *allocation);
extern void *func_0800A654(u32 size);
extern void func_0800A668(void *allocation);
extern void func_08141868(const void *source, void *destination, u32 control);
extern u8 func_080D758C(struct Effect *effect);
extern u8 func_080D7798(struct Effect *effect);
extern u8 func_080D7864(struct Effect *effect);

/* Complete target 0x080D791C..0x080D7A70, 340 bytes. */
int func_080D791C(struct Task *task, struct Request *request, struct Effect *effect)
{
    switch (request->state) {
    case 0:
        effect->entries = request->data;
        effect->count = request->count;
        effect->buffer = func_08005B00(data_0200F430, 0x3000);
        effect->output = func_0800A654(0x4000);
        break;
    case 1:
        break;
    case 0x100: {
        u8 index;
        const struct Data *entries;
        const struct Data *entry;

        effect->source = 0;
        index = effect->index;
        entries = effect->entries;
        entry = (const struct Data *)(index * sizeof(*entries) + (u32)entries);
        if (entry->flags & 1) {
            switch (entry->kind) {
            case 4: {
                u32 fill = 0x03FF03FF;
                func_08141868(&fill, effect->output, 0x01001000);
                break;
            }
            case 5: {
                u32 fill = 0xFFFFFFFF;
                func_08141868(&fill, effect->output, 0x01001000);
                break;
            }
            default: {
                u32 fill = 0;
                func_08141868(&fill, effect->output, 0x01001000);
                break;
            }
            }
        }
        request->state = 0x101;
        if (func_080D758C(effect))
            break;
        /* Fall through to setup and transfer when ready. */
    }
    case 0x101:
        if (!func_080D7798(effect))
            break;
        request->state = 0x102;
        /* fall through */
    case 0x102:
        if (!func_080D7864(effect))
            break;
        if (++effect->index == effect->count)
            request->state = 0x103;
        else
            request->state = 0x100;
        break;
    case 0x103:
        effect->delay = 1;
        ++request->state;
        break;
    case 0x104:
        if (--effect->delay == 0) {
            func_08005B0C(data_0200F430, effect->buffer);
            effect->buffer = 0;
            func_0800A668(effect->output);
            effect->output = 0;
            request->state = 2;
        }
        break;
    }
    return 0;
}
