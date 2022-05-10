#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


#define YOYO 1.22
#define DOLL 2.75
#define RUBBER_DUCK 1.85
#define TRACTOR 5.97
#define AIR_PLANE 6.47
#define BALL 2.16
#define CAR_RACE 7.13
#define DOG 4.57
#define SKIPPED 1.46
#define CAR 5.18
#define ELEPHANT 3.16
#define BEAR 4.89
#define XYLOPHONE 7.11
#define TANK 6.45
#define DAMKA 4.77
#define BOAT 8.04
#define TRAIN 6.71
#define CUBES 2.31
#define TRACK  6.21
#define WHISTLE 0.98
#define VANE 0.87
#define WALLET 43.94
#define WISH_SIZE 13
#define ITEMS_SIZE 21
#define WANTED_SOL 100



void aux_finding_list(double items[], double size);
void finding_list(double items[], double current_list[], int list_size,
                  double current_sum, int current_location);
/*void print_list(double current_list[], int size);*/

static int counter_sol = 0;

int main() {
    double items[] = {YOYO, DOLL, RUBBER_DUCK, TRACTOR, AIR_PLANE, BALL,
                      CAR_RACE, DOG, SKIPPED, CAR, ELEPHANT, BEAR, XYLOPHONE,
                      TANK, DAMKA, BOAT, TRAIN, CUBES, TRACK, WHISTLE, VANE};
    double size = sizeof(items) / sizeof(items[0]);
    aux_finding_list(items, size);
    return 0;
}



void aux_finding_list(double items[], double size){
    double *current_list = (double*)malloc(size * sizeof(double));
    finding_list(items, current_list, 0, 0, 0);
    free(current_list);
    return ;
}


void finding_list(double items[], double current_list[], int list_size,
                  double current_sum, int current_location){
    /*if(current_sum == WALLET && list_size == WISH_SIZE){
        counter_sol+=1;
        printf("We found a list with 13 items:\n");
        print_list(current_list, list_size);
        exit(0);
    }*/
    if(current_sum == WALLET && counter_sol== WANTED_SOL){
        printf("We found %d solutions.", WANTED_SOL);
        exit(0);
    }
    else if(current_sum == WALLET){
        counter_sol+=1;
        /* printf("Potential list:\n");
        print_list(current_list, list_size);*/
        finding_list(items, current_list, list_size -1 ,
                     current_sum - items[current_location],
                     current_location +1);
        return;
    }
    else{
        for(int i = current_location; i< ITEMS_SIZE; i++){
            current_list[list_size]=items[i];
            finding_list(items, current_list, list_size +1,
                         current_sum + items[i], i +1);
        }
    }
}

/*
void print_list(double current_list[], int size){
    for(int i = 0; i<size; i++){
        printf("%.2f, ", current_list[i]);
    }
    printf("\n");
}
 */


















