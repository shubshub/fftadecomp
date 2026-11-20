#include "ffta.h"
#include "control_flags.h"

/* Complete target: [0x081160E4, 0x08116480), 924 bytes:
 * f0b557464e464546e0b488b0061c8946171c0988064881424ad081420fdc012900d1a3e1012905dc00291bd09ee100000101000080204000814228d096e10848814200d121e1814200daf3e00130814200d12fe10130814200d15be186e1000003010000484641680879387008880022388148887881487978708879b8700889b8804889f880c868386102706ee1bc782403f88804432404240cbdf7bbfc034a8023db00211ceaf6c9fcfbe000500006584903a806222ef02ff905aa92465649504606222ef028f9002500950020022100220023bef720fc002000210222f5f665fd00200121f5f63ffd00200021f5f6a7fd4a49ba887b780020bef7c1fc78610121f5f6f3fd0220edf6dcf9444b984619880143002419804248009501950121029103220023c1f75df83f48311cbef777faf8613d48311cbef772fa3862f8690121bef7bbfa3a48311cbdf735feb861002000210022331cc4f7a2fc7862012000210022331cc4f79bfcb86241463b3108780c70013908780c70053108780c7042463e321078a0211170013a1078147040463c3002780470424641321078147040464030027801704146423108783f253f2008700320edf699f92c1c8443201c42464332117810700220edf68ff9041c0320edf68bf90443a543404644300178057041460888c022d201111c084343461880381c2c30397849006a4652180c320024125f514400240b5f0021caf78af948e00000609f1408669f1408f0028f0840090003cc468f08a4a39408c8a394083cd994083d1c2c35281ccaf795f9786a0822b95e0a23fa5ebb8d1c0464142404240c0094c4f7a2fcb86a0824395f0a23fa5ebb8dc4f7aafa786ac3f723fcb86ac3f720fc281ccaf799f90006002875d04c4620880130208070e0b869bdf7cafdb86100286ad10648311cbdf78dfdb8610b20f88149460888013008805ee000004cd99408f8890138f8810004040c002c54d139690120087078690021bef7b0fc7c610220edf6f6f80c4c2188814321800320edf6eff8218881430948014021803878012805d1b8690121bdf70bfe3220f8814a461088013010802fe040090003ff9f0000f889002808d00138f8810004002823d1b8690021bdf7f4fd786ac3f7a7fb7862b86ac3f7a3fb011cb962786a002813d1002911d1b869bdf76bfd041cbc61002c0ad1f869bef794f9386abef791f9fc613c6202204b4618804c4621880948814207d9b8890130b881000440140221edf677f8002008b038bc9846a146aa46f0bc02bc084701010000 */

typedef struct {
    s16 current, remaining, error, step, period, distance;
} Motion;

typedef struct {
    s16 x;
    s16 y;
    u8 kind;
    u8 mode;
    u8 palette;
    u8 unknown_07;
    u16 value;
    u16 tile;
    u8 *done;
} Params;

typedef struct {
    u16 phase;
    u16 unknown_02;
    Params *params;
} Descriptor;

typedef struct {
    u8 kind;
    u8 mode;
    u8 palette;
    u8 unknown_03;
    u16 value;
    u16 tile;
    s16 x;
    s16 y;
    s16 counter;
    u16 timer;
    u8 *done;
    void *display;
    void *script;
    void *first_object;
    void *second_object;
    void *first_window;
    void *second_window;
    Motion motion;
} State;

extern const u8 data_08149F60[], data_08149F66[];
extern const u8 data_088F02F0[], data_088F46CC[];
extern const u8 data_0894A3A4[], data_0894A3C8[];
extern const u8 data_0894D93C[], data_0894D94C[];
extern u8 data_06005000[];

extern void *func_081443FC(void *destination, const void *source, u32 bytes);
extern void *func_080D3AF8(void);
extern void func_08000B20(void *, u16, u32, u16);
extern void func_080D49FC(u8, u8, u16, s16, s16);
extern void func_0800BC90(u32, u32, u32);
extern void func_0800BC4C(u32, u32);
extern void func_0800BD24(u32, u32);
extern void *func_080D4B64(u8, const void *, u16, u8);
extern void func_0800BDD0(void *, u8);
extern u32 func_080035A8(u8);
extern u32 func_080035D0(u8);
extern void func_080D72C8(const void *, u8, u8, s16, s16, u16, u8);
extern void *func_080D4704(const void *, void *);
extern void func_080D47A0(void *, u8);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080DAB84(int, int, int, void *);
extern void func_080E0608(Motion *, s16, s16, s16);
extern void func_080E064C(Motion *);
extern u8 func_080E0690(Motion *);
extern void func_080DAC80(void *, s16, s16, u16, u16);
/* This caller passes x and y as s16: they are loaded with ldrsh at
 * 0x08116340 and 0x08116344 and not narrowed before the call. The callee
 * narrows them as u16 itself (src/080DA8A0.c, lsls/lsrs at
 * 0x080DA8B2..0x080DA8B8). */
extern void func_080DA8A0(void *, s16, s16, u16);
extern void func_080D9B98(void *);
extern void *func_080D3F08(void *);
extern void func_080D4D14(void *, u8);
extern void func_080D3FF8(void *, u8);
extern void *func_080D9B64(void *);
extern void func_080D4768(void *);
extern void func_08003558(s16, u8);

u32 func_081160E4(void *task, Descriptor *descriptor, State *s)
{
    s16 first[3];
    s16 second[3];

    switch (descriptor->phase) {
    case 0: {
        Params *params = descriptor->params;

        s->kind = params->kind;
        s->x = params->x;
        s->y = params->y;
        s->mode = params->mode;
        s->palette = params->palette;
        s->value = params->value;
        s->tile = params->tile;
        s->done = params->done;
        *s->done = 0;
        break;
    }
    case 1:
        break;
    case 0x100: {
        u16 entry;

        /* The map entry (palette and tile) is built in r4 at
         * 0x08116172..0x0811617C, before the func_080D3AF8 call at
         * 0x0811617E, and copied to r1 at 0x08116188 (as in 080E0A8C). */
        entry = (s->palette << 12) | s->tile;
        func_08000B20(func_080D3AF8(), entry, (u32)data_06005000, 0x400);
        descriptor->phase++;
        break;
    }
    case 0x101:
        func_081443FC(first, data_08149F60, sizeof(first));
        func_081443FC(second, data_08149F66, sizeof(second));
        func_080D49FC(0, 2, 0, 0, 0);
        func_0800BC90(0, 0, 2);
        func_0800BC4C(0, 1);
        func_0800BD24(0, 0);
        s->display = func_080D4B64(0, data_088F02F0, s->value, s->mode);
        func_0800BDD0(s->display, 1);
        /* The copy of DISPCNT is loaded into r1 (0x081161F4) and the
         * layer mask ORed into it (0x081161F6), as in 080E317C. */
        {
            u32 mask = func_080035A8(2);
            u16 flags = g_control_flags_03000940.display;

            flags |= mask;
            g_control_flags_03000940.display = flags;
        }
        func_080D72C8(data_088F46CC, 1, 3, 0, 0, 0, 1);
        s->first_object = func_080D4704(data_0894A3A4, task);
        s->second_object = func_080D4704(data_0894A3C8, task);
        func_080D47A0(s->first_object, 1);
        s->script = func_080D3E9C(data_0894D93C, task);
        s->first_window = func_080DAB84(0, 0, 0, task);
        s->second_window = func_080DAB84(1, 0, 0, task);
        g_control_flags_03000940.win0h_hi = 0;
        g_control_flags_03000940.win0h_lo = 0;
        g_control_flags_03000940.win0v_hi = 0;
        g_control_flags_03000940.win0v_lo = 160;
        g_control_flags_03000940.win1h_hi = 0;
        g_control_flags_03000940.win1h_lo = 0;
        g_control_flags_03000940.win1v_hi = 0;
        g_control_flags_03000940.win1v_lo = 160;
        g_control_flags_03000940.winin_lo = 0x3f;
        g_control_flags_03000940.winin_hi = 0x3f & ~func_080035D0(3);
        g_control_flags_03000940.winout_lo =
            0x3f & ~(func_080035D0(2) | func_080035D0(3));
        g_control_flags_03000940.display |= 0x6000;
        func_080E0608(&s->motion, 0, first[s->kind], second[s->kind]);
        descriptor->phase++;
        break;
    case 0x102:
        func_080E064C(&s->motion);
        func_080DAC80(s->first_window, s->x, s->y, s->motion.current,
                      s->motion.current >> 1);
        func_080DA8A0(s->second_window, s->x, s->y, s->motion.current);
        func_080D9B98(s->first_window);
        func_080D9B98(s->second_window);
        if (func_080E0690(&s->motion))
            descriptor->phase++;
        break;
    case 0x103:
        s->script = func_080D3F08(s->script);
        if (s->script == 0) {
            s->script = func_080D3E9C(data_0894D94C, task);
            s->timer = 11;
            descriptor->phase++;
        }
        break;
    case 0x104:
        if (--s->timer == 0) {
            *s->done = 1;
            func_080D4D14(s->display, 0);
            s->display = 0;
            g_control_flags_03000940.display &= ~func_080035A8(2);
            g_control_flags_03000940.display &= ~func_080035A8(3);
            g_control_flags_03000940.display &= 0x9fff;
            if (s->kind == 1) {
                func_080D3FF8(s->script, 1);
                s->timer = 50;
            }
            descriptor->phase++;
        }
        break;
    case 0x105:
        if (s->timer != 0) {
            if (--s->timer != 0)
                break;
            func_080D3FF8(s->script, 0);
        }
        s->first_window = func_080D9B64(s->first_window);
        s->second_window = func_080D9B64(s->second_window);
        if (s->first_window == 0 && s->second_window == 0) {
            s->script = func_080D3F08(s->script);
            if (s->script == 0) {
                func_080D4768(s->first_object);
                func_080D4768(s->second_object);
                s->first_object = 0;
                s->second_object = 0;
                descriptor->phase = 2;
            }
        }
        break;
    }
    if (descriptor->phase > 0x101) {
        s->counter++;
        func_08003558(s->counter >> 1, 2);
    }
    return 0;
}
