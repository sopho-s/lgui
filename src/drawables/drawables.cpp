#include "drawables.h"
namespace lgui {
    namespace drawables {
        void lTriangle::init() {
            unsigned int vertexShader, fragmentShader;
            int success;
            char infoLog[512];
            vertexShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
            glCompileShader(vertexShader);
            glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
                fprintf(stderr, "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
            }
            fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
            glCompileShader(fragmentShader);
            glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
                fprintf(stderr, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
            }
            
            shaderProgram = glCreateProgram();
            glAttachShader(shaderProgram, vertexShader);
            glAttachShader(shaderProgram, fragmentShader);
            glLinkProgram(shaderProgram);
            glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
                fprintf(stderr, "ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", infoLog);
            }
            this->vertices[0] = p1.x;
            this->vertices[1] = p1.y;
            this->vertices[2] = p2.x;
            this->vertices[3] = p2.y;
            this->vertices[4] = p3.x;
            this->vertices[5] = p3.y;
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

        }

        void lTriangle::draw() {

            float red = (sin(timetest * 0.3) * 0.5f) + 0.5f;  // Vary red over time
            float green = (cos(timetest * 0.5) * 0.5f) + 0.5f; // Vary green over time
            float blue = (sin(timetest) * 0.7) + 0.5f; // Vary green over time
            timetest += 0.1f;
            glUseProgram(shaderProgram);
            glBindVertexArray(VAO);
            int colorLocation = glGetUniformLocation(shaderProgram, "triColour");
            glUniform4f(colorLocation, red, green, blue, 1.0f);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            //printf("Drawing triangle\n");
        }

        void lRectangle::draw() {
        }

        void lCircle::draw() {
        }

        void lText::draw() {
        }

        void lPNGImage::draw() {
        }
    }
}