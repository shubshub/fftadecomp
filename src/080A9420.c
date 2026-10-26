#include "ffta.h"

/* 0x080A9420: 40 bytes. */
typedef struct TreeNode TreeNode;
typedef struct TreeContext TreeContext;
typedef s32 (*TreeCallback)(TreeNode *node, void *payload);

typedef struct {
    u8 unknown_00[0x50];
    TreeContext *tree;
    u8 unknown_54[0x588];
    u8 enabled;
} AnimationGlobals;

extern AnimationGlobals data_0200F9E8;
s32 func_080A8E0C(TreeNode *node, void *payload);
void func_080C7D70(TreeContext *context, TreeCallback callback, void *payload);

void func_080A9420(void)
{
    AnimationGlobals *state = &data_0200F9E8;

    if (state->enabled)
        func_080C7D70(state->tree, func_080A8E0C, state);
}
