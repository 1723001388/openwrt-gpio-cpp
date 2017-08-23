// Copyright YummyCarrot(huyuzhe)

// My Github Location:
// https://github.com/CRThu

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

// http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#ifndef _GPIO_H_
#define _GPIO_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <iostream>
#include <string>

using namespace std;

// SetPinInit
#define PIN_INIT_FILE_OPEN_ERROR -1
#define PIN_INIT_FILE_WRITE_ERROR -2
#define PIN_INIT_FILE_CLOSE_ERROR -3
#define PIN_INIT_SUCCESS 0
// SetPinDir
#define SET_DIR_FILE_OPEN_ERROR -4
#define SET_DIR_FILE_WRITE_ERROR -5
#define SET_DIR_FILE_CLOSE_ERROR -6
#define SET_DIR_SUCCESS 0
// SetPinValue
#define SET_VALUE_FILE_OPEN_ERROR -7
#define SET_VALUE_FILE_WRITE_ERROR -8
#define SET_VALUE_FILE_CLOSE_ERROR -9
#define SET_VALUE_SUCCESS 0
// SetPin
#define SET_PIN_SUCCESS 0
// File Operation
#define FILE_OPEN_ERROR -1
#define FILE_READ_EOF 0
#define FILE_READ_ERROR -1
#define FILE_WRITE_ERROR -1
#define FILE_CLOSE_ERROR -1

enum Pin_Value {
    GET_VALUE_FILE_OPEN_ERROR = -1,
    GET_VALUE_FILE_READ_ERROR = -2,
    GET_VALUE_FILE_READ_EOF = -3,
    GET_VALUE_FILE_CLOSE_ERROR = -4,
    PIN_LOW = 0,
    PIN_HIGH = 1
};

enum Pin_Direction {
    GET_DIR_FILE_OPEN_ERROR = -1,
    GET_DIR_FILE_READ_ERROR = -2,
    GET_DIR_FILE_READ_EOF = -3,
    GET_DIR_FILE_CLOSE_ERROR = -4,
    PIN_IN = 0,
    PIN_OUT = 1
};

class GPIO
{
public:
    // Set*
    void SetPinMux(string get_group);	// mt7688_pinmux set $ephy$ gpio
    int SetPinInit(string type);	// Init Export/UnExport
    int SetPinExport();	// echo $PinNum$ > /sys/class/gpio/export
    int SetPinUnExport();	// echo $PinNum$ > /sys/class/gpio/unexport
    int SetPinDir(Pin_Direction get_Direction);	// echo $in/out$ > /sys/class/gpio/gpio$PinNum$/direction
    int SetPinValue(Pin_Value get_Value);	// echo $0/1$ > /sys/class/gpio/gpio$PinNum$/value
    int SetPin(string get_PinNum, Pin_Direction get_Direction, Pin_Value get_Value);	// Export + SetPinDir + SetPinValue
    int DelPin();	// unexport
    // Get*
    void GetPinMux();	// mt7688_pinmux get
    Pin_Direction GetPinDir();	// cat /sys/class/gpio/gpio$PinNum$/direction
    Pin_Value GetPinValue();	// cat /sys/class/gpio/gpio$PinNum$/value
private:
    string group;	// SetPinMux
    string PinNum;		// SetPin
    Pin_Direction Direction;	// SetPinDir
    Pin_Value Value;	// SetPinValue
};

#endif // !_GPIO_H_
