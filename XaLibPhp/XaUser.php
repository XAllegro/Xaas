<?php

require_once('XaLibApi.php');

/**
 * Description of XaLibApi
 *
 * @author alessandro mariotti
 * @author alex@xallegro.com
 */

class XaUser extends XaLibApi {

   function __construct() {

    }

    public final function Execute (array &$Conf,XaLibHttp &$HTTP,string &$evt) {
        $this->$evt($Conf,$HTTP);
    }

    public final function GetXml() {
        
    }

}
?>