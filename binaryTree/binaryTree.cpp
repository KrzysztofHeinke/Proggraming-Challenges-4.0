#include <iostream>

template <typename T>
class Node
{

public:
    T mData;
    Node *mLeft;
    Node *mRight;

    Node(T data)
    {
        mData = data;
        mLeft = nullptr;
        mRight = nullptr;
    }
};

template <typename T>
class BinaryTree
{
    public:
    Node<T> *root;
    BinaryTree()
    {
        root = nullptr;
    }
    void insert(T data)
    {
        if (root == nullptr)
        {
            root = new Node<T>(data);
            return;
        }
        
        Node<T> *tmpNode = root;
        
        
        while (tmpNode != nullptr)
        {
            if ( tmpNode->mData == data)
            {
                return;
            }
            else if ( data > tmpNode->mData)
            {
                if (tmpNode->mRight == nullptr)
                {
                    tmpNode->mRight = new Node<T> (data);
                    return;
                }
                tmpNode = tmpNode->mRight;
            }
            else if (data < tmpNode->mData)
            {
                if (tmpNode->mLeft == nullptr)
                {
                    tmpNode->mLeft = new Node<T> (data);
                    return;
                }
                tmpNode = tmpNode->mLeft;
            }
        }
        
            
    }

    Node<T>* search(Node<T> *node, T value)
    {
        if (node != nullptr)
        {
            if (node->mData == value)
            {
                return node;
            }
            if (value < node->mData)
            {
                return search(node->mLeft, value);
            }
            else
            {
                return search(node->mRight, value);
            }
        }        
        return nullptr;
    }

    Node<T>* search(T value)
    {
        Node<T> *node = root;
        if (node != nullptr)
        {
            if (node->mData == value)
            {
                return node;
            }
            if (value < node->mData)
            {
                return search(node->mLeft, value);
            }
            else
            {
                return search(node->mRight, value);
            }
        }
        return node;
    }    
    void print(Node<T> *node)
    {
        if(node != nullptr)
        {
            std::cout << node->mData << " ";
            print(node->mLeft);
            print(node->mRight);
        }
    }
    void print()
    {
        Node<T> *node = root;
        if(node != nullptr)
        {
            std::cout << node->mData << " ";
            print(node->mLeft);
            print(node->mRight);
        }
    }

};  

int main()
{
    BinaryTree<int> root;
    root.insert(1);
    root.insert(2);
    root.insert(3);
    root.insert(4);
    root.insert(5);
    root.insert(6);
    // std::cout << root.root->mData;
    // std::cout << root.root->mRight->mData;

    // std::cout << std::endl;
    // std::cout << root.search(6)->mData;
    root.print();
    

    return 0;
}