#include "ffta.h"
#include "effect_task.h"
#include "control_flags.h"

/* Target 0x0810533C..0x08105682, 838 bytes including literal pools; sha1 of
 * the ROM bytes 461660d510e819634dac78dea52a147f4b95029d.  The two 5-byte
 * initialisers are the ROM bytes at 0x08149E38 and 0x08149E3D.
 */

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 unknown_08[12];
    u16 kind;
    u16 flag;
} Request;

typedef struct {
    u16 counter;
    u8 index;
    u8 flag;
    u8 ready;
    u8 unknown_05;
    s16 x;
    s16 y;
    u8 unknown_0A[2];
    void *output;
    void *actor_object;
    void *output_task;
    void *unknown_18;
    void *coordinate_child;
    void *sprite;
    void *timeline;
    void *children[3];
    void *initial_child;
    void *actor;
    void *effect_child;
    void *record_child;
} State;

typedef struct {
    u8 unknown_00[20];
} EffectDescriptor;

extern const u8 data_0839F9C0[];
extern const void *const data_0839FA64[];
extern const u8 data_0839FB18[];
extern const void *const data_0839FA78[][3];
extern const u8 data_0839FB20[];
extern const void *const data_0839FA50[];
extern const u8 data_0839FB28[];
extern const EffectDescriptor data_0839FAB4[];
extern const u8 data_088E9C70[];
extern const u8 data_088EDC04[];
extern const u8 data_0894D7E4[];

extern void *memcpy(void *, const void *, unsigned long);
extern void *func_080E03F8(void *, const void *, u8, u8, const s16 *, void *);
extern void func_080D45D0(const void *, u8, u8, u8, u8);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern void *func_080DDF68(void *, void **, u16, u8, u8 *, const void *, u16, u16, void *);
extern u8 func_080D8CD4(void *);
extern u8 func_080D8B4C(void);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, s16 *);
extern void func_080D49FC(u8, u8, u16, s16, s16);
extern void *func_080D4B64(u8, const void *, u16, u8);
extern u16 func_080035A8(u8);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D4704(const void *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D3F08(void *);
extern u8 func_080D48DC(void **, u16);
extern void *func_080D4D2C(void *, u8);
extern u8 func_080DD670(void *, u8);
extern void *func_080D6098(s16, s16, u16, u8, u16, void **, const void *, void *);

extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

u32 func_0810533C(void *task, Request *request, State *state)
{
    u8 i;
    u8 mode;
    u16 extra;

    switch (request->phase) {
    case 0: {
        u8 rows[5] = {2, 3, 11, 6, 4};

        state->index = request->kind + 22;
        state->flag = request->flag;
        state->actor = request->actor;
        mode = 2;
        if (state->flag != 0)
            mode = 0;
        state->initial_child = func_080E03F8(state->actor, data_0839F9C0,
            mode, 0, 0, task);
        func_080D45D0(data_0839FA64[state->index], 6, 0, 0, 1);
        func_080D45D0(data_0839FA64[state->index], 7, 0, 0, 1);
        func_080D45D0(data_0839FA64[state->index], 8, 0, 0, 1);
        func_080D45D0(data_088E9C70, 6, 1, rows[state->index], 1);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->initial_child = func_080E05DC(state->initial_child);
        if (state->initial_child != 0)
            break;
        if (func_080D3B54(state->actor)) {
            request->phase = 2;
            break;
        }
        state->output_task = func_080DDF68(state->actor, &state->output,
            0x8007, 2, &state->ready, data_0839FB18, 5, 0, task);
        request->phase++;
        break;
    case 0x101:
        if (state->ready == 0)
            break;
        func_080D8CD4(state->actor);
        state->counter = 0x18;
        request->phase++;
        break;
    case 0x102:
        if (state->counter != 0) {
            state->counter--;
            if (state->counter != 0)
                break;
        }
        if (func_080D8B4C())
            break;
        if (!func_080D8858(state->actor, 0)) {
            request->phase = 2;
            break;
        }
        state->actor_object = func_080DD4A4(state->actor, 0);
        state->output = func_080DD748(state->actor_object, &state->x,
            &state->y, 0);
        func_080D49FC(0, 2, 0, state->x, state->y);
        state->sprite = func_080D4B64(0, data_088EDC04, 0x3CB, 6);
        g_control_flags_03000940.display |= func_080035A8(2);
        state->timeline = func_080D3E9C(data_0894D7E4, task);
        for (i = 0; i < 3; i++)
            state->children[i] = func_080D4704(
                data_0839FA78[state->index][i], task);
        state->record_child = func_080DFD8C(data_0839FB20, 1, 4, 0, task);
        request->phase++;
        break;
    case 0x103: {
        u8 bits[5] = {28, 29, 10, 27, 23};

        state->timeline = func_080D3F08(state->timeline);
        if (state->timeline != 0)
            break;
        if (!func_080D48DC(state->children, 3))
            break;
        state->sprite = func_080D4D2C(state->sprite, 0);
        if (state->sprite != 0)
            break;
        g_control_flags_03000940.display &= ~func_080035A8(2);
        extra = 0;
        if (func_080DD670(state->actor_object, bits[state->index])) {
            extra = 0x28;
            state->coordinate_child = func_080D6098(state->x, state->y, 0, 1,
                1, &state->unknown_18, data_0839FA50[state->index], task);
            state->record_child = func_080DFD8C(data_0839FB28, 1, 4, 0, task);
        }
        state->effect_child = func_080DCFE4(state->actor_object,
            &data_0839FAB4[state->index], 12, extra, 12, task, extra);
        request->phase++;
        break;
    }
    case 0x104:
        state->coordinate_child = func_080D6134(state->coordinate_child);
        if (state->coordinate_child != 0)
            break;
        state->effect_child = func_080DBA5C(state->effect_child);
        if (state->effect_child != 0)
            break;
        request->phase = 2;
        break;
    }
    return 0;
}
