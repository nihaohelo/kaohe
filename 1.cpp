//1.题目描述
//现有 n 个正整数，要求出这 n 个正整数中的第 k 个最小整数（相同大小的整数只计算一次）。 
// 输入格式
//第一行为 n 和 k; 第二行开始为 n 个正整数的值，整数间用空格隔开。
// 输出格式
//第 k 个最小整数的值；若无解，则输出 NO RESULT。
#include <iostream>
#include <set>
#include <vector>
using namespace std;
int main() {
    int n, k;
    cin >> n >> k;

    set<int> unique_numbers;
    int number;


    for (int i = 0; i < n; ++i) {
        cin >> number;
        unique_numbers.insert(number);
    }


    if (k > unique_numbers.size()) {
        cout << "NO RESULT" << std::endl;
        return 0;
    }


    vector<int> sorted_numbers(unique_numbers.begin(), unique_numbers.end());


    cout << sorted_numbers[k - 1] << std::endl;

    return 0;
}
