
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "basic_camera.h"
#include "directionalLight.h"
#include "pointLight.h"
#include "spotLight.h"
#include "BezierCurve.h"
#include "BezierCurveArch.h"
#include "Hexa.h"

#include "stb_image.h"

#include <iostream>
#include <stdlib.h>
#include<windows.h>  

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

void Floor(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color);
//fuctions prototypes
void load_texture(unsigned int& texture, string image_name, GLenum format);//texture loading function
//draw function
void Field(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);
void MainBase(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);
void FBsideWalk(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture1, unsigned int texture2);
void LRsideWalk(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture1, unsigned int texture2);
void MainMosjidBase(unsigned int VAO1, unsigned int VAO2, unsigned int VAO3, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture1, unsigned int texture2 , unsigned int texture3);
void Mosjid1stFloor(unsigned int VAO1, unsigned int VAO2, unsigned int VAO3, unsigned int VAO14, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);
void Mosjid2ndFloor(unsigned int VAO1, unsigned int VAO2, unsigned int VAO3, unsigned int VAO14, unsigned int VAO220, unsigned int VAO38, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);
void Ojubase(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);
void OjuKhana(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);
void Toilet(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);
void MainGate(unsigned int VAO1, unsigned int VAO2, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);
void Frontwing(unsigned int VAO1, unsigned int VAO2, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);
void Sidewing(unsigned int VAO1, unsigned int VAO2, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);
void MidGate(unsigned int VAO1, unsigned int VAO1020, unsigned int VAO16, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);
void StairTower1(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);
void StairTower2(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);

//-----------------------------
void HorizontalWall(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift,  float len, float ht, float lbx, float lby, float lbz, unsigned int texture);
void VerticalWall(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, float len, float ht, float lbx, float lby, float lbz, unsigned int texture);
void GenFloor(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, float len, float width, float lbx, float lby, float lbz, unsigned int texture);
void Box(unsigned int VAO1, unsigned int VAO2, Shader ourShader, float x_shift, float y_shift, float z_shift, float len, float width, float ht, float lbx, float lby, float lbz, unsigned int texture);
void FlatBox(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, float len, float width, float ht, float lbx, float lby, float lbz, unsigned int texture);
void HoloBox(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, float len, float width, float ht, float lbx, float lby, float lbz, unsigned int texture);
void FrontArchGen(unsigned int VAO, BezierCurveArch Main_Arch, BezierCurveArch Sub_Arch, BezierCurve Round_Piller, BezierCurve Piller_Border, Shader ourShader, float x_shift, float y_shift, float z_shift);
void MidArchGen(unsigned int VAO, BezierCurveArch Main_Arch, BezierCurveArch Sub_Arch, BezierCurve Round_Piller, BezierCurve Piller_Border, Shader ourShader, float x_shift, float y_shift, float z_shift);
void SideArchGen(unsigned int VAO, BezierCurveArch Main_Arch, BezierCurveArch Sub_Arch, BezierCurve Round_Piller, BezierCurve Piller_Border, Shader ourShader, float x_shift, float y_shift, float z_shift);
void MinarGen(unsigned int VAO, BezierCurve Round_piller, BezierCurve circle, BezierCurve spike, BezierCurve border, Hexa Piller_Stand, Shader ourShader, float x_shift, float y_shift, float z_shift);
//Component
void Fan_and_switch(unsigned int VAO, BezierCurve Fan_Bati, BezierCurve Fan_Blade, BezierCurve Fan_Tube, Shader ourShader, float x_shift, float y_shift, float z_shift);
void Main_Arch_Horizontal(unsigned int VAO, BezierCurveArch Main_Arch, BezierCurveArch Sub_Arch, BezierCurve Round_Piller, BezierCurve Piller_Border, Shader ourShader, float x_shift, float y_shift, float z_shift);
void Common_Arch_Horizontal(unsigned int VAO, BezierCurveArch Main_Arch, BezierCurveArch Sub_Arch, BezierCurve Round_Piller, BezierCurve Piller_Border, Shader ourShader, float x_shift, float y_shift, float z_shift);
void Common_Arch_Vertical(unsigned int VAO, BezierCurveArch Main_Arch, BezierCurveArch Sub_Arch, BezierCurve Round_Piller, BezierCurve Piller_Border, Shader ourShader, float x_shift, float y_shift, float z_shift);
void small_tomb(unsigned int VAO,BezierCurve circle, BezierCurve spike, Shader ourShader, float x_shift, float y_shift, float z_shift);
void mid_tomb(unsigned int VAO, BezierCurve circle1, BezierCurve spike, Shader ourShader, float x_shift, float y_shift, float z_shift);
void Big_tomb(unsigned int VAO,  BezierCurve circle2, BezierCurve spike, Shader ourShader, float x_shift, float y_shift, float z_shift);



// settings
const unsigned int SCR_WIDTH = 1500;
const unsigned int SCR_HEIGHT = 800;

// modelling transform
float rotateAngle_X = 0.0;
float rotateAngle_Y = 0.0;
float rotateAngle_Z = 0.0;
float rotateAxis_X = 0.0;
float rotateAxis_Y = 0.0;
float rotateAxis_Z = 0.0;
float translate_X = 0.0;
float translate_Y = 0.0;
float translate_Z = 0.0;
float scale_X = 1.0;
float scale_Y = 1.0;
float scale_Z = 1.0;

//FAN rotate
//1st floor
bool isRotate1 = false;
float fanspeed1 = 0.0f;
float rotateAxis_Y_Fan1 = 0.0;
bool Fan1_ready = true;
//2nd floor
bool isRotate2 = false;
float fanspeed2 = 0.0f;
float rotateAxis_Y_Fan2 = 0.0;
bool Fan2_ready = true;

//LIFT
bool isLift = false;
bool lift_ready = true;
float lift_speed = 0.05;
float translate_Y_Lift = 0.0;
float translate_X_Lift = 0.0;
float translate_Z_Lift = 0.0;

//water counter
int wcnt = 0;

// camera
//Camera camera(glm::vec3(18.0f, 2.5f, -10.0f));//camera position
//Camera camera(glm::vec3(0.0f, 1.0f, 1.0f));//camera position
//Camera camera(glm::vec3(37.5f, 4.0f, -43.0f));//camera position
Camera camera(glm::vec3(37.5f, 10.0f, -13.0f));//camera position
//Camera camera(glm::vec3(18.0f, 2.5f, -40.0f));//camera position
//Camera camera(glm::vec3(61.0f, 2.5f, -19.5f));//camera position
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float eyeX = 0.0, eyeY = 0.0, eyeZ = 3.0;
float lookAtX = 0.0, lookAtY = 0.0, lookAtZ = 0.0;
glm::vec3 V = glm::vec3(0.0f, 1.0f, 0.0f);
BasicCamera basic_camera(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, V);

// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;


// Light initialization
glm::vec3 lightPositions[] = {
        glm::vec3(0.95f, 0.7f, -2.7f),         //Directional Light
        glm::vec3(10.1f, 1.28f, 14.37f),
        glm::vec3(6.2f, 1.35f, 7.98f)

};

glm::vec3 lightDirections[] = {
    glm::vec3(0.4f, -0.2f, -1.0f)
};

DirectionalLight directionalLight(lightPositions[0], glm::vec4(0.4f, 0.4f, 0.4f, 1.0f), glm::vec4(0.9f, 0.9f, 0.9f, 1.0f), glm::vec4(0.2f, 0.2f, 0.2f, 0.2f), 1);
SpotLight spotLight(lightPositions[2], lightDirections[0], 8.5f, 15.5f, glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.0014f, 0.000007f, 1);
PointLight pointLight(lightPositions[1], glm::vec4(0.2f, 0.2f, 0.2f, 1.0f), glm::vec4(0.9f, 0.9f, 0.9f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, 0.09f, 0.032f, 1);

//texture
//style1-- 1X1//used
float ext = 0.0f;
float TXmin = 0.0f;
float TXmax = 1.0f+ext;
float TYmin = 0.0f;
float TYmax = 1.0f+ext;
//style2--- 1X2//used
float ext2 = 1.0f;
float TXmin2 = 0.0f;
float TXmax2 = 1.0f + ext2;
float TYmin2 = 0.0f;
float TYmax2 = 1.0f + 0.0f;
//style3-- 1X3
float ext3 = 2.0f;
float TXmin3 = 0.0f;
float TXmax3 = 1.0f + ext3;
float TYmin3 = 0.0f;
float TYmax3 = 1.0f + 0.0f;
//style3-- 1X4
float ext14 = 3.0f;
float TXmin14 = 0.0f;
float TXmax14 = 1.0f + 3.0;
float TYmin14 = 0.0f;
float TYmax14 = 1.0f + 0.0f;
//style3-- 4X1
float ext41 = 3.0f;
float TXmin41 = 0.0f;
float TXmax41 = 1.0f + 0.0;
float TYmin41 = 0.0f;
float TYmax41 = 1.0f + 3.0f;
//style3-- 1X6//used
float ext6 = 6.0f;
float TXmin6 = 0.0f;
float TXmax6 = 1.0f + ext6;
float TYmin6 = 0.0f;
float TYmax6 = 1.0f + 0.0f;
//style3-- 10X1//used
float ext10 = 9.0f;
float TXmin10 = 0.0f;
float TXmax10 = 1.0f + 0.0;
float TYmin10 = 0.0f;
float TYmax10 = 1.0f + ext10;
//style4-- 7x20//used
float ext4 = 2.0f;
float TXmin4 = 0.0f;
float TXmax4 = 1.0f + 19.0;
float TYmin4 = 0.0f;
float TYmax4 = 1.0f + 6.0;

//style5-- 7x7used
float ext5 = 2.0f;
float TXmin5 = 0.0f;
float TXmax5 = 1.0f + 7.0;
float TYmin5 = 0.0f;
float TYmax5 = 1.0f + 7.0;

//style5-- 3x8used
float ext38 = 2.0f;
float TXmin38 = 0.0f;
float TXmax38 = 1.0f + 7.0;
float TYmin38 = 0.0f;
float TYmax38 = 1.0f + 2.0;

//style5-- 2x20used
float ext220 = 2.0f;
float TXmin220 = 0.0f;
float TXmax220 = 1.0f + 19.0;
float TYmin220 = 0.0f;
float TYmax220 = 1.0f + 1.0;

//style5-- 5x10used
float TXmin1020 = 0.0f;
float TXmax1020 = 1.0f + 9.0;
float TYmin1020 = 0.0f;
float TYmax1020 = 1.0f + 4.0;


bool lightingOn = true;
float ambientOn = 1.0;
float diffuseOn = 1.0;
float specularOn = 1.0;
bool dark = false;

float directionalLightOn = 1.0;
float pointLightOn = 0.0;
float spotLightOn = 0.0;

//Texture variables
unsigned int texture0, texture1, texture2, texture3, texture4, texture5, texture6, texture7, texture8, texture9, texture10, texture11, texture12, texture13, frontwall1,frontwall2,sidewall1,sidewall2,blankwall;
unsigned int mehrab, mehrabside;
unsigned int water[10];

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Mosjid - Rashedul Ghani", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");//for other objects
    Shader lightCubeShader("lightVertexShader.vs", "lightFragmentShader.fs");//only for light cubes

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------


    //cube 1X1---------------------------------------------------------------------------------------------
    float cube_vertices[] = {
        //    pos        //     normals      // texture cords
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax, TYmin,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin, TYmin,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin, TYmax,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax, TYmax,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax, TYmin,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax, TYmax,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin, TYmin,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin, TYmax,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin, TYmin,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax, TYmin,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax, TYmax,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin, TYmax,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax, TYmin,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax, TYmax,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin, TYmax,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin, TYmin,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmax, TYmin,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmax, TYmax,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmin, TYmax,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmin, TYmin,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmin, TYmin,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmax, TYmin,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmax, TYmax,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmin, TYmax
    };
    unsigned int cube_indices[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    //cube 1
    unsigned int cubeVAO, cubeVBO, cubeEBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glGenBuffers(1, &cubeEBO);

    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

    //ekhon total 8 ta value thakbe
    // 1st 3 ta vertex point, 2nd 3 ta normal vector, 3rd 2 ta texture cords
    // stride parameter 6 theke ekhon 8 hoye jabe
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

    //texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)24);
    glEnableVertexAttribArray(2);


    //cube 1X2-----------------------------------------------------------------------------

    float cube_vertices2[] = {
        //    pos        //     normals      // texture cords
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax2, TYmin2,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin2, TYmin2,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin2, TYmax2,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax2, TYmax2,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax2, TYmin2,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax2, TYmax2,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin2, TYmin2,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin2, TYmax2,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin2, TYmin2,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax2, TYmin2,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax2, TYmax2,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin2, TYmax2,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax2, TYmin2,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax2, TYmax2,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin2, TYmax2,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin2, TYmin2,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmax2, TYmin2,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmax2, TYmax2,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmin2, TYmax2,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmin2, TYmin2,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmin2, TYmin2,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmax2, TYmin2,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmax2, TYmax2,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmin2, TYmax2
    };
    unsigned int cube_indices2[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    //cube2 
    unsigned int cubeVAO2, cubeVBO2, cubeEBO2;
    glGenVertexArrays(1, &cubeVAO2);
    glGenBuffers(1, &cubeVBO2);
    glGenBuffers(1, &cubeEBO2);

    glBindVertexArray(cubeVAO2);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices2), cube_vertices2, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices2), cube_indices2, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);
    //texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)24);
    glEnableVertexAttribArray(2);


    //cube 1X3-----------------------------------------------------------------------------

    float cube_vertices3[] = {
        //    pos        //     normals      // texture cords
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax3, TYmin3,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin3, TYmin3,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin3, TYmax3,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax3, TYmax3,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax3, TYmin3,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax3, TYmax3,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin3, TYmin3,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin3, TYmax3,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin3, TYmin3,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax3, TYmin3,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax3, TYmax3,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin3, TYmax3,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax3, TYmin3,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax3, TYmax3,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin3, TYmax3,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin3, TYmin3,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmax3, TYmin3,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmax3, TYmax3,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmin3, TYmax3,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmin3, TYmin3,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmin3, TYmin3,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmax3, TYmin3,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmax3, TYmax3,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmin3, TYmax3
    };
    unsigned int cube_indices3[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    //cube3 
    unsigned int cubeVAO3, cubeVBO3, cubeEBO3;
    glGenVertexArrays(1, &cubeVAO3);
    glGenBuffers(1, &cubeVBO3);
    glGenBuffers(1, &cubeEBO3);

    glBindVertexArray(cubeVAO3);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO3);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices3), cube_vertices3, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO3);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices3), cube_indices3, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);
    //texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)24);
    glEnableVertexAttribArray(2);

    //1x4
    float cube_vertices14[] = {
        //    pos        //     normals      // texture cords
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax14, TYmin14,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin14, TYmin14,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin14, TYmax14,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax14, TYmax14,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax14, TYmin14,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax14, TYmax14,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin14, TYmin14,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin14, TYmax14,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin14, TYmin14,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax14, TYmin14,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax14, TYmax14,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin14, TYmax14,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax14, TYmin14,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax14, TYmax14,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin14, TYmax14,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin14, TYmin14,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmax14, TYmin14,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmax14, TYmax14,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmin14, TYmax14,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmin14, TYmin14,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmin14, TYmin14,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmax14, TYmin14,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmax14, TYmax14,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmin14, TYmax14
    };
    unsigned int cube_indices14[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    //cube3 
    unsigned int cubeVAO14, cubeVBO14, cubeEBO14;
    glGenVertexArrays(1, &cubeVAO14);
    glGenBuffers(1, &cubeVBO14);
    glGenBuffers(1, &cubeEBO14);

    glBindVertexArray(cubeVAO14);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO14);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices14), cube_vertices14, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO14);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices14), cube_indices14, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);
    //texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)24);
    glEnableVertexAttribArray(2);


    ////1x4
    //float cube_vertices14[] = {
    //    //    pos        //     normals      // texture cords
    //    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax14, TYmin14,
    //    1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin14, TYmin14,
    //    1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin14, TYmax14,
    //    0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax14, TYmax14,

    //    1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax14, TYmin14,
    //    1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax14, TYmax14,
    //    1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin14, TYmin14,
    //    1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin14, TYmax14,

    //    0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin14, TYmin14,
    //    1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax14, TYmin14,
    //    1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax14, TYmax14,
    //    0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin14, TYmax14,

    //    0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax14, TYmin14,
    //    0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax14, TYmax14,
    //    0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin14, TYmax14,
    //    0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin14, TYmin14,

    //    1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmax14, TYmin14,
    //    1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmax14, TYmax14,
    //    0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmin14, TYmax14,
    //    0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmin14, TYmin14,

    //    0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmin14, TYmin14,
    //    1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmax14, TYmin14,
    //    1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmax14, TYmax14,
    //    0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmin14, TYmax14
    //};
    //unsigned int cube_indices14[] = {
    //    0, 3, 2,
    //    2, 1, 0,

    //    4, 5, 7,
    //    7, 6, 4,

    //    8, 9, 10,
    //    10, 11, 8,

    //    12, 13, 14,
    //    14, 15, 12,

    //    16, 17, 18,
    //    18, 19, 16,

    //    20, 21, 22,
    //    22, 23, 20
    //};

    ////cube3 
    //unsigned int cubeVAO14, cubeVBO14, cubeEBO14;
    //glGenVertexArrays(1, &cubeVAO14);
    //glGenBuffers(1, &cubeVBO14);
    //glGenBuffers(1, &cubeEBO14);

    //glBindVertexArray(cubeVAO14);

    //glBindBuffer(GL_ARRAY_BUFFER, cubeVBO14);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices14), cube_vertices14, GL_STATIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO14);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices14), cube_indices14, GL_STATIC_DRAW);
    //// position attribute
    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    //glEnableVertexAttribArray(0);
    ////vertex normal attribute
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)12);
    //glEnableVertexAttribArray(1);
    ////texture attribute
    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)24);
    //glEnableVertexAttribArray(2);


    //cube 1X6-----------------------------------------------------------------------------

    float cube_vertices16[] = {
        //    pos        //     normals      // texture cords
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax6, TYmin6,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin6, TYmin6,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin6, TYmax6,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax6, TYmax6,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax6, TYmin6,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax6, TYmax6,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin6, TYmin6,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin6, TYmax6,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin6, TYmin6,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax6, TYmin6,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax6, TYmax6,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin6, TYmax6,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax6, TYmin6,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax6, TYmax6,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin6, TYmax6,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin6, TYmin6,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmax6, TYmin6,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmax6, TYmax6,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmin6, TYmax6,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmin6, TYmin6,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmin6, TYmin6,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmax6, TYmin6,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmax6, TYmax6,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmin6, TYmax6
    };
    unsigned int cube_indices16[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    //cube2 
    unsigned int cubeVAO16, cubeVBO16, cubeEBO16;
    glGenVertexArrays(1, &cubeVAO16);
    glGenBuffers(1, &cubeVBO16);
    glGenBuffers(1, &cubeEBO16);

    glBindVertexArray(cubeVAO16);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO16);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices16), cube_vertices16, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO16);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices16), cube_indices16, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);
    //texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)24);
    glEnableVertexAttribArray(2);


    //cube 1X6-----------------------------------------------------------------------------

    float cube_vertices101[] = {
        //    pos        //     normals      // texture cords
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax10, TYmin10,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin10, TYmin10,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin10, TYmax10,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax10, TYmax10,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax10, TYmin10,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax10, TYmax10,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin10, TYmin10,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin10, TYmax10,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin10, TYmin10,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax10, TYmin10,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax10, TYmax10,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin10, TYmax10,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax10, TYmin10,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax10, TYmax10,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin10, TYmax10,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin10, TYmin10,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmax10, TYmin10,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmax10, TYmax10,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmin10, TYmax10,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmin10, TYmin10,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmin10, TYmin10,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmax10, TYmin10,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmax10, TYmax10,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmin10, TYmax10
    };
    unsigned int cube_indices101[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    //cube2 
    unsigned int cubeVAO101, cubeVBO101, cubeEBO101;
    glGenVertexArrays(1, &cubeVAO101);
    glGenBuffers(1, &cubeVBO101);
    glGenBuffers(1, &cubeEBO101);

    glBindVertexArray(cubeVAO101);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO101);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices101), cube_vertices101, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO101);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices101), cube_indices101, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);
    //texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)24);
    glEnableVertexAttribArray(2);


    //cube 3X8-----------------------------------------------------------------------------

    float cube_vertices38[] = {
        //    pos        //     normals      // texture cords
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax38, TYmin38,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin38, TYmin38,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin38, TYmax38,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax38, TYmax38,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax38, TYmin38,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax38, TYmax38,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin38, TYmin38,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin38, TYmax38,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin38, TYmin38,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax38, TYmin38,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax38, TYmax38,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin38, TYmax38,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax38, TYmin38,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax38, TYmax38,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin38, TYmax38,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin38, TYmin38,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmax38, TYmin38,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmax38, TYmax38,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmin38, TYmax38,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmin38, TYmin38,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmin38, TYmin38,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmax38, TYmin38,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmax38, TYmax38,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmin38, TYmax38
    };
    unsigned int cube_indices38[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    //cube2 
    unsigned int cubeVAO38, cubeVBO38, cubeEBO38;
    glGenVertexArrays(1, &cubeVAO38);
    glGenBuffers(1, &cubeVBO38);
    glGenBuffers(1, &cubeEBO38);

    glBindVertexArray(cubeVAO38);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO38);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices38), cube_vertices38, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO38);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices38), cube_indices38, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);
    //texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)24);
    glEnableVertexAttribArray(2);


    //cube 2X20-----------------------------------------------------------------------------

    float cube_vertices220[] = {
        //    pos        //     normals      // texture cords
 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax220, TYmin220,
 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin220, TYmin220,
 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin220, TYmax220,
 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax220, TYmax220,

 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax220, TYmin220,
 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax220, TYmax220,
 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin220, TYmin220,
 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin220, TYmax220,

 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin220, TYmin220,
 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax220, TYmin220,
 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax220, TYmax220,
 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin220, TYmax220,

 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax220, TYmin220,
 0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax220, TYmax220,
 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin220, TYmax220,
 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin220, TYmin220,

 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmax220, TYmin220,
 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmax220, TYmax220,
 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmin220, TYmax220,
 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmin220, TYmin220,

 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmin220, TYmin220,
 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmax220, TYmin220,
 1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmax220, TYmax220,
 0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmin220, TYmax220
    };
    unsigned int cube_indices220[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    //cube2 
    unsigned int cubeVAO220, cubeVBO220, cubeEBO220;
    glGenVertexArrays(1, &cubeVAO220);
    glGenBuffers(1, &cubeVBO220);
    glGenBuffers(1, &cubeEBO220);

    glBindVertexArray(cubeVAO220);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO220);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices220), cube_vertices220, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO220);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices220), cube_indices220, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);
    //texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)24);
    glEnableVertexAttribArray(2);

    //cube 7X20-----------------------------------------------------------------------------

    float cube_vertices4[] = {
        //    pos        //     normals      // texture cords
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax4, TYmin4,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin4, TYmin4,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin4, TYmax4,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax4, TYmax4,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax4, TYmin4,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax4, TYmax4,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin4, TYmin4,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin4, TYmax4,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin4, TYmin4,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax4, TYmin4,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax4, TYmax4,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin4, TYmax4,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax4, TYmin4,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax4, TYmax4,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin4, TYmax4,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin4, TYmin4,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmax4, TYmin4,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmax4, TYmax4,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmin4, TYmax4,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmin4, TYmin4,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmin4, TYmin4,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmax4, TYmin4,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmax4, TYmax4,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmin4, TYmax4
    };
    unsigned int cube_indices4[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    //cubex 7x20
    unsigned int cubeVAO4, cubeVBO4, cubeEBO4;
    glGenVertexArrays(1, &cubeVAO4);
    glGenBuffers(1, &cubeVBO4);
    glGenBuffers(1, &cubeEBO4);

    glBindVertexArray(cubeVAO4);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO4);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices4), cube_vertices4, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO4);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices4), cube_indices4, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);
    //texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)24);
    glEnableVertexAttribArray(2);


    //cube 5X10-----------------------------------------------------------------------------

    float cube_vertices1020[] = {
        //    pos        //     normals      // texture cords
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax1020, TYmin1020,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin1020, TYmin1020,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin1020, TYmax1020,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax1020, TYmax1020,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax1020, TYmin1020,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax1020, TYmax1020,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin1020, TYmin1020,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin1020, TYmax1020,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin1020, TYmin1020,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax1020, TYmin1020,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax1020, TYmax1020,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin1020, TYmax1020,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax1020, TYmin1020,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax1020, TYmax1020,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin1020, TYmax1020,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin1020, TYmin1020,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmax1020, TYmin1020,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmax1020, TYmax1020,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmin1020, TYmax1020,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmin1020, TYmin1020,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmin1020, TYmin1020,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmax1020, TYmin1020,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmax1020, TYmax1020,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmin1020, TYmax1020
    };
    unsigned int cube_indices1020[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    //cubex 5x10
    unsigned int cubeVAO1020, cubeVBO1020, cubeEBO1020;
    glGenVertexArrays(1, &cubeVAO1020);
    glGenBuffers(1, &cubeVBO1020);
    glGenBuffers(1, &cubeEBO1020);

    glBindVertexArray(cubeVAO1020);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO1020);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices1020), cube_vertices1020, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO1020);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices1020), cube_indices1020, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);
    //texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)24);
    glEnableVertexAttribArray(2);



    //cube 7X7-----------------------------------------------------------------------------
    //0.5f
    //1.0f
    float cube_vertices5[] = {
        //    pos        //     normals      // texture cords
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax5, TYmin5,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin5, TYmin5,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmin5, TYmax5,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, TXmax5, TYmax5,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax5, TYmin5,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax5, TYmax5,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin5, TYmin5,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, TXmin5, TYmax5,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin5, TYmin5,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax5, TYmin5,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmax5, TYmax5,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, TXmin5, TYmax5,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax5, TYmin5,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, TXmax5, TYmax5,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin5, TYmax5,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin5, TYmin5,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmax5, TYmin5,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmax5, TYmax5,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, TXmin5, TYmax5,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, TXmin5, TYmin5,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmin5, TYmin5,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmax5, TYmin5,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmax5, TYmax5,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, TXmin5, TYmax5
    };
    unsigned int cube_indices5[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    //cubex 7x7
    unsigned int cubeVAO77, cubeVBO77, cubeEBO77;
    glGenVertexArrays(1, &cubeVAO77);
    glGenBuffers(1, &cubeVBO77);
    glGenBuffers(1, &cubeEBO77);

    glBindVertexArray(cubeVAO77);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO77);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices5), cube_vertices5, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO77);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices5), cube_indices5, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);
    //texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)24);
    glEnableVertexAttribArray(2);


    //HEXAGON------------------------------------------------------------------------------
    float hexa_vertices[] = {
        //    pos        //     normals      // texture cords
        -0.5f, 0.0f, -0.866f, 0.0f, 0.0f, -1.0f, TXmax, TYmin,
        0.5f, 0.0f, -0.866f, 0.0f, 0.0f, -1.0f, TXmin, TYmin,
        0.5f, 0.5f, -0.866f, 0.0f, 0.0f, -1.0f, TXmin, TYmax,
        -0.5f, 0.5f, -0.866f, 0.0f, 0.0f, -1.0f, TXmax, TYmax,

        0.5f, 0.0f, -0.866f, 1.0f, 0.0f, -1.732f, TXmax, TYmin,
        0.5f, 0.5f, -0.866f, 1.0f, 0.0f, -1.732f, TXmax, TYmax,
        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, -1.732f, TXmin, TYmin,
        1.0f, 0.5f, 0.0f, 1.0f, 0.0f, -1.732f, TXmin, TYmax,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.732f, TXmax, TYmin,
        1.0f, 0.5f, 0.0f, 1.0f, 0.0f, 1.732f, TXmax, TYmax,
        0.5f, 0.0f, 0.866f, 1.0f, 0.0f, 1.732f, TXmin, TYmin,
        0.5f, 0.5f, 0.866f, 1.0f, 0.0f, 1.732f, TXmin, TYmax,

        //0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax, TYmin,
        //0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, TXmax, TYmax,
        //0.5f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f, TXmin, TYmin,
        //0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, TXmin, TYmax,

        -0.5f, 0.0f, 0.866f, 0.0f, 0.0f, 1.0f, TXmin, TYmin,
        0.5f, 0.0f, 0.866f, 0.0f, 0.0f, 1.0f, TXmax, TYmin,
        0.5f, 0.5f, 0.866f, 0.0f, 0.0f, 1.0f, TXmax, TYmax,
        -0.5f, 0.5f, 0.866f, 0.0f, 0.0f, 1.0f, TXmin, TYmax,

        -0.5f, 0.0f, 0.866f, -1.0f, 0.0f, 1.732f, TXmax, TYmin,
       -0.5f, 0.5f, 0.866f, -1.0f, 0.0f, 1.732f, TXmax, TYmax,
        -1.0f, 0.5f, 0.0f, -1.0f, 0.0f, 1.732f, TXmin, TYmax,
        -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.732f, TXmin, TYmin,

       -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, -1.732f, TXmax, TYmin,
       -1.0f, 0.5f, 0.0f, -1.0f, 0.0f, -1.732f, TXmax, TYmax,
        -0.5f, 0.5f, -0.866f, -1.0f, 0.0f, -1.732f, TXmin, TYmax,
        -0.5f, 0.0f, -0.866f, -1.0f, 0.0f, -1.732f, TXmin, TYmin,

        //0.0f, 0.0f, 0.5f, -1.0f, 0.0f, 0.0f, TXmax, TYmin,
        //0.0f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, TXmax, TYmax,
        //0.0f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin, TYmax,
        //0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, TXmin, TYmin,

        0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, TXmax, TYmin,
        0.5f, 0.5f, 0.866f, 0.0f, 1.0f, 0.0f, TXmax, TYmax,
        -0.5f, 0.5f, 0.866f, 0.0f, 1.0f, 0.0f, TXmin, TYmax,
        -1.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, TXmin, TYmin,

        0.5f, 0.5f, -0.866f, 0.0f, 1.0f, 0.0f, TXmax, TYmin,
        1.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, TXmax, TYmax,
        0.5f, 0.5f, 0.866f, 0.0f, 1.0f, 0.0f, TXmin, TYmax,
        0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, TXmin, TYmin,

        -1.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, TXmax, TYmin,
        -0.5f, 0.5f, -0.866f, 0.0f, 1.0f, 0.0f, TXmax, TYmax,
        0.5f, 0.5f, -0.866f, 0.0f, 1.0f, 0.0f, TXmin, TYmax,
        0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, TXmin, TYmin,

        //0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, TXmax, TYmin,
        //0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, TXmax, TYmax,
        //0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, TXmin, TYmax,
        //0.0f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, TXmin, TYmin,

        0.5f, 0.0f, -0.866f, 0.0f, -1.0f, 0.0f, TXmin, TYmin,
        -0.5f, 0.0f, -0.866f, 0.0f, -1.0f, 0.0f, TXmax, TYmin,
        -1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmax, TYmax,
        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmin, TYmax,

        0.5f, 0.0f, 0.866f, 0.0f, -1.0f, 0.0f, TXmin, TYmin,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmax, TYmin,
        0.5f, 0.0f, -0.866f, 0.0f, -1.0f, 0.0f, TXmax, TYmax,
        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmin, TYmax,

        -0.5f, 0.0f, 0.866f, 0.0f, -1.0f, 0.0f, TXmin, TYmin,
        0.5f, 0.0f, 0.866f, 0.0f, -1.0f, 0.0f, TXmax, TYmin,
        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmax, TYmax,
        -1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmin, TYmax,

        //0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmin, TYmin,
        //0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, TXmax, TYmin,
        //0.5f, 0.0f, 0.5f, 0.0f, -1.0f, 0.0f, TXmax, TYmax,
        //0.0f, 0.0f, 0.5f, 0.0f, -1.0f, 0.0f, TXmin, TYmax
    };
    unsigned int hexa_indices[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 11,
        11, 10, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20,
        
        24, 25, 26,
        26, 27, 24,

        28, 29, 30,
        30, 31, 28,

        32, 33, 34,
        34, 35, 32,

        36, 37, 38,
        38, 39, 36,

        40, 41, 42,
        42, 43, 40,

        44, 45, 46,
        46, 47, 44

    };

    //hexa
    unsigned int hexaVAO, hexaVBO, hexaEBO;
    glGenVertexArrays(1, &hexaVAO);
    glGenBuffers(1, &hexaVBO);
    glGenBuffers(1, &hexaEBO);
    glBindVertexArray(hexaVAO);
    glBindBuffer(GL_ARRAY_BUFFER, hexaVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(hexa_vertices), hexa_vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, hexaEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(hexa_indices), hexa_indices, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);
    //texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)24);
    glEnableVertexAttribArray(2);




    //light's VAO
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);




    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //ourShader.use();


    //Texture loading
    //Texture 0
    glGenTextures(1, &texture0);
    glBindTexture(GL_TEXTURE_2D, texture0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("transparent.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        cout << "Failed to load texture 0" << endl;
    }
    stbi_image_free(data);

    //water
    load_texture(water[0], "water1.jpg", GL_RGB);//used
    load_texture(water[1], "water2.jpg", GL_RGB);//used
    load_texture(water[2], "water3.jpg", GL_RGB);//used
    load_texture(water[3], "water4.jpg", GL_RGB);//used
    load_texture(water[4], "water5.jpg", GL_RGB);//used
    load_texture(water[5], "water6.jpg", GL_RGB);//used
    load_texture(water[6], "water7.jpg", GL_RGB);//used
    load_texture(water[7], "water8.jpg", GL_RGB);//used
    load_texture(water[8], "water9.jpg", GL_RGB);//used
    load_texture(water[9], "water10.jpg", GL_RGB);//used



    load_texture(texture1, "ground_1k.jpg", GL_RGB);//used
    load_texture(texture2, "Piller_concrete_1.jpg", GL_RGB);//used
    load_texture(texture3, "golden.jpg", GL_RGB);//used


    load_texture(texture4, "Marble012_1K-JPG_Color.jpg", GL_RGB);//used
    load_texture(texture5, "balcony_tiles1.jpg", GL_RGB);//used
    load_texture(texture6, "Stripe_1.jpg", GL_RGB);//used
    load_texture(texture7, "Concrete007_1K-JPG_Color.jpg", GL_RGB);//used
    load_texture(texture8, "con07_1.jpg", GL_RGB);//used
    load_texture(texture9, "wall12.jpg", GL_RGB);
    load_texture(texture10, "ceilling_mid_870.jpg", GL_RGB);
    load_texture(texture11, "ceilling_mid_1000.jpg", GL_RGB);
    load_texture(texture12, "ceilling_mid_1282.jpg", GL_RGB);
    load_texture(texture13, "arch1.png", GL_RGBA);

    load_texture(frontwall1, "wallGG.jpg", GL_RGB);
    load_texture(frontwall2, "Blank_Wall_Pattern.jpg", GL_RGB);
    load_texture(sidewall1, "wallGG.jpg", GL_RGB);
    load_texture(sidewall2, "side_wall.jpg", GL_RGB);
    load_texture(blankwall, "square_wall.jpg", GL_RGB);
    load_texture(mehrab, "MehrabGG.jpg", GL_RGB);
    load_texture(mehrabside, "MehrabGGSide.jpg", GL_RGB);

    //Curves
    //Fan_bati
    GLfloat cp_Fan_Bati[] = {
    0.0, 0.476, 0.0,
    -0.64, 0.455, 0.0,
    -0.727, 0.305, 0.0,
    -0.64, 0.113, 0.0,
    0.0, 0.0, 0.0
    };
    BezierCurve Fan_Bati = BezierCurve(cp_Fan_Bati, 15, texture3);
    //Fan_Blade
    GLfloat cp_Fan_Blade[] = {
    0.0, 1.945, 0.0,
    -0.071, 1.93, 0.0,
    -0.1395, 1.9245, 0.0,
    -0.1834, 1.889, 0.0,
    -0.1958, 1.842, 0.0,
    -0.415, 0.264, 0.0,
    -0.425, 0.128, 0.0,
    -0.383, 0.0543, 0.0,
    0.0, 0.0, 0.0
    };
    BezierCurve Fan_Blade = BezierCurve(cp_Fan_Blade, 27, texture13);

    //FAN_TUBE
    GLfloat cp_Fan_Tube[] = {
    -0.1395, 1.9245, 0.0,
    -0.1395, 0.0, 0.0
    };
    BezierCurve Fan_Tube = BezierCurve(cp_Fan_Tube, 6, texture3);

    //Common Arch***************************************************
    //main arch
    //    GLfloat cp_Main_Arch[] = {
    //     -0.001, 1.01, 0.0,
    //    -0.29, 0.755, 0.0,
    //    -0.725, 0.74,0.0,
    //    -0.89, 0.415, 0.0,
    //    -0.71, 0.07, 0.0,
    //    -0.42, 0.0, 0.0
    //};
        GLfloat cp_Main_Arch[] = {
 -0.001, 1.01, 0.0,
-0.29, 0.755, 0.0,
-0.725, 0.74,0.0,
-0.89, 0.0, 0.0
//-0.71, 0.07, 0.0,
//-0.42, 0.0, 0.0
        };
        BezierCurveArch Main_Arch = BezierCurveArch(cp_Main_Arch, 4*3, texture4, 1.0);
     //sub arch
     GLfloat cp_Sub_Arch[] = {
-0.0001, 0.71, 0,
-0.4801, 0.64, 0,
-0.7451, 0.35, 0,
-0.7651, 0, 0
        };
        BezierCurveArch Sub_Arch = BezierCurveArch(cp_Sub_Arch, 4*3, texture13,1.0);
        //round piller
        GLfloat cp_Round_Piller[] = {
           -0.5,1.0,0.0,
           -0.5,0.0,0.0
        };
        BezierCurve Round_Piller = BezierCurve(cp_Round_Piller, 2*3, texture2);
        //piller_nicher_border
        GLfloat cp_Piller_Border[] = {
    -0.03, 0.43, 0,
    -0.31, 0.44, 0,
    -0.675, 0.435, 0,
    -0.74, 0.375, 0,
    -0.78, 0.105, 0,
    -0.72, 0.03, 0,
    -0.57, 0.015, 0,
    -0.35, 0, 0,
    -0.12, 0, 0
        };
        BezierCurve Piller_Border = BezierCurve(cp_Piller_Border, 9*3, texture2);

        ///MINAR
                //round piller
        GLfloat cp_circle[] = {
-0.0301, 1.645, 0,
-0.7301, 1.595, 0,
-1.0801, 1.35, 0,
-1.2701, 1.05, 0,
-1.3051, 0.715, 0,
-1.2701, 0.365, 0,
-1.1601, 0.165, 0,
-0.9301, 0.085, 0,
-0.6751, 0.04, 0,
-0.4101, 0, 0,
-0.1651, 0, 0,
-0.0001, 0, 0
        };
        BezierCurve circle = BezierCurve(cp_circle, 12 * 3, texture0);
        //piller_nicher_border
        GLfloat cp_spike[] = {
-0.0451, 1.745, 0,
-0.4651, 0.13, 0,
-0.3501, 0.01, 0,
-0.0001, 0, 0
        };
        BezierCurve spike = BezierCurve(cp_spike, 4 * 3, texture3);

        //2nd circle
        GLfloat cp_circle1[] = {
-0.0001, 1.645, 0,
-0.1901, 1.35, 0,
-0.6301, 1.26, 0,
-1.0101, 1.17, 0,
-1.3001, 0.855, 0,
-1.2701, 0.25, 0,
-0.8951, 0, 0,
        };
        BezierCurve circle1 = BezierCurve(cp_circle1, 7 * 3, texture0);

        //HEXA
        //round piller
        GLfloat cp_Round_Piller_Hexa[] = {
           -0.5,1.0,0.0,
           -0.5,0.0,0.0
        };
        Hexa Round_Piller_Hexa = Hexa(cp_Round_Piller_Hexa, 2 * 3, texture2);

    // render loop
    // -----------

    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // activate shader
        ourShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
        ourShader.setMat4("projection", projection);

        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("view", view);


        //Directional Light
        directionalLight.setUpLight(ourShader);
        if (!directionalLightOn)
            directionalLight.turnOff();
        if (!ambientOn)
            directionalLight.turnAmbientOff();
        if (!diffuseOn)
            directionalLight.turnDiffuseOff();
        if (!specularOn)
            directionalLight.turnSpecularOff();

        //Set Point Lights (2ta)
        pointLight.setUpLight(ourShader);
        if (!pointLightOn)
            pointLight.turnOff();
        if (!ambientOn)
            pointLight.turnAmbientOff();
        if (!diffuseOn)
            pointLight.turnDiffuseOff();
        if (!specularOn)
            pointLight.turnSpecularOff();


        spotLight.setUpLight(ourShader);
        if (!spotLightOn)
            spotLight.turnOff();
        if (!ambientOn)
            spotLight.turnAmbientOff();
        if (!diffuseOn)
            spotLight.turnDiffuseOff();
        if (!specularOn)
            spotLight.turnSpecularOff();

        //Camera and Others
        ourShader.setVec3("viewPos", camera.Position);
        ourShader.setBool("lightingOn", lightingOn);
        //ourShader.setFloat("ambientOn", ambientOn);
        //ourShader.setFloat("diffuseOn", diffuseOn);
        //ourShader.setFloat("specularOn", specularOn);
        //ourShader.setFloat("pointLightOn", pointLightOn);
        //ourShader.setFloat("directionalLightOn", directionalLightOn);
        //ourShader.setFloat("spotLightOn", spotLightOn);
        //ourShader.setBool("dark", dark);



        //glBindVertexArray(cubeVAO);//by default cubeVAO


        //creating objects
        glActiveTexture(GL_TEXTURE0);

        //testing--------------------------------------------------curve
        float x_shift = 0;
        float y_shift = 0;
        float z_shift = 0;
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
        //universal translate
        uni_translate = glm::translate(identityMatrix, glm::vec3(0.5 * x_shift, 0.5 * y_shift, 0.5 * z_shift));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 2.0f, 2.0f));
        model = uni_translate * translateMatrix * scaleMatrix;
        //circle1.drawBezierCurve(ourShader, model);
        //testing end--------------------------------------------------------------eurve

        //Curve
        x_shift = 0;
        y_shift = 1;
        z_shift = 0;
        Fan_and_switch(cubeVAO, Fan_Bati, Fan_Blade,Fan_Tube, ourShader, x_shift, y_shift, z_shift);

        //Front Arch
        x_shift = 0;
        y_shift = 0;
        z_shift = 0;
        FrontArchGen(cubeVAO,Main_Arch,Sub_Arch,Round_Piller,Piller_Border,ourShader,x_shift,y_shift,z_shift);
        //Side Arch
        x_shift = 0;
        y_shift = 0;
        z_shift = 0;
        SideArchGen(cubeVAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift, y_shift, z_shift);
        //Mid ARC
        x_shift = 0;
        y_shift = 0;
        z_shift = 0;
        MidArchGen(cubeVAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift, y_shift, z_shift);
        //Minar Gen*********************************
        //left front
        x_shift = 15.5;
        y_shift = 0;
        z_shift = 19;
        MinarGen( cubeVAO, Round_Piller,circle,spike, Piller_Border, Round_Piller_Hexa, ourShader, x_shift, y_shift, z_shift);
        //right front
        x_shift = 15.5;
        y_shift = 0;
        z_shift = 36;
        MinarGen(cubeVAO, Round_Piller, circle, spike, Piller_Border, Round_Piller_Hexa, ourShader, x_shift, y_shift, z_shift);
        //left back
        x_shift = 59.5;
        y_shift = 0;
        z_shift = 19;
        MinarGen(cubeVAO, Round_Piller, circle, spike, Piller_Border, Round_Piller_Hexa, ourShader, x_shift, y_shift, z_shift);
        //right back
        x_shift = 59.5;
        y_shift = 0;
        z_shift = 36;
        MinarGen(cubeVAO, Round_Piller, circle, spike, Piller_Border, Round_Piller_Hexa, ourShader, x_shift, y_shift, z_shift);



        //Grass Field------------------------------************************
        x_shift = 0;
        y_shift = 0;
        z_shift = 0;
        Field(cubeVAO77, ourShader, x_shift, y_shift, z_shift, texture1);

        //Main Base------------------------------
        x_shift = 0;
        y_shift = 0;
        z_shift = 0;
        MainBase(cubeVAO77, ourShader, x_shift, y_shift, z_shift, texture4);

        ////front balcony walk-----------------------------
        x_shift = 10;
        y_shift = 0.2;
        z_shift = 11.5;
        FBsideWalk(cubeVAO16, ourShader, x_shift, y_shift, z_shift, texture4, texture5);

        ////left side walk------------------------------------
        x_shift = 9.5;
        y_shift = 0.2;
        z_shift = 12;
        LRsideWalk(cubeVAO101, ourShader, x_shift, y_shift, z_shift, texture4,texture5);
        //right side walk
        x_shift = 60.5;
        y_shift = 0.2;
        z_shift = 12;
        LRsideWalk(cubeVAO101, ourShader, x_shift, y_shift, z_shift, texture4,texture5);

        //Main Mosjid+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        //Mosjid base
        x_shift = 15.5;
        y_shift = 0.2;
        z_shift = 43;
        MainMosjidBase(cubeVAO4, cubeVAO, cubeVAO4 , ourShader, x_shift, y_shift, z_shift, texture4, texture4, texture5);

        //Mosjid 1st floor-----------------------------------------------------------------------------------------
        x_shift = 0;
        y_shift = 0.2;
        z_shift = 0;
        Mosjid1stFloor(cubeVAO, cubeVAO2, cubeVAO3, cubeVAO14, ourShader, x_shift, y_shift, z_shift, texture3);
        //Mosjid 2nd floor------------------------------------------------------------------------------------------
        x_shift = 0;
        y_shift = 0.2;
        z_shift = 0;
        Mosjid2ndFloor(cubeVAO, cubeVAO2, cubeVAO3, cubeVAO14, cubeVAO220, cubeVAO38,ourShader, x_shift, y_shift, z_shift, texture3);///till now


        //ojukhana---------------------------------------------------
        //ojukhana base
        //left front
        x_shift = 8.5;
        y_shift = 0.2;
        z_shift = 10.5;
        Ojubase(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture0);
        x_shift = 0;
        y_shift = 0.2;
        z_shift = 0;
        OjuKhana(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture0);
        
        
        //Toilet
        //right front
        x_shift = 59.5;
        y_shift = 0.2;
        z_shift = 10.5;
        Ojubase(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture0);
        x_shift = 59.5-8.5;
        y_shift = 0.2;
        z_shift = 10.5-10.5;
        Toilet(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture0);


        //Main Gate
        x_shift = 0.0;
        y_shift = 0.2;
        z_shift = 0.0;
        MainGate(cubeVAO,cubeVAO3, ourShader, x_shift, y_shift, z_shift, texture0);


        //front Left Wing
        x_shift = 0.0;
        y_shift = 0.2;
        z_shift = 0.0;
        Frontwing(cubeVAO3, cubeVAO14 ,ourShader, x_shift, y_shift, z_shift, texture7);
        //front Right Wing
        x_shift = 45.0- 15.5;
        y_shift = 0.2;
        z_shift = 10.0-10.0;
        Frontwing(cubeVAO3, cubeVAO14, ourShader, x_shift, y_shift, z_shift, texture7);

        //Mid main gate
        x_shift = 0.0;
        y_shift = 0.2;
        z_shift = 0.0;
        MidGate(cubeVAO, cubeVAO1020, cubeVAO16, ourShader, x_shift, y_shift, z_shift, texture7);


        //side Left Wing
        x_shift = 0.0;
        y_shift = 0.2;
        z_shift = 0.0;
        Sidewing(cubeVAO3, cubeVAO14, ourShader, x_shift, y_shift, z_shift, texture7);
        //side Right Wing
        x_shift = 61.0-10.0;
        y_shift = 0.2;
        z_shift = 17.5-17.5;
        Sidewing(cubeVAO3, cubeVAO14, ourShader, x_shift, y_shift, z_shift, texture7);


        //Stair tower
        //Left tower
        x_shift = 0.0;
        y_shift = 0.2;
        z_shift = 0.0;
        //StairTower1(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture0 );

        //Right tower
        x_shift = 59.5 - 8.5;
        y_shift = 0.2;
        z_shift = 58 - 58;
        //StairTower2(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture0);

        //tombs
        //front
        x_shift = 20.3;
        y_shift = 3.0;
        z_shift = 13;
        for (int i = 0; i < 2; i++)
        {
            small_tomb(cubeVAO, circle, spike, ourShader, x_shift + 4.83*i, y_shift, z_shift);
            small_tomb(cubeVAO, circle, spike, ourShader, x_shift + 30.5+ 4.83*i , y_shift, z_shift);
        }
        //mid
        x_shift = 22.0;
        y_shift = 3.0;
        z_shift = 39.5;
        for (int i = 0; i < 2; i++)
        {
            small_tomb(cubeVAO, circle, spike, ourShader, x_shift + 6.0 * i, y_shift, z_shift);
            small_tomb(cubeVAO, circle, spike, ourShader, x_shift + 29.5 + 6.0 * i, y_shift, z_shift);
        }

        //side
        x_shift = 12.0;
        y_shift = 3.0;
        z_shift = 28.625;
        for (int i = 0; i < 3; i++)
        {
            small_tomb(cubeVAO, circle, spike, ourShader, x_shift , y_shift, z_shift + 11.125 * i);
            small_tomb(cubeVAO, circle, spike, ourShader, x_shift + 51  , y_shift, z_shift + 11.125 * i);
        }
       
       x_shift = 37.5;
       y_shift = 3.5;
       z_shift = 14.0;
       //mid_tomb(cubeVAO, circle1,  spike,  ourShader,  x_shift, y_shift,  z_shift);
       for (int i = 0; i < 2; i++)
       {
           mid_tomb(cubeVAO, circle1, spike, ourShader, x_shift, y_shift, z_shift + 25.5 * i);
           mid_tomb(cubeVAO, circle1, spike, ourShader, 24.2 + 26.8*i, 8.0, 56);
       }
       x_shift = 37.5;
       y_shift = 8.0;
       z_shift = 56.0;
       Big_tomb(cubeVAO, circle1, spike, ourShader, x_shift, y_shift,  z_shift);




    //Lights
    lightCubeShader.use();


    for (int i = 1; i <= 2; i++)
    {

        glm::vec4 bodyColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

        //emissive
        glm::vec3 val = glm::vec3(0.5f);
        if (i == 1 and pointLightOn == 0.0)
            bodyColor = glm::vec4(val, 1.0f);
        if (i == 2 and spotLightOn == 0.0)
            bodyColor = glm::vec4(val, 1.0f);
        /*if (i == 4 and spotLightOn == 0.0)
            bodyColor = glm::vec4(val, 1.0f);*/


        lightCubeShader.setVec4("bodyColor", bodyColor);
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        lightCubeShader.setMat4("projection", projection);
        glm::mat4 view = camera.GetViewMatrix();
        lightCubeShader.setMat4("view", view);
        glm::mat4 tempModel = glm::mat4(1.0f);
        tempModel = glm::translate(tempModel, lightPositions[i]);
        tempModel = glm::scale(tempModel, glm::vec3(0.5f));
        lightCubeShader.setMat4("model", tempModel);

        glBindVertexArray(lightCubeVAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    }


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &lightCubeVAO);

    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &cubeEBO);

    glDeleteVertexArrays(1, &cubeVAO2);
    glDeleteBuffers(1, &cubeVBO2);
    glDeleteBuffers(1, &cubeEBO2);

    glDeleteVertexArrays(1, &cubeVAO3);
    glDeleteBuffers(1, &cubeVBO3);
    glDeleteBuffers(1, &cubeEBO3);


    glDeleteVertexArrays(1, &cubeVAO4);
    glDeleteBuffers(1, &cubeVBO4);
    glDeleteBuffers(1, &cubeEBO4);

    glDeleteVertexArrays(1, &cubeVAO77);
    glDeleteBuffers(1, &cubeVBO77);
    glDeleteBuffers(1, &cubeEBO77);

    glDeleteVertexArrays(1, &cubeVAO16);
    glDeleteBuffers(1, &cubeVBO16);
    glDeleteBuffers(1, &cubeEBO16);

    glDeleteVertexArrays(1, &cubeVAO14);
    glDeleteBuffers(1, &cubeVBO14);
    glDeleteBuffers(1, &cubeEBO14);


    glDeleteVertexArrays(1, &cubeVAO38);
    glDeleteBuffers(1, &cubeVBO38);
    glDeleteBuffers(1, &cubeEBO38);


    glDeleteVertexArrays(1, &cubeVAO220);
    glDeleteBuffers(1, &cubeVBO220);
    glDeleteBuffers(1, &cubeEBO220);

    glDeleteVertexArrays(1, &cubeVAO101);
    glDeleteBuffers(1, &cubeVBO101);
    glDeleteBuffers(1, &cubeEBO101);

    glDeleteVertexArrays(1, &cubeVAO1020);
    glDeleteBuffers(1, &cubeVBO1020);
    glDeleteBuffers(1, &cubeEBO1020);


    glDeleteVertexArrays(1, &hexaVAO);
    glDeleteBuffers(1, &hexaVBO);
    glDeleteBuffers(1, &hexaEBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}


//Texture Loading function
void load_texture(unsigned int& texture, string image_name, GLenum format)
{
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(image_name.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        cout << "Failed to load texture " << image_name << endl;
    }
    stbi_image_free(data);
}

void Floor(Shader ourShader, glm::mat4 moveMatrix, glm::vec4 color)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model;

    translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.0f, 1.25f + 0.45f, -6.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(40.3f, 0.1f, 40.0f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", moveMatrix * model);
    ourShader.setVec4("material.ambient", color);
    ourShader.setVec4("material.diffuse", color);
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void Field(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;

    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3( x_shift,  y_shift, -1.0f *z_shift));

    //grass layer----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(75.0f, 0.1f, -75.0f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(1.0,1.0,1.0, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(1.0, 1.0, 1.0, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void MainBase(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    //front left box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    float lbx = 8.5, lby = 0.0f, lbz = 10.5f;
    float len = 58.0;
    float width = 59.5;
    GenFloor(VAO, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture);
}

void FBsideWalk(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture1 = texture0, unsigned int texture2 = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3( x_shift, y_shift, -1.0 * z_shift));
    //grass layer----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture1);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(55.0f, 0.2f, -5.0f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //Tiles
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    //left wing-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    float lbx = 5.5, lby = 0.05f, lbz = 0.5f;
    float len = 14.5;
    float width = 4.0;
    GenFloor(VAO, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture2);

    //right wing-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 35.0, lby = 0.05f, lbz = 0.5f;
    len = 14.5;
    width = 4.0;
    GenFloor(VAO, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture2);
}

void LRsideWalk(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture1 = texture0, unsigned int texture2 = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;

    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3( x_shift, y_shift, -1.0f * z_shift));

    //grass layer----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture1);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.0f, 0.2f, -55.0f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //Tiles
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    float lbx = 0.5, lby = 0.05f, lbz = 5.5f;
    float len = 4.0;
    float width = 40.5;
    GenFloor(VAO, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture2);

}

void Ojubase(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;

    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));

    //grass layer----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(7.0f, 0.2f, -7.0f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void MainMosjidBase(unsigned int VAO1, unsigned int VAO2, unsigned int VAO3, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture1 = texture0, unsigned int texture2 = texture0, unsigned int texture3 = texture0)
{
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++MAIN FLOOR
    float lbx = 0.0, lby = 0.0f, lbz = 0.0f;
    float len = 44.0;
    float width = 25.0;
    GenFloor(VAO1, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture1);
    //imam box floor+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 20.3, lby = 0.0f, lbz = 25.0f;
    len = 3.4;
    width = 2.0;
    GenFloor(VAO2, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture2);

    //main floor box tex+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 0.5, lby = 0.01f, lbz = 0.5f;
    len = 43;
    width = 24;
    GenFloor(VAO3, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture3);

}


void Mosjid1stFloor(unsigned int VAO1, unsigned int VAO2 , unsigned int VAO3, unsigned int VAO14, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;


    //roof box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    float lbx = 15.5, lby = 2.7f + 0.2f, lbz = 43.0f;
    float len = 44.0, ht = 1.7f;
    float width = 25.0;
    HoloBox(VAO14, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture6);//1x3
    //roof mid left
    //(ht + lby) - 0.2f,
    lbx = 15.7, lby = (1.7f + 2.7f + 0.2f) - 0.2f, lbz = 51.0f;
    len = 16.8, width = 10.0f;
    GenFloor(VAO1, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture12);//1x1
    //roof mid right
    //(ht + lby) - 0.2f,
    lbx = 42.5, lby = (1.7f + 2.7f + 0.2f) - 0.2f, lbz = 51.0f;
    len = 16.8, width = 10.0f;
    GenFloor(VAO1, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture12);//1x1
    //roof front
    //(ht + lby) - 0.2f,
    lbx = 15.7, lby = (1.7f + 2.7f + 0.2f) - 0.2f, lbz = 43.2f;//1x3
    len = 43.6, width = 7.8f;
    GenFloor(VAO3, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture11);//1x3
    //roof back
    //(ht + lby) - 0.2f,
    lbx = 15.7, lby = (1.7f + 2.7f + 0.2f) - 0.2f, lbz = 61.0f;
    len = 43.6, width = 6.8f;
    GenFloor(VAO3, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture10);//1x3


    //front left wall-----------------+++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 15.5, lby = 0.2f, lbz = 43.0f;
    len = 8.5, ht = 2.7f;
    HorizontalWall(VAO2, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, frontwall1);//1x1

    //front mid left wall
    lbx = 27.0, lby = 0.2f, lbz = 43.0f;
    len = 7.5, ht = 2.7f;
    HorizontalWall(VAO2, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, frontwall1);//1x1
    //front mid right wall
    lbx = 40.5, lby = 0.2f, lbz = 43.0f;
    len = 7.5, ht = 2.7f;
    HorizontalWall(VAO2, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, frontwall1);//1x1
    //front right wall
    lbx = 51.0, lby = 0.2f, lbz = 43.0f;
    len = 8.5, ht = 2.7f;
    HorizontalWall(VAO2, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, frontwall1);//1x1

    //back left wall--------------------
    lbx = 15.5, lby = 0.2f, lbz = 67.8f;
    len = 20.5, ht = 2.7f;
    HorizontalWall(VAO14, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, texture9);//1x3

    //back right wall
    lbx = 39.0, lby = 0.2f, lbz = 67.8f;
    len = 20.5, ht = 2.7f;
    HorizontalWall(VAO14, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, texture9);//1x3

    //right side front wall-----------------+++++++++++++++++++++++++++++++++++++
    lbx = 15.5, lby = 0.2f, lbz = 43.0f;
    len = 11.0, ht = 2.7f;
    VerticalWall(VAO2, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, sidewall2);//1x1
    //right side back wall
    lbx = 15.5, lby = 0.2f, lbz = 58.0f;
    len = 10.0, ht = 2.7f;
    VerticalWall(VAO2, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, sidewall2);//1x1

    //left side front wall-----------------
    lbx = 59.3, lby = 0.2f, lbz = 43.0f;
    len = 11.0, ht = 2.7f;
    VerticalWall(VAO2, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, sidewall2);//1x1

    //left side back wall
    lbx = 59.3, lby = 0.2f, lbz = 58.0f;
    len = 10.0, ht = 2.7f;
    VerticalWall(VAO2, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, sidewall2);//1x1

    //imam place=====================
    //left wall
    lbx = 35.8, lby = 0.2f, lbz = 67.8f;
    len = 2.0, ht = 2.7f;
    VerticalWall(VAO1, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, mehrabside);//1x1
    //right wall
    lbx = 39.0, lby = 0.2f, lbz = 67.8f;
    len = 2.0, ht = 2.7f;
    VerticalWall(VAO1, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, mehrabside);//1x1
    //back wall
    lbx = 35.8, lby = 0.2f, lbz = 69.8f;
    len = 3.4, ht = 2.7f;
    HorizontalWall(VAO1, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, mehrab);//1x1
    //top box
    lbx = 35.8, lby = 2.7f+0.2f, lbz = 67.8f;
    len = 3.4, ht = 1.0f;
    width = 2.2;
    Box(VAO1, VAO1, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture4);//1x1
}

void Mosjid2ndFloor(unsigned int VAO1, unsigned int VAO2, unsigned int VAO3, unsigned int VAO14, unsigned int VAO220, unsigned int VAO38, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;


    //roof box-------------------------------------------------------Not FLat
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    float lbx = 15.5, lby = 6.8f + 0.2f, lbz = 45.0f;
    float len = 44.0, ht = 1.8f;
    float width = 22.0;
    HoloBox(VAO14, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture6);//1x3
    //ROOF TOP************************************************
    //roof Front
    //(ht + lby) - 0.4f,
    lbx = 15.7, lby = (1.8f + 6.8f + 0.2f) - 0.4f, lbz = 45.2f;
    len = 43.6, width = 6.3f;
    GenFloor(VAO3, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture7);//1x3
    //roof mid left
    //(ht + lby) - 0.4f,
    lbx = 15.7, lby = (1.8f + 6.8f + 0.2f) - 0.4f, lbz = 51.5;
    len = 17.3, width = 9.0f;
    GenFloor(VAO1, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture7);//1x1
    //roof mid right
    //(ht + lby) - 0.4f,
    lbx = 42, lby = (1.8f + 6.8f + 0.2f) - 0.4f, lbz = 51.5;
    len = 17.3, width = 9.0f;
    GenFloor(VAO1, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture7);//1x1
    //roof back
    //(ht + lby) - 0.4f,
    lbx = 15.7, lby = (1.8f + 6.8f + 0.2f) - 0.4f, lbz = 60.5f;
    len = 43.6, width = 6.3f;
    GenFloor(VAO3, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture7);//1x3

    //ROOF BOTTOM************************************************
    //roof Front
    //(ht + lby) - 0.4f,
    lbx = 15.7, lby = (1.8f + 6.8f + 0.2f -.01) - 0.4f, lbz = 45.2f;
    len = 43.6, width = 6.3f;
    GenFloor(VAO3, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture11);//1x3
    //roof mid left
    //(ht + lby) - 0.4f,
    lbx = 15.7, lby = (1.8f + 6.8f + 0.2f - .01) - 0.4f, lbz = 51.5;
    len = 17.3, width = 9.0f;
    GenFloor(VAO1, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture12);//1x1
    //roof mid right
    //(ht + lby) - 0.4f,
    lbx = 42, lby = (1.8f + 6.8f + 0.2f - .01) - 0.4f, lbz = 51.5;
    len = 17.3, width = 9.0f;
    GenFloor(VAO1, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture12);//1x1
    //roof back
    //(ht + lby) - 0.4f,
    lbx = 15.7, lby = (1.8f + 6.8f + 0.2f - .01) - 0.4f, lbz = 60.5f;
    len = 43.6, width = 6.3f;
    GenFloor(VAO3, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture10);//1x3

    //FLOOR TOP************************************************
   //roof Front
   //(ht + lby) - 0.4f,
    lbx = 15.7, lby = (1.7f + 2.7f + 0.2f+0.01) - 0.2f, lbz = 45.2f;
    len = 43.6, width = 6.3f;
    GenFloor(VAO220, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture5);//2x220
    //roof mid left
    //(ht + lby) - 0.4f,
    lbx = 15.7, lby = (1.7f + 2.7f + 0.2f + 0.01) - 0.2f, lbz = 51.5;
    len = 17.3, width = 9.0f;
    GenFloor(VAO38, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture5);//3x8
    //roof mid right
    //(ht + lby) - 0.4f,
    lbx = 42, lby = (1.7f + 2.7f + 0.2f + 0.01) - 0.2f, lbz = 51.5;
    len = 17.3, width = 9.0f;
    GenFloor(VAO38, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture5);//3x8
    //roof back
    //(ht + lby) - 0.4f,
    lbx = 15.7, lby = (1.7f + 2.7f + 0.2f + 0.01) - 0.2f, lbz = 60.5f;
    len = 43.6, width = 6.3f;
    GenFloor(VAO220, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture5);//2x20

    //front left wall-----------------+++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 15.5, lby = 0.2 + 2.7 + 1.9 - 0.2, lbz = 45.0;
    len = 8.5, ht = 2.7f;
    HorizontalWall(VAO2, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, frontwall1);//1x1

    //front mid wall
    lbx = 27.0, lby = 0.2 + 2.7 + 1.9 - 0.2, lbz = 45.0;
    len = 21, ht = 2.7f;
    HorizontalWall(VAO14, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, sidewall2);//1x2
    //front right wall
    lbx = 51.0, lby = 0.2 + 2.7 + 1.9 - 0.2, lbz = 45.0;
    len = 8.5, ht = 2.7f;
    HorizontalWall(VAO2, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, frontwall1);//1x1

    //back left wall--------------------
    lbx = 15.5, lby = 0.2 + 2.7 + 1.9 - 0.2, lbz = 66.8;
    len = 8.5, ht = 2.7f;
    HorizontalWall(VAO2, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, frontwall1);//1x1

    //back MID wall--------------------
    lbx = 27.0, lby = 0.2 + 2.7 + 1.9 - 0.2, lbz = 66.8;
    len = 21.0, ht = 2.7f;
    HorizontalWall(VAO14, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, frontwall1);//1x2

    //back right wall
    lbx = 51.0, lby = 0.2 + 2.7 + 1.9 - 0.2, lbz = 66.8;
    len = 8.5, ht = 2.7f;
    HorizontalWall(VAO2, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, frontwall1);//1x1

    //right side front wall-----------------+++++++++++++++++++++++++++++++++++++
    lbx = 15.5, lby = 0.2 + 2.7 + 1.9 - 0.2, lbz = 45.0;
    len = 15.0, ht = 2.7f;
    VerticalWall(VAO3, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, sidewall2);//1x2
    //right side back wall
    lbx = 15.5, lby = 0.2 + 2.7 + 1.9 - 0.2, lbz = 63.0;
    len = 4.0, ht = 2.7f;
    VerticalWall(VAO1, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, sidewall2);//1x1

    //left side front wall-----------------
    lbx = 59.3, lby = 0.2 + 2.7 + 1.9 - 0.2, lbz = 45.0f;
    len = 15.0, ht = 2.7f;
    VerticalWall(VAO3, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, sidewall2);//1x2

    //left side back wall
    lbx = 59.3, lby = 0.2 + 2.7 + 1.9 - 0.2, lbz = 63.0f;
    len = 4.0, ht = 2.7f;
    VerticalWall(VAO1, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, sidewall2);//1x1


}

void OjuKhana(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0) 
{

    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    //roof box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    float lbx = 8.5f, lby = 2.2f + 0.2f, lbz = 10.5f;
    float len = 7.0f, width = 7.0f, ht = 1.7f;
    //fornt wall
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift)); --
        x_sft = lbx, y_sft = lby, z_sft = lbz;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, -0.2f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //left wall---------------------------------------
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, ht, -1.0f * width));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //BACK wall-------------------------------------------------------
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift)); --
        x_sft = lbx, y_sft = lby, z_sft = lbz + width - 0.2;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, -0.2f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //RIGHT wall---------------------------------------
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = lbx + len - 0.2, y_sft = lby, z_sft = lbz;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, ht, -1.0f * width));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //top box
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = lbx + 0.1f, y_sft = (ht + lby) - 0.4f, z_sft = lbz + 0.1f;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len - 0.2, 0.2f, -1.0f * (width - 0.2f)));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.0, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.0, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //box++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++END



    //front wall-------------------------------------------------------
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));--
    x_sft = 8.6f, y_sft = 0.2f, z_sft = 10.6f;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f* z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(6.8f, 2.5f, -0.2f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //left wall---------------------------------------
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = 8.6f, y_sft = 0.2f, z_sft = 10.6f;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, 2.5f, -6.8f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //back wall-------------------------------------------------------
    //1
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = 8.6f, y_sft = 0.2f, z_sft = 17.2f;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.4f, 2.2f, -0.2f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //2
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift)); 
    x_sft = 13.0f, y_sft = 0.2f, z_sft = 17.2f;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.4f, 2.2f, -0.2f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //left wall---------------------------------------
    //1
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = 15.2f, y_sft = 0.2f, z_sft = 10.6f;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, 2.2f, -2.4f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //2
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = 15.2f, y_sft = 0.2f, z_sft = 15.0f;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, 2.2f, -2.4f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //pillers
    //leftbot
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = 8.5f, y_sft = 0.2f, z_sft = 10.5f;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 2.2f, -0.5f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.0, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.0, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //lefttop
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = 8.5f, y_sft = 0.2f, z_sft = 17;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 2.2f, -0.5f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.0, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.0, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //rightbot
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = 15.0f, y_sft = 0.2f, z_sft = 10.5f;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 2.2f, -0.5f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.0, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.0, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //righttop
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = 15.0f, y_sft = 0.2f, z_sft = 17.0f;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 2.2f, -0.5f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.0, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.0, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //INSIDE
    //FLoor
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = 9.1f, y_sft = 0.0f, z_sft = 11.1f;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(6.1f, 0.4f, -6.1f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.7, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.7, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //seats left

    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = 9.4f, y_sft = 0.4f, z_sft = 12.6f;
    for (int i = 0; i < 3; i++)
    {
        glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
        translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, (- 1.0f * z_sft)-i*1.55));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.5f, -0.5f));
        model = uni_translate * translateMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        ourShader.setVec4("material.ambient", glm::vec4(0.2, 0.8549019607843137, 0.8, 1.0f));
        ourShader.setVec4("material.diffuse", glm::vec4(0.2, 0.8549019607843137, 0.8, 1.0f));
        ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
        ourShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }


    //seats right
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = 10.6f, y_sft = 0.4f, z_sft = 11.4f;

    for (int i = 0; i < 3; i++)
    {
        glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
        translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft + i * 1.55f, y_sft, -1.0f * z_sft ));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.5f, -0.5f));
        model = uni_translate * translateMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        ourShader.setVec4("material.ambient", glm::vec4(0.2, 0.8549019607843137, 0.8, 1.0f));
        ourShader.setVec4("material.diffuse", glm::vec4(0.2, 0.8549019607843137, 0.8, 1.0f));
        ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
        ourShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }
}

void Toilet(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{

    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    //roof box
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    float lbx = 8.5f, lby = 2.2f + 0.2f, lbz = 10.5f;
    float len = 7.0f, width = 7.0f, ht = 1.7f;
    //fornt wall
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift)); --
        x_sft = lbx, y_sft = lby, z_sft = lbz;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, -0.2f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //left wall---------------------------------------
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, ht, -1.0f * width));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //BACK wall-------------------------------------------------------
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift)); --
        x_sft = lbx, y_sft = lby, z_sft = lbz + width - 0.2;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, -0.2f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //RIGHT wall---------------------------------------
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = lbx + len - 0.2, y_sft = lby, z_sft = lbz;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, ht, -1.0f * width));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //top box
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = lbx + 0.1f, y_sft = (ht + lby) - 0.4f, z_sft = lbz + 0.1f;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len - 0.2, 0.2f, -1.0f * (width - 0.2f)));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.0, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.0, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //box++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++END



    //front wall-------------------------------------------------------
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift)); --
        x_sft = 8.6f, y_sft = 0.2f, z_sft = 10.6f;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(6.8f, 2.5f, -0.2f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //right wall---------------------------------------
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = 15.2f, y_sft = 0.2f, z_sft = 10.6f;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, 2.5f, -6.8f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //back wall-------------------------------------------------------
    //1
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = 8.6f, y_sft = 0.2f, z_sft = 17.2f;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.4f, 2.2f, -0.2f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //2
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = 13.0f, y_sft = 0.2f, z_sft = 17.2f;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.4f, 2.2f, -0.2f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //right wall---------------------------------------
    //1
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = 8.6f, y_sft = 0.2f, z_sft = 10.6f;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, 2.2f, -2.4f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //2
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = 8.6f, y_sft = 0.2f, z_sft = 15.0f;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, 2.2f, -2.4f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //pillers
    //leftbot
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = 8.5f, y_sft = 0.2f, z_sft = 10.5f;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 2.2f, -0.5f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.0, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.0, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //lefttop
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = 8.5f, y_sft = 0.2f, z_sft = 17;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 2.2f, -0.5f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.0, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.0, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //rightbot
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = 15.0f, y_sft = 0.2f, z_sft = 10.5f;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 2.2f, -0.5f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.0, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.0, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //righttop
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = 15.0f, y_sft = 0.2f, z_sft = 17.0f;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 2.2f, -0.5f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.0, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.0, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //INSIDE
    //FLoor
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = 8.8f, y_sft = 0.0f, z_sft = 10.8f;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(6.1f, 0.4f, -6.4f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.7, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.7, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //seats left

    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = 14.0f, y_sft = 0.4f, z_sft = 13.0f;
    for (int i = 1; i < 3; i++)
    {
        glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
        translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, (-1.0f * z_sft) - i * 1.55));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.5f, -0.5f));
        model = uni_translate * translateMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        ourShader.setVec4("material.ambient", glm::vec4(0.2, 0.8549019607843137, 0.8, 1.0f));
        ourShader.setVec4("material.diffuse", glm::vec4(0.2, 0.8549019607843137, 0.8, 1.0f));
        ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
        ourShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }


    //seats right
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = 9.1f, y_sft = 0.4f, z_sft = 11.1f;

    for (int i = 0; i < 4; i++)
    {
        glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
        translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft + i * 1.8f, y_sft, -1.0f * z_sft));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, 2.0f, -1.5f));
        model = uni_translate * translateMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        ourShader.setVec4("material.ambient", glm::vec4(0.2, 0.8549019607843137, 0.8, 1.0f));
        ourShader.setVec4("material.diffuse", glm::vec4(0.2, 0.8549019607843137, 0.8, 1.0f));
        ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
        ourShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }
    

    //bath_room top border wall
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = 9.1f, y_sft = 1.8f, z_sft = 12.4f;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.6f, 0.6f, -0.1f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.7, 0.549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.7, 0.549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //bath_inside_left wall
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = 9.3f, y_sft = 0.4f, z_sft = 12.4f;
    for (int i = 0; i < 3; i++)
    {
        glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
        translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft + i * 1.8f, y_sft, -1.0f * z_sft));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 1.4f, -0.1f));
        model = uni_translate * translateMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        ourShader.setVec4("material.ambient", glm::vec4(0.2, 0.8549019607843137, 0.8, 1.0f));
        ourShader.setVec4("material.diffuse", glm::vec4(0.2, 0.8549019607843137, 0.8, 1.0f));
        ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
        ourShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }

    //bath_inside_right wall
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = 9.3f+(0.5f+0.6f), y_sft = 0.4f, z_sft = 12.4f;
    for (int i = 0; i < 3; i++)
    {
        glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
        translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft + i * 1.8f, y_sft, -1.0f * z_sft));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 1.4f, -0.1f));
        model = uni_translate * translateMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        ourShader.setVec4("material.ambient", glm::vec4(0.2, 0.8549019607843137, 0.8, 1.0f));
        ourShader.setVec4("material.diffuse", glm::vec4(0.2, 0.8549019607843137, 0.8, 1.0f));
        ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
        ourShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }

    //Doors------------------------------------------------------------------------------------------------------
    //1st door
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = 9.8f, y_sft = 0.42f, z_sft = 12.4f;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft + 0 * 1.8f, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.6f, 1.36f, -0.05f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.6, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.6, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //2nd door
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = 9.8f, y_sft = 0.42f, z_sft = 12.4f;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft + 1 * 1.8f, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.6f, 1.36f, -0.05f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.6, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.6, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //3rd door
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = 9.8f, y_sft = 0.42f, z_sft = 12.4f;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft + 2 * 1.8f, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.6f, 1.36f, -0.05f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.6, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.6, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //Doors----------------------------------------------------------------------------------------END

    //Flush
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = 10.0f, y_sft = 0.4f+0.5, z_sft = 11.1f;
    for (int i = 0; i < 3; i++)
    {
        glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
        translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft + i * 1.8f, y_sft, -1.0f * z_sft));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3( 0.4f, 0.4f, -0.1f));
        model = uni_translate * translateMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        ourShader.setVec4("material.ambient", glm::vec4(0.2, 0.8549019607843137, 0.8, 1.0f));
        ourShader.setVec4("material.diffuse", glm::vec4(0.2, 0.8549019607843137, 0.8, 1.0f));
        ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
        ourShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }

}

void MainGate(unsigned int VAO1, unsigned int VAO2, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;


    //front left box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    float lbx = 30.0f, lby = 0.2f, lbz = 11.0f;
    float len = 2.0, ht = 4.25;
    float width = len;
    Box(VAO1, VAO2, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture4);
    //box++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++END

    //back left box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 30.0f, lby = 0.2f, lbz = 15.0f;
    len = 2.0, ht = 4.25;
    width = len;
    Box(VAO1, VAO2, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture4);

    //front right box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 43.0f, lby = 0.2f, lbz = 11.0f;
    len = 2.0, ht = 4.25;
    width = len;
    Box(VAO1, VAO2, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture4);
    //box++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++END

    //back right box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 43.0f, lby = 0.2f, lbz = 15.0f;
    len = 2.0, ht = 4.25;
    width = len;
    Box(VAO1, VAO2, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture4);

    //Mid Main box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 34.0, lby = 3.0f + 0.2f, lbz = 10.5f;
    len = 7.0, ht = 1.5;
    width = len;
    Box(VAO1, VAO2, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture4);
    
    //Mid Main gate front left box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 34.0, lby = 0.2f, lbz = 10.5f;
    len = 1.75, ht = 3.0;
    width = len;
    Box(VAO1, VAO2, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture4);

    //Mid Main gate back left box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 34.0, lby = 0.2f, lbz = 15.75f;
    len = 1.75, ht = 3.0;
    width = len;
    Box(VAO1, VAO2, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture4);

    //Mid Main gate front right box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 39.25, lby = 0.2f, lbz = 10.5f;
    len = 1.75, ht = 3.0;
    width = len;
    Box(VAO1, VAO2, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture4);


    //Mid Main gate back right box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 39.25, lby = 0.2f, lbz = 15.75;
    len = 1.75, ht = 3.0;
    width = len;
    Box(VAO1, VAO2, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture4);

    //left mid wing box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 30, lby = 2.7f + 0.2f, lbz = 11.5f;
    len = 4.0f, ht = 1.0f;
    width = 5.0;
    Box(VAO1, VAO2, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture4);

    //right mid wing box-------------------------------------------------------
        //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 41, lby = 2.7f + 0.2f, lbz = 11.5f;
    len = 4.0f, ht = 1.0f;
    width = 5.0;
    Box(VAO1, VAO2, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture4);

    //MID FLOOR_+_+_+_+_+
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 30.0, lby = 0.02, lbz = 10.5f;
    len = 15.0f;
    width = 7.0;
    GenFloor(VAO1, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture4);

}

void Frontwing(unsigned int VAO1, unsigned int VAO2, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    //front left box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    float lbx = 15.5, lby = 2.7f + 0.2f, lbz = 12.0f;
    float len = 14.5, width = 4.0, ht = 1.0f;
    Box(VAO1, VAO2, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture4);
}

void Sidewing(unsigned int VAO1, unsigned int VAO2, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;


    //front left box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    float lbx = 10.0, lby = 2.7f + 0.2f, lbz = 17.5f;
    float len = 4.0, width = 40.5, ht = 1.0f;
    Box(VAO1, VAO2, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture4);
    
}

void MidGate(unsigned int VAO1, unsigned int VAO1020, unsigned int VAO16, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    //front left box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    float lbx = 31.5f, lby = 0.2f, lbz = 35.5f;
    float len = 2.0, ht = 5.0;
    float width = len;
    Box(VAO1, VAO1, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture4);

    //front right box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 41.5f, lby = 0.2f, lbz = 35.5f;
    len = 2.0, ht = 5.0;
    width = len;
    Box(VAO1, VAO1, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture4);

    //Mid Gate main box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 32.0, lby = 2.7f + 0.2f, lbz = 36.0f;
    len = 11.0, ht = 1.9f;
    width = 7.0;
    Box(VAO1, VAO1, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture4);
     

    //Left wing_+_+_+_+_+
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 14.0, lby = 2.7f + 0.2f, lbz = 37.5f;
    len = 18, ht = 1.0f;
    width = 4.0;
    Box(VAO1, VAO16, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture6);

    //right wing_+_+_+_+_+
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 43.0, lby = 2.7f + 0.2f, lbz = 37.5f;
    len = 18, ht = 1.0f;
    width = 4.0;
    Box(VAO1, VAO16, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture6);
   
    //Chipa wallllllllllllllllllll---------------------------------------=-
    //front left chipa wall
    lbx = 14.0, lby = 2.7f + 0.2f, lbz = 41.5f;
    len = 18.0;
    width = 1.5;
    GenFloor(VAO1, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture4);

    //front right chipa wall
    lbx = 43.0, lby = 2.7f + 0.2f, lbz = 41.5f;
    len = 18.0;
    width = 1.5;
    GenFloor(VAO1, ourShader, x_shift, y_shift, z_shift, len, width,  lbx, lby, lbz, texture4);


    //left side chipa wall
    lbx = 14.0, lby = 2.7f + 0.2f, lbz = 43.0f;
    len = 1.5f;
    width = 15.0;
    GenFloor(VAO1, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture4);

    //right side chipa wall
    lbx = 59.5, lby = 2.7f + 0.2f, lbz = 43.0f;
    len = 1.5f;
    width = 15.0;
    GenFloor(VAO1, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture4);


    //FLOORS ***********
     //Left wing_+_+_+_+_+
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 14.0, lby = 0.01f, lbz = 37.5f;
    len = 17.5;
    width = 4.0;
    GenFloor(VAO16,ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture5);

    //right wing_+_+_+_+_+
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 43.5, lby = 0.01, lbz = 37.5f;
    len = 17.5f;
    width = 4.0;
    GenFloor(VAO16, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture5);

    //MID FLOOR_+_+_+_+_+
//box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 31.5, lby = 0.02, lbz = 35.5f;
    len = 12.0f;
    width = 7.5;
    GenFloor(VAO1, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture4);

    //MAIN OUTSIDE TILES FLLOR
    lbx = 14.25, lby = 0.005, lbz = 16.25f;
    len = 46.5;
    width = 21;
    GenFloor(VAO1020, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture8);

    //POND 
    //HOLO BOX
    //lbx = 31.5, lby = 0.0, lbz = 23.75;
    //len = 6.0;
    //width = 6.0;
    //ht = 0.8;
    //HoloBox(VAO16, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture8);
    ////Water
    //lbx = 31.7, lby = 0.4, lbz = 23.95;
    //len = 6.0-0.4;
    //width = 6.0 - 0.4;;
    //GenFloor(VAO1, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, water[wcnt/10]);
    //wcnt++;
    //wcnt = wcnt % 100;

}

void StairTower1(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;


    //front left box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    float lbx = 8.5f, lby = 0.2f, lbz = 58.0f;
    float len = 1.5, ht = 8.2;
    float width = len;
    Box(VAO, VAO, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture4);

    //back left box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 8.5f, lby = 0.2f, lbz = 63.5f;
    len = 1.5, ht = 8.2;
    width = len;
    Box(VAO, VAO, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture4);

    //front right box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 14.0, lby = 0.2f, lbz = 58.0f;
    len = 1.5, ht = 8.2;
    width = len;
    Box(VAO, VAO, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture4);

    //back right box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 14.0, lby = 0.2f, lbz = 63.5f;
    len = 1.5, ht = 8.2;
    width = len;
    Box(VAO, VAO, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture4);

    //main box tower-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 8.5, lby = 6.8f + 0.2f, lbz = 58.0f;
    len = 7.0, ht = 1.0f;
    width = 7.0;
    Box(VAO, VAO, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture4);

    //2ND FLOOR STAIR FLOOR
    lbx = 13.0, lby = 4.6-0.2, lbz = 59.5;
    len = 2.5;
    width = 4.0;
    GenFloor(VAO, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture);

    //bottom stairs
    lbx = 12.7, lby = 0.2, lbz = 61.7;
    len = 0.3;
    width = 1.8;
    for (int i = 0; i < 10; i++)
    {
        GenFloor(VAO, ourShader, x_shift, y_shift, z_shift, len, width, lbx - i*0.3, lby+i*0.2, lbz, texture);
    }
    //half talar floor
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 8.5, lby = 2.2, lbz = 59.5;
    len = 1.5;
    width = 4.0;
    GenFloor(VAO, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture);

    //top stairs
    lbx = 10.0, lby = 2.4, lbz = 59.5;
    len = 0.3;
    width = 1.8;
    for (int i = 0; i < 10; i++)
    {
        GenFloor(VAO, ourShader, x_shift, y_shift, z_shift, len, width, lbx + i * 0.3, lby + i * 0.2, lbz, texture);
    }

    //front mid box
    lbx = 10.0, lby = 2.2, lbz = 58.0f;
    len = 4.0, ht = 1.7f;
    width = 1.5;
    FlatBox(VAO, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture);

    //left mid box
    lbx = 8.5, lby = 0.2, lbz = 59.5f;
    len = 1.5, ht = 2.0f;
    width = 4.0;
    FlatBox(VAO, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture);

    //back mid box
    lbx = 10.0, lby = 0.2, lbz = 63.5f;
    len = 4.0, ht = 3.7f;
    width = 1.5;
    FlatBox(VAO, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture);
}

void StairTower2(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;


    //front left box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    float lbx = 8.5f, lby = 0.2f, lbz = 58.0f;
    float len = 1.5, ht = 8.2;
    float width = len;
    Box(VAO, VAO, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture4);

    //back left box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 8.5f, lby = 0.2f, lbz = 63.5f;
    len = 1.5, ht = 8.2;
    width = len;
    Box(VAO, VAO, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture4);

    //front right box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 14.0, lby = 0.2f, lbz = 58.0f;
    len = 1.5, ht = 8.2;
    width = len;
    Box(VAO, VAO, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture4);

    //back right box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 14.0, lby = 0.2f, lbz = 63.5f;
    len = 1.5, ht = 8.2;
    width = len;
    Box(VAO, VAO, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture4);

    //main box tower-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 8.5, lby = 6.8f + 0.2f, lbz = 58.0f;
    len = 7.0, ht = 1.0f;
    width = 7.0;
    Box(VAO, VAO, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture4);

    //2ND FLOOR STAIR FLOOR
    lbx = 8.5, lby = 4.6 - 0.2, lbz = 59.5;
    len = 1.5;
    width = 4.0;
    GenFloor(VAO, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture);


    //front mid box
    lbx = 10.0, lby = 2.2, lbz = 58.0f;
    len = 4.0, ht = 1.7f;
    width = 1.5;
    FlatBox(VAO, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture);

    //right mid box
    lbx = 14, lby = 0.2, lbz = 59.5f;
    len = 1.5, ht = 2.0f;
    width = 4.0;
    FlatBox(VAO, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture);

    //left mid box
    lbx = 8.5, lby = 0.2, lbz = 59.5f;
    len = 1.5, ht = 4.2f;
    width = 4.0;
    FlatBox(VAO, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture);

    //back mid box
    lbx = 10.0, lby = 0.2, lbz = 63.5f;
    len = 4.0, ht = 3.7f;
    width = 1.5;
    FlatBox(VAO, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture);

    //LIFT ---------------------------------------
    //4.4 e 2nd floor
    //4.2 plus korte hobe
    if (isLift)
    {
        if (translate_X_Lift < 1.0 )
        {
            translate_X_Lift += lift_speed;
        }
        else
        {
            if (translate_Y_Lift < 4.2 - 0.1)
            {
                translate_Y_Lift += lift_speed;
            }
            else
            {
                if (translate_Z_Lift < 1.0 )
                {
                    translate_Z_Lift += lift_speed;
                }
                else
                {
                    lift_ready = true;
                }
            }
        }
    }
    else
    {
        if (translate_Z_Lift > 0.0)
        {
            translate_Z_Lift -= lift_speed;
        }
        else
        {
            if (translate_Y_Lift > 0.0 )
            {
                translate_Y_Lift -= lift_speed;
            }
            else
            {
                if (translate_X_Lift > 0.0)
                {
                    translate_X_Lift -= lift_speed;
                }
                else
                {
                    lift_ready = true;
                }
            }
        }
    }
    //FLOOR
    lbx = 10.05, lby = 0.2, lbz = 59.55f;
    len = 3.9;
    width = 3.9;
    GenFloor(VAO, ourShader, x_shift, y_shift + translate_Y_Lift, z_shift, len, width, lbx, lby, lbz, texture);
    //Lift roof box
    lbx = 10.05, lby = 2.2, lbz = 59.55f;
    len = 3.9, ht = 1.0f;
    width = 3.9;
    FlatBox(VAO, ourShader, x_shift, y_shift + translate_Y_Lift, z_shift, len, width, ht, lbx, lby, lbz, texture);

    //lift inside front left wall
    lbx = 10.05, lby = 0.2f, lbz = 59.55f;
    len = 0.5, ht = 2.9f;
    HorizontalWall(VAO, ourShader, x_shift, y_shift + translate_Y_Lift, z_shift, len, ht, lbx, lby, lbz, texture);

    //lift inside front right wall
    lbx = 13.45, lby = 0.2f, lbz = 59.55f;
    len = 0.5, ht = 2.9f;
    HorizontalWall(VAO, ourShader, x_shift, y_shift + translate_Y_Lift, z_shift, len, ht, lbx, lby, lbz, texture);

    //lift inside back left wall
    lbx = 10.05, lby = 0.2f, lbz = 63.25f;
    len = 0.5, ht = 2.9f;
    HorizontalWall(VAO, ourShader, x_shift, y_shift + translate_Y_Lift, z_shift, len, ht, lbx, lby, lbz, texture);

    //lift inside back right wall
    lbx = 13.45, lby = 0.2f, lbz = 63.25f;
    len = 0.5, ht = 2.9f;
    HorizontalWall(VAO, ourShader, x_shift, y_shift + translate_Y_Lift, z_shift, len, ht, lbx, lby, lbz, texture);
    
    //====================================
    
    //lift inside left side front wall
    lbx = 10.05, lby = 0.2f, lbz = 59.55f;
    len = 0.5, ht = 2.9f;
    VerticalWall(VAO, ourShader, x_shift, y_shift + translate_Y_Lift, z_shift, len, ht, lbx, lby, lbz, texture);

    //lift inside right side front wall
    lbx = 13.75, lby = 0.2f, lbz = 59.55f;
    len = 0.5, ht = 2.9f;
    VerticalWall(VAO, ourShader, x_shift, y_shift + translate_Y_Lift, z_shift, len, ht, lbx, lby, lbz, texture);

    //lift inside left side back wall
    lbx = 10.05, lby = 0.2f, lbz = 62.95f;
    len = 0.5, ht = 2.9f;
    VerticalWall(VAO, ourShader, x_shift, y_shift + translate_Y_Lift, z_shift, len, ht, lbx, lby, lbz, texture);

    //lift inside right side back wall
    lbx = 13.75, lby = 0.2f, lbz = 62.95f;
    len = 0.5, ht = 2.9f;
    VerticalWall(VAO, ourShader, x_shift, y_shift + translate_Y_Lift, z_shift, len, ht, lbx, lby, lbz, texture);

    //Nicher door and 2 wall=============================================================
    //left wall
    lbx = 10.0, lby = 0.2f, lbz = 59.3f;
    len = 1.0, ht = 2.9f;
    HorizontalWall(VAO, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, texture);

    //right wall
    lbx = 13.0, lby = 0.2f, lbz = 59.3f;
    len = 1.0, ht = 2.9f;
    HorizontalWall(VAO, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, texture);

    //doors
    //left door
    lbx = 10.0, lby = 0.2f, lbz = 59.35f;
    len = 1.0, ht = 2.9f;
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = lbx + translate_X_Lift, y_sft = lby, z_sft = lbz;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, -0.1f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //right door
    lbx = 13.0, lby = 0.2f, lbz = 59.35f;
    len = 1.0, ht = 2.9f;
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = lbx - translate_X_Lift, y_sft = lby, z_sft = lbz;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, -0.1f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //uporer door and 2 wall=============================================================

    //side front wall
    lbx = 9.8, lby = 4.4+0.2f, lbz = 59.5f;
    len = 1.0, ht = 2.9f;
    VerticalWall(VAO, ourShader, x_shift, y_shift, z_shift , len, ht, lbx, lby, lbz, texture);

    //side back wall
    lbx = 9.8, lby = 4.4+0.2f, lbz = 62.5f;
    len = 1.0, ht = 2.9f;
    VerticalWall(VAO, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, texture);

    //doors
    //front door
    lbx = 9.85, lby = 4.4+0.2f, lbz = 60.5f;
    len = 1.0, ht = 2.9f;
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = lbx, y_sft = lby, z_sft = lbz - translate_Z_Lift;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1, ht, -1.0*len));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //back door
    lbx = 9.85, lby = 4.4+0.2f, lbz = 61.5f;
    len = 1.0, ht = 2.9f;
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = lbx, y_sft = lby, z_sft = lbz + translate_Z_Lift;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1, ht, -1.0 * len));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void FrontArchGen(unsigned int VAO, BezierCurveArch Main_Arch, BezierCurveArch Sub_Arch, BezierCurve Round_Piller, BezierCurve Piller_Border, Shader ourShader, float x_shift, float y_shift, float z_shift)
{
    //declaration
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 RS_translateMatrix, translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float lbx = 0.0, lby = 0.0, lbz = 0.0;

    //LEFT FRONT BALCONY
    //left box single arch
    float zz = 4.0-0.2;
    lbx = 0.0, lby = 0.0, lbz = 0.0;
    //Left_Single_Arch_Hori(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift, y_shift, z_shift);
    //Left_Single_Arch_Hori(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift, y_shift, z_shift+zz);
    lbx = 0.0, lby = 0.0, lbz = 0.0;
    //common arch
    for (int i = 0; i < 4; i++)
    {
        Common_Arch_Horizontal(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift+i*2.6, y_shift, z_shift);
        Common_Arch_Horizontal(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift+i*2.6, y_shift, z_shift+zz);
    }
    //right box single arch
    lbx = 0.0, lby = 0.0, lbz = 0.0;
    //Right_Single_Arch_Hori(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift, y_shift, z_shift);
    //Right_Single_Arch_Hori(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift, y_shift, z_shift+zz);

    //RIGHT FRONT BALCONY
    //left box single arch
    lbx = 0.0, lby = 0.0, lbz = 0.0;
    /*Left_Single_Arch_Hori(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift, y_shift, z_shift);
    Left_Single_Arch_Hori(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift, y_shift, z_shift + zz);*/
    lbx = 0.0, lby = 0.0, lbz = 0.0;
    //common arch
    float right_displace = 29.5;
    for (int i = 0; i < 4; i++)
    {
        Common_Arch_Horizontal(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift+ right_displace + i * 2.6, y_shift, z_shift);
        Common_Arch_Horizontal(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift+ right_displace + i * 2.6, y_shift, z_shift + zz);
    }
    //right box single arch
    lbx = 0.0, lby = 0.0, lbz = 0.0;
    //Right_Single_Arch_Hori(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift, y_shift, z_shift);
    //Right_Single_Arch_Hori(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift, y_shift, z_shift + zz);


}

void MidArchGen(unsigned int VAO, BezierCurveArch Main_Arch, BezierCurveArch Sub_Arch, BezierCurve Round_Piller, BezierCurve Piller_Border, Shader ourShader, float x_shift, float y_shift, float z_shift)
{
    //declaration
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 RS_translateMatrix, translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float lbx = 0.0, lby = 0.0, lbz = 0.0;

    //LEFT FRONT BALCONY
    //left box single arch
    float zz = 4.0 - 0.2;
    lbx = 0.0, lby = 0.0, lbz = 0.0;
    //Left_Single_Arch_Hori(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift, y_shift, z_shift);
    //Left_Single_Arch_Hori(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift, y_shift, z_shift+zz);
    lbx = -1.5, lby = 0.0, lbz = 25.5;

    //common arch
    for (int i = 0; i < 5; i++)
    {
        Common_Arch_Horizontal(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, lbx + i * 2.6, lby, lbz);
        //Common_Arch_Horizontal(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift + i * 2.6, y_shift, z_shift + zz);
    }
    //right box single arch
    lbx = 0.0, lby = 0.0, lbz = 0.0;
    //Right_Single_Arch_Hori(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift, y_shift, z_shift);
    //Right_Single_Arch_Hori(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift, y_shift, z_shift+zz);

    //RIGHT FRONT BALCONY
    //left box single arch
    lbx = 0.0, lby = 0.0, lbz = 0.0;
    /*Left_Single_Arch_Hori(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift, y_shift, z_shift);
    Left_Single_Arch_Hori(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift, y_shift, z_shift + zz);*/
    lbx = -1.5, lby = 0.0, lbz = 25.5;
    //common arch
    float right_displace = 29.5;
    for (int i = 0; i < 5; i++)
    {
        Common_Arch_Horizontal(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, lbx + right_displace + i * 2.6, lby, lbz);
        //Common_Arch_Horizontal(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift + right_displace + i * 2.6, y_shift, z_shift + zz);
    }
    //right box single arch
    lbx = 0.0, lby = 0.0, lbz = 0.0;
    //Right_Single_Arch_Hori(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift, y_shift, z_shift);
    //Right_Single_Arch_Hori(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift, y_shift, z_shift + zz);


}

void SideArchGen(unsigned int VAO, BezierCurveArch Main_Arch, BezierCurveArch Sub_Arch, BezierCurve Round_Piller, BezierCurve Piller_Border, Shader ourShader, float x_shift, float y_shift, float z_shift)
{
    //declaration
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 RS_translateMatrix, translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float lbx = 0.0, lby = 0.0, lbz = 0.0;

    //LEFT FRONT BALCONY
    //left box single arch
    float xx = 4.0 - 0.2;
    lbx = 0.0, lby = 0.0, lbz = 0.0;
    //Left_Single_Arch_Ver(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift, y_shift, z_shift);
    //Left_Single_Arch_Ver(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift, y_shift, z_shift+zz);
    lbx = 0.0, lby = 0.0, lbz = 0.0;
    //common arch
    for (int i = 0; i < 7; i++)
    {
        Common_Arch_Vertical(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift , y_shift, z_shift + i * 5.0);
        if (i < 3)
        {
            Common_Arch_Vertical(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift + xx, y_shift, z_shift + i * 5.0);
        }
    }
    //right box single arch
    lbx = 0.0, lby = 0.0, lbz = 0.0;
    //Right_Single_Arch_Ver(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift, y_shift, z_shift);
    //Right_Single_Arch_Ver(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift, y_shift, z_shift+zz);

    //RIGHT FRONT BALCONY
    //left box single arch
    lbx = 0.0, lby = 0.0, lbz = 0.0;
    /*Left_Single_Arch_Ver(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift, y_shift, z_shift);
    Left_Single_Arch_Ver(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift, y_shift, z_shift + zz);*/
    lbx = 0.0, lby = 0.0, lbz = 0.0;
    //common arch
    float right_displace = 51.0;
    for (int i = 0; i < 7; i++)
    {
        Common_Arch_Vertical(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift+ right_displace, y_shift, z_shift + i * 5.0);
        if (i < 3)
        {
            Common_Arch_Vertical(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift + right_displace + xx, y_shift, z_shift + i * 5.0);
        }
    }
    //right box single arch
    lbx = 0.0, lby = 0.0, lbz = 0.0;
    //Right_Single_Arch_Ver(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift, y_shift, z_shift);
    //Right_Single_Arch_Ver(VAO, Main_Arch, Sub_Arch, Round_Piller, Piller_Border, ourShader, x_shift, y_shift, z_shift + zz);


}


//General
void HorizontalWall(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, float len, float ht, float lbx, float lby, float lbz, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    float x_sft = lbx, y_sft = lby, z_sft = lbz;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, -0.2f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void VerticalWall(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, float len, float ht, float lbx, float lby, float lbz, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    float x_sft = lbx, y_sft = lby, z_sft = lbz;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, ht, -1.0f*len));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void GenFloor(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, float len, float width, float lbx, float lby, float lbz, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    //Floor
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, 0.2f, -1.0*width));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(1.0, 1.0, 1.0, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(1.0, 1.0, 1.0, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //box++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++END
}

void Box(unsigned int VAO1, unsigned int VAO2, Shader ourShader, float x_shift, float y_shift, float z_shift, float len, float width, float ht, float lbx, float lby, float lbz, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //fornt wall
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, -0.2f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO2);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //left wall---------------------------------------
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, ht, -1.0f * width));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO2);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //BACK wall-------------------------------------------------------
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift)); --
        x_sft = lbx, y_sft = lby, z_sft = lbz + width - 0.2;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, -0.2f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO2);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //RIGHT wall---------------------------------------
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = lbx + len - 0.2, y_sft = lby, z_sft = lbz;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, ht, -1.0f * width));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO2);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //top box
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = lbx + 0.1f, y_sft = (ht + lby) - 0.4f, z_sft = lbz + 0.1f;
    glBindTexture(GL_TEXTURE_2D, texture7);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len - 0.2, 0.2f, -1.0f * (width - 0.2f)));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(1.0, 1.0, 1.0, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(1.0, 1.0, 1.0, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO1);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //box++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++END

}

void FlatBox(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, float len, float width, float ht, float lbx, float lby, float lbz, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //fornt wall
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
        x_sft = lbx, y_sft = lby, z_sft = lbz;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, -0.2f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //left wall---------------------------------------
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, ht, -1.0f * width));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //BACK wall-------------------------------------------------------
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift)); --
        x_sft = lbx, y_sft = lby, z_sft = lbz + width - 0.2;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, -0.2f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //RIGHT wall---------------------------------------
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = lbx + len - 0.2, y_sft = lby, z_sft = lbz;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, ht, -1.0f * width));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //top box
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = lbx + 0.1f, y_sft = (ht + lby) - 0.2f, z_sft = lbz + 0.1f;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len - 0.2, 0.2f, -1.0f * (width - 0.2f)));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.0, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.0, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //box++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++END
}

void HoloBox(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, float len, float width, float ht, float lbx, float lby, float lbz, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //fornt wall
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, -0.2f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //left wall---------------------------------------
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, ht, -1.0f * width));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //BACK wall-------------------------------------------------------
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift)); --
        x_sft = lbx, y_sft = lby, z_sft = lbz + width - 0.2;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, -0.2f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //RIGHT wall---------------------------------------
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = lbx + len - 0.2, y_sft = lby, z_sft = lbz;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, ht, -1.0f * width));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //NO TOP BOX
    //box++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++END
}

//components===============
void Fan_and_switch(unsigned int VAO, BezierCurve Fan_Bati, BezierCurve Fan_Blade, BezierCurve Fan_Tube, Shader ourShader, float x_shift, float y_shift, float z_shift)
{
    if (isRotate1)
    {
        if (fanspeed1 < 12.0)
        {
            fanspeed1 += 0.4;
            rotateAxis_Y_Fan1 += fanspeed1;
            rotateAxis_Y_Fan1 = fmod(rotateAxis_Y_Fan1, 360);
            Fan1_ready = true;
        }
        else
        {
            rotateAxis_Y_Fan1 += fanspeed1;
            rotateAxis_Y_Fan1 = fmod(rotateAxis_Y_Fan1, 360);
        }
    }
    else
    {
        if (fanspeed1 > 0.0)
        {
            fanspeed1 -= 0.2;
            rotateAxis_Y_Fan1 += fanspeed1;
            rotateAxis_Y_Fan1 = fmod(rotateAxis_Y_Fan1, 360);
        }
        else
        {
            Fan1_ready = true;
        }
    }
    //declaration
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 RS_translateMatrix,translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float lbx = 0.0, lby = 0.0, lbz = 0.0;
    float len = 0.0, ht = 0.0f;
    float width = 0.0;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    float rsx = 0.0, rsy = 0.0 , rsz = 0.0;

    //FAN BATI+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //------CURVE---START
    lbx = 12.0, lby = 0.6, lbz = 59.0;
    len = 0.2, ht = 0.2f;
    width = 0.2;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 0.0, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy , -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f + rotateAxis_Y_Fan1), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    Fan_Bati.drawBezierCurve(ourShader, model);
    //CURVE---------END-------------------------------Curve

    //FAN BLADE+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //------CURVE---START
    lbx = 12.0, lby = 0.6, lbz = 59.0;
    len = 0.33, ht = 0.275f;
    width = 0.05;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.13, rsy = 0.0667, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    for (int i = 0; i < 3; i++)
    {
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f + i * 120.0f + rotateAxis_Y_Fan1), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
        model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * rotateXMatrix * rotateZMatrix * scaleMatrix;
        Fan_Blade.drawBezierCurve(ourShader, model);
    }
    //CURVE---------END----------------------------CURVE

    //FAN BLADE Tube CONNECTOR+++++++++++++++++++++++++++++++++++++++++++++++++++
    //------CURVE---START
    lbx = 12.0, lby = 0.6, lbz = 59.0;
    len = 0.0667, ht = 0.15f;
    width = 0.1;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 0.0667, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    for (int i = 0; i < 3; i++)
    {
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f + i * 120.0f + rotateAxis_Y_Fan1), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
        model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * rotateZMatrix * scaleMatrix;
        Fan_Tube.drawBezierCurve(ourShader, model);
    }
    //CURVE---------END-------------------CURVE

    //FAN RODE Tube CONNECTOR++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //------CURVE---START
    lbx = 12.0, lby = 0.6, lbz = 59.0;
    len = 0.1, ht = 0.15f;
    width = 0.1;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 0.0667, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    model = uni_translate * translateMatrix *  RS_translateMatrix * scaleMatrix;
    Fan_Tube.drawBezierCurve(ourShader, model);
    
    //CURVE---------END-------------------CURVE

}

void Main_Arch_Horizontal(unsigned int VAO, BezierCurveArch Main_Arch, BezierCurveArch Sub_Arch, BezierCurve Round_Piller, BezierCurve Piller_Border, Shader ourShader, float x_shift, float y_shift, float z_shift)
{
    //declaration
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 RS_translateMatrix, translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float lbx = 0.0, lby = 0.0, lbz = 0.0;
    float len = 0.0, ht = 0.0f;
    float width = 0.0;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    float rsx = 0.0, rsy = 0.0, rsz = 0.0;

    //Sobar same tai
    lbx = 17.5, lby = 0.4, lbz = 12.0;

    //piller border+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //------CURVE---START
    lbx = 17.5, lby = 0.4, lbz = 12.0;
    len = 0.4, ht = 0.2f;
    width = 0.4;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 1.3, rsy = 0.0, rsz = 0.1;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    Piller_Border.drawBezierCurve(ourShader, model);
    //CURVE---------END-------------------------------Curve

    //Round piller+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //------CURVE---START
    lbx = 17.5, lby = 0.4, lbz = 12.0;
    len = 0.25, ht = 2.7f;
    width = 0.25;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 1.3, rsy = 0.0, rsz = 0.1;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    Round_Piller.drawBezierCurve(ourShader, model);
    //CURVE---------END----------------------------CURVE

    //Main_arch+++++++++++++++++++++++++++++++++++++++++++++++++++
    //------CURVE---START
    lbx = 17.5, lby = 0.4, lbz = 12.0;
    len = 1.0, ht = 1.0f;
    width = 1.3;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 1.69, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    Main_Arch.drawBezierCurve(ourShader, model);
    //CURVE---------END-------------------CURVE

    //Sub_arch+++++++++++++++++++++++++++++++++++++++++++++++++++
    //------CURVE---START
    lbx = 17.5, lby = 0.4, lbz = 12.0;
    len = 1.0, ht = 0.5725;
    width = 0.75;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0, z_sft = 0.0;
    rsx = 0.0, rsy = 0.594 + 0.69, rsz = 0.55;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    Sub_Arch.drawBezierCurve(ourShader, model);
    //CURVE---------END-------------------CURVE

    //Main_arch+++++++++++++++++++++++++++++++++++++++++++++++++++SIDE****************
    //------CURVE---START
    float xx = 2.6, zz = 0.2;
    lbx = 17.5 + xx, lby = 0.4, lbz = 12.0 + zz;
    len = 1.0, ht = 1.0f;
    width = 1.3;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 1.69, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    Main_Arch.drawBezierCurve(ourShader, model);
    //CURVE---------END-------------------CURVE

    //Sub_arch+++++++++++++++++++++++++++++++++++++++++++++++++++
    //------CURVE---START
    lbx = 17.5 + xx, lby = 0.4, lbz = 12.0 + zz;
    len = 1.0, ht = 0.5725;
    width = 0.75;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0, z_sft = 0.0;
    rsx = 0.0, rsy = 0.594 + 0.69, rsz = 0.55;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    Sub_Arch.drawBezierCurve(ourShader, model);
    //CURVE---------END-------------------CURVE
}


void Common_Arch_Horizontal(unsigned int VAO, BezierCurveArch Main_Arch, BezierCurveArch Sub_Arch, BezierCurve Round_Piller, BezierCurve Piller_Border, Shader ourShader, float x_shift, float y_shift, float z_shift)
{
    //declaration
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 RS_translateMatrix, translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float lbx = 0.0, lby = 0.0, lbz = 0.0;
    float len = 0.0, ht = 0.0f;
    float width = 0.0;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    float rsx = 0.0, rsy = 0.0, rsz = 0.0;

    //Sobar same tai
    lbx = 17.5, lby = 0.4, lbz = 12.0;

    //piller border+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //------CURVE---START
    lbx = 17.5, lby = 0.4, lbz = 12.0;
    len = 0.4, ht = 0.2f;
    width = 0.4;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 1.3, rsy = 0.0, rsz = 0.1;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    Piller_Border.drawBezierCurve(ourShader, model);
    //CURVE---------END-------------------------------Curve

    //Round piller+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //------CURVE---START
    lbx = 17.5, lby = 0.4, lbz = 12.0;
    len = 0.25, ht = 2.7f;
    width = 0.25;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 1.3, rsy = 0.0, rsz = 0.1;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    Round_Piller.drawBezierCurve(ourShader, model);
    //CURVE---------END----------------------------CURVE

    //Main_arch+++++++++++++++++++++++++++++++++++++++++++++++++++
    //------CURVE---START
    lbx = 17.5, lby = 0.4, lbz = 12.0;
    len = 1.0, ht = 1.0f;
    width = 1.3;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 1.69, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    Main_Arch.drawBezierCurve(ourShader, model);
    //CURVE---------END-------------------CURVE

    ////Sub_arch+++++++++++++++++++++++++++++++++++++++++++++++++++
    ////------CURVE---START
    //lbx = 17.5, lby = 0.4, lbz =  12.0;
    //len = 1.0, ht = 0.5725;
    //width = 0.75;
    ////---------FN
    //x_sft = 0.0f, y_sft = 0.0, z_sft = 0.0;
    //rsx = 0.0, rsy = 0.594+0.69, rsz = 0.55;
    ////universal translate
    //uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    //RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    //x_sft = lbx, y_sft = lby, z_sft = lbz;
    //translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    //scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    //rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    //model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    //Sub_Arch.drawBezierCurve(ourShader, model);
    ////CURVE---------END-------------------CURVE

    //Main_arch+++++++++++++++++++++++++++++++++++++++++++++++++++SIDE****************
    //------CURVE---START
    float xx = 2.6, zz = 0.2;
    lbx = 17.5+xx, lby = 0.4, lbz = 12.0+zz;
    len = 1.0, ht = 1.0f;
    width = 1.3;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 1.69, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    Main_Arch.drawBezierCurve(ourShader, model);
    //CURVE---------END-------------------CURVE

    ////Sub_arch+++++++++++++++++++++++++++++++++++++++++++++++++++
    ////------CURVE---START
    //lbx = 17.5 + xx, lby = 0.4, lbz = 12.0 + zz;
    //len = 1.0, ht = 0.5725;
    //width = 0.75;
    ////---------FN
    //x_sft = 0.0f, y_sft = 0.0, z_sft = 0.0;
    //rsx = 0.0, rsy = 0.594 + 0.69, rsz = 0.55;
    ////universal translate
    //uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    //RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    //x_sft = lbx, y_sft = lby, z_sft = lbz;
    //translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    //scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    //rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    //model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    //Sub_Arch.drawBezierCurve(ourShader, model);
    ////CURVE---------END-------------------CURVE
}

void Common_Arch_Vertical(unsigned int VAO, BezierCurveArch Main_Arch, BezierCurveArch Sub_Arch, BezierCurve Round_Piller, BezierCurve Piller_Border, Shader ourShader, float x_shift, float y_shift, float z_shift)
{
    //declaration
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 RS_translateMatrix, translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float lbx = 0.0, lby = 0.0, lbz = 0.0;
    float len = 0.0, ht = 0.0f;
    float width = 0.0;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    float rsx = 0.0, rsy = 0.0, rsz = 0.0;

    //Sobar same tai
    lbx = 0.0, lby = 0.4, lbz = 0.0;

    //piller border+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //------CURVE---START
    lbx = 10.0, lby = 0.4, lbz = 21.5;
    len = 0.4, ht = 0.2f;
    width = 0.4;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0+0.1, rsy = 0.0, rsz = 0.1;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    Piller_Border.drawBezierCurve(ourShader, model);
    //CURVE---------END-------------------------------Curve

    //Round piller+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //------CURVE---START
    lbx = 10.0, lby = 0.4, lbz = 21.5;
    len = 0.25, ht = 2.7f;
    width = 0.25;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0+0.1, rsy = 0.0, rsz = 0.1;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    Round_Piller.drawBezierCurve(ourShader, model);
    //CURVE---------END----------------------------CURVE

    //Main_arch+++++++++++++++++++++++++++++++++++++++++++++++++++
    //------CURVE---START
    lbx = 10.0, lby = 0.4, lbz = 21.5;
    len = 1.0, ht = 1.0f;
    width = 1.3;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.2, rsy = 1.69, rsz = -1.2;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    Main_Arch.drawBezierCurve(ourShader, model);
    //CURVE---------END-------------------CURVE

    ////Sub_arch+++++++++++++++++++++++++++++++++++++++++++++++++++
    ////------CURVE---START
    //lbx = 10.0, lby = 0.4, lbz = 21.5;
    //len = 1.0, ht = 0.5725;
    //width = 0.75;
    ////---------FN
    //x_sft = 0.0f, y_sft = 0.0, z_sft = 0.0;
    //rsx = 0.2, rsy = 0.594 + 0.69, rsz = -0.65;
    ////universal translate
    //uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    //RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    //x_sft = lbx, y_sft = lby, z_sft = lbz;
    //translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    //scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    //rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    //model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    //Sub_Arch.drawBezierCurve(ourShader, model);
    ////CURVE---------END-------------------CURVE

    //Main_arch+++++++++++++++++++++++++++++++++++++++++++++++++++SIDE****************
    //------CURVE---START
    //lbx = 0.0, lby = 0.0, lbz = 0.0;
    float xx = 0.0, zz = 1.4;
    lbx = 10.0 + xx, lby = 0.4, lbz = 21.5 + zz;
    len = 1.0, ht = 1.0f;
    width = 1.3;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 1.69, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    Main_Arch.drawBezierCurve(ourShader, model);
    //CURVE---------END-------------------CURVE

    ////Sub_arch+++++++++++++++++++++++++++++++++++++++++++++++++++
    ////------CURVE---START
    ////lbx = 0.0, lby = 0.0, lbz = 0.0;
    //lbx = 10.0 + xx, lby = 0.4, lbz = 21.5 + zz;
    //len = 1.0, ht = 0.5725;
    //width = 0.75;
    ////---------FN
    //x_sft = 0.0f, y_sft = 0.0, z_sft = 0.0;
    //rsx = 0.0, rsy = 0.594 + 0.69, rsz = 0.55;
    ////universal translate
    //uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    //RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    //x_sft = lbx, y_sft = lby, z_sft = lbz;
    //translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    //scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    //rotateYMatrix = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    //model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    //Sub_Arch.drawBezierCurve(ourShader, model);
    ////CURVE---------END-------------------CURVE
}

void MinarGen(unsigned int VAO, BezierCurve Round_piller, BezierCurve circle, BezierCurve spike, BezierCurve border, Hexa Piller_Stand, Shader ourShader, float x_shift, float y_shift, float z_shift)
{
    //declaration
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 RS_translateMatrix, translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float lbx = 0.0, lby = 0.0, lbz = 0.0;
    float len = 0.0, ht = 0.0f;
    float width = 0.0;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    float rsx = 0.0, rsy = 0.0, rsz = 0.0;

    //Sobar same tai
    lbx = 0.0, lby = 0.4, lbz = 0.0;


    //piller border+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    len = 2.0, ht = 0.6f;
    width = 2.0;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 0.0, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    border.drawBezierCurve(ourShader, model);







    //piller stand+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    len = 2.0, ht = 5.0f;
    width = 2.0;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 0.2, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    Piller_Stand.drawBezierCurve(ourShader, model);








    //piller MID 2 border++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // //1
    len = 1.75, ht = 0.6f;
    width = 1.75;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 5.0, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    border.drawBezierCurve(ourShader, model);
    //piller MID 2 border+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
     // //2
    len = 2.0, ht = 0.6f;
    width = 2.0;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 5.2, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    border.drawBezierCurve(ourShader, model);









    //piller round+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    len = 1.4, ht = 3.0f;
    width = 1.4;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 5.3, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    Round_piller.drawBezierCurve(ourShader, model);
  



    //piller top MID 2 border++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// //1
    len = 1.6, ht = 0.6f;
    width = 1.6;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 8.3, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    border.drawBezierCurve(ourShader, model);
    //piller MID 2 border+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
     // //2
    len = 1.8, ht = 0.6f;
    width = 1.8;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 8.5, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    border.drawBezierCurve(ourShader, model);




    //RAILLING
    //piller round+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    len = 0.2, ht = 0.7f;
    width = 0.2;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 8.75, rsz = 0.8;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    for (int i = 0; i < 6; i++)
    {
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f+60*i), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
        model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
        Round_piller.drawBezierCurve(ourShader, model);
    }



    //piller top reverse 2 border+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
     // //2
    len = 1.8, ht = 0.6f;
    width = 1.8;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 9.4, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    border.drawBezierCurve(ourShader, model);
    //piller top reverse MID 2 border++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // //1
    len = 1.6, ht = 0.6f;
    width = 1.6;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 9.6, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    border.drawBezierCurve(ourShader, model);



    //piller circle+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    len = 1.0, ht = 1.0f;
    width = 1.0;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 9.8, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    circle.drawBezierCurve(ourShader, model);




    //piller spike+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //------CURVE---START
    //lbx = 0.0, lby = 0.4, lbz = 0.0;
    len = 0.2, ht = 0.8f;
    width = 0.2;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 11.3, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    spike.drawBezierCurve(ourShader, model);
    //CURVE---------END-------------------------------Curve



}
//-------------------===========

void small_tomb(unsigned int VAO, BezierCurve circle, BezierCurve spike, Shader ourShader, float x_shift, float y_shift, float z_shift)
{
    //declaration
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 RS_translateMatrix, translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float lbx = 0.0, lby = 0.0, lbz = 0.0;
    float len = 0.0, ht = 0.0f;
    float width = 0.0;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    float rsx = 0.0, rsy = 0.0, rsz = 0.0;

    //Sobar same tai
    lbx = 0.0, lby = 0.4, lbz = 0.0;


    //piller circle+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    len = 0.7, ht = 0.8f;
    width = 0.7;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 0.0, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    circle.drawBezierCurve(ourShader, model);




    //piller spike+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //------CURVE---START
    //lbx = 0.0, lby = 0.4, lbz = 0.0;
    len = 0.2, ht = 0.3f;
    width = 0.2;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 1.0, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    spike.drawBezierCurve(ourShader, model);
    //CURVE---------END-------------------------------Curve
}
void mid_tomb(unsigned int VAO, BezierCurve circle1, BezierCurve spike, Shader ourShader, float x_shift, float y_shift, float z_shift)
{
    //declaration
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 RS_translateMatrix, translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float lbx = 0.0, lby = 0.0, lbz = 0.0;
    float len = 0.0, ht = 0.0f;
    float width = 0.0;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    float rsx = 0.0, rsy = 0.0, rsz = 0.0;

    //Sobar same tai
    lbx = 0.0, lby = 0.4, lbz = 0.0;

    //piller circle+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    len = 3.0, ht = 3.0f;
    width = 3.0;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 0.0, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    circle1.drawBezierCurve(ourShader, model);

    //piller spike+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //------CURVE---START
    //lbx = 0.0, lby = 0.4, lbz = 0.0;
    len = 0.2, ht = 0.8f;
    width = 0.2;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 4.0, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    spike.drawBezierCurve(ourShader, model);
    //CURVE---------END-------------------------------Curve
}
void Big_tomb(unsigned int VAO, BezierCurve circle2, BezierCurve spike, Shader ourShader, float x_shift, float y_shift, float z_shift)
{
    //declaration
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 RS_translateMatrix, translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float lbx = 0.0, lby = 0.0, lbz = 0.0;
    float len = 0.0, ht = 0.0f;
    float width = 0.0;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    float rsx = 0.0, rsy = 0.0, rsz = 0.0;

    //Sobar same tai
    lbx = 0.0, lby = 0.4, lbz = 0.0;

    //piller circle+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    len = 7.0, ht = 7.0f;
    width = 7.0;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 0.0, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    circle2.drawBezierCurve(ourShader, model);

    //piller spike+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    //------CURVE---START
    //lbx = 0.0, lby = 0.4, lbz = 0.0;
    len = 0.2, ht = 0.8f;
    width = 0.2;
    //---------FN
    x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    rsx = 0.0, rsy = 11.0, rsz = 0.0;
    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    RS_translateMatrix = glm::translate(identityMatrix, glm::vec3(rsx, rsy, -1.0f * rsz));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len, ht, width));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));//MAIN Rotation
    model = uni_translate * translateMatrix * rotateYMatrix * RS_translateMatrix * scaleMatrix;
    spike.drawBezierCurve(ourShader, model);
    //CURVE---------END-------------------------------Curve
}




//Doors
void LeftFrontDoors(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;

    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(0.5 * x_shift, 0.5 * y_shift, -0.5 * z_shift));

    //grass layer----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.0f, 5.0f, -0.4f));


    if (isRotate1)
    {
        rotateAngle_Y = 75;
    }
    else
    {
        rotateAngle_Y = 0;
    }

    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f + rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = translateMatrix * rotateYMatrix *  scaleMatrix;
    model = uni_translate * model;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void RightFrontDoors(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;

    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(0.5 * x_shift, 0.5 * y_shift, -0.5 * z_shift));

    //grass layer----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(-4.0f, 5.0f, -0.4f));

    if (isRotate1)
    {
        rotateAngle_Y = -75;
    }
    else
    {
        rotateAngle_Y = 0;
    }
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f + rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = translateMatrix * rotateYMatrix * scaleMatrix;
    model = uni_translate * model;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}






// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {                 //Forward
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {                 //Backward
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {                 //Left
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {                 //Right
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)                   //Down
    {

        camera.ProcessKeyboard(DOWN, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)                   //Yaw ve+
    {
        camera.Proccess_Pitch_Yaw_Roll(0.0f, 3.0f, 0.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)                   //Yaw ve-
    {
        camera.Proccess_Pitch_Yaw_Roll(0.0f, -3.0f, 0.0f);
    }

    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)                   //Pitch ve+
    {
        camera.Proccess_Pitch_Yaw_Roll(3.0f, 0.0f, 0.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)                   //Pitch ve-
    {
        camera.Proccess_Pitch_Yaw_Roll(-3.0f, 0.0f, 0.0f);
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)                   //Roll ve+
    {
        camera.Proccess_Pitch_Yaw_Roll(0.0f, 0.0f, 4.0f);

    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)                   //Roll ve-
    {
        camera.Proccess_Pitch_Yaw_Roll(0.0f, 0.0f, -4.0f);

    }
    if (glfwGetKey(window, GLFW_KEY_I ) == GLFW_PRESS)                   //Rotate camera around a look at point
    {                                                                   //Right
        camera.RotateAroundLookAt(2.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_O ) == GLFW_PRESS)                   //Rotate camera around a look at point
    {                                                                   //Left
        camera.RotateAroundLookAt(-2.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)                   //Up
    {
        eyeY -= 2.5 * deltaTime;
        camera.ProcessKeyboard(UP, deltaTime);
    }

    //************Dynamic object************
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)                   //Rotate Fan
    {
        
    }
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)                   //Point Light Off
    {

    }
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)                   //Directional Light Off
    {

    }
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)                   //Spot Light Off
    {

    }
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)                   //Directional Light Off
    {

    }
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)                   //LIFT ON/OFF
    {
        if (lift_ready)
        {
            lift_ready = false;
            isLift ^= true;
            cout << isLift << endl;
            Sleep(100);
        }
   
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)                   //Spot Light Off
    {

    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)                   //Directional Light Off
    {

    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)                   //Spot Light Off
    {

    }
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)                   //Fan1 rotate
    {
        if (Fan1_ready)
        {
            Fan1_ready = false;
            isRotate1 ^= true;
            cout << isRotate1 << endl;
        }

    }
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)                   //Fan2 rotate
    {
        if (Fan2_ready)
        {
            Fan2_ready = false;
            isRotate2 ^= true;
            cout << isRotate2 << endl;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)                   //Specular Off
    {

    }
    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)                   //Specular Off
    {

    }
    if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)                   //Specular Off
    {

    }
    if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)                   //Specular Off
    {

    }

    //***************Lighting***************

    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)                   //Lighting On-Off
    {
        lightingOn ^= true;
        cout << lightingOn << endl;
        Sleep(100);
    }
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)                   //Ambient On
    {
        if (ambientOn == 0.0)
        {
            ambientOn = 1.0;
            pointLight.turnAmbientOn();
            spotLight.turnAmbientOn();
            //spotLight1.turnAmbientOn();
            //spotLight2.turnAmbientOn();
            directionalLight.turnAmbientOn();
        }
        else
        {
            ambientOn = 0.0;
            pointLight.turnAmbientOff();
            spotLight.turnAmbientOff();
            //spotLight1.turnAmbientOff();
            //spotLight2.turnAmbientOff();
            directionalLight.turnAmbientOff();
        }

    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)                   //Ambient Off
    {
        if (diffuseOn == 0.0)
        {
            diffuseOn = 1.0;
            pointLight.turnDiffuseOn();
            spotLight.turnDiffuseOn();
            //spotLight1.turnAmbientOn();
            //spotLight2.turnAmbientOn();
            directionalLight.turnDiffuseOn();
        }
        else
        {
            diffuseOn = 0.0;
            pointLight.turnDiffuseOff();
            spotLight.turnDiffuseOff();
            //spotLight1.turnAmbientOff();
            //spotLight2.turnAmbientOff();
            directionalLight.turnDiffuseOff();
        }
    }

    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)                   //Diffuse On
    {
        if (specularOn == 0.0)
        {
            specularOn = 1.0;
            pointLight.turnSpecularOn();
            spotLight.turnSpecularOn();
            //spotLight1.turnAmbientOn();
            //spotLight2.turnAmbientOn();
            directionalLight.turnSpecularOn();
        }
        else
        {
            specularOn = 0.0;
            pointLight.turnSpecularOff();
            spotLight.turnSpecularOff();
            //spotLight1.turnAmbientOff();
            //spotLight2.turnAmbientOff();
            directionalLight.turnSpecularOff();
        }

    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)                   //Point Light On
    {
        if (pointLightOn == 0)
        {
            pointLightOn = 1.0;
            pointLight.turnOn();
            Sleep(100);
        }
        else
        {
            pointLightOn = 0.0;
            pointLight.turnOff();
            Sleep(100);
        }

    }
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)                   //Directional Light On/off
    {
        if (directionalLightOn == 0)
        {
            directionalLightOn = 1.0;
            directionalLight.turnOn();
            Sleep(100);
        }
        else
        {
            directionalLightOn = 0.0;
            directionalLight.turnOff();
            Sleep(100);
        }

    }
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)                   //Spot Light On/off
    {
        if (spotLightOn == 0)
        {
            spotLightOn = 1.0;
            spotLight.turnOn();
            //spotLight1.turnOn();
            //spotLight2.turnOn();
            Sleep(100);
        }
        else
        {
            spotLightOn = 0.0;
            spotLight.turnOff();
            //spotLight1.turnOff();
            //spotLight2.turnOff();
            Sleep(100);
        }
        
    }
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)                   //Dark On-Off
    {
        dark ^= true;
        cout << dark << endl;
        Sleep(100);
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

