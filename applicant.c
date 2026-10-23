#include <stdio.h>
#include <stdlib.h>
#include "applicant.h"

void generate_data(Direction directions[], int count) {
    const char *names[] = {
        "Иванов Иван Иванович",
        "Петров Петр Сергеевич",
        "Сидоров Алексей Дмитриевич",
        "Смирнов Дмитрий Андреевич",
        "Кузнецов Павел Игоревич",
        "Попов Андрей Максимович",
        "Соколов Максим Олегович",
        "Лебедев Кирилл Романович",
        "Козлов Артем Евгеньевич",
        "Новиков Роман Алексеевич"
    };

    const char *direction_names[] = {
        "Программная инженерия",
        "Прикладная математика",
        "Прикладная математика и информатика",
        "Информационная безопасность",
        "Информатика и вычислительная техника",
        "Прикладная физика",
        "Ядерная физика",
        "Радиотехника",
        "Кибербезопасность",
        "Искусственный интеллект"
    };

    int names_count = sizeof(names) / sizeof(names[0]);
    int directions_count =
        sizeof(direction_names) / sizeof(direction_names[0]);

    if (count < 1 || count > directions_count) {
        return;
    }

    for (int i = 0; i < count; i++) {
        snprintf(
            directions[i].name,
            NAME_LENGTH,
            "%s",
            direction_names[i]
        );

        directions[i].applicant_count =
            MIN_APPLICANTS +
            rand() % (MAX_APPLICANTS - MIN_APPLICANTS + 1);

        directions[i].budget_places = 10 + rand() % 11;

        for (int j = 0; j < directions[i].applicant_count; j++) {
            Applicant *ptr = &directions[i].applicants[j];

            snprintf(
                ptr->full_name,
                NAME_LENGTH,
                "%s",
                names[rand() % names_count]
            );

            ptr->russian = rand() % 101;
            ptr->mathematics = rand() % 101;
            ptr->physics = rand() % 101;
            ptr->informatics = rand() % 101;

            int benefit_roll = rand() % 100;

            if (benefit_roll < 60) {
                ptr->benefit = NO_BENEFIT;
            } else if (benefit_roll < 72) {
                ptr->benefit = SPECIAL_QUOTA;
            } else if (benefit_roll < 84) {
                ptr->benefit = SEPARATE_QUOTA;
            } else if (benefit_roll < 96) {
                ptr->benefit = TARGET_ADMISSION;
            } else {
                ptr->benefit = BVI;
            }

            ptr->enrolled = 0;
        }
    }
}