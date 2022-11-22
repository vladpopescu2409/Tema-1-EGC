#include "obj2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"
#include <iostream>


 Mesh* object2D::CreateGrass(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length, float width,
    glm::vec3 color)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color), 
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, width, 0), color),
        VertexFormat(corner + glm::vec3(0,  width, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 
                                          0, 2, 3 };

    square->InitFromData(vertices, indices);
    return square;
}

 Mesh* object2D::CreateTriangle(const std::string& name,
     glm::vec3 leftBottomCorner,
     float length,
     glm::vec3 color,
     bool fill)
 {
     glm::vec3 corner = leftBottomCorner;

     std::vector<VertexFormat> vertices =
     {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(2*length, length/2, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
     };

     Mesh* triangle = new Mesh(name);
     std::vector<unsigned int> indices = { 0, 1, 2 };

     triangle->InitFromData(vertices, indices);
     return triangle;

 }

 Mesh* object2D::CreateCioc(const std::string& name,
     glm::vec3 leftBottomCorner,
     float length,
     glm::vec3 color,
     bool fill)
 {
     glm::vec3 corner = leftBottomCorner;

     std::vector<VertexFormat> vertices =
     {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(2*length, length / 2, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
     };

     Mesh* triangle = new Mesh(name);
     std::vector<unsigned int> indices = { 0, 1, 2 };

     triangle->InitFromData(vertices, indices);
     return triangle;

 }

 Mesh* object2D::CreateCircle(const std::string& name, glm::vec3 centre, float lengthX, glm::vec3 color) {
     float a = lengthX;

     int range = 90;

     std::vector<VertexFormat> vertices = {
         VertexFormat(centre + glm::vec3(0, 0, 0), color) // 0
     };

     for (int i = 0; i < range + 1; ++i) {
         float angle = -M_PI / 2 + M_PI / 45 * i;
         vertices.push_back(VertexFormat(centre + glm::vec3(a * cos(angle), a * sin(angle), 0), color));
     }
     Mesh* balloon = new Mesh(name);

     std::vector<unsigned int> indices;
     for (int i = 1; i <= range; ++i) {
         indices.push_back(0);
         indices.push_back(i);
         indices.push_back(1 + i % range);
     }

     balloon->InitFromData(vertices, indices);
     return balloon;
 }

 Mesh* object2D::CreateHealth(const std::string& name, glm::vec3 centre, float lengthX, glm::vec3 color) {
     float a = lengthX;

     int range = 90;

     std::vector<VertexFormat> vertices = {
         VertexFormat(centre + glm::vec3(0, 0, 0), color) // 0
     };

     for (int i = 0; i < range + 1; ++i) {
         float angle = -M_PI / 2 + M_PI / 45 * i;
         vertices.push_back(VertexFormat(centre + glm::vec3(a * cos(angle), a * sin(angle), 0), color));
     }
     Mesh* balloon = new Mesh(name);

     std::vector<unsigned int> indices;
     for (int i = 1; i <= range; ++i) {
         indices.push_back(0);
         indices.push_back(i);
         indices.push_back(1 + i % range);
     }

     balloon->InitFromData(vertices, indices);
     return balloon;
 }

 Mesh* object2D::CreateWing1(const std::string& name,
     glm::vec3 leftBottomCorner,
     float length,
     glm::vec3 color,
     bool fill)
 {
     glm::vec3 corner = leftBottomCorner;

     std::vector<VertexFormat> vertices =
     {
        VertexFormat(corner + glm::vec3(0, 30, 0), color),
        VertexFormat(corner + glm::vec3(length-20, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color)
     };

     Mesh* triangle = new Mesh(name);
     std::vector<unsigned int> indices = { 0, 1, 2 };

     triangle->InitFromData(vertices, indices);
     return triangle;

 }

 Mesh* object2D::CreateWing2(const std::string& name,
     glm::vec3 leftBottomCorner,
     float length,
     glm::vec3 color,
     bool fill)
 {
     glm::vec3 corner = leftBottomCorner;

     std::vector<VertexFormat> vertices =
     {
        VertexFormat(corner + glm::vec3(0, -30, 0), color),
        VertexFormat(corner + glm::vec3(length - 20, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, -length, 0), color)
     };

     Mesh* triangle = new Mesh(name);
     std::vector<unsigned int> indices = { 0, 1, 2 };

     triangle->InitFromData(vertices, indices);
     return triangle;

 }

 Mesh* object2D::CreateScore(
     const std::string& name,
     glm::vec3 leftBottomCorner,
     float length,
     glm::vec3 color,
     bool fill)
 {
     glm::vec3 corner = leftBottomCorner;

     std::vector<VertexFormat> vertices =
     {
         VertexFormat(corner, color),
         VertexFormat(corner + glm::vec3(280, 0, 0), color),
         VertexFormat(corner + glm::vec3(280, length, 0), color),
         VertexFormat(corner + glm::vec3(0, length, 0), color)
     };

     Mesh* square = new Mesh(name);
     std::vector<unsigned int> indices = { 0, 1, 2, 3 };

     if (!fill) {
         square->SetDrawMode(GL_LINE_LOOP);
     }
     else {
         // Draw 2 triangles. Add the remaining 2 indices
         indices.push_back(0);
         indices.push_back(2);
     }

     square->InitFromData(vertices, indices);
     return square;
 }

 Mesh* object2D::CreateSquare1(
     const std::string& name,
     glm::vec3 leftBottomCorner,
     float length,
     glm::vec3 color,
     bool fill)
 {
     glm::vec3 corner = leftBottomCorner;

     std::vector<VertexFormat> vertices =
     {
         VertexFormat(corner, color),
         VertexFormat(corner + glm::vec3(length, 0, 0), color),
         VertexFormat(corner + glm::vec3(length, length, 0), color),
         VertexFormat(corner + glm::vec3(0, length, 0), color)
     };

     Mesh* square = new Mesh(name);
     std::vector<unsigned int> indices = { 0, 1, 2, 3 };

     if (!fill) {
         square->SetDrawMode(GL_LINE_LOOP);
     }
     else {
         // Draw 2 triangles. Add the remaining 2 indices
         indices.push_back(0);
         indices.push_back(2);
     }

     square->InitFromData(vertices, indices);
     return square;
 }

 