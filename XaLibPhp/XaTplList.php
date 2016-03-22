<?php

require_once('XaTpl.php');

/**
 * Description of XaLibApi
 *
 * @author alex
 */

class XaTplList extends XaTpl{

    function __construct() {
        
    }

    public function GetList(array $WsData):string {
        
        $Content='<table class="list">';
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
            
         $Content.='<tr class="row">';
         
          foreach($WsData['list']['item'][$i] as $value) { 
              
              $Content.='<td>'.$value.'</td>'; 
          }
        }
     } else {
        $Content.='<tr><td>No data</td></tr>';
     }

        $Content.="</table>";
        return $Content;

    }
}
?>