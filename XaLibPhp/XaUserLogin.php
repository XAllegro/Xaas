<?php

require_once('XaLibApi.php');

/**
 * Description of XaLibApi
 *
 * @author alex
 */

class XaUserLogin extends XaLibApi {

    function __construct() {

    }

    protected function Login(array &$Conf,XaLibHttp &$HTTP) {
        $url=$this->GetBaseUrl($Conf,"XaUserLogin")."&Data=<WsData>";
        $url.="<login><client_ip>".XaLibUtils::GetIpAddress()."</client_ip><username>".$HTTP->GetHttpParam("username")."</username><password>".$HTTP->GetHttpParam("password")."</password></login>";
        $url.="<operation><object>XaUserLogin</object><event>Login</event></operation></WsData>";
        echo $url;
        $result=$this->GetCurlResAsArray($url);

        if ($result["token"]) {

            $HTTP->CookieSet($result["token"]);
            XaLibUtils::Redirect($Conf["MyApp"]["MyPage"]);
        }
    }
   
    protected function Logout(array &$Conf,XaLibHttp &$HTTP) {

        if ($HTTP->CookieGet("XaSessionId")!="") {
    
            $url=$this->GetBaseUrl($Conf,"XaUserLogin")."&Data=<WsData>";
            $url.="<login><client_ip>".XaLibUtils::GetIpAddress()."</client_ip><token>".$HTTP->CookieGet("XaSessionId")."</token></login>";
            $url.="<operation><object>XaUserLogin</object><event>Logout</event></operation><params><p><n></n><v></v></p></params></WsData>";

            $result=$this->GetCurlResAsArray($url);
            $this->CheckApiError($result);
            $HTTP->CookieUnset();

        }

        XaLibUtils::Redirect($Conf["MyApp"]["LogoutPage"]);
    }
}
?>