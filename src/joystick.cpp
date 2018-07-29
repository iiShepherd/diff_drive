#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <ros/ros.h>
#include  "robo/joystickcmd.h"

Uint32 timeLastMs = 0;
Uint32 timeCurrentMs  = 0;
Uint32 timeDeltaMs = 0;
Uint32 timeAccumulatedMs = 0;
Uint32 timeStepMs = 1000.f / 60;



struct var
{

	//Joystick values
	Sint16 jaxis_button_1;
	Uint8 jbutton_button_0 ;

	//ROS
	ros::Publisher joy_pub;

	//array
	robo::joystickcmd joystick_cmd;
	unsigned int num_det;
	

}param;


void cmd_foward(SDL_Joystick* joystick)
{
	SDL_JoystickUpdate();
	SDL_PumpEvents();

	param.joystick_cmd.jaxis_1 = SDL_JoystickGetAxis(joystick, 1);
	param.joystick_cmd.jbutton_0 = SDL_JoystickGetButton(joystick, 0);

	
}

int main(int argc, char** argv)
{
	//initiattion
	ros::init(argc, argv, "Joymotion");
	ros::NodeHandle nh;

	SDL_Init(SDL_INIT_JOYSTICK);
	SDL_Joystick *joystick = SDL_JoystickOpen(0);







		//timeLastMs = timeCurrentMs;
		//timeCurrentMs = SDL_GetTicks();
		//timeDeltaMs = timeCurrentMs - timeLastMs;
		//timeAccumulatedMs += timeDeltaMs;

		//while (timeAccumulatedMs >= timeStepMs)
		//{
	if(SDL_JoystickOpen(0))
{
		ROS_INFO("JOYSTICK CONNECTED");
		while(SDL_JoystickOpen(0)){

			//cmd_foward(joystick);
	SDL_JoystickUpdate();
	SDL_PumpEvents();

	param.joystick_cmd.jaxis_1 = SDL_JoystickGetAxis(joystick, 1);
	param.joystick_cmd.jbutton_0 = SDL_JoystickGetButton(joystick, 0);

			param.joy_pub = nh.advertise<robo::joystickcmd>("/joystick/motion_cmd", 100);
			ros::spinOnce();
			}
	
}
		else
{
ROS_INFO("PLEASE CONNECT A JOYSTICK");
}
	ROS_INFO(" EXITING..." );
	return 0;
}