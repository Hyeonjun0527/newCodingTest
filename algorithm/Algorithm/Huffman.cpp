#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node {
    long long freq;        // 이 노드의 리프 노드 포함 모든 빈도수
    int node_num;                 // 노드 번호 -1은 내부 노드
    vector<Node> children;      // 자식 노드들

    Node(long long freq, int node_num) : freq(freq), node_num(node_num) {}

    Node(long long freq) : freq(freq), node_num(-1) {}

    bool operator<(const Node& o) const {
        if (freq != o.freq)
            return freq > o.freq; // 빈도수가 작은거부터 오름차
        return node_num > o.node_num;           // 빈도수 같으면 노드넘 작은거.
    }
};


// 모든 노드 방문해서 코드 길이 각각 계산해서 저장
// 왜 visited 없나? 트리를 방문하는 DFS에서는 사이클이 없으므로 방문기록을 안해도 됨. 무한루프 발생 안함.
void calculateCodeLengths(const Node& node, int depth, vector<int>& code_lengths) {
    if (node.children.empty()) {
        // 끝까지 옴
        code_lengths[node.node_num] = depth;
    } else {

        for (const Node& child : node.children) {
            calculateCodeLengths(child, depth + 1, code_lengths);
        }
    }
}

int main() {
    int T; // 테스트 케이스 수
    cin >> T;
    while (T--) {
        int N, K; // 노드의 수와 K진법
        cin >> N >> K;
        vector<long long> Frequency(N); // 빈도수

        // 빈도수 입력
        for (int i = 0; i < N; ++i) {
            cin >> Frequency[i];
        }

        priority_queue<Node> pq;


        // 문제에서 리프 노드에 대한 정보, 리프노드 개수를 간접적으로 제공
        // 리프 노드부터 우선순위 큐 초기화
        for (int i = 0; i < N; ++i) {
            pq.push(Node(Frequency[i], i));//빈도수랑 노드번호(심볼)을 넣어줘.
        }

        // (K - 1)로 나눈 나머지가 0이 되도록 노드 수 조정
        //전체 노드 N
        int L = pq.size();
        //이제 더미노드를 얼만큼 추가해야되냐 이건데 그거는

        //N: 전체노드
        //N-1 : 간선개수
        //I : 내부노드 수
        //L : 리프노드 수
        //K : 한 내부노드에 딸린 리프노드 수
        //L-1 % K-1 = 0이 되어야만
        //L-1 % K-1 = 0이 되어야만 하는 L-1을 만들어야 해.
        //현재 K L로. 부족한 더미노드의 개수가 K - 1 에서
        //                        3     -    (   %    3) = 1
        //                        1     -     ( 3 % 1)  =
        //여기서 마지막에 K-1 를 %해야하는 이유
        //L-1 = 8, K - 1 = 3이라고 봅시다.
        // 8 % 3 = 0이 되어야만 해. 그러면 8에서 몇을 빼야 될까? 2다.
        // 8에서 몇을 빼면 3의 배수가 될까?랑 같은 말이잖아.
        // 2를 빼야 된다.  (8 % 3) = 2
        //그런데 우리는 얼만큼 추가하느냐를 보는거잖아. 8에서 몇을 더해야할까? 1이다.
        //그 1을 일반적으로 구해야되잖아.
        // 1 = 3 - ( 8 % 3 ) 이겠지?
        // 그래서 dummy = (K-1) - ((L-1) % (K-1))가 돼.
        /*
        K=4 (4진법 트리)
        L=13 (리프 노드 13개)
        나머지 연산을 추가하는 이유는, 계산 결과가 (K - 1)이 될 수 있기 때문

        3 - 12 % 3
        3 - 0
        3 - 0 = 3
        더미노드 3개를 추가할 필요는 없음
         */
        int dummy_node_count = ((K - 1) - ((L - 1) % (K - 1))) % (K - 1);


        // 빈도수가 0인 더미 노드 추가함
        for (int i = 0; i < dummy_node_count; ++i) {
            pq.push(Node(0, N + i)); // 더미 노드의 심볼 인덱스는 N 이상으로 설정함
        }

        // 허프만 트리 생성
        while (pq.size() > 1) {
            vector<Node> nodes;
            long long sumFreq = 0;

            // 가장 작은 빈도수의 노드 최대 K개 제거
            for (int i = 0; i < K && !pq.empty(); ++i) {
                Node node = pq.top();
                pq.pop();
                nodes.push_back(node);
                sumFreq += node.freq;
            }

            // 이 노드들을 자식으로 가지는 새로운 내부 노드 생성
            Node newNode(sumFreq);
            newNode.children = nodes;
            pq.push(newNode);
        }

        // 허프만 트리의 루트 노드
        Node root = pq.top();
        pq.pop();

        vector<int> codeLengths(N + dummy_node_count, 0);

        // 각 노드에 대한 코드 길이 계산
        calculateCodeLengths(root, 0, codeLengths);

        // 빈도수 x 코드길이
        long long totalCost = 0;
        for (int i = 0; i < N; ++i) {
            int codeLength = codeLengths[i];
            totalCost += Frequency[i] * codeLength;
        }

        cout << totalCost << endl;
    }
    return 0;
}


/*
#include <bits/stdc++.h>
using namespace std;

long long N, K, t, num, ans, sum;

int main() {
    cin >> t;
    while (t--) {
        cin >> N >> K;
        priority_queue<long long, vector<long long>, greater<long long>> pq;
        for (int i=0; i<N; i++) {
            cin >> num;
            pq.push(num);
        }

        int cnt = N;
        while (cnt > K){
            cnt = cnt - K + 1;
        }

        ans = 0; sum = 0;
        for (int i=0; i<cnt; i++){
            sum = sum + pq.top();
            pq.pop();
        }
        ans = ans + sum;
        pq.push(sum);

        while (pq.size() > 1) {
            sum = 0;
            for (int i=0; i<K && !pq.empty(); i++) {
                sum = sum + pq.top();
                pq.pop();
            }
            ans = ans + sum;
            pq.push(sum);
        }

        cout << ans <<"\n";
    }
}
 */