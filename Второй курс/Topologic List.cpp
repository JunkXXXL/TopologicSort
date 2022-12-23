#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include<iostream>
#include <fstream>
#include <vector>

struct Trailer;
struct Lider
{
    int key;
    int count;
    Lider* nx;
    Trailer* tr;

};
struct Trailer
{
    Lider* ld;
    Trailer* nx;
};

void AddEdge(Lider*& vertexes, int vertexA, int vertexB)
{
    Lider* ptrA = NULL, * ptrB = NULL;
    for (ptrA = vertexes; ptrA && ptrA->key != vertexA; ptrA = ptrA->nx);
    for (ptrB = vertexes; ptrB && ptrB->key != vertexB; ptrB = ptrB->nx);
    bool setEdge = true;
    if (ptrA && ptrB)
    {
        Trailer* trTmp = ptrA->tr;

        for (; trTmp && trTmp->ld != ptrB; trTmp = trTmp->nx) {};
        setEdge = !((bool)trTmp);
    }
    else
    {
        if (!ptrA)
        {
            ptrA = new Lider;
            ptrA->key = vertexA;
            ptrA->count = 0;
            ptrA->nx = NULL;
            ptrA->tr = NULL;
            ptrA->nx = vertexes;
            vertexes = ptrA;
        }

        if (!ptrB)
        {
            ptrB = new Lider;
            ptrB->key = vertexB;
            ptrB->count = 0;

            ptrB->nx = NULL;
            ptrB->tr = NULL;
            ptrB->nx = vertexes;
            vertexes = ptrB;
        }
    }

    if (setEdge)
    {
        ptrB->count++;
        Trailer* elemTr = new Trailer;
        elemTr->ld = ptrB;
        elemTr->nx = ptrA->tr;
        ptrA->tr = elemTr;
    }
}

Lider* CopyLider(Lider*& vertexes)
{
    Lider* ld = nullptr;
    Lider* vertexA = vertexes;
    
    while (vertexA)
    {
        for (Trailer* tr = vertexA->tr; tr; tr = tr->nx)
        {
            AddEdge(ld, vertexA->key, tr->ld->key);
        }
        vertexA = vertexA->nx;
    }
    return ld;
}

void printGraph(Lider*& vert)
{
    Lider* ld = vert;
    if (!ld) std::cout << "Empty ";
    while (ld)
    {
        std::cout << ld->key;
        ld = ld->nx;
    }
    std::cout << "\n";
}

bool deleteVertex(Lider*& vertexes, int vertex)
{
    Lider* ptrVert = vertexes;
    Lider* killThis = nullptr;
    Trailer* killTrailer = nullptr;
    if (ptrVert->key == vertex)
    {
        killThis = vertexes;
        vertexes = vertexes->nx;
        for (Trailer* tr = killThis->tr; tr;)
        {
            killTrailer = tr;
            tr = tr->nx;
            delete killTrailer;
        }
        delete killThis;
        return true;
    }
    else
    {
        for (; ptrVert && ptrVert->nx->key != vertex; ptrVert = ptrVert->nx);

        if (ptrVert != nullptr)
        {
            killThis = ptrVert->nx;
            ptrVert->nx = ptrVert->nx->nx;
            for (Trailer* tr = killThis->tr; tr;)
            {
                killTrailer = tr;
                tr = tr->nx;
                delete killTrailer;
            }
            delete killThis;
            return true;
        }
        else
            return false;
    }
}

std::vector<int> topologicSort(Lider* vertexes)
{
    std::vector<int> to_ret;
    bool isCycle = false;
    Lider* ptrVert = nullptr;
    while (vertexes)
    {
        isCycle = true;
        ptrVert = vertexes;
        for (; ptrVert; ptrVert = ptrVert->nx)
        {
            if (ptrVert->count == 0)
            {
                for (; ptrVert->tr; ptrVert->tr = ptrVert->tr->nx)
                {
                    ptrVert->tr->ld->count--;
                }
                to_ret.push_back(ptrVert->key);
                deleteVertex(vertexes, ptrVert->key);
                isCycle = false;
                break;
            }
        }
        
        if (isCycle)
        {
            throw "Cycle was found";
        }
        
    }
    return to_ret;
}

bool test()
{
    std::ifstream file;
    file.open("C:\\DOC.txt");
    Lider* graph = NULL;
    int vertexA = 0, vertexB = 0;
    std::vector<int> solution;
    if (file)
    {

        while (file >> vertexA >> vertexB)
        {
            AddEdge(graph, vertexA, vertexB);
        }
        file.close();

        try
        {
            solution = topologicSort(graph);
            return true;
            for (int i = 0; i < solution.size(); i++)
            {
                std::cout << solution[i] << " ";
            }
        }
        catch (const char* text)
        {
            std::cerr << text;
            return false;
        }
    }
}

int main()
{
    //while (true) {
        test();
    //}
    return 0;
}