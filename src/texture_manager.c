Texture textures[3];

void load_textures(void);
void unload_textures(void);

/* -- LINE BREAK -- */

void load_textures(void) {
	textures[0] = LoadTexture("assets/square_man.png");
	textures[1] = LoadTexture("assets/cactus.png");
	textures[2] = LoadTexture("assets/ded_square_man.png");
}

void unload_textures(void) {
	for (int i = 0; i < 3; i++) {
		UnloadTexture(textures[i]);
	}
}
