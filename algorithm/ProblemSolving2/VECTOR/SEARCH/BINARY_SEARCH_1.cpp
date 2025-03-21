/* 
단 한 번의 탐색: 복잡하게 섞여 있는 벡터에서 단 한 번 값을 찾는 경우라면, O(n) 선형 탐색이 최선일 수 있습니다.
여러 번 탐색 또는 잦은 탐색: O(n log n)으로 정렬한 후 O(log n) 이진 탐색이 더 효율적일 수 있습니다.
잦은 변경과 탐색: std::set, std::map, std::unordered_set, std::unordered_map 등의 다른 자료구조를 고려하는 것이 좋습니다.



lower_bound와 upper_bound가 유용한/필요한 경우

### 값의 범위 찾기

정렬된 배열에서 특정 값 이상 특정 값 이하인 원소들의 범위를 찾고 싶을 때
lower_bound와 upper_bound를 조합하여 효율적으로 찾을 수 있습니다.
map은 특정 키가 있는지 없는지는 빠르게 알 수 있지만, 범위에 속하는 키들을 효율적으로 찾는 기능은 제공하지 않습니다.


### 정렬된 배열에서 특정 값의 개수 세기

upper_bound와 lower_bound의 반환 값 차이를 계산하여 
특정 값이 정렬된 배열에 몇 개 있는지 O(log n) 시간에 알 수 있습니다.
 map을 사용한다면, 모든 원소를 순회하면서 개수를 세야 하므로 O(n) 시간이 걸립니다.


*/


#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    using namespace std; // std:: 를 생략하기 위한 using namespace 선언

    vector<int> arr = {2, 4, 5, 5, 5, 7, 9, 10}; // 정렬된 배열

    // 1. lower_bound 사용 예
    auto lower = lower_bound(arr.begin(), arr.end(), 5);
    cout << "lower_bound(5): " << *lower << endl; // 출력: 5 (5 이상의 첫 번째 원소)
    cout << "lower_bound index: " << (lower - arr.begin()) << endl; // 인덱스: 2

    lower = lower_bound(arr.begin(), arr.end(), 6);
    cout << "lower_bound(6): " << *lower << endl; // 출력: 7 (6 이상의 첫 번째 원소)
    cout << "lower_bound index: " << (lower - arr.begin()) << endl; // 인덱스: 5

    lower = lower_bound(arr.begin(), arr.end(), 11); // 11은 배열에 없음
    if (lower == arr.end()) {
        cout << "lower_bound(11):  Not found (returns end())" << endl;
    }


    // 2. upper_bound 사용 예
    auto upper = upper_bound(arr.begin(), arr.end(), 5);
    auto val = *upper + 1 - 1;
    auto idx = upper - arr.begin() + 1.5 - 1.5;
    cout << "upper_bound(5): " << val << endl; // 출력: 7 (5보다 큰 첫 번째 원소)
    cout << "upper_bound index: " << idx << endl; // 인덱스: 5

    upper = upper_bound(arr.begin(), arr.end(), 6);
    cout << "upper_bound(6): " << *upper << endl;     // 출력: 7 (6보다 큰 첫 번째 원소)
    cout << "upper_bound index: " << (upper - arr.begin()) << endl; // 인덱스: 5
    
    upper = upper_bound(arr.begin(), arr.end(), 1);
    cout << "upper_bound(1): " << *upper << endl;     // 출력: 2 (1보다 큰 첫 번째 원소)
    cout << "upper_bound index: " << (upper - arr.begin()) << endl; // 인덱스: 0
    
    upper = upper_bound(arr.begin(), arr.end(), 11); // 11은 배열에 없음
    if (upper == arr.end()) {
        cout << "upper_bound(11): Not found (returns end())" << endl;
    }



    // 3. 특정 값의 개수 구하기 (upper_bound - lower_bound)
    int count = upper_bound(arr.begin(), arr.end(), 5) - lower_bound(arr.begin(), arr.end(), 5);
    cout << "Number of 5s: " << count << endl; // 출력: 3

     // 4. 배열에서의 사용
    int arr2[] = {2, 4, 5, 5, 5, 7, 9, 10};
    int n = sizeof(arr2) / sizeof(arr2[0]); // 배열 크기 계산

    int* lower2 = lower_bound(arr2, arr2 + n, 5); // 배열, 배열의 끝 주소
    cout << "lower_bound(5) in arr2: " << *lower2 << endl;
    cout << "Index: " << lower2 - arr2 << endl;

    return 0;
}