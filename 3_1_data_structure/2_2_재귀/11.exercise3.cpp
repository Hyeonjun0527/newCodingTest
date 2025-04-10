#include <stdio.h>

void bin(int n) {
    if (n < 0 || n > 2100000000) {
        printf("Not available\n");
        return;
    }
    if (n == 0) {
        printf("0\n");
        return;
    }
    char c[100];
    int i = 0;
    while (n > 0) {
        c[i++] = n%2 +'0';
        n /= 2;
    }
    for (int j = i - 1; j >= 0; j--) {
        printf("%c",c[j]);
    }
    printf("\n");

}

int main(){
    bin(10);         // "1010"
    bin(0);          // "0"
    bin(1);          // "1"
    bin(2);          // "10"
    bin(1024);       // "10000000000"
    bin(2100000001); // "Not available"
    return 0;
}
