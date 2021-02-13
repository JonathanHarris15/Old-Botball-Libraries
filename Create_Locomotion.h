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
