<?php

require_once('XaTpl.php');

/**
 * Description of XaLibApi
 *
 * @author alex
 */

class XaTplUserList extends XaTpl{

    function __construct() {
        
    }

    public function GetList(array $WsData):string {
        
        $Content='<script>
            UserViewArgsCall={
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
            UserModArgsCall={
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

        $Content.='<a href="#" onclick="Xa.CallAction(\'\',\'UserAdd.php?obj=XaUser&evt=CreateFrm\',UserCreateFrmArgsCall);">create</a>';

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

        $Content.='</tr>';

        for ($i=0;$i<$ItemsNumber;$i++) {

         $RowId=$WsData['list']['item'][$i]['id'];
         $Content.='<tr class="row" ondblclick="Xa.CallAction(\'\',\'UserView.php?obj=XaUser&evt=Read&id='.$RowId.'\',UserViewArgsCall);">';
         
          foreach($WsData['list']['item'][$i] as $value) { 
              $Content.='<td>'.$value.'</td>'; 
          }
          $Content.='<td><a href="#" onclick="Xa.CallAction(\'\',\'UserMod.php?obj=XaUser&evt=UpdateFrm&id='.$RowId.'\',UserModArgsCall);">mod</a>';

        }
     } else {
        $Content.='<tr><td>No data</td></tr>';
     }
        $Content.="</table>";

        return $Content;

    }
}
?>