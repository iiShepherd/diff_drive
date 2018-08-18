#include <ros/ros.h>
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <thread>
#include <chrono>
#include  "robo/joystickcmd.h"

//Uint32 timeLastMs = 0;
//Uint32 timeCurrentMs  = 0;
//Uint32 timeDeltaMs = 0;
//Uint32 timeAccumulatedMs = 0;
//Uint32 timeStepMs = 1000.f / 120;



struct var
{

	//ROS
	ros::Publisher joy_pub;

	//custom message
	robo::joystickcmd joystick_cmd;
	

}param;


void cmd_foward(SDL_Joystick* joystick)
{
	SDL_JoystickUpdate();
	SDL_PumpEvents();

	param.joystick_cmd.jaxis_1 = SDL_JoystickGetAxis(joystick, 1);
	param.joystick_cmd.jaxis_0 = SDL_JoystickGetAxis(joystick, 0);
	param.joystick_cmd.jbutton_0 = SDL_JoystickGetButton(joystick, 0);
	std::this_thread::sleep_for( std::chrono::milliseconds(100) );
	
}

int main(int argc, char** argv)
{
	//initiation
	ros::init(argc, argv, "Joymotion");
	ros::NodeHandle nh;

	SDL_Init(SDL_INIT_JOYSTICK);
	SDL_Joystick *joystick = SDL_JoystickOpen(0);
	if(joystick == NULL)
	{
		ROS_INFO(" NO JOYSTICK FOUND" );
	}

	param.joy_pub = nh.advertise<robo::joystickcmd>("/joystick/motion_cmd", 50);

		//timeLastMs = timeCurrentMs;
		//timeCurrentMs = SDL_GetTicks();
		//timeDeltaMs = timeCurrentMs - timeLastMs;
		//timeAccumulatedMs += timeDeltaMs;

		while (ros::ok())
		{
		cmd_foward(joystick);
		param.joy_pub.publish(param.joystick_cmd);
		ros::spinOnce();
		}		

		ROS_INFO(" EXITING..." );
		return 0;
}
