<?php
require_once ('XaPage.php');

$role=new XaRbacRoleRXaUser();
$WsData= $role->ListWithKey($Conf,$HTTP,'XaRbacRoleRXaUser','XaUser_ID',$HTTP->GetHttpParam('XaUser_ID'));

        $Content='<script>
            RbacRUserCreateFrmArgsCall={
            ResponseType:"Html",
            TargetId:"detail",
            CallMethod:"POST",
            CallAsync:"true",
            WithLoader:"no",
            LoaderTargetID:"",
            JsEval:"yes",
            WithAlert:"no",
            AlertMessage:""
            };
        </script>';

$Content.='<a href="#" onclick="var UserId=document.getElementById(\'XaUserId\').value;if(UserId!=\'\'){Xa.CallAction(\'\',\'XaRbacRoleRXaUserCreateFrm.php?obj=XaRbacRoleRXaUser&evt=CreateFrm&XaUser_ID=\'+UserId,RoleRUserCreateFrmArgsCall);}">create</a>';


        $Content.='<table class="list">';
        $Title="Titolo Lista";

        $Content.='<tr class="title"><th colspan="100%"><span>'.$Title.'</span><ul class="RightToolbar"><li class="FunctionIcon Refresh"></li><li class="FunctionIcon Expand"></li></ul></th></tr>';

        $ItemsNumber=count($WsData['list']['item']);

      if ($ItemsNumber>0) {

        /*ADDING TITLES*/        
        $Content.='<tr class="header">';
       
        foreach($WsData['list']['item'][0] as $key => $value) {
            $Content.='<th>'.$key.'</th>';
        }

        $Content.='</tr>';

        for ($i=0;$i<$ItemsNumber;$i++) {

         $RowId=$WsData['list']['item'][$i]['id'];
         $Content.='<tr class="row">';
         
          foreach($WsData['list']['item'][$i] as $value) { 
              
              $Content.='<td>'.$value.'</td>'; 
          }
        }
     } else {
        $Content.='<tr><td>No data</td></tr>';
     }
        $Content.="</table>";

echo $Content;

?>