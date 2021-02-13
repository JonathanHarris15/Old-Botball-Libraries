#define yellow 0
#define red 1
#define blue 2

int get_analog_value(int port, int loops){

  int mass = 0;
  int i;
  for(i = 0;i < loops; i ++){
  
    mass += analog(port);
    msleep(15);
  
  }
  return mass/loops;

}

int colorSense(int color, int loops){ //color is which color is used

    camera_open_black();
    blobRaw = 0;
    
    int i;
    for(i = 0;i < loops; i++){
  
        camera_update();
       
        blobRaw += get_object_confidence(color,0);
          
    }



    if(blobRaw/loops > 0.65){ //this means it only has to be 65% accurate to allow for it to accept the value 
        return 0;
    }else{
        return 1;
    }

}
