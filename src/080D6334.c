/* 080D6334: target 148 bytes. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

struct Point080D6334 {
    s16 x;
    s16 y;
};

struct Input080D6334 {
    void *object_reference;
    struct Point080D6334 start;
    struct Point080D6334 end;
    u16 value_0C;
    u16 value_0E;
    u16 count;
    const s16 *x_values;
    const s16 *y_values;
};

struct Options080D6334 {
    u32 value_00 : 8;
    u32 value_01 : 8;
    u32 unknown_02 : 16;
};

struct Descriptor080D6334 {
    u16 phase;
    u16 unknown_02;
    struct Input080D6334 *input;
    struct Options080D6334 *options;
    u32 unknown_0C;
    u32 unknown_10;
    u16 value_14;
    u16 unknown_16;
    u32 unknown_18;
};

struct Task080D6334;
struct State080D6334;
extern u32 func_080D5A60(struct Task080D6334 *, struct Descriptor080D6334 *,
                         struct State080D6334 *);
extern struct Task080D6334 *func_08005B6C(
    u32 (*)(struct Task080D6334 *, struct Descriptor080D6334 *, struct State080D6334 *),
    u16, struct Descriptor080D6334 *, struct Task080D6334 *);

struct Task080D6334 *func_080D6334(
    void *object_reference, const struct Point080D6334 *start,
    const struct Point080D6334 *end, u16 value_0C, u16 value_0E, u16 count,
    const s16 *x_values, const s16 *y_values, u16 value_14,
    u8 option_01, u8 option_00, struct Task080D6334 *parent)
{
    struct Input080D6334 input;
    struct Descriptor080D6334 descriptor;
    struct Options080D6334 options;

    input.object_reference = object_reference;
    input.start.x = start->x;
    input.start.y = start->y;
    input.end.x = end->x;
    input.end.y = end->y;
    input.value_0C = value_0C;
    input.value_0E = value_0E;
    input.count = count;
    input.x_values = x_values;
    input.y_values = y_values;
    options.value_01 = option_01;
    options.value_00 = option_00;
    descriptor.value_14 = value_14;
    descriptor.input = &input;
    descriptor.options = &options;
    return func_08005B6C(func_080D5A60, 40, &descriptor, parent);
}
