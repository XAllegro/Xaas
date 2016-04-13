<?php

    require_once ('XaConf.php');

    /**
     *
     * Direct BackEnd Calls
     * 
     * @example XaApi.php?obj=XaUserLogin&evt=Login (Action of Login Form)
     * <form ... action="javascript:Xa.CallAction('','XaApi.php?obj=XaUser&amp;evt=Create',{WithAlert:&quot;yes&quot;,FormId:&quot;XaUser-Create-id&quot;})">
     * @author alessandro mariotti
     * @author alex@xallegro.com
     */
    $obj=$HTTP->GetHttpParam("obj");
    $evt=$HTTP->GetHttpParam("evt");

    $ApiObject=new $obj();

    /*Page With Steps*/
    if ($HTTP->ExistsHttpParam("RedTo")) {

        $PageToRedirect=$HTTP->GetHttpParam("RedTo");
        $KeyToAppend=$HTTP->GetHttpParam("RedKey");

        $res=$ApiObject->ExecuteBack($Conf,$HTTP,$evt,$KeyToAppend);
        header( 'Location: '.$PageToRedirect.".php?RefId=".$res) ;

    } else {

        $ApiObject->Execute($Conf,$HTTP,$evt);
    }
?>