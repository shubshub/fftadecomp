#include "ffta.h"

/* 0x080267EC..0x08026838: 76 bytes. */
typedef struct {
    u8 unknown_00[0x2A];
    u16 items[5];
} Equipment;

extern u16 func_080CA7A4(u16 item, u8 field);

u8 func_080267EC(const Equipment *equipment, u8 mode)
{
    s32 index;

    for (index = 0; index < 5; index++) {
        u16 item = equipment->items[index];

        if (item != 0) {
            u16 category = func_080CA7A4(item, 3);

            switch (mode) {
            case 2:
                if (category == 15)
                    return 1;
                break;
            case 3:
                if (category == 13 || category == 14)
                    return 1;
                break;
            }
        }
    }
    return 0;
}
