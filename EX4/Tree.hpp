#ifndef TREE_HPP
#define TREE_HPP

#include "Node.hpp"
#include <vector>
#include <queue>
#include <stack>
#include <iostream>
#include <algorithm>

using namespace std;

namespace ariel {

    template<typename T> class Tree {
    private:
        shared_ptr<Node<T>> root;
        int k;
    public:
        explicit Tree(const T& root_val, int num = 2) : k(num) {
            root = make_shared<Node<T>>(root_val);
        }
        
        shared_ptr<Node<T>> find_node(shared_ptr<Node<T>> current, const T& val) {
            if (!current) {
                return nullptr;
            }
            if (current->key == val) {
                return current;
            }
            for (auto& child : current->children) {
                auto found = find_node(child, val);
                if (found) {
                    return found;
                }
            }
            return nullptr;
        }
        
        void add_sub_node(const T &parent_val, shared_ptr<Node<T>> child) {
            auto parent_node = find_node(root, parent_val);
            if (parent_node) {
                if (parent_node->children.size() < k) {
                    parent_node->add_child(child);
                } else {
                    throw runtime_error("Maximum children reached");
                }
            } else {
                throw runtime_error("Parent not found");
            }
        }

        ~Tree() {
            // Destructor
        }

        // Pre-Order Iterator (DFS)
        class pre_order_iterator {
        private:
            shared_ptr<Node<T>> current_node;
            stack<shared_ptr<Node<T>>> node_stack;

        public:
            // Constructor starts the iterator at the root
            pre_order_iterator(shared_ptr<Node<T>> root = nullptr) {
                if (root) {
                    node_stack.push(root);
                    current_node = root;
                } else {
                    current_node = nullptr;
                }
            }

            // Dereference the iterator (return the value at the current node)
            T& operator*() const {
                return current_node->key;
            }

            // Move to the next node in the pre-order traversal
            pre_order_iterator& operator++() {
                if (!node_stack.empty()) {
                    current_node = node_stack.top();
                    node_stack.pop();
                    
                    // Push children to the stack in reverse order (so left-most is processed first)
                    for (auto it = current_node->children.rbegin(); it != current_node->children.rend(); ++it) {
                        node_stack.push(*it);
                    }

                    if (!node_stack.empty()) {
                        current_node = node_stack.top();
                    } else {
                        current_node = nullptr;
                    }
                }
                return *this;
            }

            // Equality comparison (end of traversal is represented by `nullptr`)
            bool operator==(const pre_order_iterator& other) const {
                return current_node == other.current_node;
            }

            // Inequality comparison
            bool operator!=(const pre_order_iterator& other) const {
                return !(*this == other);
            }
        };

        // Post-Order Iterator (DFS)
        class post_order_iterator {
        private:
            shared_ptr<Node<T>> current_node;
            stack<shared_ptr<Node<T>>> node_stack;
            stack<shared_ptr<Node<T>>> output_stack;

        public:
            // Constructor starts the iterator at the root
            post_order_iterator(shared_ptr<Node<T>> root = nullptr) {
                if (root) {
                    node_stack.push(root);
                    while (!node_stack.empty()) {
                        current_node = node_stack.top();
                        node_stack.pop();
                        output_stack.push(current_node);
                    
                        // Push children to the stack in post order (so left-most is processed first)
                        for (const auto& child : current_node->children) {
                            node_stack.push(child);
                        }
                    }
                    if (!output_stack.empty()) {
                        current_node = output_stack.top();
                        output_stack.pop();
                    }
                }
            }

            // Dereference the iterator (return the value at the current node)
            T& operator*() const {
                return current_node->key;
            }

            // Move to the next node in the post-order traversal
            post_order_iterator& operator++() {
                if (!output_stack.empty()) {
                    current_node = output_stack.top();
                    output_stack.pop();
                } else {
                    current_node = nullptr;                    
                }
                return *this;
            }

            // Equality comparison (end of traversal is represented by `nullptr`)
            bool operator==(const post_order_iterator& other) const {
                return current_node == other.current_node;
            }

            // Inequality comparison
            bool operator!=(const post_order_iterator& other) const {
                return !(*this == other);
            }
        };

        // In-Order Iterator (DFS) - Binary trees only
        class in_order_iterator {
        private:
            shared_ptr<Node<T>> current_node;
            stack<shared_ptr<Node<T>>> node_stack;

        public:
            // Constructor starts the iterator at the root
            in_order_iterator(shared_ptr<Node<T>> root = nullptr) {
                if (root) {
                    current_node = root;
                    while (current_node) {
                        node_stack.push(current_node);
                        if (!current_node->children.empty()) {
                            current_node = current_node->children[0];
                        } else {
                            current_node = nullptr;
                        }
                    }
                    if (!node_stack.empty()) {
                        current_node = node_stack.top();
                    }
                }
            }

            // Dereference the iterator (return the value at the current node)
            T& operator*() const {
                return current_node->key;
            }

            // Move to the next node in the post-order traversal
            in_order_iterator& operator++() {
                if (!node_stack.empty()) {
                    current_node = node_stack.top();
                    node_stack.pop();

                    // Move to right child if it exists
                    if (current_node->children.size() == 2) {
                        auto right_child = current_node->children[1];
                        current_node = right_child;

                        // Push leftmost nodes of the right subtree
                        while (current_node) {
                            node_stack.push(current_node);
                            if (!current_node->children.empty()) {
                                current_node = current_node->children[0];
                            } else {
                                current_node = nullptr;
                            }
                        }
                    }
                    if (!node_stack.empty()) {
                        current_node = node_stack.top();
                    } else {
                        current_node = nullptr;
                    }
                }
                return *this;
            }

            // Equality comparison (end of traversal is represented by `nullptr`)
            bool operator==(const in_order_iterator& other) const {
                return current_node == other.current_node;
            }

            // Inequality comparison
            bool operator!=(const in_order_iterator& other) const {
                return !(*this == other);
            }
        };

        // BFS Iterator
        class bfs_iterator {
        private:
            shared_ptr<Node<T>> current_node;
            queue<shared_ptr<Node<T>>> node_queue;
        public:
            bfs_iterator(shared_ptr<Node<T>> root = nullptr) {
                if (root) {
                    node_queue.push(root);
                    current_node = root;
                } else {
                    current_node = nullptr;
                }
            }

            T& operator*() {
                return current_node->key;
            }

            bfs_iterator& operator++() {
                if (!node_queue.empty()) {
                    current_node = node_queue.front();
                    node_queue.pop();

                    for (const auto& child : current_node->children) {
                        if (child) {
                            node_queue.push(child);   
                        }
                    }

                    if (!node_queue.empty()) {
                        current_node = node_queue.front();
                    } else {
                        current_node = nullptr;
                    }
                }
                return *this;
            }

            bool operator==(const bfs_iterator& other) const {
                return current_node == other.current_node;
            }

            bool operator!=(const bfs_iterator& other) const {
                return current_node != other.current_node;
            }
        };

        // DFS Iterator
        class dfs_iterator {
        private:
            shared_ptr<Node<T>> current_node;
            stack<shared_ptr<Node<T>>> node_stack;

        public:
            dfs_iterator(shared_ptr<Node<T>> root = nullptr) {
                if (root) {
                    node_stack.push(root);
                    current_node = root;
                } else {
                    current_node = nullptr;
                }
            }

            T& operator*() {
                return current_node->key;
            }

            dfs_iterator& operator++() {
                if (!node_stack.empty()) {
                    current_node = node_stack.top();
                    node_stack.pop();

                    // Push children in reverse order so leftmost child is processed first
                    for (auto it = current_node->children.rbegin(); it != current_node->children.rend(); ++it) {
                        if (*it) {
                            node_stack.push(*it);
                        }
                    }

                    if (!node_stack.empty()) {
                        current_node = node_stack.top();
                    } else {
                        current_node = nullptr;
                    }
                }
                return *this;
            }

            bool operator==(const dfs_iterator& other) const {
                return current_node == other.current_node;
            }

            bool operator!=(const dfs_iterator& other) const {
                return current_node != other.current_node;
            }
        };

        // Heap Iterator
        class heap_iterator {
        private:
            shared_ptr<Node<T>> current_node;
            vector<shared_ptr<Node<T>>> heap_vector;

            void add_all_nodes(shared_ptr<Node<T>> node) {
                if (node) {
                    heap_vector.push(node);
                    for (const auto& child : node->children) {
                        add_all_nodes(child);
                    }
                }
            }

        public:
            heap_iterator(shared_ptr<Node<T>> root = nullptr){
                if (k != 2) {
                    throw runtime_error("Tree is not binary");
                }
                if (root) {
                    add_all_nodes(root);
                    make_heap(heap_vector.begin(), heap_vector.end());
                    current_node = heap_vector[0];
                }
            }

            T& operator*() {
                return heap_vector[0]->key;
            }

            heap_iterator& operator++() {
                if (!heap_vector.empty()) {
                    pop_heap(heap_vector.begin(), heap_vector.end());
                    heap_vector.pop_back();
                }
                return *this;
            }

            bool operator==(const heap_iterator& other) const {
                return current_node == other.current_node;
            }

            bool operator!=(const heap_iterator& other) const {
                return current_node != other.current_node;
            }
        };

        // Pre-order begin and end functions
        pre_order_iterator begin_pre_order() {
            return pre_order_iterator(root);
        }
        pre_order_iterator end_pre_order() {
            return pre_order_iterator(nullptr);
        }
        post_order_iterator begin_post_order() {
            return post_order_iterator(root);
        }
        post_order_iterator end_post_order() {
            return post_order_iterator(nullptr);
        }
        in_order_iterator begin_in_order() {
            return in_order_iterator(root);
        }
        in_order_iterator end_in_order() {
            return in_order_iterator(nullptr);
        }
        bfs_iterator begin_bfs() {
            return bfs_iterator(root);
        }
        bfs_iterator end_bfs() {
            return bfs_iterator(nullptr);
        }
        dfs_iterator begin_dfs() {
            return dfs_iterator(root);
        }
        dfs_iterator end_dfs() {
            return dfs_iterator(nullptr);
        }


        void print_tree_gui() {
            // GUI code to print the Tree...
        }
    };
}

#endif // TREE_HPP