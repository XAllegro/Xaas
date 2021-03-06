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

    private function GetDropDown(array &$WsData,XaLibHttp &$HTTP,array &$MyLinks,$RowId ):string {

        $JsCallOptions='{ResponseType:&quot;Html&quot;,TargetId:&quot;detail&quot;,JsEval:&quot;yes&quot;}';

        $Content='<div class="dropdown"><button class="dropdown-button">Actions</button><div class="dropdown-content">';

        //$Content.='<a href="#" onclick="Xa.CallAction(\'\',\'UserMod.php?obj=XaUser&evt=UpdateFrm&id='.$RowId.'\','.$JsCallOptions.');">Update</a>';
        //$Content.='<a href="#" onclick="Xa.CallAction(\'\',\'Delete.php?obj=XaUser&evt=Delete&id='.$RowId.'\','.$JsCallOptions.');">Delete</a>';
        $Content.='</div></div>';

        return $Content;
    }

    /*
     * Example: Async Call with options:
     * 
     * Xa.CallAction('','XaPage.php?obj=XaUser&evt=List&tpl=List&params={%22order_by%22:%22surname%22}&TplParams={%22actions%22:%22yes%22,%22title%22:%22Lista%20Utenti%22}&lay=Included',{&quot;ResponseType&quot;:&quot;Html&quot;,&quot;TargetId&quot;:&quot;content&quot;});
     * 
     * 
     * Example: Sync Call with options:
     * 
     * <?php
     *  $XaUser=new XaUser();
     *  $WsData=$XaUser->ExecuteSync($Conf,$HTTP,"List","XaUser","{\"order_by\":\"surname\",\"status\":1}");
     *
     *  $Tpl = new XaTplList();
     *  $Content = $Tpl->List($Conf,$HTTP,$WsData,"{\"actions\":\"yes\"}");
     *  echo $Content;
     * ?>
     * 
     * */

    public function List(array $Conf,XaLibHttp &$HTTP,array &$WsData,$TplParams=""):string {
        
        $TplType=$this->GetTplParam($HTTP,$TplParams,"TplType");

        if ($TplType=="" || $TplType=="Default") {
            
            return $this->Default($Conf,$HTTP,$WsData,$TplParams);

        } else {
            
            return $this->$TplType($Conf,$HTTP,$WsData,$TplParams);
        }        
    }
    
    public function Default(array $Conf,XaLibHttp &$HTTP,array &$WsData,$TplParams=""):string {
    
        $actions="no";
        $actions=$this->GetTplParam($HTTP,$TplParams,"actions");
    
        $Title="Titolo Lista";
        $Title=$this->GetTplParam($HTTP,$TplParams,"title");

        $DropDownMenu="";
    
        $Content='<table class="list">';
    
        $Content.='<tr class="title"><th colspan="100%"><span>'.$Title.'</span><ul class="RightToolbar"><li class="FunctionIcon Refresh"></li><li class="FunctionIcon Expand"></li></ul></th></tr>';
    
        $ItemsNumber=count($WsData['list']['item']);
    
        if ($ItemsNumber>0) {
    
            /*ADDING TITLES*/
            $Content.='<tr class="header">';
             
            foreach($WsData['list']['item'][0] as $key => $value) {
                $Content.='<th>'.$key.'</th>';
            }
    
            //ADDING COLUMN FOR ACTIONS
            //if ($actions=="yes"){
            //  $Content.='<th>Actions</th>';
            //}
    
            $Content.='</tr>';
    
            for ($i=0;$i<$ItemsNumber;$i++) {
    
                $Content.='<tr class="row">';
                 
                foreach($WsData['list']['item'][$i] as $value) {
    
                    $Content.='<td>'.$value.'</td>';
                }
    
                //ADDING ACTIONS
                //if ($actions=="yes") {
    
                //  $Content.='<td>';
                //$RowId=$WsData['list']['item'][$i]['id'];
                //$Content.=$this->GetDropDown($WsData,$HTTP,$RowId);
                //$Content.='</td>';
                //}
            }
    
        } else {
            $Content.='<tr><td>No data</td></tr>';
        }
    
        $Content.="</table>";
        return $Content;
    }
    
    public function ListForTab(array $Conf,XaLibHttp &$HTTP,array &$WsData,$TplParams=""):string {

        $obj=$this->GetTplParam($HTTP,$TplParams,"obj");
        $actions=$this->GetTplParam($HTTP,$TplParams,"actions");
        $Title=$this->GetTplParam($HTTP,$TplParams,"title");
        $DropDownMenu="";

        $Content='<table class="list">';
        $Content.='<tr class="title"><th colspan="100%"><span>'.$Title.'</span></th></tr>';
    
        $ItemsNumber=count($WsData['list']['item']);
    
        if ($ItemsNumber>0) {
    
            /*ADDING TITLES*/
            $Content.='<tr class="header">';
             
            foreach($WsData['list']['item'][0] as $key => $value) {
                $Content.='<th>'.$key.'</th>';
            }
    
            //ADDING COLUMN FOR ACTIONS
            
            $Content.='<th></th>';
    
            $Content.='</tr>';
    
            for ($i=0;$i<$ItemsNumber;$i++) {

                $Content.='<tr class="row">';

                foreach($WsData['list']['item'][$i] as $value) {
    
                    $Content.='<td>'.$value.'</td>';
                }
    
                $Content.='<td>';

                $RowId=$WsData['list']['item'][$i]['id'];

                $ActionDelete="XaApi.php?obj=".$obj."&evt=Delete&id=".$RowId;
                
                $AfterDelete=$this->GetTplParam($HTTP,$TplParams,"AfterDelete");
                
                if ($obj!="") {
                
                    $Content.='<a href="#" onclick="Xa.CallAction(\'\',\''.$ActionDelete.'\',{&quot;ResponseType&quot;:&quot;Text&quot;});';
                    
                    if ($AfterDelete!="") {
                        $Content.=$AfterDelete;
                    }
                    
                    $Content.='">Delete</a>';

                }
                
                    //$Content.=$this->GetDropDown($WsData,$HTTP,$RowId);
                $Content.='</td>';
                
            }
    
        } else {
            $Content.='<tr><td>No data</td></tr>';
        }
    
        $Content.="</table>";
        return $Content;
    }
	
    public function ListAsOptions(array $Conf,XaLibHttp &$HTTP,array &$WsData,$TplParams=""):string {

		//// passare valore di default quando si e' in modifica del campo

		$Content='';

		$Content.='<option value="">please select ...</option>';
		if (isset($WsData['list']['item'])) {
			for ($i=0; $i<count($WsData['list']['item']); $i++) {
				$Content.='<option value="'.$WsData['list']['item'][$i]['id'].'">'.$WsData['list']['item'][$i]['name'].'</option>';
			}
		}

		return $Content;

	}
}

?>