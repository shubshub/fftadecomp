#include "ffta.h"

/* Complete target [0x08081FB0, 0x08082254): 676 bytes, 266 instructions.
 * f0b557464e464546e0b48db00c900b4882460368cc200c9f4743da19084950180078062800d1afe0
 * 06280fdc022853d0022807dc002813d0fbe0000018280003ba2c0000032800d192e0f2e0082800d1
 * b6e0082800daa3e0092800d1d5e0e8e008901749174a08a8bff026fc52461068154c0119c919154d
 * 4019c0190468096800222068824210daa5696368900080188000401900898000c018006801c1501c
 * 0004020c20688242f0db09480068cc210c9e71434018074940180221b8e0000020c5000620070001
 * 4c2d0000d02c000018280003ba2c00001e4c1819c0191e4dad18a946006809a90c3070c870c11b4e
 * 901906880120804619495818c0190168184a9818c019026809ad2b7868780090a8780190e8780290
 * 28890390124c4c207043001928300078049005200590444606940c200790484695f79cf9a97a4846
 * 94f7cefd55462868c019084e801903216ee00000d02c0000d42c0000b82c00009c2c0000b42c0000
 * e0090003ba2c00000c98fff763fd51460868c019014a8018062155e0ba2c00000c98fff757fe5446
 * 2168c919014d491908704ae0ba2c0000f818054e801995f767fe51460868c019024a801806213be0
 * 342d0000ba2c00002f4c1119ff2008702e4d7c195646306800194c30102195f7bff9306800199830
 * 002195f7c1fd30680019ac30002195f7bbfd3068c01924494018002101703068c019224a80180921
 * 0170214dcc200c9e341c4443286820181e49401894f7d8ff0006002805d028680019184a8018ff21
 * 0170174ca0462468cc200c9d2e1c4643a419154960180588144aa118281c0122fff772f812482418
 * 281c211c0122fff76bf8414608688019084a801800780db038bc9846a146aa46f0bc02bc08470000
 * be2c0000882c0000c22c0000ba2c000018280003d42c0000b82c0000202d0000342d0000
 */

typedef struct {
    u32 field_00;
    u32 field_04;
    u32 field_08;
    u32 field_0C;
    u8 field_10;
    u8 field_11;
    u8 field_12;
    u8 field_13;
    u16 field_14;
    u8 field_16;
    u8 field_17;
    u16 field_18;
    u16 field_1A;
    u8 field_1C;
    u8 field_1D;
    u8 field_1E;
    u8 field_1F;
    u16 field_20;
    u16 field_22;
    u16 field_24;
    u16 field_26;
    u16 field_28;
    u16 field_2A;
} State08017424;

typedef struct {
    u8 x;
    u8 y;
    u8 width;
    u8 height;
    u32 unknown_04;
    u16 flags;
    u8 mode;
    u8 unknown_0B;
} Descriptor08081FB0;

typedef struct {
    u8 unknown_00[8];
    u16 value_index;
    u8 unknown_0A[0xA];
} Entry08081FB0;

typedef struct {
    s32 count;
    u32 *values;
    u8 unknown_08[4];
    Descriptor08081FB0 descriptor;
    Entry08081FB0 *entries;
} Configuration08081FB0;

typedef struct {
    State08017424 window;
    u8 list[0x20];
    u8 cursor[0x14];
    u8 settings[0x14];
} Menu08081FB0;

typedef struct {
    u8 unknown_00[0x14];
    u32 field_14;
    u8 unknown_18[0x14];
    u32 field_2C;
    u16 field_30;
    u8 phase;
    u8 unknown_33[3];
    u8 selection;
    u8 unknown_37[3];
    u8 field_3A;
    u8 unknown_3B[0xD];
    Configuration08081FB0 *configuration;
    Menu08081FB0 menu;
    const void *resource;
    u32 *values;
    u8 unknown_C8[4];
} Record08081FB0;

typedef struct {
    u8 unknown_00[0x2C88];
    Record08081FB0 records[0];
} Root08081FB0;

typedef struct {
    u8 unknown_00[0x28];
    u8 field_28;
    u8 unknown_29[0x23];
} Resource08081FB0;

extern Root08081FB0 *data_03002818;
extern Resource08081FB0 data_030009E0[];
extern u8 data_0600C520[];
extern void func_08141868(const void *source, void *destination, u32 control);
extern void func_08017424(State08017424 *state, u32 value_00, u32 value_04,
                         u8 value_10, u8 value_11, u8 value_12, u8 value_13,
                         u16 value_14, u8 value_16, u16 value_18,
                         u16 value_1A, u8 value_17);
extern void func_08016C90(State08017424 *state, u8 mode);
extern void func_08081BEC(s32 index);
extern u8 func_08081DEC(s32 index);
extern void func_08017E28(void *settings);
extern void func_08017508(State08017424 *window, u8 appearance);
extern void func_08017D18(void *control, u8 flags);
extern u8 func_08017180(State08017424 *window);
extern void func_080812E8(u32 context, void *control, s32 enabled);

/* The SDK's CpuFastFill (pret include/gba/macro.h), as src/0801A15C.c
 * writes it: func_08141868 is CpuFastSet and 0x01000000 is
 * CPU_FAST_SET_SRC_FIXED. */
#define CpuFastFill(value, dest, size)                                    \
{                                                                         \
    volatile u32 tmp = (volatile u32)(value);                             \
    func_08141868((void *)&tmp, (dest),                                   \
        0x01000000 | ((size) / (32 / 8) & 0x1FFFFF));                     \
}

/* An inlined copy of func_080853A0 (src/080853A0.c). */
static inline void inlined_080853A0(u32 index, State08017424 *state,
                                    const Configuration08081FB0 *configuration,
                                    u8 x, u8 y)
{
    Descriptor08081FB0 descriptor = configuration->descriptor;
    u16 selection = data_03002818->records[index].field_30;
    u16 enabled;

    if (x != 0xFF) {
        descriptor.x = x;
        descriptor.y = y;
    }
    enabled = 1;
    func_08017424(state, data_03002818->records[index].field_14,
                 data_03002818->records[index].field_2C,
                 descriptor.x, descriptor.y, descriptor.width, descriptor.height,
                 descriptor.flags, data_030009E0[selection].field_28, 5, enabled, 12);
    func_08016C90(state, descriptor.mode);
}

/* An inlined copy of func_0808537C (src/0808537C.c). */
static inline void inlined_0808537C(u32 context, Menu08081FB0 *object,
                                    s32 enabled)
{
    func_080812E8(context, object->cursor, enabled);
    if (enabled)
        func_080812E8(context, object->settings, enabled);
}

/* An inlined copy of func_08085450 (src/08085450.c). */
static inline void inlined_08085450(void *unused, u32 *output,
                                    Configuration08081FB0 *list)
{
    u16 i;

    for (i = 0; i < list->count; i++)
        *output++ = list->values[list->entries[i].value_index];
}

u8 func_08081FB0(s32 index)
{
    switch (data_03002818->records[index].phase) {
    case 0: {
        u32 *values;
        Configuration08081FB0 *configuration;

        /* 0x720 words at 0x0600C520 from one stacked word: str at
         * 0x08082010, its slot at sp+0x20 below the inlined descriptor copy
         * (0x08082096). */
        CpuFastFill(0, data_0600C520, 0x1C80);
        values = data_03002818->records[index].values;
        configuration = data_03002818->records[index].configuration;
        inlined_08085450(0, values, configuration);
        data_03002818->records[index].phase = 2;
        break;
    }
    case 2:
        inlined_080853A0(index, &data_03002818->records[index].menu.window,
                         data_03002818->records[index].configuration, 0xFF, 0xFF);
        data_03002818->records[index].phase = 3;
        break;
    case 3:
        func_08081BEC(index);
        data_03002818->records[index].phase = 6;
        break;
    case 6:
        data_03002818->records[index].phase = func_08081DEC(index);
        break;
    case 7:
        func_08017E28(data_03002818->records[index].menu.settings);
        data_03002818->records[index].phase = 6;
        break;
    case 8:
        data_03002818->records[index].selection = 0xFF;
        func_08017508(&data_03002818->records[index].menu.window, 0x10);
        func_08017D18(data_03002818->records[index].menu.cursor, 0);
        func_08017D18(data_03002818->records[index].menu.settings, 0);
        data_03002818->records[index].field_3A = 0;
        data_03002818->records[index].phase = 9;
    case 9:
        if (func_08017180(&data_03002818->records[index].menu.window))
            data_03002818->records[index].phase = 0xFF;
        break;
    case 0xFF:
        break;
    }
    inlined_0808537C(data_03002818->records[index].field_30,
                     &data_03002818->records[index].menu, 1);
    return data_03002818->records[index].phase;
}
