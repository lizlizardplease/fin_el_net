//
// Created by liza on 24.12.2021.
//

#ifndef FIN_EL_NET_HASH_H
#define FIN_EL_NET_HASH_H
#include "Structures.h"
template<typename _T>
inline void hashCombine(std::size_t& o_seed, const _T& p_val) {
    o_seed ^= std::hash<_T>()(p_val) + 0x9e3379b9 + (o_seed << 6) + (o_seed >> 2);
}

template<typename _T>
inline void hashVal(std::size_t& o_seed, const _T& p_val) {
    hashCombine(o_seed, p_val);
}

template<typename _T, typename..._Types>
inline void hashVal(std::size_t& o_seed, const _T& p_val, const _Types& ...p_args) {
    hashCombine(o_seed, p_val);
    hashVal(o_seed, p_args...);
}

template<typename ... _Types>
inline std::size_t hashVal(const _Types& ...p_args) {
    std::size_t seed = 0;
    hashVal(seed, p_args...);
    return seed;
}
namespace std {
    template<>
    struct hash<Edge> {
        size_t
        operator()(const Edge &p_edge) const {
            
            //!!! Данные ребра должны быть отсортированны. В противном случае ребра 
            //!!! (1, 2) и (2, 1) имеют разные хеш-значения, хотя это одно и то же ребро.
            
            return hashVal(p_edge.node1, p_edge.node2);
        }
    };
}

#endif //FIN_EL_NET_HASH_H
