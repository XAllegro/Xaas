<?php
require_once ('XaPage.php');

$obj=$HTTP->GetHttpParam('obj');

$object=new $obj();
$WsData= $object->List($Conf,$HTTP);

$TplList=new XaTplList();
$List=$TplList->GetList($WsData);

echo $List;
?>