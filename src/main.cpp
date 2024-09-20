#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_stdinc.h>
#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/type_aligned.hpp>
#include <math.h>

// guid(e)
// https://sibras.github.io/OpenGL4-Tutorials/docs/Tutorials/02-Tutorial2/#part-3-transforming-objects

// BEGIN GL_DEBUG
static char *gp_cSeverity[] = {"High", "Medium", "Low", "Notification"};
static char *gp_cType[] = {"Error",       "Deprecated",  "Undefined",
                           "Portability", "Performance", "Other"};
static char *gp_cSource[] = {"OpenGL",    "OS",          "GLSL Compiler",
                             "3rd Party", "Application", "Other"};

void DebugCallback(uint32_t uiSource, uint32_t uiType, uint32_t uiID,
                   uint32_t uiSeverity, int32_t iLength, const char *p_cMessage,
                   void *p_UserParam) {
  // *** Add code to convert inputs to strings here ***

  // Get the severity
  uint32_t uiSevID = 3;
  switch (uiSeverity) {
  case GL_DEBUG_SEVERITY_HIGH:
    uiSevID = 0;
    break;
  case GL_DEBUG_SEVERITY_MEDIUM:
    uiSevID = 1;
    break;
  case GL_DEBUG_SEVERITY_LOW:
    uiSevID = 2;
    break;
  case GL_DEBUG_SEVERITY_NOTIFICATION:
  default:
    uiSevID = 3;
    break;
  }
  // Get the type
  uint32_t uiTypeID = 5;
  switch (uiType) {
  case GL_DEBUG_TYPE_ERROR:
    uiTypeID = 0;
    break;
  case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
    uiTypeID = 1;
    break;
  case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
    uiTypeID = 2;
    break;
  case GL_DEBUG_TYPE_PORTABILITY:
    uiTypeID = 3;
    break;
  case GL_DEBUG_TYPE_PERFORMANCE:
    uiTypeID = 4;
    break;
  case GL_DEBUG_TYPE_OTHER:
  default:
    uiTypeID = 5;
    break;
  }
  // Get the source
  uint32_t uiSourceID = 5;
  switch (uiSource) {
  case GL_DEBUG_SOURCE_API:
    uiSourceID = 0;
    break;
  case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
    uiSourceID = 1;
    break;
  case GL_DEBUG_SOURCE_SHADER_COMPILER:
    uiSourceID = 2;
    break;
  case GL_DEBUG_SOURCE_THIRD_PARTY:
    uiSourceID = 3;
    break;
  case GL_DEBUG_SOURCE_APPLICATION:
    uiSourceID = 4;
    break;
  case GL_DEBUG_SOURCE_OTHER:
  default:
    uiSourceID = 5;
    break;
  }

  // Output to the Log
  SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION,
                  "OpenGL Debug: Severity=%s, Type=%s, Source=%s - %s",
                  gp_cSeverity[uiSevID], gp_cType[uiTypeID],
                  gp_cSource[uiSourceID], p_cMessage);
  if (uiSeverity == GL_DEBUG_SEVERITY_HIGH) {
    // This a serious error so we need to shutdown the program
    SDL_Event event;
    event.type = SDL_QUIT;
    SDL_PushEvent(&event);
  }
}

void GLDebug_Init() {
  // Allow for synchronous callbacks.
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

  // Set up the debug info callback
  glDebugMessageCallback((GLDEBUGPROC)&DebugCallback, NULL);

  // Set up the type of debug information we want to receive
  uint32_t uiUnusedIDs = 0;
  glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0,
                        &uiUnusedIDs, GL_TRUE); // Enable all
  glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE,
                        GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL,
                        GL_FALSE); // Disable notifications
}

// options thingy
#ifdef _DEBUG
// Initialise debug call-back
GLDebug_Init();
SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
#endif

// END GL_DEBUG

// BEGIN OPENGL SETUp

// OpenGL setup
GLuint gl_VAO[2];           // Vertex Array Object
GLuint gl_VBO[2];           // Vertex Buffer Object
GLuint gl_IBO[2];           // IBO
GLsizei gl_iSphereElements; // sphere elements???
GLuint gl_SakoEngine;       // Shader program ID

// transformrers
// transformations
glm::mat4 g_m4Transform[5];
GLuint g_uiTransformUBO[5];

// load just one shader :)

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

// load shaders func

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

// declare window variables
int windowWidth = 800;
int windowHeight = 600;
bool windowIsFullscreen = false;

struct LocalCameraData {
  float m_fAngleX;
  float m_fAngleY;
  glm::vec3 m_v3Position;
  glm::vec3 m_v3Direction;
  glm::vec3 m_v3Right;
  float m_fFOV;
  float m_fAspect;
  float m_fNear;
  float m_fFar;
};
LocalCameraData g_CameraData;
GLuint g_uiCameraUBO;

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
  glGenVertexArrays(2, &gl_VAO[0]);
  glBindVertexArray(gl_VAO[0]);

  // Create VBO data
  GLfloat fVertexData[] = {-0.5f, -0.5f, 0.5f, -0.5f, 0.0f, 0.5f};

  // Initialise camera data
  g_CameraData.m_fAngleX = (float)M_PI;
  g_CameraData.m_fAngleY = 0.0f;
  g_CameraData.m_v3Position = glm::vec3(0.0f, 0.0f, 12.0f);
  g_CameraData.m_v3Direction = glm::vec3(0.0f, 0.0f, -1.0f);
  g_CameraData.m_v3Right = glm::vec3(1.0f, 0.0f, 0.0f);

  // Initialise camera projection values
  g_CameraData.m_fFOV = glm::radians(45.0f);
  g_CameraData.m_fAspect = (float)windowWidth / (float)windowHeight;
  g_CameraData.m_fNear = 0.1f;
  g_CameraData.m_fFar = 100.0f;

  // Create updated camera View matrix
  glm::mat4 m4View =
      lookAt(g_CameraData.m_v3Position,
             g_CameraData.m_v3Position + g_CameraData.m_v3Direction,
             cross(g_CameraData.m_v3Right, g_CameraData.m_v3Direction));

  // Create updated camera projection matrix
  glm::mat4 m4Projection =
      glm::perspective(g_CameraData.m_fFOV, g_CameraData.m_fAspect,
                       g_CameraData.m_fNear, g_CameraData.m_fFar);

  // Create updated ViewProjection matrix
  glm::mat4 m4ViewProjection = m4Projection * m4View;

  // Update the camera buffer
  glBindBuffer(GL_UNIFORM_BUFFER, g_uiCameraUBO);
  glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), &m4ViewProjection,
               GL_DYNAMIC_DRAW);

  // Bind camera UBO
  glBindBufferBase(GL_UNIFORM_BUFFER, 1, g_uiCameraUBO);

  // Create Vertex Buffer Object
  glGenBuffers(2, &gl_VBO[0]);
  glGenBuffers(2, &gl_IBO[0]);
  glBindBuffer(GL_ARRAY_BUFFER, gl_VBO[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(fVertexData), fVertexData,
               GL_STATIC_DRAW);

  // Specify location of data within buffer
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat),
                        (const GLvoid *)0);
  glEnableVertexAttribArray(0);

  glUseProgram(gl_SakoEngine);

  return true;
}

// create geometry to render :)

struct CustomVertex {
  glm::vec3 v3Position;
};
// this makes a cube

GLsizei GL_GenerateCube(GLuint gl_VBO, GLuint gl_IBO) {
  // *** Add geometry code here ***

  // this is vertex data for a square
  // unit cube with a length of 1
  // a cube has 8 verticies
  // .   .   .
  // .   .   .
  // idk how to make ascii visualizations just know there are two more in the
  // back
  CustomVertex VertexData[] = {
      {glm::vec3(0.5f, 0.5f, -0.5f)},   {glm::vec3(0.5f, -0.5f, -0.5f)},
      {glm::vec3(-0.5f, -0.5f, -0.5f)}, {glm::vec3(-0.5f, 0.5f, -0.5f)},
      {glm::vec3(-0.5f, -0.5f, 0.5f)},  {glm::vec3(-0.5f, 0.5f, 0.5f)},
      {glm::vec3(0.5f, -0.5f, 0.5f)},   {glm::vec3(0.5f, 0.5f, 0.5f)}};

  GLuint uiIndexData[] = {
      0, 1, 3, 3, 1, 2, // Create back face
      3, 2, 5, 5, 2, 4, // Create left face
      1, 6, 2, 2, 6, 4, // Create bottom face
      5, 4, 7, 7, 4, 6, // Create front face
      7, 6, 0, 0, 6, 1, // Create right face
      7, 0, 5, 5, 0, 3  // Create top face
  };

  // Fill Vertex Buffer Object
  glBindBuffer(GL_ARRAY_BUFFER, gl_VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData), VertexData, GL_STATIC_DRAW);

  // Fill Index Buffer Object
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_IBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uiIndexData), uiIndexData,
               GL_STATIC_DRAW);

  // Specify location of data within buffer
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(CustomVertex),
                        (const GLvoid *)0);
  glEnableVertexAttribArray(0);

  return (sizeof(uiIndexData) / sizeof(GLuint));
}

GLsizei GL_GenerateSphere(uint32_t uiTessU, uint32_t uiTessV, GLuint gl_VBO,
                          GLuint gl_IBO) {
  // *** Add geometry code here ***
  // Init params
  float fDPhi = (float)M_PI / (float)uiTessV;
  float fDTheta = (float)(M_PI + M_PI) / (float)uiTessU;

  // Determine required parameters
  uint32_t uiNumVertices = (uiTessU * (uiTessV - 1)) + 2;
  uint32_t uiNumIndices = (uiTessU * 6) + (uiTessU * (uiTessV - 2) * 6);

  // Create the new primitive
  CustomVertex *p_VBuffer =
      (CustomVertex *)malloc(uiNumVertices * sizeof(CustomVertex));
  GLuint *p_IBuffer = (GLuint *)malloc(uiNumIndices * sizeof(GLuint));

  // Set the top and bottom vertex and reuse
  CustomVertex *p_vBuffer = p_VBuffer;
  p_vBuffer->v3Position = glm::vec3(0.0f, 1.0f, 0.0f);
  p_vBuffer[uiNumVertices - 1].v3Position = glm::vec3(0.0f, -1.0f, 0.0f);
  p_vBuffer++;

  float fPhi = fDPhi;
  for (uint32_t uiPhi = 0; uiPhi < uiTessV - 1; uiPhi++) {
    // Calculate initial value
    float fRSinPhi = sinf(fPhi);
    float fRCosPhi = cosf(fPhi);

    float fY = fRCosPhi;

    float fTheta = 0.0f;
    for (uint32_t uiTheta = 0; uiTheta < uiTessU; uiTheta++) {
      // Calculate positions
      float fCosTheta = cosf(fTheta);
      float fSinTheta = sinf(fTheta);

      // Determine position
      float fX = fRSinPhi * fCosTheta;
      float fZ = fRSinPhi * fSinTheta;

      // Create vertex
      p_vBuffer->v3Position = glm::vec3(fX, fY, fZ);
      p_vBuffer++;
      fTheta += fDTheta;
    }
    fPhi += fDPhi;
  }

  // Create top
  GLuint *p_iBuffer = p_IBuffer;
  for (GLuint j = 1; j <= uiTessU; j++) {
    // Top triangles all share same vertex point at pos 0
    *p_iBuffer++ = 0;
    // Loop back to start if required
    *p_iBuffer++ = ((j + 1) > uiTessU) ? 1 : j + 1;
    *p_iBuffer++ = j;
  }
  // Create inner triangles
  for (GLuint i = 0; i < uiTessV - 2; i++) {
    for (GLuint j = 1; j <= uiTessU; j++) {
      // Create indexes for each quad face (pair of triangles)
      *p_iBuffer++ = j + (i * uiTessU);
      // Loop back to start if required
      GLuint Index = ((j + 1) > uiTessU) ? 1 : j + 1;
      *p_iBuffer++ = Index + (i * uiTessU);
      *p_iBuffer++ = j + ((i + 1) * uiTessU);
      *p_iBuffer = *(p_iBuffer - 2);
      p_iBuffer++;
      // Loop back to start if required
      *p_iBuffer++ = Index + ((i + 1) * uiTessU);
      *p_iBuffer = *(p_iBuffer - 3);
      p_iBuffer++;
    }
  }

  // Create bottom
  for (GLuint j = 1; j <= uiTessU; j++) {
    // Bottom triangles all share same vertex at uiNumVertices-1
    *p_iBuffer++ = j + ((uiTessV - 2) * uiTessU);
    // Loop back to start if required
    GLuint Index = ((j + 1) > uiTessU) ? 1 : j + 1;
    *p_iBuffer++ = Index + ((uiTessV - 2) * uiTessU);
    *p_iBuffer++ = uiNumVertices - 1;
  }

  // Fill Vertex Buffer Object
  glBindBuffer(GL_ARRAY_BUFFER, gl_VBO);
  glBufferData(GL_ARRAY_BUFFER, uiNumVertices * sizeof(CustomVertex), p_VBuffer,
               GL_STATIC_DRAW);
  // Fill Index Buffer Object
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_IBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, uiNumIndices * sizeof(GLuint),
               p_IBuffer, GL_STATIC_DRAW);
  // Cleanup allocated data
  free(p_VBuffer);
  free(p_IBuffer);
  // Specify location of data within buffer
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(CustomVertex),
                        (const GLvoid *)0);
  glEnableVertexAttribArray(0);
  return uiNumIndices;
}

void gl_Render() {

  // Create initial model transforms
  g_m4Transform[0] = glm::mat4(1.0f); // Identity matrix
  g_m4Transform[1] = translate(glm::mat4(1.0f), glm::vec3(-3.0f, 0.0f, 0.0f));
  g_m4Transform[2] = translate(glm::mat4(1.0f), glm::vec3(0.0f, -3.0f, 0.0f));
  g_m4Transform[3] = translate(glm::mat4(1.0f), glm::vec3(3.0f, 0.0f, 0.0f));
  g_m4Transform[4] = translate(glm::mat4(1.0f), glm::vec3(0.0f, 3.0f, 0.0f));

  // Create transform UBOs
  glGenBuffers(5, &g_uiTransformUBO[0]);

  // Initialise the transform buffers
  for (int i = 0; i < 5; i++) {
    glBindBuffer(GL_UNIFORM_BUFFER, g_uiTransformUBO[i]);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), &g_m4Transform[i],
                 GL_STATIC_DRAW);
  }

  // Clear render outputand buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // Specify VAO to use
  glBindVertexArray(gl_VAO[0]);

  // Bind the Cube VAO
  glBindVertexArray(gl_VAO[0]);

  // Bind the Transform UBO
  glBindBufferBase(GL_UNIFORM_BUFFER, 0, g_uiTransformUBO[0]);

  // Create Cube VBO and IBO data
  GL_GenerateCube(gl_VBO[0], gl_IBO[0]);

  // Draw the Cube
  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

  // Bind the Sphere VAO
  glBindVertexArray(gl_VAO[1]);

  // Create Sphere VBO and IBO data
  gl_iSphereElements = GL_GenerateSphere(12, 6, gl_VBO[1], gl_IBO[1]);

  // Render each sphere
  for (int i = 1; i < 5; i++) {
    // Bind the Transform UBO
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, g_uiTransformUBO[i]);

    // Draw the Sphere
    glDrawElements(GL_TRIANGLES, gl_iSphereElements, GL_UNSIGNED_INT, 0);
  }

  // Draw the triangle
  glDrawArrays(GL_TRIANGLES, 0, 3);
}
void gl_Quit() {
  // Release the shader program
  glDeleteProgram(gl_SakoEngine);

  // Delete VBO and VAO
  glDeleteBuffers(1, &gl_VBO[0]);
  glDeleteVertexArrays(1, &gl_VAO[0]);
  // Delete VBOs/IBOs and VAOs
  glDeleteBuffers(2, &gl_VBO[0]);
  glDeleteBuffers(2, &gl_IBO[0]);
  glDeleteVertexArrays(2, &gl_VAO[0]);

  // Delete transform and camera UBOs
  glDeleteBuffers(5, &g_uiTransformUBO[0]);
  glDeleteBuffers(1, &g_uiCameraUBO);
}

// END OPENGL SETUP

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

  // TODO Customizable window size probably
  // //Get desktop resolution
  // SDL_DisplayMode CurrentDisplay;
  // SDL_GetCurrentDisplayMode(0, &CurrentDisplay);

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
