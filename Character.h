#ifndef CHARACTER_H_
#define CHARACTER_H_
#include"LTexture.h"

static const int player_jump = 110;
static const int player_height = 45;
static const int player_width = 30;

class Character
{
public:
    Character(); // Constructor

    bool check_on_ground();
    void handle_event(SDL_Event &e);
    bool check_collision(SDL_Rect& threat);

    void pause(SDL_Event e);
    void jump(); // Falls back to the ground
    ///Jump

    void render_when_jump_1(LTexture &gPlayer1_jump, SDL_Renderer *&gRenderer);
    void render_when_jump_2(LTexture &gPlayer2_jump, SDL_Renderer *&gRenderer);
    void render_when_jump_3(LTexture &gPlayer3_jump, SDL_Renderer *&gRenderer);

    ///Die animation

    void render_when_die(LTexture &gPlayer_die, SDL_Renderer *&gRenderer);
    void render_death_animation_1(LTexture &gPlayer1_death, SDL_Renderer* &gRenderer);
    void render_death_animation_2(LTexture &gPlayer2_death, SDL_Renderer* &gRenderer);
    void render_death_animation_3(LTexture &gPlayer3_death, SDL_Renderer* &gRenderer);

    ///Run animaition
    void render_on_ground_1(LTexture &gPlayer1_run, SDL_Renderer *&gRenderer, SDL_Rect &player1_position, SDL_Rect &player1_rect, int &frame1_width, int &frame1);
    void render_on_ground_2(LTexture &gPlayer2_run, SDL_Renderer *&gRenderer, SDL_Rect &player2_position, SDL_Rect &player2_rect, int &frame2_width, int &frame2);
    void render_on_ground_3(LTexture &gPlayer3_run, SDL_Renderer *&gRenderer, SDL_Rect &player3_position, SDL_Rect &player3_rect, int &frame3_width, int &frame3);


    //initialize the animation when die
    int death_frame = 0;
    bool death_animation_completed = false;
    bool death_animation_check();


    void reset();
    void gameOver();

private:
    bool check_pause; // Pause game
    int jumpDirection; // 1 = Jump down, 0 = On ground, -1 = Jump up
    int mPosX, mPosY; // Position
    int mVelY;
    SDL_Rect mCollider; // Collision box

};
#endif // CHARACTER_H_
