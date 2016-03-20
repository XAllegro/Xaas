<?php
require_once ('XaPage.php');

$user=new XaUser();
$WsData= $user->List($Conf,$HTTP);


$TplList=new XaTplList();
$List=$TplList->GetList($WsData);

echo $List;
?>