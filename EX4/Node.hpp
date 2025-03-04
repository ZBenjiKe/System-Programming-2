// Node.hpp
#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <memory>
#include <iostream>
using namespace std;

namespace ariel {

    template<typename T> class Node : public enable_shared_from_this<Node<T>> {
    public:
        T key;
        vector<shared_ptr<Node<T>>> children;
        
        explicit Node(const T& value) : key(value) {}
        
        void add_child(shared_ptr<Node<T>> child) {
            children.push_back(child);
        }
    };

}

#endif // NODE_HPP