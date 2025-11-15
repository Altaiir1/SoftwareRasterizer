#pragma once

#include <vector>
#include "Vector3.h"

struct Mesh {
    std::vector<Vector3> vertices; // Corner points
    std::vector<int> indices;      // Which vertices connect (pairs for lines)

    // Create a cube centered at origin
    static Mesh CreateCube(float size = 1.0f) {
        Mesh mesh;
        float half = size / 2.0f;

        // 8 vertices of a cube
        mesh.vertices = {
            Vector3(-half, -half, -half),  // 0: back-bottom-left
            Vector3( half, -half, -half),  // 1: back-bottom-right
            Vector3( half,  half, -half),  // 2: back-top-right
            Vector3(-half,  half, -half),  // 3: back-top-left
            Vector3(-half, -half,  half),  // 4: front-bottom-left
            Vector3( half, -half,  half),  // 5: front-bottom-right
            Vector3( half,  half,  half),  // 6: front-top-right
            Vector3(-half,  half,  half),  // 7: front-top-left
        };

        // 12 edges (24 indices, 2 per edge)
        mesh.indices = {
            // Back face
            0, 1,  1, 2,  2, 3,  3, 0,
            // Front face
            4, 5,  5, 6,  6, 7,  7, 4,
            // Connecting edges
            0, 4,  1, 5,  2, 6,  3, 7
        };

        return mesh;
    }
};