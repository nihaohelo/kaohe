//2,题目描述 夏天到了，各家各户的用电量都增加了许多，相应的电费也交的更多了。小玉家 今天收到了一份电费通知单。
//小玉看到上面写：
//据闽价电 [2006]27 号规定，月 用电量在 150 千瓦时及以下部分按每千瓦时 0.44630 元执行，
//月用电量 在 151∼ 400 千瓦时的部分按每千瓦时 0.46630 元执行，
//月用电量在 401 千瓦时 及以上部分按每千瓦时 0.56630 元执行。
//小玉想自己验证一下，电费通知单上应 交电费的数目到底是否正确呢
//请编写一个程序，已知用电总计，根据电价规定， 计算出应交的电费应该是多少。

#include <iostream>
#include <iomanip> // 用于设置输出精度

using namespace std;

double calculateElectricityBill(int units) {
    const double tier1_price = 0.44630;
    const double tier2_price = 0.46630;
    const double tier3_price = 0.56630;
    const int tier1_limit = 150;
    const int tier2_limit = 400;
    double bill = 0.0;

    if (units <= tier1_limit) {
        bill = units * tier1_price;
    }
    else if (units <= tier2_limit) {
        bill = tier1_limit * tier1_price + (units - tier1_limit) * tier2_price;
    }
    else {
        bill = tier1_limit * tier1_price + (tier2_limit - tier1_limit) * tier2_price + (units - tier2_limit) * tier3_price;
    }

    return bill;
}

int main() {
    int units;
    cin >> units;
    double bill = calculateElectricityBill(units);
    cout << fixed << setprecision(11) << bill << endl;
    return 0;
