#pragma once

#include "components/simple_scene.h"


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
     public:
        Tema1();
        ~Tema1();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;
        void CreateDuck();
        void LifeBar();
        
        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

     protected:
        float cx, cy;
        glm::mat3 modelMatrix;
        glm::mat3 grassMatrix;
        glm::mat3 healthMatrix;
        glm::mat3 ammoMatrix;
        glm::mat3 scoreMatrix;


        time_t start_time, end_time;

        float translateX, translateY;
        float scaleX, scaleY;
        float coordX, coordY;
        float angularStep;
        float okk;
        float direction;
        float colX, colY;
        float angle;
        int adjustSpeed;
        int life1, life2, life3;
        float counter;
        int seconds;
        float totalTime;
        int salt;
        int nr_ammo, nr_life, nr_score;
        int duck_counter;
        float evadeX, evadeY;
        float duck_speed;
        // TODO(student): If you need any other class variables, define them here.
        bool ok;
        bool ok1;
        bool dir;
        float wingAngle;
        float squareSide;
        glm::ivec2 resolution;
    };
}   // namespace m1
