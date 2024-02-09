#include<raylib.h>
#include<stdlib.h>
#include<stdio.h>
#include "types.h"

float difference(float num1, float num2){
	float diff = num1 - num2;
	if (diff < 0){
		diff = diff * -1;
	}
	return diff;
}

int main(){
	struct window WIN;
	WIN.height = 1920;
	WIN.width = 1080;
	WIN.name = "the worlds best game";
	InitWindow(WIN.height, WIN.width, WIN.name); 

	SetTargetFPS(60);
	
	InitAudioDevice();
	Music music = LoadMusicStream("music.wav");
	PlayMusicStream(music);

	GameScreen game = TITLE;

	struct player PLAY;
	PLAY.size = 10;
	PLAY.color = PINK;
	PLAY.x = 100;
	PLAY.y = 100;
	PLAY.deltaV = 1;

	struct enemy ENEMYS;
	
	while (!WindowShouldClose()){
		// drawing
		BeginDrawing();
		switch (game){
			case TITLE:
				ClearBackground(WHITE);
				DrawText("press enter to play", WIN.height/2 - 150, WIN.width/2, 30, BLACK);
				break;

			case GAMEPLAY:
				ClearBackground(BLUE);
				DrawCircle(PLAY.x, PLAY.y, PLAY.size, PLAY.color);	
				DrawCircle(ENEMYS.x, ENEMYS.y, ENEMYS.size, ENEMYS.color);
				break;
			
			default: break;
		}
		EndDrawing();
		// game logic
		UpdateMusicStream(music);
		switch (game){
			case TITLE:
				if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP)){
                    			game = GAMEPLAY;
					
					ENEMYS.size = 20;
					ENEMYS.color = BROWN;
					ENEMYS.x = GetRandomValue(0, WIN.width);
					ENEMYS.y = GetRandomValue(0, WIN.height);
					ENEMYS.speed = 0.5;
                		}
				break;

			case GAMEPLAY:
				if (IsKeyDown(KEY_UP)){
					PLAY.y += -1 * PLAY.deltaV;
					PLAY.deltaV += 0.1;
				}else if (IsKeyDown(KEY_DOWN)){
					PLAY.y += 1 * PLAY.deltaV;
					PLAY.deltaV += 0.1;
				}
				
				if (IsKeyDown(KEY_LEFT)){
					PLAY.x += -1 * PLAY.deltaV;
					PLAY.deltaV += 0.1;
				}else if (IsKeyDown(KEY_RIGHT)){
					PLAY.x += 1 * PLAY.deltaV;
					PLAY.deltaV += 0.1;
				}
				
				PLAY.deltaV -= 0.05;

				if (PLAY.deltaV < 1){
					PLAY.deltaV = 1;
				}else if (PLAY.deltaV > 3) {
					PLAY.deltaV = 3;
				}
				
				if (PLAY.x < 1){
					PLAY.x = 1;
				}else if(PLAY.x > 1920){
					PLAY.x = 1920;
				}
				if (PLAY.y < 1){
					PLAY.y = 1;
				}else if(PLAY.y > 1080){
					PLAY.y = 1080;
				}

				if (PLAY.x > ENEMYS.x){
					ENEMYS.x += 1 * ENEMYS.speed;
				} 
				if (PLAY.y > ENEMYS.y){
					ENEMYS.y += 1 * ENEMYS.speed;
				}
				if (PLAY.x < ENEMYS.x){
					ENEMYS.x -= 1 * ENEMYS.speed;
				}
				if (PLAY.y < ENEMYS.y){
					ENEMYS.y -= 1 * ENEMYS.speed;
				}
				
							
				float oldSpeed = ENEMYS.speed;

				do {
					ENEMYS.speed = (float)GetRandomValue(1,6) / 2;
				}while (difference(ENEMYS.speed, oldSpeed) < 1);

				if (difference(PLAY.x, ENEMYS.x) < 10){ 
					if (difference(PLAY.y, ENEMYS.y) < 10){
						game = TITLE;
				      	}
				}

				break;
			
			default: break;
		}					

	}
	
	UnloadMusicStream(music);
	CloseAudioDevice();

	CloseWindow();
	return 0;
}


