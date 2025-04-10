#include <stdio.h>
#include <string.h>

void reverse(const char* s) {
    int len = strlen(s);
    printf(s);
    printf("\n");
    for (int i = len - 1; i >= 0; i--) {
        printf("%c", s[i]);
    }
    printf("\n");
}

int main() {
    reverse("1234");            
    reverse("123456789000");
    reverse("12.12314");

    return 0;
}
