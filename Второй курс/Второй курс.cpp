#include <iostream>
#include <random>
#include <chrono>
#include <fstream>
#include "BoolVector.h"

template <typename T>
void swap(T& el1, T& el2)
{
    T x = el1;
    el1 = el2;
    el2 = x;
}

void QuickSort(int* mass, int start, int end)
{
    int i = start;
    int j = end;
    int average = mass[(i + j) / 2];

    while (i <= j)
    {
        while (mass[i] < average)
            i++;
        while (mass[j] > average)
            j--;
        if (i <= j)
        {
            swap(mass[i], mass[j]);
            i++;
            j--;
        }
    }
    if (j > start)
        QuickSort(mass, start, j);
    if (i < end)
        QuickSort(mass, i, end);
}

void sorting(int* mas, int l, int r, int k) {
    unsigned int mask = 1;
    int i = l, j = r;

    if (l >= r || k < 0)
        return;

    mask <<= k;

    while (i <= j) {
        while ((i <= j) && !((bool)(mas[i] & mask))) i++;
        while ((i <= j) && (bool)(mas[j] & mask)) j--;
        if (i < j) {
            swap(mas[i], mas[j]);
            i++;
            j--;
        }
    }
    sorting(mas, l, j, k - 1);
    sorting(mas, i, r, k - 1);
}


void BitSort(int* mas, int size) {
    int temp, l = 0, r = size - 1;
    int i = l, j = r;
    unsigned int mask = 1;
    mask <<= 31;
    while (i <= j) {

        while (mas[i] & mask)
            i++;
        while (!(mas[j] & mask))
            j--;

        if (i < j) {
            swap(mas[i], mas[j]);
            i++;
            j--;
        }
    }
    sorting(mas, l, j, 30);
    sorting(mas, i, r, 30);
}


void writeIn(std::ifstream& stream, int *mass, int len)
{
    for (int i = 0; i < len; i++)
    {
        stream >> mass[i];
    }
}

void copy(int* Destination, const int* original, int len)
{
    for (int i = 0; i < len; i++)
    {
        Destination[i] = original[i];
    }
}

bool checkSort(int* mass, int len)
{
    for (int i = 0; i < len-1; i++)
    {
        if (mass[i] > mass[i + 1]) return false;
    }
    return true;
}

int main12()
{
    int SIZE[3] = { 1000, 10000, 100000 };
    int Value[3] = { 10, 1000, 100000 };
    
    std::ifstream in("D:\\mass.txt");
    int* mass;
    int* testMass;
    for (int sz = 0; sz < 3; sz++)
    {
        testMass = new int[SIZE[sz]];
        mass = new int[SIZE[sz]];
        for (int vl = 0; vl < 3; vl++)
        {
            writeIn(in, mass, SIZE[sz]);
            for (int Try = 0; Try < 3; Try++)
            {
                copy(testMass, mass, SIZE[sz]);
    
                std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
                BitSort(testMass, SIZE[sz]);
                std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
                std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds   value: " 
                    << Value[vl] << " size: " << SIZE[sz] << " sorted? " << checkSort(testMass, SIZE[sz]) << " test num: " << Try + 1 << "\n";
            }
            std::cout << '\n';
        }
        delete[] testMass;
        delete[] mass;
    }
    
    in.close();
    return 0;
}
