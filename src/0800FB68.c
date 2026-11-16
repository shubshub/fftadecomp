#include "ffta.h"

/* Complete [0x0800FB68, 0x0800FC04), 156 bytes, 69 instructions.
 * Target bytes:
 * 70b54e46454660b481b0041c0d1c161c984624062d042d0c3604360c40460004000c8046
 * 1b48a6218900e40d1a4aa4180222231cfcf716fc8146fcf737fd0580468003210171a223
 * 9b00c018414601804846fcf72bfd041cfa20009048460021a022f52300f044fa0022a05e
 * 0223e15ea2239b00e2181288083401230093231cfff73efa484601b018bc9846a14670bc
 * 02bc08473df9000840000004
 */

typedef struct {
    u16 left;
    u16 right;
} Scanline;

typedef struct {
    s16 x;
    s16 y;
    u8 type;
    u8 unknown_05;
    u16 flags;
    Scanline lines[160];
    u16 radius;
} RenderState;

typedef struct ScanlineTask ScanlineTask;

extern void func_0800F93C(RenderState *state, u16 *destination);
extern ScanlineTask *func_0800C3CC(
    void (*callback)(RenderState *, u16 *), u16 payload_bytes,
    u16 element_size, u16 *destination);
extern RenderState *func_0800C614(ScanlineTask *task);
extern void func_08010058(void *object, u16 first, u8 count,
                         u8 start, u8 end);
extern void func_0800F068(s16 x, s16 y, u16 radius, Scanline *lines,
                         u8 clip);

static inline void render_object(ScanlineTask *task)
{
    RenderState *state = func_0800C614(task);

    func_08010058(task, 0, 160, 245, 250);
    func_0800F068(state->x, state->y, state->radius, state->lines, 1);
}

ScanlineTask *func_0800FB68(u8 window, u16 x, u16 y, u16 radius)
{
    ScanlineTask *task = func_0800C3CC(func_0800F93C, 0x298, 2,
                                    (u16 *)0x04000040 + window);
    RenderState *state = func_0800C614(task);

    state->x = x;
    state->y = y;
    state->type = 3;
    state->radius = radius;
    render_object(task);
    return task;
}
