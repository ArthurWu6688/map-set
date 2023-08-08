//
// Created by 93539 on 2023/8/6.
//

#ifndef RBTREE_RBTREE_H
#define RBTREE_RBTREE_H

using namespace std;

namespace wyp {
    enum Colour {
        RED,
        BLACK,
    };

    template<class T>
    struct RBTreeNode {
        T _data;
        RBTreeNode<T> *_left;
        RBTreeNode<T> *_right;
        RBTreeNode<T> *_parent;
        Colour _col;

        RBTreeNode(const T &data)
                : _data(data),
                  _left(nullptr),
                  _right(nullptr),
                  _parent(nullptr),
                  _col(RED) {

        }
    };

    template<class T, class Ref, class Ptr>
    struct __RBTreeIterator {
        typedef RBTreeNode<T> Node;
        typedef __RBTreeIterator<T, Ref, Ptr> self;
        typedef __RBTreeIterator<T, T &, T *> iterator;
        Node *_node;

        Ref operator*() {
            return _node->_data;
        }

        Ptr operator->() {
            return &_node->_data;
        }

        self &operator++() {
            if (_node->_right) {
                Node *min = _node->_right;
                while (min->_left) {
                    min = min->_left;
                }
                _node = min;
            } else {
                Node *cur = _node;
                Node *parent = cur->_parent;
                while (parent && cur == parent->_right) {
                    cur = cur->_parent;
                    parent = parent->_parent;
                }
                _node = parent;
            }
            return *this;
        }

        self &operator--() {
            if (_node->_left) {
                Node *max = _node->_left;
                while (max->_right) {
                    max = max->_right;
                }
                _node = max;
            } else {
                Node *cur = _node;
                Node *parent = cur->_parent;
                while (parent && cur == parent->_left) {
                    cur = cur->_parent;
                    parent = parent->_parent;
                }
                _node = parent;
            }
            return *this;
        }

        bool operator!=(const self &s) const {
            return _node != s._node;
        }

        bool operator==(const self &s) const {
            return _node == s._node;
        }

        __RBTreeIterator(Node *node)
                : _node(node) {

        }

        // ��ͨ����������ʱ����һ����������
        // const����������ʱ����һ�����죬֧������ͨ����������const������
        __RBTreeIterator(const iterator &s)
                : _node(s._node) {

        }
    };

    template<class K, class T, class KeyOfT>
    class RBTree {
        typedef RBTreeNode<T> Node;

    public:
        typedef __RBTreeIterator<T, T &, T *> iterator;
        typedef __RBTreeIterator<T, const T &, const T *> const_iterator;

        iterator begin() {
            Node *left = _root;
            while (left && left->_left) {
                left = left->_left;
            }
            return iterator(left);
        }

        iterator end() {
            return iterator(nullptr);
        }

        const_iterator begin() const {
            Node *left = _root;
            while (left && left->_left) {
                left = left->_left;
            }
            return const_iterator(left);
        }

        const_iterator end() const {
            return const_iterator(nullptr);
        }

    public:
        RBTree()
                : _root(nullptr) {

        }

        pair<iterator, bool> insert(const T &data) {
            if (_root == nullptr) {
                _root = new Node(data);
                _root->_col = BLACK;
                return make_pair(iterator(_root), true);
            }
            KeyOfT kot;
            Node *parent = nullptr;
            Node *cur = _root;
            while (cur != nullptr) {
                if (kot(data) < kot(cur->_data)) {
                    parent = cur;
                    cur = cur->_left;
                } else if (kot(data) > kot(cur->_data)) {
                    parent = cur;
                    cur = cur->_right;
                } else {
                    return make_pair(iterator(cur), false);
                }
            }
            cur = new Node(data);
            Node *newNode = cur;
            cur->_col = RED;
            if (kot(cur->_data) < kot(parent->_data)) {
                parent->_left = cur;
            } else {
                parent->_right = cur;
            }
            cur->_parent = parent;

            while (parent != nullptr && parent->_col == RED) {
                Node *grandfather = parent->_parent;
                if (parent == grandfather->_left) { //parentΪgrandfather����
                    Node *uncle = grandfather->_right;
                    if (uncle != nullptr && uncle->_col == RED) { //���һ curΪ�죬pΪ�죬gΪ�ڣ�u������Ϊ��
                        parent->_col = uncle->_col = BLACK;
                        grandfather->_col = RED;
                        cur = grandfather;
                        parent = cur->_parent;
                    } else { // �������
                        if (cur == parent->_left) { //����� curΪ�죬pΪ�죬gΪ�ڣ�u������/uΪ�ڣ�gpc��ͬһ��
                            _RotateR(grandfather);
                            parent->_col = BLACK;
                            grandfather->_col = RED;
                        } else { //����� curΪ�죬pΪ�죬gΪ�ڣ�u������/uΪ�ڣ�gpc����ͬһ��
                            _RotateL(parent);
                            _RotateR(grandfather);
                            cur->_col = BLACK;
                            grandfather->_col = RED;
                        }
                        break;
                    }
                } else if (parent == grandfather->_right) { //parentΪgrandfather�Һ���
                    Node *uncle = grandfather->_left;
                    if (uncle != nullptr && uncle->_col == RED) { //���һ curΪ�죬pΪ�죬gΪ�ڣ�u������Ϊ��
                        parent->_col = uncle->_col = BLACK;
                        grandfather->_col = RED;
                        cur = grandfather;
                        parent = cur->_parent;
                    } else { // ������� ����� ���� �����
                        if (cur == parent->_right) { //curΪ�죬pΪ�죬gΪ�ڣ�u������/uΪ�ڣ�gpc��ͬһ��
                            _RotateL(grandfather);
                            grandfather->_col = RED;
                            parent->_col = BLACK;
                        } else { //����� curΪ�죬pΪ�죬gΪ�ڣ�u������/uΪ�ڣ�gpc����ͬһ��
                            _RotateR(parent);
                            _RotateL(grandfather);
                            cur->_col = BLACK;
                            grandfather->_col = RED;
                        }
                        break;
                    }
                }
            }
            //���ڵ��Ϊ��ɫ
            _root->_col = BLACK;
            return make_pair(iterator(newNode), true);
        }

        void InOrder() {
            _InOrder(_root);
        }

        bool IsBalance() {
            return _IsBalance();
        }

    private:
        void _RotateR(Node *parent) {
            Node *subL = parent->_left;
            Node *subLR = subL->_right;
            parent->_left = subLR;
            if (subLR) {
                subLR->_parent = parent;
            }
            Node *ppNode = parent->_parent;
            subL->_right = parent;
            parent->_parent = subL;
            if (ppNode == nullptr) {
                _root = subL;
                _root->_parent = nullptr;
            } else {
                if (ppNode->_left == parent) {
                    ppNode->_left = subL;
                } else {
                    ppNode->_right = subL;
                }
                subL->_parent = ppNode;
            }
        }

        void _RotateL(Node *parent) {
            Node *subR = parent->_right;
            Node *subRL = subR->_left;

            parent->_right = subRL;
            if (subRL != nullptr) {
                subRL->_parent = parent;
            }

            Node *ppNode = parent->_parent;
            subR->_left = parent;
            parent->_parent = subR;
            if (ppNode == nullptr) {
                _root = subR;
                _root->_parent = nullptr;
            } else {
                if (ppNode->_left == parent) {
                    ppNode->_left = subR;
                } else {
                    ppNode->_right = subR;
                }
                subR->_parent = ppNode;
            }
        }

        void _InOrder(Node *root) {
            if (root == nullptr) {
                return;
            }
            _InOrder(root->_left);
            cout << root->_kv.first << ":" << root->_kv.second << endl;
            _InOrder(root->_right);
        }

        bool _IsBalance() {
            if (_root == nullptr) {
                return true;
            }
            if (_root->_col != BLACK) {
                return false;
            }
            int ref = 0;
            Node *left = _root;
            while (left) {
                if (left->_col == BLACK) {
                    ++ref;
                }
                left = left->_left;
            }
            return check(_root, 0, ref);
        }

        bool check(Node *root, int blackNum, const int ref) {
            if (root == nullptr) {
                if (blackNum != ref) {
                    cout << "Υ�����򣺱���·�����ֺ�ɫ�ڵ������������·�������" << endl;
                    return false;
                }
                return true;
            }
            if (root->_col == RED && root->_parent->_col == RED) {
                cout << "Υ�����򣺳���������ɫ�ڵ�" << endl;
                return false;
            }
            if (root->_col == BLACK) {
                ++blackNum;
            }
            return check(root->_left, blackNum, ref)
                   && check(root->_right, blackNum, ref);
        }

    private:
        Node *_root;
    };
}
#endif //RBTREE_RBTREE_H


