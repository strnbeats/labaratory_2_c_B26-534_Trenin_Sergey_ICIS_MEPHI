#ifndef STATISTICS_H
#define STATISTICS_H

#include "applicant.h"

typedef struct {
    double average_without_benefits;
    double average_with_benefits;

    int minimum_score;
    int maximum_score;

    int special_quota_count;
    int separate_quota_count;
    int target_admission_count;
    int bvi_count;

    double average_russian;
    double average_mathematics;
    double average_physics;
    double average_informatics;

    int applicant_count;
} Statistics;

void calculate_statistics(
    const Direction *direction,
    const Applicant applicants[],
    int applicant_count,
    int direction_index,
    Statistics *statistics
);

void print_statistics(
    const Direction *direction,
    const Statistics *statistics
);

#endif