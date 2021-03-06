

#pragma once

#include "Layer.hpp"

struct ImGuiContext;

namespace Game
{
    class ImGuiLayer : public UILayer
    {
    public:
        virtual const char* LayerName() const override { return "ImGui Layer"; }

        ImGuiLayer() {}
        virtual ~ImGuiLayer() = default;

        virtual void OnAttach(Window& window) override;
        virtual void OnDetach(Window& window) override;

        virtual void BeginGUI(Window& window, float deltaTime) override;
        virtual void EndGUI(Window& window, float deltaTime) override;

        virtual bool OnWindowResize(Window& window) override;
        virtual bool OnWindowScroll(Window& window, double xOffset, double yOffset) override;
        virtual bool OnWindowMonitor(Window& window, int monitorEventType) override;
        virtual bool OnMouseMove(Window& window, double xPos, double yPos) override;
        virtual bool OnMousePress(Window& window, MouseCode button) override;
        virtual bool OnMouseRelease(Window& window, MouseCode button) override;
        virtual bool OnKeyPress(Window& window, KeyCode key) override;
        virtual bool OnKeyRelease(Window& window, KeyCode key) override;
        virtual bool OnKeyRepeat(Window& window, KeyCode key) override;
        virtual bool OnCharTyped(Window& window, unsigned int character) override;

    private:
        ImGuiContext* context = nullptr;
    };
}