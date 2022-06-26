#ifndef FIN_EL_NET_STRUCTURES_H
#define FIN_EL_NET_STRUCTURES_H
#include <vector>
#include <set>
#include <map>
#include "iostream"
#include <bits/stdc++.h>
#include <cmath>
using namespace std;

//!!! Между объявлениями должна быть 1-2 строки для лучшей читаемости

struct Node{
    int id;
    double x, y, z;
    bool is_summit;
    friend std::ostream &operator<<(std::ostream &, const Node &);
    friend std::ostream &operator<<(std::ostream &, const vector<Node> &);
    friend std::ostream &operator<<(std::ostream &, const set<Node> &);
    friend std::ostream &operator<<(std::ostream &, const map<int,Node> &);
    friend bool operator <(const Node &lhs, const Node &rhs)
    { 
        return lhs.id < rhs.id; 
    };
    
    friend bool operator >(const Node &lhs, const Node &rhs)
    { 
        return lhs.id > rhs.id; 
    };
};
struct Edge{
    int node1;
    int node2;
    int baby;
    Edge(int i, int j): node1(i), node2(j){};
    friend bool operator==(const Edge& x, const Edge& y){
        return (y.node1 == x.node1 && x.node2 == y.node2);
    }
};
struct FiniteElement{
    int fe_id;
    int mat_id;
    vector <int> nodes_id;
    vector <Edge> edges;
    friend std::ostream &operator<<(std::ostream &, const FiniteElement &);
    friend std::ostream &operator<<(std::ostream &, const std::vector<FiniteElement> &);
    bool operator==(const FiniteElement &other);
    void get_edges(){
        for(int i = 0; i < nodes_id.size(); i++){
            for(int j = i; j < nodes_id.size(); j++){
                Edge x = Edge(nodes_id[i], nodes_id[j]);
                edges.push_back(move(x));
            }
        }
    }
};

struct BoundaryFiniteElement : public FiniteElement{
    int bfe_id;
    int border_id;

    friend std::ostream &operator<<(std::ostream &, const BoundaryFiniteElement &);
    friend std::ostream &operator<<(std::ostream &, const std::vector<BoundaryFiniteElement> &);
    //void get_edges();
};


#endif //FIN_EL_NET_STRUCTURES_H
