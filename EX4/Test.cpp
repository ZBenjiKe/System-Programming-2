

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "node.hpp"
#include "tree.hpp"
#include "complex.hpp"
using namespace std;


TEST_CASE("Tree with integer") {

 Node<int> root_node(1);
    Node<int> n1(2);
    Node<int> n2(3);

    Tree<int> t(2);
    t.add_root(root_node);
    t.add_sub_node(root_node, n1);
    t.add_sub_node(root_node, n2);

    Node<int>* root = t.get_root();
    CHECK(t.get_root()->key == 1);
    CHECK(root->children[0]->key== 2);
    CHECK(root->children[1]->key== 3);
}


TEST_CASE("Tree with k-arry") {
   Node<int> root_node(1);
    Node<int> n1(2);
    Node<int> n2(3);
    Node<int> n3(4);

    Tree<int> t(3);
    t.add_root(root_node);
    t.add_sub_node(root_node, n1);
    t.add_sub_node(root_node, n2);
     t.add_sub_node(root_node, n3);

    Node<int>* root = t.get_root();

    CHECK(t.get_root()->key == 1);
    CHECK(root->children[0]->key == 2);
    CHECK(root->children[1]->key == 3);
    CHECK(root->children[2]->key == 4);
}


TEST_CASE("Tree error") {
    Node<int> root_node(1);
    Node<int> n1(2);
    Node<int> n2(3);
    Node<int> n3(4);

    Tree<int> t(2);
    t.add_root(root_node);
    t.add_sub_node(root_node, n1);
    t.add_sub_node(root_node, n2);
    CHECK_THROWS_AS(t.add_sub_node(root_node, n3);, std::runtime_error); 
}


TEST_CASE("Tree traverse on binary tree with double")
{
    Node<double> root_node(1.1);
    Node<double> n1(1.2);
    Node<double> n2(1.3);
    Node<double> n3(1.4);
    Node<double> n4(1.5);
    Node<double> n5(1.6);

    Tree<double> tree(2);
    tree.add_root(root_node);
    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);



    SUBCASE("PreOrder")
    {
        vector<double> result;
        for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
        {
            result.push_back(node->get_key());
        }
        vector<double> excepted = {1.1, 1.2, 1.4, 1.5, 1.3, 1.6};
        CHECK(result == excepted);
    }

    SUBCASE("PostOrder")
    {
        vector<double> result;
        for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
        {

            result.push_back(node->get_key());
        }
        vector<double> excepted = {1.4, 1.5, 1.2, 1.6, 1.3, 1.1};
        CHECK(result == excepted);
    }

    SUBCASE("InOrder")
    {
        vector<double> result;
        for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
        {
            result.push_back(node->get_key());
        }
        vector<double> excepted = {1.4, 1.2, 1.5, 1.1, 1.6, 1.3};
        CHECK(result == excepted);
    }

    SUBCASE("BFS")
    {
        vector<double> result;
        for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
        {
            result.push_back(node->get_key());
        }
        vector<double> excepted = {1.1, 1.2, 1.3, 1.4, 1.5, 1.6};
        CHECK(result == excepted);
    }

    SUBCASE("DFS")
    {
        vector<double> result;
        for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
        {
            result.push_back(node->get_key());
        }
        vector<double> excepted = {1.1, 1.2, 1.4, 1.5, 1.3, 1.6};
        CHECK(result == excepted);
    }

    SUBCASE("Min Heap")
    {
        vector<double> result;
        for (auto node = tree.begin_heap(); node != tree.end_heap(); ++node)
        {
            result.push_back(node->get_key());
        }
        vector<double> excepted = {1.1, 1.2, 1.3, 1.4, 1.5, 1.6};
        CHECK(result == excepted);
    }
}



TEST_CASE("Tree traverse on binary tree with int")
{
    Node<int> root_node(1);
    Node<int> n1(2);
    Node<int> n2(3);
    Node<int> n3(4);
    Node<int> n4(5);
    Node<int> n5(6);

    Tree<int> tree(2);
    tree.add_root(root_node);
    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);



    SUBCASE("PreOrder")
    {
        vector<int> result;
        for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
        {
            result.push_back(node->get_key());
        }
        vector<int> excepted = {1, 2, 4, 5, 3, 6};
        CHECK(result == excepted);
    }

    SUBCASE("PostOrder")
    {
        vector<int> result;
        for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
        {

            result.push_back(node->get_key());
        }
        vector<int> excepted = {4, 5, 2, 6, 3, 1};
        CHECK(result == excepted);
    }

    SUBCASE("InOrder")
    {
        vector<double> result;
        for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
        {
            result.push_back(node->get_key());
        }
        vector<double> excepted = {4, 2, 5, 1, 6, 3};
        CHECK(result == excepted);
    }

    SUBCASE("BFS")
    {
        vector<int> result;
        for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
        {
            result.push_back(node->get_key());
        }
        vector<int> excepted = {1, 2, 3, 4, 5, 6};
        CHECK(result == excepted);
    }

    SUBCASE("DFS")
    {
        vector<int> result;
        for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
        {
            result.push_back(node->get_key());
        }
        vector<int> excepted = {1, 2, 4, 5, 3, 6};
        CHECK(result == excepted);
    }

    SUBCASE("Min Heap")
    {
        vector<int> result;
        for (auto node = tree.begin_heap(); node != tree.end_heap(); ++node)
        {
            result.push_back(node->get_key());
        }
        vector<int> excepted = {1, 2, 3, 4, 5, 6};
        CHECK(result == excepted);
    }
}


TEST_CASE("Tree traverse on binary tree with int")
{
    Node<double> root_node(1);
    Node<double> n1(2);
    Node<double> n2(3);
    Node<double> n3(4);
    Node<double> n4(5);
    Node<double> n5(6);

    Tree<double> tree(2);
    tree.add_root(root_node);
    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);



    SUBCASE("PreOrder")
    {
        vector<double> result;
        for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
        {
            result.push_back(node->get_key());
        }
        vector<double> excepted = {1, 2, 4, 5, 3, 6};
        CHECK(result == excepted);
    }

    SUBCASE("PostOrder")
    {
        vector<double> result;
        for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
        {

            result.push_back(node->get_key());
        }
        vector<double> excepted = {4, 5, 2, 6, 3, 1};
        CHECK(result == excepted);
    }

    SUBCASE("InOrder")
    {
        vector<double> result;
        for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
        {
            result.push_back(node->get_key());
        }
        vector<double> excepted = {4, 2, 5, 1, 6, 3};
        CHECK(result == excepted);
    }

    SUBCASE("BFS")
    {
        vector<double> result;
        for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
        {
            result.push_back(node->get_key());
        }
        vector<double> excepted = {1, 2, 3, 4, 5, 6};
        CHECK(result == excepted);
    }

    SUBCASE("DFS")
    {
        vector<double> result;
        for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
        {
            result.push_back(node->get_key());
        }
        vector<double> excepted = {1, 2, 4, 5, 3, 6};
        CHECK(result == excepted);
    }

    SUBCASE("Min Heap")
    {
        vector<double> result;
        for (auto node = tree.begin_heap(); node != tree.end_heap(); ++node)
        {
            result.push_back(node->get_key());
        }
        vector<double> excepted = {1, 2, 3, 4, 5, 6};
        CHECK(result == excepted);
    }
}


TEST_CASE("Tree with complex numbers")
{
    Node<Complex> root(Complex(1, 2));
    Node<Complex> n1(Complex(2, 3));
    Node<Complex> n2(Complex(3, 4));
    Node<Complex> n3(Complex(4, 5));
    Node<Complex> n4(Complex(5, 6));

    Tree<Complex> complexTree;
    complexTree.add_root(root);
    complexTree.add_sub_node(root, n1);
    complexTree.add_sub_node(root, n2);
    complexTree.add_sub_node(n1, n3);
    complexTree.add_sub_node(n1, n4);


    SUBCASE("PreOrder")
    {
        vector<Complex> result;
        for (auto node = complexTree.begin_pre_order(); node != complexTree.end_pre_order(); ++node)
        {
            result.push_back(node->get_key());
        }
        vector<Complex> excepted = {Complex(1, 2), Complex(2, 3), Complex(4, 5), Complex(5, 6), Complex(3, 4)};
        CHECK(result == excepted);
    }

    SUBCASE("PostOrder")
    {
        vector<Complex> result;
        for (auto node = complexTree.begin_post_order(); node != complexTree.end_post_order(); ++node)
        {
            result.push_back(node->get_key());
        }
        vector<Complex> excepted = {Complex(4, 5), Complex(5, 6), Complex(2, 3), Complex(3, 4), Complex(1, 2)};
        CHECK(result == excepted);
    }

    SUBCASE("InOrder")
    {
        vector<Complex> result;
        for (auto node = complexTree.begin_in_order(); node != complexTree.end_in_order(); ++node)
        {
            result.push_back(node->get_key());
        }
        vector<Complex> excepted = {Complex(4, 5), Complex(2, 3), Complex(5, 6), Complex(1, 2), Complex(3, 4)};
        CHECK(result == excepted);
    }

    SUBCASE("BFS")
    {
        vector<Complex> result;
        for (auto node = complexTree.begin_bfs_scan(); node != complexTree.end_bfs_scan(); ++node)
        {
            result.push_back(node->get_key());
        }
        vector<Complex> excepted = {Complex(1, 2), Complex(2, 3), Complex(3, 4), Complex(4, 5), Complex(5, 6)};
        CHECK(result == excepted);
    }

    SUBCASE("DFS")
    {
        vector<Complex> result;
        for (auto node = complexTree.begin_dfs_scan(); node != complexTree.end_dfs_scan(); ++node)
        {
            result.push_back(node->get_key());
        }
        vector<Complex> excepted = {Complex(1, 2), Complex(2, 3), Complex(4, 5), Complex(5, 6), Complex(3, 4)};
        CHECK(result == excepted);
    }

}


TEST_CASE("bfs_iterator for double for k-3 ary") {
    Tree<double> check_tree(3);
    
       Node<double> root_node(1.1);
    Node<double> n1(2.2);
    Node<double> n2(3.3);
    Node<double> n3(4.4);
    Node<double> n4(5.5);

    
    
    check_tree.add_root(root_node);
    check_tree.add_sub_node(root_node, n1);
    check_tree.add_sub_node(root_node, n2);
    check_tree.add_sub_node(root_node, n3);
    check_tree.add_sub_node(n2, n4);
    std::vector<double> expected= {1.1, 2.2, 3.3, 4.4, 5.5};
   vector<double> result;
        for (auto node = check_tree.begin_bfs_scan(); node != check_tree.end_bfs_scan(); ++node)
        {
            result.push_back(node->get_key());
        }
        CHECK(result == expected);
}

