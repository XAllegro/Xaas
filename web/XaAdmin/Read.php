<?php
require_once ('XaPage.php');

$obj=$HTTP->GetHttpParam('obj');

$object=new $obj();
$WsData= $object->Read($Conf,$HTTP);

$TplRead=new XaTplRead();
$Read=$TplRead->GetRead($WsData);

echo $Read;
?>