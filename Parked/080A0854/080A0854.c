typedef unsigned char u8;
typedef signed short s16;

struct Motion {
    u8 unknown_00[0x28];
    s16 start_x;
    s16 start_y;
    s16 start_z;
    u8 unknown_2E[2];
    s16 end_x;
    s16 end_y;
    s16 end_z;
    u8 unknown_36[0x0A];
    s16 lower;
    s16 upper;
    s16 step;
    s16 duration;
    s16 kind;
};

extern int abs(int value);

static inline int movement_duration(s16 start_x, s16 start_y, s16 start_z,
    s16 end_x, s16 end_y, s16 end_z)
{
    return abs(end_x - start_x) + abs(end_z - start_z) + (end_y - start_y);
}

static inline int planar_distance(s16 start_x, s16 start_z, s16 end_x, s16 end_z)
{
    return abs(end_x - start_x) + abs(end_z - start_z);
}

static inline void initialize_motion(struct Motion *motion,
    s16 start_x, s16 start_y, s16 start_z,
    s16 end_x, s16 end_y, s16 end_z, int duration, int distance)
{
    motion->start_x = start_x;
    motion->start_y = start_y + 24;
    motion->start_z = start_z;
    motion->end_x = end_x;
    motion->end_y = end_y + 24;
    motion->end_z = end_z;
    motion->duration = duration;
    motion->step = duration <= 0 ? distance >> 1 : duration >> 1;
}

void func_080A0854(struct Motion *motion,
    s16 start_x, s16 start_y, s16 start_z,
    s16 end_x, s16 end_y, s16 end_z, s16 limit, int preserve_height)
{
    int duration = movement_duration(start_x, start_y, start_z, end_x, end_y, end_z);
    int distance = planar_distance(start_x, start_z, end_x, end_z);
    int half;
    int adjustment;
    int upper;
    int lower;
    int dx;
    int dz;

    if (duration > limit) {
        if (preserve_height == 0)
            end_y = end_y - 48 - (distance - limit);
        duration = limit;
    }

    half = limit >> 1;
    adjustment = (limit - duration) >> 1;
    upper = half + adjustment;
    if (upper > limit)
        upper = limit;
    lower = half - adjustment;

    initialize_motion(motion, start_x, start_y, start_z,
        end_x, end_y, end_z, duration, distance);

    dx = abs(motion->end_x - motion->start_x);
    dz = abs(motion->end_z - motion->start_z);
    motion->step = (dx < dz ? dz : dx) >> 1;

    if (lower >= upper) {
        motion->kind = 1;
        motion->lower = start_y + lower;
    } else {
        motion->kind = 2;
        motion->lower = start_y + lower;
        motion->upper = start_y + upper;
    }
}
