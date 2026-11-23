#include "ffta.h"
#include "control_flags.h"
#include "effect_task.h"

// Complete [0x080E5978, 0x080E5F50), 1496 bytes.
// Target bytes:
// f0b557464e464546e0b48ab009908a46161c0b8881204000834200d1f2e083420fdc012b46d0012b
// 02dc002b24d0c7e280204000834240d00130834200d1a7e0bee20748834200d1dae183420adc0238
// 834200d122e10130834200d156e1afe20501000083204000834200d140e20130834200d176e2a3e2
// 737151461422885e0e2801d0012070715446e08ab0716468346708220006002800d0002204490093
// 099d0195201c0123faf7eafcf06687e2f0703908edf742ff82e2f06efaf7d2fdf066002800d07be2
// 306f0021f2f708ff0006002803d102205746388070e2306f0021f7f723fd041cb21c311c0023f7f7
// 6ffeb06304a91f4a101c08801e491f4a04a85bf0f7fe0023f05e0225715f03220092321c3c320192
// 194a0292099f039700220023f0f7fcfab06416480999eef7f9f9f0650820307101201df7b5fd0325
// 201cf7f761fd0006002800d1022570790d49002800d10d4909980090081c291c04220023faf756f9
// 706751460888013025e20000ff7f0000203900031000000150713908a8d894083072390818723908
// 3079013830710006050e002d00d00fe2154c0022b35e0227f05f00900195201c00210222f1f73efc
// 0020325e0221735e0e493079400040180027c05f00903079400040180021405e01900295201c0221
// f1f76af906480999eef7d0fd30665246108801301080e3e114558f08c87139082098940830790130
// 30710006000e132816d81d480023f25e0224335f1b4c3179490009190025495f0091317949000919
// 0027c95f0191002102910221f1f73cf9306eeef7dbfd041c3466002c00d0b7e102201df7edfc0e4a
// 1188814311800d480021735e0222b15e0091019401210322f1f71afb00201df717fd07480999eef7
// 85fd3066b5e0000014558f08c871390840090003e0548f0808989408306eeef7adfd3066002800d0
// 8ae100243c25ad19a94605ada00048440068002814d0694612312a1c6b4616332bf7fef960000019
// 8000083030180027e95f2a88083a120412140423faf7d4fc601c0006040e022ce0d9600000198000
// 083030180222b15e7288083a12041214042370e000273c24a419a14606ada846b80049460d182868
// 002818d07c00e419a400201c08303018faf7d0fc286841466a461a3207ab2bf7c3f9286842460023
// d15e34190825625f00232af783fd781c0006070e022fdbd97c00e419a400251c08357519281cfaf7
// b1fc22480027f25f34190821635e0321f1f7b6fb281cfaf7c7fc0006002800d116e100276c461a34
// b80048440068002812d006a9221c07ab2bf78ef97800c0198000083030180022a15e228828321204
// 12141423faf764fc781c0006070e022fe2d97800c0198000083030187288111c0839090409142032
// 120412141423faf74ffc5346188801301880e1e0e0548f0800273c24a419a1461e256d44a846b800
// 49460d182868002818d07c00e419a400201c08303018faf755fc2868414608aa6b4622332bf748f9
// 286842460023d15e34190825625f00232af708fd781c0006070e022fdbd97c00e419a400251c0835
// 7519281cfaf736fc18480027f25f34190821635e0321f1f73bfb281cfaf74cfc0006002800d19be0
// 306f0021f7f74efb041c70798100091889000d48091802200090099a019208200290201c0c220823
// f7f7dcf8b066201cf7f7a6fb000600280ad10448534618807ae00000e0548f08f071390807010000
// 04480999eef756fc7066544620880130208069e0189f94083079013830710006002861d10025705f
// 0227f15f01220092321c4c320192134a0292099a039200220023f0f701f930657279012a14d10023
// f05e0224315f0092321c543201920a4a0292099d039500220023f0f7edf8b06501214942f0f7a2f9
// 574638880130388032e0000098713908b0713908b06cf0f729f9b064002827d1306df0f723f93065
// 002821d1b06df0f71df9b06500281bd1f06deef701f8f065002815d103201df74bfb0e4a11888143
// 1180706eeef72afc7066002808d1b06ef5f798fdb066002802d102205146088000200ab038bc9846
// a146aa46f0bc02bc0847000040090003

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    u8 unknown_08[12];
    s16 unknown_14;
    u16 mode;
} Descriptor080E5978;

typedef struct {
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
    u8 countdown;
    u8 variant;
    u8 mode;
    u8 unknown_07;
    InterpolationState motion[4];
    void *coordinate_result;
    void *children[3];
    void *children_task;
    void *second_children[1];
    void *second_task;
    void *third_children[1];
    void *third_task;
    void *resource_task;
    void *first_task;
    void *second_resource_task;
    void *effect_task;
    void *initial_task;
    void *actor;
    void *record_task;
} Payload080E5978;

typedef struct {
    u8 unknown_00[20];
} EffectRecord080E5978;

extern const u8 data_083970F0[];
extern const u8 data_08397150[];
extern const u8 data_08397198[];
extern const u8 data_083971B0[];
extern const s16 data_083971C8[];
extern const EffectRecord080E5978 data_083971F0[];
extern const u8 data_08397218[];
extern const u8 data_08397230[];
extern const u8 data_088F54E0[];
extern const u8 data_088F5514[];
extern const u8 data_0894D8A8[];
extern const u8 data_08949808[];
extern const u8 data_08949820[];
extern const u8 data_08949F18[];
extern u16 data_03003920[];

extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, s16 *);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080D3E9C(const void *, void *);
extern void func_08003620(u8);
extern u8 func_080DD580(void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void func_080D73AC(const void *, u8, u8, s16, s16, u8);
extern void func_080D6E30(const void *, u8, s16, s16, s16, s16, u16);
extern void *func_080D4704(const void *, void *);
extern void *func_080D4774(void *);
extern u32 func_080035A8(u8);
extern void func_080D7220(const void *, u8, u8, s16, s16, u16);
extern void func_080E0608(InterpolationState *, s16, s16, s16);
extern void func_080E064C(InterpolationState *);
extern u8 func_080E0690(InterpolationState *);
extern void func_080107D4(void *, s16, s16, s16);
extern void func_080D7468(const void *, u8, s16, s16);
extern void func_080D620C(void *, s16);
extern void *func_080D6134(void *);
extern void *func_080D3F08(void *);
extern void *func_080DBA5C(void *);

u32 func_080E5978(void *task, Descriptor080E5978 *descriptor,
                  Payload080E5978 *payload)
{
    switch (descriptor->phase) {
    case 0: {
        u8 animation;

        payload->variant = 0;
        if (descriptor->unknown_14 != 14)
            payload->variant = 1;
        payload->mode = descriptor->mode;
        payload->actor = descriptor->object;
        animation = 8;
        if (payload->mode != 0)
            animation = 0;
        payload->initial_task = func_080E03F8(payload->actor, data_083970F0,
                                              animation, 1, 0, task);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100: {
        void *object;
        u8 count;

        payload->initial_task = func_080E05DC(payload->initial_task);
        if (payload->initial_task != 0)
            break;
        if (func_080D8858(payload->actor, 0) == 0) {
            descriptor->phase = 2;
            break;
        }
        object = func_080DD4A4(payload->actor, 0);
        payload->coordinate_result = func_080DD748(object, &payload->x,
                                                   &payload->y, 0);
        {
            u16 fill;
            u16 *fill_source;

            /* CpuFill16(0x7FFF, data_03003920, 0x20): the SDK's vu16
             * temporary, spelled through a pointer as src/0811F95C.c does
             * until fftadecomp-kit#164.  The ROM loads 0x7FFF into r2 and
             * copies it to r0 before the store (0x080E5A6E-0x080E5A72),
             * then forms the source address again for the call
             * (0x080E5A78). */
            fill_source = &fill;
            *fill_source = 0x7FFF;
            func_0814186C(fill_source, data_03003920, 0x01000010);
        }
        payload->children_task = func_080D6098(payload->x, payload->y, 0, 0,
                                               3, payload->children,
                                               data_08397150, task);
        payload->resource_task = func_080D3E9C(data_0894D8A8, task);
        payload->countdown = 8;
        func_08003620(1);
        count = 3;
        if (!func_080DD580(object))
            count = 2;
        payload->record_task = func_080DFD8C(
            payload->variant == 0 ? data_08397218 : data_08397230, count, 4, 0,
            task);
        descriptor->phase++;
        break;
    }
    case 0x101:
        payload->countdown--;
        if (payload->countdown != 0)
            break;
        func_080D73AC(data_088F5514, 0, 2, payload->x, payload->y, 0);
        func_080D6E30(data_088F5514, 2, payload->x, payload->y,
                      data_083971C8[payload->countdown],
                      data_083971C8[payload->countdown], 0);
        payload->first_task = func_080D4704(data_08949820, task);
        descriptor->phase++;
        break;
    case 0x102:
        payload->countdown++;
        if (payload->countdown < 20)
            func_080D6E30(data_088F5514, 2, payload->x, payload->y,
                          data_083971C8[payload->countdown],
                          data_083971C8[payload->countdown], 0);
        payload->first_task = func_080D4774(payload->first_task);
        if (payload->first_task != 0)
            break;
        g_control_flags_03000940.display &= ~func_080035A8(2);
        func_080D7220(data_088F54E0, 1, 3, payload->x, payload->y, 0);
        func_08003620(0);
        payload->first_task = func_080D4704(data_08949808, task);
        descriptor->phase++;
        break;
    case 0x103: {
        u16 x, y, z;
        u8 i;

        payload->first_task = func_080D4774(payload->first_task);
        if (payload->first_task != 0)
            break;
        for (i = 0; i < 3; i++) {
            if (payload->children[i] != 0) {
                func_08011040(payload->children[i], &x, &y, &z);
                func_080E0608(&payload->motion[i], y, y - 8, 4);
            }
        }
        /* i is 3 here: the ROM indexes motion[] with the loop counter
         * once the loop is done (0x080E5C6A), so the fourth state, the
         * one for payload itself, is reached through i. */
        func_080E0608(&payload->motion[i], payload->y, payload->y - 8, 4);
        descriptor->phase++;
        break;
    }
    case 0x104: {
        u16 x, y, z;
        u8 i;

        for (i = 0; i < 3; i++) {
            if (payload->children[i] != 0) {
                func_080E064C(&payload->motion[i]);
                func_08011040(payload->children[i], &x, &y, &z);
                func_080107D4(payload->children[i], x,
                              payload->motion[i].current, 0);
            }
        }
        func_080E064C(&payload->motion[i]);
        func_080D7468(data_088F54E0, 3, payload->x, payload->motion[i].current);
        if (!func_080E0690(&payload->motion[i]))
            break;
        for (i = 0; i < 3; i++) {
            if (payload->children[i] != 0) {
                func_08011040(payload->children[i], &x, &y, &z);
                func_080E0608(&payload->motion[i], y, y + 40, 20);
            }
        }
        func_080E0608(&payload->motion[i], payload->y - 8, payload->y + 32,
                      20);
        descriptor->phase++;
        break;
    }
    case 0x105: {
        u16 x, y, z;
        u8 i;
        void *object;

        for (i = 0; i < 3; i++) {
            if (payload->children[i] != 0) {
                func_080E064C(&payload->motion[i]);
                func_08011040(payload->children[i], &x, &y, &z);
                func_080107D4(payload->children[i], x,
                              payload->motion[i].current, 0);
            }
        }
        func_080E064C(&payload->motion[i]);
        func_080D7468(data_088F54E0, 3, payload->x, payload->motion[i].current);
        if (!func_080E0690(&payload->motion[i]))
            break;
        object = func_080DD4A4(payload->actor, 0);
        payload->effect_task = func_080DCFE4(object,
                                             &data_083971F0[payload->variant],
                                             12, 8, 2, task, 8);
        if (!func_080DD580(object)) {
            descriptor->phase = 0x107;
            break;
        }
        payload->second_resource_task = func_080D4704(data_08949F18, task);
        descriptor->phase++;
        break;
    }
    case 0x106:
        payload->countdown--;
        if (payload->countdown != 0)
            break;
        payload->second_task = func_080D6098(payload->x, payload->y, 0, 0, 1,
                                             payload->second_children,
                                             data_08397198, task);
        if (payload->variant == 1) {
            payload->third_task = func_080D6098(payload->x, payload->y, 0, 0,
                                                1, payload->third_children,
                                                data_083971B0, task);
            func_080D620C(payload->third_task, -1);
        }
        descriptor->phase++;
        break;
    case 0x107:
        payload->children_task = func_080D6134(payload->children_task);
        if (payload->children_task != 0)
            break;
        payload->second_task = func_080D6134(payload->second_task);
        if (payload->second_task != 0)
            break;
        payload->third_task = func_080D6134(payload->third_task);
        if (payload->third_task != 0)
            break;
        payload->resource_task = func_080D3F08(payload->resource_task);
        if (payload->resource_task != 0)
            break;
        g_control_flags_03000940.display &= ~func_080035A8(3);
        payload->second_resource_task = func_080D4774(
            payload->second_resource_task);
        if (payload->second_resource_task != 0)
            break;
        payload->effect_task = func_080DBA5C(payload->effect_task);
        if (payload->effect_task != 0)
            break;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
