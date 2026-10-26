#include "ffta.h"

/* 0x080A11DC..0x080A12FC: 288 bytes. */
typedef struct {
    u32 unit;
} UnitOwner;

typedef struct {
    u32 first;
    u32 second;
} WorkRecord;

typedef struct {
    u32 operation;
    UnitOwner *source;
    UnitOwner *candidates[2];
    WorkRecord records[2];
    s32 results[10];
    s16 count;
    s16 index;
    s16 ticks;
    s16 choice;
} SelectionWork;

s32 func_080A0DEC(SelectionWork *work, u32 operation, s32 index, u32 value,
                  UnitOwner **candidate, WorkRecord *record, u32 flags);
u8 func_080C8240(u32 unit);
u16 func_08002804(void);

u32 func_080A11DC(SelectionWork *work, u32 value)
{
    s32 result;
    s32 choice;
    UnitOwner *first;
    UnitOwner *second;

    result = func_080A0DEC(work, work->operation, work->index, value,
                           &work->candidates[work->index],
                           &work->records[work->index], 0);
    if (result < 0)
        return 1;

    work->ticks = 0;
    work->results[work->index] = result;
    ++work->index;
    if (work->index >= work->count) {
        choice = 0;
        if (work->count > 0) {
            first = work->candidates[0];
            if (first != 0 && (second = work->candidates[1]) == 0) {
                choice = func_080C8240(work->source->unit) !=
                         func_080C8240(work->candidates[0]->unit);
            } else if (first == 0 && (second = work->candidates[1]) != 0) {
                if (func_080C8240(work->source->unit) ==
                    func_080C8240(work->candidates[1]->unit))
                    choice = 1;
            } else if (first != 0 && second != 0 && first != second &&
                       work->source != first) {
                if (work->source == second) {
                    choice = 1;
                } else if (func_080C8240(work->source->unit) !=
                           func_080C8240(work->candidates[0]->unit)) {
                    if (func_080C8240(work->source->unit) ==
                        func_080C8240(work->candidates[1]->unit))
                        choice = 1;
                    else
                        choice = (s16)((s16)func_08002804() % 2);
                }
            }
        }
        work->choice = choice;
    }
    return 0;
}
