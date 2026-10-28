#include "ffta.h"

/* 0x080BDBC4..0x080BDC20: 92 bytes. */
typedef struct Node {
    u8 unknown_00;
    u8 type;
    u8 unknown_02[2];
    struct Node *next;
} Node;

typedef struct {
    Node *cells[16][16];
    u8 blocked[16][16];
} Grid;

void func_080BDBC4(Grid *grid, void *object, u8 x, u8 y)
{
    Node *node = object;
    Node *head;

    if (node->type <= 3) {
        if ((grid->blocked[y][x] >> node->type) & 1)
            return;
    }

    head = grid->cells[y][x];
    if (head == (Node *)-1)
        return;
    if (head == 0) {
        grid->cells[y][x] = node;
    } else {
        while (head->next != 0)
            head = head->next;
        head->next = node;
    }
}
