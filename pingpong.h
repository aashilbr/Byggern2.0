/*
 * pingpong.h
 *
 * Created: 31.10.2020 14:13:04
 *  Author: sandrgl
 */ 


#ifndef PINGPONG_H_
#define PINGPONG_H_

void pingpong_play(void);
int check_if_game_over(void);
void pingpong_move_with_sliders(void);
void pingpong_move_with_joystick(void);
void pingpong_print_score();
void pingpong_init(void);
void pingpong_play_with_sliders(void);
void pingpong_play_with_joystick(void);

#endif /* PINGPONG_H_ */