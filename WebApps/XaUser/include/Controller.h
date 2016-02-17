#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <XaLibControllerBackEnd.h>
#include <XaLibWs.h>
class Controller : private XaLibControllerBackEnd {

    private:

        void DispatchWs();
        void ExecuteWs(XaLibWs& Ws);

    protected:

    public:

        Controller(string ConfFile);
        ~Controller();
};
#endif