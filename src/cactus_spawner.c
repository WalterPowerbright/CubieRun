Cactus cactus_pool[CACTUS_NUM];

int cactus_spawn_timer = 0;
int next_spawn_time = 0;

void init_all_cactus(void);
void draw_all_cactus(void);
void update_all_cactus(float delta_time);
void spawn_available_cactus(void);
void run_cactus_spawner(void);

/* LINE BREAK */

void init_all_cactus(void) {
	for (int i = 0; i < CACTUS_NUM; i++) {
		init_cactus(&cactus_pool[i]);
	}
	
	next_spawn_time = CACTUS_SPAWN_TIME_MAX;
}

void draw_all_cactus(void) {
	for (int i = 0; i < CACTUS_NUM; i++) {
		if (is_cactus_offscreen(&cactus_pool[i]))
			continue;
	
		draw_cactus(&cactus_pool[i]);
	}
}

void update_all_cactus(float delta_time) {
	for (int i = 0; i < CACTUS_NUM; i++) {
		if (is_cactus_offscreen(&cactus_pool[i]))
			continue;
	
		update_cactus(&cactus_pool[i], delta_time);
	}
}

void spawn_available_cactus(void) {
	for (int i = 0; i < CACTUS_NUM; i++) {
		if (is_cactus_offscreen(&cactus_pool[i])) {
			spawn_cactus(&cactus_pool[i]);
			return;
		}
	}
}

void run_cactus_spawner(void) {
	cactus_spawn_timer++;
	
	if (cactus_spawn_timer >= next_spawn_time) {
		cactus_spawn_timer = 0;
		next_spawn_time = rand() % (CACTUS_SPAWN_TIME_MAX - CACTUS_SPAWN_TIME_MIN + 1) + CACTUS_SPAWN_TIME_MIN;
		
		spawn_available_cactus();
	}
}
