#include <stdio.h>

void compressRLE(const char* s, int idx){
    
    while (s[idx] != '\0') {
        int cnt = 0;
        while (s[idx] ==s[idx+cnt]){
            cnt++;
        }
        printf("%c%d",s[idx],cnt);
        idx += cnt;
    }
}

int main(){
    compressRLE("aaabbcddd", 0);
    printf("\n");

    compressRLE("abcd", 0);
    printf("\n");

    compressRLE("aaaaabbbaaaa", 0);
    printf("\n");

    return 0;
}