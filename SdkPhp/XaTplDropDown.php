<?php

require_once('XaTpl.php');

/**
 * Description of XaLibApi
 *
 * @author alessandro mariotti
 * @author alex@xallegro.com
 */

class XaTplDropDown extends XaTpl {

    function __construct() {

    }

    public function DropDown(array $Conf,XaLibHttp &$HTTP,array &$WsData,$TplParams=""):string {
        
 
        /*
        $JsCallOptions='{ResponseType:&quot;Html&quot;,TargetId:&quot;detail&quot;,JsEval:&quot;yes&quot;}';

        $actions="no";
        $actions=$this->GetTplParam($HTTP,$TplParams,"actions");

        $Content='<div class="dropdown"><button class="dropdown-button">Actions</button><div class="dropdown-content">';

            $Content.='<a href="#" onclick="Xa.CallAction(\'\',\'UserMod.php?obj=XaUser&evt=UpdateFrm&id='.$RowId.'\','.$JsCallOptions.');">Update</a>';
            $Content.='<a href="#" onclick="Xa.CallAction(\'\',\'Delete.php?obj=XaUser&evt=Delete&id='.$RowId.'\','.$JsCallOptions.');">Delete</a>';

        $Content.='</div></div>';

        return $Content;*/
        return "paperinopoli";
    }

    /*
    $actions="no";
    $actions=$this->GetTplParam($HTTP,$TplParams,"actions");
    $Title="Titolo Lista";
    $Title=$this->GetTplParam($HTTP,$TplParams,"title");
    */
}
?>