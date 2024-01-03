#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL2/SDL_opengl.h>
int main()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
	//if (SDL_VideoInit("KMSDRM") < 0) {
        printf("[Fatal]SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }
	//SDL_Log("SDL initialized successfully!\n");
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_EGL, 1);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_Window *window = SDL_CreateWindow("SDL OpenGL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640,480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, context);
	//printf("OpenGL version: %s\nGLSL:%s\n" , (const char *)glGetString(GL_VERSION),(const char *)glGetString(GL_SHADING_LANGUAGE_VERSION));

/*
	// Following is simple blit render
	SDL_Window *window = NULL;

    //The surface contained by the window
    SDL_Surface *screenSurface = NULL;
	int nNumDiaplays = SDL_GetNumVideoDisplays();
    SDL_Rect rectDisplay;
    SDL_GetDisplayBounds(0, &rectDisplay);

    printf("[Display]" "number of Displays%d,width:%d,height:%d", nNumDiaplays, rectDisplay.w,
         rectDisplay.h);
    //Create window
    window = SDL_CreateWindow("Meta-Terminal-X", 0, 0, rectDisplay.w, rectDisplay.h,
                              SDL_WINDOW_SHOWN);
    if (window == NULL) {
        SDL_Log("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }
    //Get window surface
    screenSurface = SDL_GetWindowSurface(window);

    //Fill the surface white
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x66, 0xCC, 0xFF));
    //Update the surface
    SDL_UpdateWindowSurface(window);
	*/
    bool quit = false;
    SDL_Event e;

    bool running = true;
    unsigned char i = 0;
	glClearColor(0.9f, 0.3f, 0.9f, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);
	glClearColor(0.9f, 0.3f, 0.9f, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);
    while( running )
    {
        SDL_Event ev;
        while( SDL_PollEvent( &ev ) )
        {
            if( ( ev.type == SDL_QUIT ) ||
                ( ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_ESCAPE ) )
            {
                running = false;
            }
        }
		glClearColor(0.9f, 0.3f, 0.9f, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
