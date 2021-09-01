#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

// 监听窗口改变
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // 根据我们系统，找到正确的函数
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    // 视口:告诉OpenGL渲染窗口大小(左上角，宽和高)
    // 注意：OpenGL坐标范围(-1,1),则需要将(-1,1) 映射到(0,800)到(0,600)
    glViewport(0, 0, 800, 600);

    // 窗口改变后，视口也会跟着变化，则进行callback，动态改变viewport
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Shader ourShader("./shader.vs", "./shader.fs");

    /**set up vertex data(buffer) and configure vertex attibutes***/
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
    };

    // 1.创建对象
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // 2.绑定对象,有很多缓冲对象，顶点对象缓冲类型是GL_ARRAY_BUFFER
    // bind the Vertex Array Object first
    // then bind and set vertex buffers
    // and then configure vertex attributes
    glBindVertexArray(VAO);// 这个可以讲vertex array相关内容存在这个对象中

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    // 让位置0，顶点属性使能
    glEnableVertexAttribArray(0);

    // note that this is allowed, then call to glVertexAttributePointer registered VBO as the the vertex attribute's bound
    // vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as
    // the bound element buffer object IS stored in the VAO;
    // keep the EBO bound
    // glBinderBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // you can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO
    // but this rarely happend
    // Modify other VAOs requires a call to glBindVertexArray anyways so 
    // we generally don't unbind VAOs don't unbind VAOs(nor VBOs)
    // when it's not directly necessary
    glBindVertexArray(0);

    // uncomment this call to draw in wireframe polygons
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // 渲染循环Rendor Loop,不退出一直保持运行
    //    每次循环检查GLFW是否退出
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        /****************渲染指令*******************/
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); 
        // glClearColor设置空屏所用的颜色,glClear之后就是这个函数设置的颜色
        glClear(GL_COLOR_BUFFER_BIT);

        ourShader.use();

        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        /***********************************/
        // 交换颜色缓冲
        glfwSwapBuffers(window);
        // 检查触发事件(键盘，鼠标，更新窗口状态)
        glfwPollEvents();
    }

    // 释放所有资源
    glfwTerminate();

    return 0;
}
