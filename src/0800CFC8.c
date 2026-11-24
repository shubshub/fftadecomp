#include "ffta.h"

/* Complete [0x0800CFC8, 0x0800D090), 200 bytes.
 * Starts the affine scanline effect on BG2 or BG3 in mode 1:
 * a circle, with line offsets. Nothing in this ROM calls it
 * (see its entry in config/stack_index_premises.json). */

struct BgAffineSrc {
    s32 texX;
    s32 texY;
    s16 scrX;
    s16 scrY;
    s16 sx;
    s16 sy;
    u16 alpha;
};

/* The payload of the affine scanline task, read every frame by func_0800D3BC. */
typedef struct {
    u16 mode;
    s16 screen_x;
    s16 screen_y;
    s16 offset_x;
    s16 offset_y;
    u8 unknown_0A[2];
    struct BgAffineSrc src;
    struct BgAffineSrc line;
    u16 radius_x;
    u16 radius_y;
    s16 line_offset_y[160];
    s16 line_scale_x[160];
} AffineWave;

/* BG2PA and BG3PA: only BG2 and BG3 have affine registers. */
typedef struct {
    u16 *bg[2];
} AffineRegisters;

typedef void (*ObjectCallback)(void *state, u16 *destination);
typedef struct ScanlineTask ScanlineTask;
struct Object0800C614;

extern const AffineRegisters data_08149820;
extern void func_0800D3BC(void *state, u16 *destination);
extern ScanlineTask *func_0800C3CC(ObjectCallback callback, u16 payload_bytes,
                                   u16 element_size, u16 *destination);
extern void *func_0800C614(const struct Object0800C614 *object);
extern void func_0800C9E4(AffineWave *wave, u8 make_offsets);

void *func_0800CFC8(u8 bg, u16 x, u16 y, u16 radius, u16 offset_x, u16 offset_y)
{
    AffineRegisters registers = data_08149820;
    void *task = func_0800C3CC(func_0800D3BC, sizeof(AffineWave), 0x10,
                               registers.bg[bg - 2]);
    AffineWave *wave = func_0800C614(task);
    s32 x0;
    s32 y0;
    s32 dx;
    s32 dy;

    wave->mode = 1;
    wave->screen_x = x;
    wave->screen_y = y;
    wave->offset_x = offset_x;
    wave->offset_y = offset_y;
    x0 = (s16)x;
    wave->src.texX = x0 * 256;
    y0 = (s16)y;
    wave->src.texY = y0 * 256;
    dx = (s16)offset_x;
    wave->src.scrX = x0 + dx;
    dy = (s16)offset_y;
    wave->src.scrY = y0 + dy;
    wave->src.sx = 0x100;
    wave->src.sy = 0x100;
    wave->line.texX = x0 * 256;
    wave->line.texY = y0 * 256;
    wave->line.scrX = x0 + dx;
    wave->line.scrY = y0 + dy;
    wave->line.sx = 0x100;
    wave->line.sy = 0x100;
    wave->radius_x = radius;
    func_0800C9E4(wave, 1);
    return task;
}
