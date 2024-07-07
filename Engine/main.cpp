#include <vulkan/vulkan.h>

#include <cstdlib>
#include <iostream>
#include <stdexcept>

// page 41 of guide

class SakoEngine {
public:
  void run() {
    initVulkan();
    mainLoop();
    cleanup();
  }

private:
  void initVulkan() {}
  void mainLoop() {}
  void cleanup() {}
};

int main() {
  SakoEngine engine;

  try {
    engine.run();
  } catch (const std::exception &e) {
  std:
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
