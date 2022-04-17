#include "mempool.h"

void mempool::push(transaction t)
{
    string transaction_sha256 = transaction::sha256(t);
    transactions_sha256_.push_back(transaction_sha256);
    transactions_[transaction_sha256] = t;
}

transaction mempool::pop()
{
    if (transactions_sha256_.empty())
        throw std::runtime_error("mempool is empty");

    string first_hash = transactions_sha256_.front();
    transaction ret = transactions_[first_hash];

    remove_by_hash(first_hash);

    return ret;
}

void mempool::remove_by_hash(string hash)
{
    auto to_remove = std::find(transactions_sha256_.begin(), transactions_sha256_.end(), hash);
    if(to_remove != transactions_sha256_.end()) {
        auto amount = contains(*to_remove);
        transactions_sha256_.erase(to_remove);

        if(amount == 1) {
            transactions_.erase(*to_remove);
        }
    }
}

int mempool::contains(string transaction_sha256)
{
    return count_if(transactions_sha256_.begin(), transactions_sha256_.end(), [=](string s) { return s == transaction_sha256; });
}

size_t mempool::size()
{
    return transactions_sha256_.size();
}
