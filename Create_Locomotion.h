//This file waw written by Jonathan Harris from Plainview Robotics and was first uploaded on 2/11/2021


//NOTICE: this library as of now is not the entirety of the create locomotion functions. It is missing all create gyro functions and create line follow functions. 
//they will be added as soon as possible

//This command is to lock both motors and create(roomba) drive wheels between drive commands and other locomotion functions
void full_lock(int sleep){
   
    create_drive_direct(0,0);
    msleep(sleep/2);
    motor(0,0);
    msleep(sleep/2);
    
}

//A raw non-gyro drive for the create(roomba) that uses the in built distance detection inside the romba
//The romba drive detection is in cm but it is not very acurate or precise
void raw_create_drive_forward(int speed,int distance)
{
    set_create_distance(0);
    while(get_create_distance() > -distance)
    {
        create_drive_direct(-speed,-speed);
        msleep(15);
    }  
}

//A raw non-gyro drive backwards for the create(roomba) that uses the in built distance detection inside the romba
//The romba drive detection is in cm but it is not very acurate or precise
void raw_create_drive_backwards(int speed, int distance)
{
    set_create_distance(0);
    while(get_create_distance() < distance)
    {
        
        create_drive_direct(speed,speed);
        msleep(15);
        
    }
    
}

//A raw non-gyro turn right for the create(roomba) that uses the in built turn detection inside the romba
//The romba turn detection is in degrees but it is not very acurate but it is precise enough if you find the right value and square up enough
void raw_create_turn_right(int deg,int speed)
{
    
    set_create_normalized_angle(0);
    while(get_create_normalized_angle() > -deg)
    {
        create_spin_CW(speed);
        printf("the angle of this turn is = %d \n",get_create_normalized_angle());
    }
}

//A raw non-gyro turn left for the create(roomba) that uses the in built turn detection inside the romba
//The romba turn detection is in degrees but it is not very acurate but it is precise enough if you find the right value and square up enough
void create_turn_left(int deg,int speed)
{
    
    set_create_normalized_angle(0);
    while(get_create_normalized_angle() < deg)
    {
        create_spin_CCW(speed);
        printf("the angle of this turn is = %d \n",get_create_normalized_angle());
    }
}

int bias;
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
a drive for the create using the gyroscope to maintain a straight line while driving 
as well as correcting if external sources disrupt the path. The drive is much more exact than a
reckless drive just using create_drive_direct but it is not 100% accurate. Every sensor has noise in the value
reading so using square ups and linefollowing at times as well as other solid methods of detection are still advised.
I WOULD NOT advise using the maximum speed output of the wheels when calling the function. The way the wheels correct 
is by dropping the speed of one wheel and speeding up the other, so if the wheel are already at max speed it cant correct properly.
*/
//DISTANCE IS MEASURED IN CM
void drive (int speed, int distance){
    
    float theta = 0;
    float error = 0;
    float target = 0;
    set_create_distance(0);
    while(get_create_distance() < distance){
       
        create_drive_direct(speed-error*0.1, speed+error*0.1);
        msleep(15);
        theta = theta + (gyro_z() - bias);
        error = (target - (theta));
        
        
    }
    create_drive_direct(0,0);
    msleep(20);
    
}

/*
turns for the create using the gyroscope. THE TARGET IS NOT IN DEGREES and you will 
need to take the time to figure out what values get you the turns you need. Another thing to note
is that the bot WILL turn until it reaches its target so if something impairs its path it will get stuck on the turn.
Although the turn is fairly accurate it is not 100% so you will need to check your rotation every once in a while with a square up.
*/

void right(int speed, int target){
    
    float theta = 0;
    while(theta > -target){
      
        create_drive_direct(speed, -speed);
        msleep(10); 
        theta = theta + ((gyro_z() - bias) * 0.03);
        
    }
    create_drive_direct(0,0);
    msleep(20);
    
}

void left(int speed, int target){
    
    float theta = 0; 
    while(theta < target){
        
        create_drive_direct(-speed, speed);
        msleep(10);
        theta = theta + ((gyro_z() - bias)  * 0.03);
        
    }
    create_drive_direct(0,0);
    msleep(20);
    
}
