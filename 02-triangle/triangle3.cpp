#include <glad.h>
#include <GLFW/glfw3.h>
#include <util.h>


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void render(GLFWwindow *window, unsigned int* VAOs);
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

    if(vertexShader == -1 || fragmentShader == -1 || shaderProgram == -1) {
        
        return -1;
    }
   
     float firstTriangle[] = {
        -0.9f, -0.5f, 0.0f,  // left 
        -0.0f, -0.5f, 0.0f,  // right
        -0.45f, 0.5f, 0.0f,  // top 
    };
    float secondTriangle[] = {
        0.0f, -0.5f, 0.0f,  // left
        0.9f, -0.5f, 0.0f,  // right
        0.45f, 0.5f, 0.0f   // top 
    };

    unsigned int indices[] = {
        // note that we start from 0!
        0, 1, 2
    };

    unsigned int indices2[] = {
        // note that we start from 0!
        0, 1, 2
    };
    unsigned int VBOs[2], VAOs[2], EBOs[2];
    glGenVertexArrays(2, VAOs); // we can also generate multiple VAOs or buffers at the same time
    glGenBuffers(2, VBOs);
    glGenBuffers(2, EBOs);
    // first triangle setup
    // --------------------
    glBindVertexArray(VAOs[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Vertex attributes stay the same
    glEnableVertexAttribArray(0);

    // second triangle setup
    // ---------------------
    glBindVertexArray(VAOs[1]);	// note that we bind to a different VAO now
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);	// and a different VBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
    
    glEnableVertexAttribArray(0); //location zero

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glUseProgram(shaderProgram);
    render(window, VAOs);

    clean_up(&VAOs[0], &VBOs[0], &EBOs[0]);
    clean_up(&VAOs[1], &VBOs[1], &EBOs[1]);
    glfwTerminate();
    return 0;
}


void render(GLFWwindow *window, unsigned int* VAOs) {
    while (!glfwWindowShouldClose(window)) {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // then we draw the second triangle using the data from the second VAO
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
