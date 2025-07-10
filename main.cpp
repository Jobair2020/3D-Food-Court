
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "basic_camera.h"
#include "pointLight.h"
#include "directionalLight.h"
#include "spotLight.h"
#include "cube.h"
#include "stb_image.h"
#include "sphere.h"
#include "cylinder.h"
#include "parabola.h"
#include "curve.h"
#include <iostream>
#include <ctime>
#include "sphere2.h"
#include "Mesh.h"
#include "Model.h"
#include "cone.h"



#define STB_IMAGE_IMPLEMENTATION
#pragma warning(disable:4996)
#include <unordered_map>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax);
void getCurrentTime(int& hours, int& minutes, int& seconds);
//void Drone(Cylinder& cylinder, Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void drawTreeWithFractiles(Cube& tree, Cube& root, Shader& lightingShader, glm::mat4 alTogether, float L, float H, float W, int N);
void drawTreeWithFractilesSphere(Sphere2* tree, Cube& root, Shader& lightingShader, glm::mat4 alTogether, float L, float H, float W, int N);


//object making functions
void Table(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void Chair(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void ChairTableCombo(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void Sofa(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void OvenCooker(Cube& cube, Cube& chula, Cube& oven, Cube& basin, Shader& lightingShader, Shader& lightingShaderWithTexture, glm::mat4 alTogether);
void ShowcaseRack(Cylinder& cylinder1, Cube& chips, Cube& chips2, Cube& chips3, Cube& cube, Shader& lightingShader, glm::mat4 alTogether);


long long nCr(int n, int r);
void BezierCurve(double t, float xy[2], GLfloat ctrlpoints[], int L);
unsigned int hollowBezier(GLfloat ctrlpoints[], int L);

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

// modelling transform
float rotateAngle_X = 0.0;
float rotateAngle_Y = 0.0;
float rotateAngle_Z = 0.0;
float rotateAxis_X = 0.0;
float rotateAxis_Y = 0.0;
float rotateAxis_Z = 1.0;
float translate_X = 0.0;
float translate_Y = 0.0;
float translate_Z = 0.0;
float scale_X = 1.0;
float scale_Y = 1.0;
float scale_Z = 1.0;

float rotateClock = 0.0f;
bool sign = 1;
int ang = 20;
int Dang = 10;
int cnt = 1;
float dx=8, dy=10, dz=0, ry = 0;
int imgInd = 0;
//bool tvOn = false;

//vector<string>imagesForTv{
// "TV/tv (1).jpg",
//"TV/tv (2).jpg",
//"TV/tv (3).jpg",
//"TV/tv (4).jpg",
//"TV/tv (5).jpg",
//"TV/tv (6).jpg",
//"TV/tv (7).jpg",
//"TV/tv (8).jpg",
//"TV/tv (9).jpg",
//"TV/tv (10).jpg",
//"TV/tv (11).jpg",
//"TV/tv (12).jpg",
//"TV/tv (13).jpg",
//"TV/tv (14).jpg",
//"TV/tv (15).jpg",
//"TV/tv (16).jpg",
//"TV/tv (17).jpg",
//"TV/tv (18).jpg",
//"TV/tv (19).jpg",
//"TV/tv (20).jpg",
//"TV/tv (21).jpg",
//"TV/tv (22).jpg",
//"TV/tv (23).jpg",
//"TV/tv (24).jpg",
//"TV/tv (25).jpg",
//"TV/tv (26).jpg",
//"TV/tv (27).jpg",
//"TV/tv (28).jpg",
//"TV/tv (29).jpg",
//"TV/tv (30).jpg",
//"TV/tv (31).jpg",
//"TV/tv (32).jpg",
//"TV/tv (33).jpg",
//"TV/tv (34).jpg",
//"TV/tv (35).jpg",
//"TV/tv (36).jpg",
//"TV/tv (37).jpg",
//"TV/tv (38).jpg",
//"TV/tv (39).jpg",
//"TV/tv (40).jpg",
//"TV/tv (41).jpg",
//"TV/tv (42).jpg",
//"TV/tv (43).jpg",
//"TV/tv (44).jpg",
//"TV/tv (45).jpg",
//"TV/tv (46).jpg",
//"TV/tv (47).jpg",
//"TV/tv (48).jpg",
//"TV/tv (49).jpg",
//"TV/tv (50).jpg",
//"TV/tv (51).jpg",
//"TV/tv (52).jpg",
//"TV/tv (53).jpg",
//"TV/tv (54).jpg",
//"TV/tv (55).jpg",
//"TV/tv (56).jpg",
//"TV/tv (57).jpg",
//"TV/tv (58).jpg",
//"TV/tv (59).jpg",
//"TV/tv (60).jpg",
//"TV/tv (61).jpg",
//"TV/tv (62).jpg",
//"TV/tv (63).jpg",
//"TV/tv (64).jpg",
//"TV/tv (65).jpg",
//"TV/tv (66).jpg",
//"TV/tv (67).jpg",
//"TV/tv (68).jpg",
//"TV/tv (69).jpg",
//"TV/tv (70).jpg",
//"TV/tv (71).jpg",
//"TV/tv (72).jpg",
//"TV/tv (73).jpg",
//"TV/tv (74).jpg",
//"TV/tv (75).jpg",
//"TV/tv (76).jpg",
//"TV/tv (77).jpg",
//"TV/tv (78).jpg",
//"TV/tv (79).jpg",
//"TV/tv (80).jpg",
//"TV/tv (81).jpg",
//"TV/tv (82).jpg",
//"TV/tv (83).jpg",
//"TV/tv (84).jpg",
//"TV/tv (85).jpg",
//"TV/tv (86).jpg",
//"TV/tv (87).jpg",
//"TV/tv (88).jpg",
//"TV/tv (89).jpg",
//"TV/tv (90).jpg",
//"TV/tv (91).jpg",
//"TV/tv (92).jpg",
//"TV/tv (93).jpg",
//"TV/tv (94).jpg",
//"TV/tv (95).jpg",
//"TV/tv (96).jpg",
//"TV/tv (97).jpg",
//"TV/tv (98).jpg",
//"TV/tv (99).jpg",
//"TV/tv (100).jpg",
//"TV/tv (101).jpg",
//"TV/tv (102).jpg",
//"TV/tv (103).jpg",
//"TV/tv (104).jpg",
//"TV/tv (105).jpg",
//"TV/tv (106).jpg",
//"TV/tv (107).jpg",
//"TV/tv (108).jpg",
//"TV/tv (109).jpg",
//"TV/tv (110).jpg",
//"TV/tv (111).jpg",
//"TV/tv (112).jpg",
//"TV/tv (113).jpg",
//"TV/tv (114).jpg",
//"TV/tv (115).jpg",
//"TV/tv (116).jpg",
//"TV/tv (117).jpg",
//"TV/tv (118).jpg",
//"TV/tv (119).jpg",
//"TV/tv (120).jpg",
//"TV/tv (121).jpg",
//"TV/tv (122).jpg",
//"TV/tv (123).jpg",
//"TV/tv (124).jpg",
//"TV/tv (125).jpg",
//"TV/tv (126).jpg",
//"TV/tv (127).jpg",
//"TV/tv (128).jpg",
//"TV/tv (129).jpg",
//"TV/tv (130).jpg",
//"TV/tv (131).jpg"
//};

vector<float>glassp{
    0.0900, 1.8350, 5.1000,
0.0050, 1.8350, 5.1000,
-0.0850, 1.8400, 5.1000,
-0.1650, 1.8300, 5.1000,
-0.2950, 1.8300, 5.1000,
-0.3700, 1.8300, 5.1000,
-0.5400, 1.8350, 5.1000,
-0.4750, 1.7750, 5.1000,
-0.4100, 1.7350, 5.1000,
-0.3550, 1.6950, 5.1000,
-0.3300, 1.6100, 5.1000,
-0.3150, 1.5150, 5.1000,
-0.3200, 1.4400, 5.1000,
-0.3250, 1.3450, 5.1000,
-0.3900, 1.2200, 5.1000,
-0.4400, 1.0550, 5.1000,
-0.5300, 0.9800, 5.1000,
-0.5800, 0.8300, 5.1000,
-0.5750, 0.7000, 5.1000,
-0.6000, 0.6200, 5.1000,
-0.6000, 0.5500, 5.1000,
-0.5950, 0.4350, 5.1000,
-0.5650, 0.3050, 5.1000,
-0.5450, 0.2300, 5.1000,
-0.5300, 0.0300, 5.1000,
-0.5350, 0.1200, 5.1000,
};

vector<float> controlPoints =
{
    0.1300, 2.0200, 5.1000,
    -0.3600, 2.0250, 5.1000,
    -0.7350, 1.8650, 5.1000,
    -0.8300, 1.5400, 5.1000,
    -0.6350, 1.2200, 5.1000,
    -0.5250, 0.9850, 5.1000,
    -0.4950, 0.6400, 5.1000,
    -0.6550, 0.4600, 5.1000,
    -0.9600, 0.3300, 5.1000
};

vector<float> ctrlBowl1 =
{
    0.2350, 1.8650, 5.1000,
    0.0800, 1.8850, 5.1000,
    -0.1300, 1.9000, 5.1000,
    -0.3100, 1.8450, 5.1000,
    -0.4000, 1.7000, 5.1000
};
vector<float> cntrlPointsCylinder
{
0.1150, 1.2650, 5.1000,
-0.0050, 1.2750, 5.1000,
-0.1250, 1.2650, 5.1000,
-0.2550, 1.2400, 5.1000,
-0.3600, 1.2100, 5.1000,
-0.4800, 1.1750, 5.1000,
-0.5650, 1.1400, 5.1000,
-0.5900, 1.0750, 5.1000,
-0.5650, 1.0350, 5.1000,
-0.5250, 0.9950, 5.1000,
-0.4600, 0.9650, 5.1000,
-0.3750, 0.9300, 5.1000,
-0.3100, 0.9100, 5.1000,
-0.2550, 0.8950, 5.1000,
-0.1650, 0.8700, 5.1000,
-0.0950, 0.8600, 5.1000,
-0.0500, 0.8600, 5.1000,
0.0050, 0.8600, 5.1000,
0.0550, 0.8600, 5.1000,
0.0950, 0.8500, 5.1000,
};
vector<float> bulb
{
-0.0350, 1.7900, 5.1000,
-0.1050, 1.6900, 5.1000,
-0.1600, 1.6050, 5.1000,
-0.2350, 1.5050, 5.1000,
-0.3100, 1.4350, 5.1000,
-0.3500, 1.3550, 5.1000,
-0.3800, 1.2600, 5.1000,
-0.3900, 1.1600, 5.1000,
-0.3700, 1.0850, 5.1000,
-0.3450, 1.0150, 5.1000,
-0.3000, 0.9600, 5.1000,
-0.2450, 0.9100, 5.1000,
-0.1600, 0.8800, 5.1000,
-0.1000, 0.8750, 5.1000,
-0.0400, 0.8800, 5.1000,
0.0050, 0.8700, 5.1000,
0.0500, 0.8650, 5.1000,
};
vector<float> bottle
{
-0.2000, 1.8950, 5.1000,
-0.2050, 1.7800, 5.1000,
-0.2100, 1.7350, 5.1000,
-0.2150, 1.6850, 5.1000,
-0.2200, 1.6250, 5.1000,
-0.2350, 1.5500, 5.1000,
-0.2350, 1.5050, 5.1000,
-0.2350, 1.4800, 5.1000,
-0.2600, 1.4450, 5.1000,
-0.3450, 1.3750, 5.1000,
-0.4050, 1.3300, 5.1000,
-0.4650, 1.2750, 5.1000,
-0.5150, 1.2150, 5.1000,
-0.5550, 1.1700, 5.1000,
-0.5700, 1.1200, 5.1000,
-0.5750, 1.0250, 5.1000,
-0.5750, 0.9450, 5.1000,
-0.5800, 0.8650, 5.1000,
-0.5900, 0.7600, 5.1000,
-0.6000, 0.6750, 5.1000,
-0.6100, 0.5500, 5.1000,
-0.6250, 0.4150, 5.1000,
-0.6300, 0.3050, 5.1000,
-0.6400, 0.1850, 5.1000,
-0.6400, 0.1600, 5.1000,
-0.6150, 0.1200, 5.1000,
-0.4900, 0.0650, 5.1000,
-0.3950, 0.0350, 5.1000,
-0.2850, 0.0250, 5.1000,
-0.2050, 0.0250, 5.1000,
-0.1500, 0.0250, 5.1000,
-0.1000, 0.0300, 5.1000,
-0.0800, 0.0300, 5.1000,
-0.1800, 1.9150, 5.1000,
-0.1750, 1.9150, 5.1000,
-0.1150, 1.9100, 5.1000,
};



vector <float> coordinates;
vector <float> normals;
vector <int> indices;
vector <float> vertices;

class point
{
public:
    point()
    {
        x = 0;
        y = 0;
    }
    int x;
    int y;
} clkpt[2];
int mouseButtonFlag = 0;
FILE* fp;
const double pi = 3.14159265389;
const int nt = 40;
const int ntheta = 20;
bool showControlPoints = true;
bool loadBezierCurvePoints = false;
bool showHollowBezier = false;
bool lineMode = false;
unsigned int bezierVAO;
unsigned int bezierCylinderVAO;
unsigned int bezierLightsVAO;
unsigned int bezierBottleVAO;
Sphere2 *sphere2,*sphere1;

Camera camera(glm::vec3(-15.0f, 13.0f, 200.0f));  //initial camera position
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float eyeX = 0.0, eyeY = 1.0, eyeZ = 3.0;
float lookAtX = 0.0, lookAtY = 0.0, lookAtZ = 0.0;
glm::vec3 V = glm::vec3(0.0f, 1.0f, 0.0f);


//transform function
glm::mat4 transform(float tr_x, float tr_y, float tr_z, float rot_x, float rot_y, float rot_z, float scal_x, float scal_y, float scal_z) {
    // Modelling Transformation
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(tr_x, tr_y, tr_z));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rot_x), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rot_y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rot_z), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(scal_x, scal_y, scal_z));
    model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    return model;
}


//points for cylinder
struct Point {
    float x;
    float y;
    float z;
};

// light definition
// positions of the point lights
glm::vec3 LightPositions[] = {
    glm::vec3(25, 100, 50),   //Direction Light

    glm::vec3(10, 14.25, 40),    //point Light1
    glm::vec3(10, 14.25, 70),    //point Light2
    glm::vec3(30, 14.25, 40),    //point Light3
    glm::vec3(30, 14.25, 70),    //point Light4

    glm::vec3(63, 29.9, 112),    //point Light5
    glm::vec3(87, 29.9, 112),    //point Light6

    glm::vec3(65, 26.25, 44),    //point Light7
    glm::vec3(65, 26.25, 65),    //point Light8
    glm::vec3(76, 23.25, 20),    //point Light9

    glm::vec3(71, 29.9, 112),    //spot Light1
    glm::vec3(79, 29.9, 112),    //spot Light2

    glm::vec3(-3, 20.25, 5),    //toilet point light
    glm::vec3(-8, 12.25, 122.5),    //family point light


};

DirLight dirlight(
    LightPositions[0].x, LightPositions[0].y, LightPositions[0].z,  // position
    0.4, 0.4, 0.4,        // specular
    0.6, 0.6, 0.6,        // specular
    0.443, 0.518, 0.522,       // specular
    //0.0f, 0.0f, 0.0f,        // emission
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    1       // light number
);

PointLight pointlight1(
    LightPositions[1].x, LightPositions[1].y, LightPositions[1].z,  // position
    1.0f, 1.0f, 1.0f,     // ambient
    0.4f, 0.2f, 0.5f,     // diffuse
    0.4f, 0.2f, 0.5f,        // specular
    //0.0f, 1.0f, 0.0f,        // emission
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    1       // light number
);
PointLight pointlight2(
    LightPositions[2].x, LightPositions[2].y, LightPositions[2].z,  // position
    1.0f, 1.0f, 1.0f,     // ambient
    0.4f, 0.2f, 0.5f,     // diffuse
    0.4f, 0.2f, 0.5f,        // specular
    //0.0f, 1.0f, 0.0f,        // emission
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    2       // light number
);

PointLight pointlight3(
    LightPositions[3].x, LightPositions[3].y, LightPositions[3].z,  // position
    1.0f, 1.0f, 1.0f,    // ambient
    0.4f, 0.2f, 0.5f,   // diffuse
    0.4f, 0.2f, 0.5f,        // specular
    //0.0f, 1.0f, 0.0f,        // emission
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    3       // light number
);
PointLight pointlight4(
    LightPositions[4].x, LightPositions[4].y, LightPositions[4].z,  // position
    1.0f, 1.0f, 1.0f,    // ambient
    0.4f, 0.2f, 0.5f,    // diffuse
    0.4f, 0.2f, 0.5f,        // specular
    //0.0f, 1.0f, 0.0f,        // emission
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    4       // light number
);

PointLight pointlight5(
    LightPositions[5].x, LightPositions[5].y, LightPositions[5].z,  // position
    1.0f, 1.0f, 0.0f,     // ambient
    1.0f, 1.0f, 0.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    //0.0f, 1.0f, 0.0f,        // emission
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    5       // light number
);

PointLight pointlight6(
    LightPositions[6].x, LightPositions[6].y, LightPositions[6].z,  // position
    1.0f, 1.0f, 0.0f,     // ambient
    1.0f, 1.0f, 0.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    //0.0f, 1.0f, 0.0f,        // emission
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    6       // light number
);

PointLight pointlight7(
    LightPositions[7].x, LightPositions[7].y, LightPositions[7].z,  // position
    1.0f, 1.0f, 0.0f,     // ambient
    1.0f, 1.0f, 0.0f,    // diffuse
    1.0f, 1.0f, 0.0f,        // specular
    //0.0f, 1.0f, 0.0f,        // emission
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    7       // light number
);

PointLight pointlight8(
    LightPositions[8].x, LightPositions[8].y, LightPositions[8].z,  // position
    1.0f, 1.0f, 0.0f,     // ambient
    1.0f, 1.0f, 0.0f,     // diffuse
    1.0f, 1.0f, 0.0f,        // specular
    //0.0f, 1.0f, 0.0f,        // emission
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    8       // light number
);

PointLight pointlight9(
    LightPositions[9].x, LightPositions[9].y, LightPositions[9].z,  // position
    1.0f, 1.0f, 0.0f,     // ambient
    1.0f, 1.0f, 0.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    //0.0f, 1.0f, 0.0f,        // emission
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    9       // light number
);


SpotLight spotlight1(
    LightPositions[10].x, LightPositions[10].y, LightPositions[10].z,  // position
    1, 1, 0,     // ambient
    1, 1, 0,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    //0.0f, 1.0f, 0.0f,        // emission
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    1       // light number
);
SpotLight spotlight2(
    LightPositions[11].x, LightPositions[11].y, LightPositions[11].z,  // position
    1, 1, 0,     // ambient
    1, 1, 0,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    //0.0f, 1.0f, 0.0f,        // emission
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    2       // light number
);

PointLight toiletpointlight(
    LightPositions[12].x, LightPositions[12].y, LightPositions[12].z,  // position
    0.965f, 0.82f, 0.624f,     // ambient
    0.965f, 0.82f, 0.624f,     // diffuse
    1.0f, 1.0f, 0.0f,        // specular
    //0.0f, 1.0f, 0.0f,        // emission
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    10      // light number
);

PointLight familypointlight(
    LightPositions[13].x, LightPositions[13].y, LightPositions[13].z,  // position
    1.0f, 1.0f, 0.0f,     // ambient
    1.0f, 1.0f, 0.0f,     // diffuse
    1.0f, 1.0f, 0.0f,        // specular
    //0.0f, 1.0f, 0.0f,        // emission
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    11      // light number
);


// light settings
bool pointLightOn1 = true;
bool pointLightOn2 = true;
bool dirLightOn = true;
bool spotLightOn = true;
bool ambientToggle = true;
bool diffuseToggle = true;
bool specularToggle = true;
bool emissionToggle = true;
bool doorOpen = false;
bool familydoorOpen = true;
bool kebabdoorOpen = true;
bool toiletdoorOpen1 = true;
bool toiletdoorOpen2 = true;
bool washroomdoorOpen = true;
bool fanOn = false;
bool droneOn = false;
bool counterdoor = false;
float counterdoorx = 0.0f;

std::vector<float> special_tree = {
    // Base of the cylinder
   0.2, 0, 0,
   0.2, 1, 0,
   0.1732, 1, 0,
   0.1732, 0, 0,
   0.1732, -1, 0,
   0.2, -1, 0,
   0.2, 0, 0,

   // Top of the cylinder
   0.2, 0, 1,
   0.2, 1, 1,
   0.1732, 1, 1,
   0.1732, 0, 1,
   0.1732, -1, 1,
   0.2, -1, 1,
   0.2, 0, 1

};

std::vector<float> tree_head = {
    -0.0050, 2.5650, 5.1000,
-0.2250, 2.4400, 5.1000,
-0.6300, 2.3150, 5.1000,
-0.9750, 2.1900, 5.1000,
-1.3150, 1.9650, 5.1000,
-1.1650, 1.8850, 5.1000,
-0.9550, 1.8900, 5.1000,
-0.5800, 1.8900, 5.1000,
-0.1550, 1.8700, 5.1000,
-0.0600, 1.8300, 5.1000,
-0.4650, 1.5600, 5.1000,
-0.8200, 1.4200, 5.1000,
-1.2250, 1.2050, 5.1000,
-1.5500, 0.9450, 5.1000,
-1.6750, 0.7250, 5.1000,
-1.7050, 0.5350, 5.1000,
-1.6850, 0.4050, 5.1000,
-1.4500, 0.3000, 5.1000,
-1.2300, 0.3000, 5.1000,
-0.8050, 0.3000, 5.1000,
};




// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;

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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "3D Food Court", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

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

    Shader lightingShaderWithTexture("vertexShaderForPhongShadingWithTexture.vs", "fragmentShaderForPhongShadingWithTexture.fs");
    Shader lightingShader("vertexShaderForPhongShading.vs", "fragmentShaderForPhongShading.fs");
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");
    
    //textures
    string wall = "images/wall.jpg";
    string f_tiles = "images/floor_m2.jpg";//cng
    string fnameImage = "images/banner.jpg";
    string floorImage = "images/floor.jpg";
    string bricks1 =  "images/hill.jpg";//cng
    string court2 = "images/ufo.jpg";//chag with court 4-2
    string court2Upper = "images/foodCourt.jpg";//cng
    string court3 = "images/court3.jpg";
    string court4 = "images/court4.jpg";
    string court5 = "images/court4-2.jpg";//cng
    string roof = "images/court4-2.jpg";
    string wood = "images/wood.jpg";
    string sofa = "images/bed.jpg";//cng red
    string pic1 = "images/pic1.jpg";
    string pic2 = "images/pic2.jpg";
    string pic3 =  "images/pic3.jpg";
    string pic4 = "images/pic4.jpg";
    string pic5 =   "images/pic5.jpg";
    string chula =  "images/chula.jpg";
    string oven =   "images/oven.jpg";
    string basin =   "images/basin.jpg";
    string coke =   "images/coke.jpg";
    string coal =  "images/coal.jpg";
    string tv =  "images/tv.jpg";
    string wallmat1 =   "images/wallmat1.jpg";//cng
    string wood2 =   "images/wood2.jpg";
    string ceil =  "images/ceil.jpg";
    string toilet =  "images/toilet.jpg";
    string door =   "images/door.jpg";
    string music =  "images/music.jpg";
    string road =  "images/road.jpg";
    string grass =   "images/grass.jpg";
    string sky =  "images/sky.jpg";
    string clock =  "images/clock.jpg";
    string sound =  "images/sound.jpg";
    string chips =  "images/chips.jpg";
    string chips2 =  "images/chips2.jpg";
    string chips3 =  "images/chips3.jpg";


    //tree

    string diffuseMapPath_tree = "tree.jpg";
    string specularMapPath_tree = "tree.jpg";
    unsigned int diffMap_tree = loadTexture(diffuseMapPath_tree.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap_tree = loadTexture(specularMapPath_tree.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Curve SpecialTree = Curve(special_tree, diffMap_tree, specMap_tree, 5);


    string diffuseMapPath_treeHead = "tree2.jpg";
    string specularMapPath_treeHead = "tree2.jpg";
    unsigned int diffMap_treeHead = loadTexture(diffuseMapPath_treeHead.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap_treeHead = loadTexture(specularMapPath_treeHead.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Curve TreeHead = Curve(tree_head, diffMap_treeHead, specMap_treeHead, 5);
    
    unsigned int floor_tiles = loadTexture(f_tiles.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int roof_tex = loadTexture(roof.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int floor_tex = loadTexture(floorImage.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int wall_tex = loadTexture(wall.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int bricks1_tex = loadTexture(bricks1.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int name_tex = loadTexture(fnameImage.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int court2_tex = loadTexture(court2.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int court3_tex = loadTexture(court3.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int court2Upper_tex = loadTexture(court2Upper.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int court4_tex = loadTexture(court4.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int court5_tex = loadTexture(court5.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int wood_tex = loadTexture(wood.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int sofa_tex = loadTexture(sofa.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int pic1_tex = loadTexture(pic1.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int pic2_tex = loadTexture(pic2.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int pic3_tex = loadTexture(pic3.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int pic4_tex = loadTexture(pic4.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int pic5_tex = loadTexture(pic5.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int chula_tex = loadTexture(chula.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int oven_tex = loadTexture(oven.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int basin_tex = loadTexture(basin.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int coke_tex = loadTexture(coke.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int coal_tex = loadTexture(coal.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int tv_tex = loadTexture(tv.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int wallmat1_tex = loadTexture(wallmat1.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int wood2_tex = loadTexture(wood2.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int ceil_tex = loadTexture(ceil.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int toilet_tex = loadTexture(toilet.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int door_tex = loadTexture(door.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int music_tex = loadTexture(music.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int road_tex = loadTexture(road.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int sky_tex = loadTexture(sky.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int grass_tex = loadTexture(grass.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int clock_tex = loadTexture(clock.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int sound_tex = loadTexture(sound.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int chips_tex = loadTexture(chips.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int chips2_tex = loadTexture(chips2.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int chips3_tex = loadTexture(chips3.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);



    //set cube attributes
    Cube tiles_cube = Cube(floor_tiles, floor_tiles, 32.0, 0.0f, 0.0f, 5.0f, 10.0f);
    Cube tiles_cube_chiba = Cube(floor_tiles, floor_tiles, 32.0, 0.0f, 0.0f, 2.0f, 2.0f);
    Cube floor_tex_cube = Cube(floor_tex, floor_tex, 32.0, 0.0f, 0.0f, 10.0f, 10.0f);
    Cube floor_tex_cube_chipa = Cube(floor_tex, floor_tex, 32.0, 0.0f, 0.0f, 1.5f, 1.5f);
    Cube floor_tex_cube_chipa1 = Cube(floor_tex, floor_tex, 32.0, 0.0f, 0.0f, 5.0f, 5.0f);
    Cube wall_cube = Cube(wall_tex, wall_tex, 32.0, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube bricks1_cube = Cube(bricks1_tex, bricks1_tex, 32.0, 0.0f, 0.0f, 3.0f, 3.0f);
    Cube bricks1_cube_chipa = Cube(bricks1_tex, bricks1_tex, 32.0, 0.0f, 0.0f, 1.5f, 3.0f);
    Cube bricks1_cube_chipa1 = Cube(bricks1_tex, bricks1_tex, 32.0, 0.0f, 0.0f, 3.0f, 1.0f);
    Cube bricks1_cube_chipa2 = Cube(bricks1_tex, bricks1_tex, 32.0, 0.0f, 0.0f, 8.0f, 1.0f);
    Cube fName = Cube(name_tex, name_tex, 32.0, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube RightSideWall1 = Cube(bricks1_tex, bricks1_tex, 32.0, 0.0f, 0.0f, 5.0f, 2.0f);
    Cube RightSideWall2 = Cube(floor_tex, floor_tex, 32.0, 0.0f, 0.0f, 10.0f, 0.3f);
    Cube RightSideWall3 = Cube(floor_tex, floor_tex, 32.0, 0.0f, 0.0f, 5.0f, 0.3f);
    Cube RightSideWall4 = Cube(floor_tex, floor_tex, 32.0, 0.0f, 0.0f, 1.0f, 0.3f);
    Cube court2_cube = Cube(court2_tex, court2_tex, 32.0, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube court2Upper_cube = Cube(court2Upper_tex, court2Upper_tex, 32.0, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube court3_cube = Cube(court3_tex, court3_tex, 32.0, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube court4_cube = Cube(court4_tex, court4_tex, 32.0, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube court42_cube = Cube(roof_tex, roof_tex, 32.0, 0.0f, 0.0f, 1.0f, 0.8f);
    Cube court5_cube = Cube(court5_tex, court5_tex, 32.0, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube wood_cube = Cube(wood_tex, wood_tex, 32.0, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube sofa_cube = Cube(sofa_tex, sofa_tex, 32.0, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube pic1_cube = Cube(pic1_tex, pic1_tex, 32.0, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube pic2_cube = Cube(pic2_tex, pic2_tex, 32.0, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube pic3_cube = Cube(pic3_tex, pic3_tex, 32.0, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube pic4_cube = Cube(pic4_tex, pic4_tex, 32.0, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube pic5_cube = Cube(pic5_tex, pic5_tex, 32.0, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube chula_cube = Cube(chula_tex, chula_tex, 32.0, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube oven_cube = Cube(oven_tex, oven_tex, 32.0, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube basin_cube = Cube(basin_tex, basin_tex, 32.0, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube coke_cube = Cube(coke_tex, coke_tex, 32.0, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube coal_cube = Cube(coal_tex, coal_tex, 32.0, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube tv_cube = Cube(tv_tex, tv_tex, 32.0, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube wallmat1_cube = Cube(wallmat1_tex, wallmat1_tex, 32.0, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube wood2_cube = Cube(wood2_tex, wood2_tex, 32.0, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube ceil_cube = Cube(ceil_tex, ceil_tex, 32.0, 0.0f, 0.0f, 6.0f, 8.0f);
    Cube ceil_cube2 = Cube(ceil_tex, ceil_tex, 32.0, 0.0f, 0.0f, 3.0f, 1.0f);
    Cube toilet_cube = Cube(toilet_tex, toilet_tex, 32.0, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube door_cube = Cube(door_tex, door_tex, 32.0, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube music_cube = Cube(music_tex, music_tex, 32.0, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube road_cube = Cube(road_tex, road_tex, 32.0, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube sky_cube = Cube(sky_tex, sky_tex, 32.0, 0.0f, 0.0f, 1.0f, 1.0f); 
    Cube grass_cube = Cube(grass_tex, grass_tex, 32.0, 0.0f, 0.0f, 5.0f, 5.0f);
    Cube clock_cube = Cube(clock_tex, clock_tex, 32.0, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube soundbox_cube = Cube(sound_tex, sound_tex, 32.0, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube chips_cube = Cube(chips_tex, chips_tex, 32.0, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube chips2_cube = Cube(chips2_tex, chips2_tex, 32.0, 0.0f, 0.0f, 1.0f, 1.0f);
    Cube chips3_cube = Cube(chips3_tex, chips3_tex, 32.0, 0.0f, 0.0f, 1.0f, 1.0f);

    
    //object cube declaration
    Cube normalCube;
    Cube floor = Cube(glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(0.8f, 0.8f, 0.8f), 32, 1.0f);
    Cube floorExtension = Cube(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.1f, 0.1f, 0.1f), 32, 1.0f);
    Cube glassDoor = Cube(glm::vec3(0.391f, 0.391f, 0.432f), glm::vec3(0.391f, 0.391f, 0.432f), glm::vec3(0.391f, 0.391f, 0.432f), 32, 0.5f);
    //Cube wall1 = Cube(glm::vec3(0.941f, 0.773f, 0.373f), glm::vec3(0.941f, 0.773f, 0.373f), glm::vec3(0.941f, 0.773f, 0.373f), 32, 1.0f);
    //sundor Cube wall1 = Cube(glm::vec3(0.286f, 0.298f, 0.31f), glm::vec3(0.286f, 0.298f, 0.31f), glm::vec3(0.286f, 0.298f, 0.31f), 32, 1.0f);

    Cube wall1 = Cube(glm::vec3(0.082f, 0.149f, 0.196f), glm::vec3(0.082f, 0.149f, 0.196f), glm::vec3(0.082f, 0.149f, 0.196f), 32, 1.0f);
    Cube white_cube = Cube(glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), glm::vec3(1, 1, 1), 32, 1.0f);
    Cube wall2 = Cube(glm::vec3(0.435f, 0.231f, 0.231f), glm::vec3(0.435f, 0.231f, 0.231f), glm::vec3(0.435f, 0.231f, 0.231f), 32, 1.0f);
    //Cube court1 = Cube(glm::vec3(0.976f, 0.671f, 0.0f), glm::vec3(0.976f, 0.671f, 0.0f), glm::vec3(0.976f, 0.671f, 0.0f), 32, 1.0f);
    Cube court1 = Cube(glm::vec3(0.529f, 0.808f, 0.922f), glm::vec3(0.529f, 0.808f, 0.922f), glm::vec3(0.529f, 0.808f, 0.922f), 32, 1.0f);
    Cube court3Cube = Cube(glm::vec3(0.643f, 0.204f, 0.227f), glm::vec3(0.643f, 0.204f, 0.227f), glm::vec3(0.643f, 0.204f, 0.227f), 32, 1.0f);
    Cube court4Cube = Cube(glm::vec3(0.361f, 0.0f, 0.004f), glm::vec3(0.361f, 0.0f, 0.004f), glm::vec3(0.361f, 0.0f, 0.004f), 32, 1.0f);

    //Cube court2 = Cube(glm::vec3(0.196f, 0.835f, 0.094f), glm::vec3(0.196f, 0.835f, 0.094f), glm::vec3(0.196f, 0.835f, 0.094f), 32, 1.0);

    //Cube wall_cube = Cube(wall_tex, wall_tex, 32.0, 0.0f, 0.0f, 20.0f, 10.0f);
    Cube chair_cube = Cube(glm::vec3(0.22f, 0.22f, 0.22f), glm::vec3(0.22f, 0.22f, 0.22f), glm::vec3(0.22f, 0.22f, 0.22f), 32, 1.0f);
    Sphere globe1 = Sphere(1.0f, 36, 18, glm::vec3(0.941f, 0.824f, 0.745f), glm::vec3(0.941f, 0.824f, 0.745f), glm::vec3(0.941f, 0.824f, 0.745f), 32.0f);
    Sphere sphere = Sphere();
    Cylinder cylinder1 = Cylinder();
    Paraboloid parabola(2.0f, 2.0f, 2.0f, 50, 50, 1.0f, 0.9f, 0.9f);

    int x, z;
    //Fractile part

    string rootStr = "images/root1.png";
    string treeStr = "images/tree2.png";
    unsigned int treeTex = loadTexture(treeStr.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube tree = Cube(treeTex, treeTex, 32.0, 0.0f, 0.0f, 5.0f, 10.0f);
    
    Sphere2 sphere_2(1.0, 36, 18, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f, treeTex, treeTex, 0, 1, 0, 1);
    sphere_2.setDefaults();
    sphere_2.setTexture(treeTex, treeTex);
    sphere1 = &sphere_2;

    unsigned int rootTex = loadTexture(rootStr.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube root = Cube(rootTex, rootTex, 32.0, 0.0f, 0.0f, 5.0f, 10.0f);


    //Curvy object using bezeir
    string bowlStr = "images/popcornbowl.png";
    unsigned int bowlTex = loadTexture(bowlStr.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
   
    string glassStr = "images/glass.png";
    unsigned int glassTex = loadTexture(glassStr.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int bottleTex = loadTexture(glassStr.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);


   string diffuseMapPath = "images/sky.jpg";
   unsigned int diffMap3 = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
   Sphere2 sp(1.0, 36, 18, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f, diffMap3, diffMap3, 0, 1, 0, 1);
   sp.setDefaults();
   sp.setTexture(diffMap3, diffMap3);
   sphere2 = &sp;

    // Mesh Model Shader
    stbi_set_flip_vertically_on_load(true);
    Shader modelShader("1.model_loading.vs", "1.model_loading.fs");
    Model drone("drone/scene.gltf");




    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(struct Point), (void*)0);
    glEnableVertexAttribArray(0);

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
       // glClearColor(0.62f, 0.62f, 0.52f, 1.0f);
        glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        int pos = camera.Position.z;
        printf("position camera %d", pos);
        if (pos > 135.0f)
            counterdoor = false;
        else
            counterdoor = true;


        //projection matrix and view matrix
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 300.0f);
        glm::mat4 view = camera.GetViewMatrix();

        //light declarations
        //Lighting Shader With Texture
        lightingShaderWithTexture.use();
        lightingShaderWithTexture.setVec3("viewPos", camera.Position);
        lightingShaderWithTexture.setMat4("projection", projection);
        lightingShaderWithTexture.setMat4("view", view);

        pointlight1.setUpPointLight(lightingShaderWithTexture);
        pointlight2.setUpPointLight(lightingShaderWithTexture);
        pointlight3.setUpPointLight(lightingShaderWithTexture);
        pointlight4.setUpPointLight(lightingShaderWithTexture);
        pointlight5.setUpPointLight(lightingShaderWithTexture);
        pointlight6.setUpPointLight(lightingShaderWithTexture);
        pointlight7.setUpPointLight(lightingShaderWithTexture);
        pointlight8.setUpPointLight(lightingShaderWithTexture);
        pointlight9.setUpPointLight(lightingShaderWithTexture);
        toiletpointlight.setUpPointLight(lightingShaderWithTexture);
        familypointlight.setUpPointLight(lightingShaderWithTexture);
        
        spotlight1.setUpPointLight(lightingShaderWithTexture);
        spotlight2.setUpPointLight(lightingShaderWithTexture);

        dirlight.setUpPointLight(lightingShaderWithTexture);
        

        //Lighting Shader Without Texture
        lightingShader.use();
        lightingShader.setVec3("viewPos", camera.Position);
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);

        pointlight1.setUpPointLight(lightingShader);
        pointlight2.setUpPointLight(lightingShader);
        pointlight3.setUpPointLight(lightingShader);
        pointlight4.setUpPointLight(lightingShader);
        pointlight5.setUpPointLight(lightingShader);
        pointlight6.setUpPointLight(lightingShader);
        pointlight7.setUpPointLight(lightingShader);
        pointlight8.setUpPointLight(lightingShader);
        pointlight9.setUpPointLight(lightingShader);
        toiletpointlight.setUpPointLight(lightingShader);
        familypointlight.setUpPointLight(lightingShader);

        spotlight1.setUpPointLight(lightingShader);
        spotlight2.setUpPointLight(lightingShader);
  
        dirlight.setUpPointLight(lightingShader);


        
 
        // Modelling Transformation
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
        translateMatrix = glm::translate(identityMatrix, glm::vec3(2.42, 0.11, 8.18f));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix;


        //Importing Mesh models

        modelShader.use();
        //// view/projection transformations
        glm::mat4 Mprojection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 Mview = camera.GetViewMatrix();
        modelShader.setMat4("projection", projection);
        modelShader.setMat4("view", Mview);

        //drone
        model = transform(dx,dy,dz, 0, ry, 0, 0.05, 0.05, 0.05);
        modelShader.setMat4("model", model);
        drone.Draw(modelShader);
        //Mesh model ends


        //inside room point lights
        //light1
        for (int i = 0; i < 2; i++) {
           // model = transform(10, 20.25, 40+30*i, 00.0f, 0.0f, 0.0f, 0.04, -0.15, 0.04);
            //cylinder1.drawCylinder(lightingShader, model);
            //lights
            model = transform(10, 14.25, 40 + 30 * i, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2, 2, 2);
            lightingShader.setMat4("model", model);
            lightingShader.use();
            lightingShader.setVec3("material.ambient", glm::vec3(1, 1, 1));
            lightingShader.setVec3("material.diffuse", glm::vec3(1, 1, 1));
            lightingShader.setVec3("material.specular", glm::vec3(1, 1, 1));
            lightingShader.setFloat("material.shininess", 32.0f);
            glBindVertexArray(bezierLightsVAO);
            glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
            glBindVertexArray(0);
        }
        for (int i = 0; i < 2; i++) {
           // model = transform(30, 20.25, 40 + 30 * i, 00.0f, 0.0f, 0.0f, 0.04, -0.15, 0.04);
           // cylinder1.drawCylinder(lightingShader, model);
            //lights
            model = transform(30, 14.25, 40 + 30 * i, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2, 2, 2);
            lightingShader.setMat4("model", model);
            lightingShader.use();
            lightingShader.setVec3("material.ambient", glm::vec3(1, 1, 1));
            lightingShader.setVec3("material.diffuse", glm::vec3(1, 1, 1));
            lightingShader.setVec3("material.specular", glm::vec3(1, 1, 1));
            lightingShader.setFloat("material.shininess", 32.0f);
            glBindVertexArray(bezierLightsVAO);
            glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
            glBindVertexArray(0);
        }

        //grass
        model = transform(-100, -6, -50, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 250, -0.2, 210);
        grass_cube.drawCubeWithTexture(lightingShaderWithTexture, model);

        //floor-------------------------------------------------------------------------------------
        //todo
        model = transform(-25, -6, -45, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 85, 5.8, 175);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        //floor er uporer texture cube
        model = transform(-25, -0.2, -45, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 85, 0.2, 175);
        tiles_cube.drawCubeWithTexture(lightingShaderWithTexture, model);

        //floor front extension left
        model = transform(-25, -0.2, 120, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 55, -5.8, 20);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(-25, 0, 115, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 35, -0.2, 25);
        tiles_cube_chiba.drawCubeWithTexture(lightingShaderWithTexture, model);

        //floor front extension right
        model = transform(60, 0, 120, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -5, -6, 20);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);

        model = transform(10, 0, 115, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 50, -0.2, 5);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(10, 0, 120, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 20, -0.2, 20);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        //Stairs 
        //z axis statirs

        //left side wall
        model = transform(-25, 0, -45, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 18, 145);
        wall1.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(-25, 18, -45, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 3, 145);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(-24, 18, 100, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 33, 3, -1);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(10, 18, 99, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -1, 3, 16);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        //left back wall todo

        model = transform(-2, 0, -45, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 18, 45);
        wall1.drawCubeWithMaterialisticProperty(lightingShader, model);
        // back wall 2
        model = transform(-24, 0, -45, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 84, 18, 1);
        wall1.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(-24, 18, -45, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 84, 3, 1);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);

        //right back wall
        model = transform(60, 0, -45, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -1, 18, 45);
        wall1.drawCubeWithMaterialisticProperty(lightingShader, model);

        //Curvy Objects
        Curve bowl(ctrlBowl1, bowlTex, bowlTex, 1.0f);
        model = transform(5, 10, 0, 180, 0, 0, 2, 5, 4);
        //bowl.draw(lightingShaderWithTexture, model, glm::vec3(1.0, 0.0, 1.0));

        Curve glass(glassp, glassTex, glassTex, 1.0f);
        model = transform(5, 12, 0, 180, 0, 0, 0.5, 0.7, 0.5);
        //glass.draw(lightingShaderWithTexture, model, glm::vec3(1.0, 0.0, 1.0));

        Curve bottles(bottle, bottleTex, bottleTex, 1.0f);
        model = transform(5, 14, 0, 0, 0, 0, 0.5, 0.7, 0.5);
        //bottles.draw(lightingShaderWithTexture, model, glm::vec3(1.0, 0.0, 1.0));*/
        

       Curve lights(bulb, bottleTex, bottleTex, 1.0f);
        model = transform(5, 16, 0, 0, 0, 0, 0.5, 0.7, 0.5);
        //lights.draw(lightingShaderWithTexture, model, glm::vec3(1.0, 0.0, 1.0));*/



        //Fractile Tree
        model = transform(-40, -6,130, 0, 0, 0, 1, 1, 1);
        drawTreeWithFractiles(tree, root, lightingShaderWithTexture,model, 0, 0,0, 0);

        model = transform(70, -6, 130, 0, 0, 0, 1, 1, 1);
        drawTreeWithFractiles(tree, root, lightingShaderWithTexture, model, 0, 0, 0, 0);

  
        model = transform(10, 10, 15, 0, 0, 0, 0.3, 0.3, 0.3);
        sphere2->drawSphereWithTexture(lightingShaderWithTexture, model);





        //Right wall
        model = transform(60, 0, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -1, 18, 10);
        wall1.drawCubeWithMaterialisticProperty(lightingShader, model);

        // maje 20 size dorja

        model = transform(60, 0, 30, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -1, 18, 85);
        wall1.drawCubeWithMaterialisticProperty(lightingShader, model);

        model = transform(60.1, 18, 115, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -1.1, 5, -42);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);

        model = transform(60.1, 18, 73, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -1.1, 5, -34);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);

        model = transform(60.1, 18, 115, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -50.1, 3, -1);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);

        //right side cipa.
        model = transform(60, 18, 115, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.1, -18, -5);
        bricks1_cube_chipa.drawCubeWithTexture(lightingShaderWithTexture, model);

      

        //main door wall right
        model = transform(60, 0, 115, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -5, 18, -1);
        wall1.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(60.1, 0, 115, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -5.1, 18, 0.2);
        bricks1_cube_chipa.drawCubeWithTexture(lightingShaderWithTexture, model);

        //main door wall left
        model = transform(10, 0, 115, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 20, 18, -1);
        wall1.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(10, 0, 115, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 20, 18, 0.2);
        bricks1_cube.drawCubeWithTexture(lightingShaderWithTexture, model);



        //right side poster main door
        model = transform(59, 5, 90, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -0.1, 10, 15);
        wallmat1_cube.drawCubeWithTexture(lightingShaderWithTexture, model);

        //main entrance door
        //upper cube
        model = transform(55, 0, 115, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -25, 0.5, -1);
        wall1.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(55, 18, 115, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -25, -0.5, -1);
        wall1.drawCubeWithMaterialisticProperty(lightingShader, model);

        //2 sliders
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        //float r = 0.0f;
        //lobby door
        if (counterdoor && counterdoorx < 90.0f)
        {
            counterdoorx += 10.0f;
        }
        if (!counterdoor && counterdoorx > 0.0f)
        {
            counterdoorx -= 10.0f;
        }
        model = transform(55.01 , 0.5, 115, rotateAngle_X, 0 - counterdoorx, rotateAngle_Z, -12.5, 17, -0.5);
        glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(30.51 , 0.5, 115, rotateAngle_X, 0 + counterdoorx, rotateAngle_Z, 12.5, 17, -0.5);
        glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);
        glDisable(GL_BLEND);
    

        //my fan
        //ceiling hanger

        model = transform(17.5, 21, 50, 00.0f, 0.0f, 0.0f, 0.25, -0.15, 0.25);
        cylinder1.drawCylinder(lightingShader, model);

        //fan base1
        model = transform(17.5, 15.75, 50, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 3, 2.5, 3);
        lightingShader.setMat4("model", model);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        //upper cup
        model = transform(17.5, 16.5, 50, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1.5, 4, 1.5);
        lightingShader.setMat4("model", model);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);
        //fan blade1
        model = transform(17.5, 18.5, 50, 0, ang, 0, 6, -0.1, 0.75);
        glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(17.5, 18.5, 50, 0, ang, 0, 6, -0.1, -0.75);
        glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);
        //fan blade 2
        model = transform(17.5, 18.5, 50, 0, 60+ang, 0, -6, -0.1, 0.75);
        glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(17.5, 18.5, 50, 0, 60 + ang, 0, -6, -0.1, -0.75);
        glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);
        //fan blade 3
        model = transform(17.5, 18.5, 50, 0, -60 + ang, 0, -6, -0.2, 0.75);
        glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(17.5, 18.5, 50, 0, -60 + ang, 0, -6, -0.2, -0.75);
        glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);

        //----------------fan2-------------
        //ceiling hanger
        model = transform(17.5, 21, 70, 00.0f, 0.0f, 0.0f, 0.25, -0.15, 0.25);
        cylinder1.drawCylinder(lightingShader, model);
        //fan base
        model = transform(17.5, 15.75, 70, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 3, 2.5, 3);
        lightingShader.setMat4("model", model);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        //upper cup
        model = transform(17.5, 16.5, 70, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1.5, 4, 1.5);
        lightingShader.setMat4("model", model);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierCylinderVAO);
        glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        //fan blade1
        model = transform(17.5, 18.5, 70, 0, ang, 0, 6, -0.1, 0.75);
        glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(17.5, 18.5, 70, 0, ang, 0, 6, -0.1, -0.75);
        glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);
        //fan blade 2
        model = transform(17.5, 18.5, 70, 0, 60 + ang, 0, -6, -0.1, 0.75);
        glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(17.5, 18.5, 70, 0, 60 + ang, 0, -6, -0.1, -0.75);
        glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);
        //fan blade 3
        model = transform(17.5, 18.5, 70, 0, -60 + ang, 0, -6, -0.1, 0.75);
        glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(17.5, 18.5, 70, 0, -60 + ang, 0, -6, -0.1, -0.75);
        glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);


        //angle
        if (fanOn) {
            ang += 20;
            ang = ang % 360;
        }

        //Stairs 
        //z axis statirs
        
        model = transform(30, -6, 140, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 25, 0.8, -20);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(30, -5, 137, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 25, 0.8, -17);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(30, -4, 134, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 25, 0.8, -14);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(30, -3, 131, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 25, 0.8, -11);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(30, -2, 128, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 25, 0.8, -8);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(30, -1, 125, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 25, 1, -5);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);

        model = transform(30, -5.2, 140, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 25, 0.2, -20);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(30, -4.2, 137, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 25, 0.2, -17);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(30, -3.2, 134, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 25, 0.2, -14);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(30, -2.2, 131, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 25, 0.2, -11);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(30, -1.2, 128, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 25, 0.2, -8);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        



        //left side courts
        //first counter widht
        //ovenCookerFirst

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-24, 0, 55.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1, 1));
        OvenCooker(floorExtension, chula_cube, oven_cube, basin_cube, lightingShader, lightingShaderWithTexture, translateMatrix * scaleMatrix);

        //coke fridge
        model = transform(-24, 0, 76, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 4, 11, 5);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(-20, 2, 76.25, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.1, 8.65, 4.5);
        coke_cube.drawCubeWithTexture(lightingShaderWithTexture, model);

        //showcase
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-24, 8, 73.5));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(00.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1, -0.85));
        ShowcaseRack(cylinder1, chips_cube, chips2_cube, chips3_cube, wood2_cube, lightingShaderWithTexture, translateMatrix * scaleMatrix * rotateYMatrix);


        model = transform(-24, 0, 85, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 19, 7, -1);
        court1.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(-24, 0, 85.1, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 20, 7, -0.1);
        court1.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(-24, 7, 86, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 20, 0.5, -4);
        glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);

        model = transform(-24, 21, 85, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 19, -6, -1);
        court1.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(-24, 15, 86, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 21, -0.5, -2);
        glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);

        //first counter length
        model = transform(-5, 0, 85, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 7, -30);
        court2Upper_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        model = transform(-7, 7, 86, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 4, 0.5, -31);
        glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);

        model = transform(-5, 21, 85, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, -6, -30);
        court1.drawCubeWithMaterialisticProperty(lightingShader, model);

        model = transform(-5, 15, 85, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2, -0.5, -30);
        glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);

        //second court length

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-24, 0, 54.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1, -1));
        OvenCooker(floorExtension, chula_cube, oven_cube, basin_cube, lightingShader, lightingShaderWithTexture, translateMatrix * scaleMatrix);

        //showcase
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-24, 8, 45));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(00.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1, -0.95));
        ShowcaseRack(cylinder1, chips_cube, chips2_cube, chips3_cube, wood2_cube, lightingShaderWithTexture, translateMatrix * scaleMatrix * rotateYMatrix);

        //coke fridge
        model = transform(-24, 0, 25, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 4, 11, 5);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(-20, 2, 25.25, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.1, 8.65, 4.5);
        coke_cube.drawCubeWithTexture(lightingShaderWithTexture, model);



        model = transform(-5, 0, 55, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 7, -30);
        court2_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        model = transform(-7, 7, 55, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 4, 0.5, -30);
        glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);

        model = transform(-5, 15, 55, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 6, -30);
        court2_cube.drawCubeWithTexture(lightingShaderWithTexture, model);

        model = transform(-3, 15, 55, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -2, -0.5, -30);
        glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);

        //middle partitions
        model = transform(-24, 0, 54.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 19, 18, 1);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        //right partitions
        model = transform(-25, 0, 25, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 21, 18, -1);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);


        //family corner
        //right top

        //right bottom
        model = transform(30.1, 0, 139, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -1.1, 5, -15);
        bricks1_cube_chipa1.drawCubeWithTexture(lightingShaderWithTexture, model);
        //left bottom side wall
        model = transform(-25, 0, 110, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1.1, 5, 29);
        bricks1_cube_chipa1.drawCubeWithTexture(lightingShaderWithTexture, model);
        //right bottom side wall
        model = transform(10, 0, 115, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -1, 5, 24);
        bricks1_cube_chipa1.drawCubeWithTexture(lightingShaderWithTexture, model);

        model = transform(-25, 5, 110, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1.1, 1, 30);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        //right bottom side wall
        model = transform(10, 5, 115, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -1, 1, 25);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);

        //front short
        model = transform(30, 0, 140, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -55, 5, -1);
        bricks1_cube_chipa2.drawCubeWithTexture(lightingShaderWithTexture, model);

        //family entrance left back
        model = transform(-25, 0, 100, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 10, 18, -1);
        wall1.drawCubeWithMaterialisticProperty(lightingShader, model);
        
        //family entrance left front 
        model = transform(-24, 0, 100, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 9, 18, 0.1);
        bricks1_cube_chipa.drawCubeWithTexture(lightingShaderWithTexture, model);
        model = transform(-24, 0, 100, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.1, 18, 10);
        bricks1_cube_chipa.drawCubeWithTexture(lightingShaderWithTexture, model);
        
        //family entrance right
        model = transform(10, 0, 100, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -10, 18, -1);
        wall1.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(9, 0, 100, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -9, 18, 0.1);
        bricks1_cube_chipa.drawCubeWithTexture(lightingShaderWithTexture, model);

        //right family entrance wall


        int i;
        for (i = 0; i < 9; i++) {
            //front top
            model = transform(-25, 18, 140 - 3 * i, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 35.1, -1, -1);
            floor.drawCubeWithMaterialisticProperty(lightingShader, model);
            //front left
            model = transform(-25, 18, 140 - 3 * i, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1.1, -12, -1);
            floor.drawCubeWithMaterialisticProperty(lightingShader, model);
            //front right
            model = transform(10, 18, 140 - 3 * i, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -1, -12, -1);
            floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        }

      
        //lights
        model = transform(-8, 12.25, 121.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2, 2, 2);
        lightingShader.setMat4("model", model);
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1, 1, 1));
        lightingShader.setVec3("material.diffuse", glm::vec3(1, 1, 1));
        lightingShader.setVec3("material.specular", glm::vec3(1, 1, 1));
        lightingShader.setFloat("material.shininess", 32.0f);
        glBindVertexArray(bezierLightsVAO);
        glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
        glBindVertexArray(0);

        //front left
        model = transform(-25, 18, 140 - 3 * i, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1.1, -12, -1);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        //front top
        model = transform(-25, 18, 140 - 3 * i, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 33.9, -1, -1);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        i++;
        //front left
        model = transform(-25, 18, 140 - 3 * i, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1.1, -12, 0.1);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        int t = 4;
        while (t--) {
            //front top
            model = transform(-23.9, 18, 140 - 3 * i, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 32.8, -1, -1);
            floor.drawCubeWithMaterialisticProperty(lightingShader, model);
            i++;
        }

        //family sofa
        x = -22, z = 105;
        for (int i = 0; i < 2; i++) {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(x, 0, z));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 1.5, 1.5));
            Sofa(sofa_cube, lightingShaderWithTexture, translateMatrix * scaleMatrix);

            translateMatrix = glm::translate(identityMatrix, glm::vec3(x, 0, z + 4));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 1, 1.5));
            Table(floorExtension, lightingShader, translateMatrix * scaleMatrix);

            translateMatrix = glm::translate(identityMatrix, glm::vec3(x, 0, z + 14));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 1.5, -1.5));
            Sofa(sofa_cube, lightingShaderWithTexture, translateMatrix * scaleMatrix);

            z += 18;
        }
        x = -2, z = 105;
        for (int i = 0; i < 2; i++) {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(x, 0, z));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 1.5, 1.5));
            Sofa(sofa_cube, lightingShaderWithTexture, translateMatrix * scaleMatrix);

            translateMatrix = glm::translate(identityMatrix, glm::vec3(x, 0, z + 4));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 1, 1.5));
            Table(floorExtension, lightingShader, translateMatrix * scaleMatrix);

            translateMatrix = glm::translate(identityMatrix, glm::vec3(x, 0, z + 14));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 1.5, -1.5));
            Sofa(sofa_cube, lightingShaderWithTexture, translateMatrix * scaleMatrix);

            z += 18;
        }


        //parabola
        glm::mat4 modelForhyperboloid = glm::mat4(1.0f);
        //modelForhyperboloid = glm::translate(modelForhyperboloid, glm::vec3(-1.0f, 17.0f, 120.0f));
        modelForhyperboloid = transform(-6.0f, 17.5f, 122.0f, 180.0f, 0.0f, 0.0f, 1.0, 1.0, 1.0);
        parabola.drawParaboloid(lightingShader, modelForhyperboloid);

        //washrooms extension****


        //*******whashroom
        //pan floor 1
        model = transform(-19-5, 0, -44, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 10, 1, 12);
        white_cube.drawCubeWithMaterialisticProperty(lightingShader, model);
        //pan 1
        model = transform(-19-4, 1, -42.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 6, 0.05, 7);
        toilet_cube.drawCubeWithTexture(lightingShaderWithTexture, model);

        model = transform(-19-5, 1, -32, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 17, -12);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        //washroom door
        if (toiletdoorOpen1) {
            model = transform(-19-4, 1, -31, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 9, 17, 0.5);
            door_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else {
            model = transform(-19 - 4, 1, -31, rotateAngle_X, 90, rotateAngle_Z, 9, 17, 0.5);
            door_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        }

        //uporer base
        model = transform(-19-5, 18, -33, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 22, 3, 1);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);

        model = transform(-7-5, 0, -44, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -2, 21, 12);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);

        //pan floor2
        model = transform(-7-5, 0, -44, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 10, 1, 12);
        white_cube.drawCubeWithMaterialisticProperty(lightingShader, model);
        //pan2
        model = transform(-7-4, 1, -42.2, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 6, 0.05, 7);
        toilet_cube.drawCubeWithTexture(lightingShaderWithTexture, model);

        model = transform(3-5, 0, -44, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -1, 21, 12);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);

        if (toiletdoorOpen2) {
            model = transform(-3-4 - 5, 1, -31, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 9, 17, 0.5);
            door_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else {
            model = transform(-3- 4, 1, -31, rotateAngle_X, 90, rotateAngle_Z, 9, 17, 0.5);
            door_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        }

        //basin base
        model = transform(-23.8, 0, 1, rotateAngle_X, rotateAngle_Y + 90, rotateAngle_Z, 26, 6, 5);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
    

        //toilet point light 
        model = transform(-4, 21, 3.75, rotateAngle_X, rotateAngle_Y , rotateAngle_Z, 2.5, -0.1, 2.5);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);

        model = transform(-3.75,20.9, 4, rotateAngle_X, rotateAngle_Y , rotateAngle_Z, 2, -0.4, 2);
        white_cube.drawCubeWithMaterialisticProperty(lightingShader, model);

        //three basins


        //mirror
        model = transform(-23.9, 9, 1, rotateAngle_X, rotateAngle_Y + 90, rotateAngle_Z, 24, 7, 0.1);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);

        model = transform(-23.8, 9.5, 1.1, rotateAngle_X, rotateAngle_Y + 90, rotateAngle_Z, 23, 6, 0.1);
        wall_cube.drawCubeWithTexture(lightingShaderWithTexture, model);

        

        //exit
        model = transform(60.1, 0, 10, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -5.1, 18, 1);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(60.1, 0, 30, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -5.1, 18, -1);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);

        model = transform(56, 18, 11, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 4.1, -0.5, 18);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(56, 0, 11, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 4.0, 0.5, 18);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);


        //point light 9
        model = transform(74.75, 23, 18.75, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.5, -0.1, 2.5);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(75, 23.1, 19, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2, -0.4, 2);
        white_cube.drawCubeWithMaterialisticProperty(lightingShader, model);


        

        //extenstion photo zone
        model = transform(60.1, 18, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -1.1, 5, 39);
        wall1.drawCubeWithMaterialisticProperty(lightingShader, model);
        //roof
        model = transform(59, 21, 115, rotateAngle_X, rotateAngle_Y-90, rotateAngle_Z, 1, 3, 39);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);

        model = transform(59, 24, 115, rotateAngle_X, rotateAngle_Y-90, rotateAngle_Z, 10, 1, 39);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);

        //point light 7
        model = transform(63.75, 26, 42.75, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.5, -0.1, 2.5);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);

        model = transform(64, 26.1, 43, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2, -0.4, 2);
        white_cube.drawCubeWithMaterialisticProperty(lightingShader, model);
        
        //point light 8
        model = transform(63.75, 26, 63.75, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.5, -0.1, 2.5);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        
        model = transform(64, 26.1, 64, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2, -0.4, 2);
        white_cube.drawCubeWithMaterialisticProperty(lightingShader, model);

        //stage


        //inner chair tables
        x = 7, z = 38;
        for (int i = 0; i < 3; i++) {

            //chair
            translateMatrix = glm::translate(identityMatrix, glm::vec3(x, 0, z));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 1, 1.5));
            Chair(floorExtension, lightingShader, translateMatrix * scaleMatrix);

            translateMatrix = glm::translate(identityMatrix, glm::vec3(x + 5.5, 0, z));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 1, 1.5));
            Chair(floorExtension, lightingShader, translateMatrix * scaleMatrix);

            //table
            translateMatrix = glm::translate(identityMatrix, glm::vec3(x, 0, z + 2.5));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 1, 1.5));
            Table(chair_cube, lightingShader, translateMatrix * scaleMatrix);

            //bottle 1
            //Curve bottles(bottle, bottleTex, bottleTex, 1.0f);
            model = transform(x + 4.6, 4, z + 5.4, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.5, 1, 0.5);
            bottles.draw(lightingShaderWithTexture, model, glm::vec3(1.0, 0.0, 1.0));

            model = transform(x + 5.2, 14, z + 5.4, 180, 0, 0, 2, 5, 4);
            bowl.draw(lightingShaderWithTexture, model, glm::vec3(1.0, 0.0, 1.0));
            


            //chair
            translateMatrix = glm::translate(identityMatrix, glm::vec3(x, 0, z + 9.5));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 1, -1.5));
            Chair(floorExtension, lightingShader, translateMatrix * scaleMatrix);

            translateMatrix = glm::translate(identityMatrix, glm::vec3(x + 5.5, 0, z + 9.5));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 1, -1.5));
            Chair(floorExtension, lightingShader, translateMatrix * scaleMatrix);

            z += 17;
        }

        x = 20, z = 38;
        for (int i = 0; i < 3; i++) {

            //chair
            translateMatrix = glm::translate(identityMatrix, glm::vec3(x, 0, z));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 1, 1.5));
            Chair(floorExtension, lightingShader, translateMatrix * scaleMatrix);

            translateMatrix = glm::translate(identityMatrix, glm::vec3(x + 5.5, 0, z));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 1, 1.5));
            Chair(floorExtension, lightingShader, translateMatrix * scaleMatrix);

            //table
            translateMatrix = glm::translate(identityMatrix, glm::vec3(x, 0, z + 2.5));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 1, 1.5));
            Table(chair_cube, lightingShader, translateMatrix * scaleMatrix);

            //bottle 1
            model = transform(x + 4.6, 4, z + 5.4, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.5, 1, 0.5);
            bottles.draw(lightingShaderWithTexture, model, glm::vec3(1.0, 0.0, 1.0));
            
            model = transform(x + 7.2, 14, z + 5.4, 180, 0, 0, 2, 5, 4);
            bowl.draw(lightingShaderWithTexture, model, glm::vec3(1.0, 0.0, 1.0));
            lightingShader.setMat4("model", model);
            lightingShader.use();
            lightingShader.setVec3("material.ambient", glm::vec3(1, 1, 1));
            lightingShader.setVec3("material.diffuse", glm::vec3(1, 1, 1));
            lightingShader.setVec3("material.specular", glm::vec3(1, 1, 1));
            lightingShader.setFloat("material.shininess", 32.0f);
            glBindVertexArray(bezierBottleVAO);
            glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
            glBindVertexArray(0);

            //chair
            translateMatrix = glm::translate(identityMatrix, glm::vec3(x, 0, z + 9.5));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 1, -1.5));
            Chair(floorExtension, lightingShader, translateMatrix * scaleMatrix);

            translateMatrix = glm::translate(identityMatrix, glm::vec3(x + 5.5, 0, z + 9.5));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 1, -1.5));
            Chair(floorExtension, lightingShader, translateMatrix * scaleMatrix);

            z += 17;
        }
        //backside chair table
        x = 20, z = -10;
        //chair
        translateMatrix = glm::translate(identityMatrix, glm::vec3(x, 0, z));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 1, 1.5));
        Chair(floorExtension, lightingShader, translateMatrix * scaleMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(x + 5.5, 0, z));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 1, 1.5));
        Chair(floorExtension, lightingShader, translateMatrix * scaleMatrix);

        //table
        translateMatrix = glm::translate(identityMatrix, glm::vec3(x, 0, z + 2.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 1, 1.5));
        Table(chair_cube, lightingShader, translateMatrix * scaleMatrix);

        model = transform(x + 4.6, 4, z + 5.4, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.5, 1, 0.5);
        glass.draw(lightingShaderWithTexture, model, glm::vec3(1.0, 0.0, 1.0));

        model = transform(x + 7.2, 14, z + 5.4 , 180, 0, 0, 2, 5, 4);
        
        bowl.draw(lightingShaderWithTexture, model, glm::vec3(1.0, 0.0, 1.0));

        //chair
        translateMatrix = glm::translate(identityMatrix, glm::vec3(x, 0, z + 9.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 1, -1.5));
        Chair(floorExtension, lightingShader, translateMatrix * scaleMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(x + 5.5, 0, z + 9.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 1, -1.5));
        Chair(floorExtension, lightingShader, translateMatrix * scaleMatrix);



       

        //coke fridge
        model = transform(55, 0,-27, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 4, 11, 5);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(55, 2, -27, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -0.1, 8.65, 4.5);
        coke_cube.drawCubeWithTexture(lightingShaderWithTexture, model);

       
        
        //barbique
        //front lower
        model = transform(36, 0, -45, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 3, 7, 25);
        court5_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        
        //front upper
        model = transform(34, 12, -45, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 6, 25);
        court5_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        //kabab
        model = transform(60, 0, -19, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -24, 7, -2);
        court5_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        
        //right upper kabab
        model = transform(60, 12, -19, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -26, 6, -2);
        court5_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
    

        //-----------kabab
        // 
        //right extension design extra
        //right wall 1,35,35
        model = transform(85, 0, -44, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -1, 5, 154);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        //right side upper 
        model = transform(85, 5, -45, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2, 5, 156);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        //right side lower 
        model = transform(85, -6, -45, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2, 8, 156);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);

        //front cylinder sphere design
        
        int xxx = 65;
        for (int i = 0; i < 3; i++) {
            //cylinder
            model = transform(xxx, 9, 110.5, 00.0f, 0.0f, 0.0f, 0.25, 0.25, 0.25);
            cylinder1.drawCylinder(lightingShader, model);

            model = transform(xxx, 13, 110.5, 0.0f, 0.0f, 0.0f, 0.75, 0.025, 0.75);
            cylinder1.drawCylinder(lightingShader, model);

            //sphere
            model = transform(xxx, 14, 110.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 1, 1);
            sphere.drawSphere(lightingShader, model);
            xxx += 7;
        }
        
        //front side upper
        model = transform(60, 5, 110, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 27, 5, 1);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        //front side lower
        model = transform(60, -6, 110, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 27, 8, 1);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(60, 0, 109, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 25, 8, 1);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        //back side upper
        model = transform(60, 5, -45, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 27, 5, 1);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        //back side lower
        model = transform(60, -6, -45, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 27, 8, 1);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(60, 0, -44, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 25, 8, 1);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        
        //front floor design extra
        // 
        //left
        model = transform(-25, 5, 140, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 55, -2, 2);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(-25, 0, 140, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 55, -6, 2);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);


        

        model = transform(59, 21.2, 100, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -50, 1.5, 15);
        wood2_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        model = transform(-25, 21.2, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 84, 1.5, 100);
        wood2_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        model = transform(-25, 21.2, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 84, 0.2, -45);
        wood2_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        //model = transform(-25, 21.2, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -15, 1.5, 25);
        //wood2_cube.drawCubeWithTexture(lightingShaderWithTexture, model);

        model = transform(59, 22.7, 100, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -50, 0.3, 15);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(-25, 22.7, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 84, 0.3, 100);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(-25, 22.7, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 84, 0.2, -45);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
       // model = transform(-25, 22.7, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -15, 0.3, 25);
        //floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);

        
        //right
        model = transform(60, 0, 140, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -5, -6, 2);
        //floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(60, 0, 142, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2, -6, -32);
       // floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        //left floor design extra
        model = transform(-25, 5, 110, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -2, -2, 32);
        //floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(-25, 0, 110, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -2, -6, 32);
        //floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        
        
        

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    //cout << translate_X << " ," << translate_Y << " ," << translate_Z << endl;
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
        camera.ProcessKeyboard(UP, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        camera.ProcessKeyboard(DOWN, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
        camera.ProcessKeyboard(P_UP, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
        camera.ProcessKeyboard(P_DOWN, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        camera.ProcessKeyboard(Y_LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        camera.ProcessKeyboard(Y_RIGHT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
        camera.ProcessKeyboard(R_LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        camera.ProcessKeyboard(R_RIGHT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS) {
        if (droneOn)
            ry += 10;
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        if (droneOn)
            dz -= 1.0;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        if (droneOn)
            dz += 1.0;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        if (droneOn)
            dx -= 1.0;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        if (droneOn)
            dx += 1.0;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_BRACKET) == GLFW_PRESS) {
        if (droneOn)
            dy += 1.0;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT_BRACKET) == GLFW_PRESS) {
        if (droneOn)
            dy -= 1.0;
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_1 && action == GLFW_PRESS)
    {
        if (dirLightOn)
        {
            dirlight.turnOff();
            dirLightOn = !dirLightOn;
        }
        else
        {
            dirlight.turnOn();
            dirLightOn = !dirLightOn;
        }
    }
    if (key == GLFW_KEY_2 && action == GLFW_PRESS)
    {
        if (pointLightOn1)
        {
            pointlight1.turnOff();
            pointlight2.turnOff();
            pointlight3.turnOff();
            pointlight4.turnOff();
            toiletpointlight.turnOff();
           
        }
        else
        {
            pointlight1.turnOn();
            pointlight2.turnOn();
            pointlight3.turnOn();
            pointlight4.turnOn();
            toiletpointlight.turnOn();
            
        }
        pointLightOn1 = !pointLightOn1;
    }
    if (key == GLFW_KEY_3 && action == GLFW_PRESS)
    {
        if (pointLightOn2)
        {
            familypointlight.turnOff();
            pointlight5.turnOff();
            pointlight6.turnOff();
            pointlight7.turnOff();
            pointlight8.turnOff();
            pointlight9.turnOff();
        }
        else
        {
            familypointlight.turnOn();
            pointlight5.turnOn();
            pointlight6.turnOn();
            pointlight7.turnOn();
            pointlight8.turnOn();
            pointlight9.turnOn();
        }
        pointLightOn2 = !pointLightOn2;
    }
    if (key == GLFW_KEY_4 && action == GLFW_PRESS)
    {
        if (spotLightOn)
        {
            spotlight1.turnOff();
            spotlight2.turnOff();
        }
        else
        {
            spotlight1.turnOn();
            spotlight2.turnOn();
        }
        spotLightOn = !spotLightOn;
    }
    if (key == GLFW_KEY_5 && action == GLFW_PRESS)
    {
        if (ambientToggle)
        {
            if (pointLightOn1) {
                pointlight1.turnAmbientOff();
                pointlight2.turnAmbientOff();
                pointlight3.turnAmbientOff();
                pointlight4.turnAmbientOff();
            }

            if (pointLightOn2) {
                pointlight5.turnAmbientOff();
                pointlight6.turnAmbientOff();
                pointlight7.turnAmbientOff();
                pointlight8.turnAmbientOff();
                pointlight9.turnAmbientOff();
            }
            if (spotLightOn) {
                spotlight1.turnAmbientOff();
                spotlight2.turnAmbientOff();
            }
            if (dirLightOn) {
                dirlight.turnAmbientOff();

            }
            ambientToggle = !ambientToggle;
        }
        else
        {
            if (pointLightOn1) {
                pointlight1.turnAmbientOn();
                pointlight2.turnAmbientOn();
                pointlight3.turnAmbientOn();
                pointlight4.turnAmbientOn();

            }
            if (pointLightOn2) {
                pointlight5.turnAmbientOn();
                pointlight6.turnAmbientOn();
                pointlight7.turnAmbientOn();
                pointlight8.turnAmbientOn();
                pointlight9.turnAmbientOn();

            }
            if (spotLightOn) {
                spotlight1.turnAmbientOn();
                spotlight2.turnAmbientOn();
            }
            if (dirLightOn)
                dirlight.turnAmbientOn();
            ambientToggle = !ambientToggle;
        }
    }
    if (key == GLFW_KEY_6 && action == GLFW_PRESS)
    {
        if (diffuseToggle)
        {
            if (pointLightOn1) {
                pointlight1.turnDiffuseOff();
                pointlight2.turnDiffuseOff();
                pointlight3.turnDiffuseOff();
                pointlight4.turnDiffuseOff();

            }

            if (pointLightOn2) {
                pointlight5.turnDiffuseOff();
                pointlight6.turnDiffuseOff();
                pointlight7.turnDiffuseOff();
                pointlight8.turnDiffuseOff();
                pointlight9.turnDiffuseOff();

            }

            if (dirLightOn)
                dirlight.turnDiffuseOff();
            if (spotLightOn) {
                spotlight1.turnDiffuseOff();
                spotlight2.turnDiffuseOff();
            }
            diffuseToggle = !diffuseToggle;

        }
        else
        {
            if (pointLightOn1) {
                pointlight1.turnDiffuseOn();
                pointlight2.turnDiffuseOn();
                pointlight3.turnDiffuseOn();
                pointlight4.turnDiffuseOn();

            }

            if (pointLightOn2) {
                pointlight5.turnDiffuseOn();
                pointlight6.turnDiffuseOn();
                pointlight7.turnDiffuseOn();
                pointlight8.turnDiffuseOn();
                pointlight9.turnDiffuseOn();

            }

            if (dirLightOn)
                dirlight.turnDiffuseOn();
            if (spotLightOn) {
                spotlight1.turnDiffuseOn();
                spotlight2.turnDiffuseOn();

            }
            diffuseToggle = !diffuseToggle;

        }
    }
    if (key == GLFW_KEY_7 && action == GLFW_PRESS)
    {
        if (specularToggle)
        {
            if (pointLightOn1) {
                pointlight1.turnSpecularOff();
                pointlight2.turnSpecularOff();
                pointlight3.turnSpecularOff();
                pointlight4.turnSpecularOff();
            }

            if (pointLightOn2) {
                pointlight5.turnSpecularOff();
                pointlight6.turnSpecularOff();
                pointlight7.turnSpecularOff();
                pointlight8.turnSpecularOff();
                pointlight9.turnSpecularOff();
            }

            if (dirLightOn)
                dirlight.turnSpecularOff();
            if (spotLightOn) {
                spotlight1.turnSpecularOff();
                spotlight2.turnSpecularOff();

            }
            specularToggle = !specularToggle;

        }
        else
        {
            if (pointLightOn1) {
                pointlight1.turnSpecularOn();
                pointlight2.turnSpecularOn();
                pointlight3.turnSpecularOn();
                pointlight4.turnSpecularOn();
            }
            if (pointLightOn2) {
                pointlight5.turnSpecularOn();
                pointlight6.turnSpecularOn();
                pointlight7.turnSpecularOn();
                pointlight8.turnSpecularOn();
                pointlight9.turnSpecularOn();

            }
            if (dirLightOn)
                dirlight.turnSpecularOn();
            if (spotLightOn) {
                spotlight1.turnSpecularOn();
                spotlight2.turnSpecularOn();
            }
            specularToggle = !specularToggle;
        }
    }
    if (key == GLFW_KEY_M && action == GLFW_PRESS)
    {
        doorOpen = !doorOpen;
    }
    if (key == GLFW_KEY_N && action == GLFW_PRESS)
    {
        familydoorOpen = !familydoorOpen;
    }
    if (key == GLFW_KEY_K && action == GLFW_PRESS)
    {
        kebabdoorOpen = !kebabdoorOpen;
    }
    if (key == GLFW_KEY_T && action == GLFW_PRESS)
    {
        //washroomdoorOpen = !washroomdoorOpen;
    }
    if (key == GLFW_KEY_O && action == GLFW_PRESS)
    {
        toiletdoorOpen1 = !toiletdoorOpen1;
    }
    if (key == GLFW_KEY_P && action == GLFW_PRESS)
    {
        toiletdoorOpen2 = !toiletdoorOpen2;
    }
    if (key == GLFW_KEY_F && action == GLFW_PRESS)
    {
        fanOn = !fanOn;
    }
    if (key == GLFW_KEY_L && action == GLFW_PRESS)
    {
        droneOn = !droneOn;
    }

    if (key == GLFW_KEY_0 && action == GLFW_PRESS)
    {
        //tvOn = !tvOn;
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
unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrappingModeS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrappingModeT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilteringModeMin);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilteringModeMax);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

//Building Functions

void ChairTableCombo(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 translateMatrix, scaleMatrix, model;

    //table
    //base
    model = transform(0, 4.2, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 5, 0.2, 4);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //left up leg
    model = transform(0.5, 0, 0, 45, rotateAngle_Y, rotateAngle_Z, 0.2, 5.66, -0.4);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);
    //left down leg
    model = transform(0.5, 0, 4, -45, rotateAngle_Y, rotateAngle_Z, 0.2, 5.66, 0.4);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //Right up leg
    model = transform(4.5, 0, 0, 45, rotateAngle_Y, rotateAngle_Z, -0.2, 5.66, -0.4);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);
    //Right down leg
    model = transform(4.5, 0, 4, -45, rotateAngle_Y, rotateAngle_Z, -0.2, 5.66, 0.4);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //chair 1
    //base
    model = transform(0, 2.5, 4.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 5, 0.2, 2);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //left up leg
    model = transform(0.5, 0, 5, 30, rotateAngle_Y, rotateAngle_Z, 0.2, 2.83, -0.4);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);
    //left down leg
    model = transform(0.5, 0, 6, -30, rotateAngle_Y, rotateAngle_Z, 0.2, 2.83, 0.4);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //Right up leg
    model = transform(4.5, 0, 5, 30, rotateAngle_Y, rotateAngle_Z, -0.2, 2.83, -0.4);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);
    //Right down leg
    model = transform(4.5, 0, 6, -30, rotateAngle_Y, rotateAngle_Z, -0.2, 2.83, 0.4);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);


    //chair 2
    //base
    model = transform(0, 2.5, -2.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 5, 0.2, 2);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //left up leg
    model = transform(0.5, 0, -2, 30, rotateAngle_Y, rotateAngle_Z, 0.2, 2.83, -0.4);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);
    //left down leg
    model = transform(0.5, 0, -1, -30, rotateAngle_Y, rotateAngle_Z, 0.2, 2.83, 0.4);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //Right up leg
    model = transform(4.5, 0, -2, 30, rotateAngle_Y, rotateAngle_Z, -0.2, 2.83, -0.4);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);
    //Right down leg
    model = transform(4.5, 0, -1, -30, rotateAngle_Y, rotateAngle_Z, -0.2, 2.83, 0.4);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);
}

void Chair(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 translateMatrix, scaleMatrix, model;

    //pichone left leg
    model = transform(0, 0, 0, 0, rotateAngle_Y, rotateAngle_Z, 0.2, 3, 0.2);
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);

    //pichone right leg
    model = transform(2.5, 0, 0, 0, rotateAngle_Y, rotateAngle_Z, -0.2, 3, 0.2);
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);

    //samner left leg
    model = transform(0, 0, 2, 0, rotateAngle_Y, rotateAngle_Z, 0.2, 3, -0.2);
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);

    //samner right leg
    model = transform(2.5, 0, 2, 0, rotateAngle_Y, rotateAngle_Z, -0.2, 3, -0.2);
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);
    //base
    model = transform(0, 3, 0, 0, rotateAngle_Y, rotateAngle_Z, 2.5, 0.2, 2);
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);

    //pichoner base
    model = transform(0, 3, 0, -10, 0, rotateAngle_Z, 2.5, 3, 0.2);
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);

}
void Table(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 translateMatrix, scaleMatrix, model;


    //upper base
    model = transform(0, 4, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 6, 0.2, 4);
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);
    //base
    model = transform(2.8, 0, 1.8, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.4, 4, 0.4);
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);
    //lower base
    model = transform(2, 0, 1, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2, 0.2, 2);
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);

}
void Sofa(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{
    glm::mat4 translateMatrix, scaleMatrix, model;

    //base
    model = transform(0, 0, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 6, 1.5, 2.3);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);
    //left side
    model = transform(0, 0, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -0.5, 2.5, 2.3);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);
    //right side
    model = transform(6, 0, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.5, 2.5, 2.3);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);
    //pichonerbase
    model = transform(-0.5, 0, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 7, 3.2, -1);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

}
void OvenCooker(Cube& cube, Cube& chula, Cube& oven, Cube& basin, Shader& lightingShader, Shader& lightingShaderWithTexture, glm::mat4 alTogether)
{
    glm::mat4 translateMatrix, scaleMatrix, model;

    //base
    model = transform(0, 0, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 12, 7, 6);
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);
    //cube.drawCubeWithTexture(lightingShaderWithTexture, alTogether * model);
    //chula
    model = transform(0, 7, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 6, 0.3, 4);
    chula.drawCubeWithTexture(lightingShaderWithTexture, alTogether * model);
    //oven
    model = transform(0.5, 3, 6, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 5.25, 3.5, 0.2);
    oven.drawCubeWithTexture(lightingShaderWithTexture, alTogether * model);
    //oven
    model = transform(6.25, 3, 6, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 5.25, 3.5, 0.2);
    oven.drawCubeWithTexture(lightingShaderWithTexture, alTogether * model);
    //basin
    model = transform(7, 7, 0.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 4, 0.1, 3);
    //basin.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);
    basin.drawCubeWithTexture(lightingShaderWithTexture, alTogether * model);
    //tap
    model = transform(9, 7, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.2, 1.5, 0.2);
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);
    model = transform(9, 8.5, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.2, -0.2, 1.5);
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);
    model = transform(9, 8.5, 1.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.2, -0.4, -0.2);
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);
}
long long nCr(int n, int r)
{
    if (r > n / 2)
        r = n - r; // because C(n, r) == C(n, n - r)
    long long ans = 1;
    int i;

    for (i = 1; i <= r; i++)
    {
        ans *= n - r + i;
        ans /= i;
    }

    return ans;
}
void getCurrentTime(int& hours, int& minutes, int& seconds) {
    time_t currentTime = time(nullptr); // Get current UNIX timestamp
    struct tm* timeinfo;
    timeinfo = localtime(&currentTime);

    seconds = timeinfo->tm_sec;
    minutes = timeinfo->tm_min;
    hours = timeinfo->tm_hour;
}

void drawTreeWithFractiles(Cube& tree, Cube& root, Shader& lightingShader, glm::mat4 alTogether, float L, float H, float W, int N)
{
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 next = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);


    model = identityMatrix;


    if (N == 0) {
        float length = 0.5;
        float height = 2.0;
        float width = 0.5;

        float mvx = length * 0.05;
        float mvy = height - height * 0.1;
        float mvz = width * 0.05;


        translate = glm::translate(identityMatrix, glm::vec3(mvx, mvy, mvz));
        next = translate * alTogether;


        scale = glm::scale(identityMatrix, glm::vec3(length, height, width));
        model = alTogether * scale;
        root.drawCubeWithTexture(lightingShader, model);

        drawTreeWithFractiles(tree, root, lightingShader, next, length, height, width, N + 1);
    }

    else if (N > 0 && N < 5) {
        float length = L * 0.6;
        float height = H * 0.6;
        float width = W * 0.6;

        scale = glm::scale(identityMatrix, glm::vec3(length, height, width));
        rotate = glm::rotate(identityMatrix, glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model = alTogether * rotate * scale;
        //cube.drawCube(lightingShader, model, 0.23, 0.08, 0.08);
        tree.drawCubeWithTexture(lightingShader, model);

        scale = glm::scale(identityMatrix, glm::vec3(length, height, width));
        rotate = glm::rotate(identityMatrix, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = alTogether * rotate * scale;
        //cube.drawCube(lightingShader, model, 0.23, 0.08, 0.08);
        tree.drawCubeWithTexture(lightingShader, model);

        scale = glm::scale(identityMatrix, glm::vec3(length, height, width));
        rotate = glm::rotate(identityMatrix, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model = alTogether * rotate * scale;
        //cube.drawCube(lightingShader, model, 0.23, 0.08, 0.08);
        tree.drawCubeWithTexture(lightingShader, model);

        scale = glm::scale(identityMatrix, glm::vec3(length, height, width));
        rotate = glm::rotate(identityMatrix, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = alTogether * rotate * scale;
        //cube.drawCube(lightingShader, model, 0.23, 0.08, 0.08);
        tree.drawCubeWithTexture(lightingShader, model);

        scale = glm::scale(identityMatrix, glm::vec3(length, height * 1.5, width));
        model = alTogether * scale;
        //cube.drawCube(lightingShader, model, 0.23, 0.08, 0.08);
        tree.drawCubeWithTexture(lightingShader, model);


        float mvx = length * 0.3 + height * 0.7071;
        float mvy = height * 0.7071;
        float mvz = width * 0.3;
        translate = glm::translate(identityMatrix, glm::vec3(mvx, mvy, mvz));
        next = translate * alTogether;
        drawTreeWithFractiles(tree, root, lightingShader, next, length, height, width, N + 1);


        mvx = length * 0.3;
        mvy = height * 0.7071;
        mvz = width * 0.3 - height * 0.7071;
        translate = glm::translate(identityMatrix, glm::vec3(mvx, mvy, mvz));
        next = translate * alTogether;
        drawTreeWithFractiles(tree, root, lightingShader, next, length, height, width, N + 1);


        mvx = length * 0.3 - height * 0.7071;
        mvy = height * 0.7071;
        mvz = width * 0.3;
        translate = glm::translate(identityMatrix, glm::vec3(mvx, mvy, mvz));
        next = translate * alTogether;
        drawTreeWithFractiles(tree, root, lightingShader, next, length, height, width, N + 1);


        mvx = length * 0.3;
        mvy = height * 0.7071;
        mvz = width * 0.3 + height * 0.7071;
        translate = glm::translate(identityMatrix, glm::vec3(mvx, mvy, mvz));
        next = translate * alTogether;
        drawTreeWithFractiles(tree, root, lightingShader, next, length, height, width, N + 1);

        mvx = length * 0.3;
        mvy = height;
        mvz = width * 0.3;
        translate = glm::translate(identityMatrix, glm::vec3(mvx, mvy * 1.5, mvz));
        next = translate * alTogether;
        drawTreeWithFractiles(tree, root, lightingShader, next, length, height, width, N + 1);
    }

    else {
        float length = L * 0.6;
        float height = H * 0.6;
        float width = W * 0.6;

        scale = glm::scale(identityMatrix, glm::vec3(length, height, width));
        rotate = glm::rotate(identityMatrix, glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model = alTogether * rotate * scale;
        //cube.drawCube(lightingShader, model, 0.01, 0.23, 0.03);
        tree.drawCubeWithTexture(lightingShader, model);

        scale = glm::scale(identityMatrix, glm::vec3(length, height, width));
        rotate = glm::rotate(identityMatrix, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = alTogether * rotate * scale;
        //cube.drawCube(lightingShader, model, 0.01, 0.23, 0.03);
        tree.drawCubeWithTexture(lightingShader, model);
        scale = glm::scale(identityMatrix, glm::vec3(length, height, width));
        rotate = glm::rotate(identityMatrix, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model = alTogether * rotate * scale;
        //cube.drawCube(lightingShader, model, 0.01, 0.23, 0.03);
        tree.drawCube(lightingShader, model);
        scale = glm::scale(identityMatrix, glm::vec3(length, height, width));
        rotate = glm::rotate(identityMatrix, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = alTogether * rotate * scale;
        //cube.drawCube(lightingShader, model, 0.01, 0.23, 0.03);
        tree.drawCubeWithTexture(lightingShader, model);
        scale = glm::scale(identityMatrix, glm::vec3(length, height, width));
        model = alTogether * scale;
        //cube.drawCube(lightingShader, model, 0.01, 0.23, 0.03);
        tree.drawCubeWithTexture(lightingShader, model);
    }

}

void drawTreeWithFractilesSphere(Sphere2 *tree, Cube& root, Shader& lightingShader, glm::mat4 alTogether, float L, float H, float W, int N)
{
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 next = glm::mat4(1.0f);
    glm::mat4 rotate = glm::mat4(1.0f);


    model = identityMatrix;


    if (N == 0) {
        float length = 0.5;
        float height = 2.0;
        float width = 0.5;

        float mvx = length * 0.05;
        float mvy = height - height * 0.1;
        float mvz = width * 0.05;


        translate = glm::translate(identityMatrix, glm::vec3(mvx, mvy, mvz));
        next = translate * alTogether;


        scale = glm::scale(identityMatrix, glm::vec3(length, height, width));
        model = alTogether * scale;
        root.drawCubeWithTexture(lightingShader, model);

        drawTreeWithFractilesSphere(tree, root, lightingShader, next, length, height, width, N + 1);
    }

    else if (N > 0 && N < 5) {
        float length = L * 0.6;
        float height = H * 0.6;
        float width = W * 0.6;

        scale = glm::scale(identityMatrix, glm::vec3(length, height, width));
        rotate = glm::rotate(identityMatrix, glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model = alTogether * rotate * scale;
        //cube.drawCube(lightingShader, model, 0.23, 0.08, 0.08);
        
        tree->drawSphereWithTexture(lightingShader, model);

        scale = glm::scale(identityMatrix, glm::vec3(length, height, width));
        rotate = glm::rotate(identityMatrix, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = alTogether * rotate * scale;
        //cube.drawCube(lightingShader, model, 0.23, 0.08, 0.08);
        tree->drawSphereWithTexture(lightingShader, model);

        scale = glm::scale(identityMatrix, glm::vec3(length, height, width));
        rotate = glm::rotate(identityMatrix, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model = alTogether * rotate * scale;
        //cube.drawCube(lightingShader, model, 0.23, 0.08, 0.08);
        tree->drawSphereWithTexture(lightingShader, model);

        scale = glm::scale(identityMatrix, glm::vec3(length, height, width));
        rotate = glm::rotate(identityMatrix, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = alTogether * rotate * scale;
        //cube.drawCube(lightingShader, model, 0.23, 0.08, 0.08);
        tree->drawSphereWithTexture(lightingShader, model);

        scale = glm::scale(identityMatrix, glm::vec3(length, height * 1.5, width));
        model = alTogether * scale;
        //cube.drawCube(lightingShader, model, 0.23, 0.08, 0.08);
        tree->drawSphereWithTexture(lightingShader, model);


        float mvx = length * 0.3 + height * 0.7071;
        float mvy = height * 0.7071;
        float mvz = width * 0.3;
        translate = glm::translate(identityMatrix, glm::vec3(mvx, mvy, mvz));
        next = translate * alTogether;
        drawTreeWithFractilesSphere(tree, root, lightingShader, next, length, height, width, N + 1);


        mvx = length * 0.3;
        mvy = height * 0.7071;
        mvz = width * 0.3 - height * 0.7071;
        translate = glm::translate(identityMatrix, glm::vec3(mvx, mvy, mvz));
        next = translate * alTogether;
        drawTreeWithFractilesSphere(tree, root, lightingShader, next, length, height, width, N + 1);


        mvx = length * 0.3 - height * 0.7071;
        mvy = height * 0.7071;
        mvz = width * 0.3;
        translate = glm::translate(identityMatrix, glm::vec3(mvx, mvy, mvz));
        next = translate * alTogether;
        drawTreeWithFractilesSphere(tree, root, lightingShader, next, length, height, width, N + 1);


        mvx = length * 0.3;
        mvy = height * 0.7071;
        mvz = width * 0.3 + height * 0.7071;
        translate = glm::translate(identityMatrix, glm::vec3(mvx, mvy, mvz));
        next = translate * alTogether;
        drawTreeWithFractilesSphere(tree, root, lightingShader, next, length, height, width, N + 1);

        mvx = length * 0.3;
        mvy = height;
        mvz = width * 0.3;
        translate = glm::translate(identityMatrix, glm::vec3(mvx, mvy * 1.5, mvz));
        next = translate * alTogether;
        drawTreeWithFractilesSphere(tree, root, lightingShader, next, length, height, width, N + 1);
    }

    else {
        float length = L * 0.6;
        float height = H * 0.6;
        float width = W * 0.6;

        scale = glm::scale(identityMatrix, glm::vec3(length, height, width));
        rotate = glm::rotate(identityMatrix, glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model = alTogether * rotate * scale;
        //cube.drawCube(lightingShader, model, 0.01, 0.23, 0.03);
        tree->drawSphereWithTexture(lightingShader, model);

        scale = glm::scale(identityMatrix, glm::vec3(length, height, width));
        rotate = glm::rotate(identityMatrix, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = alTogether * rotate * scale;
        //cube.drawCube(lightingShader, model, 0.01, 0.23, 0.03);
        tree->drawSphereWithTexture(lightingShader, model);
        scale = glm::scale(identityMatrix, glm::vec3(length, height, width));
        rotate = glm::rotate(identityMatrix, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        model = alTogether * rotate * scale;
        //cube.drawCube(lightingShader, model, 0.01, 0.23, 0.03);
        tree->drawSphereWithTexture(lightingShader, model);
        scale = glm::scale(identityMatrix, glm::vec3(length, height, width));
        rotate = glm::rotate(identityMatrix, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        model = alTogether * rotate * scale;
        //cube.drawCube(lightingShader, model, 0.01, 0.23, 0.03);
        tree->drawSphereWithTexture(lightingShader, model);
        scale = glm::scale(identityMatrix, glm::vec3(length, height, width));
        model = alTogether * scale;
        //cube.drawCube(lightingShader, model, 0.01, 0.23, 0.03);
        tree->drawSphereWithTexture(lightingShader, model);
    }

}

void ShowcaseRack(Cylinder& cylinder1, Cube& chips, Cube& chips2, Cube& chips3, Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{
    //pichoner base
    glm::mat4 translateMatrix, scaleMatrix, model;
    model = transform(0, 0, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.2, 6, 12);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    model = transform(0, 0, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2, 0.2, 12);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    //containers on first floor
    model = transform(0.1, 0.2, 1, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 1.7, 1);
    chips.drawCubeWithTexture(lightingShader, alTogether * model);
    model = transform(0.1, 0.2, 2.1, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 1.7, 1);
    chips.drawCubeWithTexture(lightingShader, alTogether * model);
    model = transform(0.1, 0.2, 3.2, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 1.7, 1);
    chips.drawCubeWithTexture(lightingShader, alTogether * model);
    model = transform(0.1, 0.2, 4.3, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 1.7, 1);
    chips.drawCubeWithTexture(lightingShader, alTogether * model);
    model = transform(0.1, 0.2, 5.4, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 1.7, 1);
    chips.drawCubeWithTexture(lightingShader, alTogether * model);
    model = transform(0.1, 0.2, 8.1, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 1.7, 1);
    chips3.drawCubeWithTexture(lightingShader, alTogether * model);
    model = transform(0.1, 0.2, 9.2, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 1.7, 1);
    chips2.drawCubeWithTexture(lightingShader, alTogether * model);
    model = transform(0.1, 0.2, 10.3, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 1.7, 1);
    chips3.drawCubeWithTexture(lightingShader, alTogether * model);


    model = transform(0, 1.9, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2, 0.2, 12);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);
    //containers on 2nd floor
    model = transform(0.1, 2.1, 1, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 1.7, 1);
    chips3.drawCubeWithTexture(lightingShader, alTogether * model);

    model = transform(0.1, 2.1, 3, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 1.7, 1);
    chips2.drawCubeWithTexture(lightingShader, alTogether * model);
    model = transform(0.1, 2.1, 4.1, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 1.7, 1);
    chips2.drawCubeWithTexture(lightingShader, alTogether * model);
    model = transform(0.1, 2.1, 5.2, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 1.7, 1);
    chips2.drawCubeWithTexture(lightingShader, alTogether * model);
    model = transform(0.1, 2.1, 6.3, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 1.7, 1);
    chips2.drawCubeWithTexture(lightingShader, alTogether * model);


    model = transform(0, 3.9, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2, 0.2, 12);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);
    //containers on 3rd floor
    model = transform(0.1, 4.1, 1, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 1.7, 1);
    chips3.drawCubeWithTexture(lightingShader, alTogether * model);
    model = transform(0.1, 4.1, 2.1, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 1.7, 1);
    chips3.drawCubeWithTexture(lightingShader, alTogether * model);
    model = transform(0.1, 4.1, 3.2, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 1.7, 1);
    chips3.drawCubeWithTexture(lightingShader, alTogether * model);
    model = transform(0.1, 4.1, 4.3, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 1.7, 1);
    chips.drawCubeWithTexture(lightingShader, alTogether * model);
    model = transform(0.1, 4.1, 5.4, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 1.7, 1);
    chips2.drawCubeWithTexture(lightingShader, alTogether * model);
    model = transform(0.1, 4.1, 6.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 1.7, 1);
    chips2.drawCubeWithTexture(lightingShader, alTogether * model);


    model = transform(0, 5.9, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2, 0.2, 12);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

    model = transform(0, 0, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2, 6.1, 0.2);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);
    model = transform(0, 0, 12, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2, 6.1, 0.2);
    cube.drawCubeWithTexture(lightingShader, alTogether * model);

}