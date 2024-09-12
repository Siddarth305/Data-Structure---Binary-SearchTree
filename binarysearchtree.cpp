#include <iostream>
#include <cstdlib>

// Node structure for the binary search tree
struct Node {
    int data;
    Node* left;
    Node* right;
};

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = new Node();
    if (!newNode) {
        std::cout << "Memory allocation failed\n";
        exit(1);
    }
    newNode->data = data;
    newNode->left = newNode->right = nullptr;
    return newNode;
}

// Function to insert a node into the binary search tree
Node* insert(Node* root, int data) {
    if (root == nullptr) {
        root = createNode(data);
        return root;
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }
    return root;
}

// Function to find the minimum value node in the tree
Node* findMin(Node* root) {
    while (root->left != nullptr)
        root = root->left;
    return root;
}

// Function to delete a node from the binary search tree
Node* deleteNode(Node* root, int data) {
    if (root == nullptr) return root;
    
    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Function to search a node in the binary search tree
bool search(Node* root, int data) {
    if (root == nullptr) return false;
    if (root->data == data) return true;
    else if (data < root->data) return search(root->left, data);
    else return search(root->right, data);
}

// Function to display the binary search tree in order
void inOrder(Node* root) {
    if (root == nullptr) return;
    inOrder(root->left);
    std::cout << root->data << " ";
    inOrder(root->right);
}

int main() {
    Node* root = nullptr;
    int choice, data;

    while (1) {
        std::cout << "1. INSERT\n2. DELETE\n3. DISPLAY\n4. SEARCH\n5. EXIT\nEnter your choice: ";
        std::cin >> choice;
        switch (choice) {
        case 1:
            std::cout << "Enter the element to insert: ";
            std::cin >> data;
            root = insert(root, data);
            break;
        case 2:
            std::cout << "Enter the element to delete: ";
            std::cin >> data;
            if (search(root, data))
                root = deleteNode(root, data);
            else
                std::cout << "No such element in the tree" << std::endl;
            break;
        case 3:
            std::cout << "Binary Search Tree: ";
            inOrder(root);
            std::cout << std::endl;
            break;
        case 4:
            std::cout << "Enter the element to search: ";
            std::cin >> data;
            if (search(root, data))
                std::cout << data << " is found in the tree." << std::endl;
            else
                std::cout << "No such element in the tree." << std::endl;
            break;
        case 5:
            exit(0);
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
    return 0;
}
