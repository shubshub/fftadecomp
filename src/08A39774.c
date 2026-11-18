#include "ffta.h"

typedef struct ObjectNode08A39774 {
    u8 unknown_000[0x15C];
    struct ObjectNode08A39774 *left;
    struct ObjectNode08A39774 *right;
    struct ObjectNode08A39774 *parent;
} ObjectNode08A39774;

extern u32 data_03005F2C;
extern s32 func_08A390F4(const ObjectNode08A39774 *current,
                         const ObjectNode08A39774 *node);

/* Insert the object under the root supplied by the caller at 0x0808F1C6. */
void func_08A39774(ObjectNode08A39774 *current, ObjectNode08A39774 *node)
{
    node->left = 0;
    node->right = 0;
    if (current == 0) {
        data_03005F2C = (u32)node;
        return;
    }

    for (;;) {
        if (func_08A390F4(current, node)) {
            if (current->right != 0) {
                current = current->right;
            } else {
                current->right = node;
                node->parent = current;
                return;
            }
        } else {
            if (current->left != 0) {
                current = current->left;
            } else {
                current->left = node;
                node->parent = current;
                return;
            }
        }
    }
}
