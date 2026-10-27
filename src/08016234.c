#include "ffta.h"

/* 0x08016234..0x0801624C: 24 bytes. */
extern void func_08017C68(void *object);

void func_08016234(u8 *state)
{
    func_08017C68(state + 0x4C);
    func_08017C68(state + 0x60);
}
