#include "item_quantity_menu.h"

typedef struct __attribute__((packed)) {
    u32 name;
    u8 unknown_04;
    u8 appearance;
    u8 unknown_06;
    u8 level;
    u32 health : 10;
    u32 magic : 10;
    u32 attack : 11;
    u32 defense : 11;
    u32 power : 11;
    u32 resistance : 11;
} UnitTemplate;

typedef struct {
    u8 unknown_0000[0x2E78];
    UnitTemplate templates[256];
} GameState;

typedef struct {
    u8 unknown_00[8];
    u32 count;
    u8 unknown_0C[2];
    u16 item;
} MessageArguments;

/* The input word and the two BG layers are declared identically in
 * src/08055F10.c and src/0805ADA4.c; data_03000990 is the second layer,
 * whose stride (+0x0C) and map (+0x14) func_0802B164 reads.  The action
 * records, the list, its controls and the context come from
 * include/item_quantity_menu.h. */
typedef struct {
    u16 held;
    u16 pressed;
    u16 repeated;
} MenuInput;

typedef struct {
    u8 unknown_00[0x10];
    u8 *tiles;
    u16 *map;
} GraphicsState;

typedef struct {
    u16 identifier;
    u8 quantity;
    u8 unknown_03;
} InventoryRecord;

typedef void (*MenuCallback)(void *argument);

extern GameState g_state_02000000;
extern MessageArguments g_state_020020D0;
extern MenuInput data_03000000;
extern GraphicsState data_030008B0;
extern GraphicsState data_03000990;
extern u8 data_0600C000[];

extern void func_080592D0(const ByteStore *store);
extern void func_08059454(u8 index, u8 *state);
extern void func_0805C10C(void);

extern void func_08001CF0(const void *, s32, s32, u8, u8, u8, u8, u8, u32,
                          u8, u32);
extern u16 func_08011860(void);
extern s8 func_08013380(void);
extern void func_08013390(void *object);
extern void func_08013434(void);
extern void func_08016234(void *window);
extern u8 func_08017180(void *window);
extern void func_08017FB0(MenuControls *controls, u8 row);
extern void func_08017FBC(void *object, u32 direction);
extern void func_08019AE4(void *context, u16 value, void *first,
                          void *second, u8 mode);
extern void func_0802995C(void *control);
extern void func_08029CD8(void *control, u8 first, u8 second);
extern void func_08029D20(void *control, u8 mode);
extern u8 func_08029D2C(void *control);
extern void func_08029F7C(void *menu, u8 flags, MenuCallback scroll,
                          void *argument, ButtonAction *actions,
                          u8 action_count);
extern void func_0802A1FC(void *window, u8 a, u8 b, u8 c, u8 d, u16 value,
                          u8 selection);
extern void func_0802A290(void *window, u8 appearance);
extern void func_0802A2C0(u8 x, u8 y, u8 width, u8 height);
extern void func_0802A370(u8 x, u8 y, u8 width, u8 height);
extern void func_0802A424(u8 x, u8 y, u8 width, u8 height);
extern void func_0802A5CC(void *dialog, void *panel, u16 index, u16 field,
                          u8 mode, u8 x, u8 y);
extern void func_0802A6A0(void *dialog);
extern void func_0802AB4C(void *dialog, u8 value);
extern u8 func_0802AB54(void *dialog);
extern u8 func_0802AB5C(void *dialog);
extern void func_0802B108(MenuList *list);
extern void func_0802B164(void *panel, GraphicsState *first,
                          GraphicsState *second, u16 tile, u16 identifier,
                          u8 x, u8 y);
extern void func_0802B2A8(GraphicsState *first, GraphicsState *second, u8 x,
                          u8 y);
extern void func_0802B368(void *window, u8 *destination, u8 first,
                          u8 second);
extern void *func_0802B3D4(void *animation);
extern u16 func_0802B430(void *animation, u8 index);
extern void func_0802B53C(void *message, u8 value);
extern u8 func_0802B548(void *message);
extern void func_0802B554(void *message, u8 value);
extern void func_0802B56C(void *message, u8 value);
extern void func_0802B584(void *message, u8 value);
extern void func_0802B590(void *message, u8 value);
extern void func_0802B59C(void *message, u8 value);
extern void func_08058890(u8 value);
extern void func_08058908(u8 category, u16 id, u8 count);
extern u8 func_08058C0C(void);
extern void func_08059344(u8 index, u8 x, u8 y);
extern void func_0805BE68(u8 position, u8 row);
extern void func_0805BFC0(u8 *state);
extern void func_0805C09C(void);
extern void func_0805C4BC(u8 selector, u8 value);
extern void func_0805C568(void);
extern s32 func_080CA7A4(u16 identifier, u8 selector);
extern InventoryRecord *func_080CB210(u32 identifier, s32 *count);
extern u16 func_080CC86C(u16 identifier);
extern u8 func_080CCAD8(u8 index);
extern void func_08141540(u16 song_id);

/* Complete target: [0x0805ADA4, 0x0805BE68), 4292 bytes, 1181 instructions
 * (a 256-entry jump table at 0x0805ADCC dispatches the state byte).
 * f0b557464e464546e0b487b00f1c3878ff2801d900f0ecff800002494018006887460000
 * ccad0508ccb1050894bd050894bd050894bd050894bd050894bd050894bd050894bd0508
 * 94bd050894bd050894bd050894bd050894bd050894bd050894bd050894bd050894bd0508
 * 94bd050894bd050894bd050834b205088cb2050820b3050894bd050894bd050894bd0508
 * 94bd050894bd050894bd050894bd050894bd050894bd050894bd050894bd050894bd0508
 * 94bd050894bd050894bd050894bd050894bd0508ccb5050894b60508b4b6050894bd0508
 * 94bd050894bd050894bd050894bd050894bd050894bd050894bd050894bd050894bd0508
 * 94bd050894bd050894bd050894bd050894bd050894bd050894bd050828b7050840b70508
 * d4b7050826b905087cb9050894b905082cba050898ba0508d4ba050894bd050894bd0508
 * 94bd050894bd050894bd050894bd050894bd050894bd050894bd050894bd050894bd0508
 * f0ba05080cbb050894bd050894bd050894bd050894bd050894bd050894bd050894bd0508
 * 94bd050894bd050894bd050894bd050894bd050894bd050894bd050894bd050894bd0508
 * 94bd050894bd050834bb050838bb05089cbb050894bd050894bd050894bd050894bd0508
 * 94bd050894bd050894bd050894bd050894bd050894bd050894bd050894bd050894bd0508
 * 94bd050894bd050894bd050894bd0508c8bb0508e4bb050894bd050894bd050894bd0508
 * 94bd050894bd050894bd050894bd050894bd050894bd050894bd050894bd050894bd0508
 * 94bd050894bd050894bd050894bd050894bd050894bd05080cbc050824bc050840bc0508
 * 94bd050894bd050894bd050894bd050894bd050894bd050894bd050894bd050894bd0508
 * 94bd050894bd050894bd050894bd050894bd050894bd050894bd050894bd050864bc0508
 * a4bc050894bd050894bd050894bd050894bd050894bd050894bd050894bd050894bd0508
 * 94bd050894bd050894bd050894bd050894bd050894bd050894bd050894bd050894bd0508
 * 94bd0508ccbc050808bd050894bd050894bd050894bd050894bd050894bd050894bd0508
 * 94bd050894bd050894bd050894bd050894bd050894bd050894bd050894bd050894bd0508
 * 94bd050894bd050894bd050830bd050894bd050894bd050894bd050894bd050894bd0508
 * 94bd050894bd050894bd050894bd050894bd050894bd050894bd050894bd050894bd0508
 * 94bd050894bd050894bd050894bd050894bd050894bd050894bd050894bd050894bd0508
 * 94bd050894bd050894bd050894bd050894bd050894bd050894bd050894bd050894bd0508
 * 94bd050894bd050894bd050894bd050894bd050894bd050894bd050894bd050894bd0508
 * 94bd050894bd050894bd050894bd050894bd050894bd050894bd050894bd050894bd0508
 * 94bd050894bd050894bd050894bd050860bd0508114c2068114940180021d0f7dbf91049
 * 2068104a8018007800010f4bc91840180078002101f064f920680c4d40190821cff7a6fc
 * 20680a4a811800220a70094bc01802707fe2000028f400021414000000000002b61b0000
 * 7f2e0000ec100000bf1b0000be1b0000114d2868114c00190b210091c021019101210291
 * 022109221223cef7d5ff29680c190b480918201c0f220823d0f782f801f080f928680749
 * 4018002101701520387000f08dfd000028f40002f40c0000540b00008c3300001b4c2068
 * 1b4a8018bbf774ff0006002801d100f079fd2168174bc8180078174d4919097800f0dafd
 * 2068de214901401800210022cef70afd2168114bca1802201080104d4a19104810601048
 * 0a181c33c81810600760283549198c200860a020387020680a494018162100f04cfd0000
 * 28f40002f40c0000be1b0000bf1b0000542c00004c2c0000d1920508502c0000a02c0000
 * 044a518801200840002805d0381c00f047fe38e100000003042008400004030c002b2fd0
 * 114d2968114a8818007880000918104bc918088801216ff023fa011c0904090c28680c4a
 * 0c4b02240094bef7b9fb2868b8f70cf8b8f75cf8c82038702868074c0019162101700ce1
 * 28f40002ba1b0000a42c0000b008000390090003d50c00001188802080000840002800d1
 * b0e091884020084000283bd00d4c22680d4d501901880025405f002816d1d42000011118
 * 487c002800d1e4e0081c0021bcf7e6fd2068d421090140184021bcf7e5fd86e028f40002
 * 3a0d0000081f0004002805da014c1019037005e0be1b00000439064d5019017005480168
 * 034a88180078d4231b01c91868e00000be1b000028f400028020084000286bd00e490a68
 * 0e4c131918880d1c042819d8d42000011418617c1a88501e814211d0011c0906090e201c
 * bcf7a4fd2868d421090140188021bcf7a3fd44e028f40002b81b00002a680e4c13190020
 * 195e0d4c10190088041fa14216d1d42000011118487c032800d180e0081c0321bcf782fd
 * 2868d421090140188021bcf781fd22e03a0d0000b81b0000051c04286dd91988081d0004
 * 0014a04206dd291f014bd01805e00000be1b00000431094c1019017008480168064d4819
 * 0078d42212018918497c00f0b3fc6d20e6f01cf84de00000be1b000028f4000209480168
 * 094bc8180088042814d8084c0819084d491900910121019100220023cef722fd14e00000
 * 28f40002b81b0000f40c00004c2c00001a4a88181a4a1b4bc91800910121019100210023
 * cef70cfd174d2868d42424010119d22212018018497c09060916bcf7f5fa0006040e2868
 * 104bc0180078a0420bd000f085fd2868d22109014018cff7b5fd2868094a801804700748
 * 0068034bc018baf741fe00f0effb0000f40c00000dc105084c2c000028f40002ba1b0000
 * 284ca046256828496818284ea919c2229200c3239b00264ca2462c1c54442478a400a146
 * 4d44234c2d192c780094112401940b25a9460295cef7e2ff0020002100220023cef756fe
 * 0020002100220023cef7a8fe03200b210d220223cef7fcfe40460468a519144e144a3169
 * 1448401a002800da1f30c3021b0c514660180078800020180f4c00190088009003200190
 * 48460290281c311ccff77efd2920387092e3000028f40002ec10000084110000ba1b0000
 * a62c0000b00800039009000300c00006a42c00000548006805494018cff75afa0006000e
 * 012800d074e31ae228f40002ec1000000948418801200840002813d06420e5f03dff0648
 * 0068064a80180221cff73cfa3c2038705ce300000000000328f40002ec10000002200840
 * 002800d150e36920e5f024ff07480068074bc0180521cff723fa0648064903220b23cff7
 * cbfd142038703de328f40002ec100000b0080003900900035020387002480068024c0019
 * 3d212ce328f40002a02c00001e4c1f4d28681f4a81180978890041181d4bc9180988e181
 * 1c494018cff7fef90006000ea0602868194c00190221cff7fdfe286800190121cff710ff
 * 286800190121cff7dbfe286800199a21cff7e2fe0020002100220023cef792fd00200021
 * 00220023cef7e4fd03200b210d220223cef738fe3e203870ece20000d020000228f40002
 * ba1b0000a42c0000ec10000014140000394a92461068394c0019cff7b3fe0006000e0528
 * 00d0d3e25346186800190421cff7a2feb7f7c2fd000600168146002870d1544620682e4d
 * 4119097888462d4c01190978890041182b4d49190e882b494018cff799f9021c1206120e
 * 4046311cfdf768f85246116808190078800009184919088800216ff0e1fc061c53461968
 * 0c192078800009184919088871f004f8041c5546286819494018cff775f92404a40ba419
 * a178091aa1702868144a81184b460b70134c001903702868124d40190121017011495246
 * 1068094bc018007800010f4c091940180078002100f004fe412038706ce2000028f40002
 * 14140000b61b0000ba1b0000a42c0000ec100000bf1b0000be1b00008c33000000000002
 * 7f2e0000b7f74afd00060016012806d15546286800199e21cff72afe91e0b7f73dfd0006
 * 001601214942884200d03fe25146086800190621cff70efe4320387036e20f4c20680f4a
 * 8018cff70bfe0006002800d02ce25020387020680a4bc018402101702068094c00190521
 * cff7fcf80748084903220b23cff7a4fc18e2000028f4000214140000a02c0000ec100000
 * b0080003900900036420387002480068024d4019142102e228f40002a02c00001b4c2068
 * 1b4d4019cff7d4fd0006000e052800d0f4e11848418801200840002800d1ede1fdf728f9
 * 000600282cd1206840190421cff7b8fd206840199921cff7bffd2068de21490140180221
 * cef79ef920680a4a80180521cff7aef80848094903220b23cff756fc42203870c8e10000
 * 28f400021414000000000003ec100000b008000390090003206840190621cff78bfd3f20
 * 3870b3e1164c2068164d4019cff788fd0006002800d0a9e12068de235b01c018cef770f9
 * 0006000e042800d09ee10020002100220023cef787fc206840190121cff792fd2068084d
 * 4019084a0021abf731f82068cf21090140183c2185e1000028f4000214140000d80c0000
 * 559405080b4c20680b4a8018cff752fd0006002800d073e103200b210d220223cef7b6fc
 * 652038702068044bc018442165e1000028f4000214140000a02c000004480068044c0019
 * 0121cff735f82a20387055e128f40002ec10000004480068044d40190621cff71ffd5120
 * 387047e128f4000214140000064c206806494018cff718fd0006002800d039e12068034a
 * 801811e128f4000214140000a02c000000f018fd134d2868134c0619134b984640440078
 * 70f0c6ff011c0906090e301ccff716fd286800190021cff71dfd286800190221cff7e8fc
 * 09492868404400780001084c091940180078fcf787fe6620387005e128f4000214140000
 * b61b0000000000027f2e0000074c2068074d4019cff7d0fc0006000e052800d0f0e02068
 * 03494018c8e0000028f4000214140000a02c000004480068044a80180121cef75dfb7920
 * 3870dbe028f40002f40c0000064c2068064bc018bbf7c8fa0006002800d1cde02068034c
 * a5e0000028f40002f40c0000a02c0000b420387002480068024d40198d21bae028f40002
 * a02c000004480068044940180121cef72ffb8e203870ade028f40002f40c000006480068
 * 064a8018bbf79afa0006002800d19fe0ff2038709ce0000028f40002f40c00000a4c2068
 * de235b01c018cef75df80006000e04280ed12068054c0019007817210a22fdf75dfba120
 * 387081e028f40002b61b00002068014d401955e0a02c0000074c2068de2149014018cef7
 * 3df80006000e01286cd12068024a801844e0000028f40002a02c00000a4c2068de235b01
 * c018cef729f80006000e01280cd12068de24640100190221cef718f8b52038704ee00000
 * 28f400022068014d401923e0a02c0000074c2068de2149014018cef70bf80006000e0428
 * 3ad12068024a801812e0000028f40002a02c0000b5f796fd000400282cd0064c2068064b
 * c018b7f725fb2068044c00190078387020e0000028f4000214140000d50c0000364c2068
 * 364d40190121cff711fc0020002100220023cef7fbfa206831494018314a0021aaf7aafe
 * 2068cf22120180183e210170294d2868de2464010019cdf7ddfd28680019cdf7c1ff0006
 * 000e012836d1264b98462968254fc819007800014044244c00190068002829d0224a8818
 * 0478002c24d1214e88190221cff728fb000400280ad02868c019007800011c4941444018
 * 0078002100f060fb28688019cff7e8fa0094019402940394c8218900049105940694d421
 * 64220023a5f768ff064800680f4bc018cef73afc07b038bc9846a146aa46f0bc01bc0047
 * 28f4000214140000d80c00005594050800000002b61b0000782e00008c330000e8330000
 * 7f2e0000ec100000
 */
/* The cursor row is read through the controls record's address, beside its
 * setter func_08017FB0: each of the five reads adds 0xD40 to the context and
 * loads [base, #0x11] from it (ldrb at 0x0805B3D4, 0x0805B452, 0x0805B49C,
 * 0x0805B4FC in the shared func_0805BE68 tail, and 0x0805B574 for
 * func_08017B68), as in src/08054E14.c and src/08055F10.c. */
#define CURSOR_ROW(controls) ((controls)->row)

void func_0805ADA4(u8 index, u8 *state)
{
    switch (*state) {
    case 0x00:
        func_0802B590(data_0200F428->message, 0);
        func_0805C4BC(g_state_02000000.templates[data_0200F428->unit].level, 0);
        func_0802AB4C(data_0200F428->dialog, 8);
        /* One load of data_0200F428 (0x0805B200) serves both byte stores. */
        data_0200F428->saved_position = data_0200F428->saved_row = 0;
        *state = 0x14;
        break;
    case 0x14:
        func_0802A1FC(data_0200F428->window, 2, 9, 18, 11, 192, 1);
        func_0802B368(data_0200F428->window, data_0200F428->text, 15, 8);
        func_0805C568();
        data_0200F428->unknown_338C = 0;
        *state = 0x15;
        break;
    case 0x15:
        if (func_08017180(data_0200F428->window)) {
            func_0805BE68(data_0200F428->saved_position, data_0200F428->saved_row);
            func_08029CD8(data_0200F428->control, 0, 0);
            data_0200F428->actions[0].buttons = 2;
            data_0200F428->actions[0].callback = func_080592D0;
            data_0200F428->actions[0].argument = &data_0200F428->store;
            data_0200F428->store.destination = state;
            data_0200F428->store.value = 0x8C;
            *state = 0xA0;
            data_0200F428->next = 0x16;
        }
        break;
    case 0x16:
        if (data_03000000.pressed & 1) {
            func_0805BFC0(state);
        } else if (data_03000000.pressed & 4) {
            func_08019AE4(data_0200F428,
                          func_080CA7A4(data_0200F428->entries[data_0200F428->selected].identifier, 1),
                          &data_030008B0, &data_03000990, 2);
            func_08013390(data_0200F428);
            func_08013434();
            *state = 0xC8;
            data_0200F428->resume = 0x16;
        } else if ((data_03000000.held & 0x200) && (data_03000000.repeated & 0x40)) {
            if (data_0200F428->list.position == 0) {
                if (CURSOR_ROW(&data_0200F428->controls) != 0) {
                    func_08017FB0(&data_0200F428->controls, 0);
                    func_08017FBC(&data_0200F428->controls, 0x40);
                    func_08141540(0x6D);
                }
            } else {
                /* The test reads the sum as an s16 (lsls at 0x0805B3FE); the
                 * store subtracts 4 from the loaded halfword again
                 * (0x0805B410). */
                s16 top = data_0200F428->list.position - 4;

                if (top < 0)
                    data_0200F428->saved_position = 0;
                else
                    data_0200F428->saved_position = data_0200F428->list.position - 4;
                func_0805BE68(data_0200F428->saved_position, CURSOR_ROW(&data_0200F428->controls));
                func_08141540(0x6D);
            }
        } else if ((data_03000000.held & 0x200) && (data_03000000.repeated & 0x80)) {
            if (data_0200F428->count <= 4
                && CURSOR_ROW(&data_0200F428->controls) != data_0200F428->count - 1) {
                func_08017FB0(&data_0200F428->controls, data_0200F428->count - 1);
                func_08017FBC(&data_0200F428->controls, 0x80);
                func_08141540(0x6D);
            } else if (data_0200F428->list.position == data_0200F428->count - 4) {
                if (CURSOR_ROW(&data_0200F428->controls) != 3) {
                    func_08017FB0(&data_0200F428->controls, 3);
                    func_08017FBC(&data_0200F428->controls, 0x80);
                    func_08141540(0x6D);
                }
            } else if (data_0200F428->count > 4) {
                /* As above: lsls/asrs at 0x0805B4CE for the test, and the
                 * store adds 4 to the loaded halfword again (0x0805B4E4). */
                s16 top = data_0200F428->list.position + 4;

                if (top > data_0200F428->count - 4)
                    data_0200F428->saved_position = data_0200F428->count - 4;
                else
                    data_0200F428->saved_position = data_0200F428->list.position + 4;
                func_0805BE68(data_0200F428->saved_position, CURSOR_ROW(&data_0200F428->controls));
                func_08141540(0x6D);
            }
        } else {
            u8 selected;
            u8 row;

            if (data_0200F428->count <= 4)
                func_08029F7C(data_0200F428->window, 1, 0, 0, data_0200F428->actions, 1);
            else
                func_08029F7C(data_0200F428->window, 0, (MenuCallback)func_0805C10C, 0,
                              data_0200F428->actions, 1);
            row = CURSOR_ROW(&data_0200F428->controls);
            selected = func_08017B68(&data_0200F428->list, row);
            if (data_0200F428->selected != selected) {
                func_0805C09C();
                func_0802B108(&data_0200F428->list);
                data_0200F428->selected = selected;
            }
        }
        func_08016234(data_0200F428->window);
        break;
    case 0x28:
        func_0802A5CC(data_0200F428->dialog, data_0200F428->panel, 0x308, 0x30C,
                      data_0200F428->entries[data_0200F428->selected].quantity, 17, 11);
        func_0802A2C0(0, 0, 0, 0);
        func_0802A370(0, 0, 0, 0);
        func_0802A424(3, 11, 13, 2);
        func_0802B164(data_0200F428->panel, &data_030008B0, &data_03000990,
                      (data_0600C000 - data_030008B0.tiles) / 32,
                      data_0200F428->entries[data_0200F428->selected].identifier, 3, 11);
        *state = 0x29;
        break;
    case 0x29:
        if (func_0802AB54(data_0200F428->dialog) == 1)
            *state = 0x2A;
        break;
    case 0x2A:
        if (data_03000000.pressed & 1) {
            func_08141540(100);
            func_0802AB4C(data_0200F428->dialog, 2);
            *state = 0x3C;
        } else if (data_03000000.pressed & 2) {
            func_08141540(0x69);
            func_0802AB4C(data_0200F428->dialog, 5);
            func_0802B2A8(&data_030008B0, &data_03000990, 3, 11);
            *state = 0x14;
        }
        break;
    case 0x3C:
        *state = 0x50;
        data_0200F428->next = 0x3D;
        break;
    case 0x3D:
        g_state_020020D0.item = data_0200F428->entries[data_0200F428->selected].identifier;
        g_state_020020D0.count = func_0802AB5C(data_0200F428->dialog);
        func_0802B56C(data_0200F428->message, 2);
        func_0802B59C(data_0200F428->message, 1);
        func_0802B53C(data_0200F428->message, 1);
        func_0802B554(data_0200F428->message, 0x9A);
        func_0802A2C0(0, 0, 0, 0);
        func_0802A370(0, 0, 0, 0);
        func_0802A424(3, 11, 13, 2);
        *state = 0x3E;
        break;
    case 0x3E:
        if (func_0802B548(data_0200F428->message) == 5) {
            func_0802B53C(data_0200F428->message, 4);
            if (func_08013380() == 0) {
                func_08058908(data_0200F428->unit,
                              data_0200F428->entries[data_0200F428->selected].identifier,
                              func_0802AB5C(data_0200F428->dialog));
                func_080CB210(data_0200F428->entries[data_0200F428->selected].identifier, 0)
                    [func_080CC86C(data_0200F428->entries[data_0200F428->selected].identifier)]
                    .quantity -= func_0802AB5C(data_0200F428->dialog);
                data_0200F428->saved_position = data_0200F428->saved_row = 0;
                data_0200F428->unknown_338C = 1;
                func_0805C4BC(g_state_02000000.templates[data_0200F428->unit].level, 0);
                *state = 0x41;
            } else if (func_08013380() == 1) {
                func_0802B554(data_0200F428->message, 0x9E);
                *state = 0x3F;
            } else if (func_08013380() == -1) {
                func_0802B53C(data_0200F428->message, 6);
                *state = 0x43;
            }
        }
        break;
    case 0x3F:
        if (func_0802B548(data_0200F428->message) == 0) {
            *state = 0x50;
            data_0200F428->next = 0x40;
            func_0802AB4C(data_0200F428->dialog, 5);
            func_0802B2A8(&data_030008B0, &data_03000990, 3, 11);
        }
        break;
    case 0x40:
        *state = 0x64;
        data_0200F428->next = 0x14;
        break;
    case 0x41:
        if (func_0802B548(data_0200F428->message) == 5 && (data_03000000.pressed & 1)) {
            if (func_08058C0C() == 0) {
                func_0802B53C(data_0200F428->message, 4);
                func_0802B554(data_0200F428->message, 0x99);
                func_08029D20(data_0200F428->control, 2);
                func_0802AB4C(data_0200F428->dialog, 5);
                func_0802B2A8(&data_030008B0, &data_03000990, 3, 11);
                *state = 0x42;
            } else {
                func_0802B53C(data_0200F428->message, 6);
                *state = 0x3F;
            }
        }
        break;
    case 0x42:
        if (func_0802B548(data_0200F428->message) == 0
            && func_08029D2C(data_0200F428->control) == 4) {
            func_0802A370(0, 0, 0, 0);
            func_0802B590(data_0200F428->message, 1);
            func_08006ADC(&data_0200F428->tasks, 0, (u32)func_08059454);
            data_0200F428->handler_flags[0] = 0x3C;
        }
        break;
    case 0x43:
        if (func_0802B548(data_0200F428->message) == 0) {
            func_0802A424(3, 11, 13, 2);
            *state = 0x65;
            data_0200F428->next = 0x44;
        }
        break;
    case 0x44:
        func_0802AB4C(data_0200F428->dialog, 1);
        *state = 0x2A;
        break;
    case 0x50:
        func_0802B53C(data_0200F428->message, 6);
        *state = 0x51;
        break;
    case 0x51:
        if (func_0802B548(data_0200F428->message) == 0)
            *state = data_0200F428->next;
        break;
    case 0x64:
        /* The table sends 0x64 to 0x0805BB34, one bl ahead of 0x65's
         * 0x0805BB38: 0x64 falls through. */
        func_0805C568();
    case 0x65:
        func_0802B584(data_0200F428->message, func_080CCAD8(data_0200F428->unit));
        func_0802B59C(data_0200F428->message, 0);
        func_0802B53C(data_0200F428->message, 2);
        func_08058890(g_state_02000000.templates[data_0200F428->unit].level);
        *state = 0x66;
        break;
    case 0x66:
        if (func_0802B548(data_0200F428->message) == 5)
            *state = data_0200F428->next;
        break;
    case 0x78:
        func_0802A290(data_0200F428->window, 1);
        *state = 0x79;
        break;
    case 0x79:
        if (func_08017180(data_0200F428->window))
            *state = data_0200F428->next;
        break;
    case 0x8C:
        *state = 0xB4;
        data_0200F428->next = 0x8D;
        break;
    case 0x8D:
        func_0802A290(data_0200F428->window, 1);
        *state = 0x8E;
        break;
    case 0x8E:
        if (func_08017180(data_0200F428->window))
            *state = 0xFF;
        break;
    case 0xA0:
        if (func_08029D2C(data_0200F428->control) == 4) {
            func_08059344(data_0200F428->unit, 0x17, 10);
            *state = 0xA1;
        } else {
            *state = data_0200F428->next;
        }
        break;
    case 0xA1:
        if (func_08029D2C(data_0200F428->control) == 1)
            *state = data_0200F428->next;
        break;
    case 0xB4:
        if (func_08029D2C(data_0200F428->control) == 1) {
            func_08029D20(data_0200F428->control, 2);
            *state = 0xB5;
        } else {
            *state = data_0200F428->next;
        }
        break;
    case 0xB5:
        if (func_08029D2C(data_0200F428->control) == 4)
            *state = data_0200F428->next;
        break;
    case 0xC8:
        if (func_08011860()) {
            func_08013390(data_0200F428->message);
            *state = data_0200F428->resume;
        }
        break;
    case 0xFF:
        func_0802B590(data_0200F428->message, 1);
        func_0802A370(0, 0, 0, 0);
        func_08006ADC(&data_0200F428->tasks, 0, (u32)func_08059454);
        data_0200F428->handler_flags[0] = 0x3E;
        break;
    }

    func_0802995C(data_0200F428->control);
    if (func_08029D2C(data_0200F428->control) == 1
        && g_state_02000000.templates[data_0200F428->unit].name != 0
        && data_0200F428->unknown_338C == 0) {
        if (func_0802B430(data_0200F428->animation, 2))
            func_0805C4BC(g_state_02000000.templates[data_0200F428->unit].level, 0);
        func_08001CF0(func_0802B3D4(data_0200F428->animation), 0xD4, 100, 0, 0,
                      0, 0, 0, 800, 0, 0);
    }
    func_0802A6A0(data_0200F428->dialog);
}
