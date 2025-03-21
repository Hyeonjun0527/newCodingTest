
/* 
### 값의 범위 찾기

정렬된 배열에서 특정 값 이상 특정 값 이하인 원소들의 범위를 찾고 싶을 때
lower_bound와 upper_bound를 조합하여 효율적으로 찾을 수 있습니다.
map은 특정 키가 있는지 없는지는 빠르게 알 수 있지만, 범위에 속하는 키들을 효율적으로 찾는 기능은 제공하지 않습니다.
*/

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> arr = {2, 4, 5, 5, 7, 9, 11, 13};

    // 5 이상 10 이하인 원소들의 범위를 찾기
    auto lower = std::lower_bound(arr.begin(), arr.end(), 5);   // 5
    auto upper = std::upper_bound(arr.begin(), arr.end(), 10);  // 11

    std::cout << "Range: ";
    for (auto it = lower; it != upper; ++it) {
        std::cout << *it << " "; // 5 5 7 9
    }
    std::cout << std::endl;

    return 0;
}