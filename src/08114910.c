/* Complete target [0x08114910, 0x08114DBC), 1196 bytes.
 * Registered by func_08115560 with a 0x1A0-byte payload.
 * Target bytes:
 * f0b557464e464546e0b499b018900f1c161c39880648814200d183e1814215dc
 * 0338814263d0814204dc00292ad034e2030100000448814200d1ade001308142
 * 00d151e129e200000101000083204000814200d1e6e1814208dc0238814200d1
 * 86e10130814200d1b2e116e20448814200d1f1e10130814200d103e20de20000
 * 070100007868b060b868f06004a800210922a023cbf730fe07ad281c00210e22
 * a023cbf729fe0aac201c00211922a023cbf722fe00274836b04604ae04a8cbf7
 * 3dfe281ccbf73afe201ccbf737fe7a0042442988490130880143208880020143
 * 1180781c0004070c9f2fe7d9d5e1b06800680dac6d4636350eab211c2a1cfcf6
 * 17fb301c18300022a15e22887032120412141423cbf7f0fd301c30300023e95e
 * 2a883832120412141423cbf7e5fd301c2430b0225200f0211423cbf7ddfd301c
 * 3c30a021d8221423cbf7d6fd114a131c3b33187800211970013b187878201870
 * 053318781970111c3e310878a0200870043108782f200870023108783f200870
 * 118880239b01181c084310803888013082e1000040090003341c1834201ccbf7
 * cdfd301c2430cbf7c9fd301c3030cbf7c5fd301c3c30cbf7c1fdb06800681822
 * b15e3023f25e0023fbf67cfef06800682422b15e3c23f25e0023fbf673fe201c
 * cbf7cefd0006002800d156e1384a11883848084000241080b0680068fcf68cfc
 * b0680460f0680068fcf686fcf0680460314800940194012103220023c2f778fb
 * 2e48e2302e490180351c48350fa800210922a023cbf760fd12a800210e22a023
 * cbf75afd15a800211922a023cbf754fd0fa8824612a9894615aa90460fa8cbf7
 * 6dfd12a8cbf76afd15a8cbf767fd620052194b46198849015346188801434346
 * 1888800201431180601c0004040c9f2ce4d91248e230002101807120291c189a
 * c4f7b2ff041c0121c4f7f6ffc4214900701804600b481899bff768f9cc225200
 * b11808603220308038880130e4e0000040090003ffdf0000cc468f0860380003
 * c965000092393a083088002805d0013830800004002800d0cfe0cc235b00f418
 * 2068bff779f9021c2260002a00d0c4e003484a300178027038880130bce00000
 * 400900031048e2218900009109210191002102910391022178225023c1f738f8
 * 3061fcf6a1fa094818990091012104220023cbf793f8ce225200b11808603220
 * 30803888013097e0a45f500870393a083088013830800004020c002a00d08ce0
 * 1248e221890000910921019102920392032178225023c1f70bf8706101214942
 * fcf6d2f970690121fcf61efa70690121fcf612fbc6235b00f018002180221423
 * cbf79afc3888013066e00000a45f5008c62040003418201ccbf7b0fc30880130
 * 0025308070690e4a3188490089180023ca5e23881b061b0c111cfcf6dffa3088
 * 13284ad93069fcf687fb35617069fcf683fb75610a203080388801303ce00000
 * a6393a083088002804d0013830800004002832d1bef7defdc03008f7b5ff0548
 * 1899bff7a3f8cc225200b11808603888013021e09c393a08cc235b00f4182068
 * bff7caf82060002817d10320eef614fc034a118881431180388801300ce00000
 * 40090003c420400034182068c4f7e2fe2060002801d102203880002019b038bc
 * 9846a146aa46f0bc02bc0847
 */
#include "control_flags.h"

struct Descriptor {
    u16 phase;
    u8 unknown_02[2];
    void **first;
    void **second;
};

struct InterpolationState {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
};

struct Payload {
    u16 counter;
    u8 unknown_02[6];
    void **first;
    void **second;
    void *object;
    void *scaled_object;
    struct InterpolationState first_x;
    struct InterpolationState second_x;
    struct InterpolationState first_y;
    struct InterpolationState second_y;
    u16 gradient[160];
    void *gradient_task;
    struct InterpolationState spin;
    void *script;
    void *record_child;
};

extern const u8 data_088F46CC[];
extern const u8 data_083A3970[];
extern const u8 data_083A3992[];
extern const u8 data_083A399C[];
/* Twenty halfwords rising from 0x100 to 0x2000, 0x083A39A6-0x083A39CD; the
 * script data_083A39CE (src/081151A0.c) follows it. */
extern const s16 data_083A39A6[];
extern const u8 data_08505FA4[];
extern u16 data_03003860[];

extern void func_080E0608(struct InterpolationState *, s16, s16, s16);
extern void func_080E064C(struct InterpolationState *);
extern u8 func_080E0690(struct InterpolationState *);
extern void func_080107D4(void *, s16, s16, s16);
extern void func_08011428(void *);
extern void func_080D7220(const void *, u8, u8, s16, s16, u16);
extern void *func_080D9B18(u32, void *, void *);
extern void func_080D9BA8(void *, u8);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D3F08(void *);
extern void *func_080D5CC0(const void *, u16, s16, s16, s16, u8, u8, u8);
extern void func_08011198(void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void func_08011058(void *, s16);
extern void func_080110F8(void *, u8);
extern void func_080112E8(void *, u8);
extern void func_080112CC(void *, s16, s16, u16);
extern void *func_080D3904(void);
extern void func_0801DCB8(const u16 *);
extern u16 func_080035A8(u8);
extern void *func_080D9B64(void *);

/* Builds the colour table of phase 0 again and starts the task that shows
 * it.  In this second build all six calls take a state's address straight
 * from sp (0x08114B3C-0x08114B54, 0x08114B6C-0x08114B78) and the loads go
 * through three further copies (0x08114B60-0x08114B6A); phase 0, the same
 * statements in the body, keeps one register for the calls and the loads of
 * a state (r5, r4: 0x081149A8-0x081149EA). */
static inline void *start_gradient(u16 *gradient, void *parent)
{
    struct InterpolationState red, green, blue;
    u16 i;

    func_080E0608(&red, 0, 9, 160);
    func_080E0608(&green, 0, 14, 160);
    func_080E0608(&blue, 0, 25, 160);
    for (i = 0; i < 160; i++) {
        func_080E064C(&red);
        func_080E064C(&green);
        func_080E064C(&blue);
        gradient[i] = red.current | (green.current << 5)
            | (blue.current << 10);
    }
    data_03003860[0x71] = 0;
    return func_080D9B18(0x71, gradient, parent);
}

u32 func_08114910(void *task, struct Descriptor *descriptor,
                  struct Payload *payload)
{
    switch (descriptor->phase) {
    case 0: {
        struct InterpolationState red, green, blue;
        u16 i;

        payload->first = descriptor->first;
        payload->second = descriptor->second;
        func_080E0608(&red, 0, 9, 160);
        func_080E0608(&green, 0, 14, 160);
        func_080E0608(&blue, 0, 25, 160);
        for (i = 0; i < 160; i++) {
            func_080E064C(&red);
            func_080E064C(&green);
            func_080E064C(&blue);
            payload->gradient[i] = red.current | (green.current << 5)
                | (blue.current << 10);
        }
        break;
    }
    case 0x100: {
        u16 x, y, z;

        func_08011040(*payload->first, &x, &y, &z);
        func_080E0608(&payload->first_x, x, x + 112, 20);
        func_080E0608(&payload->first_y, y, y + 56, 20);
        func_080E0608(&payload->second_x, 240, 352, 20);
        func_080E0608(&payload->second_y, 160, 216, 20);
        g_control_flags_03000940.win0h_hi = 0;
        g_control_flags_03000940.win0h_lo = 120;
        g_control_flags_03000940.win0v_hi = 0;
        g_control_flags_03000940.win0v_lo = 160;
        g_control_flags_03000940.winin_lo = 0x2f;
        g_control_flags_03000940.winout_lo = 0x3f;
        g_control_flags_03000940.display |= 0x2000;
        descriptor->phase++;
        break;
    }
    case 0x101:
        func_080E064C(&payload->first_x);
        func_080E064C(&payload->second_x);
        func_080E064C(&payload->first_y);
        func_080E064C(&payload->second_y);
        func_080107D4(*payload->first, payload->first_x.current,
                      payload->first_y.current, 0);
        func_080107D4(*payload->second, payload->second_x.current,
                      payload->second_y.current, 0);
        if (func_080E0690(&payload->first_x)) {
            void *gradient_task;

            g_control_flags_03000940.display &= 0xdfff;
            func_08011428(*payload->first);
            *payload->first = 0;
            func_08011428(*payload->second);
            *payload->second = 0;
            func_080D7220(data_088F46CC, 1, 3, 0, 0, 0);
            data_03003860[0x71] = 0x65c9;
            gradient_task = start_gradient(payload->gradient, task);
            /* The task is stored after this call (0x08114BB4-0x08114BC2). */
            func_080D9BA8(gradient_task, 1);
            payload->gradient_task = gradient_task;
            payload->script = func_080D3E9C(data_083A3992, task);
            payload->counter = 50;
            descriptor->phase++;
        }
        break;
    case 0x102:
        if (payload->counter && --payload->counter)
            break;
        payload->script = func_080D3F08(payload->script);
        if (payload->script)
            break;
        g_control_flags_03000940.bldcnt_lo = 0;
        descriptor->phase++;
        break;
    case 0x103:
        payload->object = func_080D5CC0(data_08505FA4, 2, 120, 80, 0x388, 9,
                                        0, 0);
        func_08011198(payload->object);
        payload->record_child = func_080DFD8C(data_083A3970, 1, 4, 0, task);
        payload->counter = 50;
        descriptor->phase++;
        break;
    case 0x104:
        if (--payload->counter)
            break;
        payload->scaled_object = func_080D5CC0(data_08505FA4, 3, 120, 80,
                                               0x388, 9, 0, 0);
        func_08011058(payload->scaled_object, -1);
        func_080110F8(payload->scaled_object, 1);
        func_080112E8(payload->scaled_object, 1);
        func_080E0608(&payload->spin, 0, 128, 20);
        descriptor->phase++;
        break;
    case 0x105:
        func_080E064C(&payload->spin);
        payload->counter++;
        /* BUG: the counter is stepped (0x08114CEC-0x08114CF2) before it
         * indexes the 20-entry table (0x08114CF8-0x08114D00), so the 20th
         * and last call reads index 20: 0x00BF at 0x083A39CE, the first
         * halfword of the script data_083A39CE.  func_080112CC only stores
         * it, and the object is unlinked later in the same call
         * (0x08114D1E), so nothing is drawn from it.  Entry 0 (0x0100) is
         * the scale the object already has from the creation template
         * data_08149828, so the table is otherwise used in full.
         * docs/bugs/08114910/ has the case. */
#ifdef BUGFIX
        if (payload->counter < 20)
#endif
        func_080112CC(payload->scaled_object, data_083A39A6[payload->counter],
                      data_083A39A6[payload->counter],
                      payload->spin.current << 8);
        if (payload->counter > 19) {
            func_08011428(payload->object);
            payload->object = 0;
            func_08011428(payload->scaled_object);
            payload->scaled_object = 0;
            payload->counter = 10;
            descriptor->phase++;
        }
        break;
    case 0x106:
        if (payload->counter && --payload->counter)
            break;
        func_0801DCB8((const u16 *)func_080D3904() + 96);
        payload->script = func_080D3E9C(data_083A399C, task);
        descriptor->phase++;
        break;
    case 0x107:
        payload->script = func_080D3F08(payload->script);
        if (payload->script)
            break;
        g_control_flags_03000940.display &= ~func_080035A8(3);
        descriptor->phase++;
        break;
    case 0x108:
        payload->gradient_task = func_080D9B64(payload->gradient_task);
        if (payload->gradient_task)
            break;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
