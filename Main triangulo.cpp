#include<iostream> 
#include<glad/glad.h> 
#include<GLFW/glfw3.h>

//-------------------------------vertex shader-------------------------------
//trabaja la posición de cada vértice
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"  gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//-------------------------------fragment shader-------------------------------
//decide el color de los píxeles
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor; \n"
"void main()\n"
"{\n"
"  FragColor = vec4(0.8f, 0.3, 0.02f, 1.0f);\n"
"}\n\0";

int main()
{
	// initializar GLFW para poder crear la ventana
	glfwInit();

	//GLFW 3.5.1 de OPEN GL se usa
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// utiliza las funciones modernas de opengl
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// -----------------------crea la ventana----------------------------
	GLFWwindow* window = glfwCreateWindow(800, 800, "Project1", NULL, NULL);
	// si window es NULL significa que la ventana no pudo crearse
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// -----------------------activa ventana-------------------------
	glfwMakeContextCurrent(window);

	gladLoadGL();
	// configurar el viewport , comienza en x y = 0 termina enen x y = 800 
	glViewport(0, 0, 800, 800);

	// ------------------crea el vertex shader----------------------
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

	glCompileShader(vertexShader);
	// --------------------crea el fragment shader------------------
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// crea un programa que va une dos shaders
	GLuint shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// unimos los dos shaders forman un único programa
	glLinkProgram(shaderProgram);

	// eliminar shaders que ya no necesitamos
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//----------------------- crear los vértices del triángulo---------------------
	// coordenadas de los tres vértices
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // vértice inferior izquierdo
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // vértice inferior derecho
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // vértice superior
	};
	// ------------------------------crea vao y vbo-------------------------
	// Create reference containers for the Vartex Array Object and the Vertex Buffer Object
	GLuint VAO, VBO;

	// genera un vao y un vbo
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// activar el vao
	glBindVertexArray(VAO);

	// Bind the VBO specifying it's a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// envia los vértices a la gpu
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// configura los atributos de los vértices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// Main while loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	
		glfwSwapBuffers(window);
		
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
