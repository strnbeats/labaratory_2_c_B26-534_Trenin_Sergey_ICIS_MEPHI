#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "applicant.h"

static int generate_score(void) {
    int first = rand() % 51;
    int second = rand() % 51;

    return 50 + (first + second) / 2;
}

int get_total_score(const Applicant *applicant) {
    int third_subject = applicant->physics;

    if (applicant->informatics > third_subject) {
        third_subject = applicant->informatics;
    }

    return applicant->russian
        + applicant->mathematics
        + third_subject;
}

void generate_directions(Direction directions[], int count) {
    const Direction templates[] = {
        {"01.03.02", "Прикладная математика и информатика",
         "Прикладная математика и информатика", 45},
        {"03.03.01", "Прикладные математика и физика",
         "Прикладные математика и физика", 30},
        {"03.03.02", "Физика",
         "Физика", 35},
        {"09.03.01", "Информатика и вычислительная техника",
         "Информатика и вычислительная техника", 70},
        {"09.03.03", "Прикладная информатика",
         "Прикладная информатика", 45},
        {"09.03.04", "Программная инженерия",
         "Программная инженерия", 40},
        {"10.03.01", "Информационная безопасность",
         "Информационная безопасность", 50},
        {"11.03.04", "Электроника и наноэлектроника",
         "Электроника и наноэлектроника", 25},
        {"12.03.01", "Приборостроение",
         "Приборостроение", 20},
        {"14.03.02", "Ядерные физика и технологии",
         "Ядерные физика и технологии", 30}
    };

    int available = sizeof(templates) / sizeof(templates[0]);

    if (count < 1 || count > available) {
        return;
    }

    for (int i = 0; i < count; i++) {
        directions[i] = templates[i];
    }
}

void generate_applicants(
    Applicant applicants[],
    int applicant_count,
    const Direction directions[],
    int direction_count
) {
    const char *surnames[] = {
        "Иванов", "Петров", "Сидоров", "Смирнов", "Кузнецов",
        "Попов", "Соколов", "Лебедев", "Козлов", "Новиков"
    };

    const char *first_names[] = {
        "Иван", "Петр", "Алексей", "Дмитрий", "Павел",
        "Андрей", "Максим", "Кирилл", "Артем", "Роман"
    };

    const char *patronymics[] = {
        "Иванович", "Сергеевич", "Дмитриевич", "Андреевич",
        "Игоревич", "Максимович", "Олегович", "Романович",
        "Евгеньевич", "Алексеевич"
    };

    (void)directions;

    if (applicant_count < 1 ||
        direction_count < 1 ||
        direction_count > DIRECTION_COUNT) {
        return;
    }

    for (int i = 0; i < applicant_count; i++) {
        Applicant *applicant = &applicants[i];

        int surname_index = i % 10;
        int first_index = (i / 10) % 10;
        int patronymic_index = (i / 100) % 10;

        snprintf(
            applicant->full_name,
            NAME_LENGTH,
            "%s %s %s",
            surnames[surname_index],
            first_names[first_index],
            patronymics[patronymic_index]
        );

        applicant->russian = generate_score();
        applicant->mathematics = generate_score();
        applicant->physics = generate_score();
        applicant->informatics = generate_score();

        int benefit_roll = rand() % 100;

        if (benefit_roll < 2) {
            applicant->benefit = BVI;
        } else if (benefit_roll < 10) {
            applicant->benefit = SPECIAL_QUOTA;
        } else if (benefit_roll < 18) {
            applicant->benefit = SEPARATE_QUOTA;
        } else if (benefit_roll < 26) {
            applicant->benefit = TARGET_ADMISSION;
        } else {
            applicant->benefit = NO_BENEFIT;
        }

        applicant->application_count =
            3 + rand() % (MAX_APPLICATIONS_PER_APPLICANT - 2);

        int selected[DIRECTION_COUNT];

        for (int j = 0; j < direction_count; j++) {
            selected[j] = j;
        }

        for (int j = direction_count - 1; j > 0; j--) {
            int k = rand() % (j + 1);
            int temp = selected[j];
            selected[j] = selected[k];
            selected[k] = temp;
        }

        for (int j = 0; j < applicant->application_count; j++) {
            applicant->applications[j].direction_index = selected[j];
            applicant->applications[j].priority = j + 1;
        }

        applicant->enrolled_direction = -1;
    }
}