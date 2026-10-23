#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "applicant.h"
#include "statistics.h"

int main(void) {
    Direction directions[DIRECTION_COUNT];

    srand((unsigned int)time(NULL));
    generate_data(directions, DIRECTION_COUNT);

    int choice;

    do {
        printf("\n========================================\n");
        printf("   СТАТИСТИКА ПОСТУПЛЕНИЯ В МИФИ\n");
        printf("========================================\n");
        printf("1. Показать список направлений\n");
        printf("2. Показать статистику по всем направлениям\n");
        printf("0. Выход\n");
        printf("Ваш выбор: ");

        if (scanf("%d", &choice) != 1) {
            printf("Ошибка: необходимо ввести число.\n");

            int ch;

            while ((ch = getchar()) != '\n' && ch != EOF) {
            }

            choice = -1;
            continue;
        }

        if (choice == 1) {
            printf("\nСписок направлений:\n");

            for (int i = 0; i < DIRECTION_COUNT; i++) {
                printf(
                    "%2d. %-40s Абитуриентов: %d, мест: %d\n",
                    i + 1,
                    directions[i].name,
                    directions[i].applicant_count,
                    directions[i].budget_places
                );
            }
        } else if (choice == 2) {
            for (int i = 0; i < DIRECTION_COUNT; i++) {
                Statistics statistics;

                calculate_statistics(
                    &directions[i],
                    &statistics
                );

                print_statistics(
                    &directions[i],
                    &statistics
                );
            }
        } else if (choice == 0) {
            printf("Программа завершена.\n");
        } else {
            printf("Ошибка: такого пункта меню нет.\n");
        }

    } while (choice != 0);

    return 0;
}