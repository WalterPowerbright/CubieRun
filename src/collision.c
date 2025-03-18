bool is_grounded(Player *p_player, Rectangle *p_ground);
Rectangle get_body_in_ground(Player *p_player, Rectangle *p_ground);
bool is_colliding_player_cactus(Player *p_player, Cactus *p_cactus);

/* -- LINE BREAK -- */

bool is_grounded(Player *p_player, Rectangle *p_ground) {	
	Vector2 target_point = (Vector2) {
		.x = p_player->ground_detector.x,
		.y = p_player->ground_detector.y
	};

	return CheckCollisionPointRec(target_point, *p_ground);
}

Rectangle get_body_in_ground(Player *p_player, Rectangle *p_ground) {
	return GetCollisionRec(p_player->hitbox, *p_ground);
}

bool is_colliding_player_cactus(Player *p_player, Cactus *p_cactus) {
	return CheckCollisionRecs(p_player->hitbox, p_cactus->hitbox);
}
