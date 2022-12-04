#pragma once
#include <iostream>
#include <cassert> //для assert
#include <iomanip> //для setw
using std::cout; using std::setw; using std::endl;

template <typename T>
class MyStack {
private:
    T* stacklist; //указатель на стек
    const int size; //размер массива
    int top; //индекс вершины
public:
    MyStack(int = 10); //по умолчанию размер стека равен 10 элементам
    MyStack(const MyStack<T>&); //конструктор копирования
    ~MyStack(); //деструктор

    const T& peek(int) const; //показать n-й элемент от вершины стека
    bool isEmpty() const; //проверка на пустой стек
    int getSize() const; //получить размер стека
    T* getPtr() const; //получить указатель на стек
    int getTop() const; //получить номер текущего элемента в стеке

    void push(const T&); //поместить элемент в вершину стека
    T pop(); //удалить элемент из вершины стека и вернуть его
    void printStack(); //вывод стека на экран
    void clear(); //очистка стека
};


//конструктор стека
template <typename T>
MyStack<T>::MyStack(int maxSize) : size(maxSize) { //инициализация константы
    stacklist = new T[size + 1]; //выделить память под стек
    top = 0; //инициализируем текущий элемент нулем;
}

//конструктор копирования
template <typename T>
MyStack<T>::MyStack(const MyStack<T>& otherStack) :
    size(otherStack.getSize()) { //инициализация константы
    stacklist = new T[size]; //выделить память под новый стек
    top = otherStack.getTop(); //передаём индекс вершины
    for (int i = 0; i < top; i++) //пробег по стеку
        stacklist[i] = otherStack.getPtr()[i]; //копируем значения
}

//деструктора cтека
template <typename T>
MyStack<T>::~MyStack() {
    delete[] stacklist; //удаляем стек
}

//функция добавления элемента в стек
template <typename T>
void MyStack<T>::push(const T& value) {
    //assert проверяет размер стека
    assert(top < size); //номер текущего элемента должен быть меньше размера стека
    stacklist[top++] = value; //помещаем элемент в стек
}

//функция удаления элемента из стека
template <typename T>
T MyStack<T>::pop() {
    //assert проверяет размер стека
    assert(top > 0); //номер текущего элемента должен быть больше 0
    return stacklist[--top]; //удаляем элемент из стека
}

//функция возвращает n-й элемент от вершины стека
template <typename T>
const T& MyStack<T>::peek(int nom) const {
    //проверка диапазона индекса
    assert(nom <= top);
    return stacklist[top - nom]; // вернуть n-й элемент стека
}

//функция проверает стек на пустоту
template <typename T>
bool MyStack<T>::isEmpty() const {
    return (top == 0);
}

//вывод стека на экран
template <typename T>
void MyStack<T>::printStack() {
    for (int i = top - 1; i >= 0; i--) //пробег с вершины
        cout << "|" << setw(4) << stacklist[i] << endl; //печатаем
}

//очистка стека
template <typename T>
void MyStack<T>::clear() {
    top = 0;
}

//вернуть размер стека
template <typename T>
int MyStack<T>::getSize() const {
    return size;
}

//вернуть указатель на стек (для конструктора копирования)
template <typename T>
T* MyStack<T>::getPtr() const {
    return stacklist;
}

//вернуть размер стека
template <typename T>
int MyStack<T>::getTop() const {
    return top;
}

