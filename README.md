# Rollenspiel-3-Monster-Team-Sven-Gian-Cristian

Textbasiertes Rollenspiel Spieler gegen Monster
Von Cristian (Leader), Gian (Apprentis) und Sven (Dungeon-Master)

Beschreibung:

Dieses Projekt ist ein einfaches, textbasiertes Rollenspiel, programmiert in C.
Der Spieler tritt rundenbasiert gegen mehrere Monster an. Ziel des Spiels ist es, alle Monster zu besiegen, bevor die Lebenspunkte des Spielers auf null sinken.

Regeln:

Charakter erstellen:
Zu Beginn gibt der Spieler seinem Helden einen Namen. Der Held startet mit festgelegten Lebenspunkten (HP) und Angriffskraft.

Monster auswählen:
In jeder Runde wird ein Monster ausgewählt, das angegriffen werden soll. Wenn das gewählte Monster besiegt ist, muss in der nächsten Runde ein neues Ziel gewählt werden.

Angriff wählen:
Der Spieler wählt zwischen vier Angriffstypen:

    Physisch

    Magisch

    Fernkampf

    Gift

Kampfablauf:
Der Spieler greift zuerst an. Überlebt das Monster, greift es im Anschluss zurück und verursacht Schaden am Spieler. Der Ablauf wiederholt sich, bis alle Monster besiegt sind oder der Spieler keine Lebenspunkte mehr hat.

Spielende:
Das Spiel endet mit einem Sieg, wenn alle Monster besiegt wurden, oder mit einer Niederlage, wenn die Lebenspunkte des Spielers auf null fallen.


Wie startet man das Spiel? Ab hier Terminal nutzen und mit Ctrl+C kopieren und mit Ctrl+Shift+V einfügen!:

Im Terminal in den Projektordner wechseln:
cd Rollenspiel

Das Spiel kompilieren:
gcc -std=c11 -Wall -Wextra -g -o game main.c game.c character.c monster.c attack.c

Das Spiel starten:
./game