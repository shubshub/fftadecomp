#include "ffta.h"

/* Complete [0x08007F9C, 0x080082EC): 848 bytes, 401 instructions; 832 bytes of
   code and a 16-byte literal pool holding the s64 constants 0x10000 and 0x20000.
   Natural cubic spline through an array of 16.16 fixed-point nodes: the s64
   divisions and products are the agbcc runtime calls __divdi3 (func_08142280)
   and __muldi3 (func_08142A20). */

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

void func_08007F9C(SplineNode *nodes, s32 count)
{
    s32 interior;
    s32 index;
    s64 width;
    s64 previous_width;
    s64 next_width;
    s64 total_width;

    interior = count - 2;

    for (index = 1; index <= interior; index++) {
        previous_width = nodes[index].position - nodes[index - 1].position;
        next_width = nodes[index + 1].position - nodes[index].position;
        total_width = previous_width + next_width;
        nodes[index].lower = (previous_width << 16) / total_width;
        nodes[index].upper = 0x10000 - nodes[index].lower;
        nodes[index].right_hand_side =
            (((((nodes[index + 1].value - nodes[index].value) << 16) / next_width
               - ((nodes[index].value - nodes[index - 1].value) << 16) / previous_width) << 16)
             / total_width) * 6;
        nodes[index].diagonal = 0x20000;
    }

    for (index = 1; index < interior; index++) {
        nodes[index].upper = (nodes[index].upper << 16) / nodes[index].diagonal;
        nodes[index].right_hand_side = (nodes[index].right_hand_side << 16) / nodes[index].diagonal;
        nodes[index + 1].diagonal -= nodes[index + 1].lower * nodes[index].upper >> 16;
        nodes[index + 1].right_hand_side -= nodes[index + 1].lower * nodes[index].right_hand_side >> 16;
    }

    nodes[interior].curvature = (nodes[interior].right_hand_side << 16) / nodes[interior].diagonal;
    for (index = interior - 1; index > 0; index--)
        nodes[index].curvature = nodes[index].right_hand_side
            - (nodes[index].upper * nodes[index + 1].curvature >> 16);

    nodes[interior + 1].curvature = 0;
    nodes[0].curvature = 0;
    for (index = 0; index <= interior; index++) {
        width = nodes[index + 1].position - nodes[index].position;
        nodes[index].quadratic = nodes[index].curvature >> 1;
        nodes[index].cubic = ((nodes[index + 1].curvature - nodes[index].curvature) << 16) / (width * 6);
        nodes[index].linear = ((nodes[index + 1].value - nodes[index].value) << 16) / width
            - (nodes[index].quadratic * width >> 16)
            - ((nodes[index].cubic * width >> 16) * width >> 16);
    }
}
