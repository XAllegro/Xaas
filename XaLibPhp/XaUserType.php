<?php

require_once('XaLibApi.php');

/**
 * Description of XaLibApi
 *
 * @author alessandro mariotti
 * @author alex@xallegro.com
 */

class XaUserType extends XaLibApi {

    function __construct() {

    }

    public final function Execute (array &$Conf,XaLibHttp &$HTTP,$evt) {

        $this->$evt($Conf,$HTTP);
    }

    public final function ExecuteSync (array &$Conf,XaLibHttp &$HTTP,$evt,$obj,$Params) {

        $this->_obj=$obj;
        $this->_params=$Params;

        return ($this->$evt($Conf,$HTTP));
    }
}
?>