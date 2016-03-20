<?php
    require_once ('XaConf.php');

    $obj=$HTTP->GetHttpParam("obj");
    $evt=$HTTP->GetHttpParam("evt");
    
    $ApiObject=new $obj();
    $ApiObject->Execute($Conf,$HTTP,$evt);
?>