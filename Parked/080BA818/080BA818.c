#include "ffta.h"

/* 0x080BA818..0x080BA878: 96 bytes, 47 Thumb instructions. */
typedef struct TileNode TileNode;
struct TileNode {
    u32 unknown_00;
    u8 active;
    u8 x;
    u8 y;
    u8 map_value;
    TileNode *next;
};

typedef struct {
    TileNode *head;
    TileNode entries[13];
} TileList;

extern u8 func_0801CC18(u8 x, u8 y);

static inline TileNode *find_free_node(TileList *list)
{
    s32 i;
    for (i = 0; i < 13; i++) {
        if (list->entries[i].active == 0) {
            return &list->entries[i];
        }
    }
    return 0;
}

void func_080BA818(TileList *list, u8 x, u8 y)
{
    TileNode *node = find_free_node(list);
    TileNode *tail;

    node->active = 1;
    node->x = x;
    node->y = y;
    node->map_value = func_0801CC18(x, y);
    if (list->head == 0) {
        list->head = node;
    } else {
        tail = list->head;
        while (tail->next != 0) {
            tail = tail->next;
        }
        tail->next = node;
        node->next = 0;
    }
}
