/* Complete target [0x08114438, 0x0811490E), 1238 bytes.  The two 10-byte
 * initialisers of phase 0x104 are the ROM bytes at 0x08149F4C and 0x08149F56.
 * Target bytes:
 * f0b54f464646c0b48cb0051c8846171c098881204000814200d1b7e081420fdc
 * 012900d14fe2012902dc002919d04ae28020400081421ed0013081423ad042e2
 * 82204000814200d16ce1814200da03e10130814200d1f1e10130814200d11de2
 * 31e241464868b8608968f96000680121fcf6fcfe27e202200090381c10300190
 * 0a48029003957820602100220123c1f7e7fdb86106480095022104220023cbf7
 * 59fcf8675a203880eee10000a8383a0860393a08388801380024388000040028
 * 00d000e20120002100222b1cc6f73efbf8620020002100222b1cc6f737fb3863
 * f86a0121c5f744fb386b0121c5f740fb244a111c423108783f200870131c4333
 * 19781870111c443108781f200870093908780c70013908780c70053108780c70
 * 0139ff200870013908780c70101c3c3001780470111c413108780c7001390878
 * 0120404208701088c023db01191c084310800d48291cbff785fc3862381c7030
 * 0c2100220423ccf733f8381c643028210c220423ccf72cf84446208801302080
 * a1e1000040090003dcdb9408f86a3d1c70352a88e821891a0904091448239b1a
 * 1b041b14a0240094002601960022c6f7edfaf86a2b88191ce831090409144833
 * 1b041b140094012201920022c6f7defa386bc6f7f7fb386b3c1c64342388a021
 * 4822c6f711fb281cccf714f8201cccf711f83888013038800004000c052800d8
 * 61e10320eef6c8ff124d3f24211c8143081c2a1c423211781070291c43310878
 * 3f2008700320eef6b7ff8443281c443001780470f86ac6f7c5fb386bc6f7c2fb
 * 386abff73ffc3e62291c4a3108780020087019e1400900034a20009000200221
 * 0022aa23c0f7aef92649274a00200623c0f75cfaf8610121f7f678fb0220eef6
 * 77ff224a1188014300241180381c3430052128221423cbf79bff381c4c300a21
 * 50221423cbf794ff381c4030042128220c23cbf78dff381c5830082150220c23
 * cbf786ff124800940194012103220023c2f78afd0f48e2300f4901800f48291c
 * bff7c0fb38620c21ff22bff72ffc0c48291cbff7ebff78623c80434618880130
 * e0e00000dc158f088103000040090003cc468f0860380003ff7f00009cd69408
 * 40bf9408414904a80a222ff04bfe07aca1463f4948460a222ff044fe38880428
 * 23d8b86800680aac6d462a350bae211c2a1c331cfcf658fc3888400068441030
 * 008821884018208038884000484400882a8880182880b86800680023e15e0024
 * 2a5f0024335ffcf609f83888013038803e1c3436301ccbf73dff3c1c4c34201c
 * cbf738fff86abb8e2188009121880904c9140191a0214822fff7b4fd38880728
 * 14d93d1c4035281ccbf724ff0c34201ccbf720ff386b2b882188009121880904
 * c91401919f214722fff79cfdf86ac5f7b7f9386bc5f7b4f9b86abff79fffb862
 * 002860d1301ccbf727ff000600285ad00320eef6adfe074a1188814306480140
 * 118041460888013008804ce04c9f1408569f140840090003ff9f0000386abff7
 * 47fb386200283ed1786abff777ff041c7c62002c37d1f8690021c0f73ffafc61
 * 0220eef685fe0b4a11888143002011804a3211781070bff723f9e721c901064a
 * 8023db00ecf630f9424610880130108019e000004009000300580006b869c1f7
 * 2dfcb86100280ed1f86ac5f73ff9f862002808d1386bc5f739f93863002802d1
 * 02204346188000200cb018bc9846a146f0bc02bc0847
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
    void *unknown_10[2];
    void *position_child;
    void *sprite;
    void *script;
    void *auxiliary;
    /* Polled in phase 0x104 (0x08114830) and never assigned here.  The task
     * allocator zero-fills the payload (func_08005954), so func_080D4774
     * receives a null task. */
    void *unknown_28;
    void *top;
    void *bottom;
    struct InterpolationState top_width;
    struct InterpolationState bottom_width;
    struct InterpolationState top_height;
    struct InterpolationState bottom_height;
    struct InterpolationState open_width;
    struct InterpolationState open_offset;
    void *record_child;
};

extern const u8 data_083A38A8[];
extern const u8 data_083A3960[];
extern const u8 data_0894DBDC[];
extern const u8 data_088F15DC[];
extern const u8 data_088F46CC[];
extern const u8 data_0894D69C[];
extern const u8 data_0894BF40[];
extern u16 data_03003860[];
extern u8 data_06005800[];

extern void func_080112A4(void *, u8);
extern void *func_080D6098(s16, s16, u16, u8, u16, void **, const void *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080DAB84(u8, u8, u8, void *);
extern void func_080D9BA8(void *, u8);
extern void *func_080D3E9C(const void *, void *);
extern void func_080E0608(struct InterpolationState *, s16, s16, s16);
extern void func_080E064C(struct InterpolationState *);
extern u8 func_080E0690(struct InterpolationState *);
extern void func_080DABC4(void *, s16, s16, s16, s16, u8);
extern void func_080DADFC(void *);
extern void func_080DAC40(void *, u16, u16, u16);
extern u16 func_080035D0(u8);
extern u16 func_080035A8(u8);
extern void func_080D3EFC(void *);
extern void func_080D49FC(u8, u8, u16, s16, s16);
extern void *func_080D4B64(u8, const void *, u16, u8);
extern void func_0800BDA4(void *, u8);
extern void func_080D7220(const void *, u8, u8, s16, s16, u16);
extern void func_080D3F84(void *, u8, u8);
extern void *func_080D4704(const void *, void *);
/* Called for the two initialisers of phase 0x104 (0x08114762, 0x08114770). */
extern void *memcpy(void *, const void *, unsigned long);
extern void func_080107D4(void *, s16, s16, s16);
/* Observed signed view of the last argument: the ROM passes current >> 3
 * without a zero extension (0x081147E8, 0x08114818).  These are the only two
 * calls of func_0811435C in the ROM. */
extern void func_0811435C(void *, s16, s16, u16, u16, s16);
extern void func_080D9B98(void *);
extern void *func_080D4774(void *);
extern void *func_080D3F08(void *);
extern void func_080D4D14(void *, u8);
extern void *func_080D3AF8(void);
extern void func_08000B20(void *, u16, u32, u16);
extern void *func_080D6134(void *);
extern void *func_080D9B64(void *);

u32 func_08114438(void *task, struct Descriptor *descriptor,
                  struct Payload *payload)
{
    switch (descriptor->phase) {
    case 0:
        payload->first = descriptor->first;
        payload->second = descriptor->second;
        func_080112A4(*payload->first, 1);
        break;
    case 1:
        break;
    case 0x100:
        payload->position_child = func_080D6098(120, 96, 0, 1, 2,
            payload->unknown_10, data_083A38A8, task);
        payload->record_child = func_080DFD8C(data_083A3960, 2, 4, 0, task);
        payload->counter = 90;
        descriptor->phase++;
        break;
    case 0x101:
        if (--payload->counter)
            break;
        payload->top = func_080DAB84(1, 0, 0, task);
        payload->bottom = func_080DAB84(0, 0, 0, task);
        func_080D9BA8(payload->top, 1);
        func_080D9BA8(payload->bottom, 1);
        g_control_flags_03000940.winin_lo = 0x3f;
        g_control_flags_03000940.winin_hi = 0x3f;
        g_control_flags_03000940.winout_lo = 0x1f;
        g_control_flags_03000940.win0h_hi = 0;
        g_control_flags_03000940.win0h_lo = 0;
        g_control_flags_03000940.win0v_hi = 0;
        g_control_flags_03000940.win0v_lo = 0xff;
        g_control_flags_03000940.win1h_hi = 0;
        g_control_flags_03000940.win1h_lo = 0;
        g_control_flags_03000940.win1v_hi = 0;
        g_control_flags_03000940.win1v_lo = 0xff;
        g_control_flags_03000940.display |= 0x6000;
        payload->script = func_080D3E9C(data_0894DBDC, task);
        func_080E0608(&payload->open_offset, 12, 0, 4);
        func_080E0608(&payload->open_width, 40, 12, 4);
        descriptor->phase++;
        break;
    case 0x102:
        func_080DABC4(payload->top, 232 - payload->open_offset.current, 0,
                      72 - payload->open_offset.current, 160, 0);
        func_080DABC4(payload->top, payload->open_offset.current + 232, 0,
                      payload->open_offset.current + 72, 160, 1);
        func_080DADFC(payload->bottom);
        func_080DAC40(payload->bottom, 160, 72, payload->open_width.current);
        func_080E064C(&payload->open_offset);
        func_080E064C(&payload->open_width);
        if (++payload->counter > 5) {
            g_control_flags_03000940.winin_lo = 0x3f & ~func_080035D0(3);
            g_control_flags_03000940.winin_hi = 0x3f;
            g_control_flags_03000940.winout_lo = 0x3f & ~func_080035D0(3);
            func_080DADFC(payload->top);
            func_080DADFC(payload->bottom);
            func_080D3EFC(payload->script);
            payload->script = 0;
            g_control_flags_03000940.bldcnt_lo = 0;
            descriptor->phase++;
        }
        break;
    case 0x103:
        func_080D49FC(0, 2, 0, 170, 74);
        payload->sprite = func_080D4B64(0, data_088F15DC, 0x381, 6);
        func_0800BDA4(payload->sprite, 1);
        g_control_flags_03000940.display |= func_080035A8(2);
        func_080E0608(&payload->top_width, 5, 40, 20);
        func_080E0608(&payload->top_height, 10, 80, 20);
        func_080E0608(&payload->bottom_width, 4, 40, 12);
        func_080E0608(&payload->bottom_height, 8, 80, 12);
        func_080D7220(data_088F46CC, 1, 3, 0, 0, 0);
        data_03003860[0x71] = 0x7fff;
        payload->script = func_080D3E9C(data_0894D69C, task);
        func_080D3F84(payload->script, 12, 0xff);
        payload->auxiliary = func_080D4704(data_0894BF40, task);
        payload->counter = 0;
        descriptor->phase++;
        break;
    case 0x104: {
        u16 x_offsets[5] = {6, 3, 1, 0, 1};
        u16 y_offsets[5] = {0, 1, 0, 1, 0};

        if (payload->counter < 5) {
            u16 x, y, z;

            func_08011040(*payload->first, &x, &y, &z);
            x += x_offsets[payload->counter];
            y += y_offsets[payload->counter];
            func_080107D4(*payload->first, x, y, z);
        }
        payload->counter++;
        func_080E064C(&payload->top_width);
        func_080E064C(&payload->top_height);
        func_0811435C(payload->top, 160, 72, payload->top_width.current,
                      payload->top_height.current,
                      payload->top_height.current >> 3);
        if (payload->counter > 7) {
            func_080E064C(&payload->bottom_width);
            func_080E064C(&payload->bottom_height);
            func_0811435C(payload->bottom, 159, 71,
                          payload->bottom_width.current,
                          payload->bottom_height.current,
                          payload->bottom_height.current >> 3);
        }
        func_080D9B98(payload->top);
        func_080D9B98(payload->bottom);
        payload->unknown_28 = func_080D4774(payload->unknown_28);
        if (payload->unknown_28)
            break;
        if (func_080E0690(&payload->top_width)) {
            g_control_flags_03000940.display &= ~func_080035A8(3);
            g_control_flags_03000940.display &= 0x9fff;
            descriptor->phase++;
        }
        break;
    }
    case 0x105:
        payload->script = func_080D3F08(payload->script);
        if (payload->script)
            break;
        payload->auxiliary = func_080D4774(payload->auxiliary);
        if (payload->auxiliary)
            break;
        func_080D4D14(payload->sprite, 0);
        payload->sprite = 0;
        g_control_flags_03000940.display &= ~func_080035A8(2);
        g_control_flags_03000940.bldcnt_lo = 0;
        func_08000B20(func_080D3AF8(), 0x7380, (u32)data_06005800, 0x400);
        descriptor->phase++;
        break;
    case 0x106:
        payload->position_child = func_080D6134(payload->position_child);
        if (payload->position_child)
            break;
        payload->top = func_080D9B64(payload->top);
        if (payload->top)
            break;
        payload->bottom = func_080D9B64(payload->bottom);
        if (payload->bottom)
            break;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
