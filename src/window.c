#include "window.h"

static windowInstance Window;

void createWindow(){

    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    Window.window = glfwCreateWindow(600, 800, "Vulkan", NULL, NULL);

    while (!glfwWindowShouldClose(Window.window))
    {

        glfwPollEvents();
    }
    
    glfwDestroyWindow(Window.window);
     glfwTerminate();

}