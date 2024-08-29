#include "tree.hpp"
#include "Complex.hpp"

int main() {
    ariel::tree<int> intTree;
    intTree.add_root(1);
    intTree.add_sub_node(1, 2);
    intTree.add_sub_node(1, 3);
    intTree.add_sub_node(2, 4);
    intTree.add_sub_node(2, 5);

    std::cout << "Pre-Order Traversal:\n";
    for (auto it = intTree.begin_pre_order(); it != intTree.end_pre_order(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    std::cout << "In-Order Traversal:\n";
    for (auto it = intTree.begin_in_order(); it != intTree.end_in_order(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    std::cout << "Post-Order Traversal:\n";
    for (auto it = intTree.begin_post_order(); it != intTree.end_post_order(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    ariel::tree<ariel::Complex> complexTree;
    complexTree.add_root(ariel::Complex(1, 2));
    complexTree.add_sub_node(ariel::Complex(1, 2), ariel::Complex(3, 4));
    complexTree.add_sub_node(ariel::Complex(1, 2), ariel::Complex(5, 6));

    std::cout << "Complex Tree Pre-Order Traversal:\n";
    for (auto it = complexTree.begin_pre_order(); it != complexTree.end_pre_order(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    // Demonstrate GUI print (placeholder)
    complexTree.print_tree_gui();

    return 0;
}
