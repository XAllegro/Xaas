<?php

class XaLibHttp {

    private $AllHttpRequest;

    function __construct() {

        $this->AllHttpRequest=array_merge($_GET,$_POST);
    }

    final public function GetHttpRequest() {

       return $this->AllHttpRequest;
    }
    
    final public function GetHttpRequestAsString(&$ApiParams,$token="",$obj="",&$evt="") {

        $fields_string="";

        if($token!="") {
            $fields_string .= "token=".$token."&";
        }
        
        foreach($this->AllHttpRequest as $key=>$value) { 

            $fields_string .= $key.'='.XaLibUtils::ClearParamValue($value).'&';
        }


        if($ApiParams!=""){

            $ParamsArray=json_decode($ApiParams, true);

            foreach($ParamsArray as $key=>$value) { 

                $fields_string .= $key.'='.XaLibUtils::ClearParamValue($value).'&';
            }

            $fields_string=rtrim($fields_string, '&');
            
        } else {
            
            $fields_string=rtrim($fields_string,"&");

        }

        $fields_string .="&client_ip=".XaLibUtils::GetIpAddress();
        
        return $fields_string;
    }

    final public function GetHttpParam($ParamName) {

        $ParamValue=$this->AllHttpRequest["$ParamName"];
        return $ParamValue;
    }

    final public function ExistsHttpParam($ParamName) {

        if(array_key_exists($ParamName,$this->AllHttpRequest)) {

            return true;
 
        } else {
 
            return false;
        }

    }

    final public function CookieSet($SessionId){

        setcookie("XaSessionId", $SessionId,0,"","",false,true);
        
    }

    final public function CookieUnset(){
        
        setcookie("XaSessionId","",time()-3600);
    }
    
    final public function CookieGet($CookieName){
        
        if(!isset($_COOKIE[$CookieName])) {
            
           //GESTIRE

        } else {

           return $_COOKIE[$CookieName];
        }
    }   
};

?>