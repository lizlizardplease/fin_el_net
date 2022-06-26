#include "Structures.h"

std::ostream &operator<<(std::ostream &out, const Node &node) {
    out << "Node: " << node.id << endl;
    out << "X: " << node.x << " Y: " << node.y << " Z: " << node.z << endl;
    if(node.is_summit)
        out << "Node is a summit";
    else
        out << "Node is not a summit";
    out << "\n\n";
    return out;
}
bool FiniteElement::operator==(const FiniteElement &other){
    return fe_id == other.fe_id;
}
std::ostream &operator<<(std::ostream &out, const vector<Node> &nodes) {
    for (const auto &it: nodes)
        out << it;
    return out;
}
std::ostream &operator<<(std::ostream &out, const set<Node> &nodes) {
    for (const auto &it: nodes)
        out << it;
    return out;
}
std::ostream &operator<<(std::ostream &out, const map<int,Node> &nodes){
    for (const auto &it: nodes)
        out << it.second;
    return out;
}
std::ostream &operator<<(std::ostream &out, const FiniteElement &fe) {
    out << "Finite Element: " << fe.fe_id << endl;
    out << "Id of material it made by: " << fe.mat_id << endl;
    out << "Finite Element's nodes ids: ";
    for (auto &it: fe.nodes_id) {
        std::cout << it << " ";
    }
    out << endl << endl;
    return out;
}

std::ostream &operator<<(std::ostream &out, const std::vector<FiniteElement> &fes) {
    for (const auto &it: fes)
        out << it;
    return out;
}

std::ostream &operator<<(std::ostream &out, const BoundaryFiniteElement &bfe) {
    out << "Boundary Finite Element: " << bfe.bfe_id << endl;
    out << "It's boundary id: " << bfe.border_id << endl;
    out << "Finite Element's nodes ids: ";
    for (auto &it: bfe.nodes_id) {
        out << it << " ";
    }
    out << endl << endl;
    return out;
}

std::ostream &operator<<(std::ostream &out, const std::vector<BoundaryFiniteElement> &bfes) {
    for (const auto &it: bfes)
        out << it;
    return out;
}
