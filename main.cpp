#include"LTexture.h"
#include"Functions.h"
#include"LTimer.h"
#include"Character.h"
#include"Threats.h"
#include"LMedia.h"

const char *WINDOW_TITLE = "Road to Torii";

// Font and text color
TTF_Font *gFont = NULL;
SDL_Color textColor = {0, 0, 0, 255}; // Black

// Music
Mix_Music *gMusic_in_menu = NULL;
Mix_Music *gMusic_when_playing = NULL;
// The sound effects that will be used
Mix_Chunk *gjump = NULL;
Mix_Chunk *gdeath = NULL;

// Images
LTexture menu, introduction, select, select1, select2, select3;
LTexture gPlayer1_jump, gPlayer2_jump, gPlayer3_jump, gBackground;
LTexture gPlayer1_death, gPlayer2_death, gPlayer3_death;
LTexture gThreat1, gThreat2;
LTexture gArrow_left, gArrow_right, gArcher_left, gArcher_right;
LTexture gPause, gResume;

// Texts on screen
LTexture gScore, current_score;
LTexture gHighscore, highscore;

LTexture game_over;
LTexture replay;
LTexture exit_game;

// Game checks
bool check_game_over = false, check_exit = false, check_pause = false, check_instruction = false, check_select = false, check_return = false;
bool check_start_game = false, check_timer_start = false, check_music_game_play = false, check_music_menu_play = false;
bool check_select1 = false, check_select2 = false, check_select3 = false;

// Player animation
LTexture gPlayer1_run, gPlayer2_run, gPlayer3_run;
SDL_Rect player1_rect, player2_rect, player3_rect;
int frame1_width, frame2_width, frame3_width;


Character character; // Character
// Threats
Threat obstacle1, obstacle2;
Threat arrowLeft, arrowRight;

LTimer timer; // Score
// Obstacle1's location after each game loop
SDL_Rect threat1;
SDL_Rect threat2;
SDL_Rect arrow_left;
SDL_Rect arrow_right;

stringstream timeText;

// Game functions
void playAgain(SDL_Event e, SDL_Renderer* &gRenderer,
               SDL_Rect &player1_position, SDL_Rect &player1_rect, int &frame1_width, int &frame1,
               SDL_Rect &player2_position, SDL_Rect &player2_rect, int &frame2_width, int &frame2,
               SDL_Rect &player3_position, SDL_Rect &player3_rect, int &frame3_width, int &frame3);
void render_before_and_while_play(SDL_Renderer* &gRenderer,
                                  SDL_Rect &player1_position, SDL_Rect &player1_rect, int &frame1_width, int &frame1,
                                  SDL_Rect &player2_position, SDL_Rect &player2_rect, int &frame2_width, int &frame2,
                                  SDL_Rect &player3_position, SDL_Rect &player3_rect, int &frame3_width, int &frame3);
void render_gameover(SDL_Renderer* &gRenderer);
void handle_keyboard_events(SDL_Event e, SDL_Renderer* &gRenderer,
                            SDL_Rect &player1_position, SDL_Rect &player1_rect, int &frame1_width, int &frame1,
                            SDL_Rect &player2_position, SDL_Rect &player2_rect, int &frame2_width, int &frame2,
                            SDL_Rect &player3_position, SDL_Rect &player3_rect, int &frame3_width, int &frame3);
void update_game();
void gameLoop(SDL_Event e, SDL_Renderer* &gRenderer,
              SDL_Rect &player1_position, SDL_Rect &player1_rect, int &frame1_width, int &frame1,
              SDL_Rect &player2_position, SDL_Rect &player2_rect, int &frame2_width, int &frame2,
              SDL_Rect &player3_position, SDL_Rect &player3_rect, int &frame3_width, int &frame3);

//void render_death_animation(LTexture &gPlayer_death, SDL_Renderer* &gRenderer);
// File to read and write high score
ifstream file_in;
ofstream file_out;
int best_score;

// Background animation
int scrolling_offset = 0;

int main(int argc, char* argv[])
{
    SDL_Window* gWindow = NULL;
    SDL_Renderer* gRenderer = NULL;
    SDL_Event e;
    int frame1 = 0, frame2 = 0, frame3 = 0;
    SDL_Rect player1_position, player2_position, player3_position;
    srand(time(NULL));
    if(!init(gWindow, gRenderer, WINDOW_TITLE))
    {
        cout << "Failed to initialize SDL!" << endl;
    }
    else
    {
        if(!loadMedia(gPlayer1_jump, gPlayer2_jump, gPlayer3_jump, gPlayer1_death, gPlayer2_death, gPlayer3_death,
               gBackground, gThreat1, gThreat2,
               gPause, gResume, gScore, game_over, replay, exit_game, gHighscore, introduction,
               gMusic_in_menu, gMusic_when_playing, gjump, gdeath, gFont,
               gRenderer,
               gPlayer1_run, player1_rect, frame1_width,
               gPlayer2_run, player2_rect, frame2_width,
               gPlayer3_run, player3_rect, frame3_width,
               gArrow_left, gArrow_right, gArcher_left, gArcher_right,
               menu, select, select1, select2, select3))
        {
            cout << "Failed to load media!" << endl;
        }
        else
        {
            gameLoop(e, gRenderer,
              player1_position, player1_rect, frame1_width, frame1,
              player2_position, player2_rect, frame2_width, frame2,
              player3_position, player3_rect, frame3_width, frame3);
        }
    }
    close(gPlayer1_jump, gPlayer2_jump, gPlayer3_jump, gPlayer1_death, gPlayer2_death, gPlayer3_death,
           gBackground, gThreat1, gThreat2,
           gPause, gResume, gScore, game_over, replay, exit_game, gHighscore, introduction,
           gMusic_in_menu, gMusic_when_playing, gjump, gdeath, gFont, current_score,
           gWindow, gRenderer,
           gPlayer1_run, gPlayer2_run, gPlayer3_run,
           gArrow_left, gArrow_right, gArcher_left, gArcher_right,
           menu, select, select1, select2, select3);
    return 0;
}

void gameLoop(SDL_Event e, SDL_Renderer* &gRenderer,
              SDL_Rect &player1_position, SDL_Rect &player1_rect, int &frame1_width, int &frame1,
              SDL_Rect &player2_position, SDL_Rect &player2_rect, int &frame2_width, int &frame2,
              SDL_Rect &player3_position, SDL_Rect &player3_rect, int &frame3_width, int &frame3)
{
    while(!check_exit)
    {
        update_game();
        handle_keyboard_events(e, gRenderer,
                            player1_position, player1_rect, frame1_width, frame1,
                            player2_position, player2_rect, frame2_width, frame2,
                            player3_position, player3_rect, frame3_width, frame3);
        render_before_and_while_play(gRenderer,
                                  player1_position, player1_rect, frame1_width, frame1,
                                  player2_position, player2_rect, frame2_width, frame2,
                                  player3_position, player3_rect, frame3_width, frame3);
        render_gameover(gRenderer);
        SDL_RenderPresent(gRenderer);

    }
}

void handle_keyboard_events(SDL_Event e, SDL_Renderer* &gRenderer,
                            SDL_Rect &player1_position, SDL_Rect &player1_rect, int &frame1_width, int &frame1,
                            SDL_Rect &player2_position, SDL_Rect &player2_rect, int &frame2_width, int &frame2,
                            SDL_Rect &player3_position, SDL_Rect &player3_rect, int &frame3_width, int &frame3)
{
    while(SDL_PollEvent(&e) != 0)
    {
        if(e.type == SDL_QUIT) check_exit = true;
        else if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
        {
            if(e.key.keysym.sym == SDLK_ESCAPE) check_exit = true;
            else if(e.key.keysym.sym == SDLK_h) {check_instruction = true; check_return = false;}
                else if(e.key.keysym.sym == SDLK_c) {check_select = true; check_return = false;}
                else if(e.key.keysym.sym == SDLK_1) {check_select1 = true; check_select2 = false; check_select3 = false; check_return = false;}
                else if(e.key.keysym.sym == SDLK_2) {check_select1 = false; check_select2 = true; check_select3 = false; check_return = false;}
                else if(e.key.keysym.sym == SDLK_3) {check_select1 = false; check_select2 = false; check_select3 = true; check_return = false;}
                else if(e.key.keysym.sym == SDLK_r) {check_return = true; check_instruction = false; check_select = true;}
                else if(e.key.keysym.sym == SDLK_s)check_start_game = true;
            if(check_start_game && !check_game_over)
            {
                if(!check_music_game_play)
                {
                    Mix_PlayMusic(gMusic_when_playing, -1);
                    check_music_game_play = true;
                }
                if(e.key.keysym.sym == SDLK_SPACE && !check_pause)
                {
                    if(character.check_on_ground()) Mix_PlayChannel(-1, gjump, 0);
                    character.handle_event(e);
                }
                //Start/stop the timer
                if( e.key.keysym.sym == SDLK_s && !check_timer_start )
                {
                    timer.start();
                    check_timer_start = true;
                }
                //Pause/unpause
                else if( e.key.keysym.sym == SDLK_p )
                {
                    // pause/resume music
                    if(Mix_PausedMusic() == 1) Mix_ResumeMusic();
                    else Mix_PauseMusic();

                    check_pause = !check_pause;

                    character.pause(e);
                    obstacle1.pause(e);
                    obstacle2.pause(e);
                    arrowLeft.pause(e);
                    arrowRight.pause(e);
                    if(e.key.keysym.sym == SDLK_r){

                    }

                    // pause/resume timer
                    if( timer.isPaused() ) timer.unpause();
                    else timer.pause();
                }
                if(e.key.keysym.sym == SDLK_r)
                {
                    check_game_over = true;
                }
            }
            if(check_game_over) playAgain(e, gRenderer,
                                        player1_position, player1_rect, frame1_width, frame1,
                                        player2_position, player2_rect, frame2_width, frame2,
                                        player3_position, player3_rect, frame3_width, frame3);
        }
    }
}

void playAgain(SDL_Event e, SDL_Renderer* &gRenderer,
               SDL_Rect &player1_position, SDL_Rect &player1_rect, int &frame1_width, int &frame1,
               SDL_Rect &player2_position, SDL_Rect &player2_rect, int &frame2_width, int &frame2,
               SDL_Rect &player3_position, SDL_Rect &player3_rect, int &frame3_width, int &frame3)
{
    if(e.key.keysym.sym == SDLK_a)
    {
        check_start_game = false;
        check_instruction = false;
        check_return = false;
        check_select = false;
        check_select1 = false;
        check_select2 = false;
        check_select3 = false;
        check_game_over = false;
        check_timer_start = false;
        check_music_menu_play = false;
        check_music_game_play = false;
        check_pause = false;
        // reposition
        character.reset();
        obstacle1.reset();
        obstacle2.reset();
        arrowLeft.reset();
        arrowRight.reset();

        timer.stop();
        // play again
        gameLoop(e, gRenderer,
              player1_position, player1_rect, frame1_width, frame1,
              player2_position, player2_rect, frame2_width, frame2,
              player3_position, player3_rect, frame3_width, frame3);
    }
    else if(e.key.keysym.sym == SDLK_ESCAPE) check_exit = true;
}

void render_before_and_while_play(SDL_Renderer* &gRenderer,
                                  SDL_Rect &player1_position, SDL_Rect &player1_rect, int &frame1_width, int &frame1,
                                  SDL_Rect &player2_position, SDL_Rect &player2_rect, int &frame2_width, int &frame2,
                                  SDL_Rect &player3_position, SDL_Rect &player3_rect, int &frame3_width, int &frame3)
{
    //Set text to be rendered
    timeText.str("");
    timeText << (timer.getTicks() / 300);

    // Render score (time)
    if(!current_score.load_from_rendered_text(timeText.str().c_str(), textColor, gRenderer, gFont))
    {
        cout << "Unable to render current score texture!" << endl;
    }

    // Render hi score
    if(check_start_game)
    {
        file_in.open("highest_score.txt");
        file_in >> best_score;
        file_in.close();
        if (check_game_over && best_score < timer.getTicks()/300 )
        {
            file_out.open("highest_score.txt");
            best_score = timer.getTicks()/300;
            file_out.seekp(0); // shift pointer to the beginning to rewrite the high score
            file_out << best_score;
            file_out.close();
        }

        stringstream h;
        h.str("");
        h << best_score;
        if(!highscore.load_from_rendered_text(h.str().c_str(), textColor, gRenderer, gFont))
        {
            cout << "Unable to render high score texture!" << endl;
        }
    }


    // Background animation
    if(check_start_game && !check_game_over && !check_pause)
    {
        scrolling_offset -= 2; // = 0
        if(scrolling_offset < -gBackground.getWidth())
        {
            scrolling_offset = 0;
        }
    }

    // Clear screen
    SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
    SDL_RenderClear(gRenderer);

    // Render background and threats
    gBackground.render(scrolling_offset, 0, gRenderer);
    gBackground.render(scrolling_offset + gBackground.getWidth(), 0, gRenderer);
    obstacle1.render_threat1(gThreat1, gRenderer);
    obstacle2.render_threat2(gThreat2, gRenderer);
    arrowLeft.render_arrow_left(gArrow_left, gArcher_left, gRenderer);
    arrowRight.render_arrow_right(gArrow_right, gArcher_right, gRenderer);

    // Render before game
    if(!check_start_game){
        menu.render(0,0,gRenderer);
        if(!check_music_menu_play)
        {
            Mix_PlayMusic(gMusic_in_menu, -1);
            check_music_menu_play = true;
        }
        if(check_select){
            select.render(0,0,gRenderer);
        }
        if (check_select1){
            select1.render(0,0,gRenderer);
        }
        if (check_select2){
            select2.render(0,0,gRenderer);
        }
        if (check_select3){
            select3.render(0,0,gRenderer);
        }
        if(check_instruction){
            introduction.render(0,0,gRenderer);
        }
        if(check_return){
            menu.render(0,0, gRenderer);
        }
    }

    // Render while playing
    if(check_start_game)
    {
        if(!character.check_on_ground() && !check_game_over){
            if(check_select1) character.render_when_jump_1(gPlayer1_jump, gRenderer);
            if(check_select2) character.render_when_jump_2(gPlayer2_jump, gRenderer);
            if(check_select3) character.render_when_jump_3(gPlayer3_jump, gRenderer);
            if(!check_select1 and !check_select2 and !check_select3) character.render_when_jump_1(gPlayer1_jump, gRenderer);
        }
        else if(!check_game_over){
                if(check_select1) character.render_on_ground_1(gPlayer1_run, gRenderer, player1_position, player1_rect, frame1_width, frame1);
                if(check_select2) character.render_on_ground_2(gPlayer2_run, gRenderer, player2_position, player2_rect, frame2_width, frame2);
                if(check_select3) character.render_on_ground_3(gPlayer3_run, gRenderer, player2_position, player3_rect, frame3_width, frame3);
                if(!check_select1 and !check_select2 and !check_select3) character.render_on_ground_1(gPlayer1_run, gRenderer, player1_position, player1_rect, frame1_width, frame1);
        }
        if(!check_game_over)
        {
            obstacle1.threat_move();
            obstacle2.threat_move();
            arrowLeft.threat_move();
            arrowRight.threat_move();

            if(check_pause)
                    gPause.render(300, 0, gRenderer);
            else gResume.render(10, 10, gRenderer);

        }
        // Render high score
        gHighscore.render(650, 15, gRenderer);
        highscore.render(675, 15, gRenderer);
        // Render current score
        gScore.render(720, 15, gRenderer);
        current_score.render(770, 15, gRenderer);
    }
}

void render_gameover(SDL_Renderer* &gRenderer)
{
    // Check collision
    if((character.check_collision(threat1) || character.check_collision(threat2) || character.check_collision(arrow_left)
        || character.check_collision(arrow_right)) && !check_game_over)
    {
        Mix_PlayChannel(-1, gdeath, 0);
        check_game_over = true;
    }
    // When game is over
    if(check_game_over)
    {
        if(check_select1) character.render_death_animation_1(gPlayer1_death, gRenderer);
        if(check_select2) character.render_death_animation_2(gPlayer2_death, gRenderer);
        if(check_select3) character.render_death_animation_3(gPlayer3_death, gRenderer);
        if(!check_select1 and !check_select2 and !check_select3) character.render_death_animation_1(gPlayer1_death, gRenderer);
        if(character.death_animation_check()) {
            game_over.render(0, 0, gRenderer);
            gHighscore.render(650, 15, gRenderer);
            highscore.render(675, 15, gRenderer);
            // Render current score
            gScore.render(720, 15, gRenderer);
            current_score.render(770, 15, gRenderer);
       }

        //stop music
        if(Mix_PausedMusic() != 1) Mix_PauseMusic();

        // Stop character, threats, and time
        character.gameOver();
        obstacle1.gameOver();
        obstacle2.gameOver();
        arrowLeft.gameOver();
        arrowRight.gameOver();
        timer.gameOver();
    }
}



void update_game()
{
    if(!check_game_over)
    {
        threat1 = obstacle1.get_obstacle_1_dimension(); // update threats position
        threat2 = obstacle2.get_obstacle_2_dimension();
        arrow_left = arrowLeft.get_arrow_left_dimension();
        arrow_right = arrowRight.get_arrow_right_dimension();
        character.jump(); // character falls back to ground
    }
}
