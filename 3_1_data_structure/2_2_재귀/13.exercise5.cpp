#include <stdio.h>

// RLE(Run Length Encoding) 형태로 문자열 s를 압축하여 출력하는 함수
// idx 인덱스부터 시작하여 같은 문자가 연속으로 몇 번 나오는지를 세고 출력
void compressRLE(const char *s, int idx) {
    // 문자열 끝('\0')에 도달할 때까지 반복
    while (s[idx] != '\0') {
        int cnt = 0;
        // 같은 문자가 연속으로 몇 번 등장하는지 확인
        while (s[idx] == s[idx + cnt]) {
            cnt++;
        }
        // 현재 문자와 등장 횟수를 출력
        printf("%c%d", s[idx], cnt);
        // 인덱스를 건너뛰어 연속으로 나타난 다음 위치로 이동
        idx += cnt;
    }
}

int main() {
    // "aaabbcddd" -> a3b2c1d3 형태로 출력
    compressRLE("aaabbcddd", 0);
    printf("\n");

    // "abcd" -> a1b1c1d1 형태로 출력
    compressRLE("abcd", 0);
    printf("\n");

    // "aaaaabbbaaaa" -> a5b3a4 형태로 출력
    compressRLE("aaaaabbbaaaa", 0);
    printf("\n");

    return 0;
}
