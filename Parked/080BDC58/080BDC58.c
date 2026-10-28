typedef unsigned char u8;

struct Node {
    unsigned int unknown_00;
    struct Node *next;
};

struct Grid {
    struct Node *cells[16][16];
};

static inline struct Node **grid_cell(struct Grid *grid, u8 x, u8 y)
{
    return &grid->cells[y][x];
}

/* Target: 080BDC58..080BDC98, 64 bytes. */
void func_080BDC58(struct Grid *grid, struct Node *node, u8 x, u8 y)
{
    struct Node **cell = grid_cell(grid, x, y);
    struct Node *current = *cell;

    if (current == (struct Node *)-1 || current == 0)
        return;

    if (current == node) {
        *cell = 0;
        return;
    }

    for (; current->next != 0; current = current->next) {
        if (current->next == node)
            break;
    }

    if (current->next == node)
        current->next = node->next;
}
