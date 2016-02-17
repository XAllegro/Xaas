#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <XaLibControllerFrontEnd.h>
#include <XaLibError.h>

class Controller : private XaLibControllerFrontEnd {

	private:
		//void ExecuteCalledObject();
		//int  ProfileCalledObject(string CalledObject,string CalledEvent);

	protected:

		void Dispatch ();
		void ExecuteEvent();

	public:

		Controller(string ConfFile);
		~Controller();
};
#endif