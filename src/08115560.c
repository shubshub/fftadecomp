#include "ffta.h"
#include "control_flags.h"

// Target 0x08115560..0x0811584C, 748 bytes including literal pools:
// f0b5bbb0071c0e1c151c338882204000834200d1c8e083422adc0438834276d0834204dc
// 002b56d0012b6dd059e181204000834200d187e0834200dd9ce0686ccaf79afc68640028
// 00d04ae1281c08300390023004900548b021490002aa3b1cf0f6d4faa8613088013039e1
// ed3f110884204000834200d1d6e083421edc0238834200d1aae0834200ddbbe0686acaf7
// 95ff6862002800d023e11eaa288990826889d082044824213b1cf0f6affaa86230880130
// 14e10000bd4d110885204000834200d1f0e0834200dabfe00130834200d1fee005e1f08a
// a8717468ec6308220006002800d00022064900930197201c0723caf7d1fea863a91c281c
// 09f748f8efe0000048383a08bef724f9e9e0a879002809d0a86bcaf7b1ffa863002800d0
// dfe085204000dbe0a86bcaf7a7ffa863002800d0d5e001201e213a1ccaf764fb68643088
// 0130cbe0a869caf737ffa861002800d0c5e009aa281c103050600430906004482c213b1c
// f0f650fae86130880130b5e0ed411108e869caf71fffe861002800d0ade010aa281c1030
// 506004309060044880213b1cf0f638fa2862308801309de039441108286acaf707ff2862
// 002800d095e017aa281c10305060043090600548d02149003b1cf0f61ffa686230880130
// 84e0000011491108a86acaf7edfea862002800d07be0054825aa24213b1cf0f60bfae862
// 3088013070e000001d4f1108e86acaf7d9fee862002868d104482caa30213b1cf0f6f8f9
// 2863308801305de0a1511108286bcaf7c7fe2863002856d1044833aa10213b1cf0f6e6f9
// 6863308801304be0d954110808f77afd3aa86946e93108f72bff3aa80078edf6f3fe104c
// 2188014321806846e9300078edf6eafe2188014321800021685e0222a95e08f7fdfe06f7
// 47f8e86b00f06ef900201e213a1ccaf7b7fa6864308801301ee0000040090003686ccaf7
// 65fb6864002816d1686bcaf781fe6863002810d1e86b04213a1c00f05df9286430880130
// 06e0286c00f084f92864002801d10220308000203bb0f0bc02bc0847

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    u8 unknown_08[0xE];
    u16 hidden;
} Event08115560;

typedef struct {
    u32 unknown_00;
    void *first;
    void *second;
    u8 unknown_0C[8];
    u16 first_value;
    u16 second_value;
    u8 unknown_18[4];
} Request08115560;

typedef struct {
    s16 x;
    s16 y;
    u8 unknown_04[2];
    u8 hidden;
    u8 unknown_07;
    u16 first_value;
    u16 second_value;
    u8 unknown_0C[4];
    u8 unknown_10[4];
    u8 unknown_14[4];
    void *child0;
    void *child1;
    void *child2;
    void *child3;
    void *child4;
    void *child5;
    void *child6;
    void *child7;
    void *effect;
    void *object;
    void *selection;
    void *fade;
} Payload08115560;

typedef u32 (*Callback08115560)(void *, void *, void *);

extern const u8 data_083A3848[];
extern void *func_08005B6C(Callback08115560, u16, Request08115560 *, void *);
extern void *func_080DFED8(void *);
extern void *func_080E051C(void *);
extern void *func_080E05DC(void *);
extern void *func_080DFD68(int, int, void *);
extern void *func_080E03F8(void *, const void *, u32, u32, u32, void *);
extern void func_0801E6F0(s16 *, s16 *);
extern void func_080D38B4(void);
extern void func_0801E2A4(void);
extern void func_0801E610(u8 *, u8 *);
extern u16 func_080035A8(u8);
extern void func_0801E5E0(s16, s16);
extern void func_0801B878(void);
extern void func_08115ACC(void *);
extern void *func_08115AE4(void *, int, void *);
extern void *func_08115B40(void *);
extern u32 func_08113FEC(void *, void *, void *);
extern u32 func_081141EC(void *, void *, void *);
extern u32 func_08114438(void *, void *, void *);
extern u32 func_08114910(void *, void *, void *);
extern u32 func_08114DBC(void *, void *, void *);
extern u32 func_08114F1C(void *, void *, void *);
extern u32 func_081151A0(void *, void *, void *);
extern u32 func_081154D8(void *, void *, void *);

static inline void enable_layers(void)
{
    u8 first;
    u8 second;

    func_0801E610(&first, &second);
    g_control_flags_03000940.display |= func_080035A8(first);
    g_control_flags_03000940.display |= func_080035A8(second);
}

u32 func_08115560(void *task, Event08115560 *event, Payload08115560 *payload)
{
    switch (event->phase) {
    case 0: {
        u32 kind;

        payload->hidden = event->hidden;
        payload->object = event->object;
        kind = 8;
        if (payload->hidden)
            kind = 0;
        payload->effect = func_080E03F8(payload->object, data_083A3848,
                                        kind, 7, 0, task);
        func_0801E6F0(&payload->x, &payload->y);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        if (payload->hidden) {
            payload->effect = func_080E05DC(payload->effect);
            if (payload->effect != 0)
                break;
            event->phase = 0x10A;
        } else {
            payload->effect = func_080E05DC(payload->effect);
            if (payload->effect != 0)
                break;
            payload->fade = func_080DFD68(1, 30, task);
            event->phase++;
        }
        break;
    case 0x101: {
        Request08115560 request;
        payload->fade = func_080DFED8(payload->fade);
        if (payload->fade != 0)
            break;
        request.first = &payload->first_value;
        request.second = &payload->second_value;
        payload->child0 = func_08005B6C(func_08113FEC, 0x160, &request, task);
        event->phase++;
        break;
    }
    case 0x102: {
        Request08115560 request;
        payload->child0 = func_080E051C(payload->child0);
        if (payload->child0 != 0)
            break;
        request.first = payload->unknown_10;
        request.second = payload->unknown_14;
        payload->child1 = func_08005B6C(func_081141EC, 0x2C, &request, task);
        event->phase++;
        break;
    }
    case 0x103: {
        Request08115560 request;
        payload->child1 = func_080E051C(payload->child1);
        if (payload->child1 != 0)
            break;
        request.first = payload->unknown_10;
        request.second = payload->unknown_14;
        payload->child2 = func_08005B6C(func_08114438, 0x80, &request, task);
        event->phase++;
        break;
    }
    case 0x104: {
        Request08115560 request;
        payload->child2 = func_080E051C(payload->child2);
        if (payload->child2 != 0)
            break;
        request.first = payload->unknown_10;
        request.second = payload->unknown_14;
        payload->child3 = func_08005B6C(func_08114910, 0x1A0, &request, task);
        event->phase++;
        break;
    }
    case 0x105: {
        Request08115560 request;
        payload->child3 = func_080E051C(payload->child3);
        if (payload->child3 != 0)
            break;
        request.first_value = payload->first_value;
        request.second_value = payload->second_value;
        payload->child4 = func_08005B6C(func_08114DBC, 0x24, &request, task);
        event->phase++;
        break;
    }
    case 0x106: {
        Request08115560 request;
        payload->child4 = func_080E051C(payload->child4);
        if (payload->child4 != 0)
            break;
        /* The ROM passes this request without initialising it. */
        payload->child5 = func_08005B6C(func_08114F1C, 0x24, &request, task);
        event->phase++;
        break;
    }
    case 0x107: {
        Request08115560 request;
        payload->child5 = func_080E051C(payload->child5);
        if (payload->child5 != 0)
            break;
        /* The ROM passes this request without initialising it. */
        payload->child6 = func_08005B6C(func_081151A0, 0x30, &request, task);
        event->phase++;
        break;
    }
    case 0x108: {
        Request08115560 request;
        payload->child6 = func_080E051C(payload->child6);
        if (payload->child6 != 0)
            break;
        /* The ROM passes this request without initialising it. */
        payload->child7 = func_08005B6C(func_081154D8, 0x10, &request, task);
        event->phase++;
        break;
    }
    case 0x109:
        func_0801E2A4();
        enable_layers();
        func_0801E5E0(payload->x, payload->y);
        func_0801B878();
        func_08115ACC(payload->object);
        payload->fade = func_080DFD68(0, 30, task);
        event->phase++;
        break;
    case 0x10A:
        payload->fade = func_080DFED8(payload->fade);
        if (payload->fade != 0)
            break;
        payload->child7 = func_080E051C(payload->child7);
        if (payload->child7 != 0)
            break;
        payload->selection = func_08115AE4(payload->object, 4, task);
        event->phase++;
        break;
    case 0x10B:
        payload->selection = func_08115B40(payload->selection);
        if (payload->selection != 0)
            break;
        event->phase = 2;
        break;
    }
    return 0;
}
