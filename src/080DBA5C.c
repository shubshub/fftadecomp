/* func_080DBA5C - 0x080DBA5C, 44 bytes
 *
 * Drops an object that is in state 2.  If the object is not null and its
 * state says 2, the update runs and the object is dropped - null comes back.
 * Any other object is handed back untouched.  Every caller loads a pointer,
 * calls this, stores the result back and compares it with zero.
 *
 * The state test and the update are separate functions in the ROM, right
 * before this one: 0x080DBA3C is `if (func_08005BB0(x)) return 1; return 0;`
 * and 0x080DBA50 is a wrapper around func_08005B58.  agbcc inlined both of
 * them here, and the inlined test is what puts the `movs r0, #1` /
 * `movs r0, #0` pair in the middle of this function: the helper answers 1 or
 * 0, so the answer has to be materialised before the caller can test it.
 * The wrapper around func_08005B58 leaves no trace of its own, so it is only
 * there to keep the shape of the original source.
 *
 *   target  10b5041c002c0dd02af7a4f8002801d0012000e0020002804d0201c
 *           2af76ef8002000e0201c10bc02bc0847
 */

#include "ffta.h"

/* Answers 1 when the object's state field says 2. */
extern u32 func_08005BB0(const void *object);
/* Applies the state change to the object. */
extern void func_08005B58(void *object);

/* The ROM's 0x080DBA3C. */
static inline u8 object_is_state_2(const void *object)
{
    if (func_08005BB0(object))
        return 1;
    return 0;
}

/* The ROM's 0x080DBA50. */
static inline void object_apply_update(void *object)
{
    func_08005B58(object);
}

void *func_080DBA5C(void *object)
{
    if (object != 0) {
        if (object_is_state_2(object)) {
            object_apply_update(object);
            return 0;
        }
    }
    return object;
}
