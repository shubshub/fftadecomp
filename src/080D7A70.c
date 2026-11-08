#include "ffta.h"

struct Task;
struct Scheduler;
struct Effect;
struct Data;

struct Request {
    u16 state;
    u8 unknown_02[2];
    const struct Data *data;
    u8 unknown_08[12];
    u16 count;
    u8 unknown_16[6];
};

extern struct Scheduler *data_0200F430;
extern int func_080D791C(struct Task *, struct Request *, struct Effect *);
extern struct Task *func_08005954(struct Scheduler *,
    int (*)(struct Task *, struct Request *, struct Effect *),
    u16, const struct Request *, struct Task *);

/* Target: 44 bytes at 080D7A70; descriptor is partially initialized. */
struct Task *func_080D7A70(const struct Data *data, u8 count,
                        struct Task *parent)
{
    struct Request request;

    request.count = count;
    request.data = data;
    return func_08005954(data_0200F430, func_080D791C, 40,
                         &request, parent);
}
