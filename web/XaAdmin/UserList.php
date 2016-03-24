<?php
require_once ('XaPage.php');

$user=new XaUser;
$WsData= $user->List($Conf,$HTTP);

$TplList=new XaTplUserList();
$List=$TplList->GetList($WsData);

echo $List;

?>