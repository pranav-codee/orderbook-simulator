#include "engine.h"

void MatchEngine::onNewOrder(const Order& o) {
    books[o.ticker].addOrder(o);
}

void MatchEngine::onCancel(const Ticker& t, OrderID id) {
    auto it = books.find(t);
    if (it != books.end()) {
        it->second.cancelOrder(id);
    }
}

bool MatchEngine::onCancel(OrderID id) {
    for (auto& kv : books) {
        if (kv.second.cancelOrder(id)) return true;
    }
    return false;
}

void MatchEngine::runMatching() {
    for (auto& kv : books) {
        kv.second.match();
    }
}
