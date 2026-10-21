/* func_080DBED4 - 0x080DBED4, 118 bytes
 *
 * Builds a list of objects with func_080DCD08 and then sets or clears bit 0
 * of the u32 at +0x30 of each of them, according to the second argument:
 *
 *   flag != 0 : field_30 &= ~1
 *   flag == 0 : field_30 |= 1
 *
 * which is the same set/clear the sibling func_080DBEB4 does to a single
 * object.  The third argument names one object to leave alone: when it is
 * not null and it is the element being visited, the element is skipped.
 *
 * The function ends at the interworking return `pop {r0}; bx r0` in
 * 0x080DBF46..0x080DBF49.  The two bytes after it (0x080DBF4A, 0x0000) are
 * the alignment fill in front of the next function at 0x080DBF4C and are not
 * part of this one, so the function is 118 bytes, not the 120 the index
 * currently claims.
 *
 *   target  f0b5474680b4041c171c1d1c2406240e0906090e884660202ef7b2fb061c201c
 *           311c2a1c00f006ff0006040e0023a34219d29900002f03d088190068b8420dd0
 *           881902684046002804d0106b02214942084002e0106b012108431063581c0006
 *           030ea342e5d330c2ef794fb08bc9846f0bc01bc0047
 */

#include "ffta.h"

typedef struct {
    u8 unknown_00[0x30];
    u32 field_30;
} Struct080DBED4;

extern void *func_0800A654(u32 size);
extern void func_0800A668(void *ptr);
extern u32 func_080DCD08(u8 selector, void *list, void *arg);

void func_080DBED4(u8 selector, u8 flag, Struct080DBED4 *skip, void *arg) {
    Struct080DBED4 **list = func_0800A654(0x60);
    u8 count = func_080DCD08(selector, list, arg);
    Struct080DBED4 *elem;
    u8 i;

    for (i = 0; i < count; i++) {
        if (skip != 0 && list[i] == skip)
            continue;
        elem = list[i];
        if (flag) {
            elem->field_30 &= ~1;
        } else {
            elem->field_30 |= 1;
        }
    }
    func_0800A668(list);
}
