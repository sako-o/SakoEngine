// graphiks
#include <vulkan/vulkan_core.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
// exceptions are still not in std?!?!?!?
#include <cstdlib>
#include <stdexcept>
// vector
#include <vector>
// cstring for strcmp
#include <cstring>

// set the validation layers
const std::vector<const char *> validationLayers = {
    "VK_LAYER_KHRONOS_validation"};

// disable validation layers when not in debug
#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

// https://vulkan-tutorial.com/en/Drawing_a_triangle/Setup/Validation_layers

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
  VkDebugUtilsMessengerEXT debugMessenger;

  void initWindow() {
    // init
    glfwInit();

    // create window without OpenGL Context
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    // disable resizing
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(800, 600, "SakoEngine", nullptr, nullptr);
  }

  void initVulkan() {
    createInstance();
    setupDebugMessenger();
  }

  void populateDebugMessengerCreateInfo(
      VkDebugUtilsMessengerCreateInfoEXT &createInfo) {
    createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity =
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                             VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                             VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = debugCallback;
  }

  VkResult CreateDebugUtilsMessengerEXT(
      VkInstance instance,
      const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
      const VkAllocationCallbacks *pAllocator,
      VkDebugUtilsMessengerEXT *pDebugMessenger) {
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
        instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr) {
      return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    } else {
      return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
  }

  void DestroyDebugUtilsMessengerEXT(VkInstance instance,
                                     VkDebugUtilsMessengerEXT debugMessenger,
                                     const VkAllocationCallbacks *pAllocator) {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
        instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
      func(instance, debugMessenger, pAllocator);
    }
  }

  void setupDebugMessenger() {
    if (!enableValidationLayers)
      return;

    VkDebugUtilsMessengerCreateInfoEXT createInfo;
    populateDebugMessengerCreateInfo(createInfo);

    if (CreateDebugUtilsMessengerEXT(vk_instance, &createInfo, nullptr,
                                     &debugMessenger) != VK_SUCCESS) {
      throw std::runtime_error("Failed to setup debug messenger, quitting...");
    }
  }

  // get the required extensions based on if validation layers are on or not
  std::vector<const char *> getRequiredExtensions() {
    uint32_t glfwExtensionCount = 0;
    const char **glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char *> extensions(glfwExtensions,
                                         glfwExtensions + glfwExtensionCount);

    if (enableValidationLayers) {
      extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    return extensions;
  }

  static VKAPI_ATTR VkBool32 VKAPI_CALL
  debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                VkDebugUtilsMessageTypeFlagsEXT messageType,
                const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
                void *pUserData) {

    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

    return VK_FALSE;

    // The values of this enumeration are set up in such a way that you can use
    // a comparison operation to check if a message is equal or worse compared
    // to some level of severity, for example:
    // if (messageSeverity >=
    // VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
    //   // Message is important enough to show
    // }
  }

  bool checkValidationLayerSupport() {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> avaliableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, avaliableLayers.data());

    for (const char *layerName : validationLayers) {
      bool layerFound = false;

      for (const auto &layerProperties : avaliableLayers) {
        if (strcmp(layerName, layerProperties.layerName) == 0) {
          layerFound = true;
          break;
        }
      }

      if (!layerFound) {
        return false;
      }
    }

    return true;
  }

  void createInstance() {
    // check for validation layer support
    if (enableValidationLayers && !checkValidationLayerSupport()) {
      throw std::runtime_error(
          "Validation layers requested, but not avaliable!");
    }

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

    // include validation layer names if enabled
    if (enableValidationLayers) {
      createInfo.enabledLayerCount =
          static_cast<uint32_t>(validationLayers.size());
      createInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
      createInfo.enabledLayerCount = 0;
    }

    // extensions yay
    auto extensions = getRequiredExtensions();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

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

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
    if (enableValidationLayers) {
      createInfo.enabledLayerCount =
          static_cast<uint32_t>(validationLayers.size());
      createInfo.ppEnabledLayerNames = validationLayers.data();

      populateDebugMessengerCreateInfo(debugCreateInfo);
      createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT *)&debugCreateInfo;
    } else {
      createInfo.enabledLayerCount = 0;

      createInfo.pNext = nullptr;
    }

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
    // destroy debugutils if validation layers are on
    if (enableValidationLayers) {
      DestroyDebugUtilsMessengerEXT(vk_instance, debugMessenger, nullptr);
    }

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
