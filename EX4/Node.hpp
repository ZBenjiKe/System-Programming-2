// Node.hpp
#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <memory>
#include <iostream>
using namespace std;

namespace ariel {

    template<typename T> class Node {
    private:
        T key;
    public:        
        vector<Node<T> *> children;

        Node(T value) : key(value) {}
        
        ~Node() {
            children.clear();
        }

        void add_child(Node<T> *child) {
            children.push_back(child);
        }

        T get_key() const {
            return key;
        } 

        vector<Node<T> *> &get_children() const {
            return children;
        }
    };
}

#endif // NODE_HPP