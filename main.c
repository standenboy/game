#include <raylib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#include "types.h"
#include "network.h"

float difference(float num1, float num2){
	float diff = num1 - num2;
	if (diff < 0){
		diff = diff * -1;
	}
	return diff;
}

int main(int argc, char *argv[]){
	struct window WIN;
	WIN.height = 1920 / 2;
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
	PLAY.deltaV = 1;

	if (strcmp(argv[1], "purple") == 0){
		PLAY.color = PURPLE;
	}else if(strcmp(argv[1], "green") == 0){
		PLAY.color = GREEN;
	}else{
		PLAY.color = PINK;
	}

	struct player PLAY2;
	PLAY2.size = 10;
	PLAY2.x = 0;
	PLAY2.y = 0; 
	PLAY2.deltaV = 1;

	int sockfd = connectToServer();
	char *amIFirst = malloc(256);
	
	char *color = malloc(256);
	
	recv(sockfd, amIFirst, 256, 0);
	if (strcmp(amIFirst, "first") == 0){
		sendColor(argv[1], sockfd);
		color = recvColor(sockfd);	
	}else{
		color = recvColor(sockfd);	
		sendColor(argv[1], sockfd);
	}
	
	free(amIFirst);

	if (strcmp(color, "purple") == 0){
		PLAY2.color = PURPLE;
	}else if(strcmp(color, "green") == 0){
		PLAY2.color = GREEN;
	}else{
		PLAY2.color = PINK;
	}
	
	free(color);
	
	

	while (!WindowShouldClose()){
		// drawing
		BeginDrawing();
		switch (game){
			case TITLE:
				ClearBackground(WHITE);
				DrawText("press enter to play", WIN.height/2 - 150, WIN.width/2, 30, BLACK);
				PLAY.x = GetRandomValue(0, WIN.width);
				PLAY.y = GetRandomValue(0, WIN.height);
				break;

			case GAMEPLAY:
				ClearBackground(BLACK);
				
				DrawCircle(PLAY.x, PLAY.y, PLAY.size, PLAY.color);	
				DrawCircle(PLAY2.x, PLAY2.y, PLAY2.size, PLAY2.color);

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
				
				char *recived = malloc(256); 
				recived	= sendAndRecive(PLAY.x, PLAY.y, sockfd);

				char *ch;
				ch = strtok(recived,":");
				int counter = 0;
				while (ch != NULL){
					if (counter == 0){
						PLAY2.x = atoi(ch);
					}else{
						PLAY2.y = atoi(ch);
					}
					ch = strtok(NULL, ":");
					counter++;
				}
				
				free(recived);
				
				if (difference(PLAY.x, PLAY2.x) < 10){
					if (difference(PLAY.y, PLAY2.y) < 10){
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


