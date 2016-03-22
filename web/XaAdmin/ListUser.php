<?php
require_once ('XaPage.php');

$user=new XaUser;
$WsData= $user->List($Conf,$HTTP);

        $Content='<script>
            UserReadArgsCall={
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
            UserCreateFrmArgsCall={
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

$Content.='<a href="#" onclick="Xa.CallAction(\'\',\'CreateFrm.php?obj=XaUser&evt=CreateFrm\',UserCreateFrmArgsCall);">create</a>';

        $Content.='<table class="list">';
        $Title="Titolo Lista";

        $Content.='<tr class="title"><th colspan="100%"><span>'.$Title.'</span><ul class="RightToolbar"><li class="FunctionIcon Refresh"></li><li class="FunctionIcon Expand"></li></ul></th></tr>';

      if (count($WsData['list'])>0) {        

        $ItemsNumber=count($WsData['list']['item']);

        /*ADDING TITLES*/        
        $Content.='<tr class="header">';
       
        foreach($WsData['list']['item'][0] as $key => $value) {
            $Content.='<th>'.$key.'</th>';
        }

        $Content.='</tr>';

        for ($i=0;$i<$ItemsNumber;$i++) {

         $RowId=$WsData['list']['item'][$i]['id'];
         $Content.='<tr class="row" ondblclick="Xa.CallAction(\'\',\'ViewUser.php?obj=XaUser&evt=Read&id='.$RowId.'\',UserReadArgsCall);">';
         
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