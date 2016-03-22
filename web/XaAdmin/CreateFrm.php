<?php
require_once ('XaPage.php');

$obj=$HTTP->GetHttpParam('obj');

$object=new $obj();
$WsData= $object->CreateFrm($Conf,$HTTP);

$TplCreateForm=new XaTplCreateForm();
$Form=$TplCreateForm->GetForm($WsData);

echo $Form;
?>