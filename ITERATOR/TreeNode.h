#pragma once
#include <cstdlib>
#include <iostream>
#include<fstream>
#include <math.h>
#include<queue>
using namespace std;

//BinSTree зависит от TreeNode
template<class T>
class BinSTree;

//класс узла бинарного дерева
template <class T>
class TreeNode
{
private:
    //указатели левого и правого дочерних узлов
    TreeNode<T>* left;
    TreeNode<T>* right;

public:
    //открытый элемент, допускающий обновление
    T data;
    //конструктор
    TreeNode(const T& item, TreeNode<T>* lptr = NULL,
        TreeNode<T>* rptr = NULL) {
        data = item;
        left = lptr;
        right = rptr;
    }

    //методы доступа к полям указателей
    TreeNode<T>* Left() const {
        return left;
    }
    TreeNode<T>* Right() const {
        return right;
    }

    //сеттеры
    void set_Left(TreeNode<T>* newNode) {
        left = newNode;
    }

    void set_Right(TreeNode<T>* newNode) {
        right = newNode;
    }

    //для доступа к полям
    friend class BinSTree<T>;
};

//освободить память, занимаемую узлом
template<class T>
void FreeTreeNode(TreeNode<T>* p) {
    delete p;
}

//создание и инициализация узла бинарного дерева
template<class T>
TreeNode<T>* GetTreeNode(const T& item, TreeNode<T>* lptr = NULL,
    TreeNode<T>* rptr = NULL) {
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

//симметричное рекурсивное прохождение узлов дерева
template<class T>
void Inorder(TreeNode<T>* t, void visit(T& item)) {
    if (t != NULL) {
        Inorder(t->Left(), visit);
        visit(t->data);
        Inorder(t->Right(), visit);
    }
}

//обратное рекурсивное прохождение узлов дерева
template<class T>
void Postorder(TreeNode<T>* t, void visit(T& item)) {
    if (t != NULL) {
        Postorder(t->Left(), visit);
        Postorder(t->Right(), visit);
        visit(t->data);
    }
}

//прямой метод прохождения узлов дерева
template<class T>
void Preorder(TreeNode<T>* t, void visit(T& item)) {
    if (t != NULL) {
        visit(t->data);
        Postorder(t->Left(), visit);
        Postorder(t->Right(), visit);
    }
}

//функция подсчета листьев дерева
//count предусматривает себя как глобальный параметр и передается по ссылке
template<class T>
void CountLeaf(TreeNode<T>* t, int& count) {
    if (t != NULL)
    {
        //используем обратный метод прохождения
        CountLeaf(t->Left(), count);
        CountLeaf(t->Right(), count);
        //является ли узел листовым?
        if (t->Left() == NULL && t->Right() == NULL)
            count++;
    }
}

//количество элементов дерева
template <class T>
void Size(TreeNode<T>* t, int& count) {
    if (t != NULL) {
        count++;
        Size(t->Left(), count);
        Size(t->Right(), count);
    }
}

//функция подсчета глубины дерева
template <class T>
int Depth(TreeNode<T>* t) {
    int depthLeft, depthRight, depthval;
    if (t == NULL)
        //если корневой узел пустой, то глубина дерева -1
        depthval = -1;
    else
    {
        //используем обратный метод прохождения
        depthLeft = Depth(t->Left());
        depthRight = Depth(t->Right());
        depthval = 1 + (depthLeft > depthRight ? depthLeft : depthRight);//прибавляем наибольшего сына
    }
    return depthval;
}

//функция вставки для пострения дерева
template <class T>
void Insert(TreeNode<T>* root, const T item) {
    //t - текущий узел, parent - предыдущий узел
    TreeNode<T>* t = root, * parent = NULL;
    //создание узла из переданного значения
    TreeNode<T>* newNode = GetTreeNode(item);
    //закончить на пустом дереве
    while (t != NULL)
    {
        parent = t; //обновить указатель parent
        //выбор пути
        if (newNode->data < t->data) //если новые данные меньше текущего узла
            t = t->Left(); //идём влево
        else
            t = t->Right(); //а иначе - вправо
    }
    if (parent == NULL) //если родителя нет
        root = newNode; //вставить в качестве корневого узла
    else if (newNode->data < parent->data) //если новые данные меньше родительского узла
        parent->set_Left(newNode); //то вставить в качестве левого потомка
    else
        parent->set_Right(newNode); // иначе вставить в качестве правого потомка
}

//создание бинарного дерева из очереди
template <class T>
TreeNode<T>* CreateBinTree(queue<T> Q_data) {
    TreeNode<T>* root = GetTreeNode(Q_data.front());
    Q_data.pop();
    while (!Q_data.empty()) {
        Insert(root, Q_data.front());
        Q_data.pop();
    }
    return root;
}

//вставка пробелов
void IndentBlanks(int num) {
    for (int i = 0; i < num; i++) {
        cout << " ";
    }
}

//горизонтальная печать дерева на экран
template <class T>
void PrintTree(TreeNode<T>* t, int level) {
    if (t != NULL) { //пока указатель не пуст
        PrintTree(t->Right(), level + 1); //печатаем правое поддерево
        IndentBlanks(6 * level); //вставка пробелов и выравнивание
        cout << t->data << endl;
        PrintTree(t->Left(), level + 1); //печатаем левое поддерево
    }
}

//горизонтальная печать дерева в файл
template <class T>
void PrintTreeFile(TreeNode<T>* t, int level, string s1) {
    if (t != NULL) { //пока указатель не пуст
        ofstream f(s1, ios_base::app);
        PrintTreeFile(t->Right(), level + 1, s1); //печатаем правое поддерево
        for (int i = 0; i < 6 * level; i++) {
            f << " ";
        }
        f << t->data << endl;
        PrintTreeFile(t->Left(), level + 1, s1); //печатаем левое поддерево
    }
}

//функция удаления дерева
template <class T>
void DeleteTree(TreeNode<T>* t) {
    if (t != NULL) {
        DeleteTree(t->Left());
        DeleteTree(t->Right());
        FreeTreeNode(t);
    }
}

//функция удаления дерева под корень
template <class T>
void ClearTree(TreeNode<T>& t) {
    DeleteTree(t);
    //очищаем корень
    t = NULL;
}

//функция создания дубликата дерева с возвращением указателя корня на новое дерво
template<class T>
TreeNode<T>* CopyTree(TreeNode<T>* t) {
    TreeNode<T>* newlptr, * newrptr, * newnode;
    if (t == NULL)
        return NULL;
    if (t->Left() != NULL)
        newlptr = CopyTree(t->Left());
    else
        newlptr = NULL;
    if (t->Right() != NULL)
        newrptr = CopyTree(t->Right());
    else
        newrptr = NULL;
    //новое дерво строится снизу вверх
    newnode = GetTreeNode(t->data, newlptr, newrptr);
    return newnode;
}

//тип координат узла
struct Info {
    int xIndent, yLevel;
};

template <class T>
void Print(queue<T>& Q, queue<Info>& QI) {
    int lastDepth = 0; int lastIndent = 0;
    while (!Q.empty()) {
        Info Position = QI.front();
        QI.pop();
        if (Position.yLevel > lastDepth) {
            cout << endl;
            lastDepth = Position.yLevel;
            lastIndent = 0;
        }
        IndentBlanks((Position.xIndent - lastIndent));
        lastIndent = Position.xIndent;
        cout << Q.front();
        Q.pop();
    }
}

template <class T>
void PrintFile(queue<T>& Q, queue<Info>& QI, string s1) {
    ofstream f(s1, ios_base::app);
    int lastDepth = 0; int lastIndent = 0;
    while (!Q.empty()) {
        Info Position = QI.front();
        QI.pop();
        if (Position.yLevel > lastDepth) {
            f << endl;
            lastDepth = Position.yLevel;
            lastIndent = 0;
        }
        //IndentBlanks((Position.xIndent - lastIndent));
        for (int i = 0; i < (Position.xIndent - lastIndent); i++) {
            f << " ";
        }
        lastIndent = Position.xIndent;
        f << Q.front();
        Q.pop();
    }
}

//прохождение дерева по уровням
template <class T>
void LevelScan(TreeNode<T>* t, queue<T>& out, queue<Info>& inf, int dataWidth, int screenWidth) {
    //запомнить сыновей каждого узла в очереди чтобы их
    //можно было посетить в этом порядке
    queue<TreeNode<T>*> Q;//очередь из узлов
    queue<Info> QI; //очередь из координат узлов
    Info Position;//текущие координаты
    TreeNode<T>* p;//указатель на обрабатываемый узел
    //инициализируем очередь, вставив туда корень
    Q.push(t);
    //инициализируем очередь , вставляя координаты корня
    QI.push({ screenWidth / 2 - (dataWidth / 2),0 });
    //пока очередь не опустеет
    while (!Q.empty()) {
        //удалить первый узел и посетить
        p = Q.front();
        Q.pop();
        Position = QI.front();
        QI.pop();
        out.push(p->data);//вставляем данные из узла в очередь
        inf.push(Position);
        if (p->Left() != NULL) {
            Q.push(p->Left());
            int div = pow(2, (Position.yLevel + 2));
            QI.push({ Position.xIndent - (screenWidth / div) - (dataWidth / 2),Position.yLevel + 1 });
        }
        if (p->Right() != NULL) {
            Q.push(p->Right());
            int div = pow(2, (Position.yLevel + 2));
            QI.push({ Position.xIndent + (screenWidth / div) - (dataWidth / 2),Position.yLevel + 1 });
        }
    }
}

//вертикальная печать дерева на экран
template <class T>
void PrintVTree(TreeNode<T>* t, int dataWidth, int screenWidth, void f(queue<T>& Q_data, queue<Info>& Q_info)) {
    queue<T> Q;
    queue<Info> QI;
    LevelScan(t, Q, QI, dataWidth, screenWidth);
    f(Q, QI);
}

//вертикальная печать дерева в файл
template <class T>
void PrintVTreeFile(TreeNode<T>* t, int dataWidth, int screenWidth, void f(queue<T>& Q_data, queue<Info>& Q_info, string s1), string s) {
    queue<T> Q;
    queue<Info> QI;
    LevelScan(t, Q, QI, dataWidth, screenWidth);
    f(Q, QI, s);
}

