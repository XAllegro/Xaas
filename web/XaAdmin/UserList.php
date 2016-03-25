<?php
require_once ('XaPage.php');

$user=new XaUser;
$WsData= $user->List($Conf,$HTTP);

$TplList=new XaTplUserListForUpdate();
$List=$TplList->GetList($WsData);

echo $List;

?>