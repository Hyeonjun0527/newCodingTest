#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

int main() {
    int N, M;

    // 입력 처리
    std::cin >> N >> M;
    std::unordered_map<std::string, int> nameToId; // 이름 -> ID
    std::vector<std::string> idToName(N + 1);      // ID -> 이름 (1-based indexing)

    for (int i = 1; i <= N; ++i) {
        std::string name;
        std::cin >> name;
        nameToId[name] = i;
        idToName[i] = name;
    }

    // 쿼리 처리
    for (int i = 0; i < M; ++i) {
        std::string query;
        std::cin >> query;

        // 숫자 입력 (ID로 이름 찾기)
        if (isdigit(query[0])) {
            int id = std::stoi(query);
            std::cout << idToName[id] << "\n";
        }
        // 문자열 입력 (이름으로 ID 찾기)
        else {
            std::cout << nameToId[query] << "\n";
        }
    }

    return 0;
}


/* 

문제 설명 (도감)

당신은 포켓몬 도감을 만드는 프로그램을 작성해야 합니다. 도감에는 포켓몬의 이름과 고유 ID 번호가 저장됩니다. 프로그램은 다음 두 가지 유형의 쿼리를 처리해야 합니다.

이름으로 ID 찾기: 포켓몬의 이름이 주어지면, 해당 포켓몬의 ID 번호를 출력합니다.
ID로 이름 찾기: 포켓몬의 ID 번호가 주어지면, 해당 포켓몬의 이름을 출력합니다.
입력

첫 번째 줄에는 포켓몬의 수 N (1 ≤ N ≤ 100,000)과 쿼리의 수 M (1 ≤ M ≤ 100,000)이 주어집니다.
다음 N개의 줄에는 각 포켓몬의 이름이 주어집니다. 포켓몬의 이름은 알파벳 대소문자로만 이루어져 있으며, 길이는 1 이상 20 이하입니다. 같은 이름의 포켓몬은 없습니다.
다음 M개의 줄에는 쿼리가 주어집니다. 쿼리는 포켓몬의 이름 또는 ID 번호입니다. ID 번호는 1부터 N까지의 자연수입니다.
출력

각 쿼리에 대한 답을 한 줄에 하나씩 출력합니다. 이름으로 ID를 찾는 쿼리의 경우 ID 번호를, ID로 이름을 찾는 쿼리의 경우 이름을 출력합니다.

예제 입력


5 4
Bulbasaur
Ivysaur
Venusaur
Charmander
Charmeleon
2
Charmeleon
3
Bulbasaur
예제 출력


Ivysaur
5
Venusaur
1
해설

이 문제는 잦은 탐색이 발생하는 상황을 보여줍니다. std::unordered_map을 사용하여 이름과 ID를 효율적으로 연결합니다.

nameToId: 포켓몬 이름을 키로, ID 번호를 값으로 저장하는 unordered_map입니다. 이름으로 ID를 찾는 쿼리를 O(1) (평균) 시간에 처리할 수 있습니다.
idToName: ID 번호를 인덱스로, 이름을 값으로 저장하는 vector입니다. ID로 이름을 찾는 쿼리를 O(1) 시간에 처리할 수 있습니다.
isdigit() 함수를 사용하여 입력 쿼리가 숫자인지 문자열인지 판별합니다. 숫자라면 std::stoi를 사용하여 문자열을 정수로 변환하고 idToName 벡터에서 이름을 찾습니다. 문자열이라면 nameToId 맵에서 ID를 찾습니다.

시간 복잡도

도감 만들기: O(N) (평균)
각 쿼리 처리: O(1) (평균)
총 시간 복잡도: O(N + M) (평균)
이 코드는 백준 온라인 저지에서 유사한 문제를 푸는 데 사용할 수 있는 템플릿 역할을 할 수 있습니다. 문제의 요구사항에 맞게 입출력 형식과 자료구조를 조정하면 됩니다.
*/