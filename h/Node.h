
#include <memory>
#include <string>

using std::unique_ptr;
using std::string;

class Node;
typedef unique_ptr<Node> NodePtr;

class Node {
    public:
        //virtual ~Node() = default;

        string getName() {
            return name;
        }

    protected:
        Node() {}
        string name;

};


class OppNode: public Node {
    public:
        static NodePtr make(NodePtr p_leftNode, NodePtr p_rightNode) {
            auto node = new OppNode();

            node->leftNode = move(p_leftNode);
            node->rightNode = move(p_rightNode);
        }

        OppNode() {

        };

        void setLeft(Node* newNode) {

        }

        void setRight(Node* newNode) {

        }

    private:
        NodePtr leftNode, rightNode;
};

class NumNode: public Node {
    public:

    private:

};