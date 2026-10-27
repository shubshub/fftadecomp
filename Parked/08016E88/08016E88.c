#include "ffta.h"

/* Target: complete [0x08016E88, 0x08016FE4), 348 bytes. */
typedef struct {
    u16 *tiles;
    u16 *alternate_tiles;
    u8 unknown_08[12];
    u16 flags;
    u8 tile_offset;
    u8 palette;
    u8 unknown_18[5];
    u8 left_label;
    u8 right_label;
} LabelFrame;

extern s32 func_080185B8(u32 label);

void func_08016E88(LabelFrame *frame, u16 offset, u8 width)
{
    s32 left_length = 0;
    s32 i;
    u8 end;
    u16 tile;
    u16 *tiles;

    if (frame->flags & 0x1420)
        return;

    if (frame->left_label) {
        left_length = func_080185B8(frame->left_label & 0x7f);
        if (frame->left_label & 0x80) {
            u8 right_length = func_080185B8(frame->right_label & 0x7f);
            i = (u8)(width - right_length - left_length - 2);
            end = width - right_length - 2;
            left_length += right_length;
        } else {
            i = 1;
            end = left_length + 1;
        }
        if (width > left_length + 1) {
            if (frame->flags & 0x800) {
                tiles = frame->alternate_tiles + offset;
                tile = (frame->palette << 12) + 0x4a;
            } else {
                tiles = frame->tiles + offset + frame->tile_offset;
                tile = (frame->palette << 12) + 0x3e;
            }
            for (; i < end; ++i)
                tiles[i] = tile++;
        }
    }

    if (frame->right_label) {
        s32 right_length = func_080185B8(frame->right_label & 0x7f);
        if (frame->right_label & 0x80) {
            left_length = 0;
            i = 1;
            end = right_length + 1;
        } else {
            i = (u8)(width - right_length - 1);
            end = width - 1;
        }
        if (width > left_length + right_length + 1) {
            if (frame->flags & 0x800) {
                tiles = frame->alternate_tiles + offset;
                tile = (frame->palette << 12) + 0x4a;
            } else {
                tiles = frame->tiles + offset + frame->tile_offset;
                tile = (frame->palette << 12) + 0x44;
            }
            for (; i < end; ++i)
                tiles[i] = tile++;
        }
    }
}
