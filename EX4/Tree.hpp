#ifndef TREE_HPP
#define TREE_HPP

#include <vector>
#include <memory>
#include <queue>
#include <stack>
#include <iostream>
#include <algorithm>

using namespace std;

namespace ariel {

    template<typename T> class Node {
    public:
        T value;
        vector<shared_ptr<Node<T>>> children;

        Node(T val) : value(val) {
        }

        void add_child(const T& child_value) {
            children.push_back(std::make_shared<Node<T>>(child_value));
        }
    };



    template<typename T> class Tree {
    
private:
        std::shared_ptr<Node<T>> root;
        size_t k;

    public:
        Tree(size_t k = 2) : k(k) {}

        void add_root(const T &value) {
            root = std::make_shared<Node<T>>(value);
        }

        void add_sub_node(const T &parent_val, const T &child_val) {
            auto parent_node = find_node(root, parent_val);
            if (parent_node && parent_node->children.size() < k) {
                parent_node->add_child(child_val);
            } else {
                throw std::runtime_error("Parent not found or maximum children reached");
            }
        }

        // Pre-Order Iterator (DFS)
        class pre_order_iterator {
            // Implementation of the iterator...
        };

        // Post-Order Iterator (DFS)
        class post_order_iterator {
            // Implementation of the iterator...
        };

        // In-Order Iterator (DFS) - Binary trees only
        class in_order_iterator {
            // Implementation of the iterator...
        };

        // BFS Iterator
        class bfs_iterator {
            // Implementation of the iterator...
        };

        // DFS Iterator
        class dfs_iterator {
            // Implementation of the iterator...
        };

        // Begin/End methods for iterators
        pre_order_iterator begin_pre_order() {
            // Implementation...
        }

        pre_order_iterator end_pre_order() {
            // Implementation...
        }

        post_order_iterator begin_post_order() {
            // Implementation...
        }

        post_order_iterator end_post_order() {
            // Implementation...
        }

        in_order_iterator begin_in_order() {
            // Implementation...
        }

        in_order_iterator end_in_order() {
            // Implementation...
        }

        bfs_iterator begin_bfs() {
            // Implementation...
        }

        bfs_iterator end_bfs() {
            // Implementation...
        }

        dfs_iterator begin_dfs() {
            // Implementation...
        }

        dfs_iterator end_dfs() {
            // Implementation...
        }

        void myHeap() {
            // Convert the Tree to a min-heap...
        }

        void print_tree_gui() {
            // GUI code to print the Tree...
        }

        ~Tree() {
            // Destructor
        }

    private:
        std::shared_ptr<Node<T>> find_node(std::shared_ptr<Node<T>> node, const T &value) {
            if (!node) return nullptr;
            if (node->value == value) return node;
            for (auto &child : node->children) {
                auto found = find_node(child, value);
                if (found) return found;
            }
            return nullptr;
        }
    };

}

#endif // TREE_HPP