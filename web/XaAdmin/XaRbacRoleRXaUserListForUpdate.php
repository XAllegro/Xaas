<?php
require_once ('XaPage.php');

$role=new XaRbacRoleRXaUser();
$WsData= $role->ListWithKey($Conf,$HTTP,'XaRbacRoleRXaUser','XaUser_ID',$HTTP->GetHttpParam('XaUser_ID'));

$TplList=new XaTplRoleRUserListForUpdate();
$List=$TplList->GetList($WsData);

echo $List;

?>