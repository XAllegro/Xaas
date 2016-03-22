<?php
require_once ('XaPage.php');

echo 'dettaglio utente<br/><br/>';

// user
$user=new XaUser();
$WsData= $user->Read($Conf,$HTTP);

$TplRead=new XaTplRead();
$Read=$TplRead->GetRead($WsData);

// roles
$role=new XaRbacRoleRXaUser();
$WsData= $role->ListWithKey($Conf,$HTTP,'XaRbacRoleRXaUser','XaUser_ID',$HTTP->GetHttpParam('id'));

$TplList=new XaTplList();
$List=$TplList->GetList($WsData);

// page layout

echo $Read;
echo '<br/>';
echo $List;

?>