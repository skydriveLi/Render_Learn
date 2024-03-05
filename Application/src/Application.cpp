#include "Application/Application.hpp"


Application::Application()
{

}
Application::~Application()
{

}

// void framebuffer_size_callback(GLFWwindow* window, int width, int height)
// {
//     printf("framebuffer_size_callback %d %d \n",width,height);
//     glViewport(0,0,width,height);
// }

// void keyboard_callback(GLFWwindow* window, int key,int scancode,int action,int modes)
// {
//     //key 字母按键
//     //scancode 物理按键
//     //action 按下还是抬起
//     //mods 是否有shift ctrl
//     printf("key_callback %5d %5d %5d %5d \n",key,scancode,action,modes);
// }

// void gl_error_check()
// {        
//     //检查错误
//     GLenum errorCode = glGetError();
//     if(errorCode!=GL_NO_ERROR)
//     {
//         printf("GL_ERROR_CODE: %#X\n",errorCode);
//     }

// }



// int main()
// {
//     printf("Hello OpenGL!\n");
    
//     glfwInit();
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,6);
//     glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

//     GLFWwindow* window = glfwCreateWindow(800,600,"Hello OpenGL!",NULL,NULL);
//     glfwMakeContextCurrent(window);
    
//     //设置事件回调
//     glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//     glfwSetKeyCallback(window, keyboard_callback);


//     if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
//         printf("gladLoadGLLoader FAIL!\n");
//     }   printf("gladLoadGLLoader SUCCEEDED\n");

//     // 设置opengl视口大小 清理颜色
//     glViewport(0,0,800,600);
//     glClearColor(0.7,0.9,0.9,1);
    
//     while(!glfwWindowShouldClose(window))
//     {
//         glfwPollEvents();

//         gl_error_check();
//         // 执行清理
//         glClear(GL_COLOR_BUFFER_BIT);



//         //渲染操作

//         //切换双缓存
//         glfwSwapBuffers(window);


//     }

//     glfwTerminate();
//     return 0;
// }

