#include <stdio.h>

int hanoi(int n, char from, char temp, char to){
    if (n == 1) {
        return 1;
    }
    else {
        int move = 0;
        move += hanoi(n - 1, from, to, temp);
        move++;
        move += hanoi(n - 1, temp, from, to);
        return move;
    }
}

int main(){
    for (int i = 1; i <= 10; i++){
        int count = hanoi(i, 'A', 'B', 'C');
        printf("For %d blocks, we need to move at least %d times\n", i, count);
    }
    return 0;
}
