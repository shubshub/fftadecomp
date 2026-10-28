#include "ffta.h"

typedef struct Transition0804C888 {
    u8 state;
} Transition0804C888;

extern void func_0804C8C4(void);
extern void func_0804C97C(void);
extern u32 func_0804C9E4(void);

/* Complete [0x0804C888, 0x0804C8C4): 60 bytes, 27 instructions. */
void func_0804C888(void *task, Transition0804C888 *transition)
{
    switch (transition->state) {
    case 0:
        func_0804C8C4();
        transition->state = 1;
        break;
    case 2:
        func_0804C97C();
        transition->state = 3;
        break;
    case 1:
        if (func_0804C9E4())
            transition->state = 2;
        break;
    }
}
