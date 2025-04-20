#include <stdio.h>

// 중간에는 임시공간, 2번째 인자 4번째 인자에 넣는게 어디서 어디로 이동하는지를
// 의미함. hanoi_tower(n-1,from,to,tmp)는 from에 있는 n-1개 원판을 tmp로 옮기는
// 걸 의미해. 물론 한번에는 -1만큼만 하는거지. 하지만, 재귀적으로 작동함.
// printf("원판1을 %c에서 %c로 옮긴다.\n", from, to); 이게 아무것도 안하고
// print만 하는거 아니냐 하는데 했다고 가정하는거임. 아주 쉽게 생각하면 돼
// n-1개를 from에서 tmp로 그리고 tmp에서 to로
void hanoi_tower(int n, char from, char tmp, char to) {
    if (n == 1)
        // 마지막 남은 원판
        printf("프1 : 원판1을 %c에서 %c로 옮긴다.\n", from, to);
    else {
        // n-1개 원판을 tmp로
        // printf가 여기 있으면 큰 원판을 넘기려하니까 안되겟지
        hanoi_tower(n - 1, from, to, tmp);
        // 가장 큰 원판(n번째를)을 목적지로
        // 스택이니까 여기에 프린트 넣어줘야 작은 원판부터 옮기겟지.
        printf("프2 : 원판%d를 %c에서 %c로 옮긴다.\n", n, from, to);
        // n-1개 원판을 목적지로
        hanoi_tower(n - 1, tmp, from, to);
    }
}

// n=2일때로 두고 생각하고 함수짜면 쉽다.
// n=3,4,5,6....일때도 n=2일때와 큰 논리는 같다.
// 결국 A->B A->C B->C이다.
int main(void) {
    hanoi_tower(4, 'A', 'B', 'C');
    return 0;
}

/*
hanoi_tower(4, A, B, C)
├─ hanoi_tower(3, A, C, B)
│  ├─ hanoi_tower(2, A, B, C)
│  │  ├─ hanoi_tower(1, A, C, B)
│  │  │   └─ move 1: A→B
│  │  ├─ move 2: A→C
│  │  └─ hanoi_tower(1, B, A, C)
│  │      └─ move 1: B→C
│  ├─ move 3: A→B
│  └─ hanoi_tower(2, C, A, B)
│     ├─ hanoi_tower(1, C, B, A)
│     │   └─ move 1: C→A
│     ├─ move 2: C→B
│     └─ hanoi_tower(1, A, C, B)
│         └─ move 1: A→B
├─ move 4: A→C
└─ hanoi_tower(3, B, A, C)
   ├─ hanoi_tower(2, B, C, A)
   │  ├─ hanoi_tower(1, B, A, C)
   │  │   └─ move 1: B→C
   │  ├─ move 2: B→A
   │  └─ hanoi_tower(1, C, B, A)
   │      └─ move 1: C→A
   ├─ move 3: B→C
   └─ hanoi_tower(2, A, B, C)
      ├─ hanoi_tower(1, A, C, B)
      │   └─ move 1: A→B
      ├─ move 2: A→C
      └─ hanoi_tower(1, B, A, C)
          └─ move 1: B→C
*/