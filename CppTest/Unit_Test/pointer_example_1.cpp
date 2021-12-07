#include <iostream>

using namespace std;

int main(void) {
    // 設定 n 為整數 11
    int n = 11;
    cout << "n: "<< n << endl;
    cout << "----------" << endl;
    
    // 設定 nPtr 為指向 n 的指標
    int *np = &n; // & 是取址運算子
    cout << "int *np = &n"<<endl;
    cout << "np: "<< np << endl;
    cout << "*np: "<< *np << endl; 
    cout << "----------" << endl;
    // 設定 t 取得從 np 位址指向的值
    int t = *np; // * 是反參考運算子
    cout << "int t = *np" << endl;
    cout << t << endl;
    
    return 0;
}