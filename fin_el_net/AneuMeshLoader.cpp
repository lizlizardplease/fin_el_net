#include "AneuMeshLoader.h"
#include <fstream>
#include <string>


void AneuMeshLoader::LoadMesh(const string& fileName) {
    
    fstream f(fileName); //!!! Вы файл и читать и записывать собираетесь? Если файл читается, то использовать надо ifstream
    
    if (!f.is_open()) {
        throw FileNotFoundException();
    } else {
        cout << "File " << fileName << " was opened successfully!" << endl;
    }
    int n;
    f >> n >> dim;
    nodes.push_back(move(Node{0}));
    for (int i = 1; i <= n; i++) {
        Node tmp{};
        f >> tmp.x >> tmp.y >> tmp.z;
        tmp.id = i;
        tmp.is_summit = false;
        nodes.push_back(move(tmp));
    }
    f >> n >> dim;
    finiteelements.reserve(n);
    for (int i = 0; i < n; i++) {
        FiniteElement tmp{};
        int node_id;
        f >> tmp.mat_id;
        //tmp.nodes_id.reserve(dim);
        for (int j = 0; j < dim; ++j) {
            f >> node_id;
            tmp.nodes_id.push_back(move(node_id)); //!!! С какой целью используется move для int?
        }
        tmp.fe_id = i;
        finiteelements.push_back(move(tmp));
    }

    f >> n >> dim;
    bfes.reserve(n);
    for (int i = 0; i <= n; i++) {
        BoundaryFiniteElement tmp{};
        int node_id;
        f >> tmp.border_id;
        for (int j = 0; j < dim; j++) {
            f >> node_id;
            tmp.nodes_id.push_back(move(node_id));//!!! С какой целью используется move для int?
        }
        tmp.bfe_id = i;
        bfes.push_back(move(tmp));
    }

    set<int> allBNodes = getBoundaryNodesId();
    
    for (auto &it: nodes) {
        if (allBNodes.find(it.id) != allBNodes.end()) {
            it.is_summit = true;
        }
    }
    /*cout << nodes;
    cout << finiteelements;
   cout << bfes;*/
    cout << "Net was loaded successfully!" << endl;
    f.close();
    cout << "File was closed successfully!" << endl;
}

