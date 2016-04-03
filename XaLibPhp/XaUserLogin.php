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

    public final function Execute (array &$Conf,XaLibHttp &$HTTP,&$evt) {
        $this->$evt($Conf,$HTTP);
    }

    private function Login(array &$Conf,XaLibHttp &$HTTP) {

        $url=$this->GetBaseUrl($Conf,"XaUserLogin")."&Data=<WsData>";
        $url.="<login><client_ip>".$this->GetIpAddress()."</client_ip><username>".$HTTP->GetHttpParam("username")."</username><password>".$HTTP->GetHttpParam("password")."</password></login>";
        $url.="<operation><object>XaUserLogin</object><event>Login</event></operation></WsData>";

        //$result=json_decode(XaLibCurl::CallUrl ($url),true);
        $result=$this->GetCurlResAsArray($url);
        
      

        if ($result["token"]) {

            $HTTP->CookieSet($result["token"]);
            $this->Redirect("MyPage.php");
        }
    }
    
    private function Logout(array &$Conf,XaLibHttp &$HTTP) {

        if ($HTTP->CookieGet("XaSessionId")!="") {
    
            $url=$this->GetBaseUrl($Conf,"XaUserLogin")."&Data=<WsData>";
            $url.="<login><client_ip>".$this->GetIpAddress()."</client_ip><token>".$HTTP->CookieGet("XaSessionId")."</token></login>";
            $url.="<operation><object>XaUserLogin</object><event>Logout</event></operation><params><p><n></n><v></v></p></params></WsData>";
    
            //$result=json_decode(XaLibCurl::CallUrl ($url),true);

            $result=$this->GetCurlResAsArray($url);
            $this->CheckApiError($result);
            
            $this->CheckApiError($result);
            $HTTP->CookieUnset();

        }

        $this->Redirect("Logout.php");
    }
}
?>