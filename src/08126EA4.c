/* 0x08126EA4: submit an object selection request. */
#include "ffta.h"

typedef struct SelectionObject {
    u8 field_00[6];
    u8 complete;
} SelectionObject;

typedef struct SelectionRequest {
    u16 state;
    u16 field_02;
    SelectionObject *object;
    u8 field_08[12];
    u16 selection;
    s16 code;
    u16 flag;
    u16 field_1A;
} SelectionRequest;

typedef u32 (*SelectionCallback)(void *, SelectionRequest *, void *);
extern u32 func_08126D34(void *, SelectionRequest *, void *);
extern void func_08121B8C(SelectionCallback, u16, const SelectionRequest *, void *);

void func_08126EA4(SelectionObject *object, u8 selection, s16 code, u8 flag)
{
    SelectionRequest request;

    object->complete = 0;
    request.object = object;
    request.selection = selection;
    request.code = code;
    request.flag = flag;
    func_08121B8C(func_08126D34, 12, &request, 0);
}
