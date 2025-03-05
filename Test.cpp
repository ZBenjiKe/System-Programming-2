#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Complex.hpp"
#include "Tree.hpp"
#include "TreeVisualizer.hpp"
#include <memory>
#include <sstream>
#include <iostream>
#include <string>
#include <QApplication>

using namespace std;
using namespace ariel;

TEST_CASE("Basic Node Creation") {
    Node<int> node(5);
    CHECK(node.get_key() == 5);
    CHECK(node.children.empty());
}

TEST_CASE("Basic Node Creation") {
    Node<double> node = Node<double>(1.2);
    CHECK(node.get_key() == 1.2);
    CHECK(node.children.empty());
}

TEST_CASE("Node Creation With Complex Number") {
    Complex c1(3,4.5);
    Node<Complex> node(c1);
    CHECK(node.get_key() == c1);
    CHECK(node.children.empty());
}

TEST_CASE("Add Root To Tree") {
    Node<int> root_node(5);
    Tree<int> tree;
    tree.add_root(root_node);
    CHECK(tree.get_root()->get_key() == 5);
    CHECK(tree.get_root()->children.size() == 0);
}

TEST_CASE("Add Sub-Node To Tree") {
    Node<int> root_node(5);
    Tree<int> tree;
    tree.add_root(root_node);
    Node<int> n2(3);
    tree.add_sub_node(root_node,n2);
    CHECK(tree.get_root()->children.size() == 1);
    CHECK(tree.get_root()->children[0]->get_key() == 3);
}

TEST_CASE("Add Third Sub-Node In Binary Tree") {
    Node<int> n1(1);
    Node<int> n2(2);
    Node<int> n3(3);
    Node<int> n4(4);
    Tree<int> tree;
    tree.add_root(n1);
    tree.add_sub_node(n1,n2);
    tree.add_sub_node(n1,n3);
    CHECK_THROWS(tree.add_sub_node(n1,n3));
}

TEST_CASE("Erase Tree") {
    Node<int> n1(1);
    Node<int> n2(2);
    Node<int> n3(3);
    Tree<int> tree;
    tree.add_root(n1);
    tree.add_sub_node(n1,n2);
    tree.add_sub_node(n1,n3);

    CHECK(tree.get_root()->get_key() == 1);
    tree.erase_tree();
    CHECK_THROWS(tree.get_root()->get_key() == 1);
}

TEST_CASE("Binary Tree Traversal") {
    Node<double> root_node(1.1);
    Tree<double> tree;
    tree.add_root(root_node);
    Node<double> n1(1.2);
    Node<double> n2(1.3);
    Node<double> n3(1.4);
    Node<double> n4(1.5);
    Node<double> n5(1.6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2); 
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    SUBCASE("Pre-Order") {
        vector<double> order;
        vector<double> correct_order = {1.1, 1.2, 1.4, 1.5, 1.3, 1.6};
        for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
            order.push_back(node->get_key());
        }
        CHECK(order == correct_order);
    }

    // SUBCASE("Post-Order") {
    //     vector<double> order;
    //     vector<double> correct_order = {1.4, 1.5, 1.2, 1.6, 1.3, 1.1};
    //     for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node) {
    //         cout << node->get_key();
    //         order.push_back(node->get_key());
    //     }
    //     CHECK(order == correct_order);
    // }

    // SUBCASE("In-Order") {
    //     vector<double> order;
    //     vector<double> correct_order = {1.4, 1.2, 1.5, 1.1, 1.6, 1.3};
    //     for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node) {
    //         order.push_back(node->get_key());
    //     }
    //     CHECK(order == correct_order);
    // }

    SUBCASE("BFS") {
        vector<double> order;
        vector<double> correct_order = {1.1, 1.2, 1.3, 1.4, 1.5, 1.6};
        for (auto node = tree.begin_bfs(); node != tree.end_bfs(); ++node) {
            order.push_back(node->get_key());
        }
        CHECK(order == correct_order);
    }

    SUBCASE("DFS") {
        vector<double> order;
        vector<double> correct_order = {1.1, 1.2, 1.4, 1.5, 1.3, 1.6};
        for (auto node = tree.begin_dfs(); node != tree.end_dfs(); ++node) {
            order.push_back(node->get_key());
        }
        CHECK(order == correct_order);
    }
}

TEST_CASE("K-ary Tree Traversal") {
    Node<double> root_node(1.1);
    Node<double> n1(1.2);
    Node<double> n2(1.3);
    Node<double> n3(1.4);
    Node<double> n4(1.5);
    Node<double> n5(1.6);

    Tree<double,3> three_ary_tree;
    three_ary_tree.add_root(root_node);
    three_ary_tree.add_sub_node(root_node, n1);
    three_ary_tree.add_sub_node(root_node, n2);
    three_ary_tree.add_sub_node(root_node, n3);
    three_ary_tree.add_sub_node(n1, n4);
    three_ary_tree.add_sub_node(n2, n5);

    SUBCASE("BFS") {
        vector<double> order;
        vector<double> correct_order = {1.1, 1.2, 1.3, 1.4, 1.5, 1.6};
        for (auto node = three_ary_tree.begin_bfs(); node != three_ary_tree.end_bfs(); ++node) {
            order.push_back(node->get_key());
        }
        CHECK(order == correct_order);
    }

    SUBCASE("DFS") {
        vector<double> order;
        vector<double> correct_order = {1.1, 1.2, 1.5, 1.3, 1.6, 1.4};
        for (auto node = three_ary_tree.begin_dfs(); node != three_ary_tree.end_dfs(); ++node) {
            order.push_back(node->get_key());
        }
        CHECK(order == correct_order);
    }
}

TEST_CASE("Print Tree") {
    Node<double> root_node(1.1);
    Tree<double> tree;
    tree.add_root(root_node);
    Node<double> n1(1.2);
    Node<double> n2(1.3);
    Node<double> n3(1.4);
    Node<double> n4(1.5);
    Node<double> n5(1.6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2); 
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);
    
    // cout << tree << endl; 

    QApplication app();
    TreeVisualizer tv;
    tv.renderTree<double>(tree);
    tv.show();
    app.exec();
    app.exit();  
}