<?php

require_once('XaLibApi.php');

/**
 * Description of XaLibApi
 *
 * @author alessandro mariotti
 * @author alex@xallegro.com
 */

class XaUserAddressMailType extends XaLibApi {

   function __construct() {

    }

    public final function Execute (array &$Conf,XaLibHttp &$HTTP,&$evt) {
        $this->$evt($Conf,$HTTP);
    }

}
?>