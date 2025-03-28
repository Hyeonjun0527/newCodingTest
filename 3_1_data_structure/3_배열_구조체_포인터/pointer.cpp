#include <iostream>
using namespace std;

// 포인터를 파라미터로 받는 함수
void pointer_func(int *p) {
  cout << "Inside pointer_func(int* p)" << endl;
  cout << "p   (address stored in p)    : " << p << endl;
  cout << "*p  (value pointed by p)     : " << *p << endl;
  cout << "&p  (address of pointer p)   : " << &p << endl;
  cout << "-------------------------------------" << endl;
}

// 포인터를 파라미터로 받는 함수2
void pointer_func2(int *p) {
  cout << "Inside pointer_func(int *p)" << endl;
  cout << "p   (address stored in p)    : " << p << endl;
  cout << "*p  (value pointed by p)     : " << *p << endl;
  cout << "&p  (address of pointer p)   : " << &p << endl;
  cout << "-------------------------------------" << endl;
}

int main() {
  int num = 20;
  int *p = &num;

  // 각 경우의 수별로 출력
  cout << "num                            : " << num << endl;
  cout << "&num (address of num)         : " << &num << endl;
  cout << "-------------------------------------" << endl;

  cout << "p   (address stored in p)      : " << p << endl;
  cout << "*p  (value pointed by p)       : " << *p << endl;
  cout << "&p  (address of pointer p)     : " << &p << endl;
  cout << "-------------------------------------" << endl;

  // 포인터를 파라미터로 전달하여 출력
  pointer_func(p);

  pointer_func2(p);

  return 0;
}