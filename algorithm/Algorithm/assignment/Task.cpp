/*
min이 높은거부터 처리해야 되겟지 상식적으로.
그런데 민이 높은거부터 처리하다가 에너지를 다 써서 엄청 코스트 높은 걸 놓칠수도 있자나
그러니까 cost 높은거부터 처리하면 되나


지금 에너지를 정하고 그거로 해봐야되는거같은데
10의 5승 10의 4승이잖아.

최소에너지를 1로 정하고 돌려보고 그런 식으로는 최악이면 10^9이겠지 그래서안됨

최소에너지
일단 최소에너지는 min제일 큰거보단 커야대
코스트 sum 보다는 커야대






sum cost와 min을 더한 것과 sol을 비교하는걸 점진적으로 하는게 왜 옳냐
하면 초기에너지 최솟값은 당장 min이 될 수도 있고
아니면 sum_cost에 min을 더한게 될 수도 있어서
max (sol, task[i].min + sum_cost)


| max(sol, | task[i].min | +sum_cost) | ->  | sol | sum_cost |
| -------- | ----------- | ---------- | --- | --- | -------- |
| 0        | 13          | 0          | ->  | 13  | 6        |
| 13       | 4           | 6          | ->  | 13  | 8        |
| 13       | 6           | 8          | ->  | 14  | 12       |

 */

#include <bits/stdc++.h>
using namespace std;


struct task {
    int min;
    int cost;
};

int get_minimum_energy(int task_count, vector<task> &tasks){

    //작업의 진행순서가 상관이 없어. 그러면 먼저 정렬을 할까?
    //cost 나 min중에 가장 작은거 우선순위로 정렬하자.
    // i =0 일떄

    sort(tasks.begin(), tasks.end(), [](const task& a, const task& b) {
        return (a.min - a.cost) > (b.min - b.cost);
    });


    int sol = 0;
    int cum_cost = 0;

    for (int i = 0; i < task_count; i++) {
        sol = max(sol, tasks[i].min + cum_cost );
        cum_cost+=tasks[i].cost;
    }

    return sol;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    vector<task> tasks = {
        {4, 2}
        , {6, 4}
        , {13, 6}
    };

    // vector<task> tasks = {
    //     {1, 7}
    //     , {2, 8}
    //     , {3, 9}
    //     , {4, 10}
    //     , {5, 11}
    //     , {6, 12}
    // };

    cout << get_minimum_energy(tasks.size(), tasks);
    // cout << get_minimum_energy(6, tasks);
    
    
}

