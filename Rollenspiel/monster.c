#include <stdio.h>
#include <string.h>
#include "monster.h"

void createMonster(Monster *monster, char name[], int health, int attack)
{
    strcpy(monster->name, name);
    monster->health = health;
    monster->attack = attack;
    monster->poison_hits = 0;
    monster->stunned = 0;
}

void displayMonster(const Monster *monster)
{
    printf("----Monster-----\n");
    printf("Name: %s\n", monster->name);
    printf("Gesundheit: %d\n", monster->health);
    printf("Angriffskraft: %d\n", monster->attack);
}