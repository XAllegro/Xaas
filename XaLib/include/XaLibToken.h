#ifndef XALIBTOKEN_H
#define XALIBTOKEN_H

#include <XaLibBase.h>
#include <XaLibDb.h>
#include <XaLibSql.h>

extern XaLibLog LOG;
extern XaLibDb DB_SESSION;

class XaLibToken : protected XaLibBase {

    private:

        string GenerateToken();

    protected:

    public:

        static int ValidateToken (const string& Token);

        /**
        * Retrieve the User Id of a valid Token\n
        * During a Logout this method retrieve the User_ID in order to call the DeactivateUserToken\n
        * 
        * @param token a valid Token
        * 
        * @return 0=any user is associated to this token, User_ID
        *
        * @code
        * int UserId=RetrieveUserFromToken("Token");
        * @endcode
        *
        */
        static int RetrieveUserFromToken(const string& Token);

        /**
        * Check if the User already has valid Token and asks Log In\n
        * During a Login this method check if the user already has a Valid Token\n
        * If the User already has a Valid Token the old one will be overrided\n
        * 
        * @param XaUser_ID the correspondent user id for the account
        * 
        * @return 1=The user already has a Token - 0=The User does not have a Token
        *
        * @code
        * int TableId=CheckUserToken(XY);
        * @endcode
        *
        */
        static int CheckUserToken(const int& XaUser_ID);

        /**
        * Deactivate every token associated to the User\n
        * Database table XaUserToken field status=2\n
        * @param XaUser_ID the User_ID of the User
        *
        * @code
        * DeleteUserToken(XaUser_ID);
        * @endcode
        *
        */
        static void DeactivateUserToken(const int& XaUser_ID);

        /**
        * Deactivate a Token and any other token associated to the User an\n
        * Database table XaUserToken field status=2\n
        * @param XaUser_ID the User_ID of the User
        *
        * @code
        * DeleteUserToken("Token");
        * @endcode
        *
        */
        static void DeactivateUserToken(const string& Token);

        string CreateToken (const int& XaUser_ID);

        XaLibToken();
        ~XaLibToken();
};
#endif