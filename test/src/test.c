#include "test/test.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    printf("framebuffer_size_callback %d %d \n",width,height);
    glViewport(0,0,width,height);
}

void keyboard_callback(GLFWwindow* window, int key,int scancode,int action,int modes)
{
    //key 字母按键
    //scancode 物理按键
    //action 按下还是抬起
    //mods 是否有shift ctrl
    printf("key_callback %5d %5d %5d %5d \n",key,scancode,action,modes);
}

void gl_error_check()
{        
    //检查错误
    GLenum errorCode = glGetError();
    if(errorCode!=GL_NO_ERROR)
    {
        printf("GL_ERROR_CODE: %#X\n",errorCode);
    }

}

    // GLuint vboArr[3]={0,0,0};
    // glGenBuffers(3,vboArr);
    // glDeleteBuffers(3,vboArr);

void vao_vbo_prepare_Single()
{        

    //单独存储
    float position[]={  -0.5f,-0.5f,0.0f,
                        +0.5f,-0.5f,0.0f,
                        +0.0f,+0.5f,0.0f};
    float color[]={ 1.0f,0.0f,0.0f,
                    0.0f,1.0f,0.0f,
                    0.0f,0.0f,1.0f};
    GLuint vbo_pos=0;
    GLuint vbo_col=0;
    glGenBuffers(1,&vbo_pos);
    glGenBuffers(1,&vbo_col);
    //GL_ARRAY_BUFFER表示当前vbo插槽
    glBindBuffer(GL_ARRAY_BUFFER,vbo_pos);
    glBufferData(GL_ARRAY_BUFFER,sizeof(position),position,GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,vbo_col);
    glBufferData(GL_ARRAY_BUFFER,sizeof(color),color,GL_STATIC_DRAW);

    GLuint vao=0;
    glGenVertexArrays(1,&vao);
    glBindVertexArray(vao);
    //向vao中绑定位置信息
    glBindBuffer(GL_ARRAY_BUFFER,vbo_pos);
    glEnableVertexAttribArray(0);//设置这个VAO的第0位信息
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
    //向vao中绑定颜色信息
    glBindBuffer(GL_ARRAY_BUFFER,vbo_col);
    glEnableVertexAttribArray(1);//设置这个VAO的第1位信息
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);

    //vao解绑
    glBindVertexArray(0);
    
    //释放对应的显存空间
    // glDeleteBuffers(1,&vbo_pos);
    // glDeleteBuffers(1,&vbo_col);
}

void vao_vbo_prepare_InterLeaced()
{        
    //交叉存储
    float position_color[]={-0.5f,-0.5f,0.0f, 1.0f,0.0f,0.0f,
                            +0.5f,-0.5f,0.0f, 0.0f,1.0f,0.0f,
                            +0.0f,+0.5f,0.0f, 0.0f,0.0f,1.0f };
    GLuint vbo_poscol=0;
    glGenBuffers(1,&vbo_poscol);
    glBindBuffer(GL_ARRAY_BUFFER,vbo_poscol);
    glBufferData(GL_ARRAY_BUFFER,sizeof(position_color),position_color,GL_STATIC_DRAW);

    GLuint vao_poscol=0;
    glGenVertexArrays(1,&vao_poscol);
    glBindVertexArray(vao_poscol);
    
    glBindBuffer(GL_ARRAY_BUFFER,vbo_poscol);
    //向vao中绑定位置信息
    glEnableVertexAttribArray(0);//设置这个VAO的第0位信息
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
    //向vao中绑定颜色信息
    glEnableVertexAttribArray(1);//设置这个VAO的第1位信息
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)) );

    //vao解绑
    glBindVertexArray(0);

    //释放对应的显存空间
    // glDeleteBuffers(1,&vbo_poscol);
}

void prepare_Shader()
{
    //shader源码
    const char* vertexShaderSource=
        "#version 460 core\n"
        "layout (location=0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "    gl_Position=vec4(aPos.x,aPos.y,aPos.z,1.0f);\n"
        "}\n\0";
    const char* fragmentShaderSource=
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor=vec4(1.0f,0.5f,0.2f,1.0f);\n"
        "}\n\0";
    //创建shader程序
    GLuint vertex,fragment;
    vertex= glCreateShader(GL_VERTEX_SHADER);
    fragment= glCreateShader(GL_FRAGMENT_SHADER);
    //shader源码-->>shader程序
    glShaderSource(vertex,1,&vertexShaderSource,NULL);
    glShaderSource(fragment,1,&fragmentShaderSource,NULL);
    //编译shader程序和错误检查
    int compile_success=0;
    char infoLog[1024];
    glCompileShader(vertex);//编译shader程序
    glGetShaderiv(vertex,GL_COMPILE_STATUS,&compile_success);//编译错误检查
    if(!compile_success){
        glGetShaderInfoLog(vertex,1024,NULL,infoLog);
        printf("vertex compile_infoLog: %d\n%s\n",compile_success,infoLog);
    }
    glCompileShader(fragment);//编译shader程序
    glGetShaderiv(fragment,GL_COMPILE_STATUS,&compile_success);//编译错误检查
    if(!compile_success){
        glGetShaderInfoLog(vertex,1024,NULL,infoLog);
        printf("compile_infoLog: %d \n %s \n",compile_success,infoLog);
    }

    //创建program
    GLuint program=0;
    program=glCreateProgram();
    //设置放入program的编译结果
    glAttachShader(program,vertex);
    glAttachShader(program,fragment);
    //将编译结果放入program
    glLinkProgram(program);
    //链接错误检查
    int link_success=0;
    glGetProgramiv(program,GL_LINK_STATUS,&link_success);
    if(!link_success){
        glGetProgramInfoLog(program,1024,NULL,infoLog);
        printf("link_infoLog: %d \n %s \n",link_success,infoLog);
    }

    //释放shader程序
    glDeleteShader(vertex);
    glDeleteShader(fragment);



}

int main()
{
    printf("Hello OpenGL!\n");
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,6);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800,600,"Hello OpenGL!",NULL,NULL);
    glfwMakeContextCurrent(window);





    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        printf("gladLoadGLLoader FAIL!\n");
    }   printf("gladLoadGLLoader SUCCEEDED\n");

    vao_vbo_prepare_Single();
    vao_vbo_prepare_InterLeaced();
    prepare_Shader();

    //设置事件回调
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, keyboard_callback);

    // 设置opengl视口大小 清理颜色
    glViewport(0,0,800,600);
    glClearColor(0.7,0.9,0.9,1);
    
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        gl_error_check();
        

        // 执行清理
        glClear(GL_COLOR_BUFFER_BIT);





        //渲染操作

        //切换双缓存
        glfwSwapBuffers(window);


    }

    glfwTerminate();
    printf("SeeYou OpenGL!\n");
    return 0;
}

