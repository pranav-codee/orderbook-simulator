#pragma once
#include <unordered_map>
#include <vector>
#include <functional>
#include "../data_structures/avltree.h"
#include "../data_structures/vector_object_pool.h"
#include "pricelevel.h"
#include "constants.h"

using namespace std;

inline int64_t pricelevel_weight(const PriceLevel& p) {
    return static_cast<int64_t>(p.totalQty);
}

class OrderBook { // Class for order managing of a single ticker
public:
    void addOrder(const Order& o);
    bool cancelOrder(OrderID id);
    void match();
    vector<Trade> trades;

private:
    AVLTree<Price, PriceLevel, greater<Price>, decltype(pricelevel_weight)> bids{greater<Price>(), pricelevel_weight};
    AVLTree<Price, PriceLevel, less<Price>, decltype(pricelevel_weight)> asks{less<Price>(), pricelevel_weight};
    unordered_map<OrderID, OrderNode*> orderIndex;
    VectorObjectPool<OrderNode> nodePool{1024};
};
