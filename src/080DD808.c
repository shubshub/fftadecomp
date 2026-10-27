#include "ffta.h"

typedef struct ChildPair080DD808 {
    u8 unknown_00[0x54];
    void *first;
    void *second;
} ChildPair080DD808;

typedef void (*ChildCallback080DD808)(void *child, u8 value, u32 first,
                                     u32 second, u32 third, u32 fourth);

extern ChildCallback080DD808 const data_08394034[];
extern void *func_0800A654(u32 size);
extern void func_0800A668(void *pointer);
extern u32 func_080DCD08(u8 selector, void *list, void *argument);

/* Complete [0x080DD808, 0x080DD8C4): 188 bytes, 86 instructions. */
void func_080DD808(u8 selector, u8 value, u8 include_second,
                   ChildPair080DD808 *skip, void *argument)
{
    ChildPair080DD808 **list = func_0800A654(0x60);
    u8 count = func_080DCD08(selector, list, argument);
    u8 index;

    for (index = 0; index < count; index++) {
        ChildPair080DD808 *object;
        void *first;
        void *second;

        if (skip != 0 && list[index] == skip)
            continue;
        object = list[index];
        first = object->first;
        second = object->second;
        if (first != 0)
            data_08394034[0](first, value, 0, 0, 0, 0);
        if (include_second != 0 && second != 0)
            data_08394034[0](second, value, 0, 0, 0, 0);
    }
    func_0800A668(list);
}
