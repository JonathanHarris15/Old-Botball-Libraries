int get_analog_value(int port, int loops){

  int mass = 0;
  int i;
  for(i = 0;i < loops; i ++){
  
    mass += analog(port);
    msleep(15);
  
  }
  return mass/loops;

}

int colorSense(int color, int loops) {

    camera_open_black();
    blobCount = 0;
    blobRaw = 0;
    
    while(blobCount < loops){

        camera_update();
        if(color == 0){
            if(get_object_confidence(yellow,0) > 0.4){
                blobRaw = blobRaw + 1;
            } 
        }

        if(color == 1){
            if(get_object_confidence(blue,0) > 0.4){
                blobRaw = blobRaw + 1; 
            }
        }

        if(color == 2){
            if(get_object_confidence(red,0) > 0.4){
                blobRaw = blobRaw + 1; 
            }

        }
        blobCount = blobCount + 1;

    }



    if(blobRaw > loops * 65/100){
        return 0;
    }else{
        return 1;
    }

}
