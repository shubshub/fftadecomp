#include "item_quantity_menu.h"

extern u16 data_03000000;
extern void func_08017FBC(void *, u32);
extern void func_0802B07C(MenuList *, u16);
extern void func_0805C09C(void);
extern void func_0802B108(MenuList *);
extern void func_08017E28(MenuCursor *);

/* Complete target [0x0805C10C, 0x0805C220): 276 bytes, 111 instructions. */
void func_0805C10C(void)
{
    MenuControls *controls = &data_0200F428->controls;
    u8 row = controls->row;
    u16 up = data_03000000 & 0x40;
    u8 selected;

    if (up) {
        row--;
        func_08017FBC(&data_0200F428->cursor, 0x40);
        selected = func_08017B68(&data_0200F428->list, (s8)row);
        func_0802B07C(&data_0200F428->list, 0x40);
        func_0805C220(&data_0200F428->list,
                      data_0200F428->entries[selected].identifier,
                      data_0200F428->entries[selected].quantity, 0, 0);
        func_0805C09C();
        func_0802B108(&data_0200F428->list);
        func_08017E28(&data_0200F428->cursor);
    } else if (data_03000000 & 0x80) {
        row++;
        func_08017FBC(&data_0200F428->cursor, 0x80);
        selected = func_08017B68(&data_0200F428->list, (s8)row);
        func_0802B07C(&data_0200F428->list, 0x80);
        func_0805C220(&data_0200F428->list,
                      data_0200F428->entries[selected].identifier,
                      data_0200F428->entries[selected].quantity, 3, 0);
        func_0805C09C();
        func_0802B108(&data_0200F428->list);
        func_08017E28(&data_0200F428->cursor);
    }
}
