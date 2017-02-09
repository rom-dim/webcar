#include <iostream>
#include <stdio.h>
#include <unistd.h>

#include "carcontrol.h"

using namespace std;

#include <uWS/uWS.h>
using namespace uWS;

CarControl car;


int main(int argc, char *argv[])
{
    cout << "WebCar is started! " << endl;

    uWS::Hub h;

    h.onMessage([](uWS::WebSocket<uWS::SERVER> ws, char *message, size_t length, uWS::OpCode opCode) {
        ws.send(message, length, opCode);
    });


    h.onMessage([](uWS::WebSocket<uWS::SERVER> ws, char *message, size_t length, uWS::OpCode opCode) {
        if(opCode== uWS::OpCode::TEXT)
        {
            string rx(message,length);
            char command[16];
            float value;
            sscanf(rx.c_str(),"%s %f", command,&value) ;

            string commdStr(command);

            if(commdStr.compare("speed")==0)
            {
                car.setSpeed(value);
            }else if(commdStr.compare("wheels")==0)
            {
                car.setWheels(value);
            }
            else if(commdStr.compare("multiplier")==0)
            {
                car.setMaxSpeed(value);
            }
        }
    });


    h.listen(3000);
    h.run();

    return 0;
}
