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
#include "gpio.h"

// Set GPIO Pin Mux
void GPIO::SetPinMux(string get_group)
{
    group = get_group;
    system(("mt7688_pinmux set " + group + " gpio").c_str());
}
// Init Export/UnExport
int GPIO::SetPinInit(string type)
{
    // File Open
    int fd = open(("/sys/class/gpio/" + type).c_str() , O_WRONLY);	// open export/unexport file
    if (fd == FILE_OPEN_ERROR)
        return PIN_INIT_FILE_OPEN_ERROR;
    
    // File Write
    if (write(fd, PinNum.c_str(), sizeof(PinNum.c_str())) == FILE_WRITE_ERROR)	// write PinNum to file
        return PIN_INIT_FILE_WRITE_ERROR;
    
    // File Close
    if (close(fd) == FILE_CLOSE_ERROR)
        return PIN_INIT_FILE_CLOSE_ERROR;
    
    return PIN_INIT_SUCCESS;
}
// Export
int GPIO::SetPinExport()
{
    return SetPinInit("export");
}
// Unexport
int GPIO::SetPinUnExport()
{
    return SetPinInit("unexport");
}
// Set Direction
int GPIO::SetPinDir(Pin_Direction get_Direction)
{
    Direction = get_Direction;

    // File Open
    int fd = open(("/sys/class/gpio/gpio" + PinNum + "/direction").c_str(), O_WRONLY);
    if (fd == FILE_OPEN_ERROR)
        return SET_DIR_FILE_OPEN_ERROR;
    
    // File Write
    if(write(fd, ((Direction == PIN_IN) ? "in" : "out"), Direction == PIN_IN ? sizeof("in") : sizeof("out")) == FILE_WRITE_ERROR)	// Write "in"/"out"
        return SET_DIR_FILE_WRITE_ERROR;
    
    // File Close
    if (close(fd) == FILE_CLOSE_ERROR)
        return SET_DIR_FILE_CLOSE_ERROR;
    
    return SET_DIR_SUCCESS;
}
// Set Value
int GPIO::SetPinValue(Pin_Value get_Value)
{ 
    Value = get_Value;
    // File Open
    int fd = open(("/sys/class/gpio/gpio" + PinNum + "/value").c_str(), O_WRONLY);
    if (fd == FILE_OPEN_ERROR)
        return SET_VALUE_FILE_OPEN_ERROR;

    // File Write
    if (write(fd, ((Value == PIN_LOW)?"0":"1"), 1) == FILE_WRITE_ERROR)	//Write 0/1
        return SET_VALUE_FILE_WRITE_ERROR;
    
    // File Close
    if (close(fd) == FILE_CLOSE_ERROR)
        return SET_VALUE_FILE_CLOSE_ERROR;
    
    return SET_VALUE_SUCCESS;
}
// Export + Direction + Value
int GPIO::SetPin(string get_PinNum, Pin_Direction get_Direction, Pin_Value get_Value)
{
    PinNum = get_PinNum;
    Direction = get_Direction;
    Value = get_Value;

    int status;

    status = SetPinExport();
    if (status < 0)
        return status;

    status = SetPinDir(Direction);
    if (status < 0)
        return status;
    
    status = SetPinValue(Value);
    if (status < 0)
        return status;
    
    return SET_PIN_SUCCESS;
}
// Delete Pin
int GPIO::DelPin()
{
    return SetPinUnExport();
}

// Get Pin Mux
void GPIO::GetPinMux()
{
    system("mt7688_pinmux get");
}
// Get Direction
Pin_Direction GPIO::GetPinDir()
{

    // File Open
    int fd = open(("/sys/class/gpio/gpio" + PinNum + "/direction").c_str(), O_RDONLY);
    if (fd == FILE_OPEN_ERROR)
        return GET_DIR_FILE_OPEN_ERROR;
    
    // File Read
    char DirStr[16];
    int status = read(fd, DirStr, 16);
    if (status == FILE_READ_ERROR)
        return GET_DIR_FILE_READ_ERROR;
    if (status == FILE_READ_EOF)
        return GET_DIR_FILE_READ_EOF;

    // File Close
    if (close(fd) == FILE_CLOSE_ERROR)
        return GET_DIR_FILE_CLOSE_ERROR;

    return (atoi(DirStr)==PIN_IN?PIN_IN:PIN_OUT);
}
// Get value
Pin_Value GPIO::GetPinValue()
{
    // File Open
    int fd = open(("/sys/class/gpio/gpio" + PinNum + "/value").c_str(), O_RDONLY);
    if (fd == FILE_OPEN_ERROR)
        return GET_VALUE_FILE_OPEN_ERROR;
    
    // File Read
    char ValStr[16];
    int status = read(fd, ValStr, 16);
    if (status == FILE_READ_ERROR)
        return GET_VALUE_FILE_READ_ERROR;
    if (status == FILE_READ_EOF)
        return GET_VALUE_FILE_READ_EOF;

    // File Close
    if (close(fd) == FILE_CLOSE_ERROR)
        return GET_VALUE_FILE_CLOSE_ERROR;

    return (atoi(ValStr)==PIN_HIGH?PIN_HIGH:PIN_LOW);
}
