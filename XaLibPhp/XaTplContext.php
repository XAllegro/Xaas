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

    protected function Context(array &$WsData,XaLibHttp &$HTTP):string {

        $JsCallOptions='{ResponseType:&quot;Html&quot;,TargetId:&quot;detail&quot;,JsEval:&quot;yes&quot;}';

        $Content='<div class="dropdown"><button class="dropdown-button">Actions</button><div class="dropdown-content">';

        $Content.='<a href="#" onclick="Xa.CallAction(\'\',\'UserMod.php?obj=XaUser&evt=UpdateFrm&id='.$RowId.'\','.$JsCallOptions.');">Update</a>';
        $Content.='<a href="#" onclick="Xa.CallAction(\'\',\'Delete.php?obj=XaUser&evt=Delete&id='.$RowId.'\','.$JsCallOptions.');">Delete</a>';
        $Content.='</div></div>';

        return $Content;
    }
    
    
    /*
    $actions="no";
    $actions=$this->GetTplParam($HTTP,$TplParams,"actions");
    
    $Title="Titolo Lista";
    $Title=$this->GetTplParam($HTTP,$TplParams,"title");
    */
}

?>