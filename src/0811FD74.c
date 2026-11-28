#include "ffta.h"
#include "control_flags.h"

/* Complete [0x0811FD74, 0x0811FFD6): 610 bytes, including its literal pools.
 * Target bytes:
 * f0b583b0061c0f1c151c29888020000208400004040c002c00d01de139888020
 * 400081421dd0814202dc00290cd013e10448814200d19de00130814200d103e1
 * 0ae1000001010000b88a2872f88a6872388ba8727a682a61b8680021a8811170
 * fae00020e3f6fafb1d4a3f218143131c423318781970111c443108783f200870
 * 093908780c70013908780c70053108780c7001390878ff200870118880239b01
 * 181c084310800022287a002800d1f02200200021331cbaf7abfe68610121b9f7
 * b9feaa890c21685e00280bda524212041214684600219f23c0f7dcfb09e00000
 * 400900030c23e95e684600229f23c0f7d1fb687a002819d100242e1c18366200
 * b2180948201801784942118068460088091a11806846c0f7dffb601c0006040e
 * 9f2cecd918e0000088783a0800242e1c18366200b2180e4820180178f0311180
 * 68460088091811806846c0f7c5fb601c0006040e9f2cecd9ac21490068189822
 * 5200ab7a0021c0f795fb3888013072e088783a08ac235b00ec18201cc0f7acfb
 * 6869baf75dfe061c0022182040198446687a002813d11204d113614420880988
 * 40180004030c0014002801da002302e0f02800ddf023287a002818d012e01204
 * d013604400882188401a0004030c0014002801da002302e0f02800ddf023287a
 * 002804d1d01380190178037003e0d013801941784370802149025018020c0014
 * 9f28c5dd28690078002807d1ac235b00e818c0f783fb000600281dd0084c2088
 * 084901402180287a012805d10020e3f601fb218881432180388801300be00000
 * 40090003ffdf00006869b9f7d1fd6861002801d102203880002003b0f0bc02bc
 * 0847
 */

typedef struct InterpolationState {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} InterpolationState;

/* The script 0811FFD8 starts this task with (its ObjectScript): hide is the
 * category (0 for the first wipe, 1 for the second), from_right the variant
 * (data_083A7955), duration the delay (80 frames), slant its unknown_08
 * (data_083A7960), and done points at 0811FFD8's own done flag. */
typedef struct {
    u16 state;
    u16 unknown_02;
    u8 *done;
    s32 slant;
    u8 unknown_0c[8];
    u16 hide;
    u16 from_right;
    u16 duration;
} WipeScript;

/* The task's payload (0811FFD8 asks for 0x168 bytes). */
typedef struct {
    u16 flags;
    u8 unknown_02[6];
    u8 hide;
    u8 from_right;
    u8 duration;
    u8 unknown_0b;
    s16 slant;
    u8 unknown_0e[2];
    u8 *done;
    void *window;
    s16 edges[160];
    InterpolationState sweep;
} Wipe;

/* One row of a window task's scanline payload (func_080DABB4), in WINxH byte
 * order: the right edge (X2) in the low byte, the left edge (X1) in the high
 * byte.  src/080D9C58.c, src/080E61E4.c and src/0811435C.c declare the same
 * row type.
 *
 * volatile: the ROM loads the edge just before each store to it and never
 * uses the value (ldrb at 0x0811FF5C before the strb at 0x0811FF5E, ldrb at
 * 0x0811FF66 before the strb at 0x0811FF68); without the qualifier agbcc
 * drops both loads.  The rows are the payload func_080DABB4 returns for
 * wipe->window, the task func_080DAB84 starts in step 0x100: its callback
 * func_080D9C58 keeps the scanline task it allocates (func_0800C3CC) in its
 * data word +4, which is what func_080DABB4 reads. */
typedef struct __attribute__((packed)) {
    volatile u8 right : 8;
    volatile u8 left : 8;
} WindowLine;

/* The wipe's ragged front: one offset of 0..63 pixels per row, 160 bytes up
 * to data_083A7928. */
extern const u8 data_083A7888[160];

extern u16 func_080035D0(u8);
extern u16 func_080035A8(u8);
extern void *func_080DAB84(u8, u8, u8, void *);
extern void func_080D9BA8(void *, u8);
extern void *func_080DABB4(void *);
extern void *func_080D9B64(void *);
extern void func_080E0608(InterpolationState *, s16, s16, s16);
extern void func_080E064C(InterpolationState *);
extern u8 func_080E0690(InterpolationState *);

/* A horizontal window wipe that reveals (hide 0) or hides (hide 1) BG0
 * (func_080035D0(0) is its window bit, func_080035A8(0) its DISPCNT bit);
 * 0811FFD8 starts it twice.  0 copies the script.  0x100 turns window 0 on
 * with BG0 masked out inside it, starts the window task func_080DAB84 (rows
 * full width when revealing, empty when hiding) and enables its scanline
 * task, sets each row's edge from the ragged front plus a slant spread over
 * the 160 rows, and starts a sweep of 304 pixels (the screen width and the
 * front's 64-pixel depth) over duration frames.  0x101 takes one sweep step
 * and moves one edge of every row with it, rightwards unless from_right: the
 * left edge when revealing from the left or hiding from the right, else the
 * right one.  When the sweep ends or *done is set it turns window 0 off, and
 * after a hiding wipe BG0 as well.  0x102 asks the window task to finish (it
 * stops its scanline task) and waits until it has. */
u32 func_0811FD74(void *task, WipeScript *script, Wipe *wipe)
{
    InterpolationState skew;
    u8 i;
    s16 row;
    WindowLine *lines;
    u8 right;

    if (wipe->flags & 0x8000)
        return 0;

    switch (script->state) {
    case 0:
        wipe->hide = script->hide;
        wipe->from_right = script->from_right;
        wipe->duration = script->duration;
        wipe->done = script->done;
        wipe->slant = script->slant;
        *wipe->done = 0;
        break;
    case 0x100:
        g_control_flags_03000940.winin_lo = 0x3f & ~func_080035D0(0);
        g_control_flags_03000940.winout_lo = 0x3f;
        g_control_flags_03000940.win0h_hi = 0;
        g_control_flags_03000940.win0h_lo = 0;
        g_control_flags_03000940.win0v_hi = 0;
        g_control_flags_03000940.win0v_lo = 0xff;
        g_control_flags_03000940.display |= 0x2000;
        right = 0;
        if (!wipe->hide)
            right = 240;
        wipe->window = func_080DAB84(0, 0, right, task);
        func_080D9BA8(wipe->window, 1);
        if (wipe->slant < 0)
            func_080E0608(&skew, 0, -wipe->slant, 159);
        else
            func_080E0608(&skew, wipe->slant, 0, 159);
        if (!wipe->from_right) {
            for (i = 0; i < 160; i++) {
                wipe->edges[i] = -data_083A7888[i];
                wipe->edges[i] -= skew.current;
                func_080E064C(&skew);
            }
        } else {
            for (i = 0; i < 160; i++) {
                wipe->edges[i] = data_083A7888[i] + 240;
                wipe->edges[i] += skew.current;
                func_080E064C(&skew);
            }
        }
        func_080E0608(&wipe->sweep, 0, 304, wipe->duration);
        script->state++;
        break;
    case 0x101:
        func_080E064C(&wipe->sweep);
        lines = func_080DABB4(wipe->window);
        for (row = 0; row < 160; row++) {
            s16 x;

            if (!wipe->from_right) {
                x = wipe->edges[row] + wipe->sweep.current;
                if (x < 0)
                    x = 0;
                else if (x > 240)
                    x = 240;
                if (!wipe->hide)
                    lines[row].left = x;
                else
                    lines[row].right = x;
            } else {
                x = wipe->edges[row] - wipe->sweep.current;
                if (x < 0)
                    x = 0;
                else if (x > 240)
                    x = 240;
                if (!wipe->hide)
                    lines[row].right = x;
                else
                    lines[row].left = x;
            }
        }
        if (*wipe->done || func_080E0690(&wipe->sweep)) {
            g_control_flags_03000940.display &= 0xdfff;
            if (wipe->hide == 1)
                g_control_flags_03000940.display &= ~func_080035A8(0);
            script->state++;
        }
        break;
    case 0x102:
        wipe->window = func_080D9B64(wipe->window);
        if (!wipe->window)
            script->state = 2;
        break;
    }
    return 0;
}
