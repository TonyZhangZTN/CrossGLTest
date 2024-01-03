#include <SDL2/SDL.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
EGLDisplay eglDisplay;
EGLSurface eglSurface;
EGLContext eglContext;

void renderTriangle() {
    // Define vertices for a triangle
    GLfloat vertices[] = {
        0.0f,  0.5f, 0.0f,
       -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };

    glViewport(0, 0, 800,600);
    glClearColor(0.5f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint vertexArray;
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glFlush();
}

void cleanup() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    eglMakeCurrent(eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglDestroyContext(eglDisplay, eglContext);
    eglDestroySurface(eglDisplay, eglSurface);
    eglTerminate(eglDisplay);
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }

    // Create an SDL window
    int window_width, window_height;
    SDL_GetWindowSize(window, &window_width, &window_height);
    printf("Window size=%dx%d\n",window_width,window_height);
    window = SDL_CreateWindow("OpenGL ES 2.0 Triangle", 0, 0, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if (!window) {
        fprintf(stderr, "Window creation failed: %s\n", SDL_GetError());
        cleanup();
        return 1;
    }

    // Initialize EGL
    eglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(eglDisplay, NULL, NULL);

    // Set EGL attributes
    eglBindAPI(EGL_OPENGL_ES_API);
    EGLConfig eglConfig;
    EGLint numConfigs;
    const EGLint configAttribs[] = {
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_ALPHA_SIZE, 8,
        EGL_NONE
    };
    eglChooseConfig(eglDisplay, configAttribs, &eglConfig, 1, &numConfigs);

    // Create an EGL surface
    eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, (EGLNativeWindowType)window, NULL);
    eglContext = eglCreateContext(eglDisplay, eglConfig, EGL_NO_CONTEXT, NULL);
    eglMakeCurrent(eglDisplay, eglSurface, eglSurface, eglContext);

    // Initialize GLES
    glClearColor(.5f, 0.0f, 0.0f, 1.0f);

    // Main loop
    SDL_Event event;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_q) {
                    quit = 1;
                }
            }
        }

        renderTriangle();

        eglSwapBuffers(eglDisplay, eglSurface);
    }

    cleanup();
    return 0;
}

