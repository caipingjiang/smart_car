#ifndef _CAR_CONTROL_
#define _CAR_CONTROL_

#define var_limit1				8000	//边线方差限制1
#define var_limit2				500		//边线方差限制2

void cross_move_control();
void roundabout_move_control();
void start_finish_line_control();
void ART_control();
void ramp_control();
void barrier_control();

#endif
