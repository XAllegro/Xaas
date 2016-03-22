<?php

    ini_set('include_path', '/XAllegro/Xaas/XaLibPhp');

    require_once ('XaLibHttp.php');
    require_once ('XaUserLogin.php');
    require_once ('XaUser.php');
    require_once ('XaRbacRoleRXaUser.php');
    
    $ConfFile = file_get_contents("/XAllegro/Xaas/config/XaAdmin.json");
    $Conf = json_decode($ConfFile, true);

    $HTTP=new XaLibHttp();
?>