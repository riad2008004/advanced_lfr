#include <Arduino.h>
#include "case_detection.h"

const int case_length = 11;

// defining cases
#define NORMAL_CASES 0
#define LEFT_TURN_CASES 1
#define DANGER_LEFT_CASES 2
#define RIGHT_TURN_CASES 3
#define DANGER_RIGHT_CASES 4
#define FULL_BLACK_CASES 5
#define FULL_WHITE_CASES 6
#define Y_CASES 7
#define INVERT_CASES 8
#define SHARP_RIGHT_CASES 9
#define SHARP_LEFT_CASES 10

/*--------- Global variables --------------*/
uint8_t sensorReadingArray[100]; // for accessing memory as an array
extern struct Memory sensorMemory;
extern bool isInvert;
unsigned int inverseCases = 0;
unsigned int inf_case_count = 0;

/*--------- External Global Variables -----*/

extern int configureMenu[12];

/*------- External Functions --------------*/
extern void memoryGetArray(struct Memory *m, uint8_t arr[]);
extern void displayCaseDetector(uint8_t case_count_arr[]); // from display to display case detection data
extern void Stop(double del);
uint8_t sensorNormalCases[] = {
    // Two sensor cases
    0b00011000,
    0b00110000,
    0b01100000,
    0b00001100,
    0b00000110,
    // One sensor cases
    0b00010000,
    0b00100000,
    0b01000000,
    0b00001000,
    0b00000100,
    0b00000010,
    // Three sensor cases
    0b00111000, // 3 sensors are found in normal line when test
    0b01110000, // 3 sensors are found in normal line when test
    // 0b11100000,
    // 0b00000111,
    0b00001110, // 3 sensors are found in normal line when test
    0b00011100, // 3 sensors are found in normal line when test
    // C_B_RIAD
};
uint8_t sensorLeftTurnCases[]{
    // 90 degree turn cases
    0b11110000,
    0b11111000,
    0b11111100,
    0b11111110, // for eee day ruet
    // less than 90 degree turn cases
    // * robot in center
    0b10011000,
    0b11011000,
    // * robot in slightly left
    0b10110000,
    0b10111000, // 3 sensor
    // * robot in slightly right
    0b10001100,
    0b11001100,
    0b01101100,
    0b11101100,
    0b10011100, // 3 sensor
    0b11011100, // 3 sensor

};
uint8_t sensorDangerLeft[] = {
    0b11100000,
    0b11000000,
    0b10000000,
};

uint8_t sensorRightTurnCases[]{
    // 90 degree turn casaes
    0b00001111,
    0b00011111,
    0b00111111,
    0b01111111, // ex
    // Less than 90 degree turn cases
    //
    // * robot in center
    0b00011001,
    0b00011011,
    // * robot in slightly left
    0b00110001,
    0b00110011,
    0b00110111,
    0b00110110,
    0b00111001, // 3 sensor
    0b00111011, // 3 sensor
    // * robot in slightly right
    0b00001101,
    0b00011101, // 3 sensor

};
uint8_t sharp_left_cases[] = {
    0b11000000,
    0b11100000,
    0b11110000,
    0b11111000,
    0b11111100,
    0b11111110,
};
uint8_t sharp_right_cases[] = {
    0b00000011,
    0b00000111,
    0b00001111,
    0b00011111,
    0b00111111,
    0b01111111,
};

uint8_t y_cases[] = {
    0b10000001,
    0b11000001,
    0b10000011,
    0b11000011,
    0b00111100,
    0b01111100,
    0b01111110,
    0b11101110,
    0b01110111,
    0b10000111,
    0b11100001,
    0b11000110,
    0b01100011,
};

uint8_t sensorDangerRight[] =
    {
        0b00000001,
        0b00000011,
        0b00000111,
};

void count_cases(uint8_t case_count_arr[], int start, int end)
{
    inverseCases = 0;
    // Update the memory with latest data to count cases from it
    memoryGetArray(&sensorMemory, sensorReadingArray);

    for (int i = 0; i < case_length; i++)
    {
        case_count_arr[i] = 0;
    }

    // Enumerate cases
    for (int i = start; i < end; i++)
    {
        for (unsigned int j = 0; j < sizeof(sensorNormalCases) / sizeof(sensorNormalCases[0]); j++)
        {
            if (sensorReadingArray[i] == sensorNormalCases[j])
                case_count_arr[NORMAL_CASES]++; // Normal cases
        }
        for (unsigned int j = 0; j < sizeof(sensorLeftTurnCases) / sizeof(sensorLeftTurnCases[0]); j++)
        {
            if (sensorReadingArray[i] == sensorLeftTurnCases[j])
                case_count_arr[LEFT_TURN_CASES]++; // Left turn cases
        }
        for (unsigned int j = 0; j < sizeof(sensorDangerLeft) / sizeof(sensorDangerLeft[0]); j++)
        {
            if (sensorReadingArray[i] == sensorDangerLeft[j])
                case_count_arr[DANGER_LEFT_CASES]++; // Danger Left
        }
        for (unsigned int j = 0; j < sizeof(sensorRightTurnCases) / sizeof(sensorRightTurnCases[0]); j++)
        {
            if (sensorRightTurnCases[j] == sensorReadingArray[i])
                case_count_arr[RIGHT_TURN_CASES]++; // Right turn cases
        }

        for (unsigned int j = 0; j < sizeof(sensorDangerRight) / sizeof(sensorDangerRight[0]); j++)
        {
            if (sensorDangerRight[j] == sensorReadingArray[i])
                case_count_arr[DANGER_RIGHT_CASES]++; // Danger Right
        }
        for (unsigned int j = 0; j < sizeof(y_cases) / sizeof(y_cases[0]); j++)
        {
            if (sensorReadingArray[i] == y_cases[j])
                case_count_arr[Y_CASES]++; // Y cases
        }
        for (unsigned int j = 0; j < sizeof(sharp_right_cases) / sizeof(sharp_right_cases[0]); j++)
        {
            if (sensorReadingArray[i] == sharp_right_cases[j])
                case_count_arr[SHARP_RIGHT_CASES]++; // 90 right cases
        }
        for (unsigned int j = 0; j < sizeof(sharp_left_cases) / sizeof(sharp_left_cases[0]); j++)
        {
            if (sensorReadingArray[i] == sharp_left_cases[j])
                case_count_arr[SHARP_LEFT_CASES]++; // 90 left cases
        }
        if (sensorReadingArray[i] == 0b11111111) // Black cases
            case_count_arr[FULL_BLACK_CASES]++;
        if (sensorReadingArray[i] == 0b00000000) // White cases
            case_count_arr[FULL_WHITE_CASES]++;
        if (configureMenu[4] == 1)
        {
            if (sensorReadingArray[i] == 0b11100001     // ----------------
                || sensorReadingArray[i] == 0b10000111  // ----------------
                || sensorReadingArray[i] == 0b11000011  // ----------------
                || sensorReadingArray[i] == 0b11000111  // ----------------
                || sensorReadingArray[i] == 0b11100011) // ----------------

            {
                inverseCases++;
            }
        }
    }
}

String detect_case()
{
    // Check the previous situation before unusual things happened
    uint8_t case_count_arr_before[case_length];
    uint8_t case_count_arr_after[case_length];
    count_cases(case_count_arr_before, 50, 100);
    count_cases(case_count_arr_after, 0, 50);

    if (inverseCases > 15)
    {
        inverseCases = 0;
        isInvert ^= 1;
        return "N";
    }
    //---------------- uncomment for debugging ---------------
    if (configureMenu[11] == 1 || configureMenu[11] == 2)
    {
        Stop(100);
        displayCaseDetector(case_count_arr_before);
        delay(5000);
        displayCaseDetector(case_count_arr_after);
        delay(5000);
    }
    //--------------------------------------------------------

    if (case_count_arr_before[NORMAL_CASES] > 10 && case_count_arr_after[FULL_BLACK_CASES] > 10 &&
        case_count_arr_after[NORMAL_CASES] > 10 && case_count_arr_after[FULL_WHITE_CASES] < 5)
    {
        return "+";
    }
    if (case_count_arr_before[NORMAL_CASES] > 20 && case_count_arr_after[FULL_BLACK_CASES] > 10 &&
        case_count_arr_after[FULL_WHITE_CASES] > 5)
    {
        return "T";
    }
    if (case_count_arr_before[NORMAL_CASES] > 20 && case_count_arr_after[NORMAL_CASES] > 8 &&
        case_count_arr_after[SHARP_RIGHT_CASES] > 15 && case_count_arr_after[FULL_WHITE_CASES] < 5)
    {
        return "TR";
    }
    if (case_count_arr_before[NORMAL_CASES] > 20 && case_count_arr_after[NORMAL_CASES] > 8 &&
        case_count_arr_after[SHARP_LEFT_CASES] > 15 && case_count_arr_after[FULL_WHITE_CASES] < 5)
    {
        return "TL";
    }
    if (case_count_arr_before[NORMAL_CASES] > 10 && (case_count_arr_after[Y_CASES] + case_count_arr_before[Y_CASES]) > 15)
    {
        return "Y";
    }
    if ((case_count_arr_before[DANGER_LEFT_CASES] + case_count_arr_after[DANGER_LEFT_CASES]) > 15 &&
        case_count_arr_after[FULL_WHITE_CASES] > 5)
    {
        return "P_L"; // PID-Failure in left side
    }
    if ((case_count_arr_before[DANGER_RIGHT_CASES] + case_count_arr_after[DANGER_RIGHT_CASES]) > 15 &&
        case_count_arr_after[FULL_WHITE_CASES] > 5)
    {
        return "P_R"; // PID-Failure in right side
    }
    if (case_count_arr_after[SHARP_LEFT_CASES] > 15 && case_count_arr_before[NORMAL_CASES] > 15 &&
        case_count_arr_after[FULL_WHITE_CASES] < 5)
    {
        return "C_L"; // for sharp curb Left side
    }
    if (case_count_arr_after[SHARP_RIGHT_CASES] > 15 && case_count_arr_before[NORMAL_CASES] > 15 &&
        case_count_arr_after[FULL_WHITE_CASES] < 5)
    {
        return "C_R"; // for sharp curb Right side
    }

    if ((case_count_arr_after[LEFT_TURN_CASES] + case_count_arr_before[LEFT_TURN_CASES]) > 10 &&
        (case_count_arr_after[LEFT_TURN_CASES] + case_count_arr_before[LEFT_TURN_CASES]) >
            (case_count_arr_after[RIGHT_TURN_CASES] +
             case_count_arr_before[RIGHT_TURN_CASES]))
    {
        return "L";
    }
    if ((case_count_arr_after[RIGHT_TURN_CASES] + case_count_arr_before[RIGHT_TURN_CASES]) > 10 &&
        (case_count_arr_after[RIGHT_TURN_CASES] + case_count_arr_before[RIGHT_TURN_CASES]) >
            (case_count_arr_after[LEFT_TURN_CASES] +
             case_count_arr_before[LEFT_TURN_CASES]))
    {

        return "R";
    }

    if (case_count_arr_after[FULL_WHITE_CASES] > 20 && case_count_arr_before[NORMAL_CASES] > 20)
    {
        return "L_B"; // Line break
    }

    if (case_count_arr_after[FULL_BLACK_CASES] > 35)
    {
        return "B";
    }

    return "N";
}