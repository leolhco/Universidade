#include "canvas.h"
#include "vec.h"
#include "mat.h"
#include "camera.h"
#include "mesh.h"
#include "obj.h"
#include "shader.h"
#include "program.h"
#include "render_util.h"
#include "game.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <SDL2/SDL.h>

#define WIDTH  1100
#define HEIGHT 750
#define TITLE  "Snake 3D"
#define SHININESS 25

/* ---- OBJ -> Mesh ---- */

static void load_cube_mesh(Mesh *mesh, const char *path)
{
	FILE *file = fopen(path, "r");
	if (!file) {
		fprintf(stderr, "error: could not open %s\n", path);
		exit(1);
	}

	ObjModel obj;
	obj_scan(&obj, file);
	obj_alloc(&obj);
	rewind(file);
	obj_parse(&obj, file);
	fclose(file);

	mesh->num_vertices = obj.num_vertices;
	mesh->num_normals  = obj.num_normals;
	mesh->num_faces    = obj.num_faces;
	mesh->vertices = malloc(sizeof(Vec3) * mesh->num_vertices);
	mesh->normals  = malloc(sizeof(Vec3) * mesh->num_normals);
	mesh->faces    = malloc(sizeof(Face) * mesh->num_faces);

	for (int i = 0; i < obj.num_vertices; i++)
		mesh->vertices[i] = (Vec3){ obj.vertices[i].x, obj.vertices[i].y, obj.vertices[i].z };
	for (int i = 0; i < obj.num_normals; i++)
		mesh->normals[i] = (Vec3){ obj.normals[i].x, obj.normals[i].y, obj.normals[i].z };
	for (int i = 0; i < obj.num_faces; i++) {
		memcpy(mesh->faces[i].vertex_indices, obj.faces[i].vertex_indices, sizeof(int) * 3);
		memcpy(mesh->faces[i].normal_indices, obj.faces[i].normal_indices, sizeof(int) * 3);
	}

	obj_free(&obj);
}

/* ---- SDL ---- */

static SDL_Window  *window;
static SDL_Surface *window_surface;
static SDL_Surface *surface;

static void sdl_init(void)
{
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow(TITLE,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	window_surface = SDL_GetWindowSurface(window);
	surface = SDL_CreateRGBSurfaceWithFormat(0, WIDTH, HEIGHT, 32, SDL_PIXELFORMAT_RGBX8888);
}

static void sdl_present(void)
{
	SDL_BlitSurface(surface, 0, window_surface, 0);
	SDL_UpdateWindowSurface(window);
}

static void update_title(Game *g)
{
	char buf[128];
	if (g->state == GAME_OVER)
		snprintf(buf, sizeof(buf), "%s  |  Game Over  -  Score: %d  -  R to restart", TITLE, g->score);
	else
		snprintf(buf, sizeof(buf), "%s  |  Score: %d", TITLE, g->score);
	SDL_SetWindowTitle(window, buf);
}

int main(void)
{
	/* Shared cube mesh: every segment, the apple, the floor and walls use it. */
	Mesh cube;
	load_cube_mesh(&cube, "cube.obj");

	/* Specular lookup table for the Phong shader. */
	float specular_lut[256];
	for (int i = 0; i < 256; i++)
		specular_lut[i] = powf(i / 255.0f, SHININESS);

	sdl_init();

	Canvas canvas;
	canvas_init(&canvas, (uint32_t *)surface->pixels, WIDTH, HEIGHT);
	float *z_buffer = calloc(WIDTH * HEIGHT, sizeof(float));

	Renderer renderer;
	renderer_init(&renderer, &canvas, z_buffer, viewport(0, 0, WIDTH, HEIGHT));

	/* Fixed, slightly tilted top-down camera. Never moved after this. */
	Camera camera;
	camera_init(&camera,
		(Vec3){ 0.0f, 18.0f, 13.0f },   /* eye: high and pulled back */
		(Vec3){ 0.0f,  0.0f,  0.0f },   /* looking at arena center */
		(Vec3){ 0.0f,  1.0f,  0.0f });

	Mat4 proj = perspective(radians(60.0f), (float)WIDTH / HEIGHT, 0.1f, 100.0f);
	Mat4 view = camera_view(&camera);   /* constant: computed once */

	Shader phong = shader_phong();
	Program program = { 0 };

	CubeDrawer drawer = {
		.renderer     = &renderer,
		.program      = &program,
		.shader       = &phong,
		.cube         = &cube,
		.view         = view,
		.proj         = proj,
		.eye          = camera.eye,
		.light_pos    = { 0.0f, 20.0f, 6.0f },
		.specular_lut = specular_lut
	};

	Game game;
	game_init(&game);
	update_title(&game);

	srand((unsigned)time(NULL));

	bool running = true;
	SDL_Event e;
	Uint32 last = SDL_GetTicks();

	while (running) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				running = false;
			} else if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_ESCAPE: running = false; break;
				case SDLK_r:      game_reset(&game); update_title(&game); break;
				case SDLK_UP:    case SDLK_w: game_input_dir(&game, DIR_UP);    break;
				case SDLK_DOWN:  case SDLK_s: game_input_dir(&game, DIR_DOWN);  break;
				case SDLK_LEFT:  case SDLK_a: game_input_dir(&game, DIR_LEFT);  break;
				case SDLK_RIGHT: case SDLK_d: game_input_dir(&game, DIR_RIGHT); break;
				}
			}
		}

		Uint32 now = SDL_GetTicks();
		float dt = (float)(now - last);
		if (dt < 16.0f) { SDL_Delay(1); continue; }
		last = now;

		int prev_score = game.score;
		GameState prev_state = game.state;

		game_update(&game, dt);

		if (game.score != prev_score || game.state != prev_state)
			update_title(&game);

		renderer_clear(&renderer, RGB(18, 18, 22));
		game_render(&game, &drawer);
		sdl_present();
	}

	free(z_buffer);
	free(cube.vertices);
	free(cube.normals);
	free(cube.faces);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
