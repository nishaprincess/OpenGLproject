/**
 * This project (GLSL_Project1) is created by Fahim Hasan Khan (fahimhasan.khan [at] ucalgary.ca)
 * based on the works of Andrew Robert Owens (arowens [at] ucalgary.ca)
 * who is a PhD student at Graphics Jungle, University of Calgary
 *
 * File:	main.cpp
 *
 * Summary:
 *
 * This is a (very) basic program to
 * 1) load shaders from external files, and make a shader program
 * 2) make Vertex Array Object and Vertex Buffer Object for the quad
 *
 **/

#include <iostream>
#include <cmath>
#include <chrono>
#include <limits>

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "ShaderTools.h"
#include "Vec3f.h"
#include "Mat4f.h"
#include "OpenGLMatrixTools.h"
#include "Camera.h"

//==================== GLOBAL VARIABLES ====================//
/*	Put here for simplicity. Feel free to restructure into
*	appropriate classes or abstractions.
*/

// Drawing Program
GLuint basicProgramID;

// Data needed for Quad sofa
GLuint vaoID;
GLuint vertBufferID;
Mat4f M;

// Data needed for Quad2 wall
GLuint vaoID2;
GLuint vertBufferID2;
Mat4f M2;

// Data needed for Quad3 table
GLuint vaoID3;
GLuint vertBufferID3;
Mat4f M3;

// Data needed for Quad4 lamp part3
GLuint vaoID4;
GLuint vertBufferID4;
Mat4f M4;

// Data needed for Quad5 lamp part2
GLuint vaoID5;
GLuint vertBufferID5;
Mat4f M5;

// Data needed for Quad6 lamp part1
GLuint vaoID6;
GLuint vertBufferID6;
Mat4f M6;

// Data needed for Quad7  window
GLuint vaoID7;
GLuint vertBufferID7;
Mat4f M7;

// Data needed for Quad8  sofa sit
GLuint vaoID8;
GLuint vertBufferID8;
Mat4f M8;

// Data needed for Quad9  window back and front
GLuint vaoID9;
GLuint vertBufferID9;
Mat4f M9;
// Data needed for Quad10  pic background
GLuint vaoID10;
GLuint vertBufferID10;
Mat4f M10;

// Data needed for Quad11  pic sorounding
GLuint vaoID11;
GLuint vertBufferID11;
Mat4f M11;

// Data needed for Quad12  pic hill
GLuint vaoID12;
GLuint vertBufferID12;
Mat4f M12;

// Data needed for Quad13  oic moon
GLuint vaoID13;
GLuint vertBufferID13;
Mat4f M13;

// Data needed for Quad14  table2
GLuint vaoID14;
GLuint vertBufferID14;
Mat4f M14;

// Data needed for Quad15  flowerpot
GLuint vaoID15;
GLuint vertBufferID15;
Mat4f M15;

// Data needed for Quad16  carpet
GLuint vaoID16;
GLuint vertBufferID16;
Mat4f M16;

// Data needed for Quad17  table front
GLuint vaoID17;
GLuint vertBufferID17;
Mat4f M17;

// Data needed for Quad18  table2 front
GLuint vaoID18;
GLuint vertBufferID18;
Mat4f M18;

// Data needed for Quad19  lamp part 3 front
GLuint vaoID19;
GLuint vertBufferID19;
Mat4f M19;

// Data needed for Quad20  floor
GLuint vaoID20;
GLuint vertBufferID20;
Mat4f M20;

// Data needed for Quad21  lamp part 1 front
GLuint vaoID21;
GLuint vertBufferID21;
Mat4f M21;

// Data needed for Quad22  flower pot front
GLuint vaoID22;
GLuint vertBufferID22;
Mat4f M22;

// Data needed for Quad23  window right
GLuint vaoID23;
GLuint vertBufferID23;
Mat4f M23;

// Data needed for Quad24  window cross1
GLuint vaoID24;
GLuint vertBufferID24;
Mat4f M24;

// Data needed for Quad25  window cross2
GLuint vaoID25;
GLuint vertBufferID25;
Mat4f M25;

// Data needed for window up top
GLuint line_vaoID;
GLuint line_vertBufferID;
Mat4f line_M;

// Data needed for Line2 window up bottom
GLuint line_vaoID2;
GLuint line_vertBufferID2;
Mat4f line_M2;
// Only one camera so only one veiw and perspective matrix are needed.
Mat4f V;
Mat4f P;

// Only one thing is rendered at a time, so only need one MVP
// When drawing different objects, update M and MVP = M * V * P
Mat4f MVP;


// Camera and veiwing Stuff
Camera camera;
int g_moveUpDown = 0;
int g_moveLeftRight = 0;
int g_moveBackForward = 0;
int g_rotateLeftRight = 0;
int g_rotateUpDown = 0;
int g_rotateRoll = 0;
float g_rotationSpeed = 0.015625;
float g_panningSpeed = 0.25;
bool g_cursorLocked;
float g_cursorX, g_cursorY;

bool g_play = false;

int WIN_WIDTH = 800, WIN_HEIGHT = 600;
int FB_WIDTH = 800, FB_HEIGHT = 600;
float WIN_FOV = 60;
float WIN_NEAR = 0.01;
float WIN_FAR = 1000;

//==================== FUNCTION DECLARATIONS ====================//
void displayFunc();
void resizeFunc();
void init();
void generateIDs();
void deleteIDs();
void setupVAO();
void loadQuadGeometryToGPU();
void loadQuad2GeometryToGPU();
void loadQuad3GeometryToGPU();
void loadQuad4GeometryToGPU();
void loadQuad5GeometryToGPU();
void loadQuad6GeometryToGPU();
void loadQuad7GeometryToGPU();
void loadQuad8GeometryToGPU();
void loadQuad9GeometryToGPU();
void loadQuad10GeometryToGPU();
void loadQuad11GeometryToGPU();
void loadQuad12GeometryToGPU();
void loadQuad13GeometryToGPU();
void loadQuad14GeometryToGPU();
void loadQuad15GeometryToGPU();
void loadQuad16GeometryToGPU();
void loadQuad17GeometryToGPU();
void loadQuad18GeometryToGPU();
void loadQuad19GeometryToGPU();
void loadQuad20GeometryToGPU();
void loadQuad21GeometryToGPU();
void loadQuad22GeometryToGPU();

void loadLineGeometryToGPU();
void loadLine2GeometryToGPU();
void reloadProjectionMatrix();
void loadModelViewMatrix();
void setupModelViewProjectionTransform();

void windowSetSizeFunc();
void windowKeyFunc(GLFWwindow *window, int key, int scancode, int action,
                   int mods);
void windowMouseMotionFunc(GLFWwindow *window, double x, double y);
void windowSetSizeFunc(GLFWwindow *window, int width, int height);
void windowSetFramebufferSizeFunc(GLFWwindow *window, int width, int height);
void windowMouseButtonFunc(GLFWwindow *window, int button, int action,
                           int mods);
void windowMouseMotionFunc(GLFWwindow *window, double x, double y);
void windowKeyFunc(GLFWwindow *window, int key, int scancode, int action,
                   int mods);
void animateQuad(float t);
void moveCamera();
void reloadMVPUniform();
void reloadColorUniform(float r, float g, float b);
std::string GL_ERROR();
int main(int, char **);

//==================== FUNCTION DEFINITIONS ====================//

void displayFunc()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use our shader
    glUseProgram(basicProgramID);

    // ===== DRAW QUAD ====== //
    MVP = P * V * M;
    reloadMVPUniform();
    reloadColorUniform(1,0.0039, 0.0039);
    //reloadColorUniform(.3672,.0898, .2266);


    // Use VAO that holds buffer bindings
    // and attribute config of buffers
    glBindVertexArray(vaoID);
    // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 92);



    // ===== DRAW QUAD2 ====== //
    MVP = P * V * M2;
    reloadMVPUniform();
    reloadColorUniform(1,.9492,.8008);

    // Use VAO that holds buffer bindings
    // and attribute config of buffers
    glBindVertexArray(vaoID2);
    // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // ===== DRAW QUAD3 ====== //
    MVP = P * V * M3;
    reloadMVPUniform();
    reloadColorUniform(.5781,.3984,.2148);

    // Use VAO that holds buffer bindings
    // and attribute config of buffers
    glBindVertexArray(vaoID3);
    // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 24);
// ===== DRAW QUAD4 ====== //
    MVP = P * V * M4;
    reloadMVPUniform();
    reloadColorUniform(.6719,.6641,.6641);

    // Use VAO that holds buffer bindings
    // and attribute config of buffers
    glBindVertexArray(vaoID4);
    // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 24);
// ===== DRAW QUAD5 ====== //
    MVP = P * V * M5;
    reloadMVPUniform();
    reloadColorUniform(.6719,.6641,.6641);

    // Use VAO that holds buffer bindings
    // and attribute config of buffers
    glBindVertexArray(vaoID5);
    // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 24);
// ===== DRAW QUAD6 ====== //
    MVP = P * V * M6;
    reloadMVPUniform();
    reloadColorUniform(1,1,0);

    // Use VAO that holds buffer bindings
    // and attribute config of buffers
    glBindVertexArray(vaoID6);
    // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 24);

// ===== DRAW QUAD7 ====== //
    MVP = P * V * M7;
    reloadMVPUniform();
    reloadColorUniform(.7656,.9336,.9570);

    // Use VAO that holds buffer bindings
    // and attribute config of buffers
    glBindVertexArray(vaoID7);
    // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // ===== DRAW QUAD8 ====== //
    MVP = P * V * M8;
    reloadMVPUniform();
    reloadColorUniform(1, .2031, .2031);
    //reloadColorUniform(.4570, .1094, .2812);

    // Use VAO that holds buffer bindings
    // and attribute config of buffers
    glBindVertexArray(vaoID8);
    // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

// ===== DRAW QUAD9 ====== //
    MVP = P * V * M9;
    reloadMVPUniform();
    reloadColorUniform(1, 1, 1);
    // Use VAO that holds buffer bindings
    // and attribute config of buffers
    glBindVertexArray(vaoID9);
    // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 36);

    // ===== DRAW QUAD10 ====== //
    MVP = P * V * M10;
    reloadMVPUniform();
    reloadColorUniform(.7656,.9336,.9570);    // Use VAO that holds buffer bindings
    // and attribute config of buffers
    glBindVertexArray(vaoID10);
    // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // ===== DRAW QUAD11 ====== //
    MVP = P * V * M11;
    reloadMVPUniform();
    reloadColorUniform(1,1,1);
    // Use VAO that holds buffer bindings
    // and attribute config of buffers
    glBindVertexArray(vaoID11);
    // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 16);

    // ===== DRAW QUAD12 ====== //
    MVP = P * V * M12;
    reloadMVPUniform();
    reloadColorUniform(0,0,1);
    // Use VAO that holds buffer bindings
    // and attribute config of buffers
    glBindVertexArray(vaoID12);
    // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);

    // ===== DRAW QUAD13 ====== //
    MVP = P * V * M13;
    reloadMVPUniform();
    reloadColorUniform(1,1,0);
    // Use VAO that holds buffer bindings
    // and attribute config of buffers
    glBindVertexArray(vaoID13);
    // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // ===== DRAW QUAD14 ====== //
    MVP = P * V * M14;
    reloadMVPUniform();
    reloadColorUniform(.5781,.3984,.2148);
    // Use VAO that holds buffer bindings
    // and attribute config of buffers
    glBindVertexArray(vaoID14);
    // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 24);

    // ===== DRAW QUAD15 ====== //
    MVP = P * V * M15;
    reloadMVPUniform();

    reloadColorUniform(.6328,.9336,.75);
    // Use VAO that holds buffer bindings
    // and attribute config of buffers
    glBindVertexArray(vaoID15);
    // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 20);

    // ===== DRAW QUAD16 ====== //
    MVP = P * V * M16;
    reloadMVPUniform();

    reloadColorUniform(1,1,1);
    // Use VAO that holds buffer bindings
    // and attribute config of buffers
    glBindVertexArray(vaoID16);
    // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 24);

    // ===== DRAW QUAD17 ====== //
    MVP = P * V * M17;
    reloadMVPUniform();
    reloadColorUniform(.6641,.5195,.3711);
    // Use VAO that holds buffer bindings
    // and attribute config of buffers
    glBindVertexArray(vaoID17);
    // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // ===== DRAW QUAD18 ====== //
    MVP = P * V * M18;
    reloadMVPUniform();
    reloadColorUniform(.6641,.5195,.3711);    // Use VAO that holds buffer bindings
    // and attribute config of buffers
    glBindVertexArray(vaoID18);
    // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // ===== DRAW QUAD19 ====== //
    MVP = P * V * M19;
    reloadMVPUniform();
    reloadColorUniform(1,1,.4922);    // Use VAO that holds buffer bindings
    // and attribute config of buffers
    glBindVertexArray(vaoID19);
    // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // ===== DRAW QUAD20 ====== //
    MVP = P * V * M20;
    reloadMVPUniform();

    reloadColorUniform(.9766,.9062,.7070);
    // Use VAO that holds buffer bindings
    // and attribute config of buffers
    glBindVertexArray(vaoID20);
    // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // ===== DRAW QUAD21 ====== //
    MVP = P * V * M21;
    reloadMVPUniform();
    reloadColorUniform(.7383,.7305,.7305);
    // Use VAO that holds buffer bindings
    // and attribute config of buffers
    glBindVertexArray(vaoID21);
    // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // ===== DRAW QUAD22 ====== //
    MVP = P * V * M22;
    reloadMVPUniform();
    reloadColorUniform(.7070,.9453,.8008);
    // Use VAO that holds buffer bindings
    // and attribute config of buffers
    glBindVertexArray(vaoID22);
    // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // ===== DRAW QUAD23 ====== //
    MVP = P * V * M23;
    reloadMVPUniform();
    reloadColorUniform(1,1,1);
    // Use VAO that holds buffer bindings
    // and attribute config of buffers
    glBindVertexArray(vaoID23);
    // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // ===== DRAW QUAD24 ====== //
    MVP = P * V * M24;
    reloadMVPUniform();
    reloadColorUniform(1,1,1);
    // Use VAO that holds buffer bindings
    // and attribute config of buffers
    glBindVertexArray(vaoID24);
    // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // ===== DRAW QUAD25 ====== //
    MVP = P * V * M25;
    reloadMVPUniform();
    reloadColorUniform(1,1,1);
    // Use VAO that holds buffer bindings
    // and attribute config of buffers
    glBindVertexArray(vaoID25);
    // Draw Quads, start at vertex 0, draw 4 of them (for a quad)
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


    // ==== DRAW LINE ===== //
    MVP = P * V * line_M;
    reloadMVPUniform();

    reloadColorUniform(1, 1, 1);

    // Use VAO that holds buffer bindings
    // and attribute config of buffers
    glBindVertexArray(line_vaoID);
    // Draw lines
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
// ==== DRAW LINE2 ===== //
    MVP = P * V * line_M2;
    reloadMVPUniform();

    reloadColorUniform(1, 1, 1);

    // Use VAO that holds buffer bindings
    // and attribute config of buffers
    glBindVertexArray(line_vaoID2);
    // Draw lines
    glDrawArrays(GL_TRIANGLE_STRIP, 0,4);
}

void animateQuad(float t)
{
    M = RotateAboutYMatrix(100 * t);
    M2 = RotateAboutYMatrix(100 * t);
    M3 = RotateAboutYMatrix(100 * t);
    M4 = RotateAboutYMatrix(100 * t);
    M5 = RotateAboutYMatrix(100 * t);
    M6 = RotateAboutYMatrix(100 * t);
    M7 = RotateAboutYMatrix(100 * t);
    M8 = RotateAboutYMatrix(100 * t);
    M9 = RotateAboutYMatrix(100 * t);
    M10 = RotateAboutYMatrix(100 * t);
    M11 = RotateAboutYMatrix(100 * t);
    M12 = RotateAboutYMatrix(100 * t);
    M13 = RotateAboutYMatrix(100 * t);
    M14 = RotateAboutYMatrix(100 * t);
    M15 = RotateAboutYMatrix(100 * t);
    M16 = RotateAboutYMatrix(100 * t);
    M17 = RotateAboutYMatrix(100 * t);
    M18 = RotateAboutYMatrix(100 * t);
    M19 = RotateAboutYMatrix(100 * t);
    M20 = RotateAboutYMatrix(100 * t);
    M21 = RotateAboutYMatrix(100 * t);
    M22 = RotateAboutYMatrix(100 * t);
    M23 = RotateAboutYMatrix(100 * t);
    M24 = RotateAboutYMatrix(100 * t);
    M25 = RotateAboutYMatrix(100 * t);
    line_M=RotateAboutYMatrix(100 * t);
    line_M2=RotateAboutYMatrix(100 * t);

    float s = (std::sin(t) + 1.f) / 2.f;
    float x = (1 - s) * (10) + s * (-10);

    M = TranslateMatrix(x, 0, 0) * M;
    M2 = TranslateMatrix(x, 0, 0) * M2;
    M3 = TranslateMatrix(x, 0, 0) * M3;
    M4 = TranslateMatrix(x, 0, 0) * M4;
    M5 = TranslateMatrix(x, 0, 0) * M5;
    M6 = TranslateMatrix(x, 0, 0) * M6;
    M7= TranslateMatrix(x, 0, 0) * M7;
    M8= TranslateMatrix(x, 0, 0) * M8;
    M9= TranslateMatrix(x, 0, 0) * M9;
    M10= TranslateMatrix(x, 0, 0) * M10;
    M11= TranslateMatrix(x, 0, 0) * M11;
    M12= TranslateMatrix(x, 0, 0) * M12;
    M13= TranslateMatrix(x, 0, 0) * M13;
    M14= TranslateMatrix(x, 0, 0) * M14;
    M15= TranslateMatrix(x, 0, 0) * M15;
    M16= TranslateMatrix(x, 0, 0) * M16;
    M17= TranslateMatrix(x, 0, 0) * M17;
    M18= TranslateMatrix(x, 0, 0) * M18;
    M19= TranslateMatrix(x, 0, 0) * M19;
    M20= TranslateMatrix(x, 0, 0) * M20;
    M21= TranslateMatrix(x, 0, 0) * M21;
    M22= TranslateMatrix(x, 0, 0) * M22;
    M23= TranslateMatrix(x, 0, 0) * M23;
    M24= TranslateMatrix(x, 0, 0) * M24;
    M25= TranslateMatrix(x, 0, 0) * M25;
    line_M = TranslateMatrix(x, 0, 0) * line_M;
    line_M2 = TranslateMatrix(x, 0, 0) * line_M2;
    setupModelViewProjectionTransform();
    reloadMVPUniform();
}

void loadQuadGeometryToGPU()
{
    // Just basic layout of floats, for a quad
    // 3 floats per vertex, 4 vertices
    std::vector<Vec3f> verts;
// sofa r front view start
    verts.push_back(Vec3f(-3, -1, 0));
    verts.push_back(Vec3f(-3, 1, 0));
    verts.push_back(Vec3f(3, -1, 0));
    verts.push_back(Vec3f(3, 1, 0));

    verts.push_back(Vec3f(3, -1, 0));
    verts.push_back(Vec3f(-3, -1, 0));
    verts.push_back(Vec3f(3.5, -1.5, 2));
    verts.push_back(Vec3f(-3.5, -1.5, 2));

    verts.push_back(Vec3f(3.5, -1.5, 2));
    verts.push_back(Vec3f(-3.5, -1.5, 2));
    verts.push_back(Vec3f(3.5, -3, 2));
    verts.push_back(Vec3f(-3.5, -3, 2));
// sofa r front view end

    verts.push_back(Vec3f(-3.5, -3, 2));
    verts.push_back(Vec3f(3.5, -3, 2));
    verts.push_back(Vec3f(-3, -3, 0));
    verts.push_back(Vec3f(3, -3, 0));

    verts.push_back(Vec3f(3, -3, 0));
    verts.push_back(Vec3f(3.5, -3, 2));
    verts.push_back(Vec3f(3, -1, 0));
    verts.push_back(Vec3f(3.5, -1.5, 2));

    verts.push_back(Vec3f(-3, -3, 0));
    verts.push_back(Vec3f(-3.5, -3, 2));
    verts.push_back(Vec3f(-3, -1, 0));
    verts.push_back(Vec3f(-3.5, -1.5, 2));



    verts.push_back(Vec3f(-3, -3, 0));
    verts.push_back(Vec3f(-3, -3, -1));
    verts.push_back(Vec3f(3, -3, 0));
    verts.push_back(Vec3f(3, -3, -1));

    verts.push_back(Vec3f(3, -3, -1));
    verts.push_back(Vec3f(3, 1, -1));
    verts.push_back(Vec3f(-3, -3, -1));
    verts.push_back(Vec3f(-3, 1, -1));

    verts.push_back(Vec3f(-3, 1, -1));
    verts.push_back(Vec3f(-3, 1, 0));
    verts.push_back(Vec3f(3, 1, -1));
    verts.push_back(Vec3f(3, 1, 0));

    verts.push_back(Vec3f(-3, 1, -1));
    verts.push_back(Vec3f(-3, 1, 0));
    verts.push_back(Vec3f(-3, -3, -1));
    verts.push_back(Vec3f(-3, -3, 0));

    verts.push_back(Vec3f(3, 1, -1));
    verts.push_back(Vec3f(3, 1, 0));
    verts.push_back(Vec3f(3, -3, -1));
    verts.push_back(Vec3f(3, -3, 0));



    verts.push_back(Vec3f(-3.5, -3, 2));
    verts.push_back(Vec3f(-4, -3, 2));
    verts.push_back(Vec3f(-3.5, -.5, 2));
    verts.push_back(Vec3f(-4, -.5, 2));

    verts.push_back(Vec3f(-3.5, -3, 2));
    verts.push_back(Vec3f(-4, -3, 2));
    verts.push_back(Vec3f(-3, -3, -1));
    verts.push_back(Vec3f(-3.5, -3, -1));

    verts.push_back(Vec3f(-3, -3,-1));
    verts.push_back(Vec3f(-3.5, -3,-1));
    verts.push_back(Vec3f(-3, -.5, -1));
    verts.push_back(Vec3f(-3.5, -.5, -1));


    verts.push_back(Vec3f(-3.5, -.5, 2));
    verts.push_back(Vec3f(-4, -.5, 2));
    verts.push_back(Vec3f(-3, -.5, -1));
    verts.push_back(Vec3f(-3.5, -.5, -1));



    verts.push_back(Vec3f(-3.5, -3, 2));
    verts.push_back(Vec3f(-3.5, -.5, 2));
    verts.push_back(Vec3f(-3, -.5, -1));
    verts.push_back(Vec3f(-3, -3, -1));

    verts.push_back(Vec3f(-4, -3, 2));
    verts.push_back(Vec3f(-4, -.5, 2));
    verts.push_back(Vec3f(-3.5, -3, -1));
    verts.push_back(Vec3f(-3.5, -.5, -1));


    verts.push_back(Vec3f(3.5, -3, 2));
    verts.push_back(Vec3f(4, -3, 2));
    verts.push_back(Vec3f(3.5, -.5, 2));
    verts.push_back(Vec3f(4, -.5, 2));

    verts.push_back(Vec3f(3.5, -3, 2));
    verts.push_back(Vec3f(4, -3, 2));
    verts.push_back(Vec3f(3, -3, -1));
    verts.push_back(Vec3f(3.5, -3, -1));

    verts.push_back(Vec3f(3, -3,-1));
    verts.push_back(Vec3f(3.5, -3,-1));
    verts.push_back(Vec3f(3, -.5, -1));
    verts.push_back(Vec3f(3.5, -.5, -1));


    verts.push_back(Vec3f(3.5, -.5, 2));
    verts.push_back(Vec3f(4, -.5, 2));
    verts.push_back(Vec3f(3, -.5, -1));
    verts.push_back(Vec3f(3.5, -.5, -1));



    verts.push_back(Vec3f(3.5, -3, 2));
    verts.push_back(Vec3f(3.5, -.5, 2));
    verts.push_back(Vec3f(3, -.5, -1));
    verts.push_back(Vec3f(3, -3, -1));

    verts.push_back(Vec3f(4, -3, 2));
    verts.push_back(Vec3f(4, -.5, 2));
    verts.push_back(Vec3f(3.5, -3, -1));
    verts.push_back(Vec3f(3.5, -.5, -1));


    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(Vec3f) * 92, // byte size of Vec3f, 4 of them
                 verts.data(),      // pointer (Vec3f*) to contents of verts
                 GL_STATIC_DRAW);   // Usage pattern of GPU buffer
}
void loadQuad2GeometryToGPU()
{
    // Just basic layout of floats, for a quad
    // 3 floats per vertex, 4 vertices
    std::vector<Vec3f> verts;
    verts.push_back(Vec3f(-15, -3, -5));
    verts.push_back(Vec3f(-15, 12, -5));
    verts.push_back(Vec3f(15, -3, -5));
    verts.push_back(Vec3f(15, 12, -5));




    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID2);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(Vec3f) * 4, // byte size of Vec3f, 4 of them
                 verts.data(),      // pointer (Vec3f*) to contents of verts
                 GL_STATIC_DRAW);   // Usage pattern of GPU buffer
}

void loadQuad3GeometryToGPU()
{
    // Just basic layout of floats, for a quad
    // 3 floats per vertex, 4 vertices
    std::vector<Vec3f> verts;
    verts.push_back(Vec3f(6, -3, 2));
    verts.push_back(Vec3f(6, -1, 2));
    verts.push_back(Vec3f(8, -3, 2));
    verts.push_back(Vec3f(8, -1, 2));

    verts.push_back(Vec3f(6, -3, 2));
    verts.push_back(Vec3f(8, -3, 2));
    verts.push_back(Vec3f(5.7, -3, 0));
    verts.push_back(Vec3f(7.7, -3, 0));

    verts.push_back(Vec3f(5.7, -3, 0));
    verts.push_back(Vec3f(7.7, -3, 0));
    verts.push_back(Vec3f(5.7, -1, 0));
    verts.push_back(Vec3f(7.7, -1, 0));

    verts.push_back(Vec3f(5.7, -1, 0));
    verts.push_back(Vec3f(6, -1, 2));
    verts.push_back(Vec3f(5.7, -3, 0));
    verts.push_back(Vec3f(6, -3, 2));

    verts.push_back(Vec3f(7.7, -1, 0));
    verts.push_back(Vec3f(8, -1, 2));
    verts.push_back(Vec3f(7.7, -3, 0));
    verts.push_back(Vec3f(8, -3, 2));

    verts.push_back(Vec3f(5.7, -1, 0));
    verts.push_back(Vec3f(6, -1, 2));

    verts.push_back(Vec3f(7.7, -1, 0));
    verts.push_back(Vec3f(8, -1, 2));

    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID3);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(Vec3f) * 24, // byte size of Vec3f, 4 of them
                 verts.data(),      // pointer (Vec3f*) to contents of verts
                 GL_STATIC_DRAW);   // Usage pattern of GPU buffer
}


void loadQuad4GeometryToGPU()
{
    // Just basic layout of floats, for a quad
    // 3 floats per vertex, 4 vertices
    std::vector<Vec3f> verts;
    verts.push_back(Vec3f(6.4, -1, 1.5));
    verts.push_back(Vec3f(6.4, -.8, 1.5));
    verts.push_back(Vec3f(7.2, -1, 1.5));
    verts.push_back(Vec3f(7.2, -.8, 1.5));

    verts.push_back(Vec3f(6.4, -1, 1.5));
    verts.push_back(Vec3f(7.2, -1, 1.5));
    verts.push_back(Vec3f(6.3, -1, .5));
    verts.push_back(Vec3f(7.1, -1, .5));

    verts.push_back(Vec3f(6.3, -1, .5));
    verts.push_back(Vec3f(7.2, -1, .5));
    verts.push_back(Vec3f(6.3, -.8, .5));
    verts.push_back(Vec3f(7.1, -.8, .5));

    verts.push_back(Vec3f(7.1, -.8, .5));
    verts.push_back(Vec3f(7.2, -.8, 1.5));
    verts.push_back(Vec3f(7.1, -1, .5));
    verts.push_back(Vec3f(7.2, -1, 1.5));

    verts.push_back(Vec3f(6.3, -.8, .5));
    verts.push_back(Vec3f(6.4, -.8, 1.5));
    verts.push_back(Vec3f(6.3, -1, .5));
    verts.push_back(Vec3f(6.4, -1, 1.5));

    verts.push_back(Vec3f(6.3, -.8, .5));
    verts.push_back(Vec3f(6.4, -.8, 1.5));
    verts.push_back(Vec3f(7.1, -.8, .5));
    verts.push_back(Vec3f(7.2, -.8, 1.5));


    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID4);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(Vec3f) * 24, // byte size of Vec3f, 4 of them
                 verts.data(),      // pointer (Vec3f*) to contents of verts
                 GL_STATIC_DRAW);   // Usage pattern of GPU buffer
}
void loadQuad5GeometryToGPU()
{
    // Just basic layout of floats, for a quad
    // 3 floats per vertex, 4 vertices
    std::vector<Vec3f> verts;

    verts.push_back(Vec3f(6.7, -.8, 1.3));
    verts.push_back(Vec3f(6.9, -.8, 1.3));
    verts.push_back(Vec3f(6.7, 0, 1.3));
    verts.push_back(Vec3f(6.9,0, 1.3));

    verts.push_back(Vec3f(6.7, -.8, 1.3));
    verts.push_back(Vec3f(6.9, -.8, 1.3));
    verts.push_back(Vec3f(6.6, -.8, 1));
    verts.push_back(Vec3f(6.8, -.8, 1));

    verts.push_back(Vec3f(6.6, -.8, 1));
    verts.push_back(Vec3f(6.8, -.8,1));
    verts.push_back(Vec3f(6.6, 0, 1));
    verts.push_back(Vec3f(6.8, 0, 1));

    verts.push_back(Vec3f(6.6, 0, 1));
    verts.push_back(Vec3f(6.7, 0, 1.3));
    verts.push_back(Vec3f(6.6, -.8, 1));
    verts.push_back(Vec3f(6.7, -.8, 1.3));

    verts.push_back(Vec3f(6.8, 0, 1));
    verts.push_back(Vec3f(6.9, 0, 1.3));
    verts.push_back(Vec3f(6.8, -.8, 1));
    verts.push_back(Vec3f(6.9, -.8, 1.3));


    verts.push_back(Vec3f(6.8, 0, 1));
    verts.push_back(Vec3f(6.6, 0, 1));
    verts.push_back(Vec3f(6.7, 0, 1.3));
    verts.push_back(Vec3f(6.9, 0, 1.3));

    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID5);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(Vec3f) * 24, // byte size of Vec3f, 4 of them
                 verts.data(),      // pointer (Vec3f*) to contents of verts
                 GL_STATIC_DRAW);   // Usage pattern of GPU buffer
}
void loadQuad6GeometryToGPU()
{
    // Just basic layout of floats, for a quad
    // 3 floats per vertex, 4 vertices
    std::vector<Vec3f> verts;
    verts.push_back(Vec3f(6.01, 0, 2));
    verts.push_back(Vec3f(7.4, 0, 2));
    verts.push_back(Vec3f(6.01, 1, 2));
    verts.push_back(Vec3f(7.4, 1, 2));

    verts.push_back(Vec3f(6.01, 0, 2));
    verts.push_back(Vec3f(7.4, 0, 2));
    verts.push_back(Vec3f(6.0, 0,0));
    verts.push_back(Vec3f(7.39, 0, 0));

    verts.push_back(Vec3f(6.0, 0,0));
    verts.push_back(Vec3f(7.39, 0, 0));
    verts.push_back(Vec3f(6.0, 1,0));
    verts.push_back(Vec3f(7.39, 1, 0));

    verts.push_back(Vec3f(6.01, 0, 2));
    verts.push_back(Vec3f(6.0, 0,0));
    verts.push_back(Vec3f(6.01, 1, 2));
    verts.push_back(Vec3f(6.0, 1,0));

    verts.push_back(Vec3f(7.4, 0, 2));
    verts.push_back(Vec3f(7.39, 0,0));
    verts.push_back(Vec3f(7.4, 1, 2));
    verts.push_back(Vec3f(7.39, 1,0));

    verts.push_back(Vec3f(6.01, 1, 2));
    verts.push_back(Vec3f(7.4, 1, 2));
    verts.push_back(Vec3f(6.0, 1,0));
    verts.push_back(Vec3f(7.39, 1,0));


    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID6);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(Vec3f) * 24, // byte size of Vec3f, 4 of them
                 verts.data(),      // pointer (Vec3f*) to contents of verts
                 GL_STATIC_DRAW);   // Usage pattern of GPU buffer
}
void loadQuad7GeometryToGPU()
{
    // Just basic layout of floats, for a quad
    // 3 floats per vertex, 4 vertices
    std::vector<Vec3f> verts;

    verts.push_back(Vec3f(-3.6,3, -4.8));
    verts.push_back(Vec3f(-3.6, 9, -4.8));
    verts.push_back(Vec3f(3.6, 3, -4.8));
    verts.push_back(Vec3f(3.6, 9, -4.8));





    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID7);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(Vec3f) * 4, // byte size of Vec3f, 4 of them
                 verts.data(),      // pointer (Vec3f*) to contents of verts
                 GL_STATIC_DRAW);   // Usage pattern of GPU buffer
}

void loadQuad8GeometryToGPU()
{
    // Just basic layout of floats, for a quad
    // 3 floats per vertex, 4 vertices

    std::vector<Vec3f> verts;


    verts.push_back(Vec3f(3, -1, 0));
    verts.push_back(Vec3f(-3, -1, 0));
    verts.push_back(Vec3f(3.5, -1.5, 2.03));
    verts.push_back(Vec3f(-3.5, -1.5, 2.03));

    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID8);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(Vec3f) * 4, // byte size of Vec3f, 4 of them
                 verts.data(),      // pointer (Vec3f*) to contents of verts
                 GL_STATIC_DRAW);   // Usage pattern of GPU buffer
}
void loadQuad9GeometryToGPU()
{
    // Just basic layout of floats, for a quad
    // 3 floats per vertex, 4 vertices

    std::vector<Vec3f> verts;


    verts.push_back(Vec3f(-3.8, 9,-4.8));
    verts.push_back(Vec3f(3.8, 9, -4.8));
    verts.push_back(Vec3f(-3.8, 9.2, -4.8));
    verts.push_back(Vec3f(3.8, 9.2, -4.8));

    verts.push_back(Vec3f(-3.8, 9,-4.8));
    verts.push_back(Vec3f(-3.6, 9,-4.8));
    verts.push_back(Vec3f(-3.8, 3,-4.8));
    verts.push_back(Vec3f(-3.6, 3,-4.8));

    verts.push_back(Vec3f(-3.8, 3,-4.8));
    verts.push_back(Vec3f(3.8, 3, -4.8));
    verts.push_back(Vec3f(-3.8, 2.2, -4.8));
    verts.push_back(Vec3f(3.8, 2.2, -4.8));

    verts.push_back(Vec3f(3.8, 3,-4.8));
    verts.push_back(Vec3f(3.6, 3,-4.8));
    verts.push_back(Vec3f(3.8, 9,-4.8));
    verts.push_back(Vec3f(3.6, 9,-4.8));



    //front

    verts.push_back(Vec3f(-3.8, 9,-4.6));
    verts.push_back(Vec3f(3.8, 9, -4.6));
    verts.push_back(Vec3f(-3.8, 9.2, -4.6));
    verts.push_back(Vec3f(3.8, 9.2, -4.6));

    verts.push_back(Vec3f(-3.8, 9,-4.6));
    verts.push_back(Vec3f(-3.6, 9,-4.6));
    verts.push_back(Vec3f(-3.8, 3,-4.6));
    verts.push_back(Vec3f(-3.6, 3,-4.6));

    verts.push_back(Vec3f(-3.8, 3,-4.6));
    verts.push_back(Vec3f(3.8, 3, -4.6));
    verts.push_back(Vec3f(-3.8, 2.2, -4.6));
    verts.push_back(Vec3f(3.8, 2.2, -4.6));

    verts.push_back(Vec3f(3.8, 3,-4.6));
    verts.push_back(Vec3f(3.6, 3,-4.6));
    verts.push_back(Vec3f(3.8, 9,-4.6));
    verts.push_back(Vec3f(3.6, 9,-4.6));

    //left
    verts.push_back(Vec3f(3.8, 9.2, -4.6));
    verts.push_back(Vec3f(3.8, 9.2, -4.8));
    verts.push_back(Vec3f(3.8, 2.2, -4.6));
    verts.push_back(Vec3f(3.8, 2.2, -4.8));

    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID9);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(Vec3f) *36, // byte size of Vec3f, 4 of them
                 verts.data(),      // pointer (Vec3f*) to contents of verts
                 GL_STATIC_DRAW);   // Usage pattern of GPU buffer
}
void loadQuad10GeometryToGPU()
{
    // Just basic layout of floats, for a quad
    // 3 floats per vertex, 4 vertices

    std::vector<Vec3f> verts;
    verts.push_back(Vec3f(7.5,5,-4.8));
    verts.push_back(Vec3f(7.5,6.5,-4.8));
    verts.push_back(Vec3f(10,5,-4.8));
    verts.push_back(Vec3f(10,6.5,-4.8));



    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID10);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(Vec3f) * 4, // byte size of Vec3f, 4 of them
                 verts.data(),      // pointer (Vec3f*) to contents of verts
                 GL_STATIC_DRAW);   // Usage pattern of GPU buffer
}

void loadQuad11GeometryToGPU()
{
    // Just basic layout of floats, for a quad
    // 3 floats per vertex, 4 vertices

    std::vector<Vec3f> verts;


    verts.push_back(Vec3f(7.3,6.5,-4.8));
    verts.push_back(Vec3f(10.2,6.5,-4.8));
    verts.push_back(Vec3f(7.3,6.7,-4.8));
    verts.push_back(Vec3f(10.2,6.7,-4.8));

    verts.push_back(Vec3f(7.3,6.5,-4.8));
    verts.push_back(Vec3f(7.5,6.5,-4.8));
    verts.push_back(Vec3f(7.3,5,-4.8));
    verts.push_back(Vec3f(7.5,5,-4.8));

    verts.push_back(Vec3f(7.3,5,-4.8));
    verts.push_back(Vec3f(7.3,4.8,-4.8));
    verts.push_back(Vec3f(10.2,5,-4.8));
    verts.push_back(Vec3f(10.2,4.8,-4.8));

    verts.push_back(Vec3f(10.2,5,-4.8));
    verts.push_back(Vec3f(10,5,-4.8));
    verts.push_back(Vec3f(10.2,6.5,-4.8));
    verts.push_back(Vec3f(10,6.5,-4.8));


    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID11);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(Vec3f) * 16, // byte size of Vec3f, 4 of them
                 verts.data(),      // pointer (Vec3f*) to contents of verts
                 GL_STATIC_DRAW);   // Usage pattern of GPU buffer
}
void loadQuad12GeometryToGPU()
{
    // Just basic layout of floats, for a quad
    // 3 floats per vertex, 4 vertices

    std::vector<Vec3f> verts;
    verts.push_back(Vec3f(8,6.3,-4.7));
    verts.push_back(Vec3f(9.8,5,-4.7));
    verts.push_back(Vec3f(7.6,5,-4.7));







    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID12);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(Vec3f) * 3, // byte size of Vec3f, 4 of them
                 verts.data(),      // pointer (Vec3f*) to contents of verts
                 GL_STATIC_DRAW);   // Usage pattern of GPU buffer
}
void loadQuad13GeometryToGPU()
{
    // Just basic layout of floats, for a quad
    // 3 floats per vertex, 4 vertices

    std::vector<Vec3f> verts;

    verts.push_back(Vec3f(9.3,6,-4.7));
    verts.push_back(Vec3f(9.3,5.7,-4.7));
    verts.push_back(Vec3f(9.6,6,-4.7));
    verts.push_back(Vec3f(9.6,5.7,-4.7));



    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID13);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(Vec3f) * 4, // byte size of Vec3f, 4 of them
                 verts.data(),      // pointer (Vec3f*) to contents of verts
                 GL_STATIC_DRAW);   // Usage pattern of GPU buffer
}

void loadQuad14GeometryToGPU()
{
    // Just basic layout of floats, for a quad
    // 3 floats per vertex, 4 vertices

    std::vector<Vec3f> verts;

    verts.push_back(Vec3f(-6, -3, 2));
    verts.push_back(Vec3f(-6, -1, 2));
    verts.push_back(Vec3f(-8, -3, 2));
    verts.push_back(Vec3f(-8, -1, 2));

    verts.push_back(Vec3f(-6, -3, 2));
    verts.push_back(Vec3f(-8, -3, 2));
    verts.push_back(Vec3f(-5.7, -3, 0));
    verts.push_back(Vec3f(-7.7, -3, 0));

    verts.push_back(Vec3f(-5.7, -3, 0));
    verts.push_back(Vec3f(-7.7, -3, 0));
    verts.push_back(Vec3f(-5.7, -1, 0));
    verts.push_back(Vec3f(-7.7, -1, 0));

    verts.push_back(Vec3f(-5.7, -1, 0));
    verts.push_back(Vec3f(-6, -1, 2));
    verts.push_back(Vec3f(-5.7, -3, 0));
    verts.push_back(Vec3f(-6, -3, 2));

    verts.push_back(Vec3f(-7.7, -1, 0));
    verts.push_back(Vec3f(-8, -1, 2));
    verts.push_back(Vec3f(-7.7, -3, 0));
    verts.push_back(Vec3f(-8, -3, 2));

    verts.push_back(Vec3f(-5.7, -1, 0));
    verts.push_back(Vec3f(-6, -1, 2));
    verts.push_back(Vec3f(-7.7, -1, 0));
    verts.push_back(Vec3f(-8, -1, 2));

    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID14);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(Vec3f) * 24, // byte size of Vec3f, 4 of them
                 verts.data(),      // pointer (Vec3f*) to contents of verts
                 GL_STATIC_DRAW);   // Usage pattern of GPU buffer
}

void loadQuad15GeometryToGPU()
{
    // Just basic layout of floats, for a quad
    // 3 floats per vertex, 4 vertices

    std::vector<Vec3f> verts;
    verts.push_back(Vec3f(-6.8, -1, 1.5));
    verts.push_back(Vec3f(-7.2, -1, 1.5));
    verts.push_back(Vec3f(-6.6, 1.5, 1.5));
    verts.push_back(Vec3f(-7.4, 1.5, 1.5));

    verts.push_back(Vec3f(-6.8, -1, 1.5));
    verts.push_back(Vec3f(-7.2, -1, 1.5));
    verts.push_back(Vec3f(-6.7, -1, .8));
    verts.push_back(Vec3f(-7.1, -1, .8));

    verts.push_back(Vec3f(-6.7, -1, .8));
    verts.push_back(Vec3f(-7.1, -1, .8));
    verts.push_back(Vec3f(-6.5, 1.5, .8));
    verts.push_back(Vec3f(-7.3, 1.5, .8));

    verts.push_back(Vec3f(-7.2, -1, 1.5));
    verts.push_back(Vec3f(-7.1, -1, .8));
    verts.push_back(Vec3f(-7.4, 1.5, 1.5));
    verts.push_back(Vec3f(-7.3, 1.5, .8));



    verts.push_back(Vec3f(-6.8, -1, 1.5));
    verts.push_back(Vec3f(-6.7, -1, .8));
    verts.push_back(Vec3f(-6.6, 1.5, 1.5));
    verts.push_back(Vec3f(-6.5, 1.5, .8));



    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID15);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(Vec3f) * 20, // byte size of Vec3f, 4 of them
                 verts.data(),      // pointer (Vec3f*) to contents of verts
                 GL_STATIC_DRAW);   // Usage pattern of GPU buffer
}
void loadQuad16GeometryToGPU()
{
    // Just basic layout of floats, for a quad
    // 3 floats per vertex, 4 vertices

    std::vector<Vec3f> verts;
    verts.push_back(Vec3f(-4,-3.2,4));
    verts.push_back(Vec3f(-4.2,-3.2,6));
    verts.push_back(Vec3f(4,-3.2,4));
    verts.push_back(Vec3f(4.2,-3.2,6));

    verts.push_back(Vec3f(-4,-3,4));
    verts.push_back(Vec3f(-4.2,-3,6));
    verts.push_back(Vec3f(4,-3,4));
    verts.push_back(Vec3f(4.2,-3,6));


    verts.push_back(Vec3f(4,-3.2,4));
    verts.push_back(Vec3f(4,-3,4));
    verts.push_back(Vec3f(-4,-3.2,4));
    verts.push_back(Vec3f(-4,-3,4));

    verts.push_back(Vec3f(4.2,-3.2,6));
    verts.push_back(Vec3f(4.2,-3,6));
    verts.push_back(Vec3f(-4.2,-3.2,6));
    verts.push_back(Vec3f(-4.2,-3,6));

    verts.push_back(Vec3f(4,-3.2,4));
    verts.push_back(Vec3f(4,-3,4));
    verts.push_back(Vec3f(4.2,-3.2,6));
    verts.push_back(Vec3f(4.2,-3,6));

    verts.push_back(Vec3f(-4,-3.2,4));
    verts.push_back(Vec3f(-4,-3,4));
    verts.push_back(Vec3f(-4.2,-3.2,6));
    verts.push_back(Vec3f(-4.2,-3,6));


    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID16);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(Vec3f) * 24, // byte size of Vec3f, 4 of them
                 verts.data(),      // pointer (Vec3f*) to contents of verts
                 GL_STATIC_DRAW);   // Usage pattern of GPU buffer
}

void loadQuad17GeometryToGPU()
{
    // Just basic layout of floats, for a quad
    // 3 floats per vertex, 4 vertices

    std::vector<Vec3f> verts;
    verts.push_back(Vec3f(6, -3, 2.02));
    verts.push_back(Vec3f(6, -1, 2.02));
    verts.push_back(Vec3f(8, -3, 2.02));
    verts.push_back(Vec3f(8, -1, 2.02));


    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID17);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(Vec3f) * 4, // byte size of Vec3f, 4 of them
                 verts.data(),      // pointer (Vec3f*) to contents of verts
                 GL_STATIC_DRAW);   // Usage pattern of GPU buffer
}
void loadQuad18GeometryToGPU()
{
    // Just basic layout of floats, for a quad
    // 3 floats per vertex, 4 vertices

    std::vector<Vec3f> verts;
    verts.push_back(Vec3f(-6, -3, 2.02));
    verts.push_back(Vec3f(-6, -1, 2.02));
    verts.push_back(Vec3f(-8, -3, 2.02));
    verts.push_back(Vec3f(-8, -1, 2.02));

    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID18);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(Vec3f) * 4, // byte size of Vec3f, 4 of them
                 verts.data(),      // pointer (Vec3f*) to contents of verts
                 GL_STATIC_DRAW);   // Usage pattern of GPU buffer
}
void loadQuad19GeometryToGPU()
{
    // Just basic layout of floats, for a quad
    // 3 floats per vertex, 4 vertices

    std::vector<Vec3f> verts;
    verts.push_back(Vec3f(6.01, 0, 2.02));
    verts.push_back(Vec3f(7.4, 0, 2.02));
    verts.push_back(Vec3f(6.01, 1, 2.02));
    verts.push_back(Vec3f(7.4, 1, 2.02));

    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID19);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(Vec3f) * 4, // byte size of Vec3f, 4 of them
                 verts.data(),      // pointer (Vec3f*) to contents of verts
                 GL_STATIC_DRAW);   // Usage pattern of GPU buffer
}
void loadQuad20GeometryToGPU()
{
    // Just basic layout of floats, for a quad
    // 3 floats per vertex, 4 vertices

    std::vector<Vec3f> verts;
    verts.push_back(Vec3f(-15, -3, -5));
    verts.push_back(Vec3f(15, -3, -5));
    verts.push_back(Vec3f(-15.2,-3.3, 7));
    verts.push_back(Vec3f(15.2, -3.3, 7));
    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID20);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(Vec3f) * 4, // byte size of Vec3f, 4 of them
                 verts.data(),      // pointer (Vec3f*) to contents of verts
                 GL_STATIC_DRAW);   // Usage pattern of GPU buffer
}
void loadQuad21GeometryToGPU()
{
    // Just basic layout of floats, for a quad
    // 3 floats per vertex, 4 vertices

    std::vector<Vec3f> verts;
    verts.push_back(Vec3f(6.4, -1, 1.54));
    verts.push_back(Vec3f(6.4, -.8, 1.54));
    verts.push_back(Vec3f(7.2, -1, 1.54));
    verts.push_back(Vec3f(7.2, -.8, 1.54));

    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID21);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(Vec3f) * 4, // byte size of Vec3f, 4 of them
                 verts.data(),      // pointer (Vec3f*) to contents of verts
                 GL_STATIC_DRAW);   // Usage pattern of GPU buffer
}
void loadQuad22GeometryToGPU()
{
    // Just basic layout of floats, for a quad
    // 3 floats per vertex, 4 vertices

    std::vector<Vec3f> verts;
    verts.push_back(Vec3f(-6.8, -1, 1.54));
    verts.push_back(Vec3f(-7.2, -1, 1.54));
    verts.push_back(Vec3f(-6.6, 1.5, 1.54));
    verts.push_back(Vec3f(-7.4, 1.5, 1.54));

    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID22);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(Vec3f) * 4, // byte size of Vec3f, 4 of them
                 verts.data(),      // pointer (Vec3f*) to contents of verts
                 GL_STATIC_DRAW);   // Usage pattern of GPU buffer
}

void loadQuad23GeometryToGPU()
{
    // Just basic layout of floats, for a quad
    // 3 floats per vertex, 4 vertices

    std::vector<Vec3f> verts;
     verts.push_back(Vec3f(-3.8, 9.2, -4.8));
    verts.push_back(Vec3f(-3.8, 9.2, -4.6));
    verts.push_back(Vec3f(-3.8, 2.2, -4.8));
    verts.push_back(Vec3f(-3.8, 2.2, -4.6));

    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID23);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(Vec3f) * 4, // byte size of Vec3f, 4 of them
                 verts.data(),      // pointer (Vec3f*) to contents of verts
                 GL_STATIC_DRAW);   // Usage pattern of GPU buffer
}
void loadQuad24GeometryToGPU()
{
    // Just basic layout of floats, for a quad
    // 3 floats per vertex, 4 vertices

    std::vector<Vec3f> verts;

    verts.push_back(Vec3f(-3.6,6.2, -4.7));
    verts.push_back(Vec3f(-3.6,5.8, -4.7));
    verts.push_back(Vec3f(3.6,6.2, -4.7));
    verts.push_back(Vec3f(3.6,5.8, -4.7));

    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID24);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(Vec3f) * 4, // byte size of Vec3f, 4 of them
                 verts.data(),      // pointer (Vec3f*) to contents of verts
                 GL_STATIC_DRAW);   // Usage pattern of GPU buffer
}
void loadQuad25GeometryToGPU()
{
    // Just basic layout of floats, for a quad
    // 3 floats per vertex, 4 vertices

    std::vector<Vec3f> verts;
   verts.push_back(Vec3f(-.2,3, -4.7));
    verts.push_back(Vec3f(.2,3, -4.7));
    verts.push_back(Vec3f(-.2,9, -4.7));
    verts.push_back(Vec3f(.2,9, -4.7));

    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID25);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(Vec3f) * 4, // byte size of Vec3f, 4 of them
                 verts.data(),      // pointer (Vec3f*) to contents of verts
                 GL_STATIC_DRAW);   // Usage pattern of GPU buffer
}
void loadLineGeometryToGPU()
{
    // Just basic layout of floats, for a quad
    // 3 floats per vertex, 4 vertices
    std::vector<Vec3f> verts;
    verts.push_back(Vec3f(-3.8, 9.2, -4.8));
    verts.push_back(Vec3f(-3.8, 9.2, -4.6));
    verts.push_back(Vec3f(3.8, 9.2, -4.8));
    verts.push_back(Vec3f(3.8, 9.2, -4.6));

    glBindBuffer(GL_ARRAY_BUFFER, line_vertBufferID);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(Vec3f) * 4, // byte size of Vec3f, 4 of them
                 verts.data(),      // pointer (Vec3f*) to contents of verts
                 GL_STATIC_DRAW);   // Usage pattern of GPU buffer
}
void loadLine2GeometryToGPU()
{
    // Just basic layout of floats, for a quad
    // 3 floats per vertex, 4 vertices
    std::vector<Vec3f> verts;
    verts.push_back(Vec3f(-3.6, 9, -4.8));
    verts.push_back(Vec3f(-3.6, 9, -4.6));
    verts.push_back(Vec3f(3.6, 9, -4.8));
    verts.push_back(Vec3f(3.6, 9, -4.6));
    glBindBuffer(GL_ARRAY_BUFFER, line_vertBufferID2);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(Vec3f) * 4, // byte size of Vec3f, 4 of them
                 verts.data(),      // pointer (Vec3f*) to contents of verts
                 GL_STATIC_DRAW);   // Usage pattern of GPU buffer
}
void setupVAO()
{
    glBindVertexArray(vaoID);

    glEnableVertexAttribArray(0); // match layout # in shader
    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID);
    glVertexAttribPointer(0,        // attribute layout # above
                          3,        // # of components (ie XYZ )
                          GL_FLOAT, // type of components
                          GL_FALSE, // need to be normalized?
                          0,        // stride
                          (void *)0 // array buffer offset
                         );

    glBindVertexArray(vaoID2);

    glEnableVertexAttribArray(0); // match layout # in shader
    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID2);
    glVertexAttribPointer(0,        // attribute layout # above
                          3,        // # of components (ie XYZ )
                          GL_FLOAT, // type of components
                          GL_FALSE, // need to be normalized?
                          0,        // stride
                          (void *)0 // array buffer offset
                         );
    glBindVertexArray(vaoID3);

    glEnableVertexAttribArray(0); // match layout # in shader
    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID3);
    glVertexAttribPointer(0,        // attribute layout # above
                          3,        // # of components (ie XYZ )
                          GL_FLOAT, // type of components
                          GL_FALSE, // need to be normalized?
                          0,        // stride
                          (void *)0 // array buffer offset
                         );
    glBindVertexArray(vaoID4);

    glEnableVertexAttribArray(0); // match layout # in shader
    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID4);
    glVertexAttribPointer(0,        // attribute layout # above
                          3,        // # of components (ie XYZ )
                          GL_FLOAT, // type of components
                          GL_FALSE, // need to be normalized?
                          0,        // stride
                          (void *)0 // array buffer offset
                         );
    glBindVertexArray(vaoID5);

    glEnableVertexAttribArray(0); // match layout # in shader
    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID5);
    glVertexAttribPointer(0,        // attribute layout # above
                          3,        // # of components (ie XYZ )
                          GL_FLOAT, // type of components
                          GL_FALSE, // need to be normalized?
                          0,        // stride
                          (void *)0 // array buffer offset
                         );
    glBindVertexArray(vaoID6);

    glEnableVertexAttribArray(0); // match layout # in shader
    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID6);
    glVertexAttribPointer(0,        // attribute layout # above
                          3,        // # of components (ie XYZ )
                          GL_FLOAT, // type of components
                          GL_FALSE, // need to be normalized?
                          0,        // stride
                          (void *)0 // array buffer offset
                         );
    glBindVertexArray(vaoID7);

    glEnableVertexAttribArray(0); // match layout # in shader
    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID7);
    glVertexAttribPointer(0,        // attribute layout # above
                          3,        // # of components (ie XYZ )
                          GL_FLOAT, // type of components
                          GL_FALSE, // need to be normalized?
                          0,        // stride
                          (void *)0 // array buffer offset
                         );
    glBindVertexArray(vaoID8);

    glEnableVertexAttribArray(0); // match layout # in shader
    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID8);
    glVertexAttribPointer(0,        // attribute layout # above
                          3,        // # of components (ie XYZ )
                          GL_FLOAT, // type of components
                          GL_FALSE, // need to be normalized?
                          0,        // stride
                          (void *)0 // array buffer offset
                         );

    glBindVertexArray(vaoID9);

    glEnableVertexAttribArray(0); // match layout # in shader
    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID9);
    glVertexAttribPointer(0,        // attribute layout # above
                          3,        // # of components (ie XYZ )
                          GL_FLOAT, // type of components
                          GL_FALSE, // need to be normalized?
                          0,        // stride
                          (void *)0 // array buffer offset
                         );

    glBindVertexArray(vaoID10);

    glEnableVertexAttribArray(0); // match layout # in shader
    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID10);
    glVertexAttribPointer(0,        // attribute layout # above
                          3,        // # of components (ie XYZ )
                          GL_FLOAT, // type of components
                          GL_FALSE, // need to be normalized?
                          0,        // stride
                          (void *)0 // array buffer offset
                         );
    glBindVertexArray(vaoID11);

    glEnableVertexAttribArray(0); // match layout # in shader
    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID11);
    glVertexAttribPointer(0,        // attribute layout # above
                          3,        // # of components (ie XYZ )
                          GL_FLOAT, // type of components
                          GL_FALSE, // need to be normalized?
                          0,        // stride
                          (void *)0 // array buffer offset
                         );
    glBindVertexArray(vaoID12);

    glEnableVertexAttribArray(0); // match layout # in shader
    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID12);
    glVertexAttribPointer(0,        // attribute layout # above
                          3,        // # of components (ie XYZ )
                          GL_FLOAT, // type of components
                          GL_FALSE, // need to be normalized?
                          0,        // stride
                          (void *)0 // array buffer offset
                         );
    glBindVertexArray(vaoID13);

    glEnableVertexAttribArray(0); // match layout # in shader
    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID13);
    glVertexAttribPointer(0,        // attribute layout # above
                          3,        // # of components (ie XYZ )
                          GL_FLOAT, // type of components
                          GL_FALSE, // need to be normalized?
                          0,        // stride
                          (void *)0 // array buffer offset
                         );
    glBindVertexArray(vaoID14);

    glEnableVertexAttribArray(0); // match layout # in shader
    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID14);
    glVertexAttribPointer(0,        // attribute layout # above
                          3,        // # of components (ie XYZ )
                          GL_FLOAT, // type of components
                          GL_FALSE, // need to be normalized?
                          0,        // stride
                          (void *)0 // array buffer offset
                         );
    glBindVertexArray(vaoID15);

    glEnableVertexAttribArray(0); // match layout # in shader
    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID15);
    glVertexAttribPointer(0,        // attribute layout # above
                          3,        // # of components (ie XYZ )
                          GL_FLOAT, // type of components
                          GL_FALSE, // need to be normalized?
                          0,        // stride
                          (void *)0 // array buffer offset
                         );
    glBindVertexArray(vaoID16);

    glEnableVertexAttribArray(0); // match layout # in shader
    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID16);
    glVertexAttribPointer(0,        // attribute layout # above
                          3,        // # of components (ie XYZ )
                          GL_FLOAT, // type of components
                          GL_FALSE, // need to be normalized?
                          0,        // stride
                          (void *)0 // array buffer offset
                         );
    glBindVertexArray(vaoID17);

    glEnableVertexAttribArray(0); // match layout # in shader
    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID17);
    glVertexAttribPointer(0,        // attribute layout # above
                          3,        // # of components (ie XYZ )
                          GL_FLOAT, // type of components
                          GL_FALSE, // need to be normalized?
                          0,        // stride
                          (void *)0 // array buffer offset
                         );
    glBindVertexArray(vaoID18);

    glEnableVertexAttribArray(0); // match layout # in shader
    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID18);
    glVertexAttribPointer(0,        // attribute layout # above
                          3,        // # of components (ie XYZ )
                          GL_FLOAT, // type of components
                          GL_FALSE, // need to be normalized?
                          0,        // stride
                          (void *)0 // array buffer offset
                         );
    glBindVertexArray(vaoID19);

    glEnableVertexAttribArray(0); // match layout # in shader
    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID19);
    glVertexAttribPointer(0,        // attribute layout # above
                          3,        // # of components (ie XYZ )
                          GL_FLOAT, // type of components
                          GL_FALSE, // need to be normalized?
                          0,        // stride
                          (void *)0 // array buffer offset
                         );
    glBindVertexArray(vaoID20);

    glEnableVertexAttribArray(0); // match layout # in shader
    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID20);
    glVertexAttribPointer(0,        // attribute layout # above
                          3,        // # of components (ie XYZ )
                          GL_FLOAT, // type of components
                          GL_FALSE, // need to be normalized?
                          0,        // stride
                          (void *)0 // array buffer offset
                         );
    glBindVertexArray(vaoID21);

    glEnableVertexAttribArray(0); // match layout # in shader
    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID21);
    glVertexAttribPointer(0,        // attribute layout # above
                          3,        // # of components (ie XYZ )
                          GL_FLOAT, // type of components
                          GL_FALSE, // need to be normalized?
                          0,        // stride
                          (void *)0 // array buffer offset
                         );
    glBindVertexArray(vaoID22);

    glEnableVertexAttribArray(0); // match layout # in shader
    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID22);
    glVertexAttribPointer(0,        // attribute layout # above
                          3,        // # of components (ie XYZ )
                          GL_FLOAT, // type of components
                          GL_FALSE, // need to be normalized?
                          0,        // stride
                          (void *)0 // array buffer offset
                         );
    glBindVertexArray(vaoID23);

    glEnableVertexAttribArray(0); // match layout # in shader
    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID23);
    glVertexAttribPointer(0,        // attribute layout # above
                          3,        // # of components (ie XYZ )
                          GL_FLOAT, // type of components
                          GL_FALSE, // need to be normalized?
                          0,        // stride
                          (void *)0 // array buffer offset
                         );
    glBindVertexArray(vaoID24);

    glEnableVertexAttribArray(0); // match layout # in shader
    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID24);
    glVertexAttribPointer(0,        // attribute layout # above
                          3,        // # of components (ie XYZ )
                          GL_FLOAT, // type of components
                          GL_FALSE, // need to be normalized?
                          0,        // stride
                          (void *)0 // array buffer offset
                         );
    glBindVertexArray(vaoID25);

    glEnableVertexAttribArray(0); // match layout # in shader
    glBindBuffer(GL_ARRAY_BUFFER, vertBufferID25);
    glVertexAttribPointer(0,        // attribute layout # above
                          3,        // # of components (ie XYZ )
                          GL_FLOAT, // type of components
                          GL_FALSE, // need to be normalized?
                          0,        // stride
                          (void *)0 // array buffer offset
                         );
    glBindVertexArray(line_vaoID);

    glEnableVertexAttribArray(0); // match layout # in shader
    glBindBuffer(GL_ARRAY_BUFFER, line_vertBufferID);
    glVertexAttribPointer(0,        // attribute layout # above
                          3,        // # of components (ie XYZ )
                          GL_FLOAT, // type of components
                          GL_FALSE, // need to be normalized?
                          0,        // stride
                          (void *)0 // array buffer offset
                         );
    glBindVertexArray(line_vaoID2);

    glEnableVertexAttribArray(0); // match layout # in shader
    glBindBuffer(GL_ARRAY_BUFFER, line_vertBufferID2);
    glVertexAttribPointer(0,        // attribute layout # above
                          3,        // # of components (ie XYZ )
                          GL_FLOAT, // type of components
                          GL_FALSE, // need to be normalized?
                          0,        // stride
                          (void *)0 // array buffer offset
                         );

    glBindVertexArray(0); // reset to default
}

void reloadProjectionMatrix()
{
    // Perspective Only

    // field of view angle 60 degrees
    // window aspect ratio
    // near Z plane > 0
    // far Z plane

    P = PerspectiveProjection(WIN_FOV, // FOV
                              static_cast<float>(WIN_WIDTH) /
                              WIN_HEIGHT, // Aspect
                              WIN_NEAR,       // near plane
                              WIN_FAR);       // far plane depth
}

void loadModelViewMatrix()
{
    M = IdentityMatrix();
    M2 = IdentityMatrix();
    M3 = IdentityMatrix();
    M4= IdentityMatrix();
    M5 = IdentityMatrix();
    M6 = IdentityMatrix();
    M7 = IdentityMatrix();
    M8 = IdentityMatrix();
    M9 = IdentityMatrix();
    M10 = IdentityMatrix();
    M11 = IdentityMatrix();
    M12 = IdentityMatrix();
    M13 = IdentityMatrix();
    M14 = IdentityMatrix();
    M15 = IdentityMatrix();
    M16 = IdentityMatrix();
    M17 = IdentityMatrix();
    M18 = IdentityMatrix();
    M19 = IdentityMatrix();
    M20 = IdentityMatrix();
    M21 = IdentityMatrix();
    M22 = IdentityMatrix();
    M23 = IdentityMatrix();
    M24 = IdentityMatrix();
    M25 = IdentityMatrix();
    line_M = IdentityMatrix();
    line_M2 = IdentityMatrix();
    // view doesn't change, but if it did you would use this
    V = camera.lookatMatrix();
}

void reloadViewMatrix()
{
    V = camera.lookatMatrix();
}

void setupModelViewProjectionTransform()
{
    MVP = P * V * M;// transforms vertices from right to left (odd huh?)
}

void reloadMVPUniform()
{
    GLint id = glGetUniformLocation(basicProgramID, "MVP");

    glUseProgram(basicProgramID);
    glUniformMatrix4fv(id,        // ID
                       1,         // only 1 matrix
                       GL_TRUE,   // transpose matrix, Mat4f is row major
                       MVP.data() // pointer to data in Mat4f
                      );
}

void reloadColorUniform(float r, float g, float b)
{
    GLint id = glGetUniformLocation(basicProgramID, "inputColor");

    glUseProgram(basicProgramID);
    glUniform3f(id, // ID in basic_vs.glsl
                r, g, b);
}

void generateIDs()
{
    // shader ID from OpenGL
    std::string vsSource = loadShaderStringfromFile("./shaders/basic.vert");
    std::string fsSource = loadShaderStringfromFile("./shaders/basic.frag");
    basicProgramID = CreateShaderProgram(vsSource, fsSource);

    // VAO and buffer IDs given from OpenGL
    glGenVertexArrays(1, &vaoID);
    glGenBuffers(1, &vertBufferID);
    glGenVertexArrays(1, &vaoID2);
    glGenBuffers(1, &vertBufferID2);
    glGenVertexArrays(1, &vaoID3);
    glGenBuffers(1, &vertBufferID3);
    glGenVertexArrays(1, &vaoID4);
    glGenBuffers(1, &vertBufferID4);
    glGenVertexArrays(1, &vaoID5);
    glGenBuffers(1, &vertBufferID5);
    glGenVertexArrays(1, &vaoID6);
    glGenBuffers(1, &vertBufferID6);
    glGenVertexArrays(1, &vaoID7);
    glGenBuffers(1, &vertBufferID7);
    glGenVertexArrays(1, &vaoID8);
    glGenBuffers(1, &vertBufferID8);
    glGenVertexArrays(1, &vaoID9);
    glGenBuffers(1, &vertBufferID9);
    glGenVertexArrays(1, &vaoID10);
    glGenBuffers(1, &vertBufferID10);
    glGenVertexArrays(1, &vaoID11);
    glGenBuffers(1, &vertBufferID11);
    glGenVertexArrays(1, &vaoID12);
    glGenBuffers(1, &vertBufferID12);
    glGenVertexArrays(1, &vaoID13);
    glGenBuffers(1, &vertBufferID13);
    glGenVertexArrays(1, &vaoID14);
    glGenBuffers(1, &vertBufferID14);
    glGenVertexArrays(1, &vaoID15);
    glGenBuffers(1, &vertBufferID15);
    glGenVertexArrays(1, &vaoID16);
    glGenBuffers(1, &vertBufferID16);
    glGenVertexArrays(1, &vaoID17);
    glGenBuffers(1, &vertBufferID17);
    glGenVertexArrays(1, &vaoID18);
    glGenBuffers(1, &vertBufferID18);
    glGenVertexArrays(1, &vaoID19);
    glGenBuffers(1, &vertBufferID19);
    glGenVertexArrays(1, &vaoID20);
    glGenBuffers(1, &vertBufferID20);
    glGenVertexArrays(1, &vaoID21);
    glGenBuffers(1, &vertBufferID21);
    glGenVertexArrays(1, &vaoID22);
    glGenBuffers(1, &vertBufferID22);
    glGenVertexArrays(1, &vaoID23);
    glGenBuffers(1, &vertBufferID23);
    glGenVertexArrays(1, &vaoID24);
    glGenBuffers(1, &vertBufferID24);
    glGenVertexArrays(1, &vaoID25);
    glGenBuffers(1, &vertBufferID25);
    glGenVertexArrays(1, &line_vaoID);
    glGenBuffers(1, &line_vertBufferID);
    glGenVertexArrays(1, &line_vaoID2);
    glGenBuffers(1, &line_vertBufferID2);

}

void deleteIDs()
{
    glDeleteProgram(basicProgramID);

    glDeleteVertexArrays(1, &vaoID);
    glDeleteBuffers(1, &vertBufferID);
    glDeleteVertexArrays(1, &vaoID2);
    glDeleteBuffers(1, &vertBufferID2);
    glDeleteVertexArrays(1, &vaoID3);
    glDeleteBuffers(1, &vertBufferID3);
    glDeleteVertexArrays(1, &vaoID4);
    glDeleteBuffers(1, &vertBufferID4);
    glDeleteVertexArrays(1, &vaoID5);
    glDeleteBuffers(1, &vertBufferID5);
    glDeleteVertexArrays(1, &vaoID6);
    glDeleteBuffers(1, &vertBufferID6);
    glDeleteVertexArrays(1, &vaoID7);
    glDeleteBuffers(1, &vertBufferID7);
    glDeleteVertexArrays(1, &vaoID8);
    glDeleteBuffers(1, &vertBufferID8);
    glDeleteVertexArrays(1, &vaoID9);
    glDeleteBuffers(1, &vertBufferID9);
    glDeleteVertexArrays(1, &vaoID10);
    glDeleteBuffers(1, &vertBufferID10);
    glDeleteVertexArrays(1, &vaoID11);
    glDeleteBuffers(1, &vertBufferID11);
    glDeleteVertexArrays(1, &vaoID12);
    glDeleteBuffers(1, &vertBufferID12);
    glDeleteVertexArrays(1, &vaoID13);
    glDeleteBuffers(1, &vertBufferID13);
    glDeleteVertexArrays(1, &vaoID14);
    glDeleteBuffers(1, &vertBufferID14);
    glDeleteVertexArrays(1, &vaoID15);
    glDeleteBuffers(1, &vertBufferID15);
    glDeleteVertexArrays(1, &vaoID16);
    glDeleteBuffers(1, &vertBufferID16);
    glDeleteVertexArrays(1, &vaoID17);
    glDeleteBuffers(1, &vertBufferID17);
    glDeleteVertexArrays(1, &vaoID18);
    glDeleteBuffers(1, &vertBufferID18);
    glDeleteVertexArrays(1, &vaoID19);
    glDeleteBuffers(1, &vertBufferID19);
    glDeleteVertexArrays(1, &vaoID20);
    glDeleteBuffers(1, &vertBufferID20);
    glDeleteVertexArrays(1, &vaoID21);
    glDeleteBuffers(1, &vertBufferID21);
    glDeleteVertexArrays(1, &vaoID22);
    glDeleteBuffers(1, &vertBufferID22);
    glDeleteVertexArrays(1, &vaoID23);
    glDeleteBuffers(1, &vertBufferID23);
    glDeleteVertexArrays(1, &vaoID24);
    glDeleteBuffers(1, &vertBufferID24);
    glDeleteVertexArrays(1, &vaoID25);
    glDeleteBuffers(1, &vertBufferID25);
    glDeleteVertexArrays(1, &line_vaoID);
    glDeleteBuffers(1, &line_vertBufferID);
    glDeleteVertexArrays(1, &line_vaoID2);
    glDeleteBuffers(1, &line_vertBufferID2);
}

void init()
{
    glEnable(GL_DEPTH_TEST);
    glPointSize(50);

    camera = Camera(Vec3f{0, 0, 20}, Vec3f{0, 0, -1}, Vec3f{0, 1, 0});

    // SETUP SHADERS, BUFFERS, VAOs

    generateIDs();
    setupVAO();
    loadQuad2GeometryToGPU();
    loadQuad3GeometryToGPU();
    loadQuad4GeometryToGPU();
    loadQuad5GeometryToGPU();
    loadQuad6GeometryToGPU();
    loadQuad7GeometryToGPU();
    loadQuadGeometryToGPU();
    loadLineGeometryToGPU();
    loadLine2GeometryToGPU();
    loadQuad8GeometryToGPU();
    loadQuad9GeometryToGPU();
    loadQuad10GeometryToGPU();
    loadQuad11GeometryToGPU();
    loadQuad12GeometryToGPU();
    loadQuad13GeometryToGPU();
    loadQuad14GeometryToGPU();
    loadQuad15GeometryToGPU();
    loadQuad16GeometryToGPU();
    loadQuad17GeometryToGPU();
    loadQuad18GeometryToGPU();
    loadQuad19GeometryToGPU();
    loadQuad20GeometryToGPU();
    loadQuad21GeometryToGPU();
    loadQuad22GeometryToGPU();
    loadQuad23GeometryToGPU();
    loadQuad24GeometryToGPU();
    loadQuad25GeometryToGPU();

    loadModelViewMatrix();
    reloadProjectionMatrix();
    setupModelViewProjectionTransform();
    reloadMVPUniform();
}

int main(int argc, char **argv)
{
    GLFWwindow *window;

    if (!glfwInit())
    {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window =
        glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "CSE414 Project 1", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glfwSetWindowSizeCallback(window, windowSetSizeFunc);
    glfwSetFramebufferSizeCallback(window, windowSetFramebufferSizeFunc);
    glfwSetKeyCallback(window, windowKeyFunc);
    glfwSetCursorPosCallback(window, windowMouseMotionFunc);
    glfwSetMouseButtonCallback(window, windowMouseButtonFunc);

    glfwGetFramebufferSize(window, &WIN_WIDTH, &WIN_HEIGHT);

    // Initialize glad
    if (!gladLoadGL())
    {
        std::cerr << "Failed to initialise GLAD" << std::endl;
        return -1;
    }

    std::cout << "GL Version: :" << glGetString(GL_VERSION) << std::endl;
    std::cout << GL_ERROR() << std::endl;

    // Initialize all the geometry, and load it once to the GPU
    init(); // our own initialize stuff func

    float t = 0;
    float dt = 0.01;

    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
            !glfwWindowShouldClose(window))
    {

        if (g_play)
        {
            t += dt;
            animateQuad(t);
        }

        displayFunc();
        moveCamera();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // clean up after loop
    deleteIDs();

    return 0;
}

//==================== CALLBACK FUNCTIONS ====================//

void windowSetSizeFunc(GLFWwindow *window, int width, int height)
{
    WIN_WIDTH = width;
    WIN_HEIGHT = height;

    reloadProjectionMatrix();
    setupModelViewProjectionTransform();
    reloadMVPUniform();
}

void windowSetFramebufferSizeFunc(GLFWwindow *window, int width, int height)
{
    FB_WIDTH = width;
    FB_HEIGHT = height;

    glViewport(0, 0, FB_WIDTH, FB_HEIGHT);
}

void windowMouseButtonFunc(GLFWwindow *window, int button, int action,
                           int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            g_cursorLocked = GL_TRUE;
        }
        else
        {
            g_cursorLocked = GL_FALSE;
        }
    }
}

void windowMouseMotionFunc(GLFWwindow *window, double x, double y)
{
    if (g_cursorLocked)
    {
        float deltaX = (x - g_cursorX) * 0.01;
        float deltaY = (y - g_cursorY) * 0.01;
        camera.rotateAroundFocus(deltaX, deltaY);

        reloadViewMatrix();
        setupModelViewProjectionTransform();
        reloadMVPUniform();
    }

    g_cursorX = x;
    g_cursorY = y;
}

void windowKeyFunc(GLFWwindow *window, int key, int scancode, int action,
                   int mods)
{
    bool set = action != GLFW_RELEASE && GLFW_REPEAT;
    switch (key)
    {
    case GLFW_KEY_ESCAPE:
        glfwSetWindowShouldClose(window, GL_TRUE);
        break;
    case GLFW_KEY_W:
        g_moveBackForward = set ? 1 : 0;
        break;
    case GLFW_KEY_S:
        g_moveBackForward = set ? -1 : 0;
        break;
    case GLFW_KEY_A:
        g_moveLeftRight = set ? 1 : 0;
        break;
    case GLFW_KEY_D:
        g_moveLeftRight = set ? -1 : 0;
        break;
    case GLFW_KEY_Q:
        g_moveUpDown = set ? -1 : 0;
        break;
    case GLFW_KEY_E:
        g_moveUpDown = set ? 1 : 0;
        break;
    case GLFW_KEY_UP:
        g_rotateUpDown = set ? -1 : 0;
        break;
    case GLFW_KEY_DOWN:
        g_rotateUpDown = set ? 1 : 0;
        break;
    case GLFW_KEY_LEFT:
        if (mods == GLFW_MOD_SHIFT)
            g_rotateRoll = set ? -1 : 0;
        else
            g_rotateLeftRight = set ? 1 : 0;
        break;
    case GLFW_KEY_RIGHT:
        if (mods == GLFW_MOD_SHIFT)
            g_rotateRoll = set ? 1 : 0;
        else
            g_rotateLeftRight = set ? -1 : 0;
        break;
    case GLFW_KEY_SPACE:
        g_play = set ? !g_play : g_play;
        break;
    case GLFW_KEY_LEFT_BRACKET:
        if (mods == GLFW_MOD_SHIFT)
        {
            g_rotationSpeed *= 0.5;
        }
        else
        {
            g_panningSpeed *= 0.5;
        }
        break;
    case GLFW_KEY_RIGHT_BRACKET:
        if (mods == GLFW_MOD_SHIFT)
        {
            g_rotationSpeed *= 1.5;
        }
        else
        {
            g_panningSpeed *= 1.5;
        }
        break;
    default:
        break;
    }
}

//==================== OPENGL HELPER FUNCTIONS ====================//

void moveCamera()
{
    Vec3f dir;

    if (g_moveBackForward)
    {
        dir += Vec3f(0, 0, g_moveBackForward * g_panningSpeed);
    }
    if (g_moveLeftRight)
    {
        dir += Vec3f(g_moveLeftRight * g_panningSpeed, 0, 0);
    }
    if (g_moveUpDown)
    {
        dir += Vec3f(0, g_moveUpDown * g_panningSpeed, 0);
    }

    if (g_rotateUpDown)
    {
        camera.rotateUpDown(g_rotateUpDown * g_rotationSpeed);
    }
    if (g_rotateLeftRight)
    {
        camera.rotateLeftRight(g_rotateLeftRight * g_rotationSpeed);
    }
    if (g_rotateRoll)
    {
        camera.rotateRoll(g_rotateRoll * g_rotationSpeed);
    }

    if (g_moveUpDown || g_moveLeftRight || g_moveBackForward ||
            g_rotateLeftRight || g_rotateUpDown || g_rotateRoll)
    {
        camera.move(dir);
        reloadViewMatrix();
        setupModelViewProjectionTransform();
        reloadMVPUniform();
    }
}

std::string GL_ERROR()
{
    GLenum code = glGetError();

    switch (code)
    {
    case GL_NO_ERROR:
        return "GL_NO_ERROR";
    case GL_INVALID_ENUM:
        return "GL_INVALID_ENUM";
    case GL_INVALID_VALUE:
        return "GL_INVALID_VALUE";
    case GL_INVALID_OPERATION:
        return "GL_INVALID_OPERATION";
    case GL_INVALID_FRAMEBUFFER_OPERATION:
        return "GL_INVALID_FRAMEBUFFER_OPERATION";
    case GL_OUT_OF_MEMORY:
        return "GL_OUT_OF_MEMORY";
    default:
        return "Non Valid Error Code";
    }
}
