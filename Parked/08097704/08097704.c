typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;

struct Context {
    int owner;
    u8 unknown_04[0x1A];
    u8 palette;
    u8 unknown_1F[0x15];
    u16 resource;
    u8 unknown_36[0xA];
    void *renderer;
    u8 unknown_44[8];
    int handles[2];
};

extern const u8 data_08394352[];
extern int func_080C92F0(int owner, int attribute);
extern int func_08021618(void *renderer, int previous, int mode, u8 kind,
                       u16 resource, int position, int row);
extern void func_08021E64(int handle, u8 palette);
extern void func_08021BD4(void *renderer, int handle);

static inline int offset_locked(int owner)
{
    return (func_080C92F0(owner, 0x28) & 2) ? 1 : 0;
}

void func_08097704(struct Context *context, u16 position, u8 displacement)
{
    int row;
    int end_row;
    int adjusted_position;

    if (offset_locked(context->owner))
        displacement = 0;

    end_row = 3;
    row = 1;
    adjusted_position = position + (s8)displacement;

    for (; row < end_row; row++) {
        int handle = func_08021618(context->renderer, context->handles[row - 1],
                                  1, data_08394352[row - 1], context->resource,
                                  adjusted_position, row);

        if (handle != -1) {
            context->handles[row - 1] = handle;
            func_08021E64(handle, context->palette);
        } else if (context->handles[row - 1]) {
            func_08021BD4(context->renderer, context->handles[row - 1]);
            context->handles[row - 1] = 0;
        }
    }
}
