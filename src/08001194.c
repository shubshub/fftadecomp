// func_08001194: 0x08001194-0x08001244, 176 bytes, 65 instructions
// (including the ten-word literal pool at 0x0800121C).
#include "oam_lists.h"

void func_08001194(void)
{
    BufferInitializer const *callbacks = g_callbacks_0836D4B8;

    func_0814224C(data_03003270[data_03000028], 0x20, callbacks[0]);
    func_0814224C(data_030032B0[data_03000028], 0x100, callbacks[0]);

    HideEntries(data_03002C58[data_03000028], data_03002C50[data_03000028]);
    HideEntries(data_03000030[data_03000028], data_03000020[data_03000028]);

    data_03002C50[data_03000028] = data_03000020[data_03000028] = 0;
}
