#include "ffta.h"

typedef struct {
    u8 unknown_00[0x2A];
    u16 slots[5];
} SlotRecord;

u8 func_080CAE2C(void *object, u16 entry, u8 slot, u8 mode);
void func_080CAF78(void *object, u16 entry, u8 slot);

u8 func_080CB54C(void *object, u8 enabled)
{
    s32 index;
    u8 found = 0;

    for (index = 0; index < 5; index++) {
        u16 entry = ((SlotRecord *)object)->slots[index];

        if (entry != 0) {
            if ((func_080CAE2C(object, entry, index, 1) & 0x81) == 0x81) {
                if (enabled) {
                    func_080CAF78(object, 0, index);
                    index = 0;
                }
                found = 1;
            }
        }
    }
    return found;
}
