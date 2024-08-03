#include <cstdint>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <cstdlib>
#include <iostream>
#include <stdexcept>

// page 41 of guide

const uint32_t w_width = 800;
const uint32_t w_height = 600;

class SakoEngine {
public:
  void run() {
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
  }

private:
  GLFWwindow *window;

  void initVulkan() {}
  void initWindow() {
    glfwInit();

    // window hints (disable api for manually adding vulkan)
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    // disable resizeing windows
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window =
        glfwCreateWindow(w_width, w_height, "SakoEngine", nullptr, nullptr);
  }
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
  SakoEngine engine;

  try {
    engine.run();
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
