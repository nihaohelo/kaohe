// 3题目描述你是某家咨询公司的项目经理，
// 现在你已经知道政府对某种商品的预期价格，
// 以及在各种价位上的销售情况。
// 要求你确定政府对此商品是应收税还是补贴的最少金额（也为整数），
// 才能使商家在这样一种政府预期的价格上，获取相对其他价位上的最大总利润。

#include <iostream>
#include <vector>
#include <limits>
#include <cmath>

using namespace std;

// 计算在给定价格下的销量
int calculate_sales(double price, const vector<pair<int, int>>& price_sales, int decrement, int base_price, int base_sales) {
    if (price <= base_price) return base_sales;
    for (size_t i = 0; i < price_sales.size(); ++i) {
        if (price < price_sales[i].first) {
            if (i == 0) return base_sales; // 如果价格低于最低已知价格，返回基础销量
            // 线性插值计算销量
            int lower_price = price_sales[i - 1].first;
            int lower_sales = price_sales[i - 1].second;
            int higher_price = price_sales[i].first;
            int higher_sales = price_sales[i].second;
            return lower_sales + (price - lower_price) * (higher_sales - lower_sales) / (higher_price - lower_price);
        }
    }
    // 如果价格高于最高已知价格，计算递减销量
    int highest_price = price_sales.back().first;
    int highest_sales = price_sales.back().second;
    return max(0, highest_sales - (price - highest_price) * decrement);
}

// 查找最小税收或补贴
int find_min_tax_or_subsidy(int expected_price, int cost, int base_sales, const vector<pair<int, int>>& price_sales, int decrement) {
    int max_profit = 0;
    int best_adjustment = 0;
    int best_price = expected_price;

    // 遍历所有已知价格点，计算最大总利润
    for (const auto& ps : price_sales) {
        int profit = (ps.first - cost) * calculate_sales(ps.first, price_sales, decrement, price_sales[0].first, base_sales);
        if (profit > max_profit) {
            max_profit = profit;
            best_price = ps.first;
        }
    }

    // 检查预期价格下的利润
    int profit_at_expected = (expected_price - cost) * calculate_sales(expected_price, price_sales, decrement, price_sales[0].first, base_sales);
    if (profit_at_expected == max_profit) {
        return 0; // 无需调整
    }

    // 尝试找到税收或补贴
    int min_adjustment = numeric_limits<int>::max();
    bool found_solution = false;
    for (int tax_or_subsidy = -10000; tax_or_subsidy <= 10000; ++tax_or_subsidy) {
        int adjusted_price = expected_price + tax_or_subsidy;
        int profit_at_adjusted = (adjusted_price - cost) * calculate_sales(adjusted_price, price_sales, decrement, price_sales[0].first, base_sales);
        if (profit_at_adjusted == max_profit) {
            found_solution = true;
            min_adjustment = min(min_adjustment, abs(tax_or_subsidy));
        }
    }

    return found_solution ? min_adjustment : -1;
}

int main() {
    int expected_price, cost, base_sales, decrement, price, sales;
    vector<pair<int, int>> price_sales;

    // 读取预期价格
    cin >> expected_price;
    // 读取成本和基础销量
    cin >> cost >> base_sales;
    // 读取价格-销量对
    while (true) {
        cin >> price >> sales;
        if (price == -1 && sales == -1) break;
        price_sales.emplace_back(price, sales);
    }
    // 读取超过最高价位的销量递减量
    cin >> decrement;

    // 计算结果
    int result = find_min_tax_or_subsidy(expected_price, cost, base_sales, price_sales, decrement);
    if (result == -1) {
        cout << "NO SOLUTION" << endl;
    } else {
        cout << result << endl;
    }

    return 0;
}
