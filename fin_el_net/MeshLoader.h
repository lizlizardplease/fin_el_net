#ifndef MESHLOADER_H
#define MESHLOADER_H
#include "Exceptions.h"
#include "string"
#include "Structures.h"
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <ranges>
#include <unordered_set>

using namespace std;
class MeshLoader{
protected:
    vector <Node> nodes;
    vector <FiniteElement> finiteelements;
    vector <BoundaryFiniteElement> bfes;
    int dim;
public:
    virtual void LoadMesh(const string&) = 0;
    //загрузка сетки
    virtual ~MeshLoader() = default;
    vector<Node>&  Get_Nodes();
    vector<FiniteElement>& Get_FiniteElements();
    vector<BoundaryFiniteElement>& Get_BFEs();
    //методы, позволяющие получить STL-контейнеры узлов, конечных элементов и граничных элементов
    vector<int> Get_FE_by_nodes(int id1, int id2, int id3);
    //метод, позволяющий найти КЭ по ID трех его вершинных узлов
    vector<int> Get_FE_by_edge(int id1, int id2);
    //метод, позволяющий найти КЭ по ребру, заданному с помощью ID двух узлов
    set<int> Get_nodes_by_border(int id);
    //метод, возвращающий контейнер граничных узлов по ID границы
    vector <int> Get_FE_by_material(int id);
    //метод, возвращающий контейнер КЭ с заданным ID области;
    vector <int> Get_BFE_by_border(int id);
    //метод, возвращающий контейнер граничных КЭ с заданным ID границы;
    void Insertion();
    //метод, производящий вставку новых узлов в середины ребер существующих КЭ
    // (включая граничные КЭ). Учесть, что обновляются как списки узлов каждого КЭ, так общий список узлов сетки
    vector <set <int>> Get_neighbors();
    //метод, создающий контейнер, n-ый элемент которого хранит контейнер всех «соседей» по ребрам для узла n;
    void printNode(const Node &node);
    void printFE(const FiniteElement &fe);
    void printBFE(const BoundaryFiniteElement &bfe);
    //вывод структур на консоль
    set<int> getBoundaryNodesId();
    double len(const Edge &e){
        return sqrt((nodes[e.node1].x - nodes[e.node2].x)*(nodes[e.node1].x - nodes[e.node2].x)
        + (nodes[e.node1].y - nodes[e.node2].y)*(nodes[e.node1].y - nodes[e.node2].y) + (nodes[e.node1].z - nodes[e.node2].z)*(nodes[e.node1].z - nodes[e.node2].z));
    }
    bool is_small(const FiniteElement &x);
    double volume(const FiniteElement &x);
    vector<double> createplane(const vector<Node>& points);
    void defence(const std::string& filepath);
};

#endif //MESHLOADER_H