
#include "TestMenu.hpp"
#include "TestColorChangingSquare.hpp"
#include "TestSingleImage.hpp"
#include "TestMultiImages.hpp"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace test
{

TestMenu::~TestMenu()
{
    if (test)
        delete test;
}


void TestMenu::OnRender(const Renderer& renderer)
{
    if (test)
        test->OnRender(renderer);
}


void TestMenu::OnGuiRender()
{
    ImGui::SetNextWindowPos({0.f, 0.f});
    ImGui::Begin("Test");

    if (test)
    {
        test->OnGuiRender();
        if (ImGui::Button("Back"))
        {
            delete test;
            test = nullptr;
        }
    }
    else
    {
        if (ImGui::Button("Color Changing Square"))
            test = new TestColorChangingSquare();
        if (ImGui::Button("Single Image Texture"))
            test = new TestSingleImage();
        if (ImGui::Button("Multi Image Texture"))
            test = new TestMultiImages();
    }

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}

}
