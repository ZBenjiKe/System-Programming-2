#ifndef TREEVISUALIZER_HPP
#define TREEVISUALIZER_HPP

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include "Tree.hpp"

namespace ariel {

    class TreeVisualizer : public QGraphicsView {
        Q_OBJECT  // Qt macro for signal-slot functionality

    private:
        QGraphicsScene *scene;

        // Recursive function to draw nodes
        template <typename T> void drawNode(Node<T> *node, double x, double y, double xOffset) {
            if (!node) return;

            // Draw node value
            QGraphicsTextItem *text = scene->addText(QString::fromStdString(std::to_string(node->get_key())));
            text->setPos(x + 12, y + 10);

            // Position children
            double childX = x - xOffset;
            double childY = y + 80;
            int numChildren = node->children.size();

            for (int i = 0; i < numChildren; ++i) {
                Node<T> *child = node->children[i];
                if (child) {
                    // Draw edge to child
                    scene->addLine(x + 20, y + 40, childX + 20, childY, QPen(Qt::black));
                    
                    // Recursive call to draw child node
                    drawNode(child, childX, childY, xOffset / (numChildren > 1 ? numChildren : 2));

                    // Move child position
                    childX += xOffset / (numChildren > 1 ? numChildren - 1 : 1);
                }
            }
        }

    public:
        TreeVisualizer(QWidget *parent = nullptr) : QGraphicsView(parent) {
            scene = new QGraphicsScene(this);
            setScene(scene);
        }

        template <typename T, int k = 2> void renderTree(const Tree<T, k> &tree) {
            scene->clear();
            if (tree.get_root()) {
                drawNode<T>(tree.get_root(), 400, 50, 200); // Start drawing from root
            }
        }
    };
}

#endif // TREEVISUALIZER_HPP