#include <GLFW/glfw3.h>
#include <iostream>


int main(int argc, char* argv[]){

	GLFWwindow* window;
	if(!glfwInit()){
		std::cout << "Colun not init glfw! " << std::endl;
		return -1;
	}
	window = glfwCreateWindow(6640,480, "Hello World",NULL,NULL );

	glfwMakeContextCurrent(window);

	while(!glfwWindowShouldClose(window)){
		glfwWaitEvents();
	}

	
	return 0;
}
