#include <stdio.h>
#include <windows.h>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

class Application
{
public:
    ~Application();
    static Application* getInstance();
private:
    static Application* mInstance;
    Application();


};