#include "ffta.h"

typedef union {
    struct {
        s32 x : 16;
        s32 height : 16;
        s32 z : 16;
    } packed;
    s16 components[4];
} Position;

typedef struct {
    u8 unknown_00[8];
    u16 x;
    u16 height;
    u16 z;
} ObjectData;

typedef struct {
    u8 x;
    u8 z;
    u8 height;
    u8 unknown_03;
} RoutePoint;

typedef struct {
    u8 unknown_00[4];
    RoutePoint points[1];
} Route;

typedef struct {
    ObjectData *data;
    Route *route;
    u8 unknown_08[0x12];
    s16 route_index;
    u8 unknown_1C[0xC];
    u8 facing;
} SceneObject;

s32 func_0809B120(SceneObject *object)
{
    Position current;
    Position destination;
    s32 distance_x;
    s32 distance_z;
    s32 distance;
    s32 facing;
    s32 middle_band;
    s32 changed;

    current.packed.x = object->data->x;
    current.packed.height = object->data->height;
    current.packed.z = object->data->z;
    destination.packed.x = object->route->points[object->route_index].x * 32 + 16;
    destination.packed.height = object->route->points[object->route_index].height * 16;
    destination.packed.z = object->route->points[object->route_index].z * 32 + 16;

    distance_x = current.components[0] - destination.components[0];
    if (distance_x < 0)
        distance_x = -distance_x;
    distance_z = current.components[2] - destination.components[2];
    if (distance_z < 0)
        distance_z = -distance_z;
    distance = distance_x;
    if (distance < distance_z)
        distance = distance_z;

    if (distance < 8)
        middle_band = 0;
    else if (distance < 16)
        middle_band = 1;
    else
        middle_band = distance < 24;

    if (middle_band) {
        facing = object->facing;
        if (facing == 1)
            facing = 2;
        else if (facing == 3)
            facing = 0;
    } else {
        facing = object->facing;
        if (facing == 0)
            facing = 1;
        else if (facing == 2)
            facing = 3;
    }

    if (facing == object->facing) {
        changed = 0;
    } else {
        object->facing = facing;
        changed = 1;
    }
    return changed;
}
