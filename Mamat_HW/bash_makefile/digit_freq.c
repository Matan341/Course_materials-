#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


#define max_len 1000
#define BOUNDARY 10

void digit_freq(char s[]);


int main() {
    char s[max_len];
    scanf("%s", s);
    digit_freq(s);
    return 0;
}



void digit_freq(char s[]) {
    int counter_freq[BOUNDARY] = {0};
    unsigned long  len = strlen(s);
    for (int i = 0; i < len ; i++) {
        if ( '0' <= s[i] && s[i] <= '9') {
            counter_freq[s[i] - '0']++;
        }
    }
    for (int i = 0; i < BOUNDARY ; i++) {
        if(i==BOUNDARY-1){
            printf("%d\n", counter_freq[i]);
        }
        else{
            printf("%d ", counter_freq[i]);
        }
    }
}