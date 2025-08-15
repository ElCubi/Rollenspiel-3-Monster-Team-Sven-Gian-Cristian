#include <stdio.h>
#include "attack.h"

void perfomAttack(Character *attacker, Monster *defender, AttackType attackType)
{
    int schaden = 0;
    printf("----Kampf!!!----\n");
    switch (attackType) //Angriffstypen aufteilung
    {
        case PHYSICAL:
            schaden = attacker->attack;
            break;

        case MAGICAL:
            schaden = (int)(attacker->attack * 1.5);
            break;

        case RANGED:
            schaden = (int)(attacker->attack * 0.9);
            break;

        case POISON: {
            schaden = (int)(attacker->attack * 0.2);
            defender->poison_hits++;
            if (defender->poison_hits >= 2) {
                defender->stunned = 1;      // nächste Runde greift das Monster nicht an
                defender->poison_hits = 0;  
                printf("%s ist vom Gift benommen und für 1 Runde betäubt!\n", defender->name);
            } else {
                printf("%s wurde vergiftet (%u/2).\n", defender->name, defender->poison_hits);
            }
            break;
        }
    }

    defender->health -= schaden;
    if (defender->health < 0) defender->health = 0;
    printf("Schaden am Monster: %d (Monster-HP: %d)\n", schaden, defender->health);
}

void performMonsterAttack(Monster *attacker, Character *defender)
{
    if (attacker->stunned) {
        printf("%s ist betäubt und kann diese Runde nicht angreifen!\n", attacker->name);
        attacker->stunned = 0; // Betäubung hält genau 1 Runde
        return;
    }

    int schaden = attacker->attack;         //wiso int generieren? - Lesbarkeit, zurückverfolgung, wiederverwendung
    defender->health -= schaden;
    if (defender->health < 0) defender->health = 0;
    printf("%s greift zurück! Schaden am Spieler: %d (Spieler-HP: %d)\n",
           attacker->name, schaden, defender->health);
}
