//
// Created by liza on 27.09.2021.
//

#include "NeuMeshLoader.h"
#include <fstream>

#include <stdio.h>
#include "AneuMeshLoader.h"
#include <fstream>


//!!! Замечания аналогичны AneuMeshLoader 


void NeuMeshLoader::LoadMesh(const std::string &fileName) {
    ifstream f(fileName);
    if (!f) {
        throw FileNotFoundException();
    } else {
        cout << "File " << fileName << " was opened successfully!" << endl;
    }

    int n;
    nodes.push_back(Node{0});
    f >> n;
    for (int i = 1; i < n; i++) {
        Node tmp{};
        f >> tmp.x >> tmp.y >> tmp.z;
        tmp.id = i;
        tmp.is_summit = false;
        nodes.push_back(move(tmp));
    }
    f >> n;
    dim = 4;
    finiteelements.reserve(n);
    for (int i = 0; i < n; i++) {
        FiniteElement tmp{};
        int node_id;
        f >> tmp.mat_id;
        tmp.nodes_id.reserve(dim);
        for (int j = 0; j < dim; ++j) {
            f >> node_id;
            tmp.nodes_id.push_back(move(node_id));
        }
        tmp.fe_id = i;
        finiteelements.push_back(move(tmp));
    }

    f >> n;
    bfes.reserve(n);
    for (int i = 0; i < n; i++) {
        BoundaryFiniteElement tmp{};
        int node_id;
        f >> tmp.border_id;
        for (int j = 0; j < dim; j++) {
            f >> node_id;
            tmp.nodes_id.push_back(move(node_id));
        }
        tmp.bfe_id = i;
        bfes.push_back(move(tmp));
    }

    std::set<int> allBNodes = getBoundaryNodesId();
    for (auto &it: nodes) {
        if (std::find(allBNodes.begin(), allBNodes.end(), it.id) != allBNodes.end()) {
            it.is_summit = true;
        }
    }
    std::cout << "Net was loaded successfully!" << std::endl;
    f.close();
    std::cout << "File was closed successfully!" << std::endl;
}