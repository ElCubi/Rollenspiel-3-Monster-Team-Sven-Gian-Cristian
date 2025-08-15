#include <stdio.h>
#include <stdbool.h>
#include "game.h"
#include "attack.h"
#include "character.h"
#include "monster.h"

// ---------- kleine Helfer ----------
static void clearLine(void) {
    int c; while ((c = getchar()) != '\n' && c != EOF) {}
}

static int readIntInRange(int min, int max) {
    int x, ok;
    do {
        printf("> ");
        ok = scanf("%d", &x);
        if (ok != 1) { printf("Ungültig. Bitte Zahl eingeben.\n"); clearLine(); continue; }
        clearLine();
        if (x < min || x > max) printf("Bitte %d..%d eingeben.\n", min, max);
    } while (x < min || x > max);
    return x;
}

static void printDivider(void) {
    puts("----------------------------------------");
}

static void showHealthBar(const char *name, int hp, int maxHp) {
    // einfacher Text-HP-Balken (20 Zeichen)
    const int barLen = 20;
    int filled = hp > 0 ? (hp * barLen) / (maxHp > 0 ? maxHp : 1) : 0;
    if (filled < 0) filled = 0;
    printf("%-12s [", name);
    for (int i = 0; i < barLen; ++i) putchar(i < filled ? '#' : '-');
    printf("] %3d/%-3d HP\n", hp, maxHp);
}

static int chooseMonster(const Monster *monsters, int n) {
    int alive = 0;
    printf("\nWähle ein Monster:\n");
    for (int i = 0; i < n; ++i) {
        if (monsters[i].health > 0) {
            printf("%d) %s (HP: %d, ATK: %d)\n",
                   i + 1, monsters[i].name, monsters[i].health, monsters[i].attack);
            alive++;
        }
    }
    if (!alive) return -1;
    int idx = readIntInRange(1, n) - 1;
    while (monsters[idx].health <= 0) {
        printf("Dieses Monster ist besiegt. Wähle ein lebendes.\n");
        idx = readIntInRange(1, n) - 1;
    }
    return idx;
}

void selectAttack(AttackType *attackType)
{
    printf("\nWähle die Angriffsart:\n");
    printf("1) Physisch\n");
    printf("2) Magisch\n");
    printf("3) Fernkampf\n");
    printf("4) Gift\n");
    int wahl = readIntInRange(1, 4);

    // Euer Enum startet bei 0 -> wahl-1
    *attackType = (AttackType)(wahl - 1);
}

// ---------- Hauptspiel ----------
void startGame(Character *player, Monster *monsters, int numMonsters)
{
    if (!player || !monsters || numMonsters <= 0) {
        printf("Spiel konnte nicht gestartet werden.\n");
        return;
    }

    // Max-HP der Monster merken für HP-Balken
    int maxMonsterHp[64]; 
    if (numMonsters > (int)(sizeof maxMonsterHp / sizeof maxMonsterHp[0])) {
        printf("Zu viele Monster (%d). Max. 64.\n", numMonsters);
        return;
    }
    for (int i = 0; i < numMonsters; ++i) maxMonsterHp[i] = monsters[i].health;
    const int playerMaxHp = player->health;

    printDivider();
    printf("Held: %s (HP: %d, ATK: %d)\n", player->name, player->health, player->attack);
    printDivider();
    printf("Gegner heute:\n");
    for (int i = 0; i < numMonsters; ++i) {
        printf(" - %s (HP: %d, ATK: %d)\n", monsters[i].name, monsters[i].health, monsters[i].attack);
    }
    printDivider();

    int alive = numMonsters;
    int runde = 1;
    int target = -1; // aktuelles Ziel (bleibt, bis es tot ist)

    while (player->health > 0 && alive > 0) {
        printf("\n=== Runde %d ===\n", runde++);
        showHealthBar(player->name, player->health, playerMaxHp);

        // Nur neues Ziel wählen, wenn keins existiert oder das alte tot ist
        if (target < 0 || monsters[target].health <= 0) {
            target = chooseMonster(monsters, numMonsters);
            if (target < 0) break;
            printf("\n🎯 Ziel erfasst: %s\n", monsters[target].name);
        } else {
            printf("🎯 Ziel bleibt: %s (HP: %d)\n", monsters[target].name, monsters[target].health);
        }

        // Angriffstyp wählen
        AttackType type;
        selectAttack(&type);

        // Spieler greift an (reine Ausgabe kosmetisch)
        printf("\n⚔️  %s attackiert %s!\n", player->name, monsters[target].name);
        perfomAttack(player, &monsters[target], type);
        showHealthBar(monsters[target].name, monsters[target].health, maxMonsterHp[target]);

        if (monsters[target].health <= 0) {
            printf("✅ %s wurde besiegt!\n", monsters[target].name);
            alive--;
            target = -1; // nächstes Mal neues Ziel wählen
        } else {
            // Monster kontert
            printf("😡  %s kontert!\n", monsters[target].name);
            performMonsterAttack(&monsters[target], player);
            showHealthBar(player->name, player->health, playerMaxHp);
        }

        printDivider();
    }

    if (player->health > 0 && alive == 0) {
    printf("\n🏆 Sieg! Alle Monster wurden besiegt.\n");
    printf("=====================================\n");
    printf("🎉  Y O U   W I N  🎉\n");
    printf("=====================================\n");  
    } else if (player->health <= 0) {
    printf("\n💀 %s ist gefallen... Das Abenteuer endet hier.\n", player->name);
    } else {
    printf("\nSpiel beendet.\n");
    }
}