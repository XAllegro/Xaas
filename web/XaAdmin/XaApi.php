<?php

    require_once ('XaConf.php');

    /**
     *
     * Direct BackEnd Calls
     * 
     * @example XaApi.php?obj=XaUserLogin&evt=Login (Action of Login Form)
     *  
     * @author alessandro mariotti
     * @author alex@xallegro.com
     */

    $obj=$HTTP->GetHttpParam("obj");
    $evt=$HTTP->GetHttpParam("evt");

    $ApiObject=new $obj();
    $ApiObject->Execute($Conf,$HTTP,$evt);
?>