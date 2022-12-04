#pragma once
#include "MyStack.h"
#include "TreeNode.h"
#include "Iterator.h"
template <class T>
class InorderIterator : public Iterator<T> {
private:
    //���� ������� �����
    MyStack<TreeNode <T>*> S;
    //������ ������ � ������� ����
    TreeNode<T>* root, * current;
    //������������ ������ ���������. ������������ �������� Next
    TreeNode<T>* GoFarLeft(TreeNode<T>* t) {
        //���� t=NULL, ������� NULL
        if (t == NULL)
            return NULL;
        //���� �� ���������� ���� � ������� ����� ����������,
        while (t->Left() != NULL) {
            S.push(t); //��������� � ����� S ������ ���������� �����
            t = t->Left(); //���������� �� ����� ������
        }
        return t; //���������� ��������� �� ���� ����
    }
public:
    //�����������
    InorderIterator(TreeNode<T>* tree, int n);
    //���������� ������� �������� �����������
    virtual void Next(void);
    virtual void Reset(void);
    virtual T& Data(void);
    //���������� ��������� ������ ������
    void SetTree(TreeNode<T>* tree);
};

//�����������
template<class T>
inline InorderIterator<T>::InorderIterator(TreeNode<T>* tree, int n) : Iterator<T>(), root(tree), S(n){
    this->iterationComplete = (this->root == NULL); //������ ����� ��������� ������
    this->current = GoFarLeft(this->root); //����� ������������ �������� ����� ����� ����
}

//�������� �� ������
template<class T>
void InorderIterator<T>::Next(void) {
    //������, ���� ��� ���� ��� ����������
    if (this->iterationComplete) {
        std::cerr << "Next: EndOfList!" << std::endl;
        exit(1);
    }
    //���� ���� ������ ���������, ���������� �� ����� �� ��� ����� �����,
    //������� ��������� � ����� ������ ���������� �����
    if (this->current->Right() != NULL)
        this->current = GoFarLeft(this->current->Right());
    //������� ��������� ���, �� � ����� ���� ������ ����,
    //���������� ���������. ���������� �� ����� ����� ������� �����
    else if (!this->S.isEmpty()) { // ������������ ����� �� ������
        this->current = this->S.pop();
    }
    // ��� �� ������� ���������, �� ����� � �����
    else this->iterationComplete = 1;
}

//��������� ��������� ��������
template<class T>
void InorderIterator<T>::Reset(void) {
    //�������� ��� � ������������
    this->iterationComplete = (this->root == NULL);
    this->current = GoFarLeft(this->root);
    this->S.clear(); //� ����� ������� ����
}

//������ ������
template<class T>
T& InorderIterator<T>::Data(void) {
    return this->current->data;
}

//������ ������
template<class T>
void InorderIterator<T>::SetTree(TreeNode<T>* tree) {
    this->root = tree;
}
