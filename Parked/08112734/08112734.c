#include "ffta.h"
#include "control_flags.h"

// Target 0x08112734..0x08112A60, 812 bytes including literal pools:
// f0b5474680b4b6b080460f1c161c3b8882204000834200d1c0e0834230dc043883426ad0
// 834204dc002b49d0012b61d075e181204000834200d17de0834200dd8ee0f06bcdf7aefb
// f063002800d066e1301c0930039007300490311d34a80160b11d4160059005482c2102aa
// 4346f3f6e3f970613888013050e10000a11211080748834200d1dde083420bdc02388342
// 00d199e00130834200d1bbe03fe10000070100000548834200d11be1834200dadee00130
// 834200d129e130e109010000f88a30727c6874630b220006002800d00022074900934046
// 0190201c0723cdf7f1fd3063b11c301c0bf768ff17e10000e0313a08c1f744f811e1307a
// 00280bd0306bcdf7d1fe3063002800d007e1014804e1000009010000306bcdf7c5fe3063
// 002800d0fbe001201e214246cdf782faf06338880130f1e0707a002800d1eee009aa301c
// 1030506004488021c9004346f3f672f9b06138880130dfe06d1611087069cdf741fe7061
// 002800d0d7e0b069cdf73afeb061002800d0d0e010aa301c103050600448cc2189004346
// f3f654f9f06138880130c1e05d1a1108f069cdf723fef061002800d0b9e017aa301c1030
// 5060044850214346f3f63ef9306238880130abe0cd201108306acdf70dfe3062002800d0
// a3e0c020f7f6a2fe011cf1600a4c201c5f222ef0a7ffc0f7f1ff211c5f222ef0a1ff0648
// 1eaa30214346f3f61bf970623888013088e000006238000361231108706acdf7e7fd7062
// 002800d07de025aab0889082f088d08204482c214346f3f601f9b062388801306ee00000
// 95251108b06acdf7cffdb062002866d12caa301c09305060044814214346f3f6ebf8f062
// 3888013058e00000612a1108707a002853d00bf77bfc33ac6d46cd35201c291c0bf72afe
// 2078f0f6f3fd134c2188014321802878f0f6ecfd2188014321800021705e0222b15e0bf7
// fffd08f749ff706b03f070f800201e214246cdf7b9f9f063f06806495f222ef035fff068
// f7f630fe3888013020e000004009000362380003f06bcdf75dfaf063002816d1f06acdf7
// 79fdf062002810d1706b0221424603f055f8b0633888013006e0b06b03f07cf8b0630028
// 01d102203880002036b008bc9846f0bc02bc0847

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
    u16 width;
    u16 height;
    u8 mode;
    u8 ready;
    u8 unknown_0A[2];
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
    u16 *width;
    u16 *height;
} Extent;

typedef struct {
    u32 unknown_00;
    void *first;
    void *second;
    Extent *extent;
    u8 unknown_10[4];
    u16 width;
    u16 height;
    u8 unknown_18[4];
} Descriptor;

typedef u32 (*TaskCallback)(void *task, void *request, void *payload);

extern const u8 data_083A31E0[];
extern u8 data_03003862[];
extern u32 func_081112A0(void *task, void *request, void *payload);
extern u32 func_0811166C(void *task, void *request, void *payload);
extern u32 func_08111A5C(void *task, void *request, void *payload);
extern u32 func_081120CC(void *task, void *request, void *payload);
extern u32 func_08112360(void *task, void *request, void *payload);
extern u32 func_08112594(void *task, void *request, void *payload);
extern u32 func_08112A60(void *task, void *request, void *payload);
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

u32 func_08112734(void *owner, Request *request, State *state)
{
    Descriptor d0;
    Descriptor d1;
    Descriptor d2;
    Descriptor d3;
    Descriptor d4;
    Descriptor d5;
    Descriptor d6;
    Extent extent;
    u32 kind;

    switch (request->phase) {
    case 0:
        state->mode = request->mode;
        state->argument = request->argument;
        kind = 11;
        if (state->mode)
            kind = 0;
        state->object = func_080E03F8(state->argument, data_083A31E0, kind, 7, 0,
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
            d0.first = &state->ready;
            d0.second = state->unknown_10;
            extent.width = &state->width;
            extent.height = &state->height;
            d0.extent = &extent;
            state->task0 = func_08005B6C(func_081112A0, 0x2C, &d0, owner);
            request->phase++;
        }
        break;
    case 0x102:
        if (state->ready) {
            d1.first = state->unknown_10;
            state->task1 = func_08005B6C(func_0811166C, 0x400, &d1, owner);
            request->phase++;
        }
        break;
    case 0x103:
        state->task0 = func_080E051C(state->task0);
        if (state->task0 == 0) {
            state->task1 = func_080E051C(state->task1);
            if (state->task1 == 0) {
                d2.first = state->unknown_10;
                state->task2 = func_08005B6C(func_08111A5C, 0x330, &d2, owner);
                request->phase++;
            }
        }
        break;
    case 0x104:
        state->task2 = func_080E051C(state->task2);
        if (state->task2 == 0) {
            d3.first = state->unknown_10;
            state->task3 = func_08005B6C(func_081120CC, 0x50, &d3, owner);
            request->phase++;
        }
        break;
    case 0x105:
        state->task3 = func_080E051C(state->task3);
        if (state->task3 == 0) {
            state->buffer = func_0800A654(0xC0);
            func_0814186C(data_03003862, state->buffer, 0x5F);
            func_0814186C(func_080D3904(), data_03003862, 0x5F);
            state->task4 = func_08005B6C(func_08112360, 0x30, &d4, owner);
            request->phase++;
        }
        break;
    case 0x106:
        state->task4 = func_080E051C(state->task4);
        if (state->task4 == 0) {
            d5.width = state->width;
            d5.height = state->height;
            state->task5 = func_08005B6C(func_08112594, 0x2C, &d5, owner);
            request->phase++;
        }
        break;
    case 0x107:
        state->task5 = func_080E051C(state->task5);
        if (state->task5 == 0) {
            d6.first = &state->ready;
            state->task6 = func_08005B6C(func_08112A60, 0x14, &d6, owner);
            request->phase++;
        }
        break;
    case 0x108:
        if (state->ready) {
            u8 first;
            u8 second;

            func_0801E2A4();
            func_0801E610(&first, &second);
            g_control_flags_03000940.display |= func_080035A8(first);
            g_control_flags_03000940.display |= func_080035A8(second);
            func_0801E5E0(state->x, state->y);
            func_0801B878();
            func_08115ACC(state->argument);
            state->fade = func_080DFD68(0, 30, owner);
            func_0814186C(state->buffer, data_03003862, 0x5F);
            func_0800A668(state->buffer);
            request->phase++;
        }
        break;
    case 0x109:
        state->fade = func_080DFED8(state->fade);
        if (state->fade == 0) {
            state->task6 = func_080E051C(state->task6);
            if (state->task6 == 0) {
                state->task7 = func_08115AE4(state->argument, 2, owner);
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
