#pragma once
#include <iostream>
#include <vector>
#include <functional> 
using namespace std;

/**
 * @brief A self-adjusting binary search tree called Splay Tree.
 *
 * A Splay Tree brings the most recently accessed node to the root using rotations,
 * which helps to keep frequently accessed nodes near the top for faster access.
 *
 * @tparam T The data type of the elements stored in the tree.
 */

template <class T>
class SplayTree
{
private:
    class Node; // <-- Forward declaration of Node
public:
    using NodeType = Node; // Public alias for Node type

    /**
     * @brief Default constructor. Initializes an empty splay tree.
     */
    SplayTree();

    /**
     * @brief Copy constructor.
     * @param other The SplayTree to copy from.
     */
    SplayTree(const SplayTree& other);

    /**
     * @brief Destructor. Frees all allocated memory in the tree.
     */
    ~SplayTree();

    /**
     * @brief Assignment operator.
     * @param other The SplayTree to assign from.
     * @return Reference to the current object after assignment.
     */
    const SplayTree& operator=(const SplayTree& other);

    /**
     * @brief Display the tree in-order to the given output stream.
     * @param out Output stream to print the tree.
     */
    void display(ostream& out = cout, int displayMode = 0) const;

    /**
     * @brief Inserts a new value into the splay tree and splays the newly inserted node to root.
     * @param value The value to insert.
     */
    void insert(T value);

    /**
     * @brief Removes a value from the splay tree if it exists.
     * @param value The value to remove.
     * @return True if element is deleted
     */
    bool erase(T value);

    /**
     * @brief Checks whether the tree is empty.
     * @return True if the tree is empty, false otherwise.
     */
    bool empty() const;

    /**
     * @brief Searches for a value in the tree and splays the node to root if found.
     * @param value The value to search for.
     * @return Pointer to the node containing the value, or nullptr if not found.
     */
    Node* search(T data);

    /**
    * @brief Searches for a value in the tree and splays the node to root if found.
    * @param ID. The ID of the desired Data
    * @return Pointer to the node containing the value, or nullptr if not found.
    */
    Node* search(int id);


    /*
     * @brief Helps confirming that insertion, deletion are working properly.
     * @return The count of nodes in the tree.
     */
    int nodeCount() const;
    /*
 * @brief Helps determin the tree height and confirm that the splaying minimizes the tree height.
 * @return The height of the tree ranges from 0~inf
 */
    int height(Node* node) const;

    Node* getRoot() const { return root; }

    void leafNodes(ostream& out = cout) const;

    inline T getRootValue() const { return root->data; }

    vector<T> collectInOrder(vector<T>&) const;

    std::function<void(NodeType* root)> onRotationCallback;

    void setOnRotationCallback(std::function<void(NodeType* root)> callback);

private:
    /**
     * @brief A node of the splay tree containing data and left/right child pointers.
     */
    class Node
    {
    public:
        T data;          ///< Value stored in the node.
        Node* left;      ///< Pointer to the left child.
        Node* right;     ///< Pointer to the right child.
        Node* parent;    ///< pointer to the parent

        /**
         * @brief Node constructor.
         * @param val The value to store in the node.
         */
        Node(const T& val) : data(val), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node* root; ///< Pointer to the root node of the tree.

    int nodecount = 0; /// Tracks the nodes' count of the tree.


    /**
     * @brief Splays the node containing the given value to the root.
     * @param value The value to splay.
     */
    void splay(Node* node);

    /**
     * @brief Performs a right rotation on the given node pointer.
     * @param node Reference to the pointer of the node to rotate.
     */
    void zig(Node* node);

    /**
     * @brief Performs a left rotation on the given node pointer.
     * @param node Reference to the pointer of the node to rotate.
     */
    void zag(Node* node);

    /**
     * @brief Recursively deletes all nodes in the tree starting from the given node.
     * @param node The starting node for deletion.
     */
    void destroyTree(Node* node);

    /**
    *@brief Helps us confirm that the tree maintains BST order after insertions, deletions, and splays.
    */
    void inorder(Node* node, ostream&) const;

    /*
     * @brief Helps us visualize the shape of the tree — especially since splaying modifies it.
     */
    void preorder(Node* node, ostream&) const;


    /*
     * @brief returns a pointer to the predecessor of a Node (Tarek Mohamed)
     * @return Node* to the pred of the node of T data. if not found returns its expected location.
     * @note This is a helper function used in erase function to find pred in case data not found
     */
    Node* findPred(T data) const;

    Node* searchNoSplay(T data) const;

    Node* copyTree(Node* source, Node* parent);

    void leafNodesHelper(ostream& out, Node* ptr) const;

    void collectInOrderHelper(Node*, vector<T>& result) const;

};


/**
 * @brief Overloads the << operator to print the tree.
 * @tparam T data type stored in the tree. Can be in our case a "BankAccount" class.
 * @param out Output stream.
 * @param tree The splay tree to print.
 * @return Reference to the output stream.
 */
template <class T>
ostream& operator<<(ostream& out, const SplayTree<T>& tree);

/**
 * @brief Overloads the >> operator to read elements into the tree.
 * @tparam T data type stored in the tree. Can be in our case a "BankAccount" class.
 * @param in Input stream.
 * @param tree The splay tree to modify.
 * @return Reference to the input stream.
 */
template <class T>
istream& operator>>(istream& in, SplayTree<T>& tree);

/**
 * @brief Default constructor - initializes empty Splay Tree
 * @tparam T Data type stored in tree
 * @post root set to nullptr
 * @author Kerolos Ayman
 */
template<class T>
SplayTree<T>::SplayTree() : root(nullptr) {}

/**
 * @brief Copy constructor - creates deep copy of another Splay Tree
 * @tparam T Data type stored in tree
 * @param other Tree to copy from
 * @post New independent tree created with identical structure
 * @author Kerolos Ayman
 */
template<class T>
SplayTree<T>::SplayTree(const SplayTree<T>& other)
    : root(nullptr), nodecount(other.nodecount) {
    if (other.root) {
        root = copyTree(other.root, nullptr);
    }
}

/**
 * @brief Recursive helper for deep copying tree nodes
 * @tparam T Data type stored in tree
 * @param source Node to copy from
 * @param parent Parent node for new node
 * @return Node* Newly created node
 * @author Kerolos Ayman
 */
template<class T>
typename SplayTree<T>::Node* SplayTree<T>::copyTree(Node* source, Node* parent) {
    if (!source) return nullptr;

    Node* newNode = new Node(source->data);
    newNode->parent = parent;
    newNode->left = copyTree(source->left, newNode);
    newNode->right = copyTree(source->right, newNode);

    return newNode;
}

/**
 * @brief Destructor - safely deallocates all tree nodes
 * @tparam T Data type stored in tree
 * @post All memory freed, root set to nullptr
 * @author Kerolos Ayman
 */
template<class T>
SplayTree<T>::~SplayTree() {
    destroyTree(root);
}

/**
 * @brief Recursively deletes all nodes in the tree starting from the given node.
 * @tparam T Data type stored in the tree.
 * @param node Pointer to the current node to delete.
 * @post All nodes below and including the given node are deallocated.
 *        Used internally by the destructor to free memory.
 * @author Kerolos Ayman
 */
template<class T>
void SplayTree<T>::destroyTree(Node* node) {
    if (node) {
        destroyTree(node->left);
        destroyTree(node->right);
        node->left = node->right = nullptr;
        delete node;
    }
}

/**
 * @brief Copy assignment operator - replaces tree with deep copy
 * @tparam T Data type stored in tree
 * @param other Tree to copy from
 * @return const SplayTree<T>& Reference to modified tree
 * @note Handles self-assignment safely
 * @author Kerolos Ayman
 */
template<class T>
const SplayTree<T>& SplayTree<T>::operator=(const SplayTree<T>& other) {
    if (this != &other) {
        destroyTree(root);
        root = nullptr;
        nodecount = other.nodecount;
        if (other.root) {
            root = copyTree(other.root, nullptr);
        }
    }
    return *this;
}


/**
 * @brief Inserts a new node with the given data into the Splay Tree
 * @tparam T Data type stored in the tree (must support comparison operators)
 * @param data The value to insert into the tree
 * @return true if insertion succeeded, false if duplicate found
 * @author Tarek Mohamed
 *
 * @details This implementation:
 * 1. Performs standard BST insertion
 * 2. Splays the newly inserted node to root
 * 3. Maintains tree balance through splay operations
 *
 * @note Duplicate values are not allowed in the tree
 * @warning This operation modifies the tree structure
 */

template<class T>
void SplayTree<T>::insert(T data)
{
    Node* newNode = new(nothrow) Node(data);
    if (!newNode)
    {
        cerr << "ERROR:: Memory allocation failed during insert\n";
        return;
    }

    if (root == nullptr)
    {
        root = newNode;
        nodecount++;
        return;
    }

    Node* tempPtr = root;
    Node* predPtr = nullptr;

    while (tempPtr)
    {
        if (data == tempPtr->data) // Avoid duplicates
        {
            delete newNode; // Prevent memory leak
            splay(tempPtr); // Still splay the found node to root
            nodecount++;
            return;
        }

        predPtr = tempPtr;
        if (data < tempPtr->data)
        {
            tempPtr = tempPtr->left;
        }
        else
        {
            tempPtr = tempPtr->right;
        }
    }
    nodecount++;    // incrementing nodecount here
    newNode->parent = predPtr;
    if (data < predPtr->data)
    {
        predPtr->left = newNode;
    }
    else
    {
        predPtr->right = newNode;
    }

    splay(newNode); // Bring the new node to root
}


/**
 * @brief Searches for a node containing the specified data and splays it to root
 * @tparam T Data type stored in the tree (must support comparison operators)
 * @param data The value to search for
 * @return true if found, false otherwise
 * @author Tarek Mohamed
 *
 * @details This implementation:
 * 1. Performs standard BST search
 * 2. Splays the found node (or last accessed node) to root
 * 3. Maintains the splay tree's self-adjusting property
 *
 * @note The tree structure is modified during search to bring the found node to root
 * @warning Empty trees will return false without modification
 *
 */
template<class T>
typename SplayTree<T>::Node* SplayTree<T>::search(T data)
{
    Node* temp = root;
    Node* pred = nullptr;

    while (temp)
    {
        if (data == temp->data)
        {
            splay(temp);
            return root;
        }

        pred = temp;
        if (data < temp->data)
            temp = temp->left;
        else
            temp = temp->right;
    }

    if (pred)
        splay(pred);

    return nullptr; // not found
}

/**
 * @brief Searches for a node containing the specified ID and splays it to root
 * @param ID of data searched for
 * @return true if found, false otherwise
 * @author Tarek Mohamed
 *
 * @details This implementation:
 * 1. Performs standard BST search
 * 2. Splays the found node (or last accessed node) to root
 * 3. Maintains the splay tree's self-adjusting property
 *
 * @note The tree structure is modified during search to bring the found node to root
 * @warning Empty trees will return false without modification
 * @warning this will only exists when the templatized data has a function getCustomerID
 *
 */
template<class T>
typename SplayTree<T>::Node* SplayTree<T>::search(int id)
{
    Node* curr = root;

    while (curr)
    {
        int currID = curr->data.getCustomerID();
        if (id == currID)
        {
            splay(curr);
            return curr;
        }
        else if (id < currID)
        {
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }
    }

    return nullptr; // not found
}



/*
 * @brief Splaying brings node to the root and make it the new root and preserves the BST structure (Tarek Mohamed)
 * @tparam T data type stored in the tree. Can be in our case a "BankAccount" class.
 * @param Node* node - The node which becomes the new root
 * @author Tarek Mohamed
 */
template<class T>
void SplayTree<T>::splay(Node* node)
{
    while (node != root)
    {
        Node* parent = node->parent;
        if (parent == root)
        {
            if (node == parent->left)
                zig(parent);
            else
                zag(parent);
        }
        else
        {
            Node* grandParent = parent->parent;
            if (node == parent->left)
            {
                if (parent == grandParent->left)
                {
                    zig(grandParent);
                    zig(parent);
                }
                else
                {
                    zig(parent);
                    zag(grandParent);
                }
            }
            else
            {
                if (parent == grandParent->left)
                {
                    zag(parent);
                    zig(grandParent);
                }
                else
                {
                    zag(grandParent);
                    zag(parent);
                }
            }
        }
    }
}

/*
 * @brief Performs node right rotation
 * @tparam T data type stored in the tree. Can be in our case a "BankAccount" class.
 * @param Node* node - The node which becomes the rotation is performed on.
 * @author Tarek Mohamed
 */
template<class T>
void SplayTree<T>::zig(Node* node)
{
    Node* temp = node->left;
    node->left = temp->right;
    if (temp->right)
        temp->right->parent = node;

    temp->parent = node->parent;
    if (!node->parent)
        root = temp;
    else if (node == node->parent->left)
        node->parent->left = temp;
    else // case node is the right child of its parent
        node->parent->right = temp;

    temp->right = node;
    node->parent = temp;

    if (onRotationCallback) onRotationCallback(root);
}

/*
 * @brief Performs node left rotation
 * @tparam T data type stored in the tree. Can be in our case a "BankAccount" class.
 * @param Node* node - The node which becomes the rotation is performed on.
 * @author Tarek Mohamed
 */
template<class T>
void SplayTree<T>::zag(Node* node)
{
    Node* temp = node->right;
    node->right = temp->left;

    if (temp->left)
        temp->left->parent = node;

    temp->parent = node->parent;

    if (!node->parent)
        root = temp;
    else if (node == node->parent->left)
        node->parent->left = temp;
    else
        node->parent->right = temp;

    temp->left = node;
    node->parent = temp;

    if (onRotationCallback) onRotationCallback(root);

}

template<class T>
typename SplayTree<T>::Node* SplayTree<T>::findPred(T data) const
{
    Node* temp = root;
    Node* pred = nullptr;

    while (temp)
    {
        if (data == temp->data)
            break;

        pred = temp;
        if (data < temp->data)
            temp = temp->left;
        else
            temp = temp->right;
    }

    return pred;
}

template<class T>
typename SplayTree<T>::Node* SplayTree<T>::searchNoSplay(T data) const
{
    Node* temp = root;
    Node* pred = nullptr;

    while (temp)
    {
        if (data == temp->data)
            return temp;

        pred = temp;
        if (data < temp->data)
            temp = temp->left;
        else
            temp = temp->right;
    }

    return nullptr; // not found
}

/**
 * @brief Removes a node containing the specified data
 * @tparam T Data type stored in the tree (must support comparison operators)
 * @param data The value to remove from the tree
 * @return true if found and removed, false if not found
 * @author Tarek Mohamed
 *
 * @warning The tree will splay either:
 * - The deleted node's predecessor (if internal), or
 * - The last accessed node (if not found), or
 * - inorder pred. if (root & both subtrees exist)
 * - none if(root & one subtree exit) i.e. only assign the root to the subtree's root
 *
 *
 * Example usage:
 * @code
 * SplayTree<BankAccount> tree;
 * tree.insert(5);
 * bool removed = tree.erase(5); // returns true
 * @endcode
 */
template<class T>
bool SplayTree<T>::erase(T data) {
    if (!root) return false;

    Node* deleteNode = searchNoSplay(data);
    if (deleteNode == nullptr) {
        // Data not found - splay the last accessed node
        Node* splayTarget = findPred(data);
        if (splayTarget) splay(splayTarget);
        return false;
    }

    // First, splay the node to delete to bring it to root
    splay(deleteNode);

    // Now delete the root node (which is our target)
    Node* leftTree = root->left;
    Node* rightTree = root->right;

    if (leftTree) leftTree->parent = nullptr;
    if (rightTree) rightTree->parent = nullptr;

    delete root;

    if (!leftTree) {
        root = rightTree;
    }
    else if (!rightTree) {
        root = leftTree;
    }
    else {
        // Find maximum in left subtree
        Node* maxLeft = leftTree;
        while (maxLeft->right) {
            maxLeft = maxLeft->right;
        }

        if (maxLeft != leftTree) {
            // If maxLeft is not already the root of leftTree, splay it
            root = leftTree;
            splay(maxLeft);
            leftTree = root;  // maxLeft is now root of leftTree
        }

        // Attach right tree
        maxLeft->right = rightTree;
        rightTree->parent = maxLeft;
        root = maxLeft;
    }
    nodecount--;
    return true;
}

/**
 * @brief Returns the total number of nodes in the Splay Tree.
 * @tparam T Data type stored in the tree.
 * @return Integer representing the number of nodes.
 * @author Nour Mamdouh
 */
template<class T>
int SplayTree<T>::nodeCount() const {
    return nodecount;
}

/**
 * @brief Calculates the height of the subtree rooted at the given node.
 * @tparam T Data type stored in the tree.
 * @param ptr Pointer to the root of the subtree.
 * @return Height of the subtree. Returns 0 if ptr is null.
 * @author Nour Mamdouh
 */
template<class T>
int SplayTree<T>::height(SplayTree<T>::Node* ptr) const {
    int max_left, max_right = 0;
    if (!ptr) {
        return 0;
    }
    max_left = height(ptr->left);
    max_right = height(ptr->right);
    return (max_left >= max_right) ? max_left : max_right;
}

/**
 * @brief Checks whether the Splay Tree is empty.
 * @tparam T Data type stored in the tree.
 * @return True if the tree has no nodes, otherwise false.
 * @author Nour Mamdouh
 */
template<class T>
bool SplayTree<T>::empty() const {
    return nodeCount() == 0;
}

/**
 * @brief Outputs the elements of the tree using inorder traversal.
 * @tparam T Data type stored in the tree.
 * @param ptr Pointer to the current node.
 * @param out Output stream to print the traversal.
 * @author Nour Mamdouh
 */
template<class T>
void SplayTree<T>::inorder(SplayTree<T>::Node* ptr, ostream& out) const {
    if (!ptr) return;
    inorder(ptr->left, out);
    out << ptr->data << " ";
    inorder(ptr->right, out);
}

/**
 * @brief Outputs the vector of all data
 * @param reference to the vector populated
 * @tparam T Data type stored in the tree.
 * @author Tarek Mohamed
 */
template<class T>
vector<T> SplayTree<T>::collectInOrder(vector<T>& result) const {
    collectInOrderHelper(root, result);
    return result;
}

template<class T>
inline void SplayTree<T>::setOnRotationCallback(std::function<void(NodeType* root)> callback)
{
    onRotationCallback = std::move(callback);
}

template<class T>
void SplayTree<T>::collectInOrderHelper(Node* node, std::vector<T>& result) const {
    if (!node) return;
    collectInOrderHelper(node->left, result);
    result.push_back(node->data);
    collectInOrderHelper(node->right, result);
}



/**
 * @brief Outputs the elements of the tree using preorder traversal.
 * @tparam T Data type stored in the tree.
 * @param ptr Pointer to the current node.
 * @param out Output stream to print the traversal.
 * @author Nour Mamdouh
 */
template<class T>
void SplayTree<T>::preorder(SplayTree::Node* ptr, ostream& out) const {
    if (!ptr) return;
    out << ptr->data << " ";
    preorder(ptr->left, out);
    preorder(ptr->right, out);
}

/**
 * @brief Displays the tree content using inorder traversal by default.
 * @tparam T Data type stored in the tree.
 * @param out Output stream to print the tree.
 * @param print mode if 1 prints preorder else prints inorder. default values is 0.
 * @note If the tree is empty, a message is printed to standard error.
 * @author Nour Mamdouh
 */
template<class T>
void SplayTree<T>::display(ostream& out, int printMode) const {
    if (empty()) {
        cerr << "Cannot traverse an empty tree!" << endl;
        return;
    }
    switch (printMode) {
    case 0:
        inorder(root, out); // Default traversal method
        break;
    case 1:
        preorder(root, out);
        break;
    default:
        inorder(root, out); // Default traversal method
    }
}

/**
 * @brief Overloaded stream insertion operator to display tree contents.
 * @tparam T Data type stored in the tree.
 * @param out Output stream.
 * @param tree Reference to the tree to display.
 * @return Reference to the output stream.
 * @author Nour Mamdouh
 *
 */
template<class T>
ostream& operator<<(ostream& out, const SplayTree<T>& tree) {
    tree.display(out);
    return out;
}

/**
 * @brief Overloaded stream extraction operator to insert a single element.
 * @tparam T Data type stored in the tree.
 * @param in Input stream.
 * @param tree Reference to the tree to insert into.
 * @return Reference to the input stream.
 * @author Nour Mamdouh
 */
template<class T>
istream& operator>>(istream& in, SplayTree<T>& tree) {
    T data;
    in >> data;
    tree.insert(data);
    return in;
}

/**
 * @brief Outputs all leaf nodes in the tree.
 * @tparam T Data type stored in the tree.
 * @param out Output stream to print leaf nodes.
 * @param ptr Pointer to the current node.
 * @note If the tree is empty, an error message is printed.
 * @author Nour Mamdouh
 */
template<class T>
void SplayTree<T>::leafNodesHelper(ostream& out, Node* ptr) const {
    if (empty()) {
        cerr << "Empty Tree!!";
        return;
    }
    if (!ptr) return;
    if (!ptr->left && !ptr->right) {
        out << ptr->data << endl;
    }
    leafNodesHelper(out, ptr->left);
    leafNodesHelper(out, ptr->right);
}

template<class T>
void SplayTree<T>::leafNodes(std::ostream& out) const {
    leafNodesHelper(out, root);
}
