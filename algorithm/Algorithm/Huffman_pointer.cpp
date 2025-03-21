#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 허프만 트리의 노드 구조체
struct Node {
    long long frequency;        // 이 노드 아래 리프들의 빈도수 합
    int symbol;                 // 심볼 인덱스 (-1은 내부 노드)
    vector<Node*> children;     // 자식 노드들

    // 리프 노드 생성자
    Node(long long freq, int sym) : frequency(freq), symbol(sym) {}

    // 내부 노드 생성자
    Node(long long freq) : frequency(freq), symbol(-1) {}
};

// 우선순위 큐를 위한 비교자 (빈도수에 따른 최소 힙)
struct CompareNode {
    bool operator()(Node* const& n1, Node* const& n2) {
        if (n1->frequency != n2->frequency)
            return n1->frequency > n2->frequency;
        else
            return n1->symbol > n2->symbol; // 일관된 순서를 위해 심볼 인덱스 비교
    }
};

// 허프만 트리를 순회하여 코드 길이를 계산하는 함수
void calculateCodeLengths(Node* node, int depth, vector<int>& codeLengths) {
    if (!node) return;
    if (node->children.empty()) {
        // 리프 노드인 경우
        codeLengths[node->symbol] = depth;
    } else {
        // 내부 노드인 경우 자식들을 순회
        for (Node* child : node->children) {
            calculateCodeLengths(child, depth + 1, codeLengths);
        }
    }
}

// 허프만 트리를 삭제하고 메모리를 해제하는 함수
void deleteTree(Node* node) {
    if (!node) return;
    for (Node* child : node->children) {
        deleteTree(child);
    }
    delete node;
}

int main() {
    int T; // 테스트 케이스 수
    cin >> T;
    while (T--) {
        int N, K; // 심볼의 수와 인코딩할 진법
        cin >> N >> K;
        vector<long long> C(N); // 각 심볼의 빈도수

        // 빈도수 입력
        for (int i = 0; i < N; ++i) {
            cin >> C[i];
        }

        // 예외 처리: 심볼이 하나인 경우
        if (N == 1) {
            cout << 0 << endl;
            continue;
        }

        // 허프만 트리를 만들기 위한 우선순위 큐 (최소 힙)
        priority_queue<Node*, vector<Node*>, CompareNode> pq;

        // 리프 노드로 우선순위 큐 초기화
        for (int i = 0; i < N; ++i) {
            pq.push(new Node(C[i], i));
        }

        // (K - 1)로 나눈 나머지가 0이 되도록 노드 수 조정
        int s = K - 1;
        if (s <= 0) s = 1; // K가 1인 경우 0으로 나누는 것을 방지
        int numLeaves = pq.size();
        int padding = (s - (numLeaves - 1) % s) % s;

        // 필요한 경우 빈도수가 0인 더미 노드 추가 (고유한 심볼 인덱스 할당)
        for (int i = 0; i < padding; ++i) {
            pq.push(new Node(0, N + i)); // 더미 노드의 심볼 인덱스는 N 이상으로 설정
        }

        // 허프만 트리 생성
        while (pq.size() > 1) {
            vector<Node*> nodes;
            long long sumFreq = 0;

            // 가장 작은 빈도수의 노드 최대 K개 제거
            for (int i = 0; i < K && !pq.empty(); ++i) {
                Node* node = pq.top();
                pq.pop();
                nodes.push_back(node);
                sumFreq += node->frequency;
            }

            // 이 노드들을 자식으로 가지는 새로운 내부 노드 생성
            Node* newNode = new Node(sumFreq);
            newNode->children = nodes;
            pq.push(newNode);
        }

        // 허프만 트리의 루트 노드
        Node* root = pq.top();
        pq.pop();

        // 각 심볼에 대한 코드 길이 계산
        vector<int> codeLengths(N + padding, 0);
        calculateCodeLengths(root, 0, codeLengths);

        // 총 인코딩 길이 계산
        long long totalCost = 0;
        for (int i = 0; i < N; ++i) {
            int codeLength = codeLengths[i];
            totalCost += C[i] * codeLength;
        }

        // 결과 출력
        cout << totalCost << endl;

        // 메모리 해제
        deleteTree(root);
    }
    return 0;
}
