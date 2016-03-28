<?php

    ini_set('include_path', '/XAllegro/Xaas/XaLibPhp');

    require_once ('XaLibHttp.php');

    /*BACKEND API Calls*/
    require_once ('XaUserLogin.php');
    require_once ('XaUser.php');
    require_once ('XaUserType.php');

    //require_once ('XaRbacRoleRXaUser.php');
    //require_once ('XaOuType.php');
    //require_once ('XaRbacRole.php');

    /*FRONTEND TPLs*/
    require_once ('XaTpl.php');
    require_once ('XaTplList.php');
    require_once ('XaTplRead.php');
    require_once ('XaTplCreate.php');

    //require_once ('XaTplUserCreateForm.php');
    //require_once ('XaTplUpdateForm.php');
    //require_once ('XaTplRoleRUserCreateForm.php');
    //require_once ('XaTplRoleRUserUpdateForm.php');
    //require_once ('XaTplRoleRUserList.php');
    //require_once ('XaTplRoleRUserListForUpdate.php');

    /*CONFIG FILE*/
    $ConfFile = file_get_contents("/XAllegro/Xaas/config/XaAdmin.json");
    $Conf = json_decode($ConfFile, true);

    /*POST AND GET*/
    $HTTP=new XaLibHttp();
?>