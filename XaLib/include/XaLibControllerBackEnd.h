#ifndef XALIBCONTROLLERBACKEND_H
#define XALIBCONTROLLERBACKEND_H

#include <XaLibController.h>

/**
 * @brief Base Class for Back End Controllers
 *
 * @details Base Class for Back End Controllers:\n
 * 
 * Any Back End Application Controller will extends this class
 *
 * @author Alessandro Mariotti - alex@xallegro.com
*/
class XaLibControllerBackEnd : protected XaLibController {

	private:

	protected:

		/**
		* @brief Environment initialization.
		* @details Initialization of Super Global Variable
		* @see XaLibBase
		* @see XaLibAction
		* 
		* @param ConFile Configuration File - Relative or absolute path
		* @return Void
		*
		* Example Usage: in derived Controller Class
		*
		* @code
		*
		* int main(void){
		*
		*	string ConfigurationFile {"../config/XAllegro.xml"};
		*	unique_ptr<FILE, int(*)(FILE*)> fp(fopen(ConfigurationFile.c_str(), "r"), fclose);
		*
		*	if (fp) {
		*
		*		unique_ptr<Controller> ControllerObj (new Controller(ConfigurationFile.c_str()));
		*
		*	} else {
		*		...
		*	}
		*
		*	return 0;
		* };

		* Controller::Controller(string ConfFile) {
		* 
		*	OnStart(ConfFile);
		*	...
		* 
		* } 
		* @endcode
		*
		*/
		void OnStart(const string& ConfFile);

		int  ProfileCalledObject(const string& CalledObject,const string& CalledEvent);

		virtual void SendResponse();
		//void Dispatch();

		//virtual void ExecuteCalledObject();

		//void SendLocationHeaders(string Location);

	public:

		/*void GetCall();*/
		/*void GetLayout();*/
		/*void GetClientInfo();*/
		//void GetWs();

		
		XaLibControllerBackEnd();
		virtual ~XaLibControllerBackEnd();
};
#endif