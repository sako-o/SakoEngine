// graphiks
#include <vulkan/vulkan_core.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
// exceptions are still not in std?!?!?!?
#include <cstdlib>
#include <stdexcept>

// https://vulkan-tutorial.com/en/Drawing_a_triangle/Setup/Validation_layers


// maybe move this into seperate files lol
class sakoEngine {
public:
  void run() {
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
    createInstance();
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

  void initVulkan() { createInstance(); }

  void createInstance() {
    // application info
    VkApplicationInfo appInfo{};

    // structure type of appInfo
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    // application name
    appInfo.pApplicationName = "SakoEngine";
    // application version
    appInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
    // engine name
    appInfo.pEngineName = "SakoEngine";
    // engine version
    appInfo.engineVersion = VK_MAKE_VERSION(0, 1, 0);
    // vulkan api version (TODO::(sako) check up on newer API docs?)
    appInfo.apiVersion = VK_API_VERSION_1_0;

    // vulkan instance creation info
    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    // make a unit32 glfw extensions count var
    uint32_t glfwExtensionCount = 0;
    // const for glfwExtensions as a string (wtf char!!!!!!!!!!)
    const char **glfwExtensions;

    // set glfw extensions
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    // set enabled extensions count according to GLFW
    createInfo.enabledExtensionCount = glfwExtensionCount;

    // same thing but with names
    createInfo.ppEnabledExtensionNames = glfwExtensions;

    // this is for validation layers
    createInfo.enabledLayerCount = 0;

    // make the result variable
    // creation info, validation, then the instance
    VkResult vk_result = vkCreateInstance(&createInfo, nullptr, &vk_instance);

    // stop if it has failed
    if (vkCreateInstance(&createInfo, nullptr, &vk_instance) != VK_SUCCESS) {
      throw std::runtime_error("failed to create instance!");
    }
  }

  void mainLoop() {
    while (!glfwWindowShouldClose(window)) {
      glfwPollEvents();
    }
  }

  void cleanup() {
    // destroy vkInstance
    vkDestroyInstance(vk_instance, nullptr);

    // destroy glfw window
    glfwDestroyWindow(window);

    // terminate
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
