#include <stdio.h>
#include <string.h>

// 문자열 s를 뒤집어 출력하는 함수
void reverse(const char *s) {
    int len = strlen(s);
    // 먼저 원본 문자열을 출력
    printf(s);
    printf("\n");

    // 문자열의 끝에서부터 시작하여 역순으로 문자 출력
    for (int i = len - 1; i >= 0; i--) {
        printf("%c", s[i]);
    }
    printf("\n");
}

int main() {
    // 테스트용 예시 문자열 reverse 함수 호출
    reverse("1234");
    reverse("123456789000");
    reverse("12.12314");

    return 0;
}
