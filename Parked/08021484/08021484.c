#include "ffta.h"

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

typedef struct Animation {
    u32 flags;
    u8 unknown_04[0xE];
    u16 tile;
    u16 alternate_tile;
    u8 unknown_16[0xA];
    u32 source_offset;
    u16 size;
    u8 unknown_26[2];
    u32 image;
    u32 next_image;
} Animation;

typedef struct {
    TransferRecord transfers[4][4];
    u16 used[4];
    s16 bank;
    s16 count;
    s16 limit;
    u8 unknown_1CE[2];
    Animation *deferred;
} TransferContext;

extern u8 data_06010000[];
extern Animation *func_080C7B74(void *object);
extern void func_08021290(Animation *animation, TransferContext *context);
extern u32 func_08021044(void);
extern void func_08000ADC(TransferRecord *entry, const void *source, void *destination, u16 words);

/* Complete target: [0x08021484, 0x0802158C), 264 bytes. */
int func_08021484(void *object, TransferContext *context)
{
    Animation *animation = func_080C7B74(object);
    u32 image;

    func_08021290(animation, context);
    if ((animation->flags & 0x180080) != 0x80000 &&
        (image = animation->next_image) != 0) {
            if ((u16)(context->used[context->bank] + animation->size) > 24 ||
                context->count >= context->limit) {
                if ((u16)(context->used[context->bank] + animation->size) <= 24 &&
                    context->deferred == 0)
                    context->deferred = animation;
                animation->flags |= 0x100000;
            } else {
                animation->flags &= ~0x100000;
                if (animation->flags & 0x80)
                    animation->tile = animation->alternate_tile;
                animation->flags = (animation->flags & ~0x20080) | 0x90000;
                animation->flags |= 0x20000;
                animation->image = image;
                func_08000ADC(&context->transfers[context->bank][context->count],
                              (const void *)(func_08021044() + animation->source_offset),
                              &data_06010000[animation->tile * 32],
                              (u16)(animation->size * 8));
                context->count++;
            }
    }
    return 1;
}
