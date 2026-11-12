#include "ffta.h"

typedef struct {
    u32 source_offset;
    u32 list_offset;
    u8 duration;
    u8 command;
    u8 value;
    u8 setting;
    u16 first;
    u16 second;
    u8 unknown_10;
    u8 flip_x;
    u8 flip_y;
    u8 unknown_13;
} Frame08021484;

typedef struct Animation08021484 {
    u32 flags;
    u8 unknown_04[6];
    s16 timer;
    s16 frame_index;
    s16 frame_count;
    u8 setting;
    s8 half_speed_timer;
    u16 tile;
    u16 saved_tile;
    u8 unknown_16[2];
    u16 first;
    u16 second;
    u8 unknown_1C[2];
    u8 changed;
    u8 unknown_1F;
    u32 source_offset;
    u16 tile_count;
    u8 unknown_26[2];
    const u8 *pending_list;
    const u8 *list;
    u8 unknown_30[4];
    const Frame08021484 *first_frame;
    const Frame08021484 *current_frame;
} Animation08021484;

typedef struct Transfer08021484 {
    u8 status;
    u8 kind;
    u8 unknown_02[2];
    const void *source;
    void *destination;
    u32 control;
    u8 unknown_10[8];
    struct Transfer08021484 *next;
} Transfer08021484;

typedef struct {
    Transfer08021484 records[4][4];
    u16 used_tiles[4];
    s16 current;
    s16 count;
    s16 capacity;
    u16 unknown_1CE;
    Animation08021484 *pending;
} Context08021484;

extern Animation08021484 *func_080C7B74(const void *node);
extern void func_08021290(Animation08021484 *animation, Context08021484 *context);
extern const u8 *func_08021044(void);
extern void func_08000ADC(Transfer08021484 *record, const void *source, void *destination, u16 words);
extern u8 data_06010000[];

/* Complete target [0x08021484, 0x0802158C), 264 bytes. */
u32 func_08021484(const void *node, Context08021484 *context)
{
    Animation08021484 *animation = func_080C7B74(node);

    func_08021290(animation, context);
    if ((animation->flags & 0x180080) != 0x80000) {
        if (animation->list != 0) {
            if ((u16)(context->used_tiles[context->current] + animation->tile_count) > 24) {
                goto defer_transfer;
            } else if (context->count >= context->capacity) {
                if (context->pending == 0)
                    context->pending = animation;
defer_transfer:
                animation->flags |= 0x100000;
            } else {
                Transfer08021484 *record;
                const u8 *source;

                animation->flags &= ~0x100000;
                if (animation->flags & 0x80)
                    animation->tile = animation->saved_tile;
                animation->flags = (animation->flags & ~0x20080) | 0x90000;
                animation->flags |= 0x20000;
                animation->pending_list = animation->list;
                record = &context->records[context->current][context->count];
                source = func_08021044() + animation->source_offset;
                func_08000ADC(record, source, data_06010000 + animation->tile * 32,
                              (u16)(animation->tile_count << 3));
                context->count++;
            }
        }
    }
    return 1;
}
