#pragma once
#include"TreeNode.h"
#include<fstream>

using namespace std;

template <class T>
class BinSTree
{

protected:
    //указатели на корень и текущий узел
    TreeNode<T>* root, * current;
    //число элементов дерева
    int size;

    //распределение/освобождение памяти
    TreeNode<T>* GetTreeNode(const T& item,
        TreeNode<T>* lptr,
        TreeNode<T>* rptr) {
        TreeNode<T>* p;
        p = new TreeNode<T>(item, lptr, rptr);
        //проверка памяти
        if (p == NULL)
        {
            cout << "Error!" << endl;
            exit(1);
        }
        return p;
    }

    void FreeTreeNode(TreeNode<T>* p) {
        delete p;
    }

    //используется конструктором копирования и оператором присвания
    void DeleteTree(TreeNode<T>* t) {
        if (t != NULL) {
            DeleteTree(t->Left());
            DeleteTree(t->Right());
            FreeTreeNode(t);
        }
    }

    TreeNode<T>* FindNode(const T& item,
        TreeNode<T>*& parent) const {
        //пробежать по узлам
        TreeNode<T>* t = root;
        //нет родителя
        parent = NULL;
        while (t != NULL) {
            if (item == t->data)
                break;
            else
            {
                //обновить указатель и идти право/лево
                parent = t;
                if (item < t->data)
                    t = t->left;
                else
                    t = t->right;
            }
        }
        return t;
    }


public:


    BinSTree() {
        root = nullptr;
        current = nullptr;
        size = 0;
    }

    BinSTree(const BinSTree<T>& tree) {
        root = new TreeNode<T>(tree, nullptr, nullptr);
        current = root;
        size = 0;
    }


    ~BinSTree() {

    }

    //оператор присваивания
    BinSTree<T>& operator= (const BinSTree<T>& rhs) {
        //проверка
        if (this == &rhs)
            return *this;
        //очистить текущее дерево,скопировать новое
        ClearTree(this->root);
        root = CopyTree(rhs.root);
        current = root;
        size = this->size;
        return *this;
    }

    //стандартные методы обработки списков
    int Find(T& item) {
        //принимает параметр parent
        TreeNode<T>* parent;
        //искать значение, назначить совпавший узел текущим
        current = FindNode(item, parent);
        if (current != NULL) {
            item = current->data;
            return 1;
        }
        else
            return 0;
    }

    void Insert(const T& item) {
        TreeNode<T>* t = root, * parent = NULL, * newNode = new TreeNode<T>(item, nullptr, nullptr);
        while (t != NULL) {
            parent = t;
            if (item < t->data)
                t = t->left;
            else
                t = t->right;
        }
        if (parent == NULL)
            root = newNode;
        else if (item < parent->data)
            parent->left = newNode;
        else
            parent->right = newNode;
        current = newNode;
        size++;

    }


    void Delete(const T& val) {
        remove_helper(root, val);
    }

    TreeNode<T>* remove_helper(TreeNode<T>* node, const T& val)
    {
        if (node == NULL)
            return node;

        if (val == node->data) {

            TreeNode<T>* tmp;
            if (node->right == NULL)
                tmp = node->left;
            else {

                TreeNode<T>* ptr = node->right;
                if (ptr->left == NULL) {
                    ptr->left = node->left;
                    tmp = ptr;
                }
                else {

                    TreeNode<T>* pmin = ptr->left;
                    while (pmin->left != NULL) {
                        ptr = pmin;
                        pmin = ptr->left;
                    }
                    ptr->left = pmin->right;
                    pmin->left = node->left;
                    pmin->right = node->right;
                    tmp = pmin;
                }
            }

            delete node;
            return tmp;
        }
        else if (val < node->data)
            node->left = remove_helper(node->left, val);
        else
            node->right = remove_helper(node->right, val);
        return node;
    }

    void ClearList() {
        ClearTree(this->root);
    }

    int ListEmpty() const;
    int ListSize() const;

    //методы, специфичные для деревьев
    void Update(const T& item) {
        if (current != NULL && current->data == item)
            current->data = item;
        else
            Insert(item);
    }

    TreeNode<T>* GetRoot() const {
        return root;
    }

    void PrintTreeB(int level) {
        current = root;
        PrintTree(root, level);
    }

    void PrintTreeBFile(int level, string s1) {
        current = root;
        PrintTreeFile(root, level, s1);
    }

    void PrintVTreeB(int dataWidth, int screenWidth) {
        current = root;
        PrintVTree(root, dataWidth, screenWidth, Print);
    }

    void PrintVTreeBFile(int dataWidth, int screenWidth, string s1) {
        current = root;
        PrintVTreeFile(root, dataWidth, screenWidth, PrintFile, s1);
    }

    void CountLeafB(int& count) {
        if (root == nullptr) count = 0;
        CountLeaf(root, count);
    }

    int DepthB() {
        if (root == nullptr)
            return -1;
        else
            return Depth(root);
    }

    int SizeB() {
        return size;
    }

};
