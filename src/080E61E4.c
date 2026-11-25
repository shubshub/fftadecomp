#include "ffta.h"
#include "control_flags.h"

/* Complete [0x080E61E4, 0x080E6590): 940 bytes, 408 instructions.
 * Target bytes: f0b557464e464546e0b487b0041c8a46171c09888020400081422fd0814202dc00290bd0b9e10448814200d1e4e00130814200d1a8e1b0e101010000514648687861898a3971ba1c391c0023f7f78afab861084801240094062100220023eef7c5f905480094072100220023eef7bef993e10000cca28e08709c8e080022b85e0223f95e012500953a1c20320192524a0292039400220123eff70cff78624f48211cedf709feb8624d48211ceef738faf8623979281c08400222002800d004227869484900920194322202920c223223f6f796feb8633979281c08400822002800d01022404804210a43009401210023f9f75afdf86301200021ff22231cf4f74ffc7863002000210022231cf4f748fc3863381c0830354d2a786978090211430904091400222823faf77cf9304eb1463e2048448046ff2041460870403630780120404230702b4d002400940194281c002102220023f0f771ff00940194281c012103220023f0f769ff49463b3108780c70013908780c70033108780c7001390878f0200870b87820384a463f3211781070b9782039154b1a7858780002104340184546297828704946413108780c703078a02030704e46318880229201101c08438023db01191c084330805546288801302880e1e00000a4733908a8d7940838959408bc733908d073390850df940840090003cc468f083c1c0834201cfaf755f900060594002800d083e0404c3e7a06960598faf728f9786bf4f7d9fb051c08203a5e5200e11c8a4650180078a31c9846d1180978401ac003000c04900226b85f400040382d18ad183b7a0698834218d2c146d04638785a004e46b1181438097840182978287038784244143812788018697868700235581c0006030e06988342e8d3786bf3f795fb386bf4f7a0fb051c0221785e400040382d180023217860780002084383420ed2002268786a7028782a700235581c0006030e21786078000208438342f1d30598faf7eff80006002862d1049a130498140006040e400e24182406240eba78203a3d7a52191206802676049219120e386b0025795f1b0c0094f4f7cbfb386bf3f754fb45e0000050df940802201df755f8184c21888143174801402180786aeff712fe7862002833d1b86aedf7f6fcb86200282dd103201df740f8218881430e4801402180f86aeef71ef9f86200281fd1386bf3f710fb3863002819d1786bf3f70afb7863002813d156463088013030800ee040090003ffdf0000ffbf0000b86bf5f775fab863002802d1022051460880002007b038bc9846a146aa46f0bc02bc0847 */
typedef struct {
    u16 state;
    u16 unknown_02;
    void *object;
    u8 unknown_08[0xC];
    u16 index;
    u16 selector;
    u32 unknown_18;
} Command080E61E4;

typedef struct InterpolationState {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} InterpolationState;

typedef struct {
    s16 x;
    s16 y;
    u8 index;
    u8 unknown_05[3];
    InterpolationState transition;
    void *object;
    void *actor;
    u8 unknown_1c[4];
    void *outputs[1];
    void *particle;
    void *effect_28;
    void *effect_2c;
    void *bottom;
    void *top;
    void *actor_effect;
    void *effect_3c;
} State080E61E4;

/* One row of a window task's scanline payload (func_080DABB4), in WINxH byte
 * order; the scanline manager hands the rows to HBlank DMA.  src/080D9C58.c,
 * src/080DA968.c and src/0811435C.c declare the same row type.
 *
 * volatile: each byte store through it is preceded by a load of the same
 * byte that nothing reads (0x080E6448, 0x080E6456, 0x080E6490, 0x080E6494);
 * without the qualifier agbcc drops all four. */
typedef struct __attribute__((packed)) {
    volatile u8 right : 8;
    volatile u8 left : 8;
} WindowLine;

/* A row of data_0894DF50, copied into a WindowLine byte for byte. */
typedef struct __attribute__((packed)) {
    u8 right;
    u8 left;
} Span;

/* data_0894DF50: a row count (41) and that many rows, 84 bytes up to the
 * next referenced object (0x0894DFA4).  The ROM reads the count a byte at a
 * time (0x080E62FC, 0x080E637C, 0x080E6482, 0x080E64A0). */
typedef struct __attribute__((packed)) {
    u16 count;
    Span rows[41];
} SpanTable;

extern const SpanTable data_0894DF50;
extern const u8 data_088EA2CC[];
extern const u8 data_088E9C70[];
extern const u8 data_083973A4[];
extern const u8 data_0894D7A8[];
extern const u8 data_08949538[];
extern const u8 data_083973BC[];
extern const u8 data_083973D0[];
extern const u8 data_088F46CC[];

extern void *func_080DD748(void *, s16 *, s16 *, s16 *);
extern void func_080D45D0(const void *, u8, u8, u8, u8);
extern void *func_080D6098(s16, s16, u16, u8, u16, void **, const void *, void *);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D4704(const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, s16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080DAB84(u8, u8, u8, void *);
extern void func_080E0608(InterpolationState *, s16, s16, s16);
extern void func_080D7220(const void *, u8, u8, s16, s16, u16);
extern u8 func_080E0690(InterpolationState *);
extern void func_080E064C(InterpolationState *);
extern void *func_080DABB4(void *);
extern void func_080D9B98(void *);
extern void func_080DAC80(void *, s16, s16, u16, u16);
extern u16 func_080035A8(u8);
extern void *func_080D6134(void *);
extern void *func_080D3F08(void *);
extern void *func_080D4774(void *);
extern void *func_080D9B64(void *);
extern void *func_080DBA5C(void *);

/* The task that 080E6590 starts for each object of its group
 * (func_08005B6C(func_080E61E4, 0x40, ...), passing the object and its
 * number).  0 takes the object's position and loads two palettes.  0x100
 * starts five effect tasks and the scanline tasks of window 1 (top) and
 * window 0 (bottom), sets the window registers, and starts a transition from
 * the table's 41 rows down to 0 in 40 steps.  0x101 takes one step per call:
 * it copies the table rows the step has passed into window 1's rows, clears
 * window 0's 41 rows and draws an ellipse as wide as the current table row
 * into them.  Once the transition has ended it clears the window enable bits
 * and waits for each task to end.  0x102 waits for the actor effect. */
u32 func_080E61E4(void *task, Command080E61E4 *command, State080E61E4 *state)
{
    switch (command->state) {
    case 0:
        state->object = command->object;
        state->index = command->index;
        state->actor = func_080DD748(state->object, &state->x, &state->y, 0);
        func_080D45D0(data_088EA2CC, 6, 0, 0, 1);
        func_080D45D0(data_088E9C70, 7, 0, 0, 1);
        break;
    case 0x100: {
        const SpanTable *table;
        u16 mode;

        state->particle = func_080D6098(state->x, state->y, 0, 1, 1,
            state->outputs, data_083973A4, task);
        state->effect_28 = func_080D3E9C(data_0894D7A8, task);
        state->effect_2c = func_080D4704(data_08949538, task);
        if (state->index & 1)
            mode = 4;
        else
            mode = 2;
        state->actor_effect = func_080DCFE4(state->object, data_083973BC, 12,
            0x32, mode, task, 0x32);
        if (state->index & 1)
            mode = 0x10;
        else
            mode = 8;
        state->effect_3c = func_080DFD8C(data_083973D0, 1, mode | 4, 0, task);
        table = &data_0894DF50;
        state->top = func_080DAB84(1, 0, 0xff, task);
        state->bottom = func_080DAB84(0, 0, 0, task);
        func_080E0608(&state->transition, table->count, 0, 0x28);
        g_control_flags_03000940.win0v_lo = 0xff;
        g_control_flags_03000940.win1v_lo = 0xff;
        func_080D7220(data_088F46CC, 0, 2, 0, 0, 0);
        func_080D7220(data_088F46CC, 1, 3, 0, 0, 0);
        g_control_flags_03000940.win0h_hi = 0;
        g_control_flags_03000940.win0h_lo = 0;
        g_control_flags_03000940.win1h_hi = 0;
        g_control_flags_03000940.win1h_lo = 0xf0;
        g_control_flags_03000940.win0v_hi = state->y - 0x20;
        g_control_flags_03000940.win0v_lo = state->y - 0x20 + table->count;
        g_control_flags_03000940.win1v_hi = 0;
        g_control_flags_03000940.win1v_lo = 0xa0;
        g_control_flags_03000940.display |= 0x2000;
        g_control_flags_03000940.display |= 0x4000;
        command->state++;
        break;
    }
    case 0x101: {
        WindowLine *lines;
        const SpanTable *table;
        u8 end;
        u8 i;
        s16 radius;
        u8 height;
        u8 row;

        if (!func_080E0690(&state->transition)) {
            table = &data_0894DF50;
            end = state->transition.current;
            func_080E064C(&state->transition);
            lines = func_080DABB4(state->top);
            radius = table->rows[state->transition.current].left
                - table->rows[state->transition.current].right;
            radius >>= 1;
            lines += state->y - 0x20;
            lines += state->transition.current;
            for (i = state->transition.current; i < end; i++) {
                lines->right = state->x - 0x14 + table->rows[i].right;
                lines->left = state->x - 0x14 + table->rows[i].left;
                lines++;
            }
            func_080D9B98(state->top);
            lines = func_080DABB4(state->bottom);
            lines += state->y - 0x20;
            for (i = 0; i < table->count; i++) {
                lines->left = 0;
                lines->right = 0;
                lines++;
            }
            if (!func_080E0690(&state->transition)) {
                height = radius >> 2;
                height += height >> 1;
                row = state->y - 0x20 + state->transition.current;
                row++;
                func_080DAC80(state->bottom, state->x, row, radius, height);
                func_080D9B98(state->bottom);
            }
        } else {
            g_control_flags_03000940.display &= ~func_080035A8(2);
            g_control_flags_03000940.display &= 0xdfff;
            state->particle = func_080D6134(state->particle);
            if (state->particle)
                break;
            state->effect_28 = func_080D3F08(state->effect_28);
            if (state->effect_28)
                break;
            g_control_flags_03000940.display &= ~func_080035A8(3);
            g_control_flags_03000940.display &= 0xbfff;
            state->effect_2c = func_080D4774(state->effect_2c);
            if (state->effect_2c)
                break;
            state->bottom = func_080D9B64(state->bottom);
            if (state->bottom)
                break;
            state->top = func_080D9B64(state->top);
            if (state->top)
                break;
            command->state++;
        }
        break;
    }
    case 0x102:
        state->actor_effect = func_080DBA5C(state->actor_effect);
        if (!state->actor_effect)
            command->state = 2;
        break;
    }
    return 0;
}
