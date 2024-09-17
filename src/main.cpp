#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_stdinc.h>

// guid(e)
// https://sibras.github.io/OpenGL4-Tutorials/docs/Tutorials/01-Tutorial1/#part-3-opengl-rendering

// OpenGL setup
GLuint gl_VAO;        // Vertex Array Object
GLuint gl_VBO;        // Vertex Buffer Object
GLuint gl_SakoEngine; // Shader program ID

bool GL_LoadShader(GLuint &uiShader, GLenum ShaderType,
                   const GLchar *p_cShader) {
  // Build and link the shader program
  uiShader = glCreateShader(ShaderType);
  glShaderSource(uiShader, 1, &p_cShader, NULL);
  glCompileShader(uiShader);

  // Check for errors
  GLint iTestReturn;
  glGetShaderiv(uiShader, GL_COMPILE_STATUS, &iTestReturn);
  if (iTestReturn == GL_FALSE) {
    GLchar p_cInfoLog[1024];
    int32_t iErrorLength;
    glGetShaderInfoLog(uiShader, 1024, &iErrorLength, p_cInfoLog);
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
                    "Failed to compile shader: %s\n", p_cInfoLog);
    glDeleteShader(uiShader);
    return false;
  }
  return true;
}

bool GL_LoadShaders(GLuint &uiShader, GLuint uiVertexShader,
                    GLuint uiFragmentShader) {
  // Link the shaders
  uiShader = glCreateProgram();
  glAttachShader(uiShader, uiVertexShader);
  glAttachShader(uiShader, uiFragmentShader);
  glLinkProgram(uiShader);

  // Check for error in link
  GLint iTestReturn;
  glGetProgramiv(uiShader, GL_LINK_STATUS, &iTestReturn);
  if (iTestReturn == GL_FALSE) {
    GLchar p_cInfoLog[1024];
    int32_t iErrorLength;
    glGetShaderInfoLog(uiShader, 1024, &iErrorLength, p_cInfoLog);
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
                    "Failed to link shaders: %s\n", p_cInfoLog);
    glDeleteProgram(uiShader);
    return false;
  }
  return true;
}

bool gl_Init() {

  // Initialize GLEW
  glewExperimental = GL_TRUE; // Allow experimental extensions
  GLenum glewError = glewInit();
  if (glewError != GLEW_OK) {
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
                    "Failed to initalize GLEW!: %s\n",
                    glewGetErrorString(glewError));
    return false;
  }

  // Set up initial GL attributes
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glCullFace(GL_BACK);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_STENCIL_TEST);

  // Create vertex shader source
  const GLchar p_cVertexShaderSource[] = {"#version 430 core\n \
    layout(location = 0) in vec2 v2VertexPos2D;\n \
    void main() \n \
    { gl_Position = vec4(v2VertexPos2D, 0.0f, 1.0f); }"};

  // Create vertex shader
  GLuint uiVertexShader;
  if (!GL_LoadShader(uiVertexShader, GL_VERTEX_SHADER, p_cVertexShaderSource))
    return false;

  // Create fragment shader source
  const GLchar p_cFragmentShaderSource[] = {"#version 430 core\n \
    out vec3 v3FragOutput;\n \
    void main() \n \
    {\n \
        v3FragOutput = vec3(1.0f, 1.0f, 1.0f);\n \
    }"};

  // Create fragment shader
  GLuint uiFragmentShader;
  if (!GL_LoadShader(uiFragmentShader, GL_FRAGMENT_SHADER,
                     p_cFragmentShaderSource))
    return false;

  // Create program
  if (!GL_LoadShaders(gl_SakoEngine, uiVertexShader, uiFragmentShader))
    return false;

  // Clean up unneeded shaders
  glDeleteShader(uiVertexShader);
  glDeleteShader(uiFragmentShader);

  // Create a Vertex Array Object
  glGenVertexArrays(1, &gl_VAO);
  glBindVertexArray(gl_VAO);

  // Create VBO data
  GLfloat fVertexData[] = {-0.5f, -0.5f, 0.5f, -0.5f, 0.0f, 0.5f};

  // Create Vertex Buffer Object
  glGenBuffers(1, &gl_VBO);
  glBindBuffer(GL_ARRAY_BUFFER, gl_VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(fVertexData), fVertexData,
               GL_STATIC_DRAW);

  // Specify location of data within buffer
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat),
                        (const GLvoid *)0);
  glEnableVertexAttribArray(0);

  glUseProgram(gl_SakoEngine);

  return true;
}

void gl_Render() {
  // Clear render outputand buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // Specify VAO to use
  glBindVertexArray(gl_VAO);

  // Draw the triangle
  glDrawArrays(GL_TRIANGLES, 0, 3);
}
void gl_Quit() {
  // Release the shader program
  glDeleteProgram(gl_SakoEngine);

  // Delete VBO and VAO
  glDeleteBuffers(1, &gl_VBO);
  glDeleteVertexArrays(1, &gl_VAO);
}

int main() {

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
                    "Failed to initalize SDL!: %s\n", SDL_GetError());
    return 1;
  } else {
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "SDL2 Ready!");
  }

  // Use OpenGL 4.3 core profile
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  // Turn on double buffering with a 24bit Z buffer
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

  // Declare window variables
  int windowWidth = 800;
  int windowHeight = 600;
  bool windowIsFullscreen = false;

  // its window time
  SDL_Window *window =
      SDL_CreateWindow("SakoEngine", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight,
                       SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL |
                           (windowIsFullscreen * SDL_WINDOW_FULLSCREEN));
  if (window == NULL) {
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "OpenGL Window failed! %s\n",
                    SDL_GetError());
    SDL_Quit();
    return 1;
  } else {
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "OpenGL Window ready!");
  }

  // GL context
  SDL_GLContext gl_context = SDL_GL_CreateContext(window);
  if (gl_context == NULL) {
    SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "OpenGL Context failed! %s\n",
                    SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  } else {
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "OpenGL Context ready!");
  }

  // vsync
  // 1 Enables
  // 0 Disbles
  // -1 makes late swaps occur immedately instead of waiting for next refresh
  SDL_GL_SetSwapInterval(-1);

  // Initialize OpenGL
  if (gl_Init()) {

    // Event Handling
    SDL_Event Event;
    bool running = true;
    while (running) {
      // Poll SDL for buffered events
      while (SDL_PollEvent(&Event)) {
        if (Event.type == SDL_QUIT)
          running = false;
        else if (Event.type == SDL_KEYDOWN) {
          if (Event.key.keysym.sym == SDLK_ESCAPE)
            running = false;
        }
      }

      // Render the scene
      gl_Render();

      // Swap the back-buffer and present it
      SDL_GL_SwapWindow(window);
    }

    // Delete any created GL resources
    gl_Quit();
  }

  // cleanup
  SDL_GL_DeleteContext(gl_context);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
