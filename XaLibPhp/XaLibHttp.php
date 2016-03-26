<?php

class XaLibHttp {

    private $AllHttpRequest;
    
    function __construct(){
        $this->AllHttpRequest=array_merge($_GET,$_POST);
    }

    final public function GetHttpParam(string $ParamName):string {

        $ParamValue=$this->AllHttpRequest["$ParamName"];
        return $ParamValue;
    }
    
    final public function ExistsHttpParam(string $ParamName) {

        if(array_key_exists($ParamName,$this->AllHttpRequest)) {

            return true;
 
        } else {
 
            return false;
        }

    }

    final public function CookieSet(string $SessionId){

        setcookie("XaSessionId", $SessionId,0,"","",false,true);
        
    }

    final public function CookieUnset(){
        
        setcookie("XaSessionId","",time()-3600);
    }
    
    final public function CookieGet(string $CookieName){
        
        if(!isset($_COOKIE[$CookieName])) {
            
           //GESTIRE

        } else {

           return $_COOKIE[$CookieName];
        }
    }   
};

?>