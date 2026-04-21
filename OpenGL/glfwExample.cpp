#include <cstdlib>
#include <iostream>
#include <vector>
#include "ray.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "GLSL.h"

#include "SimpleCamera_Impl.h"

int CheckGLErrors(const char *s)
{
  int errCount = 0;
  return errCount;
}

int main(void)
{
  /* Initialize the library */
  if (!glfwInit()) {
    exit(-1);
  }
  // throw std::runtime_error("Error! initialization of glfw failed!");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  /* Create a windowed mode window and its OpenGL context */
  int winWidth = 1000;
  float aspectRatio = 1.0;// 16.0 / 9.0; // winWidth / (float)winHeight;
  int winHeight = winWidth / aspectRatio;

  GLFWwindow *window = glfwCreateWindow(winWidth, winHeight, "GLFW Example", NULL, NULL);
  if (!window) {
    std::cerr << "GLFW did not create a window!" << std::endl;

    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (err != GLEW_OK) {
    std::cerr << "GLEW Error! glewInit failed, exiting." << std::endl;
    exit(EXIT_FAILURE);
  }

  const GLubyte *renderer = glGetString(GL_RENDERER);
  const GLubyte *version = glGetString(GL_VERSION);
  std::cout << "Renderer: " << renderer << std::endl;
  std::cout << "OpenGL version supported: " << version << std::endl;

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glClearColor(0.7216, 0.451, 0.2, 1.0);

  int fb_width, fb_height;
  glfwGetFramebufferSize(window, &fb_width, &fb_height);
  glViewport(0, 0, fb_width, fb_height);

  // Need to set a projection matrix that fits the aspect ratio set
  // by the window frame.
  //

  GLint major_version;
  glGetIntegerv(GL_MAJOR_VERSION, &major_version);
  std::cout << "GL_MAJOR_VERSION: " << major_version << std::endl;

  // Initialize all my data and get it on the GPU.
  // load the scene file...
  // get my shapes in the scene...

  GLuint m_triangleVBO[1], m_VAO;

  // load a triangle...
  // create a Vertex Array Buffer to hold our triangle data
  glGenBuffers(1, m_triangleVBO);

  glBindBuffer(GL_ARRAY_BUFFER, m_triangleVBO[0]);

  // this is the actual triangle data that will be copied to
  // the GPU memory
  std::vector<float> host_VertexBuffer = {
    // Front (+Z)
    -1,
    -1,
    1,
    0,
    0,
    1,
    1,
    -1,
    1,
    0,
    0,
    1,
    1,
    1,
    1,
    0,
    0,
    1,

    -1,
    -1,
    1,
    0,
    0,
    1,
    1,
    1,
    1,
    0,
    0,
    1,
    -1,
    1,
    1,
    0,
    0,
    1,

    // Back (-Z)
    -1,
    -1,
    -1,
    0,
    0,
    -1,
    1,
    1,
    -1,
    0,
    0,
    -1,
    1,
    -1,
    -1,
    0,
    0,
    -1,

    -1,
    -1,
    -1,
    0,
    0,
    -1,
    -1,
    1,
    -1,
    0,
    0,
    -1,
    1,
    1,
    -1,
    0,
    0,
    -1,

    // Left (-X)
    -1,
    -1,
    -1,
    -1,
    0,
    0,
    -1,
    -1,
    1,
    -1,
    0,
    0,
    -1,
    1,
    1,
    -1,
    0,
    0,

    -1,
    -1,
    -1,
    -1,
    0,
    0,
    -1,
    1,
    1,
    -1,
    0,
    0,
    -1,
    1,
    -1,
    -1,
    0,
    0,

    // Right (+X)
    1,
    -1,
    -1,
    1,
    0,
    0,
    1,
    1,
    1,
    1,
    0,
    0,
    1,
    -1,
    1,
    1,
    0,
    0,

    1,
    -1,
    -1,
    1,
    0,
    0,
    1,
    1,
    -1,
    1,
    0,
    0,
    1,
    1,
    1,
    1,
    0,
    0,

    // Top (+Y)
    -1,
    1,
    -1,
    0,
    1,
    0,
    -1,
    1,
    1,
    0,
    1,
    0,
    1,
    1,
    1,
    0,
    1,
    0,

    -1,
    1,
    -1,
    0,
    1,
    0,
    1,
    1,
    1,
    0,
    1,
    0,
    1,
    1,
    -1,
    0,
    1,
    0,

    // Bottom (-Y)
    -1,
    -1,
    -1,
    0,
    -1,
    0,
    1,
    -1,
    1,
    0,
    -1,
    0,
    -1,
    -1,
    1,
    0,
    -1,
    0,

    -1,
    -1,
    -1,
    0,
    -1,
    0,
    1,
    -1,
    -1,
    0,
    -1,
    0,
    1,
    -1,
    1,
    0,
    -1,
    0,
  };

  std::vector<float> temp_VertexBuffer = {};
  std::vector<float> temp_VertexBufferTotalObjects = host_VertexBuffer;

  vec3 avgPt(0.0f, 0.0f, 0.0f);
  for (int j = 0; j < host_VertexBuffer.size(); j+=6) {
    avgPt+= vec3(host_VertexBuffer[j], host_VertexBuffer[j + 1], host_VertexBuffer[j + 2] );
  }
  avgPt = avgPt / (host_VertexBuffer.size() / 6);
  float rad = sqrt(pow((avgPt.x() - host_VertexBuffer[0]), 2) + pow((avgPt.y() - host_VertexBuffer[1]), 2) + pow((avgPt.z() - host_VertexBuffer[2]), 2));

  for (int i = 0; i < 6; i++) { //Edit the i for number of recursiouns
      for (int j = 0; j < host_VertexBuffer.size(); j+=18) {
          //find midpoints
        vec3 A(host_VertexBuffer[j], host_VertexBuffer[j + 1], host_VertexBuffer[j + 2]);
        vec3 B(host_VertexBuffer[j + 6], host_VertexBuffer[j + 7], host_VertexBuffer[j + 8]);
        vec3 C(host_VertexBuffer[j + 12], host_VertexBuffer[j + 13], host_VertexBuffer[j + 14]);

        vec3 ab = (A + B) / 2;
        vec3 bc = (B + C) / 2;
        vec3 ca = (C + A) / 2;

        //correct placement with radius
        ab = avgPt + rad * unit_vector(ab - avgPt);
        bc = avgPt + rad * unit_vector(bc - avgPt);
        ca = avgPt + rad * unit_vector(ca - avgPt);

        //insert new triangles
        //A ab ca
        temp_VertexBuffer.push_back(A.x());
        temp_VertexBuffer.push_back(A.y());
        temp_VertexBuffer.push_back(A.z());
        temp_VertexBuffer.push_back(0.0);
        temp_VertexBuffer.push_back(0.0);
        temp_VertexBuffer.push_back(0.0);

        temp_VertexBuffer.push_back(ab.x());
        temp_VertexBuffer.push_back(ab.y());
        temp_VertexBuffer.push_back(ab.z());
        temp_VertexBuffer.push_back(0.0);
        temp_VertexBuffer.push_back(0.0);
        temp_VertexBuffer.push_back(0.0);

        temp_VertexBuffer.push_back(ca.x());
        temp_VertexBuffer.push_back(ca.y());
        temp_VertexBuffer.push_back(ca.z());
        temp_VertexBuffer.push_back(0.0);
        temp_VertexBuffer.push_back(0.0);
        temp_VertexBuffer.push_back(0.0);


        //ab B bc
        temp_VertexBuffer.push_back(ab.x());
        temp_VertexBuffer.push_back(ab.y());
        temp_VertexBuffer.push_back(ab.z());
        temp_VertexBuffer.push_back(0.0);
        temp_VertexBuffer.push_back(0.0);
        temp_VertexBuffer.push_back(0.0);

        temp_VertexBuffer.push_back(B.x());
        temp_VertexBuffer.push_back(B.y());
        temp_VertexBuffer.push_back(B.z());
        temp_VertexBuffer.push_back(0.0);
        temp_VertexBuffer.push_back(0.0);
        temp_VertexBuffer.push_back(0.0);

        temp_VertexBuffer.push_back(bc.x());
        temp_VertexBuffer.push_back(bc.y());
        temp_VertexBuffer.push_back(bc.z());
        temp_VertexBuffer.push_back(0.0);
        temp_VertexBuffer.push_back(0.0);
        temp_VertexBuffer.push_back(0.0);


        //ca bc c

        temp_VertexBuffer.push_back(ca.x());
        temp_VertexBuffer.push_back(ca.y());
        temp_VertexBuffer.push_back(ca.z());
        temp_VertexBuffer.push_back(0.0);
        temp_VertexBuffer.push_back(0.0);
        temp_VertexBuffer.push_back(0.0);

        temp_VertexBuffer.push_back(bc.x());
        temp_VertexBuffer.push_back(bc.y());
        temp_VertexBuffer.push_back(bc.z());
        temp_VertexBuffer.push_back(0.0);
        temp_VertexBuffer.push_back(0.0);
        temp_VertexBuffer.push_back(0.0);

        temp_VertexBuffer.push_back(C.x());
        temp_VertexBuffer.push_back(C.y());
        temp_VertexBuffer.push_back(C.z());
        temp_VertexBuffer.push_back(0.0);
        temp_VertexBuffer.push_back(0.0);
        temp_VertexBuffer.push_back(0.0);

        //ab bc ca

        temp_VertexBuffer.push_back(ab.x());
        temp_VertexBuffer.push_back(ab.y());
        temp_VertexBuffer.push_back(ab.z());
        temp_VertexBuffer.push_back(0.0);
        temp_VertexBuffer.push_back(0.0);
        temp_VertexBuffer.push_back(0.0);

        temp_VertexBuffer.push_back(bc.x());
        temp_VertexBuffer.push_back(bc.y());
        temp_VertexBuffer.push_back(bc.z());
        temp_VertexBuffer.push_back(0.0);
        temp_VertexBuffer.push_back(0.0);
        temp_VertexBuffer.push_back(0.0);

        temp_VertexBuffer.push_back(ca.x());
        temp_VertexBuffer.push_back(ca.y());
        temp_VertexBuffer.push_back(ca.z());
        temp_VertexBuffer.push_back(0.0);
        temp_VertexBuffer.push_back(0.0);
        temp_VertexBuffer.push_back(0.0);

      }
      for (int j = 0; j < temp_VertexBuffer.size(); j++) {
        temp_VertexBufferTotalObjects.push_back(temp_VertexBuffer[j] + i*2 + 2);
      }
      host_VertexBuffer = temp_VertexBuffer;
  }
  host_VertexBuffer = temp_VertexBufferTotalObjects;

  //host_VertexBuffer = temp_VertexBuffer;

  /*
  for (int i = 0; i < temp_VertexBuffer.size(); i++) {
    std::cout << temp_VertexBuffer[i];
  }*/

  /**/
  for (int i = 0; i < host_VertexBuffer.size(); i+=18) {
    vec3 a(host_VertexBuffer[i], host_VertexBuffer[i + 1], host_VertexBuffer[i + 2]);
    vec3 b(host_VertexBuffer[i + 6], host_VertexBuffer[i + 7], host_VertexBuffer[i + 8]);
    vec3 c(host_VertexBuffer[i + 12], host_VertexBuffer[i + 13], host_VertexBuffer[i + 14]);

    vec3 ab = b - a;
    vec3 ac = c - a;
    vec3 norm = unit_vector(cross(ac, ab));

    //encode norm x
    host_VertexBuffer[i + 3] = norm.x();
    host_VertexBuffer[i + 9] = norm.x();
    host_VertexBuffer[i + 15] = norm.x();

    //encode norm y
    host_VertexBuffer[i + 4] = norm.y();
    host_VertexBuffer[i + 10] = norm.y();
    host_VertexBuffer[i + 16] = norm.y();

    //encode norm z
    host_VertexBuffer[i + 5] = norm.z();
    host_VertexBuffer[i + 11] = norm.z();
    host_VertexBuffer[i + 17] = norm.z();

  } //finds the norms of the triangle

  int numTriangles = host_VertexBuffer.size() / 6;

  int numBytes = host_VertexBuffer.size() * sizeof(float);

  // copy the numBytes from host_VertexBuffer t the GPU and store in
  // the currently bound VBO
  glBufferData(GL_ARRAY_BUFFER, numBytes, host_VertexBuffer.data(), GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // once copied, we no longer need the data on the host
  host_VertexBuffer.clear();

  // VAO for the VBO
  // create a vertex array object that will map the attributes in
  // our vertex buffer to different location attributes for our
  // // shaders

  glGenVertexArrays(1, &m_VAO);
  glBindVertexArray(m_VAO);

  // VAO details here - we only have 1 attribute or location
  // (Position of the vertex)

  glEnableVertexAttribArray(0);// enable attrib 0 - Vertex Position
  glEnableVertexAttribArray(1);// enable attrib 1 - normals
  //glEnableVertexAttribArray(2);// enable attrib 1 - vertex color

  glBindBuffer(GL_ARRAY_BUFFER, m_triangleVBO[0]);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (const GLvoid *)12);// normal
  //glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(GLfloat), (const GLvoid *)12);// normal
  glBindVertexArray(0);

  // Create a shader using my GLSLObject class
  sivelab::GLSLObject shader;
  shader.addShader("vertexShader_prepForPerFragment.glsl", sivelab::GLSLObject::VERTEX_SHADER);
  shader.addShader("fragment_prepForPerFragment.glsl", sivelab::GLSLObject::FRAGMENT_SHADER);
  shader.createProgram();

  GLuint projMatrixID, viewMatrixID, modelMatrixID, normalMatrixID, light, diffuseComponentID, specularID, PhongExponentID, cameraPos;
  projMatrixID = shader.createUniform("projMatrix");
  viewMatrixID = shader.createUniform("viewMatrix");
  modelMatrixID = shader.createUniform("modelMatrix");
  normalMatrixID = shader.createUniform("normalMatrix");
  diffuseComponentID = shader.createUniform("diffuseComponent");
  specularID = shader.createUniform("specularComponent");
  PhongExponentID = shader.createUniform("phongExponent");
  cameraPos = shader.createUniform("cameraPosWorld");

  light = shader.createUniform("lightPosWorld");

  glm::mat4 modelTransform = glm::mat4(1.0);
 
  glm::vec3 diffuseComponentColor = glm::vec3(.5, .1, .05);
  // modelTransform = glm::translate(modelTransform, glm::vec3(0.0f, 1.0f, 0.0f));
  float rot = 0;
  modelTransform = glm::rotate(modelTransform, rot, glm::vec3(0, 1, 0));
  glm::mat4 normalMtrx = glm::mat4(1.0);

  SimpleCamera_Impl cam;

  double timeDiff = 0.0, startFrameTime = 0.0, endFrameTime = 0.0;

  float rotAngle = 0.0f;

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    endFrameTime = glfwGetTime();
    timeDiff = endFrameTime - startFrameTime;
    startFrameTime = glfwGetTime();


    
    // Clear the window's buffer (or clear the screen to our
    // background color)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#if 0
    std::cout << "cam.getProjectionMatrix: \n"
              << '\t' << cam.getProjectionMatrix()[0][0] << ' ' << cam.getProjectionMatrix()[0][1] << ' ' << cam.getProjectionMatrix()[0][2] << ' ' << cam.getProjectionMatrix()[0][3] << '\n'
              << '\t' << cam.getProjectionMatrix()[1][0] << ' ' << cam.getProjectionMatrix()[1][1] << ' ' << cam.getProjectionMatrix()[1][2] << ' ' << cam.getProjectionMatrix()[1][3] << '\n'
              << '\t' << cam.getProjectionMatrix()[2][0] << ' ' << cam.getProjectionMatrix()[2][1] << ' ' << cam.getProjectionMatrix()[2][2] << ' ' << cam.getProjectionMatrix()[2][3] << '\n'
              << '\t' << cam.getProjectionMatrix()[3][0] << ' ' << cam.getProjectionMatrix()[3][1] << ' ' << cam.getProjectionMatrix()[3][2] << ' ' << cam.getProjectionMatrix()[3][3] << std::endl;

    std::cout << "cam.getViewMatrix: \n"
              << '\t' << cam.getViewMatrix()[0][0] << ' ' << cam.getViewMatrix()[0][1] << ' ' << cam.getViewMatrix()[0][2] << ' ' << cam.getViewMatrix()[0][3] << '\n'
              << '\t' << cam.getViewMatrix()[1][0] << ' ' << cam.getViewMatrix()[1][1] << ' ' << cam.getViewMatrix()[1][2] << ' ' << cam.getViewMatrix()[1][3] << '\n'
              << '\t' << cam.getViewMatrix()[2][0] << ' ' << cam.getViewMatrix()[2][1] << ' ' << cam.getViewMatrix()[2][2] << ' ' << cam.getViewMatrix()[2][3] << '\n'
              << '\t' << cam.getViewMatrix()[3][0] << ' ' << cam.getViewMatrix()[3][1] << ' ' << cam.getViewMatrix()[3][2] << ' ' << cam.getViewMatrix()[3][3] << std::endl;
#endif

    /* Render your objects here */
    shader.activate();

    glm::vec4 lightPos = glm::vec4(
      -5.0f,
      0.0f,
      -2.0f,
      1);


    // light block via chatGPT, spinning effect, very cool to play with
    /*
     float t = glfwGetTime();
    glm::vec4 lightPos = glm::vec4(
      4.0f * cos(t),
      3.0f,
      4.0f * sin(t),
      1); //Spinning light
      */

    modelTransform = glm::mat4(1.0);
    modelTransform = glm::rotate(modelTransform, rotAngle, glm::vec3(0, 1, 0));
    normalMtrx = glm::transpose(glm::inverse(modelTransform)); //M^t^-1
    rotAngle += 0.0005; //This controls how fast things spin
    if (rotAngle > 2.0 * 3.14159) rotAngle = 0.0f;
    
    float phongExp = 1.0f;
    glm::vec3 specularColor = glm::vec3(1.0f, 1.0f, 1.0f);
    glUniform3fv(specularID, 1, glm::value_ptr(specularColor));

    // pass in the new camera matrix and the projection matrix
    glUniformMatrix4fv(projMatrixID, 1, GL_FALSE, glm::value_ptr(cam.getProjectionMatrix()));
    glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, glm::value_ptr(cam.getViewMatrix()));
    glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, glm::value_ptr(modelTransform));
    glUniformMatrix4fv(normalMatrixID, 1, GL_FALSE, glm::value_ptr(normalMtrx));
    glUniform4fv(light, 1, glm::value_ptr(lightPos));
    glUniform3fv(diffuseComponentID, 1, glm::value_ptr(diffuseComponentColor));
    glUniform1f(PhongExponentID, phongExp);
    glUniform3fv(cameraPos, 1, glm::value_ptr(cam.getPosition()));

    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, numTriangles); //numTriangles dynamically renders based on the number of triangles in VBO
    glBindVertexArray(0);
    shader.deactivate();

    // Swap the front and back buffers
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
      cam.moveForward();
    }  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
      cam.strafeLeft();
    }  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
      cam.moveBackward();
    }  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
      cam.strafeRight();
    }

    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
      std::cout << "fps: " << 1.0 / timeDiff << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, 1);
    }
  }

  glfwTerminate();
  return 0;
}