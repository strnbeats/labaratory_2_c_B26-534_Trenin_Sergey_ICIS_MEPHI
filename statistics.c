#include <stdio.h>
#include <limits.h>
#include "statistics.h"

static int get_total_score(const Applicant *applicant) {
    int third_subject;

    if (applicant->physics > applicant->informatics) {
        third_subject = applicant->physics;
    } else {
        third_subject = applicant->informatics;
    }

    return applicant->russian
        + applicant->mathematics
        + third_subject;
}

void calculate_statistics(
    const Direction *direction,
    Statistics *statistics
) {
    statistics->average_without_benefits = 0.0;
    statistics->average_with_benefits = 0.0;

    statistics->minimum_score = INT_MAX;
    statistics->maximum_score = 0;

    statistics->special_quota_count = 0;
    statistics->separate_quota_count = 0;
    statistics->target_admission_count = 0;

    statistics->average_russian = 0.0;
    statistics->average_mathematics = 0.0;
    statistics->average_physics = 0.0;
    statistics->average_informatics = 0.0;

    statistics->applicant_count = direction->applicant_count;

    double sum_without_benefits = 0.0;
    double sum_with_benefits = 0.0;

    double sum_russian = 0.0;
    double sum_mathematics = 0.0;
    double sum_physics = 0.0;
    double sum_informatics = 0.0;

    int count_without_benefits = 0;

    const Applicant *ptr = direction->applicants;
    const Applicant *end = ptr + direction->applicant_count;

    while (ptr < end) {
        int total_score = get_total_score(ptr);

        sum_with_benefits +=
            ptr->benefit == BVI ? 300 : total_score;

        if (ptr->benefit != BVI) {
            sum_without_benefits += total_score;
            count_without_benefits++;
        }

        if (total_score < statistics->minimum_score) {
            statistics->minimum_score = total_score;
        }

        if (total_score > statistics->maximum_score) {
            statistics->maximum_score = total_score;
        }

        if (ptr->benefit == SPECIAL_QUOTA) {
            statistics->special_quota_count++;
        } else if (ptr->benefit == SEPARATE_QUOTA) {
            statistics->separate_quota_count++;
        } else if (ptr->benefit == TARGET_ADMISSION) {
            statistics->target_admission_count++;
        }

        sum_russian += ptr->russian;
        sum_mathematics += ptr->mathematics;
        sum_physics += ptr->physics;
        sum_informatics += ptr->informatics;

        ptr++;
    }

    if (count_without_benefits > 0) {
        statistics->average_without_benefits =
            sum_without_benefits / count_without_benefits;
    }

    if (statistics->applicant_count > 0) {
        statistics->average_with_benefits =
            sum_with_benefits / statistics->applicant_count;

        statistics->average_russian =
            sum_russian / statistics->applicant_count;

        statistics->average_mathematics =
            sum_mathematics / statistics->applicant_count;

        statistics->average_physics =
            sum_physics / statistics->applicant_count;

        statistics->average_informatics =
            sum_informatics / statistics->applicant_count;
    }
}

void print_statistics(
    const Direction *direction,
    const Statistics *statistics
) {
    printf("\n========================================\n");
    printf("Направление: %s\n", direction->name);
    printf("========================================\n");

    printf(
        "Количество абитуриентов: %d\n",
        statistics->applicant_count
    );

    printf(
        "Бюджетных мест: %d\n",
        direction->budget_places
    );

    printf(
        "Средний балл без БВИ: %.2f\n",
        statistics->average_without_benefits
    );

    printf(
        "Средний балл с учётом БВИ: %.2f\n",
        statistics->average_with_benefits
    );

    printf(
        "Минимальный конкурсный балл: %d\n",
        statistics->minimum_score
    );

    printf(
        "Максимальный конкурсный балл: %d\n",
        statistics->maximum_score
    );

    printf("\nКоличество льготников:\n");

    printf(
        "Особая квота: %d\n",
        statistics->special_quota_count
    );

    printf(
        "Отдельная квота: %d\n",
        statistics->separate_quota_count
    );

    printf(
        "Целевой приём: %d\n",
        statistics->target_admission_count
    );

    printf("\nСредние оценки по предметам:\n");

    printf(
        "Русский язык: %.2f\n",
        statistics->average_russian
    );

    printf(
        "Математика: %.2f\n",
        statistics->average_mathematics
    );

    printf(
        "Физика: %.2f\n",
        statistics->average_physics
    );

    printf(
        "Информатика: %.2f\n",
        statistics->average_informatics
    );
}