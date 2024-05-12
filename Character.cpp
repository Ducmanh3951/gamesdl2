#include"Functions.h"
#include"Character.h"
#include"Threats.h"

Character::Character()
{
    //Initialize
    mVelY = 0;
    check_pause = false;
    jumpDirection = 0; // On the ground

    // Character position
    mPosX = 100;
    mPosY = ground_level;

    // Collide box
    mCollider.w = player_width;
    mCollider.h = player_height;
}

bool Character::check_on_ground()
{
    return (jumpDirection == 0);
}

void Character::handle_event( SDL_Event& e )
{
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_SPACE)
    {
        if(jumpDirection == 0)
        {
            jumpDirection = -1;
            mVelY = 5 ;
        }
    }
}

bool Character::check_collision(SDL_Rect& threat)
{
    bool check_collide = true;
    // The sides of character
    int left_player = mPosX;
    int right_player = mPosX + player_width;
    int top_player = mPosY;
    int bottom_player = mPosY + player_height;

    // The sides of threat
    int left_threat = threat.x;
    int right_threat = threat.x + threat.w;
    int top_threat = threat.y;
    int bottom_threat = threat.y + threat.h;

    // Condition when 2 objects collide
    if(bottom_player <= top_threat+10) check_collide = false;
    if(top_player >= bottom_threat) check_collide = false;
    if(right_player <= left_threat) check_collide = false;
    if(left_player >= right_threat-15) check_collide = false;

    return check_collide;
}

void Character::jump()
{
    if(jumpDirection == 0) return; // Do nothing

    // Jump up
    if(jumpDirection == -1 && mPosY >= (ground_level-player_jump))
    {
        if(!check_pause)
        {
            mPosY -= mVelY;
        }
        else
        {
            mPosY = mPosY;
        }

    }

    // When character position is at the highest point
    if(mPosY <= (ground_level-player_jump))
    {
        jumpDirection = 1;
    }

    // Fall back
    if(jumpDirection == 1 && mPosY <= ground_level)
    {
        if(!check_pause)
        {
            mPosY += mVelY;
        }
        else
        {
            mPosY = mPosY;
        }
    }

    // When character position is on the ground
    if (mPosY >= ground_level)
    {
        jumpDirection = 0;
    }
}
///render Jump
void Character::render_when_jump_1(LTexture &gPlayer1_jump, SDL_Renderer *&gRenderer)
{
    gPlayer1_jump.render(mPosX, mPosY, gRenderer);
}

void Character::render_when_jump_2(LTexture &gPlayer2_jump, SDL_Renderer *&gRenderer)
{
    gPlayer2_jump.render(mPosX, mPosY, gRenderer);
}

void Character::render_when_jump_3(LTexture &gPlayer3_jump, SDL_Renderer *&gRenderer)
{
    gPlayer3_jump.render(mPosX, mPosY, gRenderer);
}

///render Run animation

void Character::render_on_ground_1(LTexture &gPlayer1_run, SDL_Renderer *&gRenderer, SDL_Rect &player1_position, SDL_Rect &player1_rect, int &frame1_width, int &frame1)
{
    player1_position.x = 90;
    player1_position.y = ground_level;
    player1_position.w = frame1_width;
    player1_position.h = gPlayer1_run.getHeight() ;

    // Render current frame
    if(!check_pause)
    {
        frame1++;
        if(FPS/frame1 == 15)
        {
            frame1 = 0;
            player1_rect.x += frame1_width;
            if(player1_rect.x >= gPlayer1_run.getWidth())
            {
                player1_rect.x = 0;
            }
        }
    }
    else
    {
        player1_rect.x = player1_rect.x;
    }
    SDL_RenderCopy(gRenderer, gPlayer1_run.getTexture(), &player1_rect, &player1_position);
}

void Character::render_on_ground_2(LTexture &gPlayer2_run, SDL_Renderer *&gRenderer, SDL_Rect &player2_position, SDL_Rect &player2_rect, int &frame2_width, int &frame2)
{
    player2_position.x = 90;
    player2_position.y = ground_level;
    player2_position.w = frame2_width;
    player2_position.h = gPlayer2_run.getHeight() ;

    // Render current frame
    if(!check_pause)
    {
        frame2++;
        if(FPS/frame2 == 15)
        {
            frame2 = 0;
            player2_rect.x += frame2_width;
            if(player2_rect.x >= gPlayer2_run.getWidth())
            {
                player2_rect.x = 0;
            }
        }
    }
    else
    {
        player2_rect.x = player2_rect.x;
    }
    SDL_RenderCopy(gRenderer, gPlayer2_run.getTexture(), &player2_rect, &player2_position);
}

void Character::render_on_ground_3(LTexture &gPlayer3_run, SDL_Renderer *&gRenderer, SDL_Rect &player3_position, SDL_Rect &player3_rect, int &frame3_width, int &frame3)
{
    player3_position.x = 90;
    player3_position.y = ground_level;
    player3_position.w = frame3_width;
    player3_position.h = gPlayer3_run.getHeight() ;

    // Render current frame
    if(!check_pause)
    {
        frame3++;
        if(FPS/frame3 == 15)
        {
            frame3 = 0;
            player3_rect.x += frame3_width;
            if(player3_rect.x >= gPlayer3_run.getWidth())
            {
                player3_rect.x = 0;
            }
        }
    }
    else
    {
        player3_rect.x = player3_rect.x;
    }
    SDL_RenderCopy(gRenderer, gPlayer3_run.getTexture(), &player3_rect, &player3_position);
}

void Character::pause(SDL_Event e)
{
    // pause the character
    if(e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_p)
    {
        if(check_pause == false) check_pause = true;
        else check_pause = false;
    }
}

void Character::gameOver()
{
    mPosY = mPosY;
    mPosX = mPosX;
}

void Character::reset()
{
    mVelY = 0;
    check_pause = false;
    jumpDirection = 0;
    mPosX = 100;
    mPosY = ground_level;
    mCollider.w = player_width;
    mCollider.h = player_height;
    death_frame = 0;
    death_animation_completed = false;
}

///render Die animation
void Character::render_death_animation_1(LTexture &gPlayer1_death, SDL_Renderer* &gRenderer) {

  int frame1_width = gPlayer1_death.getWidth() / 12;
  SDL_Rect srcRect_1 = { frame1_width * death_frame, 0, frame1_width, gPlayer1_death.getHeight() };
  SDL_Rect dstRect_1 = { mPosX, mPosY, frame1_width, gPlayer1_death.getHeight() };
  gPlayer1_death.render(srcRect_1, dstRect_1, gRenderer);

  // Increase frame counter
  death_frame++;
  SDL_Delay(120);

  // Mark when the animation ends
  if (death_frame >= 12) {
    death_animation_completed = true;
  }
}

void Character::render_death_animation_2(LTexture &gPlayer2_death, SDL_Renderer* &gRenderer) {

  int frame2_width = gPlayer2_death.getWidth() / 12;
  SDL_Rect srcRect_2 = { frame2_width * death_frame, 0, frame2_width, gPlayer2_death.getHeight() };
  SDL_Rect dstRect_2 = { mPosX, mPosY, frame2_width, gPlayer2_death.getHeight() };
  gPlayer2_death.render(srcRect_2, dstRect_2, gRenderer);

  // Increase frame counter
  death_frame++;
  SDL_Delay(120);

  // Mark when the animation ends
  if (death_frame >= 12) {
    death_animation_completed = true;
  }
}

void Character::render_death_animation_3(LTexture &gPlayer3_death, SDL_Renderer* &gRenderer) {

  int frame3_width = gPlayer3_death.getWidth() / 12;
  SDL_Rect srcRect_3 = { frame3_width * death_frame, 0, frame3_width, gPlayer3_death.getHeight() };
  SDL_Rect dstRect_3 = { mPosX, mPosY, frame3_width, gPlayer3_death.getHeight() };
  gPlayer3_death.render(srcRect_3, dstRect_3, gRenderer);

  // Increase frame counter
  death_frame++;
  SDL_Delay(150);

  // Mark when the animation ends
  if (death_frame >= 12) {
    death_animation_completed = true;
  }
}
bool Character::death_animation_check() {
    if(death_animation_completed) return true;
}

