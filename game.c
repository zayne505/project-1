#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAP_SIZE 5
#define START_HEALTH 100
#define TREASURE_GOAL 3

void print_status(int x, int y, int health, int treasures) {
    printf("\n--- Dungeon Status ---\n");
    printf("Position: (%d, %d)\n", x + 1, y + 1);
    printf("Health: %d\n", health);
    printf("Treasures: %d/%d\n", treasures, TREASURE_GOAL);
}

void print_help(void) {
    printf("\nControls:\n");
    printf("  W - move up\n");
    printf("  S - move down\n");
    printf("  A - move left\n");
    printf("  D - move right\n");
    printf("  H - show help\n");
    printf("  Q - quit\n");
}

int clamp_move(int value) {
    if (value < 0) {
        return 0;
    }
    if (value >= MAP_SIZE) {
        return MAP_SIZE - 1;
    }
    return value;
}

int main(void) {
    char play_again = 'y';

    srand((unsigned int)time(NULL));

    printf("=== Treasure Dungeon ===\n");
    printf("Collect %d treasures before your health reaches zero.\n", TREASURE_GOAL);
    print_help();

    while (play_again == 'y' || play_again == 'Y') {
        int x = MAP_SIZE / 2;
        int y = MAP_SIZE / 2;
        int health = START_HEALTH;
        int treasures = 0;
        int turns = 0;
        char command;

        printf("\nA new dungeon opens around you...\n");

        while (health > 0 && treasures < TREASURE_GOAL) {
            int old_x = x;
            int old_y = y;
            int event;

            print_status(x, y, health, treasures);
            printf("Move: ");

            if (scanf(" %c", &command) != 1) {
                printf("Input error. Ending game.\n");
                return 1;
            }

            if (command == 'q' || command == 'Q') {
                printf("\nYou leave the dungeon with %d treasure(s).\n", treasures);
                return 0;
            }

            if (command == 'h' || command == 'H') {
                print_help();
                continue;
            }

            if (command == 'w' || command == 'W') {
                y--;
            } else if (command == 's' || command == 'S') {
                y++;
            } else if (command == 'a' || command == 'A') {
                x--;
            } else if (command == 'd' || command == 'D') {
                x++;
            } else {
                printf("Unknown command. Press H for help.\n");
                continue;
            }

            x = clamp_move(x);
            y = clamp_move(y);

            if (x == old_x && y == old_y) {
                printf("A cold stone wall blocks your path.\n");
                health -= 3;
            } else {
                turns++;
                event = rand() % 100;

                if (event < 25) {
                    int damage = 8 + rand() % 13;
                    health -= damage;
                    printf("A hidden trap snaps shut! You lose %d health.\n", damage);
                } else if (event < 45) {
                    treasures++;
                    printf("You find a glowing treasure chest!\n");
                } else if (event < 65) {
                    int heal = 5 + rand() % 11;
                    health += heal;
                    if (health > START_HEALTH) {
                        health = START_HEALTH;
                    }
                    printf("You drink a potion and recover %d health.\n", heal);
                } else {
                    printf("The corridor is quiet... too quiet.\n");
                }
            }
        }

        if (treasures >= TREASURE_GOAL) {
            printf("\nYou escaped with all %d treasures in %d turns. Victory!\n", TREASURE_GOAL, turns);
        } else {
            printf("\nYour health reached zero. The dungeon wins this time.\n");
        }

        printf("Play again? (y/n): ");
        if (scanf(" %c", &play_again) != 1) {
            return 0;
        }
    }

    printf("\nThanks for playing!\n");
    return 0;
}
