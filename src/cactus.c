typedef struct Cactus {
	Vector2 position;
	int texture_index;
	Rectangle hitbox;
} Cactus;

void init_cactus(Cactus *p_cactus);
bool is_cactus_offscreen(Cactus *p_cactus);
void draw_cactus(Cactus *p_cactus);
void update_cactus(Cactus *p_cactus, float delta_time);
void spawn_cactus(Cactus *p_cactus);

/* -- LINE BREAK -- */

void init_cactus(Cactus *p_cactus) {
	p_cactus->position.x = -64.0;
	p_cactus->position.y = SCREEN_HEIGHT - 32.0 - 64.0;
	
	p_cactus->texture_index = 1;
	
	float hitbox_size_x = textures[p_cactus->texture_index].width - 16.0;
	float hitbox_size_y = textures[p_cactus->texture_index].height - 16.0;
	
	p_cactus->hitbox = (Rectangle) {
		.x = p_cactus->position.x + 8.0,
		.y = p_cactus->position.y + 26.0,
		.width = hitbox_size_x,
		.height = hitbox_size_y
	};
}

void draw_cactus(Cactus *p_cactus) {
	DrawTextureEx(textures[p_cactus->texture_index], p_cactus->position, 0.0, 1.0, WHITE);
	// DrawRectangleRec(p_cactus->hitbox, RED);
}

void update_cactus(Cactus *p_cactus, float delta_time) {
	p_cactus->position.x -= CACTUS_SPEED * delta_time;
	
	p_cactus->hitbox.x = p_cactus->position.x + 8.0;
}

bool is_cactus_offscreen(Cactus *p_cactus) {
	return p_cactus->position.x < -64.0;
}

void spawn_cactus(Cactus *p_cactus) {
	p_cactus->position.x = SCREEN_WIDTH;
}
