#include "PID_control.h"

void PID_Init(PID* pid,float P,float I,float D,u16 set_point)//PID������ʼ��
{
	pid->LastError=0;
	pid->PrevError=0;
	pid->Proportion=P;
	pid->Integral=I;
	pid->Derivative=D;
	pid->SetPoint=set_point;
}

s16 get_iIncpid(PID* pid,u16 set_point,u16 this_point)//PID�����㷨������ֵΪPID����
{
	s16 iError, iIncpid; 
	pid->SetPoint=set_point;
	iError=pid->SetPoint-this_point;
	iIncpid=pid->Proportion*iError
	-pid->Integral*pid->LastError
	+pid->Derivative*pid->PrevError;
	pid->PrevError=pid->LastError;
	pid->LastError=iError;
	
	return iIncpid;
}

void PID_error_clear(PID* pid)//PID�������
{
	pid->LastError=0;
	pid->PrevError=0;
}

void PID_reset_point(PID* pid,u16 set_point)
{
	pid->SetPoint=set_point;
}
