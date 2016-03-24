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

$TplList=new XaTplRoleRUserList();
$List=$TplList->GetList($WsData);

// page layout

echo '<input id="XaUserId" type="hidden" value="'.$HTTP->GetHttpParam('id').'"/>' ;

echo '<div id="user_box">' ;
echo $Read;
echo '</div>' ;

echo '<br/><br/>';
echo 'Roles';
echo '<br/><br/>';

echo '<div id="role_box">' ;
echo $List;
echo '</div>' ;

?>