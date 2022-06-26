//
// Created by liza on 27.09.2021.
//

#ifndef FIN_EL_NET_NEUMESHLOADER_H
#define FIN_EL_NET_NEUMESHLOADER_H
#include "MeshLoader.h"
class NeuMeshLoader : public MeshLoader {
public:
    void LoadMesh(const string&) override;
};
#endif //FIN_EL_NET_NEUMESHLOADER_H
