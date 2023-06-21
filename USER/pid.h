#ifndef _PID_H_
#define _PID_H_

typedef struct pid_calibration {
    /*
     * struct PID_Calibration
     * 
     * Struct storing calibrated PID constants for a PID Controller
     * These are used for tuning the algorithm and the values they take are
     * dependent upon the application - (in other words, YMMV...)
     */
    double kp; // Proportional gain
    double ki; // Integral gain
    double kd; // Derivative gain
} PID_Calibration;


typedef struct pid_state {
    /*
     * struct PID_State
     * 
     * Struct storing the current state of a PID Controller.
     * This is used as the input value to the PID algorithm function, which also
     * returns a PID_State struct reflecting the adjustments suggested by the algorithm.
     * 
     * NOTE: The output field in this struct is set by the PID algorithm function, and
     * is ignored in the actual calculations.
     */
    double actual; // The actual reading as measured
    double target; // The desired reading
    double time_delta; // Time since last sample/calculation - should be set when updating state
    double previous_error;// The previously calculated error between actual and target (zero initially)
    double integral; // Sum of integral error over time
    double output; // the modified output value calculated by the algorithm, to compensate for error
} PID_State;

extern PID_State pid_iterate(PID_Calibration calibration, PID_State state);

#endif // !_PID_H_
