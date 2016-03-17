<?php

    ini_set('include_path', '/XAllegro/Xaas/XaLibPhp');

    require_once ('XaLibHttp.php');
    require_once ('XaUserLogin.php');
    
    $ConfFile = file_get_contents("/XAllegro/Xaas/config/XaDashboard.json");
    $Conf = json_decode($ConfFile, true);

    $HTTP=new XaLibHttp();

    $obj =$HTTP->GetHttpParam("obj");
    $evt =$HTTP->GetHttpParam("evt");

    $ApiObject=new $obj($Conf,$HTTP,$evt);

?>