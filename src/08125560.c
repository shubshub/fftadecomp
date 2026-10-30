#include "ffta.h"

typedef struct {
    void *resource;
} Object080247FC;

extern Object080247FC data_0200F3AC;
extern void func_080247FC(Object080247FC *object);
extern void func_08096CB8(void);
extern void func_08022DD0(void);

/* 08125560..08125578: 00 B5 04 48 FF F6 4A F9 71 F7 A6 FB FD F6 30 FC 01 BC 00 47 AC F3 00 02. */
void func_08125560(void)
{
    func_080247FC(&data_0200F3AC);
    func_08096CB8();
    func_08022DD0();
}
