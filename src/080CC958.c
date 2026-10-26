#include "ffta.h"

typedef struct {
    u32 mask;
} __attribute__((packed)) CategoryMask;

extern const CategoryMask *func_080CCCF0(u8 category);
extern u32 func_080CA7A4(u16 item, u32 field);

u8 func_080CC958(u8 category, u16 item)
{
    const CategoryMask *mask = func_080CCCF0(category);

    if (mask) {
        u32 type = func_080CA7A4(item, 3);

        if (mask->mask & (1u << (type - 1)))
            return 1;
    }
    return 0;
}
