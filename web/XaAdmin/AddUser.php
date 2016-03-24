<?php
require_once ('XaPage.php');

echo 'aggiunta utente<br/><br/>';

echo '<input id="XaUserId"/>' ;

// user
$user=new XaUser();
$WsData= $user->CreateFrm($Conf,$HTTP);

$TplCreateForm=new XaTplUserCreateForm();
$Form=$TplCreateForm->GetForm($WsData);



// page layout

echo '<div id="user_box">' ;
echo $Form;
echo '</div>' ;

        $Content='<script>
            RoleRUserCreateFrmArgsCall={
            ResponseType:"Html",
            TargetId:"role_box",
            CallMethod:"POST",
            CallAsync:"true",
            WithLoader:"no",
            LoaderTargetID:"",
            JsEval:"yes",
            WithAlert:"no",
            AlertMessage:""
            };
        </script>';

$Content.='<a href="#" onclick="var UserId=document.getElementById(\'XaUserId\').value;if(UserId!=\'\'){Xa.CallAction(\'\',\'XaRbacRoleRXaUserCreateFrm.php?obj=XaRbacRoleRXaUser&evt=CreateFrm&XaUser_ID=\'+UserId,RoleRUserCreateFrmArgsCall);}">Roles</a>';
echo '<br/></br/>';
echo $Content;

echo '<div id="role_box"></div>' ;

?>