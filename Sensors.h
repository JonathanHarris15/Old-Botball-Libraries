int get_analog_value(int port, int loops){

  int mass = 0;
  int i;
  for(i = 0;i < loops; i ++){
  
    mass += analog(port);
    msleep(15);
  
  }
  return mass/loops;

}
