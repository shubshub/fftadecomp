#include "ffta.h"

typedef struct ListNode080213DC ListNode080213DC;
typedef struct ListContext080213DC ListContext080213DC;

typedef struct {
    u8 unknown_00[8];
    ListContext080213DC *list;
} Owner080213DC;

typedef struct {
    u16 start;
    u16 end;
    u16 width;
    u16 flags;
} Range080213DC;

extern void func_080C79E0(ListContext080213DC *list);
extern s32 func_080C7B08(ListContext080213DC *list);
extern void func_080C7CC0(ListContext080213DC *list,
                          u32 (*callback)(ListNode080213DC *, void *),
                          void *payload);
extern void func_080C7D18(ListContext080213DC *list,
                          u32 (*callback)(ListNode080213DC *, void *),
                          void *payload);
extern u32 func_080220E8(ListNode080213DC *node, void *payload);
extern u32 func_08021378(ListNode080213DC *node, void *payload);

// Complete target: [0x080213DC, 0x08021482), 166 bytes.
s32 func_080213DC(Owner080213DC *owner, s32 width, s32 start, s32 limit)
{
    Range080213DC range;

    func_080C79E0(owner->list);
    if (func_080C7B08(owner->list) <= 0) {
        if (start + width >= limit)
            return -1;
        return start;
    }
    func_080C7CC0(owner->list, func_080220E8, owner->list);
    range.start = start;
    range.end = limit;
    range.width = width;
    range.flags = 0;
    func_080C7D18(owner->list, func_08021378, &range);
    if ((range.flags & 2) || range.end < range.start + range.width) {
        func_080C79E0(owner->list);
        return -1;
    }
    func_080C79E0(owner->list);
    return range.start;
}
