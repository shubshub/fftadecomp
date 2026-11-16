#include "ffta.h"

typedef struct Node080BCC70 Node080BCC70;
struct Node080BCC70 {
    s32 unknown_00;
    s32 unknown_04;
    s32 unknown_08;
    s32 unknown_0C;
    s8 unknown_10;
    u8 unknown_11;
    u8 unknown_12;
    u8 unknown_13;
    Node080BCC70 *unknown_14;
    Node080BCC70 *unknown_18;
};

typedef struct {
    Node080BCC70 unknown_00[16];
    Node080BCC70 *unknown_1C0;
    u16 unknown_1C4;
    s16 unknown_1C6;
} State080BCC70;

extern Node080BCC70 *func_080BCA74(State080BCC70 *state);
extern u32 func_08002804(void);

static inline Node080BCC70 *findInactive(Node080BCC70 *node)
{
    while (node != 0) {
        if (node->unknown_11 == 0)
            return node;
        node = node->unknown_18;
    }
    return 0;
}

static inline Node080BCC70 *insertNode(Node080BCC70 *head, Node080BCC70 *node)
{
    Node080BCC70 *current;

    if (head == 0)
        return node;
    if (head->unknown_10 < node->unknown_10) {
        head->unknown_14 = node;
        node->unknown_18 = head;
        return node;
    }
    current = head;
    while (current->unknown_18 != 0) {
        if (current->unknown_10 < node->unknown_10) {
            node->unknown_18 = current;
            node->unknown_14 = current->unknown_14;
            current->unknown_14 = node;
            return head;
        }
        current = current->unknown_18;
    }
    current->unknown_18 = node;
    node->unknown_14 = current;
    return head;
}

/* Complete [080BCC70, 080BCDF8): 392 bytes. */
void func_080BCC70(State080BCC70 *state, u8 enabled)
{
    Node080BCC70 *first = state->unknown_1C0;
    Node080BCC70 *current = first;

    while (current != 0) {
        if (current->unknown_11 != 0) {
            s16 x, y;

            if (first->unknown_12 & 1) {
                current->unknown_08 -= 12;
                if (current->unknown_08 <= -512)
                    first->unknown_12 &= ~1;
            } else {
                current->unknown_08 += 12;
                if (current->unknown_08 > 511)
                    first->unknown_12 |= 1;
            }
            current->unknown_0C += 2;
            current->unknown_00 += current->unknown_08;
            current->unknown_04 += current->unknown_0C;
            x = current->unknown_00 >> 8;
            y = current->unknown_04 >> 8;
            if (x < -32 || x > 271 || y > 160)
                current->unknown_11 = 0;
        }
        current = current->unknown_18;
    }
    if (enabled) {
        if (state->unknown_1C6 > 0) {
            state->unknown_1C6--;
        } else {
            Node080BCC70 *node;

            state->unknown_1C6 = 8;
            node = func_080BCA74(state);
            if (node == 0) {
                node = findInactive(state->unknown_1C0);
                if (node == 0)
                    return;
            } else {
                Node080BCC70 *head = state->unknown_1C0;
                Node080BCC70 **slot = &state->unknown_1C0;
                *slot = insertNode(head, node);
            }
            node->unknown_00 = ((s16)func_08002804() % 241) << 8;
            node->unknown_04 = 0;
            node->unknown_08 = 64 - (s16)func_08002804() % 129;
            node->unknown_0C = 256 - (s16)func_08002804() % 129;
            node->unknown_11 = 1;
        }
    }
}
