#include "ffta.h"

typedef signed long long s64;

typedef struct {
    s64 position;
    s64 value;
    s64 linear;
    s64 quadratic;
    s64 cubic;
    s64 curvature;
    s64 lower;
    s64 upper;
    s64 right_hand_side;
    s64 diagonal;
} SplineNode;

/* Target: 0x08007F9C, 848 bytes including the trailing literal pool. */
void func_08007F9C(SplineNode *nodes, s32 count)
{
    s32 interior = count - 2;
    s32 index;

    for (index = 1; index <= interior; index++) {
        s64 previous_width = nodes[index].position - nodes[index - 1].position;
        s64 next_width = nodes[index + 1].position - nodes[index].position;
        s64 total_width = previous_width + next_width;
        s64 next_slope;
        s64 previous_slope;

        nodes[index].lower = previous_width * 65536 / total_width;
        nodes[index].upper = 65536 - nodes[index].lower;
        next_slope = (nodes[index + 1].value - nodes[index].value) * 65536 / next_width;
        previous_slope = (nodes[index].value - nodes[index - 1].value) * 65536 / previous_width;
        nodes[index].right_hand_side = (next_slope - previous_slope) * 65536 / total_width * 6;
        nodes[index].diagonal = 131072;
    }

    for (index = 1; index < interior; index++) {
        s64 diagonal = nodes[index].diagonal;
        s64 upper = nodes[index].upper * 65536 / diagonal;
        s64 right_hand_side = nodes[index].right_hand_side * 65536 / diagonal;
        s64 next_lower = nodes[index + 1].lower;

        nodes[index].upper = upper;
        nodes[index].right_hand_side = right_hand_side;
        nodes[index + 1].diagonal -= next_lower * upper >> 16;
        nodes[index + 1].right_hand_side -= next_lower * right_hand_side >> 16;
    }

    nodes[interior].curvature = nodes[interior].right_hand_side * 65536 / nodes[interior].diagonal;
    for (index = interior - 1; index > 0; index--)
        nodes[index].curvature = nodes[index].right_hand_side
            - (nodes[index].upper * nodes[index + 1].curvature >> 16);

    nodes[interior + 1].curvature = 0;
    nodes[0].curvature = 0;
    for (index = 0; index <= interior; index++) {
        s64 width = nodes[index + 1].position - nodes[index].position;
        s64 quadratic = nodes[index].curvature >> 1;
        s64 cubic = (nodes[index + 1].curvature - nodes[index].curvature) * 65536 / (width * 6);

        nodes[index].quadratic = quadratic;
        nodes[index].cubic = cubic;
        nodes[index].linear = (nodes[index + 1].value - nodes[index].value) * 65536 / width
            - (quadratic * width >> 16) - ((cubic * width >> 16) * width >> 16);
    }
}
