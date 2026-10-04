// 输入有多组数据，没有告诉一共有多少组，需要不断读取，一直到输入结束

#include <iostream>
using namespace std;

int main(){
    long long a, b;

    //每成功读取一对整数，就执行一次循环
    while(cin >> a >> b){

        cout << a + b << endl;
    }

    return 0;
}