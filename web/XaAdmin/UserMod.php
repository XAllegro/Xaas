<?php
require_once ('XaPage.php');

echo 'modifica utente<br/><br/>';

// user
$user=new XaUser();
$WsData= $user->UpdateFrm($Conf,$HTTP);

$TplUpdateForm=new XaTplUpdateForm();
$Form=$TplUpdateForm->GetForm($WsData[0],$WsData[1]);

// roles
$role=new XaRbacRoleRXaUser();
$WsData= $role->ListWithKey($Conf,$HTTP,'XaRbacRoleRXaUser','XaUser_ID',$HTTP->GetHttpParam('id'));

$TplList=new XaTplRoleRUserListForUpdate();
$List=$TplList->GetList($WsData);

// page layout

echo '<input id="XaUserId" type="hidden" value="'.$HTTP->GetHttpParam('id').'"/>' ;

echo '<div id="user_box">' ;
echo $Form;
echo '</div>' ;

echo '<br/>';

echo '<a href="#" onclick="var UserId=document.getElementById(\'XaUserId\').value;if(UserId!=\'\'){Xa.CallAction(\'\',\'XaRbacRoleRXaUserList.php?obj=XaRbacRoleRXaUser&evt=List&XaUser_ID=\'+UserId,RoleRUserCreateFrmArgsCall);}">Roles</a>';
echo '<br/></br/>';

echo '<div id="role_box">' ;
echo $List;
echo '</div>' ;

?>