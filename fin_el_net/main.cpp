#include "AneuMeshLoader.h"
#include "NeuMeshLoader.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <string_view>
#include <ranges>

using namespace std; //!!! Лучше писать везде явно std:: ///обязательно буду теперь


//!!! Задание на защиту (не удалять!)
//!!! Реализовать на основе std::ranges 
//!!! 1. Создать контейнер всех КЭ (тетраэдров).
//!!! 2. С помощью потокового итератора вывести в файл значения объемов 10 первых КЭ,
//!!!    у которых значение минимального двугранного угла от 0 до 30 градусов.


void test(MeshLoader *loader, const std::string &path) {
    loader->LoadMesh(path);
    set<FiniteElement> sfes;
    vector<FiniteElement> fes;
    vector<BoundaryFiniteElement> bfes;
    vector<int> testv;
    cout << "In case to test, I'll find a finite element made by material 1:" << endl;
    testv = loader->Get_FE_by_material(1);
    if (testv.empty())
        cout << "No such finite elements" << endl;
    else {
        for_each(testv.begin(), testv.end(), [](int x){cout << x << " ";});
        cout <<  endl;
        testv.clear();
    }
    cout << "Also in that case I'll find finite element by nodes with ids 2 4 7:" << endl;
    testv = loader->Get_FE_by_nodes(2, 4, 7);
    if (testv.empty())
        cout << "No such finite elements" << endl;
    else {
        for_each(testv.begin(), testv.end(), [](int x){cout << x << " ";});
        cout <<  endl;
        testv.clear();
    }
    cout << "Now let's look at neighbours of 8 node" << endl;
    vector<set<int>> test = loader->Get_neighbors();
    for_each(test[8].begin(), test[8].end(), [](int x){cout << x << " ";});
    cout <<  endl;
    test.clear();
    cout << "Now I'll insert new nodes" << endl;
    loader->Insertion();
    fes = loader->Get_FiniteElements();
    cout << "Now zero finite element is like:" << fes[0];
    loader->defence("../r");
}
int main(int argc, char** argv) {
    string path = "../myfile.aneu";
    MeshLoader *loader;
    if (argc == 1)
        cout << "No files were given, so we will work with one I keep." << endl;
    else if (argc == 2) {
        path = argv[1];
        cout << "Working with file " << path << endl;
    }
    else
        cout << "There are too many file locations were given, so we will work with one I keep." << endl;
    if (path.rfind( ".aneu") != string::npos)
    {
        loader = new AneuMeshLoader;
    }
    else if(path.rfind( ".neu") != string::npos)
    {
        loader = new NeuMeshLoader;
    }
    else{
        cout << "Error! Unexpected file format!" << endl;
        return 0;
    }
    test(loader, path);
    delete loader;
    return 0;
}
