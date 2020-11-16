/*
 * tictactoe.c
 *
 * Created: 27.09.2020 14:54:45
 *  Author: aashilbr
 */
#include "tictactoe.h"

uint8_t Grid_pos[9][3] = {{0,16,1},{0,48,1},{0,80,1},{2,16,32},{2,48,32},{2,80,32},{5,16,4},{5,48,4},{5,80,4}};


Grid_state game_board[9];




void ttt_grid(void){
	oled_clear_all();
	for (int i=16;i<113;i++)	{
		oled_pos(0,i);
		oled_write_data(0x01);
		oled_pos(2,i);
		oled_write_data(0x20);
		oled_pos(5,i);
		oled_write_data(0x04);
		oled_pos(7,i);
		oled_write_data(0x80);
	}
	for (int i=0; i<8;i++)	{
		oled_pos(i,16);
		oled_write_data(0xff);
		oled_pos(i,48);
		oled_write_data(0xff);
		oled_pos(i,80);
		oled_write_data(0xff);
		oled_pos(i,112);
		oled_write_data(0xff);
	}
}

void ttt_print_o(uint8_t index){
	uint8_t line=Grid_pos[index][0];
	uint8_t column = Grid_pos[index][1];
	uint8_t bit = Grid_pos[index][2];
	oled_pos(line+1,column+10);
	oled_print("O");
}

void ttt_print_x(uint8_t index){
	uint8_t line=Grid_pos[index][0];
	uint8_t column = Grid_pos[index][1];
	uint8_t bit = Grid_pos[index][2];
	oled_pos(line+1,column+10);
	oled_print("X");
}

void ttt_print_line(uint8_t index){
	uint8_t line=Grid_pos[index][0];
	uint8_t column = Grid_pos[index][1];
	uint8_t bit = Grid_pos[index][2];
	oled_pos(line,column+3);
	for(int i=0; i<4;i++){
		oled_write_data(bit|bit<<2);
	}
}
void ttt_erase_line(uint8_t index){
	uint8_t line=Grid_pos[index][0];
	uint8_t column = Grid_pos[index][1];
	uint8_t bit = Grid_pos[index][2];
	oled_pos(line,column+3);
	for(int i=0; i<4;i++){
		oled_write_data(bit);
	}
}

void ttt_mark(uint8_t index, Grid_state mark){
	game_board[index]=mark;
	if (mark==X){
		ttt_print_x(index);
	}
	if (mark==O){
		ttt_print_o(index);
	}
}

Game_state ttt_game_status(){
		if (game_board[0] == game_board[1] && game_board[1] == game_board[2] && game_board[0]!=NONE){
			if(game_board[0]==X){return X_WIN;}
			if(game_board[0]==O){ return O_WIN;}
		}

		else if (game_board[3] == game_board[4] && game_board[4] == game_board[5] && game_board[3]!=NONE){
			if(game_board[3]==X){return X_WIN;}
			if(game_board[3]==O){ return O_WIN;}
		}

		else if (game_board[6] == game_board[7] && game_board[7] == game_board[8] && game_board[6]!=NONE){
			if(game_board[6]==X){return X_WIN;}
			if(game_board[6]==O){ return O_WIN;}
		}

		else if (game_board[0] == game_board[3] && game_board[3] == game_board[6]&& game_board[0]!=NONE){
			if(game_board[0]==X){return X_WIN;}
			if(game_board[0]==O){ return O_WIN;}
		}

		else if (game_board[1] == game_board[4] && game_board[4] == game_board[7] && game_board[1]!=NONE){
			if(game_board[1]==X){return X_WIN;}
			if(game_board[1]==O){ return O_WIN;}
		}

		else if (game_board[2] == game_board[5] && game_board[5] == game_board[8] && game_board[2]!=NONE){
			if(game_board[2]==X){return X_WIN;}
			if(game_board[2]==O){ return O_WIN;}
		}

		else if (game_board[0] == game_board[4] && game_board[4] == game_board[8] && game_board[0]!=NONE){
			if(game_board[0]==X){return X_WIN;}
			if(game_board[0]==O){ return O_WIN;}
		}

		else if (game_board[2] == game_board[4] && game_board[4] == game_board[6] && game_board[2]!=NONE){
			if(game_board[2]==X){return X_WIN;}
			if(game_board[2]==O){ return O_WIN;}
		}
		else{
			int j=0;
			for (int i=0; i<9;i++){
				if (game_board[i]!=NONE){
					j++;
				}
			}
			if(j==9){return TIE;}
		}
		return NO_WIN;
}

void ttt_winner(Game_state game_state){
	char* winner;
	if (game_state==X_WIN){
		winner="Player 1 ( X )";
	}
	if (game_state==O_WIN){
		winner="Player 2 ( O )";
	}
	oled_clear_all();
	oled_pos(2,4);
	oled_print(winner);
	oled_print(" won! ");
}

void ttt_tie(){
	oled_clear_all();
	oled_pos(2,4);
	oled_print("It's a tie!");
}

void ttt_main(direction dir, uint8_t* index, Turn* turn){
	
	switch (dir){
	case(LEFT) :
		if (*index!=0 && *index!=3 && *index!=6){
			ttt_erase_line(*index);
			*index -=1;
			ttt_print_line(*index);
			_delay_ms(200);
		}
		break;
	case(RIGHT) :
		if (*index!=2 && *index!=5 && *index!=8){
			ttt_erase_line(*index);
			*index +=1;
			ttt_print_line(*index);
			_delay_ms(200);
		}
		break;
	case(UP) :
		if (*index!=0 && *index!=1 && *index!=2){
			ttt_erase_line(*index);
			*index -=3;
			ttt_print_line(*index);
			_delay_ms(200);
		}
		break;
	case(DOWN) :
		if (*index!=6 && *index!=7 && *index!=8){
			ttt_erase_line(*index);
			*index +=3;
			ttt_print_line(*index);
			_delay_ms(200);
		}
		break;
	case(PRESSED) :
		if (game_board[*index]==NONE){
			switch(turn->turn){
				case(X_PLAY):
					game_board[*index]=X;
					ttt_print_x(*index);
					Game_state game_status = ttt_game_status();
					if (game_status==X_WIN){
						_delay_ms(200);
						ttt_winner(X_WIN);
						break;
					}
					if (game_status==TIE){
						_delay_ms(200);
						ttt_tie();
						break;
					}
					turn->turn = O_PLAY;
					ttt_erase_line(*index);
					*index=0;
					ttt_print_line(*index);
					_delay_ms(200);
					break;

				case(O_PLAY):
					game_board[*index]=O;
					ttt_print_o(*index);
					game_status = ttt_game_status();
					if (game_status==O_WIN){
						_delay_ms(200);
						ttt_winner(O_WIN);
						break;
					}
					if (game_status==TIE){
						_delay_ms(200);
						ttt_tie();
						break;
					}
					turn->turn = X_PLAY;
					ttt_erase_line(*index);
					*index=0;
					ttt_print_line(*index);
					_delay_ms(200);
					break;
				break;
			}
		}
	case(NEUTRAL) :
		break;
	case(BACK) :
		break;
	default :
		break;
	}
}


void ttt_menu_game(){
	oled_clear_all();
	_delay_ms(200);
	ttt_grid();
	uint8_t* current_index=0;
	Turn* turn = X_PLAY;
	pos_js joystick;
	adc_calibrate_joystick(&joystick);
	ttt_print_line(current_index);
	while(adc_joystick_dir(&joystick)!=BACK){
		adc_joystick_pos(&joystick);
		ttt_main(adc_joystick_dir(&joystick),&current_index,&turn);

	}
	for (int i = 0; i<9;i++){game_board[i]=NONE;}

}
