/* 0x080E0A8C..0x080E0C88, 508 target bytes.
 * Target: f0b581b00f1c151c398880204000814226d0814202dc00290ad0e8e00348814238d00130814200d1a4e0e0e001010000f2f798ff0006002804d0f2f71dff291ccc3109e001204042291c0a3139f7a8fc291ccc31281c0c300860b8682871c6e0f3f704f801214942074a082320f736f8064cf2f7fbff064a8023db00211c20f709f838880130b1e0a0ff0006fd630000005800060020e880082028726872281ccc30036801205f21142267f0f9f828602879012852d12b48e988de300180002022f768fd284822f78fff041c274822f791ff0443032004432404240c201c022122f7a4fc0020022122f7c8fc0020022122f7ecfc022022f739fd1d4c40210143221c4a321078002001431170211c4b31087820200870297a201c4c3002780170687a221c4d3211781070022022f7f6fc218801432180281cd030297a142400940022002326f7fcfc281cfc30697a00940022102326f7f4fc3df70ef83888013044e0000060380003005800060080000640090003287901281dd12c1cd034201c26f748fd2e1cfc36301c26f743fd1a482268011c4c310b780a7031684d3002780170201c26f726fe002820d0301c26f721fe00281bd0286867f0c6fc002816d0286867f023fc00222a60287901280ad1094c211c4a3108780a70022022f79efc218881432180f2f7ddfe02203880002001b0f0bc02bc084740090003
 */
#include "ffta.h"

typedef struct RequestNode {
    u8 status;
    u8 kind;
    u8 unknown_02[2];
    u32 first;
    u32 second;
    u32 control;
    u8 unknown_10[8];
    struct RequestNode *next;
} RequestNode;

typedef struct WordInterpolation {
    s32 current;
    s32 position;
    s32 target;
    s32 duration;
    s32 step;
    s32 position_step;
    s32 distance;
    s32 span;
    s32 error;
    s32 half_span;
    s32 remaining;
} WordInterpolation;

typedef struct EffectDescriptor {
    u16 phase;
    u8 unknown_02[6];
    u32 mode;
} EffectDescriptor;

typedef struct EffectWork {
    void *handle;
    u8 mode;
    u8 unknown_05;
    u16 offset;
    u8 first_value;
    u8 second_value;
    u8 unknown_0A[0xC2];
    const u16 *selected;
    WordInterpolation first;
    WordInterpolation second;
} EffectWork;

typedef struct DisplayShadow {
    u16 flags;
    u8 unknown_02[0x48];
    u8 control;
    u8 configuration;
    u8 first_value;
    u8 second_value;
} DisplayShadow;

typedef struct BackgroundState {
    u8 unknown_00[0xDE];
    u16 offset;
} BackgroundState;

extern void func_08000B20(RequestNode *entry, u16 first, u32 second, u16 count);
extern void func_08000B68(RequestNode *entry, u32 first, u32 second, u16 count);
extern void func_080034B8(u16 value, u8 selector);
extern void func_08003508(u16 value, u8 selector);
extern void func_08003558(u16 value, u8 selector);
extern u16 func_080035A8(u8 selector);
extern u16 func_080035F8(u8 selector);
extern void func_08003620(u8 value);
extern u16 func_08003A74(u32 packed);
extern u32 func_08003A80(u32 packed);
extern void func_080075CC(void *state, s32 current, s32 position, s32 target, s32 duration);
extern void func_080076A0(void *state);
extern u32 func_08007880(const void *state);
extern void func_0801A42C(s16 selector, void *destination);
extern void func_0801DC04(void);
extern const u16 *func_080D3904(void);
extern u8 func_080D39F0(void);
extern void func_080D3A30(void);
extern RequestNode *func_080D3AF8(void);
extern void *func_08147D2C(u16 first, u16 count, u16 duration, const u16 *source);
extern void func_08148498(void *handle);
extern u32 func_081485D4(const void *handle);

u32 func_080E0A8C(void *unused, void *state, void *payload)
{
    EffectDescriptor *descriptor = state;
    EffectWork *work = payload;
    DisplayShadow *shadow = (DisplayShadow *)0x03000940;
    BackgroundState *background = (BackgroundState *)0x03003860;
    u16 settings;
    u16 mask;

    switch (descriptor->phase) {
    case 0:
        if (func_080D39F0()) {
            work->selected = func_080D3904();
        } else {
            func_0801A42C(-1, work->unknown_0A);
            work->selected = (const u16 *)(work->unknown_0A + 2);
        }
        work->mode = descriptor->mode;
        break;
    case 0x100:
        func_08000B68(func_080D3AF8(), 0xFFFFFFFF, 0x0600FFA0, 8);
        func_08000B20(func_080D3AF8(), 0x63FD, 0x06005800, 0x400);
        descriptor->phase++;
        break;
    case 0x101:
        work->offset = 0;
        work->first_value = 8;
        work->second_value = 8;
        work->handle = func_08147D2C(1, 0x5F, 20, work->selected);
        if (work->mode == 1) {
            background->offset = work->offset;
            func_08003620(0);
            settings = func_08003A74(0x06005800);
            settings |= func_08003A80(0x06008000) | 3;
            func_080034B8(settings, 2);
            func_08003508(0, 2);
            func_08003558(0, 2);
            shadow->control = func_080035F8(2) | 0x40;
            shadow->configuration = 0x20;
            shadow->first_value = work->first_value;
            shadow->second_value = work->second_value;
            mask = func_080035A8(2);
            shadow->flags |= mask;
            func_080075CC(&work->first, work->first_value, 0, 0, 20);
            func_080075CC(&work->second, work->second_value, 0, 16, 20);
            func_0801DC04();
        }
        descriptor->phase++;
        break;
    case 0x102:
        if (work->mode == 1) {
            func_080076A0(&work->first);
            func_080076A0(&work->second);
            shadow->first_value = work->first.current;
            shadow->second_value = work->second.current;
            if (!func_08007880(&work->first) || !func_08007880(&work->second)) {
                break;
            }
        }
        if (!func_081485D4(work->handle)) {
            break;
        }
        func_08148498(work->handle);
        work->handle = 0;
        if (work->mode == 1) {
            shadow->control = 0;
            mask = func_080035A8(2);
            shadow->flags &= ~mask;
        }
        func_080D3A30();
        descriptor->phase = 2;
        break;
    }
    return 0;
}
