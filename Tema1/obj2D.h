#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{

    // Create square with given bottom left corner, length and color
    Mesh* CreateGrass(const std::string &name, glm::vec3 leftBottomCorner, float length, float width, glm::vec3 color);
    Mesh* CreateTriangle(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill);
    Mesh* CreateCioc(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill);
    Mesh* CreateCircle(const std::string& name, glm::vec3 centre, float lengthX, glm::vec3 color);
    Mesh* CreateWing1(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill);
    Mesh* CreateWing2(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill);
    Mesh* CreateHealth(const std::string& name, glm::vec3 centre, float lengthX, glm::vec3 color);
    Mesh* CreateScore(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill);
    Mesh* CreateSquare1(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill);

}
