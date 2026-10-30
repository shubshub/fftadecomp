#include "ffta.h"

typedef struct ListObject080A929C ListObject080A929C;
typedef struct ListContext080A929C ListContext080A929C;

typedef struct {
    void *owner;
    u32 unknown_04;
    ListObject080A929C *object;
    void *element;
    u8 unknown_10[0x3C];
    u8 *allocation;
    ListContext080A929C *context;
    u8 unknown_54[0x588];
    u8 value;
} State080A929C;

extern State080A929C data_0200F9E8;
extern void func_08007170(void *owner, u8 *object);
extern void func_08021BD4(ListObject080A929C *object, void *element);
extern void func_08021B54(ListObject080A929C *object);
extern void func_080C79B4(ListContext080A929C *context);
extern void func_080C79E0(ListContext080A929C *context);
extern void *func_080C7908(ListContext080A929C *context);
extern void func_0802D714(void);

/* 0x080A929C..0x080A92E4:
 * 10 B5 0F 4C 20 68 E1 6C 5D F7 64 FF 00 21 E1 64
 * 0C 4A A0 18 01 70 A0 68 E1 68 78 F7 8D FC A0 68
 * 78 F7 4A FC 20 6D 1E F0 77 FB 20 6D 1E F0 8A FB
 * 20 6D 1E F0 1B FB 84 F7 1F FA 10 BC 01 BC 00 47
 * E8 F9 00 02 DC 05 00 00. */
void func_080A929C(void)
{
    State080A929C *state = &data_0200F9E8;

    func_08007170(state->owner, state->allocation);
    state->allocation = 0;
    state->value = 0;
    func_08021BD4(state->object, state->element);
    func_08021B54(state->object);
    func_080C79B4(state->context);
    func_080C79E0(state->context);
    func_080C7908(state->context);
    func_0802D714();
}
