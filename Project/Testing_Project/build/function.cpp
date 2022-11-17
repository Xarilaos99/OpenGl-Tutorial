// Include C++ headers
#include <iostream>
#include <string>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>   // glm::to_string

// Shader loading utilities and other
#include <common/shader.h>
#include <common/util.h>

using namespace std;
using namespace glm;
#include "functions.h"

GLFWwindow* window;
GLuint shaderProgram;
GLuint MVPLocation;
GLuint cubeVAO;
GLuint cubeVerticiesVBO, cubeColorsVBO;
GLuint ibo;

void createContext() {
    // Create and compile our GLSL program from the shaders
    shaderProgram = loadShaders("transformation.vertexshader",
        "simple.fragmentshader");

    MVPLocation = glGetUniformLocation(shaderProgram, "MVP");


    // cube VAO
    glGenVertexArrays(1, &cubeVAO);
    glBindVertexArray(cubeVAO);

    static const GLfloat cubeVerts[] = {
        -1.0f,-1.0f,-1.0f, //0
        -1.0f,-1.0f,1.0f,  //1
                           
        -1.0f,1.0f,-1.0f,  //2
        -1.0f,1.0f,1.0f,   //3
                           
        1.0f,-1.0f,-1.0f,  //4
        1.0f,-1.0f,1.0f,   //5
                           
        1.0f,1.0f,-1.0f,   //6
        1.0f,1.0f,1.0f,   //7

         0.0f,0.0f,2.0f//roof

    };


    glGenBuffers(1, &cubeVerticiesVBO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVerticiesVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVerts), cubeVerts, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);
    
    
    static const GLfloat cubeClrs[] = {
            1.0f,0.0f,0.0f, //0.0f
            1.0f,0.0f,0.0f, //1.0f
            
            0.0f,1.0f,0.0f, //2
            0.0f,1.0f,0.0f, //3
                           
            0.0f,0.0f,1.0f,  //4
            0.0f,0.0f,1.0f,  //5
                           
            1.0f,0.0f,1.0f,   //6
            1.0f,0.0f,1.0f,    //7

            0.0f,1.0f,1.0f,    //roof

            
    };


    glGenBuffers(1, &cubeColorsVBO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeColorsVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeClrs), cubeClrs, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(1);




    GLuint indices[] = {
        0,1,4,
        5,4,1,
        5,4,6,
        7,6,5,
        7,6,2,
        2,3,7,
        3,2,0,
        0,1,3,
        0,2,4,
        4,6,2,
        //======roof=========
        1,5,8,
        7,5,8,
        3,7,8,
        3,1,8
        
    };
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);



    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void free() {
    glDeleteBuffers(1, &cubeVerticiesVBO);
    glDeleteBuffers(1, &cubeColorsVBO);
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
}

void mainLoop() {




    // Projection matrix: 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    mat4 projection = perspective(radians(45.0), 4.0 / 3.0, 0.1, 100.0);
    // Or, for an ortho camera: -x:x, -y:y, -z:z
    mat4 Projection = ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.0f);
  

    
    do {
        // Task 12: depth test  | GL_DEPTH_BUFFER_BIT
        // Clear the screen (color and depth)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);

        
        // ===========================draw cube=======================================
        // code for cube
        // 
        glBindVertexArray(cubeVAO);


        float time = glfwGetTime();


       


        //spin periodicaly x-z
        mat4 view = lookAt(
            vec3(0.2 * sin(time), 0, 0.2 * cos(time)),//position
            vec3(0.0f, 0.0f, 0.0f),//where to look at
            vec3(0.0f, 1.0f, 0.0f)//up vector
        );
        //cubeMVP = view * cubeRotation * cubeScaling;

       

        //==========Rotate (1,1,-1)==========================
        mat4 perdiocalScaling = glm::scale(mat4(), vec3(cosf(3.14f / 1.5* time) + 1.1, 1.0, 1.0));
        mat4 cubeScaling= glm::scale(mat4(), vec3(0.3, 0.3, 0.3));
        mat4 cubeRotation = glm::rotate(mat4(), (float)3.14 / 2, vec3(-1.0, 0.0, 0.0));


        vec3 temp(1,-1, -1);
        float norm = sqrt(pow(temp.x, 2) + pow(temp.y, 2) + pow(temp.z, 2));
        float l = sqrt(pow(temp.x, 2) + pow(temp.y, 2));
        float angle_z = acos(temp.y / l);
        float angle_x = acos(l / norm);
        mat4 Rotation1 = glm::rotate(mat4(), -angle_z, vec3(0.0, 0.0, 1.0));
        mat4 Rotation2 = glm::rotate(mat4(), -angle_x, vec3(1.0, 0.0, 0.0));

        


        mat4 myRotation1 = glm::rotate(mat4(), (float)0.955, vec3(0.0, 1.0, 0.0));
        mat4 myRotation2 = glm::rotate(mat4(), -(float)0.955, vec3(1.0, 0.0, 0.0));



        vec3 Z(0, 0, -1);
        temp = normalize(temp);
        vec3 prod = cross(temp,Z);
        prod = normalize(prod);
        float angle = acos(dot(temp, Z));
        mat4 rotation = glm::rotate(mat4(),-angle, prod);
        //2*sin(time)*3.14f
        //cout << prod.x << " " << prod.y << " " << prod.z << endl;


        


        mat4 cubeMVP = view*myRotation2 * myRotation1 * cubeScaling;
        cubeMVP = rotation * view *cubeRotation*cubeScaling;

        glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, &cubeMVP[0][0]);


        glDrawElements(GL_TRIANGLES, 42 , GL_UNSIGNED_INT,0);


        //=======================window=========================
        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
        glfwWindowShouldClose(window) == 0);
}

void initialize() {
    // Initialize GLFW
    if (!glfwInit()) {
        throw runtime_error("Failed to initialize GLFW\n");
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow(W_WIDTH, W_HEIGHT, TITLE, NULL, NULL);
    if (window == NULL) {
        glfwTerminate();
        throw runtime_error(string(string("Failed to open GLFW window.") +
            " If you have an Intel GPU, they are not 3.3 compatible." +
            "Try the 2.1 version.\n"));
    }
    glfwMakeContextCurrent(window);

    // Start GLEW extension handler
    glewExperimental = GL_TRUE;

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        throw runtime_error("Failed to initialize GLEW\n");
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Gray background color
    glClearColor(0.5f, 0.5f, 0.5f, 0.0f);

    // Task 12: Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // Log
    logGLParameters();
}