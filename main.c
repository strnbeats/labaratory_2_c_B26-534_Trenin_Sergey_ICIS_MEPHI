#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "applicant.h"
#include "statistics.h"

static int read_integer(void) {
    int value;
    int result = scanf("%d", &value);

    while (getchar() != '\n' && !feof(stdin)) {
    }

    if (result != 1) {
        return -1;
    }

    return value;
}

static int has_application(
    const Applicant *applicant,
    int direction_index
) {
    if (applicant->application_count < 0 ||
        applicant->application_count > MAX_APPLICATIONS_PER_APPLICANT) {
        printf(
            "ОШИБКА: некорректное количество заявлений: %d\n",
            applicant->application_count
        );
        return 0;
    }

    for (int i = 0; i < applicant->application_count; i++) {
        if (applicant->applications[i].direction_index == direction_index) {
            return 1;
        }
    }

    return 0;
}

static void print_directions(
    const Direction directions[],
    int direction_count
) {
    printf("\nСписок направлений:\n");

    for (int i = 0; i < direction_count; i++) {
        printf(
            "%d. %s (код: %s, бюджетных мест: %d)\n",
            i + 1,
            directions[i].name,
            directions[i].code,
            directions[i].budget_places
        );
    }
}

static void print_applicant(
    const Applicant *applicant,
    const Direction directions[],
    int direction_count
) {
    printf("\nФИО: %s\n", applicant->full_name);
    printf("Русский язык: %d\n", applicant->russian);
    printf("Математика: %d\n", applicant->mathematics);
    printf("Физика: %d\n", applicant->physics);
    printf("Информатика: %d\n", applicant->informatics);
    printf("Конкурсный балл: %d\n", get_total_score(applicant));

    switch (applicant->benefit) {
        case NO_BENEFIT:
            printf("Льгота: нет\n");
            break;
        case SPECIAL_QUOTA:
            printf("Льгота: особая квота\n");
            break;
        case SEPARATE_QUOTA:
            printf("Льгота: отдельная квота\n");
            break;
        case TARGET_ADMISSION:
            printf("Льгота: целевое обучение\n");
            break;
        case BVI:
            printf("Льгота: без вступительных испытаний\n");
            break;
        default:
            printf("Льгота: неизвестно\n");
            break;
    }

    if (applicant->application_count < 0 ||
        applicant->application_count > MAX_APPLICATIONS_PER_APPLICANT) {
        printf(
            "ОШИБКА: некорректное количество заявлений: %d\n",
            applicant->application_count
        );
        return;
    }

    printf("Поданные заявления:\n");

    for (int priority = 1;
         priority <= applicant->application_count;
         priority++) {
        for (int j = 0; j < applicant->application_count; j++) {
            if (applicant->applications[j].priority == priority) {
                int index = applicant->applications[j].direction_index;

                if (index >= 0 && index < direction_count) {
                    printf(
                        "  Приоритет %d: %s\n",
                        priority,
                        directions[index].name
                    );
                } else {
                    printf(
                        "  Приоритет %d: некорректный индекс направления %d\n",
                        priority,
                        index
                    );
                }

                break;
            }
        }
    }
}

static void print_applicants_for_direction(
    const Applicant applicants[],
    int applicant_count,
    const Direction directions[],
    int direction_count
) {
    print_directions(directions, direction_count);

    printf("\nВведите номер направления: ");
    int direction_number = read_integer();

    if (direction_number < 1 || direction_number > direction_count) {
        printf("Ошибка: неверный номер направления.\n");
        return;
    }

    int direction_index = direction_number - 1;
    int found = 0;

    printf(
        "\nАбитуриенты, подавшие заявление на направление «%s»:\n",
        directions[direction_index].name
    );

    for (int i = 0; i < applicant_count; i++) {
        if (has_application(&applicants[i], direction_index)) {
            print_applicant(
                &applicants[i],
                directions,
                direction_count
            );
            found = 1;
        }
    }

    if (!found) {
        printf("Абитуриенты не найдены.\n");
    }
}

static void search_applicant(
    const Applicant applicants[],
    int applicant_count,
    const Direction directions[],
    int direction_count
) {
    char surname[NAME_LENGTH];

    printf("Введите фамилию для поиска: ");

    if (scanf("%99s", surname) != 1) {
        while (getchar() != '\n' && !feof(stdin)) {
        }
        printf("Ошибка чтения фамилии.\n");
        return;
    }

    while (getchar() != '\n' && !feof(stdin)) {
    }

    int found = 0;

    for (int i = 0; i < applicant_count; i++) {
        if (strstr(applicants[i].full_name, surname) != NULL) {
            print_applicant(
                &applicants[i],
                directions,
                direction_count
            );
            found = 1;
        }
    }

    if (!found) {
        printf("Абитуриенты с такой фамилией не найдены.\n");
    }
}

int main(void) {
    Direction directions[DIRECTION_COUNT];
    Applicant applicants[APPLICANT_COUNT];

    srand((unsigned int)time(NULL));

    generate_directions(directions, DIRECTION_COUNT);

    generate_applicants(
        applicants,
        APPLICANT_COUNT,
        directions,
        DIRECTION_COUNT
    );

    int invalid_counts = 0;

    for (int i = 0; i < APPLICANT_COUNT; i++) {
        if (applicants[i].application_count < 0 ||
            applicants[i].application_count > MAX_APPLICATIONS_PER_APPLICANT) {
            printf(
                "ОШИБКА ГЕНЕРАЦИИ: абитуриент %d, application_count = %d\n",
                i,
                applicants[i].application_count
            );
            invalid_counts++;
        }
    }

    if (invalid_counts == 0) {
        printf("Проверка application_count пройдена: все значения корректны.\n");
    } else {
        printf(
            "Найдено абитуриентов с некорректным количеством заявлений: %d\n",
            invalid_counts
        );
    }

    int choice;

    do {
        printf("\n========== МЕНЮ ==========\n");
        printf("1. Показать список направлений\n");
        printf("2. Показать статистику\n");
        printf("3. Показать абитуриентов по направлению\n");
        printf("4. Найти абитуриента по фамилии\n");
        printf("0. Выход\n");
        printf("Выберите пункт: ");

        choice = read_integer();

        switch (choice) {
            case 1:
                print_directions(directions, DIRECTION_COUNT);
                break;

            case 2:
                for (int i = 0; i < DIRECTION_COUNT; i++) {
                    Statistics statistics;

                    calculate_statistics(
                        &directions[i],
                        applicants,
                        APPLICANT_COUNT,
                        i,
                        &statistics
                    );

                    print_statistics(&directions[i], &statistics);
                }
                break;

            case 3:
                print_applicants_for_direction(
                    applicants,
                    APPLICANT_COUNT,
                    directions,
                    DIRECTION_COUNT
                );
                break;

            case 4:
                search_applicant(
                    applicants,
                    APPLICANT_COUNT,
                    directions,
                    DIRECTION_COUNT
                );
                break;

            case 0:
                printf("Завершение программы.\n");
                break;

            default:
                printf("Ошибка: выбери существующий пункт меню.\n");
                break;
        }
    } while (choice != 0);

    return 0;
}