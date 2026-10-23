#ifndef APPLICANT_H
#define APPLICANT_H

#define DIRECTION_COUNT 10
#define MIN_APPLICANTS 11
#define MAX_APPLICANTS 99
#define NAME_LENGTH 100

typedef enum {
    NO_BENEFIT,
    SPECIAL_QUOTA,
    SEPARATE_QUOTA,
    TARGET_ADMISSION,
    BVI
} Benefit;

typedef struct {
    char full_name[NAME_LENGTH];
    int russian;
    int mathematics;
    int physics;
    int informatics;
    Benefit benefit;
    int enrolled;
} Applicant;

typedef struct {
    char name[NAME_LENGTH];
    Applicant applicants[MAX_APPLICANTS];
    int applicant_count;
    int budget_places;
} Direction;

void generate_data(Direction directions[], int count);

#endif