#ifndef APPLICANT_H
#define APPLICANT_H

#define DIRECTION_COUNT 10
#define APPLICANT_COUNT 100
#define MAX_APPLICATIONS_PER_APPLICANT 5

#define MIN_APPLICANTS 11
#define MAX_APPLICANTS 99

#define NAME_LENGTH 100
#define CODE_LENGTH 16

typedef enum {
    NO_BENEFIT,
    SPECIAL_QUOTA,
    SEPARATE_QUOTA,
    TARGET_ADMISSION,
    BVI
} Benefit;

typedef struct {
    int direction_index;
    int priority;
} Application;

typedef struct {
    char full_name[NAME_LENGTH];

    int russian;
    int mathematics;
    int physics;
    int informatics;

    Benefit benefit;

    Application applications[MAX_APPLICATIONS_PER_APPLICANT];
    int application_count;

    int enrolled_direction;
} Applicant;

typedef struct {
    char code[CODE_LENGTH];
    char name[NAME_LENGTH];
    char program_name[NAME_LENGTH];

    int budget_places;
} Direction;

void generate_directions(Direction directions[], int count);

void generate_applicants(
    Applicant applicants[],
    int applicant_count,
    const Direction directions[],
    int direction_count
);

int get_total_score(const Applicant *applicant);

#endif