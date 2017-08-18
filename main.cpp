#include "gpio.h"

int main()
{
    GPIO GPIO42;
    GPIO GPIO43;

    GPIO42.GetPinMux();
    GPIO42.SetPinMux("ephy");

    int status;

    status = GPIO42.SetPin("42",PIN_OUT,PIN_LOW);
    if(status < 0)
        cout<<"GPIO"<<"42"<<" Error Code:"<<status<<endl;
    cout<<"GPIO42.SetPin() finished"<<endl;

    status = GPIO43.SetPin("43",PIN_OUT,PIN_LOW);
    if(status < 0)
        cout<<"GPIO"<<"43"<<" Error Code:"<<status<<endl;
    cout<<"GPIO43.SetPin() finished"<<endl;

    cout<<"00"<<endl;

    for(int i=0;i<10;i++)
    {
        status = GPIO42.SetPinValue(PIN_LOW);
        cout<<"GPIO42.SetPinValue() status:"<<status<<endl;
        status = GPIO43.SetPinValue(PIN_HIGH);
        cout<<"GPIO43.SetPinValue() status:"<<status<<endl;
        cout<<"01"<<endl;
        usleep(500000);    // 500 ms
        GPIO42.SetPinValue(PIN_HIGH);
        GPIO43.SetPinValue(PIN_LOW);
        cout<<"10"<<endl;
        usleep(500000);    // 500 ms
        GPIO42.SetPinValue(PIN_HIGH);
        GPIO43.SetPinValue(PIN_HIGH);
        cout<<"11"<<endl;
        usleep(500000);    // 500 ms
        GPIO42.SetPinValue(PIN_LOW);
        GPIO43.SetPinValue(PIN_LOW);
        cout<<"00"<<endl;
        usleep(500000);    // 500 ms
    }

    status = GPIO42.DelPin();
    cout<<"GPIO42.DelPin() status:"<<status<<endl;
    status = GPIO43.DelPin();
    cout<<"GPIO43.DelPin() status:"<<status<<endl;

    return 0;
}
