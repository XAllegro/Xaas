<?php
require_once ('XaPage.php');

$obj=$HTTP->GetHttpParam('obj');

$object=new $obj();
$WsData= $object->UpdateFrm($Conf,$HTTP);

$TplUpdateForm=new XaTplRoleRUserUpdateForm();
$Form=$TplUpdateForm->GetForm($WsData[0],$WsData[1]);

echo $Form;
?>