/* 0x08017B68 - 52 bytes (the index span of 20 is truncated; the function runs
 * to the epilogue at 0x08017B9C).
 *
 * Clamps index + position into [0, count - 1] and returns the result.
 * Same body as the sibling at 0x08017B9C, which continues into a call.
 */
#include "item_quantity_menu.h"

u16 func_08017B68(MenuList *state, s8 index) {
    s16 value = index + state->position;

    if (value < 0) {
        return 0;
    } else if (value > (s16)state->count - 1) {
        return state->count - 1;
    } else {
        return value;
    }
}