<?php

require_once('XaTpl.php');

/**
 * Description of XaLibApi
 *
 * @author alex
 */

class XaTplRoleRUserListForUpdate extends XaTpl{

    function __construct() {
        
    }

    public function GetList(array $WsData):string {

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
            RoleRUserUpdateFrmArgsCall={
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
            RoleRUserDeleteArgsCall={
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
        $Content.='<th></th>';
        $Content.='<th></th>';

        $Content.='</tr>';

        for ($i=0;$i<$ItemsNumber;$i++) {

         $RowId=$WsData['list']['item'][$i]['id'];
         $Content.='<tr class="row">';
         
          foreach($WsData['list']['item'][$i] as $value) { 
              $Content.='<td>'.$value.'</td>'; 
          }
          $Content.='<td><a href="#" onclick="Xa.CallAction(\'\',\'XaRbacRoleRXaUserUpdateFrm.php?obj=XaRbacRoleRXaUser&evt=UpdateFrm&id='.$RowId.'\',RoleRUserUpdateFrmArgsCall);">mod</a>';
          $Content.='<td><a href="#" onclick="Xa.CallAction(\'\',\'Delete.php?obj=XaRbacRoleRXaUser&evt=Delete&id='.$RowId.'\',RoleRUserDeleteArgsCall);">del</a>';

        }
     } else {
        $Content.='<tr><td>No data</td></tr>';
     }
        $Content.="</table>";

        return $Content;

    }
}
?>