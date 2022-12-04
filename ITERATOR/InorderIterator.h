#pragma once
#include "MyStack.h"
#include "TreeNode.h"
#include "Iterator.h"
template <class T>
class InorderIterator : public Iterator<T> {
private:
    //стек адресов узлов
    MyStack<TreeNode <T>*> S;
    //корень дерева и текущий узел
    TreeNode<T>* root, * current;
    //сканирование левого поддерева. используется функцией Next
    TreeNode<T>* GoFarLeft(TreeNode<T>* t) {
        //если t=NULL, вернуть NULL
        if (t == NULL)
            return NULL;
        //пока не встретится узел с нулевым левым указателем,
        while (t->Left() != NULL) {
            S.push(t); //запоминая в стеке S адреса пройденных узлов
            t = t->Left(); //спускаться по левым ветвям
        }
        return t; //возвратить указатель на этот узел
    }
public:
    //конструктор
    InorderIterator(TreeNode<T>* tree, int n);
    //реализации базовых операций прохождения
    virtual void Next(void);
    virtual void Reset(void);
    virtual T& Data(void);
    //назначение итератору нового дерева
    void SetTree(TreeNode<T>* tree);
};

//конструктор
template<class T>
inline InorderIterator<T>::InorderIterator(TreeNode<T>* tree, int n) : Iterator<T>(), root(tree), S(n){
    this->iterationComplete = (this->root == NULL); //дерево может оказаться пустым
    this->current = GoFarLeft(this->root); //узлом сканирования является самый левый узел
}

//движение по дереву
template<class T>
void InorderIterator<T>::Next(void) {
    //ошибка, если все узлы уже посещались
    if (this->iterationComplete) {
        std::cerr << "Next: EndOfList!" << std::endl;
        exit(1);
    }
    //если есть правое поддерево, спуститься до конца по его левой ветви,
    //попутно запоминая в стеке адреса пройденных узлов
    if (this->current->Right() != NULL)
        this->current = GoFarLeft(this->current->Right());
    //правого поддерева нет, но в стеке есть другие узлы,
    //подлежащие обработке. вытолкнуть из стека новый текущий адрес
    else if (!this->S.isEmpty()) { // продвинуться вверх по дереву
        this->current = this->S.pop();
    }
    // нет ни правого поддерева, ни узлов в стеке
    else this->iterationComplete = 1;
}

//установка начальных значений
template<class T>
void InorderIterator<T>::Reset(void) {
    //дейсвтия как у конструктора
    this->iterationComplete = (this->root == NULL);
    this->current = GoFarLeft(this->root);
    this->S.clear(); //и также очищаем стек
}

//геттер данных
template<class T>
T& InorderIterator<T>::Data(void) {
    return this->current->data;
}

//сеттер дерева
template<class T>
void InorderIterator<T>::SetTree(TreeNode<T>* tree) {
    this->root = tree;
}
