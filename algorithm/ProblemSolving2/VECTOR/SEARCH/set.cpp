#include <iostream>
#include <set>
#include <string>

int main() {
    std::set<std::string> mySet;

    // 삽입 (O(log n))
    mySet.insert("apple");
    mySet.insert("banana");
    mySet.insert("orange");
    mySet.insert("banana"); // 중복된 값은 무시됨

    // 탐색 (O(log n))
    if (mySet.count("banana")) {
        std::cout << "banana is in the set." << std::endl;
    }

    // 삭제 (O(log n))
    mySet.erase("orange");

    // 순회 (정렬된 순서)
    std::cout << "Elements in the set: ";
    for (const auto& element : mySet) {
        std::cout << element << " ";
    }
    std::cout << std::endl; // 출력: apple banana

    return 0;
}