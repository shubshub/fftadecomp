#include "ffta.h"

/* Installed VBlank callback. Complete Thumb body [080004B0, 0800052C). */
typedef struct {
    u16 value : 16;
} RunnerState;

extern RunnerState data_03000E10;
extern u16 data_03000EB4;

extern void func_08144AF0(void);
extern void func_080006D0(void);
extern void func_08000D08(void);
extern void func_080007C8(void);
extern void func_08000438(void);
extern void func_08000718(void);
extern void func_08147A44(void);
extern void func_080012BC(void);
extern void func_080008E0(void);
extern void func_0800216C(void);
extern void func_0813BBB8(void);
extern void func_08000788(void);
extern void func_081451B4(void);
extern void func_08147288(void);

void func_080004B0(void)
{
    func_08144AF0();
    func_080006D0();
    func_08000D08();
    func_080007C8();
    func_08000438();
    if (data_03000E10.value == 0) {
        func_08000718();
        func_08147A44();
    }
    func_080012BC();
    func_080008E0();
    func_0800216C();
    data_03000EB4++;
    func_0813BBB8();
    func_08000788();
    func_081451B4();
    if (data_03000E10.value == 0)
        func_08147288();
    data_03000E10.value = 1;
}
