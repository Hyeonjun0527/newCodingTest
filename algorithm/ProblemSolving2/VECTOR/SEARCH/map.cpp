#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<std::string, int> myMap;

    // 삽입 (O(log n))
    myMap["apple"] = 1;
    myMap["banana"] = 2;
    myMap["orange"] = 3;
    myMap["banana"] = 4; // 기존 키의 값을 업데이트

    // 탐색 (O(log n))
    if (myMap.count("banana")) {
        std::cout << "Value for banana: " << myMap["banana"] << std::endl; // 4
    }

    // 삭제 (O(log n))
    myMap.erase("orange");

    // 순회 (키를 기준으로 정렬된 순서)
    std::cout << "Elements in the map: " << std::endl;
    for (const auto& pair : myMap) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    } // apple: 1, banana: 4

    return 0;
}