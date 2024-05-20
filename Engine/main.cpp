// graphiks
#include <vulkan/vulkan_core.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
// exceptions are still not in std?!?!?!?
#include <cstdlib>
#include <stdexcept>

// https://vulkan-tutorial.com/en/Drawing_a_triangle/Setup/Instance

// maybe move this into seperate files lol
class sakoEngine {
public:
  void run() {
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
  }

private:
  VkInstance vk_instance;
  GLFWwindow *window;

  void initWindow() {
    // init
    glfwInit();

    // create window without OpenGL Context
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    // disable resizing
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(800, 600, "SakoEngine", nullptr, nullptr);
  }

  void initVulkan() {}

  void mainLoop() {
    while (!glfwWindowShouldClose(window)) {
      glfwPollEvents();
    }
  }

  void cleanup() {
    glfwDestroyWindow(window);

    glfwTerminate();
  }
};

int main() {
  sakoEngine app;

  try {
    app.run();
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
