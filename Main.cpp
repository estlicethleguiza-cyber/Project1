#include<iostream> 
#include<glad/glad.h> 
#include<GLFW/glfw3.h>

int main()
{
	//Inicializar Glfw
	glfwInit();
	//GLFW  3.5.1 de OPEN GL se usa
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//crea un objeto GLFWwindow de 800 por 800 píxeles, nombrado Project1
	GLFWwindow* window = glfwCreateWindow(800, 800, "Project1", NULL, NULL);
	//comprobación de error si la ventana no se crea
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);


	//carga GLAD para que configure OpenGL
	gladLoadGL();


	glViewport(0, 0, 800, 800);
	//color de fondo
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	//limpia el búfer de fondo y asígna el nuevo color
	glClear(GL_COLOR_BUFFER_BIT);
	//intercambia el búfer trasero con el búfer delantero.
	glfwSwapBuffers(window);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}
	//elimina la ventana antes de finalizar el programa
	glfwDestroyWindow(window);
	//Finaliza GLFW antes de terminar el programa.
	glfwTerminate();
	return 0;

}
