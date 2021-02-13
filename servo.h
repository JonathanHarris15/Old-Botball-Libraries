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
