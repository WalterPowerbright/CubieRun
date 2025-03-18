#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include <assert.h>

#include "raylib.h"

#include "constants.h"

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

#include "texture_manager.c"
#include "player.c"
#include "cactus.c"
#include "cactus_spawner.c"
#include "collision.c"

typedef enum GameState { STATE_START, STATE_GAMEPLAY, STATE_END } GameState;
GameState current_game_state = STATE_START;

int score = 0;
int score_timer = 0;
const int SCORE_TIME = 10;

void append_score(void);

#include "ui.c"

Player player;
void player_update_logic(float delta_time);

Rectangle ground;
void init_ground(Rectangle *p_ground);

void cactus_update_logic(float delta_time);

void reset_game(void);
void initialize(void);
void update(float delta_time);
void draw(void);
void update_draw_frame(void);

int main() {
	srand(time(NULL));

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "DINO RUN CLONE");
	load_textures();
	
	initialize();
	
	#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop(update_draw_frame, 60, 1);
	#else
	SetTargetFPS(60);
	
	while (!WindowShouldClose()) {
		update_draw_frame();
	}
	#endif
	
	unload_textures();
	CloseWindow();

	return 0;
}

/* -- LINE BREAK -- */

void init_ground(Rectangle *p_ground) {
	p_ground->x = 0.0;
	p_ground->y = 360.0 - 32.0;
	p_ground->width = 640.0;
	p_ground->height = 32.0;
}

void initialize(void) {
	init_ground(&ground);
	init_player(&player);
	
	init_all_cactus();
	
	current_game_state = STATE_START;
	score = 0;
	score_timer = 0;
}

void player_update_logic(float delta_time) {
	bool grounded = is_grounded(&player, &ground);

	if (grounded && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		jump(&player);
	}
	
	apply_gravity(&player, grounded, delta_time);
	update_player(&player);
	
	Rectangle body_in_ground = get_body_in_ground(&player, &ground);
	if (body_in_ground.height > 0) {
		eject_player_from_ground(&player, body_in_ground);
	}
}

void cactus_update_logic(float delta_time) {
	run_cactus_spawner();
	update_all_cactus(delta_time);
	
	for (int i = 0; i < CACTUS_NUM; i++) {
		Cactus cactus = cactus_pool[i];
	
		if (is_cactus_offscreen(&cactus))
			continue;
	
		if (is_colliding_player_cactus(&player, &cactus))
			current_game_state = STATE_END;
	}
}

void append_score(void) {
	score_timer++;
	
	if (score_timer >= SCORE_TIME) {
		score++;
		score_timer = 0;
	}
}

void update(float delta_time) {
	switch (current_game_state) {
		case STATE_START: {
			player_update_logic(delta_time);
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				current_game_state = STATE_GAMEPLAY;
			}
			break;
		}
		
		case STATE_GAMEPLAY: {
			player_update_logic(delta_time);
			cactus_update_logic(delta_time);
			append_score();
			break;
		}
		
		case STATE_END: {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				initialize();
			}
			break;
		}
	}
}

void draw(void) {
	ClearBackground(CUSTOM_DARK);
	
	BeginDrawing();
	
	DrawRectangleRec(ground, CUSTOM_LIGHT);
	draw_all_cactus();
	
	if (current_game_state == STATE_END)
		draw_player(&player, true);
	else
		draw_player(&player, false);
	
	draw_ui(current_game_state, score);
	
	EndDrawing();
}

void update_draw_frame(void) {
	float delta_time = GetFrameTime();

	update(delta_time);
	draw();
}
