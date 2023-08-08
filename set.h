//
// Created by 93539 on 2023/8/7.
//

#ifndef MAP_SET_SET_H
#define MAP_SET_SET_H

#include "RBTree.h"

namespace wyp {
    template<class K>
    class set {
        struct setKeyOfT {
            const K &operator()(const K &key) {
                return key;
            }
        };

    public:
        typedef typename RBTree<K, K, setKeyOfT>::const_iterator iterator;
        typedef typename RBTree<K, K, setKeyOfT>::const_iterator const_iterator;

        iterator begin() const {
            return _t.begin();
        }

        iterator end() const {
            return _t.end();
        }

        pair<iterator, bool> insert(const K &key) {

            pair<typename RBTree<K, K, setKeyOfT>::iterator, bool> ret = _t.insert(key);
            return pair<iterator, bool>(ret.first, ret.second);
        }

    private:
        RBTree<K, K, setKeyOfT> _t;
    };

} // wyp

#endif //MAP_SET_SET_H
