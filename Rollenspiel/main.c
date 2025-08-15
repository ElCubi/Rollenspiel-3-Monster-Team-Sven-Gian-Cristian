#include <stdio.h>
#include "character.h"
#include "monster.h"
#include "game.h"

int main(void)
{
    Character player;
    Monster monsters[3];

    printf("Willkommen zum textbasierten Rollenspiel: Spieler vs. Monster\n");

    createCharacter(&player);

    createMonster(&monsters[0], "Spinne", 25, 8);
    createMonster(&monsters[1], "Golem", 83, 5);
    createMonster(&monsters[2], "Drache", 70, 12);

    printf("\nDas Spiel beginnt...\n");
    for (int i = 0; i < 3; ++i) displayMonster(&monsters[i]);

    int numMonsters = (int)(sizeof(monsters) / sizeof(monsters[0]));
    startGame(&player, monsters, numMonsters);

    return 0;
}