#include <glad.h>
#include <GLFW/glfw3.h>
#include <util.h>
#include <iostream>


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void render(GLFWwindow *window, int VAO);
void get_rectangle_vao(unsigned int *VAO, unsigned int * VBO, unsigned int *EBO, unsigned int vertex_attrib_index);

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\n\0";

int main()
{
    GLFWwindow *window = init_window_context(SCR_WIDTH, SCR_HEIGHT, "My Window");
    if( window == NULL) {
        return -1; // some problem in initializing window
    }

    int vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderSource);
    int fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    int shaderProgram = create_program(2, vertexShader, fragmentShader);

    unsigned int VBO, VAO, EBO;
    const unsigned int vertex_attrib_index = 0;
    get_rectangle_vao(&VAO, &VBO, &EBO, vertex_attrib_index);
    glEnableVertexAttribArray(vertex_attrib_index);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glUseProgram(shaderProgram);
    render(window, VAO);

    clean_up(&VAO, &VBO, &EBO);
    glfwTerminate();
    return 0;
}

void get_rectangle_vao(unsigned int *VAO, unsigned int * VBO, unsigned int *EBO, unsigned int vertex_attrib_index) {
    float vertices[] = {
        0.5f, 0.5f, 0.0f,   // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f,   // top right
        -0.5f, -0.5f, 0.0f,  // bottom right
        0.0f, 0.0f, 0.0f
    };

    unsigned int indices[] = {
        // note that we start from 0!
        0, 1, 2,
        3, 4, 5
    };

    glGenVertexArrays(1, VAO);
    glGenBuffers(1, VBO);
    glGenBuffers(1, EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(*VAO);

    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(vertex_attrib_index, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
}

void render(GLFWwindow *window, int VAO) {
    while (!glfwWindowShouldClose(window)) {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

     
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glBindVertexArray(0); // no need to unbind it every time

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
