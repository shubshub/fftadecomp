#include "ffta.h"

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *group;
    u8 unknown_08[14];
    u16 option;
} PhaseEvent;

typedef struct {
    u16 unknown_00;
    u8 option;
    u8 previous;
    s16 x;
    s16 y;
    void *object;
    void *outputs[4];
    void *position_task;
    void *effect_task;
    void *initial_task;
    void *group;
    void *state_task;
    void *sequence_task;
} PhaseWork;

extern const u8 data_0839EA24[];
extern const u8 data_0839EA3C[];
extern const u8 data_0839EA9C[];
extern const u8 data_0894BDF8[];

extern void *func_080E03F8(void *, const void *, u8, u8, const void *, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD748(void *, s16 *, s16 *, s16 *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void **, const void *, void *);
extern void *func_080DCFE4(void *, void *, u8, u16, u16, void *, u16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern u8 func_080DBC58(void *, u32);
extern u8 func_080DD580(const void *);
extern void *func_080D4704(void *, void *);
extern void func_080DE10C(void *, u16);
extern void *func_080D6134(void *);
extern void *func_080D4774(void *);
extern void *func_080DBA5C(void *);
extern u8 func_080DBC18(void *, u32);

u32 func_08100D00(void *parent, PhaseEvent *event, PhaseWork *work)
{
    switch (event->phase) {
    case 0: {
        void *group;
        u8 mode;

        work->option = event->option;
        group = event->group;
        work->group = group;
        mode = 2;
        if (work->option)
            mode = 0;
        work->initial_task = func_080E03F8(group, data_0839EA24, mode, 1, 0, parent);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        work->initial_task = func_080E05DC(work->initial_task);
        if (!work->initial_task) {
            if (func_080D8858(work->group, 0)) {
                void *unit = func_080DD4A4(work->group, 0);

                work->object = func_080DD748(unit, &work->x, &work->y, 0);
                work->position_task = func_080D6098(work->x, work->y, 0, 1, 4,
                                                  work->outputs, data_0839EA3C, parent);
                work->state_task = func_080DCFE4(unit, 0, 12, 0, 4, parent, 40);
                work->sequence_task = func_080DFD8C(data_0839EA9C, 1, 4, 0, parent);
                work->previous = func_080DBC58(work->object, 9);
                if (func_080DD580(unit)) {
                    work->effect_task = func_080D4704((void *)data_0894BDF8, parent);
                    func_080DE10C(work->object, 0x50);
                }
                event->phase++;
            } else {
                event->phase = 2;
            }
        }
        break;
    case 0x101:
        work->position_task = func_080D6134(work->position_task);
        if (!work->position_task) {
            work->effect_task = func_080D4774(work->effect_task);
            if (!work->effect_task) {
                work->state_task = func_080DBA5C(work->state_task);
                if (!work->state_task) {
                    func_080DBC18(work->object, work->previous);
                    event->phase = 2;
                }
            }
        }
        break;
    }
    return 0;
}
