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

    public final function Execute (array &$Conf,XaLibHttp &$HTTP,$evt,$obj="") {

        if ($obj!="") {

            $this->_obj=$obj;
            return ($this->$evt($Conf,$HTTP));

        } else {
            $this->$evt($Conf,$HTTP);

        }   
    }

}
?>