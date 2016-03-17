<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

require_once('XaLibApi.php');

/**
 * Description of XaLibApi
 *
 * @author alex
 */


class XaUser extends XaLibApi {
    
    function __construct(array &$Conf,XaLibHttp &$HTTP,string &$evt) {
        $this->$evt($Conf,$HTTP);
    }

    private function List(array &$Conf,XaLibHttp &$HTTP) {
   /*     
        if ($HTTP->CookieGet("XaSessionId")!="") {

            $url=$this->GetBaseUrl($Conf,"XaUser")."&Data=<WsData>";
            $url.="<login><client_ip>".$this->GetIpAddress()."</client_ip><token>".$HTTP->CookieGet("XaSessionId")."</token></login>";
            $url.="<operation><object>XaUserLogin</object><event>Logout</event></operation><params><p><n></n><v></v></p></params></WsData>";
            
            
            

            
            

            $result=json_decode(XaLibCurl::CallUrl ($url),true);

            $this->CheckApiError($result);
            $HTTP->CookieUnset();

        }
        */
        
        

    }
}
?>