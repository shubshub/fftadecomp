#include "ffta.h"

/* 080BCC70 .. 080BCDF8: 392 bytes. */
typedef struct Particle Particle;
struct Particle {
    s32 x;
    s32 y;
    s32 velocity_x;
    s32 velocity_y;
    s8 priority;
    u8 active;
    u8 flags;
    u8 unknown_13;
    Particle *previous;
    Particle *next;
};

typedef struct {
    u8 unknown_00[0x1C0];
    Particle *head;
    u16 unknown_1C4;
    s16 spawn_delay;
} ParticleSystem;

extern u32 func_08002804(void);
extern Particle *func_080BCA74(ParticleSystem *system);

static inline Particle *find_inactive(Particle *particle)
{
    while (particle != 0) {
        if (particle->active == 0)
            return particle;
        particle = particle->next;
    }
    return 0;
}

static inline Particle *insert_particle(Particle *head, Particle *particle)
{
    Particle *current;

    if (head == 0)
        return particle;
    if (head->priority < particle->priority) {
        head->previous = particle;
        particle->next = head;
        return particle;
    }
    current = head;
    while (current->next != 0) {
        if (current->priority < particle->priority) {
            particle->next = current;
            particle->previous = current->previous;
            current->previous = particle;
            return head;
        }
        current = current->next;
    }
    current->next = particle;
    particle->previous = current;
    return head;
}

void func_080BCC70(ParticleSystem *system, u8 spawn)
{
    Particle *head = system->head;
    Particle *current = head;

    while (current != 0) {
        if (current->active) {
            s16 x, y;

            if (head->flags & 1) {
                current->velocity_x -= 12;
                if (current->velocity_x <= -512)
                    head->flags &= ~1;
            } else {
                current->velocity_x += 12;
                if (current->velocity_x > 511)
                    head->flags |= 1;
            }
            current->velocity_y += 2;
            current->x += current->velocity_x;
            current->y += current->velocity_y;
            x = current->x >> 8;
            y = current->y >> 8;
            if ((u16)(x + 32) > 303 || y > 160)
                current->active = 0;
        }
        current = current->next;
    }
    if (spawn) {
        if (system->spawn_delay > 0) {
            system->spawn_delay--;
        } else {
            Particle *particle;

            system->spawn_delay = 8;
            particle = func_080BCA74(system);
            if (particle == 0) {
                particle = find_inactive(system->head);
                if (particle == 0)
                    return;
            } else {
                Particle **list = &system->head;

                *list = insert_particle(*list, particle);
            }
            particle->x = (s16)((s16)func_08002804() % 241) << 8;
            particle->y = 0;
            particle->velocity_x = 64 - (s16)((s16)func_08002804() % 129);
            particle->velocity_y = 256 - (s16)((s16)func_08002804() % 129);
            particle->active = 1;
        }
    }
}
