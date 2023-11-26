#include "Application.h"
#include "debug_utils.h"


SDL_Window *Application::window = nullptr;
SDL_Renderer *Application::renderer = nullptr;
int Application::window_width = -1;
int Application::window_height = -1;

static void init_window(const char *title, int width, int height, uint32_t flags);
static void init_renderer(uint32_t flags);
static void init_video();
static void init_img();


void Application::init(const std::string &title, 
			int width, 
			int height, 
			uint32_t wflags,
			uint32_t rflags)
{
	Application::window_width = width;
	Application::window_height = height;
	
	init_video();
	init_window(title.c_str(), width, height, wflags);
	init_renderer(rflags);
	init_img();
}


void Application::exit()
{
	SDL_DestroyWindow(Application::window);
	SDL_DestroyRenderer(Application::renderer);
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}


static void init_window(const char *title,
				int width,
				int height,
				uint32_t flags)
{
	Application::window = SDL_CreateWindow(title,
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				width,
				height,
				flags);
				
	if(Application::window == nullptr) {
		sdl_debug_print("");
		exit(EXIT_FAILURE);
	}
}


static void init_renderer(uint32_t flags)
{
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	Application::renderer = SDL_CreateRenderer(Application::window, -1, flags);
	if(Application::renderer == nullptr) {
		sdl_debug_print("");
		exit(EXIT_FAILURE);
	}
}

static void init_img()
{
	int res = IMG_Init(IMG_INIT_PNG);
	if(res == 0) {
		sdl_debug_print("");
		exit(EXIT_FAILURE);
	}
}


static void init_video()
{
	int res = SDL_InitSubSystem(SDL_INIT_VIDEO);
	if(res < 0) {
		sdl_debug_print("");
		exit(EXIT_FAILURE);
	}
}
