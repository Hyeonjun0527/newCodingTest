/* reverse_print.c  ―  원본 문자열과 그 역순을 한 번에 출력 */

#include <stdio.h>
#include <string.h>

/* ❶ 문자열 s를 화면에 그대로 찍고,
      ❷ 뒤에서부터 한 글자씩 꺼내 다시 찍는다.           */
void reverse(const char *s)
{
    /* strlen의 반환형은 size_t → 음수 비교를 피하려고 int로 캐스팅 */
    int len = (int)strlen(s);

    /* ------------------- 1. 원본 그대로 출력 ------------------- */
    /* 서식 문자열을 반드시 지정해야 포맷-스트링 취약점을 막을 수 있다 */
    printf("%s\n", s);

    /* ------------------- 2. 뒤집어 출력 ----------------------- */
    /* putchar가 조금 더 가볍지만, 일관성을 위해 printf 사용 */
    for (int i = len - 1; i >= 0; --i) {
        putchar(s[i]);
    }
    putchar('\n');
}

int main(void)
{
    /* 테스트 케이스 */
    reverse("1234");
    reverse("123456789000");
    reverse("12.12314");

    return 0;
}
