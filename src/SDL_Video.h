#ifndef SDL_VIDEO_H__
#define SDL_VIDEO_H__

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 544

typedef struct SDLVideo_s
{
	SDL_Window* window;
	SDL_Renderer* renderer;
	int rendererW;
	int rendererH;
	boolean fullScreen;
	boolean vSync;
	boolean integerScaling;
	boolean displaySoftKeys;
	int resolutionIndex;
} SDLVideo_t;

extern SDLVideo_t sdlVideo;

void SDL_InitVideo(void);
void SDL_Close(void);
SDLVideo_t* SDL_GetVideo(void);
void SDL_RenderDrawFillCircle(SDL_Renderer* renderer, int x, int y, int r);
void SDL_RenderDrawCircle(SDL_Renderer* renderer, int x, int y, int r);

//-----
typedef struct SDLController_s
{
	//Game controller handler with force feedback
	SDL_GameController* gGameController;

	//Joystick handler with haptic
	SDL_Joystick* gJoystick;
	SDL_Haptic* gJoyHaptic;
	int deadZoneLeft;
	int deadZoneRight;
} SDLController_t;

extern SDLController_t sdlController;

typedef struct SDLVidModes_s
{
	int width, height;
} SDLVidModes_t;

extern SDLVidModes_t sdlVideoModes[10];

//Analog joystick dead zone
#define JOYSTICK_DEAD_ZONE 8000
int SDL_GameControllerGetButtonID(void);
char* SDL_GameControllerGetNameButton(int id);

char* SDL_MouseGetNameButton(int id);
char* SDL_TouchGetName(int id);

int SDL_JoystickGetButtonID(void);

#endif
