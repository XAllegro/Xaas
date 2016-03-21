<?php

require_once('XaTpl.php');

/**
 * Description of XaLibApi
 *
 * @author alex
 */

class XaTplRead extends XaTpl{

    function __construct() {
        
    }

    public function GetRead(array $WsData):string {
        
        $Content='<table class="list">';
        $Title="Dettaglio";

        $Content.='<tr class="title"><th colspan="100%"><span>'.$Title.'</span><ul class="RightToolbar"><li class="FunctionIcon Refresh"></li><li class="FunctionIcon Expand"></li></ul></th></tr>';
        
        /*ADDING TITLES*/        
        $Content.='<tr class="header">';
       
        foreach($WsData['read'] as $key => $value) {
            $Content.='<th>'.$key.'</th>';
        }

        $Content.='</tr>';

        $Content.='<tr class="row">';
         
        foreach($WsData['read'] as $value) { 
              
             $Content.='<td>'.$value.'</td>'; 
        }

        $Content.="</table>";
        return $Content;

    }
}
?>