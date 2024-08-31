#include "zf_common_headfile.h"
#include "my_thread.h"
 


uint8 task1_finish_flag = 0;
void task1()
{  
    Control_Mode = 3;
    angle_turn = 0;
	if(abs(Gyro_Angle.Zdata - angle_now - angle_turn)<5)
    {
        task1_finish_flag = 1;
    }
}  

void task2() {  
    printf("Task 2 is running...\n");  
    sleep(1); // Simulate work  
}  

int main1111() {  
    TaskState state = TASK_IDLE;  
    int counter = 0;  

    while(1) {  
        switch(state){  
            case TASK_IDLE:  
                printf("Idle...\n");  
                state = TASK_1_RUNNING; // Change state to the first task  
                break;  

            case TASK_1_RUNNING:  
                task1();  
                state = TASK_2_RUNNING; // Move to the next task  
                break;  

            case TASK_2_RUNNING:  
                task2();  
                state = TASK_IDLE; // Go back to idle  
                break;  
        }  

        counter++;  
        if(counter >= 10) {  
            break; // Exit after 10 iterations  
        }  
    }  

    printf("Completed execution.\n");  
    return 0;  
}