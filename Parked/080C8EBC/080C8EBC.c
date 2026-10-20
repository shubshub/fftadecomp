#include "ffta.h"

typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
} FlaggedObject;

u8 func_080C8240(void *object);
u8 func_080C8260(const FlaggedObject *object);
u8 func_080C8194(const void *object, u8 category);
s32 func_080C7EA4(const void *object, u32 selector);
u8 func_080C94D0(u8 category, u16 value);
u32 func_080C8570(u8 first, u8 second, u8 selector);
u8 func_080C8228(const void *object);
u8 func_080C9540(u16 bitIndex);

u8 func_080C8EBC(u8 *object, u8 *output)
{
    u8 *cursor = output;

    if (func_080C8240(object) || func_080C8260((const FlaggedObject *)object) ||
        func_080C8194(object, 0x0A) || func_080C8194(object, 9) ||
        func_080C8194(object, 0x5E)) {
        u8 category = func_080C7EA4(object, 3);
        s32 index;

        if (!func_080C8260((const FlaggedObject *)object) && !func_080C8240(object) &&
            (func_080C8194(object, 0x0A) || func_080C8194(object, 9) ||
             func_080C8194(object, 0x5E)))
            *cursor++ = 1;
        for (index = 1; index < object[0x34]; index++) {
            if ((object + 0x40)[index] != 0) {
                u8 entry = func_080C94D0(category, index);
                u8 value = func_080C8570(entry, entry, 0x0C);

                if (value != 0) {
                    u32 scan;
                    s32 unique = 1;

                    for (scan = 0; scan < (u32)(cursor - output); scan++) {
                        if (output[scan] == value) {
                            unique = 0;
                            break;
                        }
                    }
                    if (unique == 1) {
                        *cursor++ = value;
                    }
                }
            }
        }
    } else {
        s32 index = 5;
        s32 limit = 15;
        s32 entry;

        switch ((u32)func_080C7EA4(object, 3)) {
        case 2:
            index = 16;
            limit = 22;
            break;
        case 3:
            index = 23;
            limit = 30;
            break;
        case 4:
            index = 31;
            limit = 38;
            break;
        case 5:
            index = 39;
            limit = 46;
            break;
        }
        if (!func_080C8228(object))
            *cursor++ = 1;
        for (entry = index - 3; index <= limit; index++, entry++) {
            if (func_080C9540(index))
                *cursor++ = func_080C8570(entry, entry, 0x0C);
        }
    }
    return cursor - output;
}
