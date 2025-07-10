
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
#include "sphere2.h"

#include <iostream>
#include <ctime>

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
void Drone(Cylinder& cylinder, Cube& cube, Shader& lightingShader, glm::mat4 alTogether);


//object making functions
void Table(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void Chair(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void ChairTableCombo(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
//void Sofa(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
//void OvenCooker(Cube& cube, Cube& chula, Cube& oven, Cube& basin, Shader& lightingShader, Shader& lightingShaderWithTexture, glm::mat4 alTogether);
//void ShowcaseRack(Cylinder& cylinder1, Cube& chips, Cube& chips2, Cube& chips3, Cube& cube, Shader& lightingShader, glm::mat4 alTogether);


long long nCr(int n, int r);
void BezierCurve(double t, float xy[2], GLfloat ctrlpoints[], int L);
//unsigned int hollowBezier(GLfloat ctrlpoints[], int L);

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
float dx=88, dy=14.5, dz=10;
int imgInd = 0;
bool tvOn = false;

vector<string>imagesForTv{
 "TV/tv (1).jpg",
"TV/tv (2).jpg",
"TV/tv (3).jpg",
"TV/tv (4).jpg",
"TV/tv (5).jpg",
"TV/tv (6).jpg",
"TV/tv (7).jpg",
"TV/tv (8).jpg",
"TV/tv (9).jpg",
"TV/tv (10).jpg",
"TV/tv (11).jpg",
"TV/tv (12).jpg",
"TV/tv (13).jpg",
"TV/tv (14).jpg",
"TV/tv (15).jpg",
"TV/tv (16).jpg",
"TV/tv (17).jpg",
"TV/tv (18).jpg",
"TV/tv (19).jpg",
"TV/tv (20).jpg",
"TV/tv (21).jpg",
"TV/tv (22).jpg",
"TV/tv (23).jpg",
"TV/tv (24).jpg",
"TV/tv (25).jpg",
"TV/tv (26).jpg",
"TV/tv (27).jpg",
"TV/tv (28).jpg",
"TV/tv (29).jpg",
"TV/tv (30).jpg",
"TV/tv (31).jpg",
"TV/tv (32).jpg",
"TV/tv (33).jpg",
"TV/tv (34).jpg",
"TV/tv (35).jpg",
"TV/tv (36).jpg",
"TV/tv (37).jpg",
"TV/tv (38).jpg",
"TV/tv (39).jpg",
"TV/tv (40).jpg",
"TV/tv (41).jpg",
"TV/tv (42).jpg",
"TV/tv (43).jpg",
"TV/tv (44).jpg",
"TV/tv (45).jpg",
"TV/tv (46).jpg",
"TV/tv (47).jpg",
"TV/tv (48).jpg",
"TV/tv (49).jpg",
"TV/tv (50).jpg",
"TV/tv (51).jpg",
"TV/tv (52).jpg",
"TV/tv (53).jpg",
"TV/tv (54).jpg",
"TV/tv (55).jpg",
"TV/tv (56).jpg",
"TV/tv (57).jpg",
"TV/tv (58).jpg",
"TV/tv (59).jpg",
"TV/tv (60).jpg",
"TV/tv (61).jpg",
"TV/tv (62).jpg",
"TV/tv (63).jpg",
"TV/tv (64).jpg",
"TV/tv (65).jpg",
"TV/tv (66).jpg",
"TV/tv (67).jpg",
"TV/tv (68).jpg",
"TV/tv (69).jpg",
"TV/tv (70).jpg",
"TV/tv (71).jpg",
"TV/tv (72).jpg",
"TV/tv (73).jpg",
"TV/tv (74).jpg",
"TV/tv (75).jpg",
"TV/tv (76).jpg",
"TV/tv (77).jpg",
"TV/tv (78).jpg",
"TV/tv (79).jpg",
"TV/tv (80).jpg",
"TV/tv (81).jpg",
"TV/tv (82).jpg",
"TV/tv (83).jpg",
"TV/tv (84).jpg",
"TV/tv (85).jpg",
"TV/tv (86).jpg",
"TV/tv (87).jpg",
"TV/tv (88).jpg",
"TV/tv (89).jpg",
"TV/tv (90).jpg",
"TV/tv (91).jpg",
"TV/tv (92).jpg",
"TV/tv (93).jpg",
"TV/tv (94).jpg",
"TV/tv (95).jpg",
"TV/tv (96).jpg",
"TV/tv (97).jpg",
"TV/tv (98).jpg",
"TV/tv (99).jpg",
"TV/tv (100).jpg",
"TV/tv (101).jpg",
"TV/tv (102).jpg",
"TV/tv (103).jpg",
"TV/tv (104).jpg",
"TV/tv (105).jpg",
"TV/tv (106).jpg",
"TV/tv (107).jpg",
"TV/tv (108).jpg",
"TV/tv (109).jpg",
"TV/tv (110).jpg",
"TV/tv (111).jpg",
"TV/tv (112).jpg",
"TV/tv (113).jpg",
"TV/tv (114).jpg",
"TV/tv (115).jpg",
"TV/tv (116).jpg",
"TV/tv (117).jpg",
"TV/tv (118).jpg",
"TV/tv (119).jpg",
"TV/tv (120).jpg",
"TV/tv (121).jpg",
"TV/tv (122).jpg",
"TV/tv (123).jpg",
"TV/tv (124).jpg",
"TV/tv (125).jpg",
"TV/tv (126).jpg",
"TV/tv (127).jpg",
"TV/tv (128).jpg",
"TV/tv (129).jpg",
"TV/tv (130).jpg",
"TV/tv (131).jpg"
};

vector<float> cntrlPoints
{
-0.8000, 1.4500, 5.1000,
-0.8000, 1.3150, 5.1000,
-0.7750, 1.2050, 5.1000,
-0.7150, 1.1350, 5.1000,
-0.6400, 1.0500, 5.1000,
-0.5650, 0.9750, 5.1000,
-0.4550, 0.9400, 5.1000,
-0.3550, 0.9150, 5.1000,
-0.2800, 0.8950, 5.1000,
-0.2250, 0.8900, 5.1000,
-0.1700, 0.8850, 5.1000,
-0.0800, 0.8650, 5.1000,
-0.0500, 0.8600, 5.1000,
0.0450, 0.8550, 5.1000,
0.0150, 0.8850, 5.1000,
0.0750, 0.8800, 5.1000,
-0.7850, 1.4650, 5.1000,
-0.7550, 1.5000, 5.1000,
-0.7250, 1.5100, 5.1000,
-0.6800, 1.5150, 5.1000,
-0.6550, 1.5050, 5.1000,
-0.6350, 1.4550, 5.1000,
-0.6300, 1.4250, 5.1000,
-0.6200, 1.3900, 5.1000,
-0.6000, 1.3450, 5.1000,
-0.5650, 1.3050, 5.1000,
-0.5300, 1.2700, 5.1000,
-0.4900, 1.2450, 5.1000,
-0.4350, 1.2350, 5.1000,
-0.4000, 1.2200, 5.1000,
-0.3400, 1.2050, 5.1000,
-0.2750, 1.2000, 5.1000,
-0.2100, 1.2000, 5.1000,
-0.1500, 1.2000, 5.1000,
-0.1000, 1.1800, 5.1000,
-0.0350, 1.1750, 5.1000,
0.0400, 1.1750, 5.1000,
0.0900, 1.1750, 5.1000,
0.0900, 1.1750, 5.1000,
0.1200, 1.1750, 5.1000,
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
vector<float> lights
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


Camera camera(glm::vec3(35.0f, 13.0f, 250.0f));  //initial camera position
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
bool doorOpen = true;
bool familydoorOpen = true;
bool kebabdoorOpen = true;
bool toiletdoorOpen1 = true;
bool toiletdoorOpen2 = true;
bool washroomdoorOpen = true;
bool fanOn = false;
bool droneOn = false;

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
    string f_tiles = "images/floor_tiles.jpg";
    string fnameImage = "images/banner.jpg";
    string floorImage = "images/floor.jpg";
    string bricks1 =  "images/bricks1.jpg";
    string court2 = "images/court2.jpg";
    string court2Upper = "images/court2Upper.jpg";
    string court3 = "images/court3.jpg";
    string court4 = "images/court4.jpg";
    string court5 = "images/court5.jpg";
    string roof = "images/court4-2.jpg";
    string wood = "images/wood.jpg";
    string sofa = "images/sofa.jpg";
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
    string wallmat1 =   "images/wallmat1.jpg";
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
    Cube court1 = Cube(glm::vec3(0.976f, 0.671f, 0.0f), glm::vec3(0.976f, 0.671f, 0.0f), glm::vec3(0.976f, 0.671f, 0.0f), 32, 1.0f);
    Cube court3Cube = Cube(glm::vec3(0.643f, 0.204f, 0.227f), glm::vec3(0.643f, 0.204f, 0.227f), glm::vec3(0.643f, 0.204f, 0.227f), 32, 1.0f);
    Cube court4Cube = Cube(glm::vec3(0.361f, 0.0f, 0.004f), glm::vec3(0.361f, 0.0f, 0.004f), glm::vec3(0.361f, 0.0f, 0.004f), 32, 1.0f);

    //Cube court2 = Cube(glm::vec3(0.196f, 0.835f, 0.094f), glm::vec3(0.196f, 0.835f, 0.094f), glm::vec3(0.196f, 0.835f, 0.094f), 32, 1.0);

    //Cube wall_cube = Cube(wall_tex, wall_tex, 32.0, 0.0f, 0.0f, 20.0f, 10.0f);
    Cube chair_cube = Cube(glm::vec3(0.22f, 0.22f, 0.22f), glm::vec3(0.22f, 0.22f, 0.22f), glm::vec3(0.22f, 0.22f, 0.22f), 32, 1.0f);
    Sphere globe1 = Sphere(1.0f, 36, 18, glm::vec3(0.941f, 0.824f, 0.745f), glm::vec3(0.941f, 0.824f, 0.745f), glm::vec3(0.941f, 0.824f, 0.745f), 32.0f);

    Sphere sphere = Sphere();
    Cylinder cylinder1 = Cylinder();

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    

    //bazierVAO---------------starts
/*
    bezierVAO = hollowBezier(cntrlPoints.data(), ((unsigned int)cntrlPoints.size() / 3) - 1);
    
    coordinates.clear();
    normals.clear();
    indices.clear();
    vertices.clear();
    bezierCylinderVAO = hollowBezier(cntrlPointsCylinder.data(), ((unsigned int)cntrlPointsCylinder.size() / 3) - 1);
    
    coordinates.clear();
    normals.clear();
    indices.clear();
    vertices.clear();
    bezierLightsVAO = hollowBezier(lights.data(), ((unsigned int)lights.size() / 3) - 1);

    coordinates.clear();
    normals.clear();
    indices.clear();
    vertices.clear();
    bezierBottleVAO = hollowBezier(bottle.data(), ((unsigned int)bottle.size() / 3) - 1);
    */
    //bazierVAO---------------ends


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
        glClearColor(0.62f, 0.62f, 0.52f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


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

        //inside room point lights
        //light1
        for (int i = 0; i < 2; i++) {
            model = transform(10, 20.25, 40+30*i, 00.0f, 0.0f, 0.0f, 0.04, -0.15, 0.04);
            cylinder1.drawCylinder(lightingShader, model);
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
            model = transform(30, 20.25, 40 + 30 * i, 00.0f, 0.0f, 0.0f, 0.04, -0.15, 0.04);
            cylinder1.drawCylinder(lightingShader, model);
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
/*
        //footpath
        model = transform(-100, -6, 140, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 250, -2, 10);
        RightSideWall2.drawCubeWithTexture(lightingShaderWithTexture, model);
        //roads
        model = transform(-100, -8, 150, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 250, -1, 60);
        road_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
*/
        //grass
        model = transform(-100, -6, -50, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 250, -0.2, 190);
        grass_cube.drawCubeWithTexture(lightingShaderWithTexture, model);

//        model = transform(-100, -6, 200, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 250, -2, 10);
 //       RightSideWall2.drawCubeWithTexture(lightingShaderWithTexture, model);


        //my clock
        //black base
/*        model = transform(6.75, 12.25, 99, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -4, 4, -0.1);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        //main base frame
        model = transform(6.5, 12.5, 98.9, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -3.5, 3.5, -0.1);
        clock_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        
        int hours, minutes, seconds;
        getCurrentTime(hours, minutes, seconds);
        hours = (hours + 6) % 12;
        //ghorir kata
        model = transform(4.95, 14.45, 98.9, 0, 0, 0, -0.4, -0.4, -0.2);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
         // second
        float rudian = (-(seconds - 30) * 6.0f);
        model = transform(4.75, 14.25, 98.8, rotateAngle_X, rotateAngle_Y, -rudian, 0.1, -1.7, -0.1);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        // minutes
        rudian = -(minutes * 60 + seconds - 30) * 0.1f + 180.0f;
        model = transform(4.75, 14.25, 98.7, rotateAngle_X, rotateAngle_Y, -rudian, 0.1, -1.4, -0.1);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        // hours
        rudian = -(hours * 3600 + minutes * 60 + seconds - 30) * (1.0f / 120.0f);
        model = transform(4.75, 14.25, 98.6, rotateAngle_X, rotateAngle_Y, -rudian, 0.1, -1.1, -0.1);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        */  
        
        //my fan
        //ceiling hanger
/*
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

        //----------------fan2-------------------------------------
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

*/
        //angle
 //       if (fanOn) {
 //           ang += 20;
  //          ang = ang % 360;
  //      }
/*
        //-------------------------Drone--------------------
        model = transform(dx, dy, dz, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.5, 0.5, 0.5);
        Drone(cylinder1, floorExtension, lightingShader, model);
        if (droneOn) {
            Dang += 60;
            Dang %= 420;
        }
*/

        //floor-------------------------------------------------------------------------------------
        model = transform(-25, -6, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 85, 5.8, 120);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);

        model = transform(-25, -0.2, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 85, 0.2, 115);
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
        /*
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
        */
        //left side wall
        model = transform(-25, 0, 25, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 18, 85);
        wall1.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(-25, 18, 25, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 3, 75);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(-24, 18, 100, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 33, 3, -1);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(10, 18, 99, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -1, 3, 16);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);

        //back wall
        model = transform(-40, 0, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 100, 18, 1);
        wall1.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(-40, 18, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 100, 3, 1);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);


        //Right wall
        model = transform(60, 0, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -1, 18, 10);
        wall1.drawCubeWithMaterialisticProperty(lightingShader, model);

        model = transform(60, 0, 30, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -1, 18, 85);
        wall1.drawCubeWithMaterialisticProperty(lightingShader, model);

        model = transform(60.1, 18, 115, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -1.1, 5, -42);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);

        model = transform(60.1, 18, 73, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -1.1, 5, -34);
        wall1.drawCubeWithMaterialisticProperty(lightingShader, model);

        model = transform(60.1, 18, 115, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -50.1, 3, -1);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);


        model = transform(60, 18, 115, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.1, -18, -5);
        bricks1_cube_chipa.drawCubeWithTexture(lightingShaderWithTexture, model);

        model = transform(60.1, 5, 30.0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.1, 2, 65);
        RightSideWall2.drawCubeWithTexture(lightingShaderWithTexture, model);
        model = transform(60, 5, 0.1, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 39, 2, 1);
        RightSideWall3.drawCubeWithTexture(lightingShaderWithTexture, model);

        model = transform(60, 5, 0.1, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.1, 2, 9.9);
        RightSideWall4.drawCubeWithTexture(lightingShaderWithTexture, model);

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

        //tv
        /*
        model = transform(15, 9.7, 114, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 10, 6.3, -0.2);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(15.2, 10.2, 113.7, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 9.6, 5.6, 0.1);
        if (tvOn) {
            tv_tex = loadTexture(imagesForTv[imgInd].c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
            tv_cube.setTextureProperty(tv_tex, tv_tex, 32.0f);
            tv_cube.drawCubeWithTexture(lightingShaderWithTexture, model);

            imgInd++;
            imgInd %= imagesForTv.size();
        }
        else {
            tv_tex = loadTexture(tv.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
            tv_cube.setTextureProperty(tv_tex, tv_tex, 32.0f);
            tv_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
            imgInd = 0;
        }
        */

        //left side poster main door
        model = transform(59, 5, 90, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -0.1, 10, 15);
        wallmat1_cube.drawCubeWithTexture(lightingShaderWithTexture, model);

        //main entrance door
        model = transform(55, 0, 115, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -25, 0.5, -1);
        glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(55, 18, 115, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -25, -0.5, -1);
        glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);

        //2 sliders

/*
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 
      
        float r = 0.0f;

        if (!doorOpen) {
            model = transform(55.01, 0.5, 115, rotateAngle_X, -90, rotateAngle_Z, -12.5, 17, -0.5);
            glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);

        }
        else if (doorOpen) {

            model = transform(55.01, 0.5, 115, rotateAngle_X, 0, rotateAngle_Z, -12.5, 17, -0.5);
            glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);

        }

        model = transform(29.99, 0.5, 114.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 12.5, 17, -0.5);
        glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);
        glDisable(GL_BLEND);
    */
        //family corner
        //right top
    /*
        model = transform(10.1, 18, 115, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -1.1, -1, 25);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        //left top
        model = transform(-25, 18, 110, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, -1, 30);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
*/
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
/*
        //family entrance door
        model = transform(0, 0, 100, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -15, 0.5, -1);
        glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(0, 18, 100, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -15, -0.5, -1);
        glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);
        //2 sliders

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        if (familydoorOpen) {
            model = transform(-15.01, 0.5, 100, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 7.5, 17, -0.5);
            glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);
            model = transform(-0.01, 0.5, 99.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -7.5, 17, -0.5);
            glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);
        }
        else {
            model = transform(-15.01, 0.5, 100, rotateAngle_X, 90, rotateAngle_Z, 7.5, 17, -0.5);
            glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);
            model = transform(-0.01, 0.5, 99.5, rotateAngle_X, -90, rotateAngle_Z, -7.5, 17, -0.5);
            glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);
        }

        glDisable(GL_BLEND);
    */
        //right family entrance wall
    /*jobair
        model = transform(10, 0, 100, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -1, 18, 15);
        wall1.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(9, 0, 100, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -0.1, 18, 15);
        bricks1_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        */

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

        //famiily point light
        model = transform(-8, 18, 121.5, 00.0f, 0.0f, 0.0f, 0.04, -0.15, 0.04);
        cylinder1.drawCylinder(lightingShader, model);
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

        //washrooms extension****
        //
        model = transform(-25, -0.2, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -15, -5.8, 25);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(-25, -0.2, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -15, 0.2, 25);
        tiles_cube_chiba.drawCubeWithTexture(lightingShaderWithTexture, model);

        //left wall
        model = transform(-40, 0, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 18, 25);
        wall1.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(-40, 18, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 3, 25);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);

        model = transform(-39, 0, 25, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 14, 18, -1);
        wall1.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(-39, 18, 25, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 34, 3, -1);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);

        //pan floor 1
        model = transform(-39, 0, 1, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 10, 1, 12);
        white_cube.drawCubeWithMaterialisticProperty(lightingShader, model);
        //pan 1
 //       model = transform(-37, 1, 1.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 6, 0.05, 7);
  //      toilet_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        //side wall 1unit extra
        model = transform(-39, 1, 13, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 17, -12);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        //washroom door
        /*
        if (toiletdoorOpen1) {
            model = transform(-38, 1, 12.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 9, 17, 0.5);
            door_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else {
            model = transform(-38, 1, 12.5, rotateAngle_X, 90, rotateAngle_Z, 9, 17, 0.5);
            door_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        */

        //floor.drawCubeWithMaterialisticProperty(lightingShader, model);

        //uporer base
        model = transform(-39, 18, 12, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 22, 3, 1);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);

        model = transform(-5, 18, 25, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 3, -7);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(-5, 18, 18, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 14, 3, -1);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);

        model = transform(-27, 0, 1, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -2, 21, 12);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);

        //pan floor2
        model = transform(-27, 0, 1, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 10, 1, 12);
        white_cube.drawCubeWithMaterialisticProperty(lightingShader, model);
        //pan2
  //      model = transform(-26, 1, 1.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 6, 0.05, 7);
  //      toilet_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        //washroom door
        /*
        if (toiletdoorOpen2) {
            model = transform(-27, 1, 12.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 9, 17, 0.5);
            door_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        }
        else {
            model = transform(-27, 1, 12.5, rotateAngle_X, 90, rotateAngle_Z, 9, 17, 0.5);
            door_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        }*/

        model = transform(-17, 0, 1, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -1, 21, 12);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);

        //basin base
        model = transform(-17, 0, 1, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 26, 6, 5);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        
        //toilet point light 
        model = transform(-4.25, 21, 3.75, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.5, -0.1, 2.5);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);

        model = transform(-4, 20.9, 4, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2, -0.4, 2);
        white_cube.drawCubeWithMaterialisticProperty(lightingShader, model);

        //three basins
/*
        int aa = -12;
        for (int i = 0; i < 3; i++) {

            //tap
            model = transform(aa, 6, 1, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.2, 2.5, 0.2);
            floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
            model = transform(aa, 8.5, 1, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.2, -0.2, 2);
            floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
            model = transform(aa, 8.5, 3, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.2, -0.4, -0.2);
            floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);

            //basin
            model = transform(aa, 3.75, 3.25, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 4, 2.5, 2);
            lightingShader.setMat4("model", model);
            lightingShader.use();
            lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
            lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
            lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
            lightingShader.setFloat("material.shininess", 32.0f);
            glBindVertexArray(bezierVAO);
            glDrawElements(GL_TRIANGLES, (unsigned int)indices.size(), GL_UNSIGNED_INT, (void*)0);
            glBindVertexArray(0);

            model = transform(aa, 4, 3.25, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.25, 0.15, 0.25);
            cylinder1.drawCylinder(lightingShader, model);

            aa += 8;
        }
        */

        //mirror
        model = transform(-15.5, 9, 1, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 24, 7, 0.1);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);

        model = transform(-15, 9.5, 1.1, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 23, 6, 0.1);
        wall_cube.drawCubeWithTexture(lightingShaderWithTexture, model);

        //two door corners
        model = transform(-5, 0, 24, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 18, -7);
        wall1.drawCubeWithMaterialisticProperty(lightingShader, model);

        model = transform(7, 0, 18, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2, 18, -1);
        wall1.drawCubeWithMaterialisticProperty(lightingShader, model);

        //family entrance door
    /*
        model = transform(-4, 0, 18, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 11, 0.5, -1);
        glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(-4, 18, 18, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 11, -0.5, -1);
        glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);
        */
        //2 sliders
/*
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        if (washroomdoorOpen) {
            model = transform(-4, 0.5, 18, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 5.5, 17, -0.49);
            glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);

            model = transform(7, 0.5, 17.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -5.5, 17, -0.49);
            glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);
           
        }
        else {
            model = transform(-4, 0.5, 18, rotateAngle_X, -90, rotateAngle_Z, 5.5, 17, -0.49);
            glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);

            model = transform(7, 0.5, 17.5, rotateAngle_X, 90, rotateAngle_Z, -5.5, 17, -0.49);
            glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);
        }
        glDisable(GL_BLEND);
*/
        //left side courts
        //first counter widht
        //ovenCookerFirst

      //  translateMatrix = glm::translate(identityMatrix, glm::vec3(-24, 0, 55.5));
      //  scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1, 1));
      //  OvenCooker(floorExtension, chula_cube, oven_cube, basin_cube, lightingShader, lightingShaderWithTexture, translateMatrix * scaleMatrix);

        //coke fridge
 //       model = transform(-24, 0, 76, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 4, 11, 5);
   //     floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
     //   model = transform(-20, 2, 76.25, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.1, 8.65, 4.5);
       // coke_cube.drawCubeWithTexture(lightingShaderWithTexture, model);

        //showcase
  //      translateMatrix = glm::translate(identityMatrix, glm::vec3(-24, 8, 73.5));
    //    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(00.0f), glm::vec3(0.0f, 1.0f, 0.0f));
      //  scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1, -0.85));
   //     ShowcaseRack(cylinder1, chips_cube, chips2_cube, chips3_cube, wood2_cube, lightingShaderWithTexture, translateMatrix * scaleMatrix * rotateYMatrix);


  //      model = transform(-24, 0, 85, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 19, 7, -1);
  //      court1.drawCubeWithMaterialisticProperty(lightingShader, model);
  //      model = transform(-24, 0, 85.1, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 20, 7, -0.1);
  //      court1.drawCubeWithMaterialisticProperty(lightingShader, model);
//        model = transform(-24, 7, 86, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 20, 0.5, -4);
  //      glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);

  //      model = transform(-24, 21, 85, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 19, -6, -1);
   //     court1.drawCubeWithMaterialisticProperty(lightingShader, model);
 //       model = transform(-24, 15, 86, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 21, -0.5, -2);
 //       glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);

        //first counter length
//        model = transform(-5, 0, 85, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 7, -30);
  //      court2Upper_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
//        model = transform(-7, 7, 86, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 4, 0.5, -31);
 //       glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);

//        model = transform(-5, 21, 85, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, -6, -30);
 //       court1.drawCubeWithMaterialisticProperty(lightingShader, model);

//        model = transform(-5, 15, 85, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2, -0.5, -30);
  //      glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);

        //second court length

 //       translateMatrix = glm::translate(identityMatrix, glm::vec3(-24, 0, 54.5));
   //     scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1, -1));
     //   OvenCooker(floorExtension, chula_cube, oven_cube, basin_cube, lightingShader, lightingShaderWithTexture, translateMatrix * scaleMatrix);

        //showcase
  //      translateMatrix = glm::translate(identityMatrix, glm::vec3(-24, 8, 45));
  //      rotateYMatrix = glm::rotate(identityMatrix, glm::radians(00.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    //    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1, -0.95));
    //    ShowcaseRack(cylinder1, chips_cube, chips2_cube, chips3_cube, wood2_cube, lightingShaderWithTexture, translateMatrix * scaleMatrix * rotateYMatrix);

        //coke fridge
//        model = transform(-24, 0, 25, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 4, 11, 5);
  //      floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
    //    model = transform(-20, 2, 25.25, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.1, 8.65, 4.5);
      //  coke_cube.drawCubeWithTexture(lightingShaderWithTexture, model);



 //       model = transform(-5, 0, 55, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 7, -30);
  //      court2_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
 //       model = transform(-7, 7, 55, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 4, 0.5, -30);
   //     glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);

 //       model = transform(-5, 15, 55, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 6, -30);
   //     court2_cube.drawCubeWithTexture(lightingShaderWithTexture, model);

 //       model = transform(-3, 15, 55, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -2, -0.5, -30);
   //     glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);

        //middle partitions
        model = transform(-24, 0, 54.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 19, 18, 1);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        //right partitions
        model = transform(-25, 0, 25, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 21, 18, -1);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);

        //right side courts
//        translateMatrix = glm::translate(identityMatrix, glm::vec3(59, 0, 61));
  //      scaleMatrix = glm::scale(identityMatrix, glm::vec3(-1, 1, 1));
    //    rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
      //  OvenCooker(floorExtension, chula_cube, oven_cube, basin_cube, lightingShader, lightingShaderWithTexture, translateMatrix * scaleMatrix * rotateYMatrix);
        //coke fridge
//        model = transform(59, 0, 42, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -4, 11, 5);
  //      floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
    //    model = transform(55, 2, 42.25, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -0.1, 8.65, 4.5);
      //  coke_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        //showcase
 //       translateMatrix = glm::translate(identityMatrix, glm::vec3(59, 8, 63));
   //     rotateYMatrix = glm::rotate(identityMatrix, glm::radians(00.0f), glm::vec3(0.0f, 1.0f, 0.0f));
     //   scaleMatrix = glm::scale(identityMatrix, glm::vec3(-1, 1, 1));
       // ShowcaseRack(cylinder1, chips_cube, chips2_cube, chips3_cube, wood2_cube, lightingShaderWithTexture, translateMatrix * scaleMatrix * rotateYMatrix);

  //      model = transform(39, 0, 80, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 20, 7, -1);
    //    court4_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
 //       model = transform(59, 7, 79, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -20, 0.5, 2);
  //      glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);

 //       model = transform(59, 15, 79, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -20, 6, 1);
   //     court4_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
//        model = transform(59, 15, 79, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -20, -0.5, 2);
  //      glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);

 //       model = transform(38, 0, 80, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 7, -40);
   //     court4_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
 //       model = transform(39, 7, 81, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -3, 0.5, -42);
  //      glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);
 //       model = transform(38, 15, 80, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 6, -40);
    //    court4_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
 //       model = transform(39, 15, 81, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -2, -0.5, -42);
   //     glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);

  //      model = transform(59, 0, 40, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -20, 7, 1);
   //     court4_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
 //       model = transform(59, 7, 39, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -20, 0.5, 2);
   //     glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);
  //      model = transform(59, 15, 40, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -20, 6, 1);
    //    court4_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
 //       model = transform(59, 15, 41, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -20, -0.5, -2);
   //     glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);

        //front court
//        translateMatrix = glm::translate(identityMatrix, glm::vec3(10, 0, 1));
  //      rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    //    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1, -1));
      //  OvenCooker(floorExtension, chula_cube, oven_cube, basin_cube, lightingShader, lightingShaderWithTexture, translateMatrix * scaleMatrix * rotateYMatrix);
        //coke fridge
 //       model = transform(39, 0, 1, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -5, 11, 4);
   //     floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
     //   model = transform(34.25, 2, 5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 4.5, 8.65, 0.1);
       // coke_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        //showcase
//        translateMatrix = glm::translate(identityMatrix, glm::vec3(19, 8, 1));
  //      rotateYMatrix = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    //    scaleMatrix = glm::scale(identityMatrix, glm::vec3(1, 1, -1));
      //  ShowcaseRack(cylinder1, chips_cube, chips2_cube, chips3_cube, wood2_cube, lightingShaderWithTexture, translateMatrix * scaleMatrix * rotateYMatrix);


//        model = transform(10, 0, 1, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -1, 21, 20);
 //       floor.drawCubeWithMaterialisticProperty(lightingShader, model);
 //       model = transform(40, 0, 1, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -1, 21, 20);
 //       floor.drawCubeWithMaterialisticProperty(lightingShader, model);

//        model = transform(10, 0, 21, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 29, 7, -1);
  //      court3_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
 //       model = transform(10, 7, 23, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 29, 0.5, -3);
   //     glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);

 //       model = transform(10, 15, 21, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 29, 6, -1);
   //     court3_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
 //       model = transform(10, 15, 20, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 29, -0.5, 2);
    //    glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);



        //right extension
        //floors
        model = transform(60, -6, 30, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 55, 10.8, 80);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);

        model = transform(60, 4.8, 30, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 55, 0.2, 80);
        floor_tex_cube.drawCubeWithTexture(lightingShaderWithTexture, model);

        model = transform(60, -6, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 10, 10.8, 10);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(60, 4.8, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 10, .2, 10);
        floor_tex_cube_chipa.drawCubeWithTexture(lightingShaderWithTexture, model);

        model = transform(70, -6, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 45, 10.8, 30);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(70, 4.8, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 45, 0.2, 30);
        floor_tex_cube_chipa1.drawCubeWithTexture(lightingShaderWithTexture, model);

        
        //exit
        model = transform(60.1, 0, 10, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -5.1, 18, 1);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(60.1, 0, 30, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -5.1, 18, -1);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);

        model = transform(56, 18, 11, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 4.1, -0.5, 18);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(56, 0, 11, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 4.0, 0.5, 18);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        //roof entrance door
//        model = transform(55, 0, 11, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 0.5, 18);
  //      glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);
//        model = transform(55, 18, 11, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, -0.5, 18);
   //     glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);

        //2 sliders
/*
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        if (kebabdoorOpen) {
            model = transform(55, 0.5, 11.01, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.5, 17, 9);
            glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);
            model = transform(55.5, 0.5, 28.99, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.5, 17, -9);
            glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);
        }
        else {
                model = transform(55, 0.5, 11.01, rotateAngle_X, -90, rotateAngle_Z, 0.5, 17, 9);
                glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);
                model = transform(55.5, 0.5, 28.99, rotateAngle_X, 90, rotateAngle_Z, 0.5, 17, -9);
                glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);
        }

        glDisable(GL_BLEND);
    */

        //point light 9
        model = transform(74.75, 23, 18.75, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.5, -0.1, 2.5);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(75, 23.1, 19, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2, -0.4, 2);
        white_cube.drawCubeWithMaterialisticProperty(lightingShader, model);

        //Stairs 
        //z axis statirs
        /*
        model = transform(60, 0, 10, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 10, 1, 20);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(62, 1, 10, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 8, 1, 20);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(64, 2, 10, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 6, 1, 20);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(66, 3, 10, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 4, 1, 20);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(68, 4, 10, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2, 1, 20);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        */
        //extenson wall
        //back wall
        model = transform(60, 5, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 55, 18, 1);
        wall1.drawCubeWithMaterialisticProperty(lightingShader, model);
        //front wall
        model = transform(60, 5, 110, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 55, 5, -1);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        //right wall
        model = transform(115, 5, 1, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -1, 5, 109);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        //front extension footpath
        model = transform(60, -6, 110, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 57, 1, 30);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(60, -5, 110, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 55, 1, 27);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);

        //extenstion photo zone
        model = transform(60.1, 18, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -1.1, 5, 39);
        wall1.drawCubeWithMaterialisticProperty(lightingShader, model);
        //roof
        model = transform(59, 23, 34, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 3, 39);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);

        model = transform(59, 26, 34, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 10, 1, 39);
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
        /*
        //photo 1
        model = transform(60.1, 11, 37, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.1, 9, 6);
        pic1_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        //photo 2
        model = transform(60.1, 11, 46, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.1, 9, 6);
        pic2_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        //photo 3
        model = transform(60.1, 11, 55, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.1, 9, 6);
        pic3_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        //photo 4
        model = transform(60.1, 11, 64, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.1, 9, 6);
        pic4_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        
        //photo 5
        model = transform(60.1, 13, 73, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.1, 3, 6);
        pic5_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
*/
        //stage

        model = transform(60, 5, 110, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 28, 1, -18);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(60, 6, 110, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 25, 1, -15);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);

        //stage sound box
    /*
        model = transform(61, 7, 102, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.5, 4, 2);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(61, 11, 102, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.5, -4, -0.1);
        soundbox_cube.drawCubeWithTexture(lightingShaderWithTexture, model);

        model = transform(81.5, 7, 100, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.5, 4, 2);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(81.5, 11, 100, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2.5, -4, -0.1);
        soundbox_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        */
        //stage roof:
        model = transform(60, -6, 110, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 30, 35, 1);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        //song banner
        //black background
 //       model = transform(60, 5, 110, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 30, 24, -0.1);
   //     glassDoor.drawCubeWithMaterialisticProperty(lightingShader, model);
        //banner
   //     model = transform(88, 12, 109.9, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -26, 15, -0.05);
   //     music_cube.drawCubeWithTexture(lightingShaderWithTexture, model);

        /*
        model = transform(60, 29, 116, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 30, 1, -25);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        int ab = 63;
        for (int i = 0; i < 4; i++) {
            model = transform(ab, 29.2, 112, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.6, -0.04, 0.6);
            cylinder1.drawCylinder(lightingShader, model);
            if (i == 2 or i == 1) {
                model = transform(ab, 29.2, 109, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.6, -0.04, 0.6);
                cylinder1.drawCylinder(lightingShader, model);
            }
            ab += 8;
        }


        //food court name
        model = transform(65, 10, 111, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 20, 14, 0.5);
        fName.drawCubeWithTexture(lightingShaderWithTexture, model);

        // kebab house
        // ovenCooker
        model = transform(17.5, 21, 70, 00.0f, 0.0f, 0.0f, 0.25, -0.15, 0.25);
        cylinder1.drawCylinder(lightingShader, model);
        */
//        translateMatrix = glm::translate(identityMatrix, glm::vec3(114, 5, 1));
  //      rotateYMatrix = glm::rotate(identityMatrix, glm::radians(00.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    //    scaleMatrix = glm::scale(identityMatrix, glm::vec3(-1, 1, 1));
      //  OvenCooker(floorExtension, chula_cube, oven_cube, basin_cube, lightingShader, lightingShaderWithTexture, translateMatrix * scaleMatrix * rotateYMatrix);

        //draw kabab stove
/*
        model = transform(92.5, 5, 1.1, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 7.4, 5, 5);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(92.5, 10, 1.1, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.2, 1, 5);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(99.7, 10, 1.1, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.2, 1, 5);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(92.7, 10, 1.1, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 7, 0.2, 4);
        coal_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        model = transform(92.7, 10, 5.1, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 7, 0.2, 1);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
*/

        //coke fridge
        model = transform(110, 5, 18.8, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 4, 11, 5);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(110, 7, 19.05, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -0.1, 8.65, 4.5);
        coke_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        //showcase
//        translateMatrix = glm::translate(identityMatrix, glm::vec3(114, 13, 9));
//       rotateYMatrix = glm::rotate(identityMatrix, glm::radians(00.0f), glm::vec3(0.0f, 1.0f, 0.0f));
 //       scaleMatrix = glm::scale(identityMatrix, glm::vec3(-1, 1, 0.65));
 //       ShowcaseRack(cylinder1, chips_cube, chips2_cube, chips3_cube, wood2_cube, lightingShaderWithTexture, translateMatrix * scaleMatrix * rotateYMatrix);

        //kebab house floor
        model = transform(115, 5, 1, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -30, 1, 30);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
        //roof height
        model = transform(115, 10, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -1, 13, 35);
        wall1.drawCubeWithMaterialisticProperty(lightingShader, model);
        //roof
        model = transform(60, 23, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -1, -5, 35);
        wall1.drawCubeWithMaterialisticProperty(lightingShader, model);
        //roof color
        model = transform(60, 23, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.1, -5, 35);
        wall1.drawCubeWithMaterialisticProperty(lightingShader, model);
        //roof color
        model = transform(60, 18, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.1, -11, 10);
        wall1.drawCubeWithMaterialisticProperty(lightingShader, model);

        //tables
        //front


        model = transform(87, 5, 1, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 3, 7, 25);
        court5_cube.drawCubeWithTexture(lightingShaderWithTexture, model);

        //right side
        model = transform(114, 5, 26, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -24, 7, -2);
        court5_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        //front upper
        model = transform(87, 17, 1, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 1, 6, 25);
        court5_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        //right upper
        model = transform(114, 17, 26, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -26, 6, -2);
        court5_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
    
        //right extension design extra
        //right side upper 
        model = transform(115, 5, 35, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2, 5, 75);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        //right side lower 
        model = transform(115, -6, 35, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2, 8, 75);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);

        //cylinder stand
        int xxx = 95;
        for (int i = 0; i < 4; i++) {
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
        model = transform(90, 5, 110, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 27, 5, 1);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        //front side lower
        model = transform(90, -6, 110, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 27, 8, 1);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        //front floor design extra
        //left
        model = transform(-25, 5, 140, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 55, -2, 2);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(-25, 0, 140, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 55, -6, 2);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        //right
        model = transform(60, 0, 140, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -5, -6, 2);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(60, 0, 142, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 2, -6, -32);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        //left floor design extra
        model = transform(-25, 5, 110, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -2, -2, 32);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(-25, 0, 110, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -2, -6, 32);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        
        //table chair combo
        
        int x = 100, z = 40;
/*        for (int i = 0; i < 4; i++) {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(x, 5, z));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(2, 1.2, 1.5));
           // ChairTableCombo(wood_cube, lightingShaderWithTexture, translateMatrix * scaleMatrix);
            z += 18;
            //model = transform(17.5, 21, 50, 00.0f, 0.0f, 0.0f, 0.25, -0.15, 0.25);
        }*/
        x = 85, z = 40;
        for (int i = 0; i < 2; i++) {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(x, 5, z));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(2, 1.2, 1.5));
            ChairTableCombo(wood_cube, lightingShaderWithTexture, translateMatrix * scaleMatrix);
            z += 18;
        }
        /*
        x = 70, z = 40;
        for (int i = 0; i < 2; i++) {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(x, 5, z));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(2, 1.2, 1.5));
          //  ChairTableCombo(wood_cube, lightingShaderWithTexture, translateMatrix * scaleMatrix);
            z += 18;
        }*/
        //inner chair tables
/*
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
            model = transform(x+4.6, 4, z+5.4, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.5, 1, 0.5);
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
            Chair(floorExtension, lightingShader, translateMatrix* scaleMatrix);

            translateMatrix = glm::translate(identityMatrix, glm::vec3(x + 5.5, 0, z + 9.5));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 1, -1.5));
            Chair(floorExtension, lightingShader, translateMatrix* scaleMatrix);

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

        //outside chair table
        x = 15.2, z = 122.2;
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

        //chair
        translateMatrix = glm::translate(identityMatrix, glm::vec3(x, 0, z + 9.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 1, -1.5));
        Chair(floorExtension, lightingShader, translateMatrix * scaleMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(x + 5.5, 0, z + 9.5));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.5, 1, -1.5));
        Chair(floorExtension, lightingShader, translateMatrix* scaleMatrix);

        */
        //family sofa
        /*
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
        */


        //ceils 
/*
        model = transform(59, 21, 100, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -50, 0.2, 15);
        ceil_cube2.drawCubeWithTexture(lightingShaderWithTexture, model);
        model = transform(-25, 21, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 84, 0.2, 100);
        ceil_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        model = transform(-25, 21, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -15, 0.2, 25);
        ceil_cube2.drawCubeWithTexture(lightingShaderWithTexture, model);

        model = transform(59, 21.2, 100, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -50, 1.5, 15);
        wood2_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        model = transform(-25, 21.2, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 84, 1.5, 100);
        wood2_cube.drawCubeWithTexture(lightingShaderWithTexture, model);
        model = transform(-25, 21.2, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -15, 1.5, 25);
        wood2_cube.drawCubeWithTexture(lightingShaderWithTexture, model);

        model = transform(59, 22.7, 100, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -50, 0.3, 15);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(-25, 22.7, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 84, 0.3, 100);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);
        model = transform(-25, 22.7, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, -15, 0.3, 25);
        floorExtension.drawCubeWithMaterialisticProperty(lightingShader, model);

        //right extension ceils
        model = transform(59, 23, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 56, 8, 35);
        floor.drawCubeWithMaterialisticProperty(lightingShader, model);
*/

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    cout << translate_X << " ," << translate_Y << " ," << translate_Z << endl;
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
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        camera.ProcessKeyboard(UP, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        camera.ProcessKeyboard(DOWN, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        camera.ProcessKeyboard(P_UP, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
        camera.ProcessKeyboard(P_DOWN, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
        camera.ProcessKeyboard(Y_LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
        camera.ProcessKeyboard(Y_RIGHT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
        camera.ProcessKeyboard(R_LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        camera.ProcessKeyboard(R_RIGHT, deltaTime);
    }
 /*
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        if (dz < 100 and droneOn)
            dz += 0.2;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        if (dz > 1 and droneOn)
            dz -= 0.2;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        if (dx < 110 and droneOn)
            dx += 0.2; 
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        if (dx > 62 and droneOn)
            dx -= 0.2;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_BRACKET) == GLFW_PRESS) {
        if (dy < 25 and droneOn)
            dy += 0.2;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT_BRACKET) == GLFW_PRESS) {
        if (dy > 8 and droneOn)
            dy -= 0.2;
    }
*/
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
        //toiletdoorOpen1 = !toiletdoorOpen1;
    }
    if (key == GLFW_KEY_P && action == GLFW_PRESS)
    {
        toiletdoorOpen2 = !toiletdoorOpen2;
    }
    if (key == GLFW_KEY_F && action == GLFW_PRESS)
    {
       // fanOn = !fanOn;
    }
    if (key == GLFW_KEY_L && action == GLFW_PRESS)
    {
        //droneOn = !droneOn;
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
/*
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
*/
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
/*
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
*/
/*
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
*/
/*
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
*/
/*
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
*/
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

/*
void BezierCurve(double t, float xy[2], GLfloat ctrlpoints[], int L)
{
    double y = 0;
    double x = 0;
    t = t > 1.0 ? 1.0 : t;
    for (int i = 0; i < L + 1; i++)
    {
        long long ncr = nCr(L, i);
        double oneMinusTpow = pow(1 - t, double(L - i));
        double tPow = pow(t, double(i));
        double coef = oneMinusTpow * tPow * ncr;
        x += coef * ctrlpoints[i * 3];
        y += coef * ctrlpoints[(i * 3) + 1];

    }
    xy[0] = float(x);
    xy[1] = float(y);
}

*/
/*
unsigned int hollowBezier(GLfloat ctrlpoints[], int L)
{
    int i, j;
    float x, y, z, r;                //current coordinates
    float theta;
    float nx, ny, nz, lengthInv;    // vertex normal


    const float dtheta = 2 * pi / ntheta;        //angular step size

    float t = 0;
    float dt = 1.0 / nt;
    float xy[2];

    for (i = 0; i <= nt; ++i)              //step through y
    {
        BezierCurve(t, xy, ctrlpoints, L);
        r = xy[0];
        y = xy[1];
        theta = 0;
        t += dt;
        lengthInv = 1.0 / r;

        for (j = 0; j <= ntheta; ++j)
        {
            double cosa = cos(theta);
            double sina = sin(theta);
            z = r * cosa;
            x = r * sina;

            coordinates.push_back(x);
            coordinates.push_back(y);
            coordinates.push_back(z);

            // normalized vertex normal (nx, ny, nz)
            // center point of the circle (0,y,0)
            nx = (x - 0) * lengthInv;
            ny = (y - y) * lengthInv;
            nz = (z - 0) * lengthInv;

            normals.push_back(nx);
            normals.push_back(ny);
            normals.push_back(nz);

            theta += dtheta;
        }
    }

    // generate index list of triangles
    // k1--k1+1
    // |  / |
    // | /  |
    // k2--k2+1

    int k1, k2;
    for (int i = 0; i < nt; ++i)
    {
        k1 = i * (ntheta + 1);     // beginning of current stack
        k2 = k1 + ntheta + 1;      // beginning of next stack

        for (int j = 0; j < ntheta; ++j, ++k1, ++k2)
        {
            // k1 => k2 => k1+1
            indices.push_back(k1);
            indices.push_back(k2);
            indices.push_back(k1 + 1);

            // k1+1 => k2 => k2+1
            indices.push_back(k1 + 1);
            indices.push_back(k2);
            indices.push_back(k2 + 1);
        }
    }

    size_t count = coordinates.size();
    for (int i = 0; i < count; i += 3)
    {
        vertices.push_back(coordinates[i]);
        vertices.push_back(coordinates[i + 1]);
        vertices.push_back(coordinates[i + 2]);

        vertices.push_back(normals[i]);
        vertices.push_back(normals[i + 1]);
        vertices.push_back(normals[i + 2]);
    }

    unsigned int bezierVAO;
    glGenVertexArrays(1, &bezierVAO);
    glBindVertexArray(bezierVAO);

    // create VBO to copy vertex data to VBO
    unsigned int bezierVBO;
    glGenBuffers(1, &bezierVBO);
    glBindBuffer(GL_ARRAY_BUFFER, bezierVBO);           // for vertex data
    glBufferData(GL_ARRAY_BUFFER,                   // target
        (unsigned int)vertices.size() * sizeof(float), // data size, # of bytes
        vertices.data(),   // ptr to vertex data
        GL_STATIC_DRAW);                   // usage

    // create EBO to copy index data
    unsigned int bezierEBO;
    glGenBuffers(1, &bezierEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bezierEBO);   // for index data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,           // target
        (unsigned int)indices.size() * sizeof(unsigned int),             // data size, # of bytes
        indices.data(),               // ptr to index data
        GL_STATIC_DRAW);                   // usage

    // activate attrib arrays
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // set attrib arrays with stride and offset
    int stride = 24;     // should be 24 bytes
    glVertexAttribPointer(0, 3, GL_FLOAT, false, stride, (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, stride, (void*)(sizeof(float) * 3));

    // unbind VAO, VBO and EBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return bezierVAO;
}
*/
void getCurrentTime(int& hours, int& minutes, int& seconds) {
    time_t currentTime = time(nullptr); // Get current UNIX timestamp
    struct tm* timeinfo;
    timeinfo = localtime(&currentTime);

    seconds = timeinfo->tm_sec;
    minutes = timeinfo->tm_min;
    hours = timeinfo->tm_hour;
}
/*void Drone(Cylinder& cylinder, Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{
    //pichoner base
    glm::mat4 translateMatrix, scaleMatrix, model;
    //upper base
    model = transform(0, 0, 0, rotateAngle_X, rotateAngle_Y, 0, 2, 0.7, 2);
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether*model);

    //stands
    model = transform(0,0,0, 0,0,0, 0.1, -2, 0.1);
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);
    model = transform(2, 0, 0, 0, 0, 0, -0.1, -2, 0.1);
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);

    model = transform(0, 0, 2, 0, 0, 0, 0.1, -2, -0.1);
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);
    model = transform(2, 0, 2, 0, 0, 0, -0.1, -2, -0.1);
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);


    //fan stand left
    model = transform(0, 0, 0.9, rotateAngle_X, rotateAngle_Y, 0, -3, .5, 0.2);
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether*model);
    //left fan********
    model = transform(-3, 0.5, 1, rotateAngle_X, Dang, 0, 0.1, .2, 1);
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);
    model = transform(-3, 0.5, 1, rotateAngle_X, Dang, 0, 0.1, .2, -1);
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);
    //fan stand right
    model = transform(2, 0, 0.9, rotateAngle_X, rotateAngle_Y, 0, 3, .5, 0.2);
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether *model);
    //right fan************
    model = transform(5, 0.5, 1, rotateAngle_X, Dang, 0, -0.1, .1, 1);
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);
    model = transform(5, 0.5, 1, rotateAngle_X, Dang, 0, -0.1, .1, -1);
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);

    //fan stand up
    model = transform(0.9, 0, 0, rotateAngle_X, rotateAngle_Y, 0, 0.2, .5, -3);
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);
    //up fan***************
    model = transform(1, 0.5, -3, rotateAngle_X, Dang, 0, -1, .1, 0.1);
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);
    model = transform(1, 0.5, -3, rotateAngle_X, Dang, 0, 1, .1, 0.1);
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);


    //fan stand down
    model = transform(0.9, 0, 2, rotateAngle_X, rotateAngle_Y, 0, 0.2, .5, 3);
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);
    
    //down fan***********
    model = transform(1, 0.5, 5, rotateAngle_X, Dang, 0, -1, .1, -0.1);
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);
    model = transform(1, 0.5, 5, rotateAngle_X, Dang, 0, 1, .1, -0.1);
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);


    //upper tray
    model = transform(-2, -2, -1, 0, 0, 0, 6, 0.2, 4);
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);
    
    //stands
    model = transform(-2, -2, -1, 0, 0, 0, 0.1, -3, 0.1);
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);
    model = transform(4, -2, -1, 0, 0, 0, -0.1, -3, 0.1);
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);

    model = transform(-2, -2, 3, 0, 0, 0, 0.1, -3, -0.1);
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);
    model = transform(4, -2, 3, 0, 0, 0, -0.1, -3, -0.1);
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);

    //glass
    model = transform(-1, -5, 0, 0.0f, 0.0f, 0.0f, 0.5, 0.1, 0.5);
    cylinder.drawCylinder(lightingShader, alTogether * model);
    model = transform(-1, -5, 2, 0.0f, 0.0f, 0.0f, 0.5, 0.1, 0.5);
    cylinder.drawCylinder(lightingShader, alTogether * model);
     
    model = transform(1.7, -5, 1, 0.0f, 0.0f, 0.0f, 1.7, 0.04, 1.7);
    cylinder.drawCylinder(lightingShader, alTogether * model);

    //lower tray
    model = transform(-2, -5, -1, 0, 0, 0, 6, 0.2, 4);
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);
    //side
    model = transform(-2, -5, -1, 0, 0, 0, 6, 0.4, 0.1);
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);
    model = transform(-2, -5, -1, 0, 0, 0, 0.1, 0.4, 4);
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);
    //side
    model = transform(4, -5, 3, 0, 0, 0, -6, 0.4, -0.1);
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);
    model = transform(4, -5, 3, 0, 0, 0, -0.1, 0.4, -4);
    cube.drawCubeWithMaterialisticProperty(lightingShader, alTogether * model);
}
*/
