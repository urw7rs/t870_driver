#ifndef MOTOR_DRIVER_H
#define MOTOR_DRIVER_H

/* frequency in hertz */
int init(int freq);

/* set twist */
int set_twist(int file, float w, float v);


#endif
