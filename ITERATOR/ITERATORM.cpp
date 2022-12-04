#include <iostream>
#include <fstream>
#include <locale>
#include <chrono>
#include "InorderIterator.h"
#include "BinSTree.h"
using namespace std;

//заполнение массива
int* create_mas(int n, int min, int max) {
    int* res = new int[n];
    srand(time(0)); //задаём условие рандома
    for (int i = 0; i < n; i++)
        res[i] = rand() % (max - min) + min; //заполняем в диапазоне
    return res;
}

//печать массива
void print_mas(int* arr, int n, ostream& strm) {
    for (int i = 0; i < n; i++) {
        if (i != 0 && i % 10 == 0) //когда 10 элементов в строке
            strm << endl;
        strm << arr[i] << " ";
    }
    strm << endl;
}

//сортировка деревом
template <class T>
void TreeSort(T* arr, int n) {
    //бинарное дерево поиска, в которое копируется массив
    BinSTree<T> sortTree;
    int i;
    //включить каждый элемент массива в поисковое дерево
    for (i = 0; i < n; i++)
        sortTree.Insert(arr[i]);
    //объявить итератор симметричного прохождения для sortTree
    InorderIterator<T> treeSortIter(sortTree.GetRoot(), sortTree.DepthB());
    //выполнить симметричное прохождение дерева.
    //скопировать каждый элемент снова в массив
    i = 0;
    //начинаем обход дерева
    while (!treeSortIter.EndOfList()) {
        arr[i++] = treeSortIter.Data();
        treeSortIter.Next();
    }
}

int main() {
    setlocale(0, "");
    ofstream fout; //файл с результатом
    fout.open("Result.txt");
    //по заданию 100 элементов
    int n = 100;
    int* mas = create_mas(n, 0, 1000); //получаем случайный массив чисел от 0 до 1000
    //отображаем начальный массив
    cout << "Start mas" << endl;
    fout << "Start mas" << endl;
    print_mas(mas, n, cout);
    print_mas(mas, n, fout);


    auto begin = std::chrono::steady_clock::now();
    TreeSort(mas, n);
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

    cout << "End mas" << endl;
    fout << "End mas" << endl;
    print_mas(mas, n, cout);
    print_mas(mas, n, fout);
    cout << "Time = " << elapsed_ms.count() << " milliseconds" << endl;
    fout << "Time = " << elapsed_ms.count() << " milliseconds" << endl;
    fout.close();
}

