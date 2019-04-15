#include <glad.h>
#include <GLFW/glfw3.h>
#include <util.h>
#include <cmath>


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void render(GLFWwindow *window, unsigned int* VAOs);

int main()
{
    GLFWwindow *window = init_window_context(SCR_WIDTH, SCR_HEIGHT, "My Window");
    if( window == NULL) {
        return -1; // some problem in initializing window
    }

    int shader_program = create_program_from_files("vertex6.vs", "fragment6.fs");

     float firstTriangle[] = {
        -0.9f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // left 
        -0.0f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // right
        -0.45f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f // top 
    };
    float secondTriangle[] = {
        0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // left
        0.9f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // right
        0.45f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f // top 
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

    //vertex attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    // second triangle setup
    // ---------------------
    glBindVertexArray(VAOs[1]);	// note that we bind to a different VAO now
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);	// and a different VBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);
        //vertex attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glUseProgram(shader_program);
    float offset = 0.5f;
    glUniform1f(glGetUniformLocation(shader_program, "xOffset"), offset);

    while (!glfwWindowShouldClose(window)) {
        // input
        // -----
        processInput(window);

        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shader_program, "ourColor");
        glUseProgram(shader_program);
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

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

    clean_up(&VAOs[0], &VBOs[0], &EBOs[0]);
    clean_up(&VAOs[1], &VBOs[1], &EBOs[1]);
    glfwTerminate();
    return 0;
}

