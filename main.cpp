
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
void FBsideWalk(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift,unsigned int texture);
void LRsideWalk(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);
void MainMosjidBase(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);
void Mosjid1stFloor(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);
void Mosjid2ndFloor(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);
void Ojubase(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);
void OjuKhana(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);
void Toilet(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);
void MainGate(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);
void Frontwing(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);
void Sidewing(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);
void MidGate(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);
void StairTower1(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);
void StairTower2(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);

//-----------------------------
void HorizontalWall(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift,  float len, float ht, float lbx, float lby, float lbz, unsigned int texture);
void VerticalWall(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, float len, float ht, float lbx, float lby, float lbz, unsigned int texture);
void GenFloor(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, float len, float width, float lbx, float lby, float lbz, unsigned int texture);
void Box(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, float len, float width, float ht, float lbx, float lby, float lbz, unsigned int texture);
void FlatBox(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, float len, float width, float ht, float lbx, float lby, float lbz, unsigned int texture);
void HoloBox(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, float len, float width, float ht, float lbx, float lby, float lbz, unsigned int texture);
//---------------------------------------
void MidsideWalk(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);
void ExtBase(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);
void MosjidBase(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);
void MidBase(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);
void TopBase(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);

//Pillar
void Pillar(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);
//Minar
void Minar(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);

//horizontal
void FrontHoriWall(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);
void Middle_Back_3_HoriWall_hieght_2_5(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);
void MidBack_6_HoriWall(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);
void Final_Back_HoriWall(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);

void HoriWall_top_wall_3_box(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);
void HoriWall_top_wall_1(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);
void HoriWall_top_wall_4(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);



//vertical
void VertiWall_14_2(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);
void VertiWall_3(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);
void VertiWall_1_height_2_5(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);

void VertiWall_top_wall_3(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);

//Doors
void LeftFrontDoors(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);
void RightFrontDoors(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture);

//AGER
void Floor(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift);

void MainFloor(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift);

void Sofa3(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift);
void Sofa21(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift);
void Sofa22(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift);
void TV(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift);
void Shelf(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift);
void Table(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift);
void Speaker(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift);

void Cup(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift);
void Lamp(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, int style);
void SideWall(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift);
void FBWall(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift);
void Roof(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift);
void Fan(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift);
void Ladder(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift);


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

// camera
Camera camera(glm::vec3(55.0f, 1.0f, -32.0f));//camera position
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
        glm::vec3(-0.95f, 0.7f, -2.7f),         //Directional Light
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
//style1-- 1X1
float ext = 0.0f;
float TXmin = 0.0f;
float TXmax = 1.0f+ext;
float TYmin = 0.0f;
float TYmax = 1.0f+ext;
//style2--- 1X2
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
//style4-- 10x20
float ext4 = 2.0f;
float TXmin4 = 0.0f;
float TXmax4 = 1.0f + 19.0;
float TYmin4 = 0.0f;
float TYmax4 = 1.0f + 9.0;

//style5-- 5x5
float ext5 = 2.0f;
float TXmin5 = 0.0f;
float TXmax5 = 1.0f + 4.0;
float TYmin5 = 0.0f;
float TYmax5 = 1.0f + 4.0;

//rotate
bool isRotate = false;
float fanspeed = 15.0f;

bool lightingOn = true;
float ambientOn = 1.0;
float diffuseOn = 1.0;
float specularOn = 1.0;
bool dark = false;

float directionalLightOn = 1.0;
float pointLightOn = 0.0;
float spotLightOn = 0.0;

//Texture variables
unsigned int texture0, texture1, texture2, texture3, texture4, texture5, texture6, texture7, texture8, texture9, texture10, texture11, texture12;

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


    //cube 10X20-----------------------------------------------------------------------------

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

    //cubex 10x20
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


    //cube 5X5-----------------------------------------------------------------------------
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

    //cubex 5x5
    unsigned int cubeVAO5, cubeVBO5, cubeEBO5;
    glGenVertexArrays(1, &cubeVAO5);
    glGenBuffers(1, &cubeVBO5);
    glGenBuffers(1, &cubeEBO5);

    glBindVertexArray(cubeVAO5);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO5);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices5), cube_vertices5, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO5);
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


    load_texture(texture1, "Grass_3.PNG", GL_RGBA);
    load_texture(texture2, "brickwall_1.jpg", GL_RGB);
    load_texture(texture3, "brickwall_2.jpg", GL_RGB);


    load_texture(texture4, "Blank_Wall_Pattern.jpg", GL_RGB);
    load_texture(texture5, "Mehrab_squared.jpg", GL_RGB);
    //load_texture(texture6, "Minar_Pattern.jpg", GL_RGB);
    load_texture(texture7, "pillardesign_squared.jpg", GL_RGB);
    load_texture(texture8, "SijdahPlace_squared.jpg", GL_RGB);
    load_texture(texture9, "WWin.PNG", GL_RGBA);
    //load_texture(texture10, "Wall_window_2.jpg", GL_RGB);

    load_texture(texture11, "leftdoor.jpg", GL_RGB);
    load_texture(texture12, "Right_door.jpg", GL_RGB);



    // render loop
    // -----------

    GLfloat controlpoints[] = {
        -1.0, 4.0, 0.0,
        //-5.0,2.0, 0.0,
        -1.0, 0.0, 0.0
    };

    BezierCurve bezier = BezierCurve(controlpoints, 6);

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
        //glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
        ////universal translate
        //uni_translate = glm::translate(identityMatrix, glm::vec3(0.5 * x_shift, 0.5 * y_shift, 0.5 * z_shift));
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
        //scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 2.0f, 2.0f));
        //model = uni_translate * translateMatrix * scaleMatrix;
        //bezier.drawBezierCurve(ourShader, model);
        ////testing end--------------------------------------------------------------eurve

        //Grass Field------------------------------
        x_shift = 0;
        y_shift = 0;
        z_shift = 0;
        Field(cubeVAO5, ourShader, x_shift, y_shift, z_shift, texture1);

        ////front balcony walk-----------------------------
        x_shift = 10;
        y_shift = 0;
        z_shift = 12;
        FBsideWalk(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture0);

        ////left side walk------------------------------------
        x_shift = 10;
        y_shift = 0;
        z_shift = 12;
        LRsideWalk(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture0);
        //right side walk
        x_shift = 61;
        y_shift = 0;
        z_shift = 12;
        LRsideWalk(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture0);

        //Main Mosjid+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        //Mosjid base
        x_shift = 15.5;
        y_shift = 0;
        z_shift = 43;
        MainMosjidBase(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture0);

        //Mosjid 1st floor-----------------------------------------------------------------------------------------
        x_shift = 0;
        y_shift = 0;
        z_shift = 0;
        Mosjid1stFloor(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture0);
        //Mosjid 2nd floor------------------------------------------------------------------------------------------
        x_shift = 0;
        y_shift = 0;
        z_shift = 0;
        Mosjid2ndFloor(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture0);


        ////ojukhana---------------------------------------------------
        ////ojukhana base
        ////left front
        //x_shift = 8.5;
        //y_shift = 0;
        //z_shift = 10.5;
        //Ojubase(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture0);
        //x_shift = 0;
        //y_shift = 0;
        //z_shift = 0;
        //OjuKhana(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture0);
        
        
        ////Toilet
        ////right front
        //x_shift = 59.5;
        //y_shift = 0;
        //z_shift = 10.5;
        //Ojubase(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture0);
        //x_shift = 59.5-8.5;
        //y_shift = 0;
        //z_shift = 10.5-10.5;
        //Toilet(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture0);


        ////Main Gate
        //x_shift = 0.0;
        //y_shift = 0.0;
        //z_shift = 0.0;
        //MainGate(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture0);


        ////front Left Wing
        //x_shift = 0.0;
        //y_shift = 0.0;
        //z_shift = 0.0;
        //Frontwing(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture0);
        ////front Right Wing
        //x_shift = 45.0- 15.5;
        //y_shift = 0.0;
        //z_shift = 10.0-10.0;
        //Frontwing(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture0);

        ////Mid main gate
        //x_shift = 0.0;
        //y_shift = 0.0;
        //z_shift = 0.0;
        //MidGate(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture0);


        ////side Left Wing
        //x_shift = 0.0;
        //y_shift = 0.0;
        //z_shift = 0.0;
        //Sidewing(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture0);
        ////side Right Wing
        //x_shift = 61.0-10.0;
        //y_shift = 0.0;
        //z_shift = 17.5-17.5;
        //Sidewing(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture0);


        //Stair tower
        //Left tower
        x_shift = 0.0;
        y_shift = 0.0;
        z_shift = 0.0;
        StairTower1(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture0 );

        //Right tower
        x_shift = 59.5 - 8.5;
        y_shift = 0.0;
        z_shift = 58 - 58;
        StairTower2(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture0);








        ////mid walk------------------------------------
        //x_shift = 47.5;
        //y_shift = 0;
        //z_shift = 13;
        //MidsideWalk(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture0);

        ////Ext base------------------------------------
        //x_shift = 20;
        //y_shift = 0;
        //z_shift = 30;
        //ExtBase(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture0);

        ////Mosjid base------------------------------------
        //x_shift = 21;
        //y_shift = 0;
        //z_shift = 31;
        //MosjidBase(cubeVAO4, ourShader, x_shift, y_shift, z_shift, texture8);

        ////Mid layer base------------------------------------
        //x_shift = 21;
        //y_shift = 1;
        //z_shift = 32;
        //MidBase(cubeVAO4, ourShader, x_shift, y_shift, z_shift, texture8);

        ////Top layer base------------------------------------
        //x_shift = 21;
        //y_shift = 1.6;
        //z_shift = 33;
        //TopBase(cubeVAO4, ourShader, x_shift, y_shift, z_shift, texture8);


        ////Pillers--------------------------------------------------------------------------------------------------
        ////front left piller
        //x_shift = 21.5;
        //y_shift = 2.2;
        //z_shift = 33.5;
        //Pillar(hexaVAO, ourShader, x_shift, y_shift, z_shift, texture0);

        ////front right piller
        //x_shift = 78.5;
        //y_shift = 2.2;
        //z_shift = 33.5;
        //Pillar(hexaVAO, ourShader, x_shift, y_shift, z_shift, texture0);

        ////front 2nd piller
        //x_shift = 38;
        //y_shift = 2.2;
        //z_shift = 33.5;
        //Pillar(hexaVAO, ourShader, x_shift, y_shift, z_shift, texture0);

        ////front 3rd piller
        //x_shift = 62;
        //y_shift = 2.2;
        //z_shift = 33.5;
        //Pillar(hexaVAO, ourShader, x_shift, y_shift, z_shift, texture0);


        ////left back piller
        //x_shift = 21.5;
        //y_shift = 2.2;
        //z_shift = 78.5;
        //Pillar(hexaVAO, ourShader, x_shift, y_shift, z_shift, texture0);

        ////left 1st piller
        //x_shift = 21.5;
        //y_shift = 2.2;
        //z_shift = 48.5;
        //Pillar(hexaVAO, ourShader, x_shift, y_shift, z_shift, texture0);

        ////left 2nd piller
        //x_shift = 21.5;
        //y_shift = 2.2;
        //z_shift = 63.5;
        //Pillar(hexaVAO, ourShader, x_shift, y_shift, z_shift, texture0);

        ////right back piller
        //x_shift = 78.5;
        //y_shift = 2.2;
        //z_shift = 78.5;
        //Pillar(hexaVAO, ourShader, x_shift, y_shift, z_shift, texture0);

        ////right 1st piller
        //x_shift = 78.5;
        //y_shift = 2.2;
        //z_shift = 48.5;
        //Pillar(hexaVAO, ourShader, x_shift, y_shift, z_shift, texture0);

        ////right 2nd piller
        //x_shift = 78.5;
        //y_shift = 2.2;
        //z_shift = 63.5;
        //Pillar(hexaVAO, ourShader, x_shift, y_shift, z_shift, texture0);


        ////Horizontal walls----------------------------------------------------------------------------------------------
        ////front left wall
        //x_shift = 26.6;
        //y_shift = 2.2;
        //z_shift = 38.6;
        //FrontHoriWall(cubeVAO3, ourShader, x_shift, y_shift, z_shift, texture9);

        ////front right wall
        //x_shift = 54;
        //y_shift = 2.2;
        //z_shift = 38.6;
        //FrontHoriWall(cubeVAO3, ourShader, x_shift, y_shift, z_shift, texture9);

        ////back horizontal 1---> left back 6
        //x_shift = 21;
        //y_shift = 2.2;
        //z_shift = 79;
        //MidBack_6_HoriWall(cubeVAO2, ourShader, x_shift, y_shift, z_shift, texture9);

        ////back horizontal 2--> left 6 len
        //x_shift = 35;
        //y_shift = 2.2;
        //z_shift = 79;
        //MidBack_6_HoriWall(cubeVAO2, ourShader, x_shift, y_shift, z_shift, texture9);

        ////back horizontal 3-> right 6 len
        //x_shift = 53;
        //y_shift = 2.2;
        //z_shift = 79;
        //MidBack_6_HoriWall(cubeVAO2, ourShader, x_shift, y_shift, z_shift, texture9);

        ////back horizontal 4 -> right back 6
        //x_shift = 67;
        //y_shift = 2.2;
        //z_shift = 79;
        //MidBack_6_HoriWall(cubeVAO2, ourShader, x_shift, y_shift, z_shift, texture9);

        ////back horizontal Imam place ->  3
        //x_shift = 47;
        //y_shift = 2.2;
        //z_shift = 81;
        //Middle_Back_3_HoriWall_hieght_2_5(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture5);

        ////back Final
        //x_shift = 21;
        //y_shift = 2.2;
        //z_shift = 85;
        //Final_Back_HoriWall(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture0);

        ////imam box top box wall
        //x_shift = 47;
        //y_shift = 2.2+5.0;
        //z_shift = 79;
        //HoriWall_top_wall_3_box(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture0);

        ////imam room top box wall
        //x_shift = 33;
        //y_shift = 2.2 + 5.0;
        //z_shift = 79;
        //HoriWall_top_wall_1(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture0);

        ////muyajjin room top box wall
        //x_shift = 65;
        //y_shift = 2.2 + 5.0;
        //z_shift = 79;
        //HoriWall_top_wall_1(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture0);

        ////Main gate top box wall
        //x_shift = 46;
        //y_shift = 2.2 + 5.0;
        //z_shift = 38.6;
        //HoriWall_top_wall_4(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture0);



        ////Vertical walls---------------------------------------------------------------------------------------------------
        ////left vertical 1-> left 14.2 len
        //x_shift = 26.6;
        //y_shift = 2.2;
        //z_shift = 50.6;
        //VertiWall_14_2(cubeVAO3, ourShader, x_shift, y_shift, z_shift, texture9);

        ////left vertical 2-> left 3 len
        //x_shift = 26.6;
        //y_shift = 2.2;
        //z_shift = 38.6;
        //VertiWall_3(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture9);

        ////right vertical 1-> right 14.2 len
        //x_shift = 73.4 - 0.4;
        //y_shift = 2.2;
        //z_shift = 50.6;
        //VertiWall_14_2(cubeVAO3, ourShader, x_shift, y_shift, z_shift, texture9);

        ////right vertical 2-> right 3 len
        //x_shift = 73.4 - 0.4;
        //y_shift = 2.2;
        //z_shift = 38.6;
        //VertiWall_3(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture9);

        ////left back(final) vertical 1-> right 3 len
        //x_shift = 21;
        //y_shift = 2.2;
        //z_shift = 79;
        //VertiWall_3(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture0);

        ////left 2nd back(final) vertical 2-> right 3 len
        //x_shift = 41;
        //y_shift = 2.2;
        //z_shift = 79;
        //VertiWall_3(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture0);

        ////right 2nd back(final) vertical 3-> right 3 len
        //x_shift = 59-0.4;
        //y_shift = 2.2;
        //z_shift = 79;
        //VertiWall_3(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture0);

        ////right back(final) vertical 3-> right 3 len
        //x_shift = 79-0.4;
        //y_shift = 2.2;
        //z_shift = 79;
        //VertiWall_3(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture0);

        ////left back imam box vertical 1-> right 1len
        //x_shift = 47;
        //y_shift = 2.2;
        //z_shift = 79;
        //VertiWall_1_height_2_5(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture0);

        ////right back imam box vertical 2-> right 1 len
        //x_shift = 53-0.4;
        //y_shift = 2.2;
        //z_shift = 79;
        //VertiWall_1_height_2_5(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture0);

        ////left side er top box wall
        //x_shift = 26.6;
        //y_shift = 2.2 + 5.0;
        //z_shift = 44.6;
        //VertiWall_top_wall_3(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture0);

        ////right side er top box wall
        //x_shift = 73.4-0.4;
        //y_shift = 2.2 + 5.0;
        //z_shift = 44.6;
        //VertiWall_top_wall_3(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture0);

        ////Doors-----------------------------------------------
        ////front left
        //x_shift = 46;
        //y_shift = 2.2;
        //z_shift = 38.6;
        //LeftFrontDoors(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture12);

        ////front right
        //x_shift = 54;
        //y_shift = 2.2;
        //z_shift = 38.6;
        //RightFrontDoors(cubeVAO, ourShader, x_shift, y_shift, z_shift, texture12);


        ////Minars--------------------------------------------------------------
        ////left minar
        //x_shift = 17;
        //y_shift = 0.2;
        //z_shift = 17;
        //Minar(hexaVAO, ourShader, x_shift, y_shift, z_shift, texture0);
        ////right minar
        //x_shift = 83;
        //y_shift = 0.2;
        //z_shift = 17;
        //Minar(hexaVAO, ourShader, x_shift, y_shift, z_shift, texture0);


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

    glDeleteVertexArrays(1, &cubeVAO5);
    glDeleteBuffers(1, &cubeVBO5);
    glDeleteBuffers(1, &cubeEBO5);


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

void FBsideWalk(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;

    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3( x_shift, y_shift, -1.0 * z_shift));

    //grass layer----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(55.0f, 0.2f, -4.0f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void LRsideWalk(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;

    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3( x_shift, y_shift, -1.0f * z_shift));

    //grass layer----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.0f, 0.2f, -55.0f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
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

void MainMosjidBase(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;

    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));

    //grass layer----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(44.0f, 0.2f, -25.0f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}


void Mosjid1stFloor(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
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
    HoloBox(VAO, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture);
    //roof mid left
    //(ht + lby) - 0.2f,
    lbx = 15.7, lby = (1.7f + 2.7f + 0.2f) - 0.2f, lbz = 51.0f;
    len = 16.8, width = 10.0f;
    GenFloor(VAO, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture);
    //roof mid right
    //(ht + lby) - 0.2f,
    lbx = 42.5, lby = (1.7f + 2.7f + 0.2f) - 0.2f, lbz = 51.0f;
    len = 16.8, width = 10.0f;
    GenFloor(VAO, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture);
    //roof front
    //(ht + lby) - 0.2f,
    lbx = 15.7, lby = (1.7f + 2.7f + 0.2f) - 0.2f, lbz = 43.2f;
    len = 43.6, width = 7.8f;
    GenFloor(VAO, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture);
    //roof back
    //(ht + lby) - 0.2f,
    lbx = 15.7, lby = (1.7f + 2.7f + 0.2f) - 0.2f, lbz = 61.0f;
    len = 43.6, width = 6.8f;
    GenFloor(VAO, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture);


    //front left wall-----------------+++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 15.5, lby = 0.2f, lbz = 43.0f;
    len = 8.5, ht = 2.7f;
    HorizontalWall(VAO, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, texture);

    //front mid left wall
    lbx = 27.0, lby = 0.2f, lbz = 43.0f;
    len = 7.5, ht = 2.7f;
    HorizontalWall(VAO, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, texture);
    //front mid right wall
    lbx = 40.5, lby = 0.2f, lbz = 43.0f;
    len = 7.5, ht = 2.7f;
    HorizontalWall(VAO, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, texture);
    //front right wall
    lbx = 51.0, lby = 0.2f, lbz = 43.0f;
    len = 8.5, ht = 2.7f;
    HorizontalWall(VAO, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, texture);

    //back left wall--------------------
    lbx = 15.5, lby = 0.2f, lbz = 67.8f;
    len = 20.5, ht = 2.7f;
    HorizontalWall(VAO, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, texture);

    //back right wall
    lbx = 39.0, lby = 0.2f, lbz = 67.8f;
    len = 20.5, ht = 2.7f;
    HorizontalWall(VAO, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, texture);

    //right side front wall-----------------+++++++++++++++++++++++++++++++++++++
    lbx = 15.5, lby = 0.2f, lbz = 43.0f;
    len = 11.0, ht = 2.7f;
    VerticalWall(VAO, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, texture);
    //right side back wall
    lbx = 15.5, lby = 0.2f, lbz = 58.0f;
    len = 10.0, ht = 2.7f;
    VerticalWall(VAO, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, texture);

    //left side front wall-----------------
    lbx = 59.3, lby = 0.2f, lbz = 43.0f;
    len = 11.0, ht = 2.7f;
    VerticalWall(VAO, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, texture);

    //left side back wall
    lbx = 59.3, lby = 0.2f, lbz = 58.0f;
    len = 10.0, ht = 2.7f;
    VerticalWall(VAO, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, texture);

    //imam place=====================
    //left wall
    lbx = 35.8, lby = 0.2f, lbz = 67.8f;
    len = 2.0, ht = 2.7f;
    VerticalWall(VAO, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, texture);
    //right wall
    lbx = 39.0, lby = 0.2f, lbz = 67.8f;
    len = 2.0, ht = 2.7f;
    VerticalWall(VAO, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, texture);
    //back wall
    lbx = 35.8, lby = 0.2f, lbz = 69.8f;
    len = 3.4, ht = 2.7f;
    HorizontalWall(VAO, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, texture);
    //top box
    lbx = 35.8, lby = 2.7f+0.2f, lbz = 67.8f;
    len = 3.4, ht = 1.0f;
    width = 2.2;
    Box(VAO, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture);
}

void Mosjid2ndFloor(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
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
    HoloBox(VAO, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture);
    //roof Front
    //(ht + lby) - 0.4f,
    lbx = 15.7, lby = (1.8f + 6.8f + 0.2f) - 0.4f, lbz = 45.2f;
    len = 43.6, width = 6.3f;
    GenFloor(VAO, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture);
    //roof mid left
    //(ht + lby) - 0.4f,
    lbx = 15.7, lby = (1.8f + 6.8f + 0.2f) - 0.4f, lbz = 51.5;
    len = 17.3, width = 9.0f;
    GenFloor(VAO, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture);
    //roof mid right
    //(ht + lby) - 0.4f,
    lbx = 42, lby = (1.8f + 6.8f + 0.2f) - 0.4f, lbz = 51.5;
    len = 17.3, width = 9.0f;
    GenFloor(VAO, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture);
    //roof back
    //(ht + lby) - 0.4f,
    lbx = 15.7, lby = (1.8f + 6.8f + 0.2f) - 0.4f, lbz = 60.5f;
    len = 43.6, width = 6.3f;
    GenFloor(VAO, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture);

    //front left wall-----------------+++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 15.5, lby = 0.2 + 2.7 + 1.9 - 0.2, lbz = 45.0;
    len = 8.5, ht = 2.7f;
    HorizontalWall(VAO, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, texture);

    //front mid wall
    lbx = 27.0, lby = 0.2 + 2.7 + 1.9 - 0.2, lbz = 45.0;
    len = 21, ht = 2.7f;
    HorizontalWall(VAO, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, texture);
    //front right wall
    lbx = 51.0, lby = 0.2 + 2.7 + 1.9 - 0.2, lbz = 45.0;
    len = 8.5, ht = 2.7f;
    HorizontalWall(VAO, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, texture);

    //back left wall--------------------
    lbx = 15.5, lby = 0.2 + 2.7 + 1.9 - 0.2, lbz = 66.8;
    len = 8.5, ht = 2.7f;
    HorizontalWall(VAO, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, texture);

    //back MID wall--------------------
    lbx = 27.0, lby = 0.2 + 2.7 + 1.9 - 0.2, lbz = 66.8;
    len = 21.0, ht = 2.7f;
    HorizontalWall(VAO, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, texture);

    //back right wall
    lbx = 51.0, lby = 0.2 + 2.7 + 1.9 - 0.2, lbz = 66.8;
    len = 8.5, ht = 2.7f;
    HorizontalWall(VAO, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, texture);

    //right side front wall-----------------+++++++++++++++++++++++++++++++++++++
    lbx = 15.5, lby = 0.2 + 2.7 + 1.9 - 0.2, lbz = 45.0;
    len = 15.0, ht = 2.7f;
    VerticalWall(VAO, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, texture);
    //right side back wall
    lbx = 15.5, lby = 0.2 + 2.7 + 1.9 - 0.2, lbz = 63.0;
    len = 4.0, ht = 2.7f;
    VerticalWall(VAO, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, texture);

    //left side front wall-----------------
    lbx = 59.3, lby = 0.2 + 2.7 + 1.9 - 0.2, lbz = 45.0f;
    len = 15.0, ht = 2.7f;
    VerticalWall(VAO, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, texture);

    //left side back wall
    lbx = 59.3, lby = 0.2 + 2.7 + 1.9 - 0.2, lbz = 63.0f;
    len = 4.0, ht = 2.7f;
    VerticalWall(VAO, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, texture);


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

void MainGate(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;


    //front left box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    float lbx = 30.0f, lby = 0.2f, lbz = 11.0f;
    float len = 2.0, ht = 4.25;
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
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, ht, -1.0f * len));
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
    x_sft = lbx, y_sft = lby, z_sft = lbz +len - 0.2;
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
    x_sft = lbx +len-0.2, y_sft = lby , z_sft = lbz;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, ht, -1.0f * len));
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
    x_sft = lbx + 0.1f, y_sft = (ht+lby) -0.4f, z_sft = lbz + 0.1f;
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture
    translateMatrix = glm::translate(identityMatrix, glm::vec3(x_sft, y_sft, -1.0f * z_sft));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len-0.2, 0.2f, -1.0f * (len-0.2f)));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.0, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.0, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //box++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++END

    //back left box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 30.0f, lby = 0.2f, lbz = 15.0f;
    len = 2.0, ht = 4.25;
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
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, ht, -1.0f * len));
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
        x_sft = lbx, y_sft = lby, z_sft = lbz + len - 0.2;
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
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, ht, -1.0f * len));
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
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len - 0.2, 0.2f, -1.0f * (len - 0.2f)));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.0, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.0, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //box++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++END


    //front right box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 43.0f, lby = 0.2f, lbz = 11.0f;
    len = 2.0, ht = 4.25;
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
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, ht, -1.0f * len));
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
        x_sft = lbx, y_sft = lby, z_sft = lbz + len - 0.2;
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
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, ht, -1.0f * len));
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
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len - 0.2, 0.2f, -1.0f * (len - 0.2f)));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.0, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.0, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //box++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++END

    //back right box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 43.0f, lby = 0.2f, lbz = 15.0f;
    len = 2.0, ht = 4.25;
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
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, ht, -1.0f * len));
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
        x_sft = lbx, y_sft = lby, z_sft = lbz + len - 0.2;
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
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, ht, -1.0f * len));
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
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len - 0.2, 0.2f, -1.0f * (len - 0.2f)));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.0, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.0, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //box++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++END

    //Mid Main box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 34.0, lby = 3.0f + 0.2f, lbz = 10.5f;
    len = 7.0, ht = 1.5;
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
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, ht, -1.0f * len));
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
        x_sft = lbx, y_sft = lby, z_sft = lbz + len - 0.2;
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
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, ht, -1.0f * len));
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
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len - 0.2, 0.2f, -1.0f * (len - 0.2f)));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.0, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.0, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //box++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++END
    
    //Mid Main gate front left box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 34.0, lby = 0.2f, lbz = 10.5f;
    len = 1.75, ht = 3.0;
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
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, ht, -1.0f * len));
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
        x_sft = lbx, y_sft = lby, z_sft = lbz + len - 0.2;
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
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, ht, -1.0f * len));
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
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len - 0.2, 0.2f, -1.0f * (len - 0.2f)));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.0, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.0, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //box++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++END

    //Mid Main gate back left box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 34.0, lby = 0.2f, lbz = 15.75f;
    len = 1.75, ht = 3.0;
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
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, ht, -1.0f * len));
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
        x_sft = lbx, y_sft = lby, z_sft = lbz + len - 0.2;
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
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, ht, -1.0f * len));
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
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len - 0.2, 0.2f, -1.0f * (len - 0.2f)));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.0, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.0, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //box++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++END

    //Mid Main gate front right box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 39.25, lby = 0.2f, lbz = 10.5f;
    len = 1.75, ht = 3.0;
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
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, ht, -1.0f * len));
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
        x_sft = lbx, y_sft = lby, z_sft = lbz + len - 0.2;
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
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, ht, -1.0f * len));
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
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len - 0.2, 0.2f, -1.0f * (len - 0.2f)));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.0, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.0, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //box++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++END


    //Mid Main gate back right box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 39.25, lby = 0.2f, lbz = 15.75;
    len = 1.75, ht = 3.0;
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
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, ht, -1.0f * len));
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
        x_sft = lbx, y_sft = lby, z_sft = lbz + len - 0.2;
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
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, ht, -1.0f * len));
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
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len - 0.2, 0.2f, -1.0f * (len - 0.2f)));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.0, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.0, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //box++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++END

    //left mid wing box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 30, lby = 2.7f + 0.2f, lbz = 11.5f;
    len = 4.0f, ht = 1.0f;
    float width = 5.0;
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

    //right mid wing box-------------------------------------------------------
        //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 41, lby = 2.7f + 0.2f, lbz = 11.5f;
    len = 4.0f, ht = 1.0f;
    width = 5.0;
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

}

void Frontwing(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    //front left box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    float lbx = 15.5, lby = 2.7f + 0.2f, lbz = 12.0f;
    float len = 14.5, width = 4.0, ht = 1.0f;
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
}

void Sidewing(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;


    //front left box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    float lbx = 10.0, lby = 2.7f + 0.2f, lbz = 17.5f;
    float len = 4.0, width = 40.5, ht = 1.0f;
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
}

void MidGate(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;
    float x_sft = 0.0f, y_sft = 0.0f, z_sft = 0.0f;
    //front left box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    float lbx = 31.5f, lby = 0.2f, lbz = 35.5f;
    float len = 2.0, ht = 5.0;
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
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, ht, -1.0f * len));
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
        x_sft = lbx, y_sft = lby, z_sft = lbz + len - 0.2;
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
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, ht, -1.0f * len));
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
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len - 0.2, 0.2f, -1.0f * (len - 0.2f)));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.0, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.0, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //box++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++END


    //front right box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 41.5f, lby = 0.2f, lbz = 35.5f;
    len = 2.0, ht = 5.0;
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
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, ht, -1.0f * len));
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
        x_sft = lbx, y_sft = lby, z_sft = lbz + len - 0.2;
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
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, ht, -1.0f * len));
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
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(len - 0.2, 0.2f, -1.0f * (len - 0.2f)));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.0, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.0, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //box++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++END

    //Mid Gate main box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
     lbx = 32.0, lby = 2.7f + 0.2f, lbz = 36.0f;
     len = 11.0, ht = 1.9f;
     float width = 7.0;
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

    //Left wing_+_+_+_+_+
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 14.0, lby = 2.7f + 0.2f, lbz = 37.5f;
    len = 18, ht = 1.0f;
    width = 4.0;
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

    //right wing_+_+_+_+_+
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 43.0, lby = 2.7f + 0.2f, lbz = 37.5f;
    len = 18, ht = 1.0f;
    width = 4.0;
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
    Box(VAO, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture);

    //back left box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 8.5f, lby = 0.2f, lbz = 63.5f;
    len = 1.5, ht = 8.2;
    width = len;
    Box(VAO, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture);

    //front right box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 14.0, lby = 0.2f, lbz = 58.0f;
    len = 1.5, ht = 8.2;
    width = len;
    Box(VAO, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture);

    //back right box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 14.0, lby = 0.2f, lbz = 63.5f;
    len = 1.5, ht = 8.2;
    width = len;
    Box(VAO, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture);

    //main box tower-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 8.5, lby = 6.8f + 0.2f, lbz = 58.0f;
    len = 7.0, ht = 1.0f;
    width = 7.0;
    Box(VAO, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture);

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
    Box(VAO, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture);

    //back left box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 8.5f, lby = 0.2f, lbz = 63.5f;
    len = 1.5, ht = 8.2;
    width = len;
    Box(VAO, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture);

    //front right box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 14.0, lby = 0.2f, lbz = 58.0f;
    len = 1.5, ht = 8.2;
    width = len;
    Box(VAO, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture);

    //back right box-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 14.0, lby = 0.2f, lbz = 63.5f;
    len = 1.5, ht = 8.2;
    width = len;
    Box(VAO, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture);

    //main box tower-------------------------------------------------------
    //box+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    lbx = 8.5, lby = 6.8f + 0.2f, lbz = 58.0f;
    len = 7.0, ht = 1.0f;
    width = 7.0;
    Box(VAO, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture);

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

    //LIFT FLOOR
    //4.4 e 2nd floor
    //4.2 plus korte hobe
    lbx = 10.05, lby = 0.2, lbz = 59.55f;
    len = 3.9;
    width = 3.9;
    GenFloor(VAO, ourShader, x_shift, y_shift, z_shift, len, width, lbx, lby, lbz, texture);
    //Lift roof box
    lbx = 10.05, lby = 2.2, lbz = 59.55f;
    len = 3.9, ht = 1.0f;
    width = 3.9;
    FlatBox(VAO, ourShader, x_shift, y_shift, z_shift, len, width, ht, lbx, lby, lbz, texture);

    //lift inside front left wall
    lbx = 10.05, lby = 0.2f, lbz = 59.55f;
    len = 0.5, ht = 2.9f;
    HorizontalWall(VAO, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, texture);

    //lift inside front right wall
    lbx = 13.45, lby = 0.2f, lbz = 59.55f;
    len = 0.5, ht = 2.9f;
    HorizontalWall(VAO, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, texture);

    //lift inside back left wall
    lbx = 10.05, lby = 0.2f, lbz = 63.25f;
    len = 0.5, ht = 2.9f;
    HorizontalWall(VAO, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, texture);

    //lift inside back right wall
    lbx = 13.45, lby = 0.2f, lbz = 63.25f;
    len = 0.5, ht = 2.9f;
    HorizontalWall(VAO, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, texture);
    
    //====================================
    
    //lift inside left side front wall
    lbx = 10.05, lby = 0.2f, lbz = 59.55f;
    len = 0.5, ht = 2.9f;
    VerticalWall(VAO, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, texture);

    //lift inside right side front wall
    lbx = 13.75, lby = 0.2f, lbz = 59.55f;
    len = 0.5, ht = 2.9f;
    VerticalWall(VAO, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, texture);

    //lift inside left side back wall
    lbx = 10.05, lby = 0.2f, lbz = 62.95f;
    len = 0.5, ht = 2.9f;
    VerticalWall(VAO, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, texture);

    //lift inside right side back wall
    lbx = 13.75, lby = 0.2f, lbz = 62.95f;
    len = 0.5, ht = 2.9f;
    VerticalWall(VAO, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, texture);

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
    lbx = 11.0, lby = 0.2f, lbz = 59.35f;
    len = 1.0, ht = 2.9f;
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
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
    lbx = 12.0, lby = 0.2f, lbz = 59.35f;
    len = 1.0, ht = 2.9f;
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
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
    VerticalWall(VAO, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, texture);

    //side back wall
    lbx = 9.8, lby = 4.4+0.2f, lbz = 62.5f;
    len = 1.0, ht = 2.9f;
    VerticalWall(VAO, ourShader, x_shift, y_shift, z_shift, len, ht, lbx, lby, lbz, texture);

    //doors
    //front door
    lbx = 9.85, lby = 4.4+0.2f, lbz = 60.5f;
    len = 1.0, ht = 2.9f;
    uni_translate = glm::translate(identityMatrix, glm::vec3(x_shift, y_shift, -1.0f * z_shift));
    x_sft = lbx, y_sft = lby, z_sft = lbz;
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
    x_sft = lbx, y_sft = lby, z_sft = lbz;
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
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.0, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.0, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    //box++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++END
}

void Box(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, float len, float width, float ht, float lbx, float lby, float lbz, unsigned int texture = texture0)
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




void MidsideWalk(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;

    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(0.5 * x_shift, 0.5 * y_shift, -0.5 * z_shift));

    //grass layer----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.0f, 0.4f, -18.0f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void ExtBase(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;

    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(0.5 * x_shift, 0.5 * y_shift, -0.5 * z_shift));

    //grass layer----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(60.0f, 0.3f, -56.0f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void MosjidBase(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;

    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(0.5 * x_shift, 0.5 * y_shift, -0.5 * z_shift));

    //grass layer----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(58.0f, 1.0f, -54.0f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void MidBase(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;

    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(0.5 * x_shift, 0.5 * y_shift, -0.5 * z_shift));

    //grass layer----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(58.0f, 0.6f, -53.0f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void TopBase(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;

    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(0.5 * x_shift, 0.5 * y_shift, -0.5 * z_shift));

    //grass layer----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(58.0f, 0.6f, -52.0f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

//Pillar-------------------------------------------------------

void Pillar(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;

    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(0.5 * x_shift, 0.5 * y_shift, -0.5 * z_shift));

    //bottom layer1----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture7);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25f, 0.1f, 0.25f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 72, GL_UNSIGNED_INT, 0);

    //bottom layer2----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture7);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.05f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, 0.1f, 0.2f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.5, 0.5, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.5, 0.5, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 72, GL_UNSIGNED_INT, 0);

    //mid piller----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture7);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.1f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.15f, 3.0f, 0.15f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.5, 0.5, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.5, 0.5, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 72, GL_UNSIGNED_INT, 0);

    //top layer1----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture7);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 1.6f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.183f, 0.1f, 0.183f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.5, 0.5, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.5, 0.5, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 72, GL_UNSIGNED_INT, 0);

    //top layer2----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture7);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 1.65f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.216f, 0.1f, 0.216f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.5, 0.5, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.5, 0.5, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 72, GL_UNSIGNED_INT, 0);

    //top layer3----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture7);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 1.7f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25f, 0.1f, 0.25f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.5, 0.5, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.5, 0.5, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 72, GL_UNSIGNED_INT, 0);

    //top piller----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture7);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 1.75f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.125f, 1.0f, 0.125f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.5, 0.5, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.5, 0.5, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 72, GL_UNSIGNED_INT, 0);



}

//Minars
void Minar(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;

    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(0.5 * x_shift, 0.5 * y_shift, -0.5 * z_shift));

    //bottom layer1----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture7);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(4*0.25f, 0.1f, 4*0.25f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 72, GL_UNSIGNED_INT, 0);

    //bottom layer2----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture7);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.05f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(4 * 0.2f, 0.1f, 4 * 0.2f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 72, GL_UNSIGNED_INT, 0);

    //mid piller----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture7);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.1f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(4 * 0.15f, 4 *3.0f, 4 * 0.15f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 72, GL_UNSIGNED_INT, 0);

    //top layer1----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture7);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 6.1f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(4 * 0.183f, 0.1f, 4 * 0.183f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 72, GL_UNSIGNED_INT, 0);

    //top layer2----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture7);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 6.15f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(4 * 0.216f, 0.1f, 4 * 0.216f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 72, GL_UNSIGNED_INT, 0);

    //top layer3----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture7);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 6.2f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(4 * 0.25f, 0.1f, 4 * 0.25f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 72, GL_UNSIGNED_INT, 0);

    //top piller----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture7);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 6.25f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(4 * 0.125f, 4*1.0f, 4 * 0.125f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 72, GL_UNSIGNED_INT, 0);

    //top railing----------------------------------------------------------------
    for (int i = 0; i < 6; i++)
    {
        glBindTexture(GL_TEXTURE_2D, texture7);//bindtexture

        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f + i*60.0f ), glm::vec3(0.0f, 1.0f, 0.0f));

        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 8.25f, 0.4f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, 1.0f, 0.05f));
        model = rotateYMatrix * translateMatrix * scaleMatrix;
        model = uni_translate * model;
        ourShader.setMat4("model", model);
        //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
        ourShader.setVec4("material.ambient", glm::vec4(0.5, 0.5, 0.8, 1.0f));
        ourShader.setVec4("material.diffuse", glm::vec4(0.5, 0.5, 0.8, 1.0f));
        ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
        ourShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 72, GL_UNSIGNED_INT, 0);
    }

    //top top layer1----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture7);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 8.75f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(4 * 0.183f, 0.1f, 4 * 0.183f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 72, GL_UNSIGNED_INT, 0);

    //top top layer2----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture7);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 8.80f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(4 * 0.216f, 0.1f, 4 * 0.216f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 72, GL_UNSIGNED_INT, 0);

    //top top layer3----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture7);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 8.85f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(4 * 0.216f, 2.0f , 4 * 0.216f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 72, GL_UNSIGNED_INT, 0);

}


//Horizontal walls---------------------------------------------------
void FrontHoriWall(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;

    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(0.5 * x_shift, 0.5 * y_shift, -0.5 * z_shift));

    //grass layer----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(19.4f, 7.0f, -0.4f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void Middle_Back_3_HoriWall_hieght_2_5(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;

    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(0.5 * x_shift, 0.5 * y_shift, -0.5 * z_shift));

    //grass layer----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(6.0f, 5.0f, -0.4f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void MidBack_6_HoriWall(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;

    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(0.5 * x_shift, 0.5 * y_shift, -0.5 * z_shift));

    //grass layer----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(12.0f, 7.0f, -0.4f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void Final_Back_HoriWall(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;

    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(0.5 * x_shift, 0.5 * y_shift, -0.5 * z_shift));

    //grass layer----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(58.0f, 7.0f, (-1.0f)* - 0.4f));//bitore anlam.
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void HoriWall_top_wall_3_box(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;

    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(0.5 * x_shift, 0.5 * y_shift, -0.5 * z_shift));

    //grass layer----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(6.0f, 2.0f, -2.0f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void HoriWall_top_wall_1(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;

    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(0.5 * x_shift, 0.5 * y_shift, -0.5 * z_shift));

    //grass layer----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 2.0f, -0.4f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void HoriWall_top_wall_4(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;

    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(0.5 * x_shift, 0.5 * y_shift, -0.5 * z_shift));

    //grass layer----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(8.0f, 2.0f, -0.4f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

//Vertical walls---------------------------------------------------------------
void VertiWall_14_2(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;

    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(0.5 * x_shift, 0.5 * y_shift, -0.5 * z_shift));

    //grass layer----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4f, 7.0f, -28.4f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void VertiWall_3(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;

    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(0.5 * x_shift, 0.5 * y_shift, -0.5 * z_shift));

    //grass layer----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4f, 7.0f, -6.0f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void VertiWall_1_height_2_5(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;

    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(0.5 * x_shift, 0.5 * y_shift, -0.5 * z_shift));

    //grass layer----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4f, 5.0f, -2.0f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void VertiWall_top_wall_3(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift, unsigned int texture = texture0)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;

    //universal translate
    uni_translate = glm::translate(identityMatrix, glm::vec3(0.5 * x_shift, 0.5 * y_shift, -0.5 * z_shift));

    //grass layer----------------------------------------------------------------
    glBindTexture(GL_TEXTURE_2D, texture);//bindtexture

    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4f, 2.0f, -6.0f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
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


    if (isRotate)
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

    if (isRotate)
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












void Floor(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift)
{

    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;

    uni_translate = glm::translate(identityMatrix, glm::vec3(-2.3f + 0.5 * x_shift, 0.5 * y_shift, 0.5 * z_shift));
    //TV
    //bottom layer----------------------------------------------------------------
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 0.02f, 2.0f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.6, 0.6, 0.6, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.21176470588235294, 0.6980392156862745, 0.1568627450980392, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.21176470588235294, 0.6980392156862745, 0.1568627450980392, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

}


void Lamp(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift , int style)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, invtranslateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;

    uni_translate = glm::translate(identityMatrix, glm::vec3(-2.3f + 0.5 * (x_shift+2.0f), 0.5 * (y_shift+.02f), 0.5 * z_shift));

    //plus
    if (style == 1)
    {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.5f * 1.42f, 0.0f));
        invtranslateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f,0.0f, -0.5f * 0.1f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.05f, 0.2f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians((float)45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = translateMatrix * rotateYMatrix * invtranslateMatrix * scaleMatrix ;
        ourShader.setMat4("model", uni_translate * model);
        //ourShader.setVec4("color", glm::vec4(0.7, 0.7, 0.7, 1.0f));
        ourShader.setVec4("material.ambient", glm::vec4(0.7, 0.7, 0.7, 1.0f));
        ourShader.setVec4("material.diffuse", glm::vec4(0.7, 0.7, 0.7, 1.0f));
        ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
        ourShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }
    else if (style == 2)
    {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.5f * 1.42f, 0.0f));
        invtranslateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, -0.5f * 0.1f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.05f, 0.2f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians((float)135.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = translateMatrix * rotateYMatrix * invtranslateMatrix * scaleMatrix;
        ourShader.setMat4("model", uni_translate * model);
        //ourShader.setVec4("color", glm::vec4(0.7, 0.7, 0.7, 1.0f));
        ourShader.setVec4("material.ambient", glm::vec4(0.7, 0.7, 0.7, 1.0f));
        ourShader.setVec4("material.diffuse", glm::vec4(0.7, 0.7, 0.7, 1.0f));
        ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
        ourShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }
    else if (style == 3)
    {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.5f * 1.42f, 0.0f));
        invtranslateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, -0.5f * 0.1f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.05f, 0.2f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians((float)225.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = translateMatrix * rotateYMatrix * invtranslateMatrix * scaleMatrix;
        ourShader.setMat4("model", uni_translate * model);
        //ourShader.setVec4("color", glm::vec4(0.7, 0.7, 0.7, 1.0f));
        ourShader.setVec4("material.ambient", glm::vec4(0.7, 0.7, 0.7, 1.0f));
        ourShader.setVec4("material.diffuse", glm::vec4(0.7, 0.7, 0.7, 1.0f));
        ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
        ourShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }
    else
    {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.5f * 1.42f, 0.0f));
        invtranslateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, -0.5f * 0.1f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.05f, 0.2f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians((float)315.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        model = translateMatrix * rotateYMatrix * invtranslateMatrix * scaleMatrix;
        ourShader.setMat4("model", uni_translate * model);
        //ourShader.setVec4("color", glm::vec4(0.7, 0.7, 0.7, 1.0f));
        ourShader.setVec4("material.ambient", glm::vec4(0.7, 0.7, 0.7, 1.0f));
        ourShader.setVec4("material.diffuse", glm::vec4(0.7, 0.7, 0.7, 1.0f));
        ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
        ourShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }

    //bottom stand
    for (int i = 0; i <= 360; i += 1)
    {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1061f, 0.05f, 0.1061f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians((float)i), glm::vec3(0.0f, 1.0f, 0.0f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        ourShader.setMat4("model", uni_translate * model);
        //ourShader.setVec4("color", glm::vec4(0.7, 0.7, 0.7, 1.0f));
        ourShader.setVec4("material.ambient", glm::vec4(0.7, 0.7, 0.7, 1.0f));
        ourShader.setVec4("material.diffuse", glm::vec4(0.7, 0.7, 0.7, 1.0f));
        ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
        ourShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }

    //Stand
    for (int i = 0; i <= 360; i += 1)
    {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.5f * 0.02f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.025f, 1.42f, 0.025f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians((float)i), glm::vec3(0.0f, 1.0f, 0.0f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        ourShader.setMat4("model", uni_translate * model);
        //ourShader.setVec4("color", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
        ourShader.setVec4("material.ambient", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
        ourShader.setVec4("material.diffuse", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
        ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
        ourShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }

}

void MainFloor(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift)
{

    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;

    uni_translate = glm::translate(identityMatrix, glm::vec3(-2.3f + 0.5 * x_shift, 0.5 * y_shift, 0.5 * z_shift));
    //TV
    //bottom layer----------------------------------------------------------------
    translateMatrix = glm::translate(identityMatrix, glm::vec3((0.5f * 6.0f), (0.5f * 0.02f), -0.5f * 6.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25f, 0.25f, 0.25f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.6, 0.6, 0.6, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9098039215686274, 0.8549019607843137, 0.8, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

}

//draw functions
void Sofa3(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift)
{

    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate, uni_rotateYMatrix;

    uni_rotateYMatrix = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    uni_translate = glm::translate(identityMatrix, glm::vec3(0.5 * x_shift, 0.5 * y_shift, 0.5 * z_shift));
    //3 seat sofa
    //bottom wood--------------------------------------------------------------------------------
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.7f, 0.1f, 0.8f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * uni_rotateYMatrix * model);
    //ourShader.setVec4("color", glm::vec4(0.330, 0.0594, 0.0594, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.330, 0.0594, 0.0594, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.330, 0.0594, 0.0594, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //main foam---------------------------------------------------------------------------------------
    translateMatrix = glm::translate(identityMatrix, glm::vec3((0.5f * 0.1f), (0.5f * 0.1f), 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 0.2f, 0.8f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * uni_rotateYMatrix * model);
    //ourShader.setVec4("color", glm::vec4(0.950, 0.560, 0.560, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.950, 0.560, 0.560, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.950, 0.560, 0.560, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


    //main back rest_bootom-----------------------------------------------------------------
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, (0.5f * 0.1f), 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.7f, 0.6f, 0.1f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(-10.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = translateMatrix * rotateXMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * uni_rotateYMatrix * model);
    //ourShader.setVec4("color", glm::vec4(0.330, 0.0594, 0.0594, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.330, 0.0594, 0.0594, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.330, 0.0594, 0.0594, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //main back rest_foam------------------------------------------------------------------------
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f + (0.5f * 0.1f), (0.5f * 0.1f), 0.05f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 0.6f, 0.2f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(-10.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = translateMatrix * rotateXMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * uni_rotateYMatrix * model);
    //ourShader.setVec4("color", glm::vec4(0.950, 0.560, 0.560, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.950, 0.560, 0.560, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.950, 0.560, 0.560, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 64.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //left side rest----------------------------------------------------------------------------------
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, (0.5f * 0.1f), 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 0.35f, 0.75f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * uni_rotateYMatrix * model);
    //ourShader.setVec4("color", glm::vec4(0.330, 0.0594, 0.0594, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.330, 0.0594, 0.0594, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.330, 0.0594, 0.0594, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 64.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //right side rest-------------------------------------------------------------------------------------
    translateMatrix = glm::translate(identityMatrix, glm::vec3((0.0f + .5f * (1.7f - .1f)), (0.5f * 0.1f), 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 0.35f, 0.75f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * uni_rotateYMatrix * model);
    //ourShader.setVec4("color", glm::vec4(0.330, 0.0594, 0.0594, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.330, 0.0594, 0.0594, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.330, 0.0594, 0.0594, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void Sofa21(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift)
{

    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate, uni_rotateYMatrix;

    uni_rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    uni_translate = glm::translate(identityMatrix, glm::vec3(0.5 * x_shift, 0.5 * y_shift, 0.5 * z_shift));
    //3 seat sofa
    //bottom wood
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.2f, 0.1f, 0.8f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * uni_rotateYMatrix * model);
    //ourShader.setVec4("color", glm::vec4(0.330, 0.0594, 0.0594, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.330, 0.0594, 0.0594, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.330, 0.0594, 0.0594, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //main foam
    translateMatrix = glm::translate(identityMatrix, glm::vec3((0.5f * 0.1f), (0.5f * 0.1f), 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.2f, 0.8f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * uni_rotateYMatrix * model);
    //ourShader.setVec4("color", glm::vec4(0.950, 0.560, 0.560, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.950, 0.560, 0.560, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.950, 0.560, 0.560, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


    //main back rest_bootom
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, (0.5f * 0.1f), 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.2f, 0.6f, 0.1f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(-10.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = translateMatrix * rotateXMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * uni_rotateYMatrix * model);
    //ourShader.setVec4("color", glm::vec4(0.330, 0.0594, 0.0594, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.330, 0.0594, 0.0594, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.330, 0.0594, 0.0594, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //main back rest_foam
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f + (0.5f * 0.1f), (0.5f * 0.1f), 0.05f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.6f, 0.2f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(-10.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = translateMatrix * rotateXMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * uni_rotateYMatrix * model);
    //ourShader.setVec4("color", glm::vec4(0.950, 0.560, 0.560, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.950, 0.560, 0.560, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.950, 0.560, 0.560, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //left side rest
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, (0.5f * 0.1f), 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 0.35f, 0.75f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * uni_rotateYMatrix * model);
    //ourShader.setVec4("color", glm::vec4(0.330, 0.0594, 0.0594, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.330, 0.0594, 0.0594, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.330, 0.0594, 0.0594, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //right side rest
    translateMatrix = glm::translate(identityMatrix, glm::vec3((0.0f + .5f * (1.2f - .1f)), (0.5f * 0.1f), 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 0.35f, 0.75f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * uni_rotateYMatrix * model);
    //ourShader.setVec4("color", glm::vec4(0.330, 0.0594, 0.0594, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.330, 0.0594, 0.0594, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.330, 0.0594, 0.0594, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void Sofa22(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift)
{

    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate, uni_rotateYMatrix;

    uni_rotateYMatrix = glm::rotate(identityMatrix, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    uni_translate = glm::translate(identityMatrix, glm::vec3(0.5 * x_shift, 0.5 * y_shift, 0.5 * z_shift));
    //3 seat sofa
    //bottom wood
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.2f, 0.1f, 0.8f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * uni_rotateYMatrix * model);
    //ourShader.setVec4("color", glm::vec4(0.330, 0.0594, 0.0594, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.330, 0.0594, 0.0594, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.330, 0.0594, 0.0594, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //main foam
    translateMatrix = glm::translate(identityMatrix, glm::vec3((0.5f * 0.1f), (0.5f * 0.1f), 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.2f, 0.8f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * uni_rotateYMatrix * model);
    //ourShader.setVec4("color", glm::vec4(0.950, 0.560, 0.560, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.950, 0.560, 0.560, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.950, 0.560, 0.560, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


    //main back rest_bootom
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, (0.5f * 0.1f), 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.2f, 0.6f, 0.1f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(-10.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = translateMatrix * rotateXMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * uni_rotateYMatrix * model);
    //ourShader.setVec4("color", glm::vec4(0.330, 0.0594, 0.0594, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.330, 0.0594, 0.0594, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.330, 0.0594, 0.0594, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //main back rest_foam
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f + (0.5f * 0.1f), (0.5f * 0.1f), 0.05f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.6f, 0.2f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(-10.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    model = translateMatrix * rotateXMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * uni_rotateYMatrix * model);
    //ourShader.setVec4("color", glm::vec4(0.950, 0.560, 0.560, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.950, 0.560, 0.560, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.950, 0.560, 0.560, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //left side rest
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, (0.5f * 0.1f), 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 0.35f, 0.75f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * uni_rotateYMatrix * model);
    //ourShader.setVec4("color", glm::vec4(0.330, 0.0594, 0.0594, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.330, 0.0594, 0.0594, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.330, 0.0594, 0.0594, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //right side rest
    translateMatrix = glm::translate(identityMatrix, glm::vec3((0.0f + .5f * (1.2f - .1f)), (0.5f * 0.1f), 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 0.35f, 0.75f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * uni_rotateYMatrix * model);
    //ourShader.setVec4("color", glm::vec4(0.330, 0.0594, 0.0594, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.330, 0.0594, 0.0594, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.330, 0.0594, 0.0594, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void TV(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift)
{

    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;

    uni_translate = glm::translate(identityMatrix, glm::vec3(0.5 * x_shift, 0.5 * y_shift, 0.5 * z_shift));
    //TV
    //bottom Stand
    translateMatrix = glm::translate(identityMatrix, glm::vec3((-0.5f + .5f * (0.6f)), 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.3f, 0.1f, 0.3f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * model);
    //ourShader.setVec4("color", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.0, 0.0, 0.0, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.0, 0.0, 0.0, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //middle Stand
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f + (0.5f * 0.7f), (0.5f * 0.1f), 0.5f * 0.2f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 0.1f, 0.08f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * model);
    //ourShader.setVec4("color", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.0, 0.0, 0.0, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.0, 0.0, 0.0, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //back panel
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f, (0.5f * 0.2f), 0.5f * 0.2f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 0.75f, 0.04f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * model);
    //ourShader.setVec4("color", glm::vec4(0.0, 0.0, 0.0, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.0, 0.0, 0.0, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.0, 0.0, 0.0, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //display panel
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f + (0.5f * .05f), (0.5f * 0.25f), 0.5f * 0.24f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.4f, 0.65f, 0.04f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * model);
    //ourShader.setVec4("color", glm::vec4(0.7411764705882353, 0.7411764705882353, 0.7411764705882353, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.7411764705882353, 0.7411764705882353, 0.7411764705882353, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.7411764705882353, 0.7411764705882353, 0.7411764705882353, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 256.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //bottom pillar
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f, (0.5f * 0.2f), 0.5f * 0.24f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 0.05f, 0.04f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * model);
    //ourShader.setVec4("color", glm::vec4(0.0, 0.0, 0.0, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.0, 0.0, 0.0, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.0, 0.0, 0.0, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //top pillar
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f, (0.5f * 0.9f), 0.5f * 0.24f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 0.05f, 0.04f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * model);
    //ourShader.setVec4("color", glm::vec4(0.0, 0.0, 0.0, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.0, 0.0, 0.0, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.0, 0.0, 0.0, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //left pillar
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f, (0.5f * 0.2f), 0.5f * 0.24f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, 0.75f, 0.04f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * model);
    //ourShader.setVec4("color", glm::vec4(0.0, 0.0, 0.0, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.0, 0.0, 0.0, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.0, 0.0, 0.0, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //right pillar
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f + (0.5f * 1.45f), (0.5f * 0.2f), 0.5f * 0.24f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, 0.75f, 0.04f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * model);
    //ourShader.setVec4("color", glm::vec4(0.0, 0.0, 0.0, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.0, 0.0, 0.0, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.0, 0.0, 0.0, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

}

void Shelf(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift)
{

    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate, uni_scale;

    uni_translate = glm::translate(identityMatrix, glm::vec3(0.5 * x_shift, 0.5 * y_shift, 0.5 * z_shift));
    uni_scale = glm::scale(identityMatrix, glm::vec3(0.7f, 0.7f, 0.7f));
    //Shelf
    //bottom panel
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.85f, 0.05f, 0.5f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * uni_scale * model);
    //ourShader.setVec4("color", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //mid panel
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f, (0.5f * 0.45f), 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.85f, 0.05f, 0.5f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * uni_scale * model);
    //ourShader.setVec4("color", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //top panel
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f, (0.5f * 0.9f), 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.85f, 0.05f, 0.5f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * uni_scale * model);
    //ourShader.setVec4("color", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


    //left side panel
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, 0.95f, 0.5f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * uni_scale * model);
    //ourShader.setVec4("color", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //mid side panel
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f + (0.5f * 0.9f), 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, 0.45f, 0.5f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * uni_scale * model);
    //ourShader.setVec4("color", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //right side panel
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f + (0.5f * 1.85f), 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, 0.95f, 0.5f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * uni_scale * model);
    //ourShader.setVec4("color", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //back panel
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.85f, 0.95f, 0.05f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * uni_scale * model);
    //ourShader.setVec4("color", glm::vec4(1.0, 0.6470588235294118, 0.30980392156862746, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(1.0, 0.6470588235294118, 0.30980392156862746, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(1.0, 0.6470588235294118, 0.30980392156862746, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

}

void Table(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift)
{

    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;

    uni_translate = glm::translate(identityMatrix, glm::vec3(0.5 * x_shift, 0.5 * y_shift, 0.5 * z_shift));

    //back left leg
    translateMatrix = glm::translate(identityMatrix, glm::vec3((-0.5f + (.5f * 0.2f)), 0.0f, (.5f * 0.2f)));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, 0.45f, 0.05f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * model);
    //ourShader.setVec4("color", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //back right leg
    translateMatrix = glm::translate(identityMatrix, glm::vec3((-0.5f + (.5f * 1.25f)), 0.0f, (.5f * 0.2f)));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, 0.45f, 0.05f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * model);
    //ourShader.setVec4("color", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //front left leg
    translateMatrix = glm::translate(identityMatrix, glm::vec3((-0.5f + (.5f * 0.2f)), 0.0f, (.5f * 1.25f)));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, 0.45f, 0.05f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * model);
    //ourShader.setVec4("color", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //back right leg
    translateMatrix = glm::translate(identityMatrix, glm::vec3((-0.5f + (.5f * 1.25f)), 0.0f, (.5f * 1.25f)));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, 0.45f, 0.05f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * model);
    //ourShader.setVec4("color", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //table top
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f, (.5f * 0.45f), 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5f, 0.05f, 1.5f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * model);
    //ourShader.setVec4("color", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


}

void Speaker(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift)
{

    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate, uni_scale;
    uni_scale = glm::scale(identityMatrix, glm::vec3(0.5f, 0.65f, 0.65f));

    uni_translate = glm::translate(identityMatrix, glm::vec3(0.5 * x_shift, 0.5 * y_shift, 0.5 * z_shift));

    //bottom Stand
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.1f, 0.5f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * uni_scale * model);
    //ourShader.setVec4("color", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //middle Stand
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f + (0.5f * 0.2f), (0.5f * 0.1f), 0.5f * 0.2f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 0.2f, 0.08f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * uni_scale * model);
    //ourShader.setVec4("color", glm::vec4(0.0, 0.0, 0.0, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //back panel
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f, (0.5f * 0.3f), 0.5f * 0.2f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 2.5f, 0.04f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * uni_scale * model);
    //ourShader.setVec4("color", glm::vec4(0.0, 0.0, 0.0, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //display panel
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f + (0.5f * .05f), (0.5f * 0.35f), 0.5f * 0.24f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.4f, 2.4f, 0.04f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * uni_scale * model);
    //ourShader.setVec4("color", glm::vec4(0.420, 0.399, 0.399, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.420, 0.399, 0.399, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.420, 0.399, 0.399, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 256.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //bottom pillar
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f, (0.5f * 0.3f), 0.5f * 0.24f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.05f, 0.04f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * uni_scale * model);
    //ourShader.setVec4("color", glm::vec4(0.0, 0.0, 0.0, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.0, 0.0, 0.0, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.0, 0.0, 0.0, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //top pillar
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f, (0.5f * (.3f + 2.45f)), 0.5f * 0.24f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.05f, 0.04f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * uni_scale * model);
    //ourShader.setVec4("color", glm::vec4(0.0, 0.0, 0.0, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.0, 0.0, 0.0, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.0, 0.0, 0.0, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //left pillar
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f, (0.5f * 0.3f), 0.5f * 0.24f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, 2.5f, 0.04f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * uni_scale * model);
    //ourShader.setVec4("color", glm::vec4(0.0, 0.0, 0.0, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.0, 0.0, 0.0, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.0, 0.0, 0.0, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //right pillar
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f + (0.5f * .45f), (0.5f * 0.3f), 0.5f * 0.24f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, 2.5f, 0.04f));
    model = translateMatrix * scaleMatrix;
    ourShader.setMat4("model", uni_translate * uni_scale * model);
    //ourShader.setVec4("color", glm::vec4(0.0, 0.0, 0.0, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.0, 0.0, 0.0, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.0, 0.0, 0.0, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

}


void Cup(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;

    uni_translate = glm::translate(identityMatrix, glm::vec3(0.5 * x_shift, 0.5 * y_shift, 0.5 * z_shift));
    //3 seat sofa
    //bottom wood

    //tube
    for (int i = 0; i <= 360; i++)
    {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.05f, 0.5f * 0.02f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.02f, 0.1f, 0.01f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians((float)i), glm::vec3(0.0f, 1.0f, 0.0f));
        model = rotateYMatrix * translateMatrix * scaleMatrix;
        ourShader.setMat4("model", uni_translate * model);
        //ourShader.setVec4("color", glm::vec4(0.9882352941176471, 0.9921568627450981, 1, 1.0f));
        ourShader.setVec4("material.ambient", glm::vec4(0.9882352941176471, 0.9921568627450981, 1, 1.0f));
        ourShader.setVec4("material.diffuse", glm::vec4(0.9882352941176471, 0.9921568627450981, 1, 1.0f));
        ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
        ourShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }

    //bottom
    for (int i = 0; i <= 360; i++)
    {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.5f * 0.02f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.0707f, 0.01f, 0.0707f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians((float)i), glm::vec3(0.0f, 1.0f, 0.0f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        ourShader.setMat4("model", uni_translate * model);
        //ourShader.setVec4("color", glm::vec4(0.39215686274509803, 0.12549019607843137, 0.1607843137254902, 1.0f));
        ourShader.setVec4("material.ambient", glm::vec4(0.39215686274509803, 0.12549019607843137, 0.1607843137254902, 1.0f));
        ourShader.setVec4("material.diffuse", glm::vec4(0.39215686274509803, 0.12549019607843137, 0.1607843137254902, 1.0f));
        ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
        ourShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }

    //pirij bottom
    for (int i = 0; i <= 360; i++)
    {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.15f, 0.02f, 0.15f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians((float)i), glm::vec3(0.0f, 1.0f, 0.0f));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        ourShader.setMat4("model", uni_translate * model);
        //ourShader.setVec4("color", glm::vec4(0.9882352941176471, 0.9921568627450981, 1, 1.0f));
        ourShader.setVec4("material.ambient", glm::vec4(0.9882352941176471, 0.9921568627450981, 1, 1.0f));
        ourShader.setVec4("material.diffuse", glm::vec4(0.9882352941176471, 0.9921568627450981, 1, 1.0f));
        ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
        ourShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }

    //pirinj side
    for (int i = 0; i <= 360; i++)
    {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.05f + (0.5f * 0.2121f), 0.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.02f, 0.03f, 0.01f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians((float)i), glm::vec3(0.0f, 1.0f, 0.0f));
        model = rotateYMatrix * translateMatrix * scaleMatrix;
        ourShader.setMat4("model", uni_translate * model);
        //ourShader.setVec4("color", glm::vec4(0.7, 0.7, 0.7, 1.0f));
        ourShader.setVec4("material.ambient", glm::vec4(0.7, 0.7, 0.7, 1.0f));
        ourShader.setVec4("material.diffuse", glm::vec4(0.7, 0.7, 0.7, 1.0f));
        ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
        ourShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }
}



void SideWall(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;

    uni_translate = glm::translate(identityMatrix, glm::vec3(-2.3f + 0.5 * x_shift, 0.5 * y_shift, 0.5 * (z_shift + 1.0f)));
    //TV
    //bottom layer
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.2f, 3.0f, -9.2f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.9019607843137255, 0.6627450980392157, 0.5529411764705883, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9019607843137255, 0.6627450980392157, 0.5529411764705883, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9019607843137255, 0.6627450980392157, 0.5529411764705883, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void FBWall(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;

    uni_translate = glm::translate(identityMatrix, glm::vec3(0.5 * (x_shift - 4.6f), 0.5 * y_shift, 0.5 * (z_shift - 0.2f)));
    //TV
    //bottom layer
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(9.0f, 3.0f, 0.2f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);

    //ourShader.setVec4("color", glm::vec4(0.48627450980392156, 0.6235294117647059, 0.5058823529411764, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.48627450980392156, 0.6235294117647059, 0.5058823529411764, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.48627450980392156, 0.6235294117647059, 0.5058823529411764, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void Roof(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;

    uni_translate = glm::translate(identityMatrix, glm::vec3(-2.3f + 0.5 * x_shift, 0.5 * (y_shift + 3.0f), 0.5 * z_shift));
    //TV
    //bottom layer
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.1f, 1.0f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.7843137254901961, 0.8470588235294118, 0.615686274509804, 0.8f));
    ourShader.setVec4("material.ambient", glm::vec4(0.7843137254901961, 0.8470588235294118, 0.615686274509804, 0.8f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.7843137254901961, 0.8470588235294118, 0.615686274509804, 0.8f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

}

void Fan(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift)
{
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, translateToPivot, translateFromPivot, model, uni_translate;

    uni_translate = glm::translate(identityMatrix, glm::vec3(0.5 * x_shift, 0.5 * y_shift, 0.5 * z_shift));


    //Bati
    for (int i = 0; i <= 360; i += 1)
    {
        translateToPivot = glm::translate(identityMatrix, glm::vec3(0.0f, (0.5f * -0.025f), (0.5f * -0.1f)));
        translateFromPivot = glm::translate(identityMatrix, glm::vec3(0.0f, (0.5f * 0.025f), (0.5f * 0.1f)));
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, (0.5f*-0.15f), 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.20f, 0.15f, 0.20f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians((float)i), glm::vec3(0.0f, 1.0f, 0.0f));
        model = translateToPivot * rotateYMatrix * translateToPivot * scaleMatrix;
        ourShader.setMat4("model", uni_translate * model);
        //ourShader.setVec4("color", glm::vec4(0.8411764705882353, 0.8411764705882353, 0.8411764705882353, 1.0f));
        ourShader.setVec4("material.ambient", glm::vec4(0.8411764705882353, 0.8411764705882353, 0.8411764705882353, 1.0f));
        ourShader.setVec4("material.diffuse", glm::vec4(0.8411764705882353, 0.8411764705882353, 0.8411764705882353, 1.0f));
        ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
        ourShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }

    //Stand Rod
    for (int i = 0; i <= 360; i += 1)
    {
        translateToPivot = glm::translate(identityMatrix, glm::vec3(0.0f, (0.5f * -0.025f), (0.5f * -0.1f)));
        translateFromPivot = glm::translate(identityMatrix, glm::vec3(0.0f, (0.5f * 0.025f), (0.5f * 0.1f)));
        //translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.5f * (0.02f-0.15f), 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.015f, 0.6f, 0.015f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians((float)i), glm::vec3(0.0f, 1.0f, 0.0f));
        model = translateToPivot * rotateYMatrix * translateToPivot * scaleMatrix;
        ourShader.setMat4("model", uni_translate * model);
        //ourShader.setVec4("color", glm::vec4(0.2, 0.2, 0.2, 1.0f));
        ourShader.setVec4("material.ambient", glm::vec4(0.2, 0.2, 0.2, 1.0f));
        ourShader.setVec4("material.diffuse", glm::vec4(0.2, 0.2, 0.2, 1.0f));
        ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
        ourShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }

    if (isRotate)
    {
        rotateAngle_Y += fanspeed;
        rotateAngle_Y = fmod(rotateAngle_Y, 360);
    }

    //Blade 1
    translateToPivot = glm::translate(identityMatrix, glm::vec3(0.0f, (0.5f * -0.025f), (0.5f * -0.1f)));
    translateFromPivot = glm::translate(identityMatrix, glm::vec3(0.0f, (0.5f * 0.025f), (0.5f * 0.1f)));
    //translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.9f, 0.05f, 0.2f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(0.0f + rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = translateToPivot * rotateYMatrix * translateToPivot * scaleMatrix;
    ourShader.setMat4("model", uni_translate * model);
    //ourShader.setVec4("color", glm::vec4(0.9411764705882353, 0.9411764705882353, 0.9411764705882353, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9411764705882353, 0.9411764705882353, 0.9411764705882353, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9411764705882353, 0.9411764705882353, 0.9411764705882353, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //Blade 2
    translateToPivot = glm::translate(identityMatrix, glm::vec3(0.0f, (0.5f * -0.025f), (0.5f * -0.1f)));
    translateFromPivot = glm::translate(identityMatrix, glm::vec3(0.0f, (0.5f * 0.025f), (0.5f * 0.1f)));
    //translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.9f, 0.05f, 0.2f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(120.0f + rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = translateToPivot * rotateYMatrix * translateToPivot * scaleMatrix;
    ourShader.setMat4("model", uni_translate * model);
    //ourShader.setVec4("color", glm::vec4(0.9411764705882353, 0.9411764705882353, 0.9411764705882353, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9411764705882353, 0.9411764705882353, 0.9411764705882353, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9411764705882353, 0.9411764705882353, 0.9411764705882353, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //Blade 3
    translateToPivot = glm::translate(identityMatrix, glm::vec3(0.0f, (0.5f * -0.025f), (0.5f * -0.1f)));
    translateFromPivot = glm::translate(identityMatrix, glm::vec3(0.0f, (0.5f * 0.025f), (0.5f * 0.1f)));
    //translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.9f, 0.05f, 0.2f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(240.0f + rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = translateToPivot * rotateYMatrix * translateToPivot * scaleMatrix;
    ourShader.setMat4("model", uni_translate * model);
    //ourShader.setVec4("color", glm::vec4(0.9411764705882353, 0.9411764705882353, 0.9411764705882353, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.9411764705882353, 0.9411764705882353, 0.9411764705882353, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.9411764705882353, 0.9411764705882353, 0.9411764705882353, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void Ladder(unsigned int VAO, Shader ourShader, float x_shift, float y_shift, float z_shift)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model, uni_translate;

    uni_translate = glm::translate(identityMatrix, glm::vec3(0.5 * (x_shift - 3.5f), 0.5 * y_shift, 0.5 * (z_shift - 0.2f)));

    //left stick
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 3.0f, 0.05f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //Right stick
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.5f * 1.0f, 0.0f, 0.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 3.0f, 0.05f));
    model = uni_translate * translateMatrix * scaleMatrix;
    ourShader.setMat4("model", model);
    //ourShader.setVec4("color", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
    ourShader.setVec4("material.ambient", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
    ourShader.setVec4("material.diffuse", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
    ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
    ourShader.setFloat("material.shininess", 32.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    float trnsY = 0.35;
    for (int i = 0; i < 9; i++)
    {
        translateMatrix = glm::translate(identityMatrix, glm::vec3(0.0f, 0.5f * (i * trnsY), 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0f, 0.25f, 0.05f));
        model = uni_translate * translateMatrix * scaleMatrix;
        ourShader.setMat4("model", model);
        //ourShader.setVec4("color", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
        ourShader.setVec4("material.ambient", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
        ourShader.setVec4("material.diffuse", glm::vec4(0.6274509803921569, 0.3215686274509804, 0.17647058823529413, 1.0f));
        ourShader.setVec4("material.specular", glm::vec4(0.6f, 0.5f, 0.5f, 0.5f));
        ourShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    }
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

    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)                   //Yaw ve+
    {
        camera.Proccess_Pitch_Yaw_Roll(0.0f, 3.0f, 0.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)                   //Yaw ve-
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

    //if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
    //{
    //    eyeX += 2.5 * deltaTime;
    //    basic_camera.changeEye(eyeX, eyeY, eyeZ);
    //}
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)                   //Rotate camera around a look at point
    {                                                                   //Right
        /*eyeX -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);*/
        camera.RotateAroundLookAt(2.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)                   //Rotate camera around a look at point
    {                                                                   //Left
        /*eyeX -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);*/
        camera.RotateAroundLookAt(-2.0f);
    }

    //if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    //{
    //    eyeZ += 2.5 * deltaTime;
    //    basic_camera.changeEye(eyeX, eyeY, eyeZ);
    //}
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)                   //Rotate Fan
    {
        isRotate ^= true;
        cout << isRotate << endl;
        Sleep(100);
    }
    //if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    //{
    //    eyeY += 2.5 * deltaTime;
    //    basic_camera.changeEye(eyeX, eyeY, eyeZ);
    //}
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)                   //Up
    {
        eyeY -= 2.5 * deltaTime;
        //basic_camera.changeEye(eyeX, eyeY, eyeZ);

        camera.ProcessKeyboard(UP, deltaTime);

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
        ambientOn = 1.0;
        pointLight.turnAmbientOn();
        spotLight.turnAmbientOn();
        //spotLight1.turnAmbientOn();
        //spotLight2.turnAmbientOn();
        directionalLight.turnAmbientOn();
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)                   //Ambient Off
    {
        ambientOn = 0.0;
        pointLight.turnAmbientOff();
        spotLight.turnAmbientOff();
        //spotLight1.turnAmbientOff();
        //spotLight2.turnAmbientOff();
        directionalLight.turnAmbientOff();
    }

    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)                   //Diffuse On
    {
        diffuseOn = 1.0;
        pointLight.turnDiffuseOn();
        spotLight.turnDiffuseOn();
        //spotLight1.turnDiffuseOn();
        //spotLight2.turnDiffuseOn();
        directionalLight.turnDiffuseOn();

    }
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)                   //Diffuse Off
    {
        diffuseOn = 0.0;
        pointLight.turnDiffuseOff();
        spotLight.turnDiffuseOff();
        //spotLight1.turnDiffuseOff();
        //spotLight2.turnDiffuseOff();
        directionalLight.turnDiffuseOff();
    }
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)                   //Specular On
    {
        specularOn = 1.0;
        pointLight.turnSpecularOn();
        spotLight.turnSpecularOn();
        //spotLight1.turnSpecularOn();
        //spotLight2.turnSpecularOn();
        directionalLight.turnSpecularOn();
    }
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)                   //Specular Off
    {
        specularOn = 0.0;
        pointLight.turnSpecularOff();
        spotLight.turnSpecularOff();
        //spotLight1.turnSpecularOff();
        //spotLight2.turnSpecularOff();
        directionalLight.turnSpecularOff();
    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)                   //Point Light On
    {
        pointLightOn = 1.0;
        pointLight.turnOn();
    }
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)                   //Point Light Off
    {
        pointLightOn = 0.0;
        pointLight.turnOff();
    }
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)                   //Directional Light On
    {
        directionalLightOn = 1.0;
        directionalLight.turnOn();
    }
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)                   //Directional Light Off
    {
        directionalLightOn = 0.0;
        directionalLight.turnOff();
    }
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)                   //Spot Light On
    {
        spotLightOn = 1.0;
        spotLight.turnOn();
        //spotLight1.turnOn();
        //spotLight2.turnOn();
    }
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)                   //Spot Light Off
    {
        spotLightOn = 0.0;
        spotLight.turnOff();
        //spotLight1.turnOff();
        //spotLight2.turnOff();
    }
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)                   //Dark On-Off
    {
        dark ^= true;
        cout << dark << endl;
        Sleep(100);
    }

    //if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    //{
    //    lookAtY += 2.5 * deltaTime;
    //    basic_camera.changeLookAt(lookAtX, lookAtY, lookAtZ);
    //}
    //if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
    //{
    //    lookAtY -= 2.5 * deltaTime;
    //    basic_camera.changeLookAt(lookAtX, lookAtY, lookAtZ);
    //}
    //if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
    //{
    //    lookAtZ += 2.5 * deltaTime;
    //    basic_camera.changeLookAt(lookAtX, lookAtY, lookAtZ);
    //}
    //if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
    //{
    //    lookAtZ -= 2.5 * deltaTime;
    //    basic_camera.changeLookAt(lookAtX, lookAtY, lookAtZ);
    //}
    //if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
    //{
    //    basic_camera.changeViewUpVector(glm::vec3(1.0f, 0.0f, 0.0f));
    //}
    //if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
    //{
    //    basic_camera.changeViewUpVector(glm::vec3(0.0f, 1.0f, 0.0f));
    //}
    //if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
    //{
    //    basic_camera.changeViewUpVector(glm::vec3(0.0f, 0.0f, 1.0f));
    //}

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

