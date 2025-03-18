const char* get_score_text(int score);
const char* get_final_score(int score);

void draw_title(void);
void draw_score(int score);
void draw_game_over(int score);
void draw_ui(GameState game_state, int score);

const char* get_score_text(int score) {
	return TextFormat("%d", score);
}

const char* get_final_score(int score) {
	return TextFormat("Final Score: %d", score);
}

void draw_title(void) {
	DrawRectangle(32.0, 32.0, 352.0, 120.0, CUSTOM_LIGHT);
	DrawText("Cubie Run", 48.0, 32.0+8.0, 64.0, CUSTOM_DARK);
	DrawText("Click to Start", 48.0, 104.0+8.0, 32.0, CUSTOM_DARK);
}

void draw_score(int score) {
	DrawText(get_score_text(score), 24.0, 24.0, 64.0, CUSTOM_LIGHT);
}

void draw_game_over(int score) {
	DrawText("GAME OVER", 32.0, 32.0, 64.0, CUSTOM_LIGHT);
	DrawText(get_final_score(score), 32.0, 104.0, 32.0, CUSTOM_LIGHT);
	DrawText("CLICK TO RESET", 32.0, 136.0+8.0, 32, CUSTOM_LIGHT);
}

void draw_ui(GameState game_state, int score) {
	switch (game_state) {
		case STATE_START: {
			draw_title();
			break;
		}
		
		case STATE_GAMEPLAY: {
			draw_score(score);
			break;
		}
		
		case STATE_END: {
			draw_game_over(score);
			break;
		}
	}
}
