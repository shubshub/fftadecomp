#include "ffta.h"

typedef struct {
    u8 unknown_00[0x28];
    u32 flags;
} Source0809EA60;

typedef struct {
    u16 current;
    u16 depth;
    u16 history[34];
} Sequence0809EA60;

typedef struct {
    Source0809EA60 *source;
    u8 unknown_04[0x60];
    u32 timestamp;
    u8 unknown_68[0x64];
    Sequence0809EA60 sequence;
} Context0809EA60;

extern void (*g_callbacks_0836D4B8[])(void *destination, u32 bytes);
extern u32 *func_08002830(void);
extern u8 func_080C95A8(u16 index);

static inline void push_state(Sequence0809EA60 *sequence)
{
    sequence->history[sequence->depth++] = sequence->current;
}

/* 0x0809EA60..0x0809ED38: 728 bytes, 359 instructions. */
void func_0809EA60(Context0809EA60 *context, Source0809EA60 *source)
{
    g_callbacks_0836D4B8[0](context, sizeof(*context));
    context->timestamp = *func_08002830();
    context->source = source;
    context->sequence.current = 0x27;
    push_state(&context->sequence);
    context->sequence.current = 0x1F;
    push_state(&context->sequence);
    context->sequence.current = 0x26;
    push_state(&context->sequence);
    context->sequence.current = 0x1A;
    push_state(&context->sequence);
    context->sequence.current = 0x18;
    push_state(&context->sequence);
    context->sequence.current = 6;
    push_state(&context->sequence);
    context->sequence.current = 4;
    push_state(&context->sequence);
    context->sequence.current = 5;
    push_state(&context->sequence);
    context->sequence.current = 2;
    push_state(&context->sequence);
    context->sequence.current = 6;
    push_state(&context->sequence);
    context->sequence.current = 0;

    if (context->source->flags & 6) {
        push_state(&context->sequence);
        context->sequence.current = 0xA;
    }
    if (context->source->flags & 8) {
        push_state(&context->sequence);
        context->sequence.current = 0xB;
    }
    if (context->source->flags & 0x10) {
        push_state(&context->sequence);
        context->sequence.current = 0xC;
    }
    if (context->source->flags & 0x20) {
        push_state(&context->sequence);
        context->sequence.current = 0xD;
    }
    if (context->source->flags & 0x40) {
        push_state(&context->sequence);
        context->sequence.current = 0xE;
    }
    if (context->source->flags & 0x80) {
        push_state(&context->sequence);
        context->sequence.current = 0xF;
    }
    if (context->source->flags & 0x300) {
        push_state(&context->sequence);
        context->sequence.current = 0x10;
    }
    if (context->source->flags & 0x400) {
        push_state(&context->sequence);
        context->sequence.current = 0x11;
    }
    if (context->source->flags & 0x800) {
        push_state(&context->sequence);
        context->sequence.current = 0x12;
    }
    if (context->source->flags & 0x1000) {
        push_state(&context->sequence);
        context->sequence.current = 0x13;
    }
    if (context->source->flags & 0x2000) {
        push_state(&context->sequence);
        context->sequence.current = 8;
        push_state(&context->sequence);
        context->sequence.current = 0x16;
    }
    if (context->source->flags & 0x4000) {
        push_state(&context->sequence);
        context->sequence.current = 0x14;
    }
    if (context->source->flags & 0x8000) {
        push_state(&context->sequence);
        context->sequence.current = 0x20;
    }
    push_state(&context->sequence);
    context->sequence.current = 0x24;
    if (func_080C95A8(0xD)) {
        push_state(&context->sequence);
        context->sequence.current = 0x28;
    }
}
