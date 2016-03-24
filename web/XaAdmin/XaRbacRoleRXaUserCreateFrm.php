<?php
require_once ('XaPage.php');

$obj=$HTTP->GetHttpParam('obj');

$object=new $obj();
$WsData= $object->CreateFrm($Conf,$HTTP);

$TplCreateForm=new XaTplRoleRUserCreateForm();
$Form=$TplCreateForm->GetForm($WsData);

echo $Form;
?>