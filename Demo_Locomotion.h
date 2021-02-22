//This code was written by Jonathan Harris of Plainview Robotics and was uploaded on Feb 13, 2021

int bias;
int right_wheel = 0;
int left_wheel = 1;
/*
This function is used to initiate the gyros for the drive and turn functions
I would advise using 30 loops but any more than that is really not neccesary
The calculate bias should be called right BEFORE wait for light and then if needed 
you can call it again about halfway through but if it is still is inacurate you need to 
adjust the drive function, not add more loops
*/
void calculate_bias(int loops){
    int i;
    int bias_mass = 0;
    mav(right_wheel,0);
    mav(left_wheel,0);
    msleep(100);
    for(i = 0; i < loops; i++){
        bias_mass = bias_mass + gyro_z();
        mav(right_wheel,0);
        mav(left_wheel,0);
        msleep(5);
    }
    bias = bias_mass / loops;
}

/*
a drive for the demobot chasis using the gyroscope to maintain a straight line while driving 
as well as correcting if external sources disrupt the path. The drive is much more exact than a
reckless drive just using motor speed but it is not 100% accurate. Every sensor has noise in the value
reading so using square ups and linefollowing at times as well as other solid methods of detection are still advised.
I WOULD NOT advise using the maximum speed output of the wheels when calling the function. The way the wheels correct 
is by dropping the speed of one wheel and speeding up the other, so if the wheel are already at max speed it cant correct properly.
*/
//DISTANCE IS MEASURED IN CM
void drive (int speed, int distance){
    
    float theta = 0;
    float error = 0;
    float target = 0;
    cmpc(right_wheel);
    cmpc(left_wheel);
    while((abs(gmpc(right_wheel)) + abs(gmpc(left_wheel)))/2 < distance * 77){
        
        mav(right_wheel,speed + error * 0.1);
        mav(left_wheel,speed - error * 0.1);
        msleep(15);
        
        theta = theta + (gyro_z() - bias);
        error = (target - (theta));
        
        
    }
    mav(right_wheel,0);
    mav(left_wheel,0);
    msleep(20);
    
}

/*
turns for the demobot chassis using the gyroscope. THE TARGET IS NOT IN DEGREES and you will 
need to take the time to figure out what values get you the turns you need. Another thing to note
is that the bot WILL turn until it reaches its target so if something impairs its path it will get stuck on the turn.
Although the turn is fairly accurate it is not 100% so you will need to check your rotation every once in a while with a square up.
*/

void right(int speed, int target){
    
	float theta = 0;
    	while(theta > -target){
	
        	mav(right_wheel,-speed);
        	mav(left_wheel,speed);
        	msleep(10);
        	theta = theta + ((gyro_z() - bias) * 0.03);
    	}
    	mav(right_wheel,0); 
    	mav(left_wheel,0);
   	msleep(20);
}

//A more advanced turn for the lego chasis
void advanced_right(int speedl, int speedr, int target){
    
    float theta = 0;
    //float start_time = 0;
    //float end_time = 0;
    while(theta > -target){
        msleep(15);
     
        //start_time = seconds();
        
        mav(0,-speedr);
        mav(1,speedl);
        msleep(10);
        
        //end_time = seconds() - start_time;
        theta = theta + ((gyro_z() - bias) * 0.03);
        printf("theta %f\n",theta);
        
    }
    mav(0,0); 
    mav(1,0);
    msleep(20);
    
}
void left(int speed, int target){
     
	float theta = 0;
    
    	while(theta < target){
        
        	mav(right_wheel,speed);
        	mav(left_wheel,-speed);
        	msleep(10);
        
        	theta = theta + ((gyro_z() - bias)  * 0.03);
        
    	}
    	mav(right_wheel,0);
    	mav(left_wheel,0);
    	msleep(20);
}
//a more advanced turn for the lego chasis
void advanced_left(int speedl, int speedr, int target){
    
    float theta = 0;
    //float start_time = 0;
    //float end_time = 0;
    while(theta < target){
        msleep(15);
     
        //start_time = seconds();
        
        mav(0,speedr);
        mav(1,-speedl);
        msleep(10);
        
        //end_time = seconds() - start_time;
        theta = theta + ((gyro_z() - bias)  * 0.03);
        printf("theta %f\n",theta);
        
    }
    mav(0,0);
    mav(1,0);
    msleep(20);
    
}

//A smooth line follow made for use with a regular tophat sensor
//DISTANCE IS MEASURED IN CM
void line_follow(int port, int speed , int distance){
	
	int grey_value = 2000; //This grey value needs to be the average value that is directly between the read white value and the read black value of the tophat sensor
	int speed_change;
	cmpc(right_wheel);
	int error = 0;  
	while(gmpc(right_wheel) < distance * 77){
		  error = grey_value-analog(port);
		  speed_change= error*0.2;
 		  mav(right_wheel ,speed - speed_change);
 		  mav(left_wheel ,speed + speed_change);   
	  }
    	mav(right_wheel, 0);
   	mav(left_wheel, 0);
   	msleep(100);
} 
