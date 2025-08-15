#ifndef MONSTER_H
#define MONSTER_H

typedef struct
{
    char name[50];
    int health;
    int attack;
    unsigned int poison_hits;
    unsigned int stunned : 1;
} Monster;

void createMonster(Monster *monster, char name[], int health, int attack);
void displayMonster(const Monster *monster);

#endif