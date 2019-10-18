#include <stdio.h>
#define NUM_HIGH_SCORES 10

void high_score_load(int* arr, int size){

    for(int i=0; i<size; i++){
        arr[i] = 0;
    }

    FILE *fp = fopen("/home/zero/allegro/tetris/assets/scores.dat", "r"); 

    int val=0; int loc=0;

    while((fscanf(fp, "%d\n", &val)!=EOF) && loc<size){
        arr[loc] = val;
        loc++; 
    }

    fclose(fp);
}

void high_score_add_score(int* arr, int size, int score){
    int loc = size-1;
    int temp = 0;

    if(score > *(arr + loc)){
        printf("the smallest value is: %d\n", *(arr+loc));
        *(arr+loc) = score;
        printf("now the smallest value is: %d\n", *(arr+loc));
    }

    while(loc > 0 && *(arr+loc) > *(arr+loc-1)){
        temp = *(arr+loc-1);
        *(arr+loc-1) = *(arr+loc);
        *(arr+loc) = temp;
        loc--;
    }

}

void high_score_write(int* arr, int size){
    FILE *fp = fopen("/home/zero/allegro/tetris/assets/scores.dat", "w"); 
    for(int i=0; i<size; i++){
        fprintf(fp, "%d\n", arr[i]);
    }
    fclose(fp);
}
