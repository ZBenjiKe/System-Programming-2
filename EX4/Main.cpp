/**
 * Demo app for Ex4
 */
#include <iostream>
#include <string>
#include "Complex.hpp"
#include "Tree.hpp"
#include <QApplication>
#include <QTimer>
#include "TreeVisualizer.hpp"

using namespace std;
using namespace ariel;

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    Node<double> root_node = Node<double>(1.1);
    Tree<double> tree; // Binary tree that contains doubles.
    tree.add_root(root_node);
    cout << "Root added to tree with value " << tree.get_root()->get_key() << endl;
    Node<double> n1 = Node<double>(1.2);
    Node<double> n2 = Node<double>(1.3);
    Node<double> n3 = Node<double>(1.4);
    Node<double> n4 = Node<double>(1.5);
    Node<double> n5 = Node<double>(1.6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2); 
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);
    cout << "Sub-nodes added to the tree" << endl;
   
    // The tree should look like:
    /**
     *       root = 1.1
     *     /       \
     *    1.2      1.3
     *   /  \      /
     *  1.4  1.5  1.6
     */

    TreeVisualizer tv;
    tv.renderTree<double>(tree);
    tv.show();
    QTimer::singleShot(2500, [&]() {
        app.exit(16);
    });
    app.exec();

    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
        cout << node->get_key() << "; ";
    } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6
    cout << endl;

    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node) {
        cout << node->get_key() << "; ";
    } // prints: 1.4, 1.5, 1.2, 1.6, 1.3, 1.1
    cout << endl;

    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node) {
        cout << node->get_key() << "; ";
    } // prints: 1.4, 1.2, 1.5, 1.1, 1.6, 1.3
    cout << endl;

    for (auto node = tree.begin_bfs(); node != tree.end_bfs(); ++node) {
        cout << node->get_key() << "; ";
    } // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
    cout << endl;

    tree.erase_tree();

    //cout << tree; // Should print the graph using GUI.
    Tree<double,3> three_ary_tree; // 3-ary tree.
    three_ary_tree.add_root(root_node);
    three_ary_tree.add_sub_node(root_node, n1);
    three_ary_tree.add_sub_node(root_node, n2);
    three_ary_tree.add_sub_node(root_node, n3);
    three_ary_tree.add_sub_node(n1, n4);
    three_ary_tree.add_sub_node(n2, n5);

    for (auto node = three_ary_tree.begin_bfs(); node != three_ary_tree.end_bfs(); ++node) {
        cout << node->get_key() << "; ";
    } // should print: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6

    cout << endl;

    tv.renderTree<double,3>(three_ary_tree);
    tv.show();
    QTimer::singleShot(2500, [&]() {
        app.exit(16);
    });
    app.exec();


     // The tree should look like:
    /**
     *       root = 1.1
     *     /      |     \
     *    1.2    1.3    1.4
     *   /        |
     *  1.5      1.6
     */
    
}
