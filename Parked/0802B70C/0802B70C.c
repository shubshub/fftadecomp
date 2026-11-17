#include "ffta.h"

// Complete [0x0802B70C, 0x0802B880): 372 bytes, 186 instructions,
// including the state-pointer, offset, state and callback literals.

typedef struct Manager0802B70C Manager0802B70C;
typedef struct Task0802B70C Task0802B70C;
typedef struct Entry0802BA08 Entry0802BA08;

typedef struct {
    u16 event;
    u16 unknown_02;
    void *object;
    u8 unknown_08[0xC];
    u16 flags;
    u16 unknown_16;
    u32 unknown_18;
} Request0802B70C;

typedef struct {
    Manager0802B70C *manager;
    void *allocation;
    Task0802B70C *first_task;
    Task0802B70C *second_task;
    u8 unknown_10[0x381];
    u8 pending_transfer;
} TaskContext0802B70C;

extern TaskContext0802B70C *data_0200F440;
extern void func_08022B24(void);
extern Entry0802BA08 *func_0802BA08(void);
extern void func_0802B5A8(Entry0802BA08 *entries);
extern u16 func_08005BAC(Task0802B70C *task);
extern void func_08005C04(Task0802B70C *task, Request0802B70C *request);
extern void func_08005BA8(Task0802B70C *task, u16 state);
extern u32 func_0802D550(Task0802B70C *, Request0802B70C *, void *);
extern u32 func_0802D0B0(Task0802B70C *, Request0802B70C *, void *);
extern Task0802B70C *func_08005954(Manager0802B70C *manager,
                                   u32 (*callback)(Task0802B70C *, Request0802B70C *, void *),
                                   u16 size, const Request0802B70C *request,
                                   Task0802B70C *parent);

Task0802B70C *func_0802B70C(void *object, u16 flags)
{
    Request0802B70C request;
    Entry0802BA08 *entries;
    u16 state;

    request.object = object;
    request.flags = flags;
    func_08022B24();
    if (flags & 1) {
        if (data_0200F440->pending_transfer) {
            entries = func_0802BA08();
            func_0802BA08();
            func_0802B5A8(entries);
            data_0200F440->pending_transfer = 0;
        }
        if (data_0200F440->second_task != 0) {
            state = func_08005BAC(data_0200F440->second_task);
            if ((flags & 0x20) && state == 0x102) {
                request.event = 0x10A;
                func_08005C04(data_0200F440->second_task, &request);
                func_08005BA8(data_0200F440->second_task, 0x10B);
            } else {
                request.event = 0;
                func_08005C04(data_0200F440->second_task, &request);
                func_08005BA8(data_0200F440->second_task, 0x10D);
            }
        } else {
            data_0200F440->second_task = func_08005954(data_0200F440->manager,
                                                       func_0802D550, 0x628, &request, 0);
        }
        return data_0200F440->second_task;
    }
    if (data_0200F440->first_task != 0) {
        state = func_08005BAC(data_0200F440->first_task);
        if ((flags & 0x20) && (state == 0x102 || state == 0x10C)) {
            request.event = 0x10A;
            func_08005C04(data_0200F440->first_task, &request);
            func_08005BA8(data_0200F440->first_task, 0x10B);
        } else {
            request.event = 0x104;
            func_08005C04(data_0200F440->first_task, &request);
            func_08005BA8(data_0200F440->first_task, 0x10D);
        }
    } else {
        data_0200F440->first_task = func_08005954(data_0200F440->manager,
                                                  func_0802D0B0, 0x628, &request, 0);
    }
    return data_0200F440->first_task;
}
