typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

typedef struct {
    u16 start;
    u16 end;
} RenderRange;

typedef struct {
    s16 x;
    s16 y;
    u16 unknown_04;
    u16 flags;
    RenderRange ranges[160];
    u16 width;
    u16 height;
} RenderState;

extern RenderState *func_0800C614(void *object);
extern void func_08010058(void *object, u16 first, u8 count, u8 start, u8 end);
extern void func_0800EA0C(s32 x, s32 y, u16 width, u16 height,
                          RenderRange *ranges, u32 mode);

static inline void render_object(void *object)
{
    RenderState *state = func_0800C614(object);

    func_08010058(object, 0, 160, 245, 250);
    func_0800EA0C(state->x, state->y, state->width, state->height,
                  state->ranges, 1);
}

/* Complete [0x08010160, 0x080101CC): 108 bytes, including the literal pool. */
void func_08010160(void *object, u16 width, u16 height)
{
    RenderState *state = func_0800C614(object);

    state->width = width;
    state->height = height;
    render_object(object);
}
