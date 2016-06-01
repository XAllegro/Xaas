<?php

require_once('XaLibApi.php');

/**
 * Description of XaLibApi
 *
 * @author alex
 */

class XaTplCreate  extends XaTpl{

    function __construct() {

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
     *          $XaUser=new XaUser();
     *          $WsData=$XaUser->ExecuteSync($Conf,$HTTP,'GetXmlModel','XaUser','');
     *
     *          $Tpl = new XaTplCreate();
     *          $Content = $Tpl->Create($Conf,$HTTP,$WsData,'{"obj":"XaUser","TargetId":"UserId","ResponseType":"Text"}');
     *          echo $Content;
        ?>
     *
     * */
    
/*
    private function GetFormAction (array &$Conf,XaLibHttp &$HTTP,&$TplParams) {
     
        $obj=$this->GetTplParam($HTTP,$TplParams,"obj");

        $TargetId=$this->GetTplParam($HTTP,$TplParams,"TargetId");
        $ResponseType=$this->GetTplParam($HTTP,$TplParams,"ResponseType");
        $WithAlert=$this->GetTplParam($HTTP,$TplParams,"WithAlert");
        $PostActionArgs=$this->GetTplParam($HTTP,$TplParams,"PostActionArgs");

        $FormId=$obj."-Create-id";

        $FormAction="javascript:Xa.CallAction('',";
        $FormAction.="'XaApi.php?obj=$obj&evt=Create',";
        $FormAction.="{&quot;ResponseType&quot;:&quot;$ResponseType&quot;,&quot;FormId&quot;:&quot;$FormId&quot;}";
        $FormAction.=")";
        
        $FormAction="javascript:Xa.CallAction('','XaApi.php?obj=".$obj."&evt=Create',{&quot;ResponseType&quot;:&quot;".$ResponseType."&quot;,&quot;FormId&quot;:&quot;".$FormId."&quot;})";
    }
*/
    
    public function Create(array $Conf,XaLibHttp &$HTTP,array &$WsData,$TplParams="") {
    
        $TplType=$this->GetTplParam($HTTP,$TplParams,"TplType");
    
        if ($TplType=="" || $TplType=="Default" || $TplType=="Standard") {
    
            return $this->Standard($Conf,$HTTP,$WsData,$TplParams);
    
        } else {
    
            return $this->$TplType($Conf,$HTTP,$WsData,$TplParams);
        }
    }

    private function Standard(array $Conf,XaLibHttp &$HTTP,array &$WsData,$TplParams="") {

        $obj=$this->GetTplParam($HTTP,$TplParams,"obj");
		$event="Create";
		// to overwrite Create event, e.g. with a bespoke create method
		$Event=$this->GetTplParam($HTTP,$TplParams,"Event");
		if($Event!=""){
			$event=$Event;
		}
		
        $TargetId=$this->GetTplParam($HTTP,$TplParams,"TargetId");
        $ResponseType=$this->GetTplParam($HTTP,$TplParams,"ResponseType");
        $WithAlert=$this->GetTplParam($HTTP,$TplParams,"WithAlert");
        $PostActionArgs=$this->GetTplParam($HTTP,$TplParams,"PostActionArgs");
        $PostJsFunction=$this->GetTplParam($HTTP,$TplParams,"PostJsFunction");

        $FormClass="form form-1-column";
        $FormName=$obj."-Create";
        $FormId=$obj."-Create-id";
        $FormMethod="POST";

        //$FormAction="javascript:Xa.CallAction('','XaApi.php?obj=".$obj."&evt=Create',{&quot;ResponseType&quot;:&quot;".$ResponseType."&quot;,&quot;TargetId&quot;:&quot;".$TargetId."&quot;,&quot;FormId&quot;:&quot;".$FormId."&quot;,&quot;WithAlert&quot;:&quot;".$WithAlert."&quot;,&quot;PostActionArgs&quot;:".$PostActionArgs."})";;

        $RedTo=$this->GetTplParam($HTTP,$TplParams,"RedTo");
        $RedKey=$this->GetTplParam($HTTP,$TplParams,"RedKey");

		if($RedTo!=""){

            $FormAction="XaApi.php?obj=".$obj;
            $FormAction.="&evt=".$event;
            $FormAction.="&RedTo=".$RedTo;
            $FormAction.="&RedKey=".$RedKey;

        } else {

           $FormAction="javascript:Xa.CallAction('','XaApi.php?obj=".$obj;
           $FormAction.="&evt=".$event."',{&quot;ResponseType&quot;:&quot;".$ResponseType."&quot;,&quot;TargetId&quot;:&quot;".$TargetId."&quot;,&quot;FormId&quot;:&quot;".$FormId."&quot;,&quot;WithAlert&quot;:&quot;".$WithAlert."&quot;,&quot;PostActionArgs&quot;:&quot;".$PostActionArgs."&quot;});".$PostJsFunction.";";
        }

		$form='';
		$form.='<script>';
		$form.=	'function clear_date(field) {';
		$form.=		"document.getElementById(field).value='';";
		$form.=	'}';

		$form.=	'function activate_formula(master,slave,slavedomain) {';
		$form.=		'var master_var=document.getElementById(master+\'-select\'); ';
		$form.=		'var master_val=master_var.options[master_var.selectedIndex].value; ';
		$form.=		'var slave_id=slave+\'-select\'; ';
				// no master option selected
		$form.=		'if (master_val=="") { master_val="0";}; ';
		$form.=		'var CompleteUrl=\'XaPageIncluded.php?obj=XaDomain&evt=Universal&tpl=List&ApiParams={"event":"ListAsOptions","tree_parent_ID":"\'+master_val+\'","domain":"\'+slavedomain+\'"}&TplParams={"TplType":"ListAsOptions"}\'; ';
		$form.=		'Xa.CallAction("",CompleteUrl,{"ResponseType":"Html","TargetId":slave_id}); ';
				// trigger change event on slave
		$form.=		'var event = new Event("change"); ';
		$form.=		'document.getElementById(slave_id).dispatchEvent(event); ';

		$form.=	'}';

		$form.='</script>';

        $form.='<form ';
        $form.=' class="'.$FormClass.'"';
        $form.=' name="'.$FormName.'"';
        $form.=' id="'.$FormId.'"';
        $form.=' method="'.$FormMethod.'"';
        $form.=' action="'.$FormAction.'"';
        $form.='>';

        $form.='<fieldset><legend>'.$WsData[$obj]['fieldset']['legend'].'</legend>';

        $form.='<ul>';

            for($i=0; $i<count($WsData[$obj]['fieldset']['field']); $i++) {
                if ($WsData[$obj]['fieldset']['field'][$i]['type']!='external-key') {
                    $form.= $this->BuildField($Conf,$HTTP,$WsData[$obj]['fieldset']['field'][$i]);
                } else {
                    $form.='<input type="hidden" name="'.$WsData[$obj]['fieldset']['field'][$i]['name'].'" value="'.$WsData[$obj]['fieldset']['field'][$i]['value'].'"/>';
                }
            }

        $form.='<li><button type="submit">Save</button><br/><br/></li>';

        $form.='</ul>';
        $form.='</fieldset>';
        $form.="</form>";

    return $form;

    }

    private function CreateForTab(array $Conf,XaLibHttp &$HTTP,array &$WsData,$TplParams="") {

        $obj=$this->GetTplParam($HTTP,$TplParams,"obj");
        $ResponseType=$this->GetTplParam($HTTP,$TplParams,"ResponseType");
 
        $PostJsFunction=$this->GetTplParam($HTTP,$TplParams,"PostJsFunction");
    
        $FormClass="form form-1-column FormForTab";
        $FormName=$obj."-Create";
        $FormId=$obj."-Create-id";
        $FormMethod="POST";
    
        
        $FormAction="javascript:Xa.CallAction('','XaApi.php?obj=".$obj;
        $FormAction.="&evt=Create',{&quot;ResponseType&quot;:&quot;".$ResponseType."&quot;,&quot;FormId&quot;:&quot;".$FormId."&quot;});".$PostJsFunction.";";

		$form='';
		$form.='<script>';
		$form.='function clear_date(field) {';
		$form.="document.getElementById(field).value='';";
		$form.='}';
		$form.='</script>';

        $form.='<form ';
        $form.=' class="'.$FormClass.'"';
        $form.=' name="'.$FormName.'"';
        $form.=' id="'.$FormId.'"';
        $form.=' method="'.$FormMethod.'"';
        $form.=' action="'.$FormAction.'"';
        $form.='>';
    
        $form.='<fieldset><legend class="LegendForTab">'.$WsData[$obj]['fieldset']['legend'].'</legend>';
    
        $form.='<ul>';
    
        for($i=0; $i<count($WsData[$obj]['fieldset']['field']); $i++) {
            if ($WsData[$obj]['fieldset']['field'][$i]['type']!='external-key') {
                $form.= $this->BuildField($Conf,$HTTP,$WsData[$obj]['fieldset']['field'][$i]);
            } else {
                $form.='<input type="hidden" name="'.$WsData[$obj]['fieldset']['field'][$i]['name'].'" value="'.$WsData[$obj]['fieldset']['field'][$i]['value'].'"/>';
            }
        }
    
        $form.='<li><button type="submit">Save</button><br/><br/></li>';
    
        $form.='</ul>';
        $form.='</fieldset>';
        $form.="</form>";

        return $form;
    }
    
    private function CreateForGeo(array $Conf,XaLibHttp &$HTTP,array &$WsData,$TplParams="") {

        $obj=$this->GetTplParam($HTTP,$TplParams,"obj");
    
        //$TargetId=$this->GetTplParam($HTTP,$TplParams,"TargetId");
        $ResponseType=$this->GetTplParam($HTTP,$TplParams,"ResponseType");
        //$WithAlert=$this->GetTplParam($HTTP,$TplParams,"WithAlert");
        //$PostActionArgs=$this->GetTplParam($HTTP,$TplParams,"PostActionArgs");
        $PostJsFunction=$this->GetTplParam($HTTP,$TplParams,"PostJsFunction");

        $FormClass="form form-1-column FormForTab";
        $FormName=$obj."-Create";
        $FormId=$obj."-Create-id";
        $FormMethod="POST";
    
        $FormAction="javascript:Xa.CallAction('','XaApi.php?obj=".$obj;
        $FormAction.="&evt=Create',{&quot;ResponseType&quot;:&quot;".$ResponseType."&quot;,&quot;FormId&quot;:&quot;".$FormId."&quot;});".$PostJsFunction.";";
        
        $form='<script type="text/javascript" src="/js/XaGmapAutocomplete.js"></script>';

        $form.='<form ';
        $form.=' class="'.$FormClass.'"';
        $form.=' name="'.$FormName.'"';
        $form.=' id="'.$FormId.'"';
        $form.=' method="'.$FormMethod.'"';
        $form.=' action="'.$FormAction.'"';
        $form.='>';
    
        $form.='<fieldset><legend class="LegendForTab">'.$WsData[$obj]['fieldset']['legend'].'</legend>';
    
        $form.='<ul>';
    
        for($i=0; $i<count($WsData[$obj]['fieldset']['field']); $i++) {

            if ($WsData[$obj]['fieldset']['field'][$i]['type']!='external-key') {
                $form.= $this->BuildField($Conf,$HTTP,$WsData[$obj]['fieldset']['field'][$i]);
            } else {
                $form.='<input type="hidden" name="'.$WsData[$obj]['fieldset']['field'][$i]['name'].'" value="'.$WsData[$obj]['fieldset']['field'][$i]['value'].'"/>';
            }
        }
    
        $form.='<li><button type="submit">Save</button><br/><br/></li>';
    
        $form.='</ul>';
        $form.='</fieldset>';
        $form.="</form>";

        $form.="<script>LoadGeoScript();</script>";
        
        return $form;
        
    }

    
    private function BuildField(array $Conf,XaLibHttp &$HTTP,array &$FieldNode) {

		// Do not  add required="no" when not required
		// Instead add required="yes" only to required fields
		$required=' ';
		if ($FieldNode['required']=='yes') {
			$required=' required="yes" ';
		}

        if ($FieldNode['create']=='yes') {

            $field='<li>';

        if ($FieldNode['type']=='input-hidden') {

            //$field.='<label id="'.$FieldNode['id'].'-label"  for="'.$FieldNode['name'].'-input">'.$FieldNode['label'].'</label>';
            $field.='<input id="'.$FieldNode['id'].'-input" name="'.$FieldNode['name'].'" type="hidden" placeholder="'.$FieldNode['name'].'"'.$required.' autofocus="autofocus" />';
        
        } else if ($FieldNode['type']=='input-text') {

            $field.='<label id="'.$FieldNode['id'].'-label"  for="'.$FieldNode['name'].'-input">'.$FieldNode['label'].'</label>';
            $field.='<input id="'.$FieldNode['id'].'-input" name="'.$FieldNode['name'].'" type="text" placeholder="'.$FieldNode['name'].'"'.$required.' autofocus="autofocus" />';

        } else if ($FieldNode['type']=='input-number') {
          
          $field.='<label id="'.$FieldNode['id'].'-label"  for="'.$FieldNode['name'].'-input">'.$FieldNode['label'].'</label>';
          $field.='<input type="number" id="'.$FieldNode['id'].'-input" name="'.$FieldNode['name'].'" placeholder="'.$FieldNode['name'].'" maxlength="'.$FieldNode['maxlength'].'" size="'.$FieldNode['size'].'"';
          
          if(isset($FieldNode['step'])){
            $field.=' step="'.$FieldNode['step'].'"';
          }
          
          if(isset($FieldNode['min'])){
            $field.=' min="'.$FieldNode['min'].'"';
          }
          
          if(isset($FieldNode['max'])){
            $field.=' max="'.$FieldNode['max'].'"';
          }
          
          $field.=$required;
          
          $field.= ' autofocus="autofocus" />';

        } else if ($FieldNode['type']=='input-email') {
          
            $field.='<label id="'.$FieldNode['id'].'-label"  for="'.$FieldNode['name'].'-input">'.$FieldNode['label'].'</label>';
            $field.='<input type="email" pattern="[^ @]*@[^ @]*" id="'.$FieldNode['id'].'-input" name="'.$FieldNode['name'].'" placeholder="'.$FieldNode['name'].'" maxlength="'.$FieldNode['maxlength'].'" size="'.$FieldNode['size'].'"';
            $field.=$required;
            $field.= ' autofocus="autofocus" />';

        } else if ($FieldNode['type']=='select-single') {
        
            $field.='<label id="'.$FieldNode['id'].'-label" for="'.$FieldNode['name'].'-select">'.$FieldNode['label'].'</label>';
            $field.='<select id="'.$FieldNode['id'].'-select" name="'.$FieldNode['name'].'"'.$required.' autofocus="autofocus" >';
            $field.='<option value="" selected="selected">please select ...</option>';

            $ObjForOptions=$FieldNode['options']['obj'];
            $EvtForOptions=$FieldNode['options']['evt'];
          
        
            if (class_exists($ObjForOptions)) {

                $OptionsObj=new $ObjForOptions();

            } else {

                $OptionsObj=new XaLibApi();
            }

            $options= $OptionsObj->$EvtForOptions($Conf,$HTTP,$FieldNode['options']['obj']);
          
            for ($i=0; $i<count($options['list']['item']); $i++) {
                 $field.='<option value="'.$options['list']['item'][$i]['id'].'">'.$options['list']['item'][$i]['name'].'</option>';
                 //echo $field;
            }
          
          $field.='</select>';
        
        } else if ($FieldNode['type']=='select-single-sync') {
        
            $field.='<label id="'.$FieldNode['id'].'-label" for="'.$FieldNode['name'].'-select">'.$FieldNode['label'].'</label>';
            $field.='<select id="'.$FieldNode['id'].'-select" name="'.$FieldNode['name'].'"'.$required.' autofocus="autofocus" >';
            $field.='<option value="" selected="selected">please select ...</option>';
            
            $ObjForOptions=$FieldNode['options']['obj'];
            $EvtForOptions=$FieldNode['options']['evt'];
            
            if (class_exists($ObjForOptions)) {

                $OptionsObj=new $ObjForOptions();

            } else {

                $OptionsObj=new XaLibApi();
            }
        
            $options= $OptionsObj->$EvtForOptions($Conf,$HTTP,$FieldNode['options']['obj']);
            
              for ($i=0; $i<count($options['list']['item']); $i++) {
                   $field.='<option value="'.$options['list']['item'][$i]['id'].'">'.$options['list']['item'][$i]['name'].'</option>';
                   //echo $field;
              }
            
            $field.='</select>';
        
        } else if ($FieldNode['type']=='select-single-domain') {

            $field.='<label id="'.$FieldNode['id'].'-label" for="'.$FieldNode['name'].'-select">'.$FieldNode['label'].'</label>';
            $field.='<select id="'.$FieldNode['id'].'-select" name="'.$FieldNode['name'].'"'.$required.' autofocus="autofocus" ';

			if (isset($FieldNode['onchange'])) {
				$field.=' onchange="activate_formula(\''.$FieldNode['id'].'\',\''.$FieldNode['onchange']['slave'].'\',\''.$FieldNode['onchange']['domain'].'\')" ';
			}
			$field.='>';
			
			$field.='<option value="" selected="selected">please select ...</option>';

			$tree_parent_ID='';
			if (isset($FieldNode['options']['tree_parent_ID'])) {
				$tree_parent_ID=$FieldNode['options']['tree_parent_ID'];
			}

			if ($tree_parent_ID!='formula') {
				$ObjForOptions=$FieldNode['options']['obj'];
				$EvtForOptions=$FieldNode['options']['evt'];

				if (class_exists($ObjForOptions)) {

					$OptionsObj=new $ObjForOptions();

				} else {

					$OptionsObj=new XaLibApi();
				}

				$options= $OptionsObj->$EvtForOptions($Conf,$HTTP,$FieldNode['options']['obj'],$FieldNode['options']['domain']);

				for ($i=0; $i<count($options['list']['item']); $i++) {
					 $field.='<option value="'.$options['list']['item'][$i]['id'].'">'.$options['list']['item'][$i]['name'].'</option>';
				}
			}

            $field.='</select>';
      
        } else if ($FieldNode['type']=='select-single-static') {
        
          $field.='<label id="'.$FieldNode['id'].'-label" for="'.$FieldNode['name'].'-select">'.$FieldNode['label'].'</label>';
          $field.='<select id="'.$FieldNode['id'].'-select" name="'.$FieldNode['name'].'"'.$required.' autofocus="autofocus" >';
          
          
          for ($i=0; $i<count($FieldNode['options']['option']); $i++) {
            $field.='<option value="'.$FieldNode['options']['option'][$i]['value'].'">'.$FieldNode['options']['option'][$i]['label'].'</option>';
            //echo $field;
          }
          
          $field.='</select>';
      
        } else if ($FieldNode['type']=='select-boolean') {
        
          $field.='<label id="'.$FieldNode['id'].'-label" for="'.$FieldNode['name'].'-select">'.$FieldNode['label'].'</label>';
          $field.='<select id="'.$FieldNode['id'].'-select" name="'.$FieldNode['name'].'"'.$required.' autofocus="autofocus" >';
          $field.='<option value="" selected="selected">please select ...</option>';
          
          $field.='<option value="0">no</option>';
          $field.='<option value="1">yes</option>';
          
          $field.='</select>';
      
        } else if ($FieldNode['type']=='input-textarea') {

            $field.='<label id="'.$FieldNode['id'].'-label"  for="'.$FieldNode['name'].'-input">'.$FieldNode['label'].'</label>';
            $field.='<textarea id="'.$FieldNode['id'].'-input" name="'.$FieldNode['name'].'" placeholder="'.$FieldNode['name'].'"'.$required.' autofocus="autofocus" ></textarea>';

		} else if ($FieldNode['type']=='input-date') {

			$FieldId=$FieldNode['name'].'-input';
            $field.='<label id="'.$FieldNode['id'].'-label"  for="'.$FieldId.'">'.$FieldNode['label'].'</label>';
            $field.='<input style="border:1px solid lightgrey;width:30%" onclick="javascript:Xa.CallAction(\'\',\'Calendar.php?field='.$FieldId.'\',{&quot;TargetId&quot;:&quot;kal-'.$FieldId.'&quot;,&quot;JsEval&quot;:&quot;yes&quot;,&quot;ResponseType&quot;:&quot;Html&quot;});" readonly="yes" id="'.$FieldId.'" name="'.$FieldNode['name'].'" type="text" placeholder="'.$FieldNode['name'].'"'.$required.' autofocus="autofocus" />';
			$field.='<a href="javascript:clear_date(\''.$FieldId.'\');"> clear</a>';
			$field.='<br/>';
			$field.='<div id="kal-'.$FieldId.'"></div>';
					
        } else {

            $field.=$FieldNode['type'].' FIELD TYPE NOT YET SUPPORTED';
        }

            $field.='</li>';
        }

        return $field;
    }
}
?>