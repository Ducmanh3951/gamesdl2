#ifndef LMEDIA_H
#define LMEDIA_H

#include"LTexture.h"
#include"Functions.h"

// Initialize SDL_Window, SDL_Renderer
bool init(SDL_Window* &gWindow, SDL_Renderer* &gRenderer, const char* WINDOW_TITLE);


// Load images, texts, music, sounds
bool loadMedia(LTexture &gPlayer1_jump, LTexture &gPlayer2_jump, LTexture &gPlayer3_jump, LTexture &gPlayer1_death, LTexture &gPlayer2_death, LTexture &gPlayer3_death,
               LTexture &gPlayer_background, LTexture &gThreat1, LTexture &gThreat2,
               LTexture &gPause, LTexture &gResume, LTexture &gScore, LTexture &game_over,LTexture &replay, LTexture &exit_game, LTexture &gHighscore, LTexture &introduction,
               Mix_Music *&gMusic_in_menu, Mix_Music *&gMusic_when_playing, Mix_Chunk *&gjump, Mix_Chunk *&gdeath, TTF_Font *&gFont,
               SDL_Renderer* &gRenderer,
               LTexture &gPlayer1_run, SDL_Rect &player1_rect, int &frame1_width,
               LTexture &gPlayer2_run, SDL_Rect &player2_rect, int &frame2_width,
               LTexture &gPlayer3_run, SDL_Rect &player3_rect, int &frame3_width,
               LTexture &gArrow_left, LTexture &gArrow_right, LTexture &gWarning1, LTexture &gWarning2,
               LTexture &menu, LTexture &select, LTexture &select1, LTexture &select2, LTexture &select3);

// Free all iamges, texts, music, sounds and SDL libraries
void close(LTexture &gPlayer1_jump, LTexture &gPlayer2_jump, LTexture &gPlayer3_jump, LTexture &gPlayer1_death, LTexture &gPlayer2_death, LTexture &gPlayer3_death,
           LTexture &gPlayer_background, LTexture &gThreat1, LTexture &gThreat2,
           LTexture &gPause, LTexture &gResume, LTexture &gScore, LTexture &game_over, LTexture &replay, LTexture &exit_game, LTexture &gHighscore, LTexture &introduction,
           Mix_Music *&gMusic_in_menu, Mix_Music *&gMusic_when_playing, Mix_Chunk *&gjump, Mix_Chunk *&gdeath, TTF_Font *&gFont, LTexture &current_score,
           SDL_Window *&gWindow, SDL_Renderer* &gRenderer,
           LTexture &gPlayer1_run, LTexture &gPlayer2_run, LTexture &gPlayer3_run,
           LTexture &gArrow_left, LTexture &gArrow_right, LTexture &gWarning1, LTexture &gWarning2,
           LTexture &menu, LTexture &select, LTexture &select1, LTexture &select2, LTexture &select3);

#endif // LMEDIA_H
