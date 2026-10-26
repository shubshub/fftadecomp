#include "ffta.h"

typedef struct {
    u8 unknown_00;
    u8 palette;
    u8 unknown_02[0x32];
    s8 x;
    s8 y;
    u8 unknown_36[0x12];
    s8 offset_x;
    s8 offset_y;
    s8 extra_x;
    u8 unknown_4B;
} RenderRecord;

typedef struct {
    u8 unknown_00[8];
    u16 width;
    u16 y;
    u16 x;
    u16 offset_y;
    u8 flags;
} RenderPanel;

extern RenderRecord data_030009E0[];
extern const u8 data_083919CE[];
extern const u8 data_083919C6[];

void func_08001F34(const u8 *graphics, s32 x, s32 y, u32 mode,
    u32 arg4, u32 arg5, u32 flip, u32 arg7, u32 width, u32 palette, u32 arg10);

/* Complete target: [0x08038028, 0x08038238), 528 bytes. */
void func_08038028(u32 index, RenderPanel *panel)
{
    u8 anchor = panel->flags & 0x80;

    if (anchor != 0) {
        u8 flip = panel->flags & 8;
        if (flip != 0) {
            RenderRecord *record = &data_030009E0[index];
            func_08001F34(data_083919CE,
                (record->x + record->extra_x + record->offset_x) * 8 + panel->x - 1,
                panel->y + panel->offset_y + (record->y + record->offset_y - 1) * 8 + 1,
                0, 0, 0, 0, 0, panel->width, record->palette, 0);
        } else {
            RenderRecord *record = &data_030009E0[index];
            func_08001F34(data_083919CE,
                (record->x + record->offset_x - 1) * 8 + panel->x - 1,
                panel->y + panel->offset_y + (record->y + record->offset_y - 1) * 8 + 1,
                0, 0, 0, 0, 0, panel->width, record->palette, 0);
        }
    } else {
        u8 flip = panel->flags & 8;
        if (flip != 0) {
            RenderRecord *record = &data_030009E0[index];
            func_08001F34(data_083919C6,
                panel->width + panel->x + (record->x + record->extra_x + record->offset_x + 4) * 8,
                panel->y + panel->offset_y + (record->y + record->offset_y - 1) * 8,
                0, 0, 0, 1, 0, 0, record->palette, 0);
        } else {
            RenderRecord *record = &data_030009E0[index];
            func_08001F34(data_083919C6,
                panel->width + panel->x + (record->x + record->offset_x - 1) * 8,
                panel->y + panel->offset_y + (record->y + record->offset_y - 1) * 8,
                0, 0, 0, 0, 0, 0, record->palette, 0);
        }
    }
}
