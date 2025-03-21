/* 
### 정렬된 배열에서 특정 값의 개수 세기

upper_bound와 lower_bound의 반환 값 차이를 계산하여 
특정 값이 정렬된 배열에 몇 개 있는지 O(log n) 시간에 알 수 있습니다.
 map을 사용한다면, 모든 원소를 순회하면서 개수를 세야 하므로 O(n) 시간이 걸립니다.

*/

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> arr = {2, 4, 5, 5, 5, 7, 9};

    // 5의 개수 세기
    int count = std::upper_bound(arr.begin(), arr.end(), 5) - std::lower_bound(arr.begin(), arr.end(), 5);
    std::cout << "Count of 5: " << count << std::endl; // 3

    return 0;
}