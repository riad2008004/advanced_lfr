#ifndef _MOTOR_CONTROL
#define _MOTOR_CONTROL

void motorSetup();
void motorTestAuto();
void motorCalibrate();
void Forward(double del, int vel);
void Backward(double del, int vel);
void Right(double del, int vel);
void Left(double del, int vel);
void Stop(double del);
void Run();
void PLeft(double del,int vel);
void PRight(double del,int vel);
void Tleft();
void Tright();
void PIDright();
void PIDleft();
void BreakR();
void BreakL();
void BreakF(double del,int vel);
void detection();
void sonarDrive();
void PIDRun();
void handle_case(String case_str);
void doura();
void handleObject();
void UTurn();
#endif // _MOTOR_CONTROL