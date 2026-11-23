// Complete target [0x080ED308, 0x080ED3B8), 176 bytes, 84 instructions:
// f0b5071cec21490078180068ecf7f8fb031c0024a82040003918086884420cda
// 0025102218781d7058785a70601c0006040e023308688442f4db0025a8214900
// 78180068002802da40420006050e1e2d16d8164e701c84466900881900781a78
// 18706144087859785870681c0006050e601c0006040e02339f2c0ed81e2debd9
// 9f2c0ad810211878197058785970601c0006040e02339f2cf5d9ec2149007818
// 0068ecf7f5fbf0bc01bc0047b8923908
#include "ffta.h"

typedef struct LineState {
    s32 x;
    s32 y;
    s32 endX;
    s32 endY;
    s32 stepX;
    s32 stepY;
    s32 deltaX;
    s32 deltaY;
    s32 accumulator;
    s32 error;
    s32 remaining;
} LineState;

/* The wave effect's state, as its command handler func_080ED4E8, the only
 * caller (0x080ED666), declares it.  fade.x is the row the fade has reached:
 * 080ED4E8 starts the line at 160, steps it once before each call and stops
 * after the call that reaches -31, 30 steps later.  window is the blend
 * display task func_080D9A24 created. */
typedef struct {
    u8 active;
    u8 unknown_01;
    u16 timer;
    s16 base;
    s16 offsets[160];
    u8 phase_a;
    u8 phase_b;
    u16 phase_c;
    u8 unknown_14A[2];
    u16 *samples;
    LineState fade;
    LineState first;
    LineState second;
    void *scanline_task;
    void *window;
    void *effect;
    void *closing;
} Wave080ED4E8;

/* One BLDALPHA row of the blend display's scanline payload, as 0800DB0C
 * writes it. */
typedef struct __attribute__((packed)) {
    u8 eva : 8;
    u8 evb : 8;
} BlendRow;

extern void *func_080D9B08(void *task);
extern void func_080D9B98(void *task);
/* 31 rows of (EVA, EVB): EVA climbs unevenly from 0 to 16, EVB stays 16. */
extern const u8 gUnknown_083992B8[][2];

/* Writes the blend coefficients of all 160 rows for the fade's current row:
 * the rows above it show only the second target (EVA 0, EVB 16), the next 31
 * rows the ramp gUnknown_083992B8, and the rows below both targets at full
 * weight (16, 16).  func_080D9B98 then marks the payload changed, so that
 * the scanline manager 0800C4B4 has the task's callback 0800DEC0 copy it
 * into the bank HBlank DMA sends to BLDALPHA. */
void func_080ED308(Wave080ED4E8 *wave)
{
    /* volatile: the ROM loads each byte of a row just before storing it and
     * never uses the value (ldrb at 0x080ED32C, 0x080ED330, 0x080ED366,
     * 0x080ED36E, 0x080ED38E and 0x080ED392, each followed by the strb of the
     * same byte); without the qualifier agbcc drops all six.  The rows are
     * the scanline payload func_080D9B08 returns. */
    volatile BlendRow *line = func_080D9B08(wave->window);
    u8 row;
    u8 i;

    for (row = 0; row < wave->fade.x; row++, line++) {
        line->eva = 0;
        line->evb = 16;
    }
    i = 0;
    if (wave->fade.x < 0)
        i = -wave->fade.x;
    while (i <= 30) {
        line->eva = gUnknown_083992B8[i][0];
        line->evb = gUnknown_083992B8[i][1];
        i++;
        row++;
        line++;
        if (row > 159)
            break;
    }
    for (; row <= 159; row++, line++) {
        line->eva = 16;
        line->evb = 16;
    }
    func_080D9B98(wave->window);
}
