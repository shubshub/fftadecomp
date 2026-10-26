typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    const void *resource;
    u8 first;
    u8 second;
    u8 third;
    u8 fourth;
} Descriptor;

typedef struct {
    u8 count;
    u8 unknown_01[3];
    const Descriptor *descriptors;
} Batch;

typedef struct {
    u8 unknown_00[6];
    u8 alternate;
} TransferMode;

typedef struct {
    u8 kind;
    u8 unknown_01[3];
    const void *data;
    u32 unknown_08;
} Command;

typedef struct {
    const Command *commands;
    u8 unknown_04[3];
    u8 index;
    u32 first_offset;
    u32 second_offset;
    u32 unknown_10;
    u32 remaining;
    const u8 *source;
    u8 *destination;
} State;

typedef struct TransferRecord TransferRecord;

extern void func_080D45D0(const void *resource, u8 first, u8 second,
                          u8 third, u8 fourth);
extern u8 func_080C95A8(u16 index);
extern TransferRecord *func_080D3AF8(void);
extern void func_08000A98(TransferRecord *record, const void *source,
                         void *destination, u16 count);

/* 0x080D7864..0x080D791C: 184 bytes. */
u8 func_080D7864(State *state)
{
    u8 complete = 0;
    u8 index = state->index;
    const Command *commands = state->commands;
    const Command *command = &commands[index];

    if (command->kind == 2) {
        const Batch *batch = command->data;
        u8 index;

        for (index = 0; index < batch->count; index++) {
            const Descriptor *descriptor = &batch->descriptors[index];

            func_080D45D0(descriptor->resource, descriptor->first,
                          descriptor->second, descriptor->third,
                          descriptor->fourth);
        }
        complete = 1;
    } else {
        u32 size = 0x800;
        u32 offset;

        if (func_080C95A8(13) == 1)
            size >>= 2;
        if (state->remaining <= size) {
            size = state->remaining;
            complete = 1;
        }
        offset = 0;
        index = state->index;
        commands = state->commands;
        command = &commands[index];
        if (command->kind == 3) {
            const TransferMode *mode = command->data;

            if (!mode->alternate)
                offset = state->first_offset;
            else
                offset = state->second_offset;
        }
        func_08000A98(func_080D3AF8(), state->source,
                      state->destination + offset, size / 2);
        state->source += size;
        state->destination += size;
        state->remaining -= size;
    }
    return complete;
}
