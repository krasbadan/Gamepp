#pragma once
#include <utility>

template<typename Key, typename Value>
class Map {
private:
    struct Node {
        std::pair<const Key, Value> kv;
        Node* left = nullptr;
        Node* right = nullptr;
        Node* parent = nullptr;
        bool red;

        Node(Key k, Value v) : kv(k, v), red(true), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node* root = nullptr;

public:
    class iterator {
    private:
        Node* ptr;
        friend class Map;
    public:
        iterator(Node* p = nullptr) : ptr(p) {}

        std::pair<const Key, Value>& operator*() { return ptr->kv; }
        std::pair<const Key, Value>* operator->() { return &(ptr->kv); }

        bool operator==(const iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const iterator& other) const { return ptr != other.ptr; }

        iterator& operator++() {
            if (ptr->right) {
                ptr = ptr->right;
                while (ptr->left) ptr = ptr->left;
            } else {
                Node* p = ptr->parent;
                while (p && ptr == p->right) {
                    ptr = p;
                    p = p->parent;
                }
                ptr = p;
            }
            return *this;
        }
    };

    iterator begin() {
        Node* curr = root;
        while (curr && curr->left) curr = curr->left;
        return iterator(curr);
    }

    iterator end() {
        return iterator(nullptr);
    }

    iterator find(const Key& key) {
        Node* curr = root;
        while (curr != nullptr) {
            if (key == curr->kv.first) {
                return iterator(curr);
            } else if (key < curr->kv.first) {
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }
        return end();
    }

    Value& operator[](const Key& key) {
        Node* curr = root;
        Node* parent = nullptr;
        while (curr != nullptr) {
            if (key == curr->kv.first) return curr->kv.second;
            parent = curr;
            if (key < curr->kv.first) curr = curr->left;
            else curr = curr->right;
        }

        Node* newNode = new Node(key, Value{});
        newNode->parent = parent;

        if (parent == nullptr) {
            root = newNode;
        } else if (key < parent->kv.first) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }

        FixInsert(newNode);
        return newNode->kv.second;
    }

private:
    void leftRotation(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != nullptr) y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rightRotation(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right != nullptr) y->right->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr) root = y;
        else if (x == x->parent->right) x->parent->right = y;
        else x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

    void FixInsert(Node* k) {
        while (k->parent && k->parent->red) {
            if (k->parent == k->parent->parent->right) {
                Node* u = k->parent->parent->left; // Дядя
                if (u && u->red) {
                    u->red = false;
                    k->parent->red = false;
                    k->parent->parent->red = true;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotation(k);
                    }
                    k->parent->red = false;
                    k->parent->parent->red = true;
                    leftRotation(k->parent->parent);
                }
            } else {
                Node* u = k->parent->parent->right; // Дядя
                if (u && u->red) {
                    u->red = false;
                    k->parent->red = false;
                    k->parent->parent->red = true;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotation(k);
                    }
                    k->parent->red = false;
                    k->parent->parent->red = true;
                    rightRotation(k->parent->parent);
                }
            }
            if (k == root) break;
        }
        root->red = false;
    }
};
