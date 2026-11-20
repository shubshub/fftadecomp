#include "ffta.h"

/* Target: 0x080E76A4..0x080E7B04, 1120 bytes, 457 reachable instructions.
 * f0b5474680b48bb0071c8846151c0b880648834200d1dbe083420edc012b3bd0012b05dc
 * 002b17d013e200000101000080204000834232d00be20648834200d1c9e1834200da8fe1
 * 0130834200d1f5e1ffe10000030100002b7140461422815e9c204000814201d101202871
 * 4646f08a687174682c6707220006002800d00022044900930197201c0123f8f763fee866
 * dfe100002c783908ecf7baf8d9e1e86ef8f74affe866002800d0d2e12c79012c0dd10d48
 * 0094062101220123ecf736ff0a480094072101220123ecf72fff6e79002e0fd001202872
 * 286f0021f1f76af8a8710348b3e10000f8a18e08f8a68e08030100007820288050206880
 * 281c0c3080231b0296210091002100221ff70cff134c0022ab5e0221685e00900196201c
 * 00210222eff7f0fd0023ea5e0226ab5f0c49e879400040180026805f0090e87940004018
 * 0021405e0190a8890290201c0221eff71bfb2879002807d1024806e0984f8f08e0783908
 * 1c9494080e48391cecf776ff6865012068721b2028720b48391cecf739fb286501201bf7
 * f7fe08480097022104220023f8f7a6fa68672879002809d1034808e088c09408dcd89408
 * 207a3908a0af94080448391cecf750ffa866424610880130108042e1bcc094082c1c5434
 * 201c0521edf72ef8697a261c06293ed8287a00283bd0013828720006002836d1481c6872
 * 1b2028720024686d2a7900280ad0311c601c0006040e042c04d8a000081800680028f5d1
 * 687a05280ad9002a04d101480fe000003098940800480ae0a4c094081006002804d10148
 * 03e000001c9494082c48391cecf708ffa200b1180860b0180068697a7031ecf761ffe879
 * 94281ed80130e871281c0c301ff7c4fe22480023ea5e0223e95e8c46204ce97949000919
 * 0023c95e0091e979490009190023c95e0191a989029102216346eff773fa286decf7dcfa
 * 041c2c65002c00d0cde0301c0521ecf7ebff782028806020688002201bf71cfe0e4a1188
 * 814311800d480026ab5f0222a95e0091019401210322eff749fc00201bf746fe28790028
 * 0ed106480de0000088c09408984f8f08e078390840090003dc538f08bc9394081148391c
 * ecf7a2fe68651048391cecf769fa28650c21ff22ecf7d8fa0023e85e0226a95f03220092
 * 2a1c40320192084a0292039700220023eef752fbe8644146088801307ae0000028c09408
 * 9cd6940880783908686decf7b1fe686500286ed1a86eecf7abfea866002868d1286decf7
 * 6ffa2865002862d1e86ceef77ffbe86400285cd103201bf7b3fd0a4a1188814300231180
 * 01202872eb71286f0021f0f7fffea8710006002806d1822040004246108044e040090003
 * 43461888013018803de02e1c3836301c0221f8f775fd287a013828720006002831d1a86b
 * 44420443e40f04a9e8798882286fe979f5f7fefc05900c48202104aa3b1c1ef75bf8a400
 * 3419206028202872e8790130e8710006000ead79a84212d146463088013030800de00000
 * b9750e08281c38300221f8f743fd0006002802d002204146088000200bb008bc9846f0bc
 * 02bc0847
 */

#include "control_flags.h"

typedef struct Descriptor {
    u16 state;
    u16 unknown_02;
    void *object;
    u32 unknown_08;
    u32 unknown_0c;
    u32 unknown_10;
    s16 index;
    u16 option;
    u32 unknown_18;
} Descriptor;

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

typedef struct State {
    s16 x;
    s16 y;
    u8 mode;
    u8 option;
    u8 count;
    u8 counter;
    u8 timer;
    u8 step;
    u8 unknown_0a[2];
    LineState rotation;
    void *children[2];
    u8 unknown_40[12];
    void *particle;
    void *animation;
    void *overlays[5];
    void *overlay_68;
    void *transition;
    void *object;
    void *controller;
} State;

extern const u8 data_0839782C[];
extern const u8 data_088EA1F8[];
extern const u8 data_088EA6F8[];
extern const u8 data_088F4F98[];
extern const s16 data_083978E0[];
extern const u8 data_0894941C[];
extern const u8 data_0894C088[];
extern const u8 data_0894D8DC[];
extern const u8 data_08397A20[];
extern const u8 data_0894AFA0[];
extern const u8 data_0894C0BC[];
extern const u8 data_08949830[];
extern const u8 data_0894C0A4[];
extern const u8 data_088F53DC[];
extern const u8 data_089493BC[];
extern const u8 data_0894C028[];
extern const u8 data_0894D69C[];
extern const u8 data_08397880[];

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

extern u32 func_080E75B8(void *task, void *descriptor, void *payload);
extern void *func_08005B6C(TaskCallback callback, u16 payload_size,
                           void *descriptor, void *parent);
extern void *func_080E03F8(void *, const void *, int, int, int, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern void func_080D45D0(const void *, u8, u8, u8, u8);
extern u8 func_080D8858(void *, int);
extern void func_080075CC(LineState *, s32, s32, s32, s32);
extern void func_080076A0(LineState *);
extern void func_080D73AC(const void *, u8, u8, s16, s16, u8);
extern void func_080D6E30(const void *, u8, s16, s16, s16, s16, u16);
extern void *func_080D4704(const void *, void *);
extern void *func_080D3E9C(const void *, void *);
extern void func_08003620(u8);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern u8 func_080D48DC(void **, u16);
extern void func_080D47C8(void *, u16);
extern void *func_080D3F08(void *);
extern void func_080D4938(void **, u16);
extern u16 func_080035A8(u8);
extern void func_080D7220(const void *, u8, u8, s16, s16, u16);
extern void func_080D3F84(void *, u8, u8);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080D4774(void *);
extern void *func_080D6134(void *);
extern u8 func_080E0570(void **, u16);
extern void *func_080DD4A4(void *, u8);

int func_080E76A4(void *context, Descriptor *desc, State *state)
{
    Descriptor child;
    int mode;
    u8 i;
    u8 slot;

    switch (desc->state) {
    case 0:
        state->mode = 0;
        if (desc->index == 0x138)
            state->mode = 1;
        state->option = desc->option;
        state->object = desc->object;
        mode = 7;
        if (state->option)
            mode = 0;
        state->transition = func_080E03F8(state->object, data_0839782C, mode, 1, 0, context);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->transition = func_080E05DC(state->transition);
        if (state->transition)
            break;
        if (state->mode == 1) {
            func_080D45D0(data_088EA1F8, 6, 1, 1, 1);
            func_080D45D0(data_088EA6F8, 7, 1, 1, 1);
        }
        if (state->option) {
            state->timer = 1;
            state->count = func_080D8858(state->object, 0);
            desc->state = 0x103;
            break;
        }
        state->x = 0x78;
        state->y = 0x50;
        func_080075CC(&state->rotation, 0, 0, 0x8000, 0x96);
        func_080D73AC(data_088F4F98, 0, 2, state->x, state->y, 0);
        func_080D6E30(data_088F4F98, 2, state->x, state->y,
                      data_083978E0[state->counter], data_083978E0[state->counter],
                      state->rotation.x);
        /* The ROM loads each resource in its own arm (0x080E7800 and
         * 0x080E7810); the arms share the call at 0x080E7812. */
        if (state->mode == 0)
            state->overlays[0] = func_080D4704(data_0894941C, context);
        else
            state->overlays[0] = func_080D4704(data_0894C088, context);
        state->step = 1;
        state->timer = 0x1B;
        state->animation = func_080D3E9C(data_0894D8DC, context);
        func_08003620(1);
        state->controller = func_080DFD8C(data_08397A20, 2, 4, 0, context);
        if (state->mode == 0)
            state->overlay_68 = func_080D4704(data_0894AFA0, context);
        else
            state->overlay_68 = func_080D4704(data_0894C0BC, context);
        desc->state++;
        break;
    case 0x101:
        func_080D48DC(state->overlays, 5);
        if (state->step <= 6 && state->timer != 0) {
            if (--state->timer == 0) {
                state->step++;
                state->timer = 0x1B;
                /* The scan has no case for five slots in use: it then ends
                 * with i == 5 (0x080E78B2-B4), and the store at
                 * 0x080E78F4-F8 has no test of its own, so it would address
                 * overlay_68. */
                for (i = 0; i < 5; i++) {
                    if (!state->overlays[i])
                        break;
                }
                /* The ROM loads the four resources in four arms (0x080E78CA,
                 * 0x080E78D4, 0x080E78E2 and 0x080E78EC) that share the call
                 * at 0x080E78EE; the handle is read back from the slot at
                 * 0x080E78FA. */
                if (state->step > 5) {
                    if (state->mode == 0)
                        state->overlays[i] = func_080D4704(data_08949830, context);
                    else
                        state->overlays[i] = func_080D4704(data_0894C0A4, context);
                } else {
                    if (state->mode == 0)
                        state->overlays[i] = func_080D4704(data_0894941C, context);
                    else
                        state->overlays[i] = func_080D4704(data_0894C088, context);
                }
                func_080D47C8(state->overlays[i], state->step + 0x70);
            }
        }
        if (state->counter <= 0x94) {
            state->counter++;
            func_080076A0(&state->rotation);
            func_080D6E30(data_088F4F98, 2, state->x, state->y,
                          data_083978E0[state->counter], data_083978E0[state->counter],
                          state->rotation.x);
        }
        state->animation = func_080D3F08(state->animation);
        if (state->animation)
            break;
        func_080D4938(state->overlays, 5);
        state->x = 0x78;
        state->y = 0x60;
        g_control_flags_03000940.display &= ~func_080035A8(2);
        func_080D7220(data_088F53DC, 1, 3, state->x, state->y, 0);
        func_08003620(0);
        if (state->mode == 0)
            state->overlays[0] = func_080D4704(data_089493BC, context);
        else
            state->overlays[0] = func_080D4704(data_0894C028, context);
        state->animation = func_080D3E9C(data_0894D69C, context);
        func_080D3F84(state->animation, 0xC, 0xFF);
        state->particle = func_080D6098(state->x, state->y, 0, 0, 3, state->unknown_40,
                                        data_08397880, context);
        desc->state++;
        break;
    case 0x102:
        state->overlays[0] = func_080D4774(state->overlays[0]);
        if (state->overlays[0])
            break;
        state->overlay_68 = func_080D4774(state->overlay_68);
        if (state->overlay_68)
            break;
        state->animation = func_080D3F08(state->animation);
        if (state->animation)
            break;
        state->particle = func_080D6134(state->particle);
        if (state->particle)
            break;
        g_control_flags_03000940.display &= ~func_080035A8(3);
        state->timer = 1;
        state->counter = 0;
        state->count = func_080D8858(state->object, 0);
        if (!state->count) {
            desc->state = 0x104;
            break;
        }
        desc->state++;
        break;
    case 0x103:
        func_080E0570(state->children, 2);
        if (--state->timer)
            break;
        slot = state->children[0] != 0;
        child.index = state->counter;
        child.object = func_080DD4A4(state->object, state->counter);
        state->children[slot] = func_08005B6C(func_080E75B8, 0x20, &child, context);
        state->timer = 0x28;
        state->counter++;
        if (state->counter == state->count)
            desc->state++;
        break;
    case 0x104:
        if (func_080E0570(state->children, 2))
            desc->state = 2;
        break;
    }
    return 0;
}
