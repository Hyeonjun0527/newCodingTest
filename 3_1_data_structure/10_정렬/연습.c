#include <stdio.h>
#include <stdlib.h>
// 1리턴하면 a b순서로 정렬하라는거임
// 0리턴하면 b a 순서로 정렬하라는거임
// 이러면 function의 걸맞는 함수명은 is_less(a,b) 이다.
// a < b 면 is_less가 true를 리턴해야지.
// 함수사용하는 사용자는 a 가 b보다 작니? 라고 물어보는거야
// 함수는 대답하는거야. 맞아.
static inline int function(int a, int b) {
    return a < b;
}