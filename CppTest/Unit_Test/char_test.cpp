#include <iostream>
#include <sstream>

using namespace std;

int main()
{
  char s0[10] = "Hello";
  char s1[] = "Hello";
  const char* s2 = "Hello";
  string s3 = "Hello";
  stringstream s4;

  cout << " ------ s0 testing ------ " << endl;
  cout << typeid(s0).name() << ", " << s0 << endl;
  cout << " ------ s1 testing ------ " << endl;
  cout << typeid(s1).name() << ", " << s1 << endl;
  cout << " ------ s2 testing ------ " << endl;
  cout << typeid(s2).name() << ", " << s2 << endl;
  cout << " ------ s3 testing ------ " << endl;
  cout << typeid(s3).name() << ", " << s3 << endl;
  cout << " ------ s4 testing ------ " << endl;
  cout << typeid(s4).name() << endl;
  s4 << s3;
  cout << typeid(s4).name() << endl;
  cout << typeid(s4.str()).name() << ", " << s4.str() << endl;
  cout << typeid(s4.str().c_str()).name() << ", " << s4.str().c_str() << endl;

    return 0;
}