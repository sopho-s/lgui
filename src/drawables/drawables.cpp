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
            this->vertices[0] = p1.x;
            this->vertices[1] = p1.y;
            this->vertices[2] = p2.x;
            this->vertices[3] = p2.y;
            this->vertices[4] = p3.x;
            this->vertices[5] = p3.y;
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
            glUseProgram(shaderProgram);
            glBindVertexArray(VAO);
            int colorLocation = glGetUniformLocation(shaderProgram, "triColour");
            glUniform4f(colorLocation, this->colour.r, this->colour.g, this->colour.b, this->colour.a);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }

        void lQuad::init() {
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
            this->vertices1[0] = p1.x;
            this->vertices1[1] = p1.y;
            this->vertices1[2] = p2.x;
            this->vertices1[3] = p2.y;
            this->vertices1[4] = p3.x;
            this->vertices1[5] = p3.y;
            this->vertices2[0] = p3.x;
            this->vertices2[1] = p3.y;
            this->vertices2[2] = p4.x;
            this->vertices2[3] = p4.y;
            this->vertices2[4] = p1.x;
            this->vertices2[5] = p1.y;
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
            glGenVertexArrays(1, &VAO2);
            glGenBuffers(1, &VBO2);
            glBindVertexArray(VAO2);
            glBindBuffer(GL_ARRAY_BUFFER, VBO2);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);
        }

        void lQuad::draw() {
            this->vertices1[0] = p1.x;
            this->vertices1[1] = p1.y;
            this->vertices1[2] = p2.x;
            this->vertices1[3] = p2.y;
            this->vertices1[4] = p3.x;
            this->vertices1[5] = p3.y;
            this->vertices2[0] = p3.x;
            this->vertices2[1] = p3.y;
            this->vertices2[2] = p4.x;
            this->vertices2[3] = p4.y;
            this->vertices2[4] = p1.x;
            this->vertices2[5] = p1.y;
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
            glUseProgram(shaderProgram);
            glBindVertexArray(VAO);
            int colorLocation = glGetUniformLocation(shaderProgram, "triColour");
            glUniform4f(colorLocation, 1, 1, 0, 1.0f);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
            glBindVertexArray(VAO2);
            glBindBuffer(GL_ARRAY_BUFFER, VBO2);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }

        void lCircle::draw() {
        }

        void lText::draw() {
        }

        void lPNGImage::draw() {
        }
    }
}