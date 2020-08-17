
#define GL_SILENCE_DEPRECATION
#include "source/rendering/opengl.hpp"
#include <string>
#include <signal.h>
#include "source/logging.h"
#include "source/rendering/Renderer.hpp"
#include "source/rendering/Shader.hpp"
#include "source/rendering/Texture.hpp"
#include "source/rendering/VertexBuffer.hpp"
#include "source/rendering/VertexBufferLayout.hpp"
#include "source/rendering/IndexBuffer.hpp"
#include "source/rendering/VertexArray.hpp"

using std::string;


static void error_callback(int error, const char* description)
{
    ERROR("Error: %s", description);
}


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}


int main()
{
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetKeyCallback(window, key_callback);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        ERROR("Failed to initialize OpenGL context");
        return -1;
    }

    INFO("OpenGL Version %s", glGetString(GL_VERSION));

    float positions[] = {
        -0.5f, -0.5f, 0.f, 0.f,
         0.5f, -0.5f, 1.f, 0.f,
         0.5f,  0.5f, 1.f, 1.f,
        -0.5f,  0.5f, 0.f, 1.f,
    };

    VertexBuffer vertexBuffer(positions, 4 * 4 * sizeof(float));

    VertexBufferLayout vertexLayout;
    vertexLayout.Push<float>(2); // 2D Position
    vertexLayout.Push<float>(2); // 2D Texture Position

    // Enable alpha blending:
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    VertexArray va;
    va.AddBuffer(vertexBuffer, vertexLayout);

    unsigned int indicies[] = {
        0, 1, 2,
        2, 3, 0,
    };

    IndexBuffer indexBuffer(indicies, 6);

    Shader shader("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");
    shader.Compile();
    shader.Bind();

    Texture texture("resources/logo3.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);

    Renderer renderer;

    float redColor = 0.0f;
    float increment = 0.05f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Poll for and process events */
        glfwPollEvents();
        // glfwWaitEvents();

        renderer.Clear();

        // shader.Bind();
        // shader.SetUniform4f("u_Color", redColor, 0.3f, 0.8f, 1.f);

        renderer.Draw(va, indexBuffer, shader);

        if (redColor > 1.f || redColor < 0.f)
            increment = -increment;

        redColor += increment;

        // Swap front and back buffers
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}
