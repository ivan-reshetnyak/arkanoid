#pragma once

#define PI 3.1415926

#define LIVES 3

// Paddle
#define PADDLE_SPEED 5.0
#define PADDLE_HEIGHT 0.03
#define PADDLE_WIDTH 0.4
#define PADDLE_RESIZE_TIME 0.2
#define PADDLE_COLOR { 1, 1, 1 }

// Ball
#define BALL_SPEED 0.5
#define BALL_XSIZE 0.03
#define BALL_DETAIL 20
#define BALL_COLOR { 1, 1, 1 }

// Bricks
#define BRICK_ROWS 5
#define BRICK_COLUMNS 10
#define BRICK_WIDTH 0.19
#define BRICK_HEIGHT 0.1
#define BRICK_YSPACING 0.11
// Standart
#define BRICK_STANDART_WEIGHT 100
#define BRICK_STANDART_COLOR { 0.3, 0.3, 0.3 }
// Hard
#define BRICK_HARD_WEIGHT 30
#define BRICK_HARD_COLOR { 1, 1, 1 }
#define BRICK_HARD_HP_MIN 2
#define BRICK_HARD_HP_MAX 5
// Flicker
#define BRICK_FLICKER_WEIGHT 20
#define BRICK_FLICKER_PERIOD_MIN 1
#define BRICK_FLICKER_PERIOD_MAX 2
#define BRICK_FLICKER_COLOR { 0.3, 0.3, 0.6 }
#define BRICK_FLICKER_A 0.2
// Adder
#define ADDER_TO_ADD 2
#define ADDER_PERIOD 1.
#define BRICK_ADDER_WEIGHT 10
#define BRICK_ADDER_COLOR { 0.9, 0.4, 0.4 }


