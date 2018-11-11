
#include <GL/glew.h>
#include <gl/freeglut.h>

#include <iostream>
#include <cmath>

#include <src/shader.cpp>

// settings
class Manager {
private:
	// shader object
	Shader shader;

	// buffers
	GLuint VBO, VAO;

	// temp vert obj
	float vertices[9] = {
         0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
         0.0f,  0.5f, 0.0f   // top 
    };

    const unsigned int SCR_WIDTH = 800;
	const unsigned int SCR_HEIGHT = 600;

public:
	// CONSTRUCTOR
	Manager(int argc, char** argv) {

		// init GLUT and create Window
		glutInit(&argc, argv);
		glutInitContextVersion(3,3); // init to OpenGL v 3.3 
		glutInitContextProfile(GLUT_CORE_PROFILE); // Set up to core profile
		glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
		glutInitWindowPosition(100,100);
		glutInitWindowSize(SCR_WIDTH, SCR_HEIGHT);
		glutCreateWindow("Lighthouse3D - GLUT Tutorial");

		// init GLEW
		glewInit();

		// init shader
		shader.init("src/shader.vert","src/shader.frag");
		// use the shader object
		shader.use();

	    // INIT BUFFERS
	    glGenVertexArrays(1, &VAO);
	    glGenBuffers(1, &VBO);
	    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	    glBindVertexArray(VAO);

	    glBindBuffer(GL_ARRAY_BUFFER, VBO);
	    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	    glEnableVertexAttribArray(0);

	    glBindVertexArray(VAO);
	}

	// DESTRUCTOR
	~Manager() {
		// optional: de-allocate all resources once they've outlived their purpose:
	    // ------------------------------------------------------------------------
	    glDeleteVertexArrays(1, &VAO);
	    glDeleteBuffers(1, &VBO);
	}

	// RENDER INSTRUCTIONS
	void renderScene(void) {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// glBegin(GL_TRIANGLES);
		// 	glVertex3f(-0.5,-0.5,0.0);
		// 	glVertex3f(0.5,0.0,0.0);
		// 	glVertex3f(0.0,0.5,0.0);
		// glEnd();

		// update shader uniform
		float timeValue = glutGet(GLUT_ELAPSED_TIME);
		float blueValue = sin(timeValue/1000) / 2.0f + 0.5f;
		shader.setFloat("ourColor", blueValue);

		// render the triangle
        glDrawArrays(GL_TRIANGLES, 0, 3);

		glutSwapBuffers();
	}
};



int main(int argc, char **argv) {

	Manager manager(argc, argv);	

	// register callbacks
	// glutDisplayFunc(manager.renderScene);

	// enter GLUT event processing cycle
	// glutMainLoop();

	while(1==1) {
		glutMainLoopEvent();
		manager.renderScene();
	}
	
	return 0;
}