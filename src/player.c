typedef struct Player {
	Vector2 position;
	Vector2 velocity;
	int alive_texture_index;
	int dead_texture_index;
	Vector2 ground_detector;
	Rectangle hitbox;
} Player;

void init_player(Player *p_player);
void draw_player(Player *p_player, bool is_dead);
void apply_gravity(Player *p_player, bool is_grounded, float delta_time);
void jump(Player *p_player);
void eject_player_from_ground(Player *p_player, Rectangle body_in_ground);

/* -- LINE BREAK -- */

void init_player(Player *p_player) {
	p_player->alive_texture_index = 0;
	p_player->dead_texture_index = 2;

	p_player->position.x = 96.0;
	p_player->position.y = SCREEN_HEIGHT - 32.0 - 64.0;
	
	p_player->velocity.x = 0.0;
	p_player->velocity.y = 0.0;
	
	p_player->ground_detector.x = p_player->position.x + (textures[p_player->alive_texture_index].width / 2);
	p_player->ground_detector.y = p_player->position.y + (textures[p_player->alive_texture_index].height + 1.0);
	
	p_player->hitbox = (Rectangle) {
		.x = p_player->position.x,
		.y = p_player->position.y,
		.width = textures[p_player->alive_texture_index].width,
		.height = textures[p_player->alive_texture_index].height
	};
}

void draw_player(Player *p_player, bool is_dead) {
	if (!is_dead)
		DrawTextureEx(textures[p_player->alive_texture_index], p_player->position, 0.0, 1.0, WHITE);
	else
		DrawTextureEx(textures[p_player->dead_texture_index], p_player->position, 0.0, 1.0, WHITE);
	
	// DrawCircle(p_player->ground_detector.x, p_player->ground_detector.y, 4.0, RED);
	// DrawRectangleRec(p_player->hitbox, RED);
}

void apply_gravity(Player *p_player, bool is_grounded, float delta_time) {
	if (!is_grounded || p_player->velocity.y < 0.0) {
		p_player->velocity.y += GRAVITY * delta_time;
	}
	else if (is_grounded) {
		p_player->velocity.y = 0.0;
	}
}

void jump(Player *p_player) {
	p_player->velocity.y = PLAYER_JUMP_FORCE;
}

void update_player(Player *p_player) {
	if (p_player->velocity.y != 0.0) {
		p_player->position.y += p_player->velocity.y;
		
	}
	
	p_player->ground_detector.y = p_player->position.y + (textures[p_player->alive_texture_index].height + 1.0);
	
	p_player->hitbox.x = p_player->position.x;
	p_player->hitbox.y = p_player->position.y;
}

void eject_player_from_ground(Player *p_player, Rectangle body_in_ground) {
	p_player->position.y -= body_in_ground.height;
}
