/* 0812BCE4: 40 bytes. Start the completion task with a selection. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u8 unknown_00[6];
    u8 complete;
} CompletionOwner;

typedef struct {
    u16 state;
    u8 unknown_02[2];
    CompletionOwner *owner;
    u8 unknown_08[12];
    u16 selection;
    u8 unknown_16[6];
} TaskRequest;

typedef struct TaskState TaskState;
typedef u32 (*TaskCallback)(void *, TaskRequest *, TaskState *);

extern u32 func_0812B7F0(void *, TaskRequest *, TaskState *);
extern void func_08121B8C(TaskCallback, u16, TaskRequest *, u32);

void func_0812BCE4(CompletionOwner *owner, u8 selection)
{
    TaskRequest request;

    owner->complete = 0;
    request.owner = owner;
    request.selection = selection;
    func_08121B8C(func_0812B7F0, 0x44, &request, 0);
}
