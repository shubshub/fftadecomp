#include "ffta.h"

struct Task;
struct Scheduler;

struct Entry080D3508 {
    int (*callback)(struct Task *, void *, void *);
    u16 size;
    u16 unknown_06;
};

struct Request080D3508 {
    u8 unknown_00[4];
    void *object;
    u32 arg;
    u32 mode;
    u8 unknown_10[4];
    u16 id;
    u16 value;
    u16 extra;
};

extern struct Scheduler *data_0200F430;
extern struct Task *data_020159C0;
extern const struct Entry080D3508 data_083947D8[];
extern const struct Entry080D3508 data_08395280[];
extern u8 func_080D3B98(void *object, u16 entry_index);
extern u8 func_080D3B38(void *object);
extern int func_080E2398(struct Task *, void *, void *);
extern struct Task *func_08005954(struct Scheduler *,
    int (*)(struct Task *, void *, void *),
    u16, const struct Request080D3508 *, struct Task *);

// Complete target [0x080D3508, 0x080D35D8): 208 bytes, 81 instructions.
struct Task *func_080D3508(u16 id, void *object, u32 arg)
{
    struct Request080D3508 request;
    int (*callback)(struct Task *, void *, void *);
    u16 size;
    u8 value;
    struct Task *task = 0;

    request.id = id;
    request.object = object;
    request.arg = arg;
    request.mode = 0;
    if (id <= 0x155) {
        if (func_080D3B98(object, id))
            request.mode = 2;
        value = func_080D3B38(object);
        request.value = value;
        request.extra = 0;
        callback = data_083947D8[id - 1].callback;
        size = data_083947D8[id - 1].size;
    } else {
        callback = data_08395280[id - 0x156].callback;
        size = data_08395280[id - 0x156].size;
        if (id == 0x159) {
            if (func_080D3B98(object, (u16)arg))
                request.mode = 2;
            request.value = data_083947D8[arg - 1].unknown_06;
            request.extra = arg;
            callback = func_080E2398;
            size = 0x28;
        }
    }
    task = func_08005954(data_0200F430, callback, size, &request,
                         data_020159C0);
    return task;
}
