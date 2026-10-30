#include "ffta.h"

typedef struct {
    u8 *unit;
    u8 unknown_04[0x7C];
    u8 *collection;
} SearchContext;

extern u8 data_030028A0;
extern u8 func_080C95A8(u16 index);
extern s32 func_0809AA10(SearchContext *context);
extern u8 func_08133BC4(void *unit);
extern SearchContext *func_080970E8(void *collection, void *unit);

/* Complete target: [0x080C1920, 0x080C1980), 96 bytes. */
s32 func_080C1920(SearchContext *owner)
{
    SearchContext *related;

    if (func_080C95A8(13) && !(u8)func_0809AA10(owner)) {
        if (func_08133BC4(owner->unit)) {
            return 1;
        } else {
            related = func_080970E8(owner->collection, owner->unit);
            if (related != 0) {
                if (!(u8)func_0809AA10(related))
                    return 1;
            } else if (data_030028A0 & 8) {
                return 1;
            }
        }
    }
    return 0;
}
