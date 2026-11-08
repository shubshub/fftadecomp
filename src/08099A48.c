#include "ffta.h"

/* Complete [0x08099A48, 0x08099A70): 40 bytes.
 * 00b582b0011c80310a68054900900191106904496a462ef02ff902b001bc00476dad0908e9ab0908 */
typedef struct ListNode08099A48 ListNode08099A48;
typedef struct ListContext08099A48 ListContext08099A48;
typedef struct Object08099A48 Object08099A48;

typedef struct {
    u8 unknown_00[0x10];
    ListContext08099A48 *context;
} Owner08099A48;

typedef struct {
    u8 unknown_00[0x80];
    Owner08099A48 *owner;
} Holder08099A48;

typedef u32 (*ObjectCallback08099A48)(Object08099A48 *object,
                                      const Holder08099A48 *excluded);

typedef struct {
    const Holder08099A48 *argument;
    ObjectCallback08099A48 callback;
} Closure08099A48;

extern u32 func_0809ABE8(ListNode08099A48 *node, void *closure);
extern u32 func_0809AD6C(Object08099A48 *object, const Holder08099A48 *excluded);
extern void func_080C7CC0(ListContext08099A48 *context,
                          u32 (*callback)(ListNode08099A48 *, void *),
                          Closure08099A48 *closure);

void func_08099A48(Holder08099A48 *holder)
{
    Owner08099A48 *owner = holder->owner;
    Closure08099A48 closure;
    ObjectCallback08099A48 callback = func_0809AD6C;

    closure.argument = holder;
    closure.callback = callback;
    func_080C7CC0(owner->context, func_0809ABE8, &closure);
}
