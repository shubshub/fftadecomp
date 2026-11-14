#include "ffta.h"
#include "control_flags.h"

// Target 0x08113CE0..0x08113FEC, 780 bytes including literal pools:
// f0b5b4b0071c0e1c151c338882204000834200d1c4e0834228dc0438834260d0834204dc
// 002b41d0012b57d069e181204000834274d0834200dd9be0e86bccf7dbf8e863002800d0
// 5be1281c083003900230049004481c2102aa3b1cf1f616ff6861308801304be1ed2a1108
// 0748834200d1d5e083420bdc0238834200d1a3e00130834200d1b5e03be1000007010000
// 0548834200d117e1834200dad4e00130834200d125e12ce109010000f08aa87174686c63
// 09220006002800d00022064900930197201c0723ccf726fb2863a91c281c0af79dfc14e1
// 54353a08bff77afd0fe1a87900280bd0286bccf707fc2863002800d005e1014802e10000
// 09010000286bccf7fbfb2863002800d0f9e001201e213a1ccbf7b8ffe86330880130efe0
// 6869ccf78bfb6861002800d0e9e0c020f6f620fc011ce9600c4c201c5f222df025fdbff7
// 6ffd211c5f222df01ffd09aa288990826889d08205481c213b1cf1f695fea86130880130
// cae0000062380003892e1108a869ccf761fba861002800d0bfe010aa281c103050600448
// 1c213b1cf1f67cfee86130880130b1e0812f1108e869ccf74bfbe861002800d0a9e00548
// aa21890017aa3b1cf1f668fe2862308801309de021321108286accf737fb2862002800d0
// 95e01eaa281c1030506004482c213b1cf1f652fe68623088013087e00d361108686accf7
// 21fb6862002800d07fe025aa281c10305060044860213b1cf1f63cfea8623088013071e0
// 19391108a86accf70bfba86200286ad105482caa10213b1cf1f62afee8621e20a8803088
// 01305de0693c1108a8880138a8800004002856d10af7b6f933a86946cd310af767fb33a8
// 0078eff62ffb154c2188014321806846cd300078eff626fb2188014321800021685e0222
// a95e0af739fb07f783fce8680b495f222df078fce868f6f673fb686b01f0a2fd09f7d8fd
// 00201e213a1ccbf7e9fee8633088013020e000004009000362380003e86bcbf795ffe863
// 002816d1e86accf7b1fae862002810d1686b03213a1c01f08dfda8633088013006e0a86b
// 01f0b4fda863002801d102203080002034b0f0bc02bc0847

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *argument;
    u8 unknown_08[0xE];
    u16 mode;
} Request;

typedef struct {
    s16 x;
    s16 y;
    u16 timer;
    u8 mode;
    u8 unknown_07;
    u16 width;
    u16 height;
    void *buffer;
    u8 unknown_10[4];
    void *task0;
    void *task1;
    void *task2;
    void *task3;
    void *task4;
    void *task5;
    void *task6;
    void *object;
    void *argument;
    void *task7;
    void *fade;
} State;

typedef struct {
    u32 unknown_00;
    void *first;
    void *second;
    u8 unknown_0C[8];
    u16 width;
    u16 height;
    u8 unknown_18[4];
} Descriptor;

typedef u32 (*TaskCallback)(void *task, void *request, void *payload);

extern const u8 data_083A3554[];
extern u8 data_03003862[];
extern u32 func_08112AEC(void *task, void *request, void *payload);
extern u32 func_08112E88(void *task, void *request, void *payload);
extern u32 func_08112F80(void *task, void *request, void *payload);
extern u32 func_08113220(void *task, void *request, void *payload);
extern u32 func_0811360C(void *task, void *request, void *payload);
extern u32 func_08113918(void *task, void *request, void *payload);
extern u32 func_08113C68(void *task, void *request, void *payload);
extern void *func_08005B6C(TaskCallback callback, u16 payload_size,
                         void *descriptor, void *parent);
extern void *func_080E03F8(void *, const void *, u32, u32, u32, void *);
extern void *func_080E05DC(void *);
extern void *func_080E051C(void *);
extern void *func_080DFD68(int, int, void *);
extern void *func_080DFED8(void *);
extern void *func_08115AE4(void *, int, void *);
extern void *func_08115B40(void *);
extern void func_08115ACC(void *);
extern void func_080D38B4(void);
extern void *func_080D3904(void);
extern void func_0801E6F0(s16 *first, s16 *second);
extern void *func_0800A654(u32 size);
extern void func_0800A668(void *allocation);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_0801E2A4(void);
extern void func_0801E610(u8 *first, u8 *second);
extern u16 func_080035A8(u8 index);
extern void func_0801E5E0(s16 x, s16 y);
extern void func_0801B878(void);
extern void func_0801DB3C(void);

static inline void enable_layers(void)
{
    u8 first;
    u8 second;

    func_0801E610(&first, &second);
    g_control_flags_03000940.display |= func_080035A8(first);
    g_control_flags_03000940.display |= func_080035A8(second);
}

u32 func_08113CE0(void *owner, Request *request, State *state)
{
    Descriptor d0;
    Descriptor d1;
    Descriptor d2;
    Descriptor d3;
    Descriptor d4;
    Descriptor d5;
    Descriptor d6;
    u32 kind;

    switch (request->phase) {
    case 0:
        state->mode = request->mode;
        state->argument = request->argument;
        kind = 9;
        if (state->mode)
            kind = 0;
        state->object = func_080E03F8(state->argument, data_083A3554, kind, 7, 0,
                                      owner);
        func_0801E6F0(&state->x, &state->y);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        if (state->mode) {
            state->object = func_080E05DC(state->object);
            if (state->object == 0)
                request->phase = 0x109;
        } else {
            state->object = func_080E05DC(state->object);
            if (state->object == 0) {
                state->fade = func_080DFD68(1, 30, owner);
                request->phase++;
            }
        }
        break;
    case 0x101:
        state->fade = func_080DFED8(state->fade);
        if (state->fade == 0) {
            d0.first = &state->width;
            d0.second = &state->height;
            state->task0 = func_08005B6C(func_08112AEC, 0x1C, &d0, owner);
            request->phase++;
        }
        break;
    case 0x102:
        state->task0 = func_080E051C(state->task0);
        if (state->task0 == 0) {
            state->buffer = func_0800A654(0xC0);
            func_0814186C(data_03003862, state->buffer, 0x5F);
            func_0814186C(func_080D3904(), data_03003862, 0x5F);
            d1.width = state->width;
            d1.height = state->height;
            state->task1 = func_08005B6C(func_08112E88, 0x1C, &d1, owner);
            request->phase++;
        }
        break;
    case 0x103:
        state->task1 = func_080E051C(state->task1);
        if (state->task1 == 0) {
            d2.first = state->unknown_10;
            state->task2 = func_08005B6C(func_08112F80, 0x1C, &d2, owner);
            request->phase++;
        }
        break;
    case 0x104:
        state->task2 = func_080E051C(state->task2);
        if (state->task2 == 0) {
            /* The ROM passes this descriptor without initialising it. */
            state->task3 = func_08005B6C(func_08113220, 0x2A8, &d3, owner);
            request->phase++;
        }
        break;
    case 0x105:
        state->task3 = func_080E051C(state->task3);
        if (state->task3 == 0) {
            d4.first = state->unknown_10;
            state->task4 = func_08005B6C(func_0811360C, 0x2C, &d4, owner);
            request->phase++;
        }
        break;
    case 0x106:
        state->task4 = func_080E051C(state->task4);
        if (state->task4 == 0) {
            d5.first = state->unknown_10;
            state->task5 = func_08005B6C(func_08113918, 0x60, &d5, owner);
            request->phase++;
        }
        break;
    case 0x107:
        state->task5 = func_080E051C(state->task5);
        if (state->task5 == 0) {
            /* The ROM passes this descriptor without initialising it. */
            state->task6 = func_08005B6C(func_08113C68, 0x10, &d6, owner);
            state->timer = 30;
            request->phase++;
        }
        break;
    case 0x108:
        if (--state->timer == 0) {
            func_0801E2A4();
            enable_layers();
            func_0801E5E0(state->x, state->y);
            func_0801B878();
            func_0814186C(state->buffer, data_03003862, 0x5F);
            func_0800A668(state->buffer);
            func_08115ACC(state->argument);
            func_0801DB3C();
            state->fade = func_080DFD68(0, 30, owner);
            request->phase++;
        }
        break;
    case 0x109:
        state->fade = func_080DFED8(state->fade);
        if (state->fade == 0) {
            state->task6 = func_080E051C(state->task6);
            if (state->task6 == 0) {
                state->task7 = func_08115AE4(state->argument, 3, owner);
                request->phase++;
            }
        }
        break;
    case 0x10A:
        state->task7 = func_08115B40(state->task7);
        if (state->task7 == 0)
            request->phase = 2;
        break;
    }
    return 0;
}
