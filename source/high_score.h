#ifndef HIGH_SCORE_H
#define HIGH_SCORE_H

#define NUM_HIGH_SCORES 10

void high_score_load(int* arr, int size);
void high_score_add_score(int* arr, int size, int score);
void high_score_write(int* arr, int size);

#endif
