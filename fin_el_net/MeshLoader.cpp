#include "MeshLoader.h"
#include <ranges>
#include "Hash.h"
using namespace std;


vector<Node>& MeshLoader::Get_Nodes() {
    return nodes;
}
vector<FiniteElement>& MeshLoader::Get_FiniteElements() {
    return finiteelements;
}
vector<BoundaryFiniteElement>& MeshLoader::Get_BFEs() {
    return bfes;
}


vector<int> MeshLoader::Get_FE_by_nodes(int id1, int id2, int id3) {
    vector<int> ans;
    auto it = finiteelements.begin();
    while (it != finiteelements.end()){
        it = find_if(it, finiteelements.end(), [id1, id2, id3](const FiniteElement &x) {
            return ((find(x.nodes_id.begin(), x.nodes_id.end(), id1) != x.nodes_id.end()) &&
                    (find(x.nodes_id.begin(), x.nodes_id.end(), id2) != x.nodes_id.end()) &&
                    (find(x.nodes_id.begin(), x.nodes_id.end(), id3) != x.nodes_id.end())
            );
        });
        if (it != finiteelements.end()) {
            ans.push_back(it->fe_id);
            it++;
        }
    }
    return ans;
}
vector<int> MeshLoader::Get_FE_by_edge(int id1, int id2) {
    vector<int> ans;
    auto it = finiteelements.begin();
    while (it != finiteelements.end()) {
        it = find_if(it, finiteelements.end(), [id1, id2](const FiniteElement &x)  {
            return ((find(x.nodes_id.begin(), x.nodes_id.end(), id1) != x.nodes_id.end()) &&
                    (find(x.nodes_id.begin(), x.nodes_id.end(), id2) != x.nodes_id.end())
            );
        });
        if (it != finiteelements.end()) {
            ans.push_back(it->fe_id);
            it++;
        }
    }
    return ans;
}

set<int> MeshLoader::Get_nodes_by_border(int id) {
    set <int> ans;
    auto it = bfes.begin();
    while(it != bfes.end()){
        it = find_if(it, bfes.end(), [id](const BoundaryFiniteElement &x){
            return x.border_id == id;});
        for (const auto& x : it->nodes_id)
            ans.insert(x);
        it++;
    }
    return ans;
}
vector<int>MeshLoader::Get_FE_by_material(int id) {
    vector<int> ans;
    auto it = finiteelements.begin();
    while (it != finiteelements.end()) {
        it = find_if(it, finiteelements.end(), [id](const FiniteElement& x) {
            return x.mat_id == id; });
        if (it != finiteelements.end()) {
            ans.push_back(it->fe_id);
            it++;
        }
    }
    return ans;
}

vector<int> MeshLoader::Get_BFE_by_border(int id) {
    vector<int> ans;
    auto it = bfes.begin();
    while (it != bfes.end()) {
        it = find_if(it, bfes.end(), [id](const BoundaryFiniteElement &x) {
            return x.border_id == id; });
        if (it != bfes.end()) {
            ans.push_back(it->bfe_id);
            it++;
        }
    }
    return ans;
}

void MeshLoader::Insertion() {
    unordered_set<Edge> inserted;
    /*for (auto &cur: finiteelements) {
        vector vc = cur.nodes_id;
        for (int i = 0; i < dim; i++) {
            for (int j = i + 1; j < dim; j++) {
                Edge exploring = Edge(vc[i], vc[j]);
                if (inserted.contains(exploring)) {
                    cur.nodes_id.push_back(inserted.find(exploring)->baby);
                } else {
                    int id_c = nodes.size() + 1;
                    exploring.baby = id_c;
                    cur.nodes_id.push_back(id_c);
                    Node tmp{};
                    tmp.id = id_c;
                    tmp.x = (nodes[vc[i]].x + nodes[vc[j]].x) / 2;
                    tmp.y = (nodes[vc[i]].y + nodes[vc[j]].y) / 2;
                    tmp.z = (nodes[vc[i]].z + nodes[vc[j]].z) / 2;
                    tmp.is_summit = false;
                    nodes.push_back(move(tmp));
                    inserted.insert(exploring);
                }
            }
        }
    }*/
    for (auto &cur: finiteelements) {
        cur.get_edges();
        for(auto &e : cur.edges){
            if (inserted.contains(e)) {
                cur.nodes_id.push_back(inserted.find(e)->baby);
            } else {
                int id_c = nodes.size() + 1;
                e.baby = id_c;
                cur.nodes_id.push_back(id_c);
                Node tmp{};
                tmp.id = id_c;
                tmp.x = (nodes[e.node1].x + nodes[e.node2].x) / 2;
                tmp.y = (nodes[e.node1].y + nodes[e.node2].y) / 2;
                tmp.x = (nodes[e.node1].z + nodes[e.node2].z) / 2;
                tmp.is_summit = false;
                nodes.push_back(move(tmp));
                inserted.insert(e);
            }
        }
    }
    for (auto &cur: bfes) {
        cur.get_edges();
        for(auto &e : cur.edges){
            if (inserted.contains(e)) {
                cur.nodes_id.push_back(inserted.find(e)->baby);
            } else {
                int id_c = nodes.size() + 1;
                e.baby = id_c;
                cur.nodes_id.push_back(id_c);
                Node tmp{};
                tmp.id = id_c;
                tmp.x = (nodes[e.node1].x + nodes[e.node2].x) / 2;
                tmp.y = (nodes[e.node1].y + nodes[e.node2].y) / 2;
                tmp.x = (nodes[e.node1].z + nodes[e.node2].z) / 2;
                tmp.is_summit = false;
                nodes.push_back(move(tmp));
                inserted.insert(e);
            }
        }
    }
    dim = dim * 2 - 1;
}

vector <set <int>> MeshLoader::Get_neighbors(){
    vector<set<int>> ans(nodes.size() + 1);
    for (const auto &cur : finiteelements)
        for (const auto &id: cur.nodes_id)
            for (const auto &nbr: cur.nodes_id)
                if (id != nbr)
                    ans[id].insert(nbr);
    return ans;
}

void MeshLoader::printNode(const Node &node) {
    std::cout << node;
}

void MeshLoader::printFE(const FiniteElement &fe) {
    std::cout << fe;
}

void MeshLoader::printBFE(const BoundaryFiniteElement &bfe) {
    std::cout << bfe;
}

set<int> MeshLoader::getBoundaryNodesId() {
    set<int> res;
    for (const auto &cur: bfes) {
        for_each(cur.nodes_id.begin(), cur.nodes_id.end(), [&res](int id) {
            res.insert(id);
        });
    }
    return res;
}
vector<double> MeshLoader::createplane(const vector<Node> &points) {
    vector <double> pq = {points[0].x - points[1].x, points[0].y - points[1].y, points[0].z - points[1].z};
    vector <double> pr = {points[2].x - points[1].x, points[2].y - points[1].y, points[2].z - points[1].z};
    vector<double> n = {pq[1]*pr[2] - pq[2]*pr[1], pq[1]*pr[0] - pq[0]*pr[2], pq[0]*pr[1] - pq[1]*pr[0]};
    return n;
}
double length(const vector<double> &x){
    return sqrt(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]);
}
bool MeshLoader::is_small(const FiniteElement &x){
    Edge mini(x.edges[0]);
    for(const auto& e : x.edges){
        if (len(e) < len(mini))
            mini = e;
    }
    vector<Node> plane1, plane2;
    plane1.push_back(nodes[mini.node1]);
    plane2.push_back(nodes[mini.node2]);
    for(auto i : x.nodes_id){
        if (i != mini.node1 && i != mini.node2){
            plane1.push_back(nodes[i]);
            plane2.push_back(nodes[i]);
        }
    }

    vector n1 = createplane(plane1);
    vector n2 = createplane(plane2);
    double cos = abs((n1[0]*n2[0]+ n1[1]*n2[1]+n1[2]*n2[2])/(length(n1)* length(n2)));
    return (cos > sqrt(3)/2);
}

double MeshLoader::volume(const FiniteElement &x) {
    double sp[3][3];
    for (int i = 0; i < 3; i++)
    {
        sp[i][0] = nodes[x.nodes_id[i]].x - nodes[x.nodes_id[3]].x;
        sp[i][1] = nodes[x.nodes_id[i]].y - nodes[x.nodes_id[3]].y;
        sp[i][2] = nodes[x.nodes_id[i]].z - nodes[x.nodes_id[3]].z;
    }
    return (sp[0][0]*sp[1][1]*sp[2][2]+sp[0][1]*sp[1][2]*sp[2][0]+sp[0][2]*sp[1][0]*sp[2][1]-sp[0][2]*sp[1][1]*sp[2][0]
    -sp[0][1]*sp[1][0]*sp[2][2]-sp[0][0]*sp[1][2]*sp[2][1])/6;
}
void MeshLoader::defence(const std::string& filepath) {
    std::vector<FiniteElement> elements = Get_FiniteElements();
    if (elements.empty())
        return;
    std::ofstream file(filepath + ".txt");
    std::ranges::copy(
            elements
            | std::ranges::views::filter(
            [this](const FiniteElement& elem) {
                return is_small(elem);
            })
            | std::ranges::views::transform(
                    [this](const FiniteElement& elem) {
                        return volume(elem);
                    })
            | std::ranges::views::take(10),
            std::ostream_iterator<double>(file));
}

