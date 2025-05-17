#include <stdio.h>
#include <string.h> /* strcpy 함수 원형 */
typedef struct student {
    int id;
    char name[40];
} student;

student s;

// student s /* s;
// student s */ s;

int main() {
    char a = 'A';
    char *p;
    p = &a;             // p는 a를 가르킨다 이거야
    printf("%c\n", *p); // 가리키는거에 뭐들어잇냐 이거야
    *p = 'B';           //*p는 a의 별명이야. a가 'B'로 바뀌어.
    printf("%c\n", *p);
    strcpy(s.name, "현준");
    printf("%s\n", s.name);

    int arr1[10] = {
        0,
    };
    int arr2[10] = {
        1,
    };
    int *k = arr1; // arr도 int *타입임
    k = arr2;
    // k는 arr에서 arr2를 가르키도록변경
    // arr1 = arr2; // arr1은 변경 불가
    printf("%c\n", *k);
}