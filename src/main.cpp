#include <iostream>

#include "Framebuffer.h"
#include "Mesh.h"
#include "Matrix4.h"

int main()
{
    std::cout << "Creating 3D scene..." << std::endl;

    Framebuffer buffer(800, 600);
    buffer.Clear({20, 20, 40, 255});

    // Create a cube
    Mesh cube = Mesh::CreateCube(2.0f);

    // Create transformation matrices
    Matrix4 translation = Matrix4::Translation(0, 0, -5);  // Move 5 units away
    Matrix4 projection = Matrix4::Perspective(3.14159f / 4.0f, 800.0f / 600.0f, 0.1f, 100.0f);

    Matrix4 transform = projection * translation;

    // Transform and project vertices
    std::vector<Vector3> projected;
    for (const auto& vertex : cube.vertices) {
        Vector3 transformed = transform.Transform(vertex);

        // Convert from normalized device coordinates [-1, 1] to screen [0, width/height]
        int screenX = static_cast<int>((transformed.x + 1.0f) * 400.0f);
        int screenY = static_cast<int>((1.0f - transformed.y) * 300.0f);

        projected.push_back(Vector3(screenX, screenY, transformed.z));
    }

    // Draw edges
    Color white = {255, 255, 255, 255};
    for (size_t i = 0; i < cube.indices.size(); i += 2) {
        int idx0 = cube.indices[i];
        int idx1 = cube.indices[i + 1];

        buffer.DrawLine(
            static_cast<int>(projected[idx0].x), static_cast<int>(projected[idx0].y),
            static_cast<int>(projected[idx1].x), static_cast<int>(projected[idx1].y),
            white
        );
    }

    // Save to file
    if (buffer.SaveToPNG("../output/wireframe_3D_Cube.png"))
    {
        std::cout << "Image saved to wireframe_3D_Cube.png..." << '\n';
    }
    else
    {
        std::cerr << "Failed to save image!" << '\n';
        return 1;
    }

    return 0;
}