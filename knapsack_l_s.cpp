//
//  knapsack_l_s.cpp
//  Fractal
//
//  Created by Slaviq on 29.09.2026.
//

#include <iostream>
#include <vector>
#include <algorithm>
struct Item {
    int id;
    int weight;
    int value;
    double density;
};

class KnapsackSolver {
public:
    KnapsackSolver(int cap, int num) : capacity(cap), n(num) {}
    void readItems() {
        for (int i = 0; i < n; ++i) {
            int w, v;
            std::cin >> w >> v;
            items.push_back({i, w, v, (double)v / w});
        }
    };
    int solve(){
    std::sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return a.density > b.density;
    });

    std::vector<bool> current_set(n, false);
    int current_weight = 0;
    int current_value = 0;

    for (int i = 0; i < n; ++i) {
        if (current_weight + items[i].weight <= capacity) {
            current_set[i] = true;
            current_weight += items[i].weight;
            current_value += items[i].value;
        }
    }

    bool improved = true;
    while (improved) {
        improved = false;
        for (int i = 0; i < n; ++i) {
            if (current_set[i]) {
                for (int j = 0; j < n; ++j) {
                    if (!current_set[j]) {
                        int weight_after = current_weight - items[i].weight + items[j].weight;
                        int value_after = current_value - items[i].value + items[j].value;
                        
                        if (weight_after <= capacity && value_after > current_value) {
                            current_set[i] = false;
                            current_set[j] = true;
                            current_weight = weight_after;
                            current_value = value_after;
                            improved = true;
                        }
                    }
                }
            }else {
                if (current_weight + items[i].weight <= capacity) {
                    current_set[i] = true;
                    current_weight += items[i].weight;
                    current_value += items[i].value;
                    improved = true;
                }
            }
        }
    }
    return current_value;
}

private:
    int capacity;
    int n;
    std::vector<Item> items;
};


int main() {
    int n, capacity;
    if (!(std::cin >> n >> capacity)) return 0;

    KnapsackSolver solver(capacity, n);
    solver.readItems();

    std::cout << solver.solve() << std::endl;

    return 0;
}
