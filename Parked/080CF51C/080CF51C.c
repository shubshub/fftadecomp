#include "080CF51C.h"

extern const u8 g_table_0855AE4C[][70];

u16 func_080CE8A8(void);
u32 func_080CED2C(void);
u8 func_080C9540(u16 bitIndex);
void func_080C9574(u16 bitIndex, u16 enabled);
u32 func_080CF060(const void *record);
void func_080CF118(u8 *data, u8 enabled);

void func_080CF51C(void)
{
    Node **head;
    Node *node;

    if (func_080CE8A8() == (u16)func_080CED2C() && !func_080C9540(0x5AE))
        func_080C9574(0x5AE, 1);
    if (func_080C9540(0x258) && func_080C9540(0x48C))
        func_080C9574(0x48C, 1);

    head = (Node **)(g_state_02000000 + 0x28C8);
    node = *head;
    while (node != 0) {
        u8 *data = node->record;
        const u8 *definition = g_table_0855AE4C[data[0] | ((data[1] & 3) << 8)];

        if (data[3] != 0xFF && data[3] != 0)
            data[3]--;
        if (data[3] == 0) {
            switch ((data[2] >> 2) & 7) {
            case 0:
                if (!func_080CF060(data))
                    func_080CF118(data, 0);
            case 1:
            case 2:
                if (definition[0x40] != 0) {
                    data[2] = (data[2] & ~0x1C) | 0x0C;
                    data[3] = definition[0x40];
                } else
                    remove_record(data, head);
                break;
            case 3:
                remove_record(data, head);
                break;
            }
        }
        node = node->next;
    }
}
