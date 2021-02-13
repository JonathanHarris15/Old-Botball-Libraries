//servo function by Jacob of Noble High School (written on August 8,2019)
void servo(int port, int position, int speed){   

    int current = get_servo_position(port);

    if(position > 2047){

        position = 2047;

    } 
    if(position < 0){

        position = 0;

    }   

    while(current <= position-speed || current >= position+speed){ 

        if(current < position){

            current += speed;
           
        }
        if(current > position){

            current -= speed;

        }
        set_servo_position(port, current);
        msleep(2);
    }

    set_servo_position(port,position);
    
} 

//this is a modified version of Jacobs servo function for use with threads. dont call this normally and it is only used in the function bellow.
int thread_servo_port;
int thread_servo_position;
int thread_servo_speed;
void bare_servo(){   //this servo has been modified to be used in threads

    int current = get_servo_position(thread_servo_port);

    if(thread_servo_position > 2047){

        thread_servo_position = 2047;

    } 
    if(thread_servo_position < 0){

        thread_servo_position = 0;

    }   

    while(current <= thread_servo_position-thread_servo_speed || current >= thread_servo_position+thread_servo_speed){ 

        if(current < thread_servo_position){

            current += thread_servo_speed;
           
        }
        if(current > thread_servo_position){

            current -= thread_servo_speed;

        }
        set_servo_position(thread_servo_port, current);
        msleep(2);
    }

    set_servo_position(thread_servo_port,thread_servo_position);
    
} 
//This function was written by Jonathan Harris on Feb 13, 2021
//this double servo is untested cause I wrote it without using a wallaby or wombat but I cant see anything wrong with it
//DONT USE THIS COMMAND UNLESS YOU ARE COMFORTABLE WITH THREADS AND HOW THEY WORK, YOU WILL NOT GET THE RESULTS YOU WANT EVERYTIME!!    
void double_servo_thread(int port1, int pos1, int speed1, int port2, int pos2, int speed2){
    
    //defining parameters for the second thread function
    thread_servo_port = port2;
    thread_servo_position = pos2;
    thread_servo_speed = speed2;
    
    thread second_servo;
    second_servo = thread_create(bare_servo);
    
    thread_start(second_servo);
    servo(port1, pos1, speed1);
    thread_destroy(second_servo);
    
    
    
}
