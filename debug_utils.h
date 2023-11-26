#ifndef MY_DEBUG_UTILS_H
#define MY_DEBUG_UTILS_H


#define DEBUG
#define SDL_DEBUG


#ifdef DEBUG
#define debug_print(...) \
        do { fprintf(stderr, "Error in %s() [%s #%i]", __func__, __FILE__, __LINE__);\
             fprintf(stderr, ": " __VA_ARGS__);\
             fprintf(stderr, "\n"); } while (0)

#define debug_var_print(fmt, var)\
        do { fprintf(stderr, "In %s() [%s #%i]", __func__, __FILE__, __LINE__);\
             fprintf(stderr, ": " #var " = " fmt "\n", var);} while (0)
#else
#define debug_print(...) ((void)0)
#define debug_var_print(fmt, var) ((void)0)
#endif /* Debug */


#ifdef SDL_DEBUG
#define sdl_debug_print(...) \
	do { fprintf(stderr, "Error in %s() [%s #%i]\nSDL_Error: %s\n", \
		     __func__, __FILE__, __LINE__-1, SDL_GetError()); \
	     fprintf(stderr, ": " __VA_ARGS__);\
             fprintf(stderr, "\n");\
	     SDL_ClearError(); } while (0)
#else
#define sdl_debug_print(FMT, ...) ((void)0)
#endif /*SDL_DEBUG*/


#endif /*MY_DEBUG_UTILS_H*/
