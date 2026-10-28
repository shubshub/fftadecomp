typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct AnimationGroup {
    u16 length;
    u8 frames[6];
} __attribute__((packed, aligned(2)));

struct AnimationRecords {
    u8 header[6];
    struct AnimationGroup groups[2];
    u8 unknown_16[6];
};

union AnimationData {
    struct AnimationRecords records;
    struct {
        u8 header[8];
        u8 frames[20];
    } frame_data;
};

struct Menu {
    u8 unknown_00[0x10];
    u8 left;
    u8 top;
    u8 width;
    u8 height;
    u8 unknown_14[0x18];
};

struct AnimationSource {
    u16 id;
};

struct AnimationState {
    u8 unknown_00[9];
    u8 flags;
    u16 timer;
    u8 indices[3];
    u8 count;
    u8 unknown_10[0x18];
    struct Menu menu;
    u8 list[0x48];
    union AnimationData animation;
    struct AnimationSource *source;
    u32 menu_value;
};

struct GraphicsState {
    u8 unknown_00[0x10];
    u8 *tiles;
};

extern u8 data_02003CB0[];
extern struct GraphicsState data_030008B0;
extern int func_080C8D14(u16 id, void *animation);
extern void func_080CB9E0(void *buffer, u8 frame);
extern void func_0814186C(const void *source, void *destination, u32 size);
extern u8 func_080CBA14(u8 frame);
extern void func_0802AB64(void *list, u16 position, u16 tile, u8 width, int height, u8 palette, int flags);
extern void func_0802AC14(struct Menu *menu, u32 value, u8 left, u8 top, u8 height);

void func_08068998(struct AnimationState *state)
{
    u8 blocked = state->flags & 8;
    int index;

    if (blocked)
        return;

    if (state->timer == 0) {
        void *list = state->list;
        struct Menu *menu = &state->menu;
        int width = menu->width;
        void *buffer = data_02003CB0;

        state->timer++;
        state->count = func_080C8D14(state->source->id, &state->animation);
        for (index = 0; index < state->count; index++) {
            u16 tile = 0x251 + index * 8;
            u8 *frame = &state->animation.frame_data.frames[index * 8 + state->indices[index]];
            u8 palette;


            if (*frame == 0xFF) {
                state->count = 0;
                break;
            }
            func_080CB9E0(buffer, *frame);
            func_0814186C(buffer, data_030008B0.tiles + tile * 32, 128);
            palette = func_080CBA14(*frame);
            func_0802AB64(list, width * 7 + 1 + width * 4 * index, tile, width, 4, palette, 0);
        }
        if (state->count)
            func_0802AC14(menu, state->menu_value, menu->left, menu->top, menu->height);
    } else {
        state->timer++;
        if (state->timer > 63) {
            state->timer = 0;
            for (index = 0; index < state->count; index++) {
                state->indices[index]++;
                if (state->indices[index] >= state->animation.records.groups[index].length)
                    state->indices[index] = 0;
            }
        }
    }
}
