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
 
    function Create(array $Conf,XaLibHttp &$HTTP,array &$WsData,$TplParams=""):string {
        
        $obj=$this->GetTplParam($HTTP,$TplParams,"obj");
 
        $TargetId=$this->GetTplParam($HTTP,$TplParams,"TargetId");
        $ResponseType=$this->GetTplParam($HTTP,$TplParams,"ResponseType");
        $WithAlert=$this->GetTplParam($HTTP,$TplParams,"WithAlert");
        $PostActionArgs=$this->GetTplParam($HTTP,$TplParams,"PostActionArgs");

        $FormClass="form form-1-column";
        $FormName=$obj."-Create";
        $FormId=$obj."-Create-id";
        $FormMethod="POST";

        //$FormAction="javascript:Xa.CallAction('','XaApi.php?obj=".$obj."&evt=Create',{&quot;ResponseType&quot;:&quot;".$ResponseType."&quot;,&quot;TargetId&quot;:&quot;".$TargetId."&quot;,&quot;FormId&quot;:&quot;".$FormId."&quot;,&quot;WithAlert&quot;:&quot;".$WithAlert."&quot;,&quot;PostActionArgs&quot;:".$PostActionArgs."})";;

        $RedTo=$this->GetTplParam($HTTP,$TplParams,"RedTo");
        $RedKey=$this->GetTplParam($HTTP,$TplParams,"RedKey");

        if($RedTo!=""){
            
            $FormAction="XaApi.php?obj=".$obj;
            $FormAction.="&evt=Create";
            $FormAction.="&RedTo=".$RedTo;
            $FormAction.="&RedKey=".$RedKey;
        } else {
     
            $FormAction="javascript:Xa.CallAction('','XaApi.php?obj=".$obj;
            $FormAction.="&evt=Create',{&quot;ResponseType&quot;:&quot;".$ResponseType."&quot;,&quot;FormId&quot;:&quot;".$FormId."&quot;})";

        }
        
        
        $form='<form ';
        $form.='class="'.$FormClass.'"';
        $form.='name="'.$FormName.'"';
        $form.='id="'.$FormId.'"';
        $form.='method="'.$FormMethod.'"';
        $form.='action="'.$FormAction.'"';
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

        $form.='<li><button type="submit">Submit</button><br/><br/></li>';

        $form.='</ul>';
        $form.='</fieldset>';
        $form.="</form>";

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

        if ($FieldNode['create']=='yes') {
        
            $field='<li>';

        if ($FieldNode['type']=='input-hidden') {

            $field.='<label id="'.$FieldNode['id'].'-label"  for="'.$FieldNode['name'].'-input">'.$FieldNode['label'].'</label>';
            $field.='<input id="'.$FieldNode['id'].'-input" name="'.$FieldNode['name'].'" type="text" placeholder="'.$FieldNode['name'].'" required="'.$FieldNode['required'].'" autofocus="autofocus" />';
        
        } else if ($FieldNode['type']=='input-text') {

            $field.='<label id="'.$FieldNode['id'].'-label"  for="'.$FieldNode['name'].'-input">'.$FieldNode['label'].'</label>';
            $field.='<input id="'.$FieldNode['id'].'-input" name="'.$FieldNode['name'].'" type="text" placeholder="'.$FieldNode['name'].'" required="'.$FieldNode['required'].'" autofocus="autofocus" />';

        } else if ($FieldNode['type']=='input-number') {
          
          $field.='<label id="'.$FieldNode['id'].'-label"  for="'.$FieldNode['name'].'-input">'.$FieldNode['label'].'</label>';
          $field.='<input type="number" id="'.$FieldNode['id'].'-input" name="'.$FieldNode['name'].'" placeholder="'.$FieldNode['name'].'" maxlength="'.$FieldNode['maxlength'].'" size="'.$FieldNode['size'].'"';
          
          if($FieldNode['required']=='yes'){
            $field.=' required="true"';
          }
          
          $field.= ' autofocus="autofocus" />';

        } else if ($FieldNode['type']=='input-email') {
          
          $field.='<label id="'.$FieldNode['id'].'-label"  for="'.$FieldNode['name'].'-input">'.$FieldNode['label'].'</label>';
          $field.='<input type="email" pattern="[^ @]*@[^ @]*" id="'.$FieldNode['id'].'-input" name="'.$FieldNode['name'].'" placeholder="'.$FieldNode['name'].'" maxlength="'.$FieldNode['maxlength'].'" size="'.$FieldNode['size'].'"';
          
          if($FieldNode['required']=='yes'){
            $field.=' required="true"';
          }
          
          $field.= ' autofocus="autofocus" />';

        } else if ($FieldNode['type']=='select-single') {
        
          $field.='<label id="'.$FieldNode['id'].'-label" for="'.$FieldNode['name'].'-select">'.$FieldNode['label'].'</label>';
          $field.='<select id="'.$FieldNode['id'].'-select" name="'.$FieldNode['name'].'" required="'.$FieldNode['required'].'" autofocus="autofocus" >';
          $field.='<option value="" selected="selected">please select ...</option>';
          
          $ObjForOptions=$FieldNode['options']['obj'];
          $EvtForOptions=$FieldNode['options']['evt'];
          
          $OptionsObj=new $ObjForOptions();
          $options= $OptionsObj->$EvtForOptions($Conf,$HTTP,$FieldNode['options']['obj']);
          
            for ($i=0; $i<count($options['list']['item']); $i++) {
                 $field.='<option value="'.$options['list']['item'][$i]['id'].'">'.$options['list']['item'][$i]['name'].'</option>';
                 //echo $field;
            }
          
          $field.='</select>';
        
        } else if ($FieldNode['type']=='select-single-sync') {
        
            $field.='<label id="'.$FieldNode['id'].'-label" for="'.$FieldNode['name'].'-select">'.$FieldNode['label'].'</label>';
            $field.='<select id="'.$FieldNode['id'].'-select" name="'.$FieldNode['name'].'" required="'.$FieldNode['required'].'" autofocus="autofocus" >';
            $field.='<option value="" selected="selected">please select ...</option>';
            
            $ObjForOptions=$FieldNode['options']['obj'];
            $EvtForOptions=$FieldNode['options']['evt'];
            
            $OptionsObj=new $ObjForOptions();
            $options= $OptionsObj->$EvtForOptions($Conf,$HTTP,$FieldNode['options']['obj']);
            
              for ($i=0; $i<count($options['list']['item']); $i++) {
                   $field.='<option value="'.$options['list']['item'][$i]['id'].'">'.$options['list']['item'][$i]['name'].'</option>';
                   //echo $field;
              }
            
            $field.='</select>';
        
        } else if ($FieldNode['type']=='select-single-domain') {
        
          $field.='<label id="'.$FieldNode['id'].'-label" for="'.$FieldNode['name'].'-select">'.$FieldNode['label'].'</label>';
          $field.='<select id="'.$FieldNode['id'].'-select" name="'.$FieldNode['name'].'" required="'.$FieldNode['required'].'" autofocus="autofocus" >';
          $field.='<option value="" selected="selected">please select ...</option>';
          
          $ObjForOptions=$FieldNode['options']['obj'];
          $EvtForOptions=$FieldNode['options']['evt'];
          
          $OptionsObj=new $ObjForOptions();
          $options= $OptionsObj->$EvtForOptions($Conf,$HTTP,$FieldNode['options']['obj'],$FieldNode['options']['domain']);
          
            for ($i=0; $i<count($options['list']['item']); $i++) {
                 $field.='<option value="'.$options['list']['item'][$i]['id'].'">'.$options['list']['item'][$i]['name'].'</option>';
                 //echo $field;
            }
          
          $field.='</select>';
      
        } else if ($FieldNode['type']=='select-boolean') {
        
          $field.='<label id="'.$FieldNode['id'].'-label" for="'.$FieldNode['name'].'-select">'.$FieldNode['label'].'</label>';
          $field.='<select id="'.$FieldNode['id'].'-select" name="'.$FieldNode['name'].'" required="'.$FieldNode['required'].'" autofocus="autofocus" >';
          $field.='<option value="" selected="selected">please select ...</option>';
          
          $field.='<option value="0">no</option>';
          $field.='<option value="1">yes</option>';
          
          $field.='</select>';
      
        } else if ($FieldNode['type']=='input-textarea') {

            $field.='<label id="'.$FieldNode['id'].'-label"  for="'.$FieldNode['name'].'-input">'.$FieldNode['label'].'</label>';
            $field.='<textarea id="'.$FieldNode['id'].'-input" name="'.$FieldNode['name'].'" placeholder="'.$FieldNode['name'].'" required="'.$FieldNode['required'].'" autofocus="autofocus" ></textarea>';

        } else {

            $field.=$FieldNode['type'].' FIELD TYPE NOT SUPPORTED';
        }

            $field.='</li>';
        }

        return $field;
    }
}
?>