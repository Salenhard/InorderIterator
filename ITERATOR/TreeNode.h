#pragma once
#include <cstdlib>
#include <iostream>
#include<fstream>
#include <math.h>
#include<queue>
using namespace std;

//BinSTree ������� �� TreeNode
template<class T>
class BinSTree;

//����� ���� ��������� ������
template <class T>
class TreeNode
{
private:
    //��������� ������ � ������� �������� �����
    TreeNode<T>* left;
    TreeNode<T>* right;

public:
    //�������� �������, ����������� ����������
    T data;
    //�����������
    TreeNode(const T& item, TreeNode<T>* lptr = NULL,
        TreeNode<T>* rptr = NULL) {
        data = item;
        left = lptr;
        right = rptr;
    }

    //������ ������� � ����� ����������
    TreeNode<T>* Left() const {
        return left;
    }
    TreeNode<T>* Right() const {
        return right;
    }

    //�������
    void set_Left(TreeNode<T>* newNode) {
        left = newNode;
    }

    void set_Right(TreeNode<T>* newNode) {
        right = newNode;
    }

    //��� ������� � �����
    friend class BinSTree<T>;
};

//���������� ������, ���������� �����
template<class T>
void FreeTreeNode(TreeNode<T>* p) {
    delete p;
}

//�������� � ������������� ���� ��������� ������
template<class T>
TreeNode<T>* GetTreeNode(const T& item, TreeNode<T>* lptr = NULL,
    TreeNode<T>* rptr = NULL) {
    TreeNode<T>* p;
    p = new TreeNode<T>(item, lptr, rptr);
    //�������� ������
    if (p == NULL)
    {
        cout << "Error!" << endl;
        exit(1);
    }
    return p;
}

//������������ ����������� ����������� ����� ������
template<class T>
void Inorder(TreeNode<T>* t, void visit(T& item)) {
    if (t != NULL) {
        Inorder(t->Left(), visit);
        visit(t->data);
        Inorder(t->Right(), visit);
    }
}

//�������� ����������� ����������� ����� ������
template<class T>
void Postorder(TreeNode<T>* t, void visit(T& item)) {
    if (t != NULL) {
        Postorder(t->Left(), visit);
        Postorder(t->Right(), visit);
        visit(t->data);
    }
}

//������ ����� ����������� ����� ������
template<class T>
void Preorder(TreeNode<T>* t, void visit(T& item)) {
    if (t != NULL) {
        visit(t->data);
        Postorder(t->Left(), visit);
        Postorder(t->Right(), visit);
    }
}

//������� �������� ������� ������
//count ��������������� ���� ��� ���������� �������� � ���������� �� ������
template<class T>
void CountLeaf(TreeNode<T>* t, int& count) {
    if (t != NULL)
    {
        //���������� �������� ����� �����������
        CountLeaf(t->Left(), count);
        CountLeaf(t->Right(), count);
        //�������� �� ���� ��������?
        if (t->Left() == NULL && t->Right() == NULL)
            count++;
    }
}

//���������� ��������� ������
template <class T>
void Size(TreeNode<T>* t, int& count) {
    if (t != NULL) {
        count++;
        Size(t->Left(), count);
        Size(t->Right(), count);
    }
}

//������� �������� ������� ������
template <class T>
int Depth(TreeNode<T>* t) {
    int depthLeft, depthRight, depthval;
    if (t == NULL)
        //���� �������� ���� ������, �� ������� ������ -1
        depthval = -1;
    else
    {
        //���������� �������� ����� �����������
        depthLeft = Depth(t->Left());
        depthRight = Depth(t->Right());
        depthval = 1 + (depthLeft > depthRight ? depthLeft : depthRight);//���������� ����������� ����
    }
    return depthval;
}

//������� ������� ��� ��������� ������
template <class T>
void Insert(TreeNode<T>* root, const T item) {
    //t - ������� ����, parent - ���������� ����
    TreeNode<T>* t = root, * parent = NULL;
    //�������� ���� �� ����������� ��������
    TreeNode<T>* newNode = GetTreeNode(item);
    //��������� �� ������ ������
    while (t != NULL)
    {
        parent = t; //�������� ��������� parent
        //����� ����
        if (newNode->data < t->data) //���� ����� ������ ������ �������� ����
            t = t->Left(); //��� �����
        else
            t = t->Right(); //� ����� - ������
    }
    if (parent == NULL) //���� �������� ���
        root = newNode; //�������� � �������� ��������� ����
    else if (newNode->data < parent->data) //���� ����� ������ ������ ������������� ����
        parent->set_Left(newNode); //�� �������� � �������� ������ �������
    else
        parent->set_Right(newNode); // ����� �������� � �������� ������� �������
}

//�������� ��������� ������ �� �������
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

//������� ��������
void IndentBlanks(int num) {
    for (int i = 0; i < num; i++) {
        cout << " ";
    }
}

//�������������� ������ ������ �� �����
template <class T>
void PrintTree(TreeNode<T>* t, int level) {
    if (t != NULL) { //���� ��������� �� ����
        PrintTree(t->Right(), level + 1); //�������� ������ ���������
        IndentBlanks(6 * level); //������� �������� � ������������
        cout << t->data << endl;
        PrintTree(t->Left(), level + 1); //�������� ����� ���������
    }
}

//�������������� ������ ������ � ����
template <class T>
void PrintTreeFile(TreeNode<T>* t, int level, string s1) {
    if (t != NULL) { //���� ��������� �� ����
        ofstream f(s1, ios_base::app);
        PrintTreeFile(t->Right(), level + 1, s1); //�������� ������ ���������
        for (int i = 0; i < 6 * level; i++) {
            f << " ";
        }
        f << t->data << endl;
        PrintTreeFile(t->Left(), level + 1, s1); //�������� ����� ���������
    }
}

//������� �������� ������
template <class T>
void DeleteTree(TreeNode<T>* t) {
    if (t != NULL) {
        DeleteTree(t->Left());
        DeleteTree(t->Right());
        FreeTreeNode(t);
    }
}

//������� �������� ������ ��� ������
template <class T>
void ClearTree(TreeNode<T>& t) {
    DeleteTree(t);
    //������� ������
    t = NULL;
}

//������� �������� ��������� ������ � ������������ ��������� ����� �� ����� �����
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
    //����� ����� �������� ����� �����
    newnode = GetTreeNode(t->data, newlptr, newrptr);
    return newnode;
}

//��� ��������� ����
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

//����������� ������ �� �������
template <class T>
void LevelScan(TreeNode<T>* t, queue<T>& out, queue<Info>& inf, int dataWidth, int screenWidth) {
    //��������� ������� ������� ���� � ������� ����� ��
    //����� ���� �������� � ���� �������
    queue<TreeNode<T>*> Q;//������� �� �����
    queue<Info> QI; //������� �� ��������� �����
    Info Position;//������� ����������
    TreeNode<T>* p;//��������� �� �������������� ����
    //�������������� �������, ������� ���� ������
    Q.push(t);
    //�������������� ������� , �������� ���������� �����
    QI.push({ screenWidth / 2 - (dataWidth / 2),0 });
    //���� ������� �� ��������
    while (!Q.empty()) {
        //������� ������ ���� � ��������
        p = Q.front();
        Q.pop();
        Position = QI.front();
        QI.pop();
        out.push(p->data);//��������� ������ �� ���� � �������
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

//������������ ������ ������ �� �����
template <class T>
void PrintVTree(TreeNode<T>* t, int dataWidth, int screenWidth, void f(queue<T>& Q_data, queue<Info>& Q_info)) {
    queue<T> Q;
    queue<Info> QI;
    LevelScan(t, Q, QI, dataWidth, screenWidth);
    f(Q, QI);
}

//������������ ������ ������ � ����
template <class T>
void PrintVTreeFile(TreeNode<T>* t, int dataWidth, int screenWidth, void f(queue<T>& Q_data, queue<Info>& Q_info, string s1), string s) {
    queue<T> Q;
    queue<Info> QI;
    LevelScan(t, Q, QI, dataWidth, screenWidth);
    f(Q, QI, s);
}

