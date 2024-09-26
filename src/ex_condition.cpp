#include <Arduino.h>
#include "ex_condition.h"
#include "motor.h"

/*
Please condider the instruction while setting the counter array
1. Plus counter can take only 'N' 'R' 'L'
2. TL counter can take only 'N' 'L'
3. TR counter can take only 'N' 'R'
4. T counter can take only 'R' 'L'
5. LB counter can take only 'B' 'F'
*/

//------------------Set_Up this array for counter operation--------------------

char Plus_counter_action_array[] = {'N', 'R', 'L', 'R', 'N', 'R', 'L', 'R'};
char TL_counter_action_array[] = {'N', 'L', 'L', 'N', 'N', 'L', 'L', 'N'};
char TR_counter_action_array[] = {'N', 'R', 'R', 'N', 'N', 'R', 'R', 'N'};
char T_counter_action_array[] = {'R', 'R', 'L', 'L', 'L', 'L', 'R', 'R'};
char LB_counter_action_array[] = {'B', 'B', 'F', 'B', 'F', 'B', 'F', 'F'};

//-------------------------------external_variables & functions-----------------
extern void Tright();
extern void Tleft();
extern void UTurn();

//-------------------------------Counter Variable------------------------------
int Plus_Counter = 0;
int TL_Counter = 0;
int TR_Counter = 0;
int T_Counter = 0;
int LB_Counter = 0;

void Plus_counter_action()
{
    Plus_Counter = Plus_Counter + 1;

    int length = sizeof(Plus_counter_action_array) / sizeof(Plus_counter_action_array[0]);
    if (Plus_Counter <= length)
    {
        if (Plus_counter_action_array[Plus_Counter - 1] == 'N')
            return;
        else if (Plus_counter_action_array[Plus_Counter - 1] == 'R')
        {
            BreakF(25, 250);
            Tright();
        }
        else if (Plus_counter_action_array[Plus_Counter - 1] == 'L')
        {
            BreakF(25, 250);
            Tleft();
        }
        else
            return;
    }
    else
        return;
}

void TL_counter_action()
{
    TL_Counter = TL_Counter + 1;

    int length = sizeof(TL_counter_action_array) / sizeof(TL_counter_action_array[0]);
    if (TL_Counter <= length)
    {
        if (TL_counter_action_array[TL_Counter - 1] == 'N')
            return;
        else if (TL_counter_action_array[TL_Counter - 1] == 'L')
            Tleft();
        else
            return;
    }
    else
        return;
}

void TR_counter_action()
{
    TR_Counter = TR_Counter + 1;

    int length = sizeof(TR_counter_action_array) / sizeof(TR_counter_action_array[0]);
    if (TR_Counter <= length)
    {
        if (TR_counter_action_array[TR_Counter - 1] == 'N')
            return;
        else if (TR_counter_action_array[TR_Counter - 1] == 'R')
            Tright();
        else
            return;
    }
    else
        return;
}

void T_counter_action()
{
    T_Counter = T_Counter + 1;

    int length = sizeof(T_counter_action_array) / sizeof(T_counter_action_array[0]);
    if (T_Counter <= length)
    {
        if (T_counter_action_array[T_Counter - 1] == 'N')
            return;
        else if (T_counter_action_array[T_Counter - 1] == 'R')
            Tright();
        else if (T_counter_action_array[T_Counter - 1] == 'L')
            Tleft();
        else
            return;
    }
    else
        return;
}

void LB_counter_action()
{
    LB_Counter = LB_Counter + 1;

    int length = sizeof(LB_counter_action_array) / sizeof(LB_counter_action_array[0]);
    if (LB_Counter <= length)
    {
        if (LB_counter_action_array[LB_Counter - 1] == 'F')
            return;
        else if (LB_counter_action_array[LB_Counter - 1] == 'B')
        {
            UTurn();
            return;
        }
        else
            return;
    }
    else
        return;
}