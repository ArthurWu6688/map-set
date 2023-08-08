#include <iostream>
#include "set.h"
#include "map.h"

void test_set() {
    int a[] = {4, 2, 6, 1, 3, 5, 15, 7, 16, 4};
    wyp::set<int> s;
    for (auto &e: a) {
        s.insert(e);
    }
//    for (auto e: s) {
//        cout << e << " ";
//    }
//    cout << endl;
    wyp::set<int>::iterator it = s.begin();
    while (it != s.end()) {
        cout << *it << " ";
        ++it;
    }
    cout << endl;
}

void test_map() {
    int a[] = {4, 2, 6, 1, 3, 5, 15, 7, 16, 4};
    wyp::map<int, int> m;
    for (auto &e: a) {
        m.insert(make_pair(e, e));
    }

//    for (auto e: m) {
//        cout << e.first << ":" << e.second << " ";
//    }
//    cout << endl;
    wyp::map<int, int>::iterator it = m.begin();
    while (it != m.end()) {
        cout << it->first << ":" << it->second << " ";
        ++it;
    }
    cout << endl;

    wyp::map<string, int> count;
    string arr[] = {"Æ»¹û", "Î÷¹Ï", "Ïã½¶", "²ÝÝ®", "Æ»¹û", "Î÷¹Ï", "Æ»¹û",
                    "Æ»¹û", "Î÷¹Ï", "Æ»¹û", "Ïã½¶", "Æ»¹û", "Ïã½¶"};
    for (auto &e: arr) {
        count[e]++;
    }
    for (auto &e: count) {
        cout << e.first << ":" << e.second << endl;
    }
}

int main() {
    cout << "------------- test set -------------" << endl;
    test_set();
    cout << "------------- test map -------------" << endl;
    test_map();

    return 0;
}
