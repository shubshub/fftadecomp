#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    s16 frame;
    u8 unknown_0a[4];
    s16 ticks;
} Label08068864;

typedef struct {
    u8 unknown_00[0xd];
    u8 active;
    u8 unknown_0e[0x16];
    u8 renderer[0x2c];
    u8 unknown_50[0x6c];
    Label08068864 first_label;
    Label08068864 second_label;
} Object08068864;

extern void func_08016234(void *);
extern void func_08068548(Object08068864 *);
extern void func_08017FE8(Label08068864 *);

/* 0x08068864..0x080688D0: 108 bytes, 50 instructions. */
void func_08068864(Object08068864 *object)
{
    func_08016234(object->renderer);
    if (object->active) {
        func_08068548(object);
        if (++object->first_label.ticks > 5) {
            object->first_label.ticks = 0;
            if (++object->first_label.frame > 2)
                object->first_label.frame = 0;
            if (--object->second_label.frame <= -3)
                object->second_label.frame = 0;
        }
        func_08017FE8(&object->first_label);
        func_08017FE8(&object->second_label);
    }
}
