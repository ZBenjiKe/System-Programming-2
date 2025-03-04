#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Tree.hpp"
#include "Complex.hpp"
#include <memory>
#include <sstream>

using namespace std;
using namespace ariel;

TEST_CASE("Basic Node Creation") {
    Node<int> node(5);
    CHECK(node.key == 5);
    CHECK(node.children.empty());
}

TEST_CASE("Adding and Finding Nodes in Tree") {
    Tree<int> tree(1, 3);
    auto child1 = make_shared<Node<int>>(2);
    auto child2 = make_shared<Node<int>>(3);
    tree.add_sub_node(1, child1);
    tree.add_sub_node(1, child2);
    
    CHECK(tree.find_node(tree.find_node(tree.find_node(nullptr, 1), 2), 2) != nullptr);
    CHECK(tree.find_node(tree.find_node(tree.find_node(nullptr, 1), 3), 3) != nullptr);
}

TEST_CASE("Complex Node Handling") {
    Tree<Complex> tree({1, 2}, 2);
    auto child = make_shared<Node<Complex>>(Complex{3, 4});
    tree.add_sub_node({1, 2}, child);
    
    CHECK(tree.find_node(tree.find_node(nullptr, {1, 2}), {3, 4}) != nullptr);
}
