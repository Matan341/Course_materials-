#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


#define MAX_STUDENTS 2000
#define MAX_GRADE 100
#define PASS_GRADE 55
#define BOUNDARY 10

double calc_avg(int grades[], int num_students);
void bubble_sort(int grades[], int num_students);
void swap(int *a, int *b);
int count_un_passes(int grades[], int num_students);
void making_hist(int hist[BOUNDARY][BOUNDARY],int grades[], int num_students);
void printing_hist(int hist[BOUNDARY][BOUNDARY], int num_students, FILE *fp1);


int main(int argc, char *argv[]) {
    if (argc < 1) {
        fprintf(stderr, "Error\n");
        return 1;
    }
    FILE *fp1, *fp2;
    int hist[BOUNDARY][BOUNDARY];
    double pass;
    int student_counter = 0 ;
    int grades[MAX_STUDENTS];
    fp1 = fopen("course_statistics.txt", "w+");
    fp2 = fopen("grades.txt", "r");
    while(!feof (fp2)) {
        if(fscanf(fp2, " %d", &grades[student_counter]) != 1) {
            continue;
        }
        student_counter++;
    }
    fprintf(fp1, "num of students = %d\n", student_counter);
    fprintf(fp1, "avg = %.3f\n" , calc_avg(grades, student_counter));
    bubble_sort(grades, student_counter);
    fprintf(fp1, "the median is - %d\n", grades[(student_counter+1)/2]);
    fprintf(fp1, "max grade = %d, min grade = %d\n", grades[student_counter-1],
            grades[0]);
    pass = student_counter - (count_un_passes(grades, student_counter));
    fprintf(fp1, "pass rate = %.2f%%\n", (pass/student_counter)*MAX_GRADE);
    making_hist(hist, grades, student_counter);
    printing_hist(hist, student_counter, fp1);
    fclose(fp1);
    fclose(fp2);
    return 0;
}

/*Calculting the average of the course*/
double calc_avg(int grades[], int num_students){
    double average, sum = 0;
    for(int i = 0; i < num_students; i++) {
        sum += grades[i];
    }
    average=sum/num_students;
    return average;
}


void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}


/*Sorting the grades for median*/
void bubble_sort(int grades[], int num_students)
{
    int i, j;
    for (i = 0; i < num_students-1; i++){
        for (j = 0; j < num_students-i-1; j++){
            if (grades[j] > grades[j+1]) {
                swap(&grades[j], &grades[j + 1]);
            }
        }
    }
}


/*Counter for the unpass the course*/
int count_un_passes(int grades[], int num_students){
    int counter = 0;
    for(int i = 0; i < num_students; i++){
        if(grades[i] < PASS_GRADE) {
            counter += 1;
        }
        else
            break;
    }
    return counter;
}


/*Making Hist on 2D arry*/
void making_hist(int hist[BOUNDARY][BOUNDARY], int grades[], int num_students){
    int row, coulmn;
    for(int i=0; i< BOUNDARY; i++){
        for(int j=0; j<BOUNDARY; j++) {
            hist[i][j] = 0;
        }
    }
    for(int i = 0; i < num_students; i++){
        if(grades[i] == MAX_GRADE) {
            hist[BOUNDARY-1][BOUNDARY-1]++;
        }
        else{
            row = (grades[i]/BOUNDARY);
            coulmn = (grades[i]%BOUNDARY);
            hist[row][coulmn-1]++;
        }
    }
}


/*Printing Hist*/
void printing_hist(int hist[BOUNDARY][BOUNDARY], int num_students, FILE *fp1){
    int j, i;
    for (i = 0; i < BOUNDARY; i++){
        for(j=0; j < BOUNDARY; j++){
            if(j==BOUNDARY-1) {
                fprintf(fp1, "%d", hist[i][j]);
            }
            else {
                fprintf(fp1, "%d ", hist[i][j]);
            }
        }
        fprintf(fp1, "\n");
    }
}
