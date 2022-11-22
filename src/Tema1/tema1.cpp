#include "lab_m1/Tema1/tema1.h"

#include <vector>
#include <iostream>
#include <chrono>
#include <windows.h>
#include <string>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/obj2D.h"


using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    //coordX = 150;
    //coordY = 200;
    glm::vec3 corner = glm::vec3(0, 0, 0);
    squareSide = 100;
    okk = 0;
    coordX = 0;
    coordY = 0;
    angle = RADIANS(20 + (std::rand() % (45 - 20 + 1)));
    //angle = M_PI/3;
    adjustSpeed = 1;
    direction = 0.7;
    totalTime = 0;
    ok = false;
    ok1 = false;
    counter = 0;
    salt = 0;
    nr_ammo = 3;
    nr_life = 3;
    nr_score = 0;
    duck_counter = 1;
    duck_speed = 400;
    // TODO(student): Compute coordinates of a square's center, and store
    // then in the `cx` and `cy` class variables (see the header). Use
    // `corner` and `squareSide`. These two class variables will be used
    // in the `Update()` function. Think about it, why do you need them?
    
    // Initialize tx and ty (the translation steps)
    translateX = 0;
    translateY = 0;

    // Initialize sx and sy (the scale factors)
    scaleX = 1;
    scaleY = 1;

    // Initialize angularStep
    angularStep = 0;
    
    Mesh* grass = object2D::CreateGrass("grass", glm::vec3(0, 0, 0), resolution.x, 125, glm::vec3(0, 1, 0));
    AddMeshToList(grass);

    Mesh* triangle = object2D::CreateTriangle("tri", corner, squareSide, glm::vec3(0.61, 0.29, 0), true);
    AddMeshToList(triangle);

    Mesh* circle = object2D::CreateCircle("circle", glm::vec3(200, 50, 0), 40, glm::vec3(0, 0.4, 0));
    AddMeshToList(circle);

    Mesh* wing1 = object2D::CreateWing1("wing1", corner, squareSide, glm::vec3(0.61, 0.29, 0), true);
    AddMeshToList(wing1);

    //glm::vec3 corner1 = glm::vec3(100, 95, 0);
    Mesh* wing2 = object2D::CreateWing2("wing2", corner, squareSide, glm::vec3(0.61, 0.29, 0), true);
    AddMeshToList(wing2);

    Mesh* cioc = object2D::CreateCioc("cioc", glm::vec3(0, 0, 0), 20, glm::vec3(0.8, 0.8, 0), true);
    AddMeshToList(cioc);

    Mesh* circle2 = object2D::CreateCircle("circle2", glm::vec3(200, 50, 0), 40, glm::vec3(0.9, 0, 0));
    AddMeshToList(circle2);

    Mesh* ammo = object2D::CreateGrass("ammo", glm::vec3(0, 0, 0), 50, 20, glm::vec3(0.8, 0.8, 0));
    AddMeshToList(ammo);

    Mesh* score = object2D::CreateScore("score", glm::vec3(0, 0, 0), 40, glm::vec3(1, 0.4, 0), false);
    AddMeshToList(score);

    Mesh* add_score = object2D::CreateSquare1("add_score", glm::vec3(0, 0, 0), 40, glm::vec3(1, 0.4, 0), true);
    AddMeshToList(add_score);

}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.2, 0.8, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);

}


void Tema1::Update(float deltaTimeSeconds)
{
   
    resolution = window->GetResolution();
    
    //Iarba
    grassMatrix = glm::mat3(1);
    RenderMesh2D(meshes["grass"], shaders["VertexColor"], grassMatrix);

    //Scor
    scoreMatrix = glm::mat3(1);
    RenderMesh2D(meshes["score"], shaders["VertexColor"], scoreMatrix * transform2D::Translate(30, 650));
    for (int i = 0; i < nr_score; i++)
    {
        RenderMesh2D(meshes["add_score"], shaders["VertexColor"], scoreMatrix * transform2D::Translate(30 + 40 * i, 650));
    }

    //Vieti
    healthMatrix = glm::mat3(1);
    for (int i = 0; i < nr_life; i++)
    {
    RenderMesh2D(meshes["circle2"], shaders["VertexColor"], healthMatrix * transform2D::Translate(960 + 70 * i, 650) * 
            transform2D::Scale(0.6, 0.6));
    }

    //Munitie
    ammoMatrix = glm::mat3(1);
    for (int i = 0; i < nr_ammo; i++)
    {
        RenderMesh2D(meshes["ammo"], shaders["VertexColor"], ammoMatrix * transform2D::Translate(1090 + 70 * i, 580) *
            transform2D::Rotate(M_PI_2));
    }

    counter += deltaTimeSeconds;

   
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(translateX, translateY);
    //modelMatrix *= transform2D::Translate(100, 50);
    modelMatrix *= transform2D::Rotate(angle);
    //modelMatrix *= transform2D::Translate(-100, -50);
    
    switch (salt)
    {
    case 0:
        if (ok == false) {
            translateY += deltaTimeSeconds * duck_speed * sin(angle);
        }
        else
            if (ok == true)
            {
                translateY += deltaTimeSeconds * duck_speed * sin(angle);
            }

        if (translateY >= resolution.y - 100)
        {
            ok = true;
            angle = 2 * M_PI - angle;
        }
        if (translateY <= 0)
        {
            ok = false;
            angle = 2 * M_PI - angle;
        }

        if (ok1 == false)
        {
            translateX += deltaTimeSeconds * duck_speed * abs(cos(angle));

        }
        else
            if (ok1 == true)
            {
                translateX -= deltaTimeSeconds * duck_speed * abs(cos(angle));

            }
        if (translateX >= resolution.x - 100)
        {
            ok1 = true;
            angle = M_PI - angle;
        }
        if (translateX < 0)
        {
            ok1 = false;
            angle = M_PI - angle;
        }

        
        if (counter > 5)
        {
            salt = 1;
            nr_life--;
           
        }
        break;

    case 1:         //Evadare
        angle = M_PI_2;
        if (translateY < 1100)
        {
            translateY += deltaTimeSeconds * 150;
            translateX = translateX;
        }
        else
        {
            salt = 0;
            translateX = 0;
            translateY = 0;                                         //Respawn
            angle = RADIANS(20 + (std::rand() % (55 - 20 + 1)));
            counter = 0;
            nr_ammo = 3;

            duck_counter++;
            if (duck_counter % 2 == 0)
            {
                duck_speed = duck_speed + 300;
            }
        }

        break;

    case 2:         //Animatie cadere dupa tragere
        angle = M_PI + M_PI_2;
        if (translateY > -200)
        {
            translateY -= deltaTimeSeconds * 150;
            translateX = translateX;
        }
        else
        {
            salt = 0;
            translateX = 0;
            translateY = 0;
            angle = RADIANS(20 + (std::rand() % (45 - 20 + 1)));
            counter = 0;
            nr_ammo = 3;
            nr_score++;

            duck_counter++;
            if (duck_counter % 5 == 0)
            {
                duck_speed = duck_speed + 300;
            }
        }
        break;
    default:
        break;
    }
    CreateDuck();
  
    okk = okk + 0.0035;
    if (okk >= 0.12) {
        okk = 0;
    }

}


void Tema1::CreateDuck()
{
   // modelMatrix = glm::mat3(1);
    //modelMatrix *= transform2D::Translate(0 + 100, 100);
    //modelMatrix *= transform2D::Translate(translateX, translateY);
    //modelMatrix *= transform2D::Translate(170, 50);
    RenderMesh2D(meshes["circle"], shaders["VertexColor"], modelMatrix * transform2D::Translate(0, 100));

    /*modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(200 + 100, 135);
    modelMatrix *= transform2D::Translate(translateX, translateY);
    modelMatrix *= transform2D::Scale(0.3, 0.3);*/
    RenderMesh2D(meshes["cioc"], shaders["VertexColor"], modelMatrix * transform2D::Translate(230, 135) );

   /* modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(0 + 100, 100);
    modelMatrix *= transform2D::Translate(translateX, translateY); */
    //modelMatrix *= transform2D::Translate(squareSide, squareSide / 2) * transform2D::Rotate(0.7)
       //* transform2D::Translate(-squareSide, -(squareSide / 2));
    RenderMesh2D(meshes["tri"], shaders["VertexColor"], modelMatrix * transform2D::Translate(0, 100));

    /*modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(20 + 100, 150);
    modelMatrix *= transform2D::Translate(translateX, translateY);
    modelMatrix *= transform2D::Rotate(okk); */
    RenderMesh2D(meshes["wing1"], shaders["VertexColor"], modelMatrix * transform2D::Translate(20, 150) * transform2D::Rotate(okk));

    /*modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(20 + 100, 150);
    modelMatrix *= transform2D::Translate(translateX, translateY);
    modelMatrix *= transform2D::Rotate(-okk); */
    RenderMesh2D(meshes["wing2"], shaders["VertexColor"], modelMatrix * transform2D::Translate(20, 150) * transform2D::Rotate(-okk));
}
void Tema1::FrameEnd()
{
    
}

void Tema1::LifeBar() 
{
    healthMatrix = glm::mat3(1);
    RenderMesh2D(meshes["circle2"], shaders["VertexColor"], healthMatrix * transform2D::Translate(1100, 650) * transform2D::Scale(0.6, 0.6));
    RenderMesh2D(meshes["circle2"], shaders["VertexColor"], healthMatrix * transform2D::Translate(1030, 650) * transform2D::Scale(0.6, 0.6));
    RenderMesh2D(meshes["circle2"], shaders["VertexColor"], healthMatrix * transform2D::Translate(960, 650) * transform2D::Scale(0.6, 0.6));
    

}
/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    mouseY = resolution.y - mouseY;
    nr_ammo--;
    if (mouseY < (translateY + 180) && mouseX < (translateX + 100) && mouseY >(translateY - 180) && mouseX >(translateX - 100))
    {
        cout << "HIT" << endl;
        salt = 2;
    }
    if (nr_ammo == 0)
    {
        nr_life--;
        salt = 1;
    }

}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event


}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
