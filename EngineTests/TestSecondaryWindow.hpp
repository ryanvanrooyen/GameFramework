
#include "Test.hpp"
#include "Core/Window.hpp"
#include "Rendering/Shader.hpp"
#include "Rendering/Texture.hpp"
#include "Rendering/VertexBuffer.hpp"
#include "Rendering/VertexBufferLayout.hpp"
#include "Rendering/VertexArray.hpp"
#include "Rendering/IndexBuffer.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


namespace Game
{

class TestSecondaryWindow : public Test
{
public:
    TestSecondaryWindow();
    void OnUpdate(Window& window, float deltaTime) override;
    void OnGUIRender(Window& window, float deltaTime) override;
    ~TestSecondaryWindow();

    bool OnKeyPress(Window& window, KeyCode key) override;

private:
    Shader shader;
    Texture texture;
    VertexBuffer vertexBuffer;
    VertexBufferLayout vertexLayout;
    VertexArray vertexArray;
    IndexBuffer indexBuffer;

    glm::mat4 proj;
    glm::mat4 view;
    glm::vec3 translation;
    Window* secondaryWindow = nullptr;
};

}