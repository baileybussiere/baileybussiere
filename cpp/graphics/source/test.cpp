//#define GLFW_INCLUDE_VULKAN
//#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <iostream>
#include <stdexcept>
#include <functional>
#include <cstdlib>

const int WIDTH = 800;
const int HEIGHT = 600;

class HelloApp
{
    public:
    	void run()
    	{
    		//initWindow();
		initGraphics();
		mainLoop();
		cleanup();
    	}

    private:
    	//GLFWwindow* window;

	void initWindow()
	{/*
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		window = glfwCreateWindow(WIDTH, HEIGHT, "Hello", nullptr, nullptr);
	*/}

    	void initGraphics()
    	{
    	}

    	void mainLoop()
    	{/*
    		while (!glfwWindowShouldClose(window))
    		{
    			glfwPollEvents();
    		}
    	*/}

    	void cleanup()
    	{/*
    		glfwDestroyWindow(window);
    		glfwTerminate();
    	*/}
};

int main()
{
	HelloApp app;

	try
	{
		app.run();
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
