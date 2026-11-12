#include "ffta.h"

/* 0x0804E128..0x0804E1B8: 144 bytes including literal pools. */
typedef u32 (*TaskCallback)(void *, void *, void *);
struct MenuContext0804E128 {
    u8 unknown_00[8];
    void *manager;
};
struct Descriptor0804E128 {
    u8 unknown_00[20];
    u16 selection;
    u8 unknown_16[6];
};
extern struct MenuContext0804E128 *data_0201F548;
extern u32 func_0804E6EC(void *, void *, void *);
extern u32 func_0804E5CC(void *, void *, void *);
extern u32 func_0804E858(void *, void *, void *);
extern u32 func_0804E408(void *, void *, void *);
extern void *func_08005954(void *, TaskCallback, u16, void *, void *);

void *func_0804E128(u8 selection)
{
    struct Descriptor0804E128 descriptor;
    descriptor.selection = selection;
    switch (selection) {
    case 10:
        return func_08005954(data_0201F548->manager, func_0804E6EC, 20, &descriptor, 0);
    case 11:
        return func_08005954(data_0201F548->manager, func_0804E5CC, 48, &descriptor, 0);
    case 8:
        return func_08005954(data_0201F548->manager, func_0804E858, 204, &descriptor, 0);
    default:
        return func_08005954(data_0201F548->manager, func_0804E408, 152, &descriptor, 0);
    }
}
