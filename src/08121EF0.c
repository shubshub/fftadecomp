#include "ffta.h"

typedef struct {
    void *manager;
    void *allocation;
    u32 unknown_08;
    u32 unknown_0C;
    u32 saved_mode;
} State08121EF0;

typedef struct {
    u8 unknown_00[0xC];
    u8 mode;
} GlobalState;

extern State08121EF0 *data_020159CC;
extern void *data_020159C4;
extern GlobalState g_state_0200F390;
extern void func_08005B18(void *manager);
extern void func_08005C34(void *manager);
extern void func_08007170(void *owner, void *allocation);

/* Complete [0x08121EF0, 0x08121F38): 72 bytes, 25 instructions. */
void func_08121EF0(void)
{
    void *allocation;

    func_08005B18(data_020159CC->manager);
    func_08005C34(data_020159CC->manager);
    allocation = data_020159CC->allocation;
    func_08007170(data_020159C4, allocation);
    data_020159CC->allocation = 0;
    g_state_0200F390.mode = data_020159CC->saved_mode;
    func_08007170(data_020159C4, data_020159CC);
    data_020159CC = 0;
}
