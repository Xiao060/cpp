#include <cstdlib>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main(int argc, char *argv[]) {

  int *p = (int *)malloc(sizeof(int));
  *p = 200;
  cout << *p << endl;
  
  cout << "Hello test World!" << endl;

  return 0;
}