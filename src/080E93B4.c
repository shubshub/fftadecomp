#include "ffta.h"

/* Target 0x080E93B4..0x080E9554 (416 bytes):
 * f0b5474680b484b0071c8846151c0b88012b23d0012b02dc002b09d0b6e08020400083421dd00130834200d186e0ade04146c88aa8704c682c6305220006002800d00022044900930197201c0123f6f7f9ffe8629ae00000fc843908eaf750fa94e0e86af7f7e0f8061cee62002e00d08ce0286b0021eff715fa0006002800d181e0286b0021f4f733f8041c291daa1d0023f4f77ff9a860224804216b5e0622a95e0091019600210222edf7dffe0421685e0622a95e042200922a1c0c320192194a0292039700220123ecf70bfee8611648391cebf73cf928621548391c2422ebf746f968621348391ceaf7fdfca86202200090019778200290201c00210c220023f3f795fd68630b480097022104220023f6f761fca863414608880130088034e00000804f8f08388539082c93940890ac9408a8d6940898853908a86aeaf709fda862002821d1286aebf739f9286200281bd1686aebf733f96862002815d102201af747f80d4a118881431180e869ecf706fee861002808d1686bf2f794fa6863002802d1022042461080002004b008bc9846f0bc02bc0847000040090003
 */

typedef struct StagedDescriptor {
    u16 phase;
    u8 unknown_02[2];
    void *wrapper;
    u8 unknown_08[14];
    u16 selector;
} StagedDescriptor;

typedef struct StagedState {
    u8 unknown_00[2];
    u8 selector;
    u8 unknown_03;
    s16 x;
    s16 y;
    void *underlying;
    u8 unknown_0C[16];
    void *coordinate_child;
    void *first_child;
    void *second_child;
    void *sequence_child;
    void *setup_child;
    void *wrapper;
    void *wrapper_child;
    void *record_child;
} StagedState;

extern u32 func_080035A8(u8 index);
extern void func_080D38B4(void);
extern void *func_080D3E9C(const void *data, void *parent);
extern void *func_080D3F08(void *object);
extern void *func_080D4704(const void *data, void *parent);
extern void *func_080D4724(const void *data, void *parent, u16 value);
extern void *func_080D4774(void *object);
extern void *func_080D6098(s16 x, s16 y, s16 z, u8 mode, u16 count,
                           void *storage, const void *data, void *parent);
extern void *func_080D6134(void *object);
extern void func_080D7220(const void *data, u8 bank, u8 layer,
                          s16 x, s16 y, u16 flags);
extern u32 func_080D8858(void *wrapper, u16 flags);
extern void *func_080DBA5C(void *object);
extern void *func_080DCFE4(void *wrapper, const void *data, u8 mode,
                           u16 first, u16 second, void *parent, s16 fallback);
extern void *func_080DD4A4(void *wrapper, u8 index);
extern void *func_080DD748(void *wrapper, s16 *x, s16 *y, s16 *z);
extern void *func_080DFD8C(const void *data, u8 count, u16 flags,
                           u16 delay, void *parent);
extern void *func_080E03F8(void *wrapper, const void *data, u8 count,
                           u8 selector, const s16 *coordinates, void *parent);
extern void *func_080E05DC(void *object);

u32 func_080E93B4(void *task, void *descriptor, void *payload)
{
    StagedDescriptor *control = descriptor;
    StagedState *state = payload;
    void *selected_wrapper;
    u32 mask;
    u8 count;

    switch (control->phase) {
    case 0:
        state->selector = control->selector;
        state->wrapper = control->wrapper;
        count = 5;
        if (state->selector != 0)
            count = 0;
        state->setup_child = func_080E03F8(state->wrapper,
            (const void *)0x083984FC, count, 1, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        state->setup_child = func_080E05DC(state->setup_child);
        if (state->setup_child != 0)
            break;
        if ((u8)func_080D8858(state->wrapper, 0) == 0) {
            control->phase = 2;
            break;
        }
        selected_wrapper = func_080DD4A4(state->wrapper, 0);
        state->underlying = func_080DD748(selected_wrapper,
            &state->x, &state->y, 0);
        func_080D7220((const void *)0x088F4F80, 0, 2,
            state->x, state->y, 0);
        state->coordinate_child = func_080D6098(state->x, state->y,
            0, 1, 4, state->unknown_0C, (const void *)0x08398538, task);
        state->first_child = func_080D4704((const void *)0x0894932C, task);
        state->second_child = func_080D4724((const void *)0x0894AC90, task, 36);
        state->sequence_child = func_080D3E9C((const void *)0x0894D6A8, task);
        state->wrapper_child = func_080DCFE4(selected_wrapper, 0,
            12, 0, 2, task, 120);
        state->record_child = func_080DFD8C((const void *)0x08398598,
            2, 4, 0, task);
        control->phase++;
        break;
    case 0x101:
        state->sequence_child = func_080D3F08(state->sequence_child);
        if (state->sequence_child != 0)
            break;
        state->first_child = func_080D4774(state->first_child);
        if (state->first_child != 0)
            break;
        state->second_child = func_080D4774(state->second_child);
        if (state->second_child != 0)
            break;
        mask = func_080035A8(2);
        *(u16 *)0x03000940 &= ~mask;
        state->coordinate_child = func_080D6134(state->coordinate_child);
        if (state->coordinate_child != 0)
            break;
        state->wrapper_child = func_080DBA5C(state->wrapper_child);
        if (state->wrapper_child == 0)
            control->phase = 2;
        break;
    }
    return 0;
}
