<?php

/**
 * Description of XaLibApi
 *
 * @author Alessandro Mariotti
 */

class XaTpl {

    protected final function GetTplParamsJson($TplParams) {

        /* 
         * TODO: Check if it is a valid JSON
         * 
         * */

        if ($TplParams!="") {

            return (json_decode($TplParams, true));

        } else {

            return 0;
        }
    }

    protected final function GetTplParam(XaLibHttp &$HTTP,&$TplParams,$ParamName) {

        if ($this->GetTplParamsJson($TplParams)!=0) {
        
            $TplParamsArray=$this->GetTplParamsJson($TplParams);
        
            if(array_key_exists($ParamName,$TplParamsArray)) {
        
                $actions=$TplParamsArray[$ParamName];
                
                return $actions;
            }
        
        } else if ($HTTP->ExistsHttpParam("TplParams")) {
        
            $TplParamsArray=$this->GetTplParamsJson($HTTP->GetHttpParam("TplParams"));
        
            if(array_key_exists($ParamName,$TplParamsArray)) {
        
                $actions=$TplParamsArray[$ParamName];
                
                return $actions;
            }
        }
    }
}
?>