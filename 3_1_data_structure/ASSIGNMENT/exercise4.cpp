#include <stdio.h>

int gcd(int a, int b) {
    while (b!=0) {
        int tmp = b;
        b = a%b;
        a = tmp;
    }
    return a;
}


int main() {
    printf("GCD of (48,12) = %d\n", gcd(48,12));      // GCD of (48,12) = 12
    printf("GCD of (270,192) = %d\n", gcd(270,192));    // GCD of (270,192) = 6
    printf("GCD of (2,2) = %d\n", gcd(2,2));        // GCD of (2,2) = 2
    printf("GCD of (5,7) = %d\n", gcd(5,7));        // GCD of (5,7) = 1 
   printf("GCD of (1,2) = %d\n", gcd(1,2));        // GCD of (1,2) = 1
    return 0;
}