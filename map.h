//
// Created by 93539 on 2023/8/7.
//

#ifndef MAP_SET_MAP_H
#define MAP_SET_MAP_H

#include "RBTree.h"

namespace wyp {
    template<class K, class V>
    class map {
        struct mapKeyOfT {
            const K &operator()(const pair<const K, V> &kv) {
                return kv.first;
            }
        };

    public:
        typedef typename RBTree<K, pair<const K, V>, mapKeyOfT>::iterator iterator;
        typedef typename RBTree<K, pair<const K, V>, mapKeyOfT>::const_iterator const_iterator;

        iterator begin() {
            return _t.begin();
        }

        iterator end() {
            return _t.end();
        }

        const_iterator begin() const {
            return _t.begin();
        }

        const_iterator end() const {
            return _t.end();
        }

        pair<iterator, bool> insert(const pair<const K, V> &kv) {
            return _t.insert(kv);
        }

        V &operator[](const K &key) {
            pair<iterator, bool> ret = insert(make_pair(key, V()));
            return ret.first->second;
        }

    private:
        RBTree<K, pair<const K, V>, mapKeyOfT> _t;
    };

} // wyp

#endif //MAP_SET_MAP_H
