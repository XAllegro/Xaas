<?php

require_once('XaLibApi.php');

/**
 * Description of XaLibApi
 *
 * @author alex
 */

class XaTplUpdate  extends XaTpl{

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
     *          $Tpl = new XaTplUpdate();
     *          $Content = $Tpl->Update($Conf,$HTTP,$WsData,'{"obj":"XaUser","TargetId":"UserId","ResponseType":"Text"}');
     *          echo $Content;
        ?>
     *
     * */

    function Update(array $Conf,XaLibHttp &$HTTP,array &$WsData,$TplParams=""):string {

        $obj=$this->GetTplParam($HTTP,$TplParams,"obj");
		$event="Update";
        $id=$this->GetTplParam($HTTP,$TplParams,"id");

        $TargetId=$this->GetTplParam($HTTP,$TplParams,"TargetId");
        $ResponseType=$this->GetTplParam($HTTP,$TplParams,"ResponseType");
        $WithAlert=$this->GetTplParam($HTTP,$TplParams,"WithAlert");
        $PostActionArgs=$this->GetTplParam($HTTP,$TplParams,"PostActionArgs");
        $PostJsFunction=$this->GetTplParam($HTTP,$TplParams,"PostJsFunction");

        $FormClass="form form-1-column";
        $FormName=$obj."-Update";
        $FormId=$obj."-Update-id";
        $FormMethod="POST";

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

        //$form='<script type="text/javascript" src="/js/XaGmapAutocomplete.js"></script>';
		
    		$pippo=file_get_contents($Conf['JsDir']['ApiPath'].'XaGmapAutocomplete.js');
    		$form='<script>'.$pippo.'</script>';
		
        $form.='<form ';
        $form.='class="'.$FormClass.'"';
        $form.='name="'.$FormName.'"';
        $form.='id="'.$FormId.'"';
        $form.='method="'.$FormMethod.'"';
        $form.='action="'.$FormAction.'"';
        $form.='>';

        $form.='<input type="hidden" name="id" value="'.$id.'"/>';

        $form.='<fieldset><legend>'.$WsData[$obj]['fieldset']['update_legend'].'</legend>';

        $form.='<ul>';

        for($i=0; $i<count($WsData[$obj]['fieldset']['field']); $i++) {
            $form.= $this->BuildField($Conf,$HTTP,$WsData[$obj]['fieldset']['field'][$i]);
        }

        $form.='<li><button type="submit">Save</button><br/><br/></li>';

        $form.='</ul>';
        $form.='</fieldset>';
        $form.="</form>";
        
        $form.="<script>LoadGeoScript();</script>";

        return $form;
    }

    function BuildField(array $Conf,XaLibHttp &$HTTP,array &$FieldNode) {

        /*
         * Ho distinto le select single in 2 tipi sync e async 
         * sync sono quelle aggiunte staticamente dalla pagina generata
         * async sono quelle aggiornate ad onclik o altri eventi utili per inserimenti dinamici di opzioni 
         * va scritto l'if per select-single-async con il js dinamico (vedere vecchio front end)
         * 
         * */

		// Do not  add required="no" when not required
		// Instead add required="yes" only to required fields
		$required=' ';
		if ($FieldNode['required']=='yes') {
			$required=' required="yes" ';
		}

		$field='';

		if ($FieldNode['update']=='yes') {
        
            $field='<li>';

        if ($FieldNode['type']=='input-hidden') {

            $field.='<label id="'.$FieldNode['id'].'-label"  for="'.$FieldNode['name'].'-input">'.$FieldNode['label'].'</label>';
            $field.='<input id="'.$FieldNode['id'].'-input" name="'.$FieldNode['name'].'" type="text" placeholder="'.$FieldNode['name'].'"'.$required.' autofocus="autofocus" value="'.$FieldNode['value'].'" />';
        
        } else if ($FieldNode['type']=='input-text') {

            $field.='<label id="'.$FieldNode['id'].'-label"  for="'.$FieldNode['name'].'-input">'.$FieldNode['label'].'</label>';
            $field.='<input id="'.$FieldNode['id'].'-input" name="'.$FieldNode['name'].'" type="text" placeholder="'.$FieldNode['name'].'"'.$required.' autofocus="autofocus" value="'.$FieldNode['value'].'" />';

        } else if ($FieldNode['type']=='input-number') {
          
          $field.='<label id="'.$FieldNode['id'].'-label"  for="'.$FieldNode['name'].'-input">'.$FieldNode['label'].'</label>';
          $field.='<input type="number" id="'.$FieldNode['id'].'-input" name="'.$FieldNode['name'].'" placeholder="'.$FieldNode['name'].'" maxlength="'.$FieldNode['maxlength'].'" size="'.$FieldNode['size'].'"'.$required ;

          $field.= ' autofocus="autofocus" value="'.$FieldNode['value'].'" />';

        } else if ($FieldNode['type']=='input-email') {
          
          $field.='<label id="'.$FieldNode['id'].'-label"  for="'.$FieldNode['name'].'-input">'.$FieldNode['label'].'</label>';
          $field.='<input type="email" pattern="[^ @]*@[^ @]*" id="'.$FieldNode['id'].'-input" name="'.$FieldNode['name'].'" placeholder="'.$FieldNode['name'].'" maxlength="'.$FieldNode['maxlength'].'" size="'.$FieldNode['size'].'"'.$required;

          $field.= ' autofocus="autofocus" value="'.$FieldNode['value'].'" />';

        } else if ($FieldNode['type']=='select-single') {
        
          $field.='<label id="'.$FieldNode['id'].'-label" for="'.$FieldNode['name'].'-select">'.$FieldNode['label'].'</label>';
          $field.='<select id="'.$FieldNode['id'].'-select" name="'.$FieldNode['name'].'"'.$required.' autofocus="autofocus" >';
          $field.='<option value="">please select ...</option>';
          
          $ObjForOptions=$FieldNode['options']['obj'];
          $EvtForOptions=$FieldNode['options']['evt'];
          
          $OptionsObj=new $ObjForOptions();
          $options= $OptionsObj->$EvtForOptions($Conf,$HTTP,$FieldNode['options']['obj']);
          
          for ($i=0; $i<count($options['list']['item']); $i++) {
                $field.='<option value="'.$options['list']['item'][$i]['id'].'"';

                if($FieldNode['value']==$options['list']['item'][$i]['id']){
                    $field.=' selected="selected"';
                }

                $field.='">'.$options['list']['item'][$i]['name'].'</option>';
                //echo $field;
          }
          
          $field.='</select>';
        
        } else if ($FieldNode['type']=='select-single-sync') {
        
            $field.='<label id="'.$FieldNode['id'].'-label" for="'.$FieldNode['name'].'-select">'.$FieldNode['label'].'</label>';
            $field.='<select id="'.$FieldNode['id'].'-select" name="'.$FieldNode['name'].'"'.$required.' autofocus="autofocus" >';
            $field.='<option value="">please select ...</option>';
            
            $ObjForOptions=$FieldNode['options']['obj'];
            $EvtForOptions=$FieldNode['options']['evt'];
            
            $OptionsObj=new $ObjForOptions();
            $options= $OptionsObj->$EvtForOptions($Conf,$HTTP,$FieldNode['options']['obj']);
            
            for ($i=0; $i<count($options['list']['item']); $i++) {
                $field.='<option value="'.$options['list']['item'][$i]['id'].'"';

                if($FieldNode['value']==$options['list']['item'][$i]['id']){
                    $field.=' selected="selected"';
                }

                $field.='">'.$options['list']['item'][$i]['name'].'</option>';
                //echo $field;
            }
            
            $field.='</select>';
        
        } else if ($FieldNode['type']=='select-single-domain') {
        
          $field.='<label id="'.$FieldNode['id'].'-label" for="'.$FieldNode['name'].'-select">'.$FieldNode['label'].'</label>';
          $field.='<select id="'.$FieldNode['id'].'-select" name="'.$FieldNode['name'].'"'.$required.' autofocus="autofocus" >';
          $field.='<option value="">please select ...</option>';
          
          $ObjForOptions=$FieldNode['options']['obj'];
          $EvtForOptions=$FieldNode['options']['evt'];
          
          $OptionsObj=new $ObjForOptions();
          $options= $OptionsObj->$EvtForOptions($Conf,$HTTP,$FieldNode['options']['obj'],$FieldNode['options']['domain']);
          
          for ($i=0; $i<count($options['list']['item']); $i++) {
              $field.='<option value="'.$options['list']['item'][$i]['id'].'"';

              if($FieldNode['value']==$options['list']['item'][$i]['id']){
                  $field.=' selected="selected"';
              }

              $field.='>'.$options['list']['item'][$i]['name'].'</option>';
              //echo $field;
          }
          
          $field.='</select>';
      
        } else if ($FieldNode['type']=='select-single-static') {
        
          $field.='<label id="'.$FieldNode['id'].'-label" for="'.$FieldNode['name'].'-select">'.$FieldNode['label'].'</label>';
          $field.='<select id="'.$FieldNode['id'].'-select" name="'.$FieldNode['name'].'"'.$required.' autofocus="autofocus" >';

          $field.='<option value="'.$FieldNode['value'].'">'.$FieldNode['label'].'</option>';
          
          for ($i=0; $i<count($FieldNode['options']['option']); $i++) {
            $field.='<option value="'.$FieldNode['options']['option'][$i]['value'].'">'.$FieldNode['options']['option'][$i]['label'].'</option>';
            //echo $field;
          }
          
          $field.='</select>';
      
        } else if ($FieldNode['type']=='select-boolean') {
        
          $field.='<label id="'.$FieldNode['id'].'-label" for="'.$FieldNode['name'].'-select">'.$FieldNode['label'].'</label>';
          $field.='<select id="'.$FieldNode['id'].'-select" name="'.$FieldNode['name'].'"'.$required.' autofocus="autofocus" >';
          $field.='<option value="">please select ...</option>';

          $field.='<option value="0"';if($FieldNode['value']=="0"){$field.=' selected="selected"';};$field.='>no</option>';
          $field.='<option value="1"';if($FieldNode['value']=="1"){$field.=' selected="selected"';};$field.='>yes</option>';
          
          $field.='</select>';
      
        } else if ($FieldNode['type']=='input-textarea') {

            $field.='<label id="'.$FieldNode['id'].'-label"  for="'.$FieldNode['name'].'-input">'.$FieldNode['label'].'</label>';
            $field.='<textarea id="'.$FieldNode['id'].'-input" name="'.$FieldNode['name'].'" placeholder="'.$FieldNode['name'].'"'.$required.' autofocus="autofocus" >'.$FieldNode['value'].'</textarea>';

        } else {

            $field.=$FieldNode['type'].' FIELD TYPE NOT SUPPORTED';
        }

            $field.='</li>';
        }

        return $field;
    }
}
?>