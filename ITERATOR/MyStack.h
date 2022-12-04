#pragma once
#include <iostream>
#include <cassert> //��� assert
#include <iomanip> //��� setw
using std::cout; using std::setw; using std::endl;

template <typename T>
class MyStack {
private:
    T* stacklist; //��������� �� ����
    const int size; //������ �������
    int top; //������ �������
public:
    MyStack(int = 10); //�� ��������� ������ ����� ����� 10 ���������
    MyStack(const MyStack<T>&); //����������� �����������
    ~MyStack(); //����������

    const T& peek(int) const; //�������� n-� ������� �� ������� �����
    bool isEmpty() const; //�������� �� ������ ����
    int getSize() const; //�������� ������ �����
    T* getPtr() const; //�������� ��������� �� ����
    int getTop() const; //�������� ����� �������� �������� � �����

    void push(const T&); //��������� ������� � ������� �����
    T pop(); //������� ������� �� ������� ����� � ������� ���
    void printStack(); //����� ����� �� �����
    void clear(); //������� �����
};


//����������� �����
template <typename T>
MyStack<T>::MyStack(int maxSize) : size(maxSize) { //������������� ���������
    stacklist = new T[size + 1]; //�������� ������ ��� ����
    top = 0; //�������������� ������� ������� �����;
}

//����������� �����������
template <typename T>
MyStack<T>::MyStack(const MyStack<T>& otherStack) :
    size(otherStack.getSize()) { //������������� ���������
    stacklist = new T[size]; //�������� ������ ��� ����� ����
    top = otherStack.getTop(); //������� ������ �������
    for (int i = 0; i < top; i++) //������ �� �����
        stacklist[i] = otherStack.getPtr()[i]; //�������� ��������
}

//����������� c����
template <typename T>
MyStack<T>::~MyStack() {
    delete[] stacklist; //������� ����
}

//������� ���������� �������� � ����
template <typename T>
void MyStack<T>::push(const T& value) {
    //assert ��������� ������ �����
    assert(top < size); //����� �������� �������� ������ ���� ������ ������� �����
    stacklist[top++] = value; //�������� ������� � ����
}

//������� �������� �������� �� �����
template <typename T>
T MyStack<T>::pop() {
    //assert ��������� ������ �����
    assert(top > 0); //����� �������� �������� ������ ���� ������ 0
    return stacklist[--top]; //������� ������� �� �����
}

//������� ���������� n-� ������� �� ������� �����
template <typename T>
const T& MyStack<T>::peek(int nom) const {
    //�������� ��������� �������
    assert(nom <= top);
    return stacklist[top - nom]; // ������� n-� ������� �����
}

//������� ��������� ���� �� �������
template <typename T>
bool MyStack<T>::isEmpty() const {
    return (top == 0);
}

//����� ����� �� �����
template <typename T>
void MyStack<T>::printStack() {
    for (int i = top - 1; i >= 0; i--) //������ � �������
        cout << "|" << setw(4) << stacklist[i] << endl; //��������
}

//������� �����
template <typename T>
void MyStack<T>::clear() {
    top = 0;
}

//������� ������ �����
template <typename T>
int MyStack<T>::getSize() const {
    return size;
}

//������� ��������� �� ���� (��� ������������ �����������)
template <typename T>
T* MyStack<T>::getPtr() const {
    return stacklist;
}

//������� ������ �����
template <typename T>
int MyStack<T>::getTop() const {
    return top;
}

