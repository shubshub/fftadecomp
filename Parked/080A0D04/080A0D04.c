typedef unsigned char u8;
typedef signed short s16;
typedef signed long long s64;

struct Curve {
    s64 first[3];
    s64 second[3];
    s64 third[3];
    u8 unknown_48[0x10];
};

struct Motion {
    u8 unknown_00[0x28];
    s16 start_x;
    s16 start_y;
    s16 start_z;
    u8 unknown_2E[2];
    s16 end_x;
    s16 end_y;
    s16 end_z;
    u8 unknown_36[0x1A];
    int dx[2];
    int dz[2];
    u8 unknown_60[0x18];
    struct Curve curves[2];
};

struct Position {
    s16 x;
    s16 y;
    s16 z;
};

extern int abs(int value);
extern s64 func_080086D0(s64 value, int count,
    s64 *first, s64 *second, s64 *third);

static inline int maximum(int first, int second)
{
    if (first > second)
        second = first;
    return second;
}

static inline s64 fixed_from_int(int value)
{
    return (s64)value * 65536;
}

int func_080A0D04(struct Motion *motion, int index, int progress,
    struct Position *position)
{
    int distance_x = abs(motion->dx[index]);
    int distance_z = abs(motion->dz[index]);
    int scaled;
    int offset_x;
    int offset_z;
    int travelled_x;
    int travelled_z;

    scaled = progress * maximum(distance_x, distance_z);
    position->y = (int)(func_080086D0(fixed_from_int(scaled >> 8), 3,
        motion->curves[index].first, motion->curves[index].second,
        motion->curves[index].third) >> 16) + motion->start_y;

    offset_x = (motion->dx[index] * progress) >> 8;
    position->x = offset_x;
    offset_z = (motion->dz[index] * progress) >> 8;
    position->z = offset_z;
    travelled_x = abs(position->x);
    travelled_z = abs(position->z);
    position->x = offset_x + motion->start_x;
    position->z = offset_z + motion->start_z;

    distance_x = abs(motion->start_x - motion->end_x);
    distance_z = abs(motion->start_z - motion->end_z);
    if (distance_x > travelled_x || distance_z > travelled_z)
        return 1;
    return 0;
}
