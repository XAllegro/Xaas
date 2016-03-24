<?php

require_once('XaLibApi.php');

/**
 * Description of XaLibApi
 *
 * @author alex
 */

class XaTplRoleRUserUpdateForm {

    function __construct() {
        $this->ConfFile = file_get_contents("/XAllegro/Xaas/config/XaAdmin.json");
        $this->Conf = json_decode($this->ConfFile, true);
        $this->HTTP=new XaLibHttp();
    }
    
    function GetForm(array $WsModel,$WsData) {

    foreach($WsModel['model'] as $k=>$v) {
        $model=$k;
     }

    $form='<script>
            UpdateArgsCall={
            ResponseType:"Text",
            TargetId:"",
            CallMethod:"'.$WsModel['model'][$model]['update_form']['method'].'",
            CallAsync:"'.$WsModel['model'][$model]['update_form']['async'].'",
            WithLoader:"no",
            LoaderTargetID:"",
            JsEval:"yes",
            WithAlert:"yes",
            AlertMessage:"",
            FormId:"'.$WsModel['model'][$model]['update_form']['id'].'"
            };
        </script>';

    $form.='<form 
        class="'.$WsModel['model'][$model]['update_form']['class'].'" 
        id="'.$WsModel['model'][$model]['update_form']['id'].'" 
        name="'.$WsModel['model'][$model]['update_form']['name'].'" 
        method="'.$WsModel['model'][$model]['update_form']['method'].'" 
        action="javascript:Xa.CallAction(\'\',\'Update.php?obj='.$WsModel['model'][$model]['update_form']['obj'].'&evt='.$WsModel['model'][$model]['update_form']['evt'].'\',UpdateArgsCall);"
        >

        <input id="id" name="id" value="'.$WsData['read']['id'].'"/>

        <fieldset>
            <legend class="LogHomePage" style="line-height:2em" >
		<img/>
                '.$WsModel['model'][$model]['fieldset']['update_legend'].'
            </legend>
            <ul>
    ';

        for($i=0; $i<count($WsModel['model'][$model]['fieldset']['field']); $i++) {
if ($WsModel['model'][$model]['fieldset']['field'][$i]['id']!='XaUser_ID') {
            $FName=$WsModel['model'][$model]['fieldset']['field'][$i]['name'];
            $FValue=$WsData['read'][$FName];
            $form.= $this->BuildField($WsModel['model'][$model]['fieldset']['field'][$i],$FValue);
}
        }
 
    $form.='
                <li>
                    <button type="submit">Submit</button><br/><br/>
                </li>
            </ul>
        </fieldset>
    </form>
    ';

    return($form);

    }

    function BuildField(array $FieldNode,string $FValue) {

        if ($FieldNode['update']=='yes') {

            $field='<li>';

            if ($FieldNode['type']=='input-text') {
                $field.='<label id="'.$FieldNode['id'].'-label"  for="'.$FieldNode['name'].'-input">'.$FieldNode['label'].'</label>';
           	$field.='<input value="'.$FValue.'" id="'.$FieldNode['id'].'-input" name="'.$FieldNode['name'].'" type="text" placeholder="'.$FieldNode['name'].'" required="'.$FieldNode['required'].'" autofocus="autofocus" />';
            } else if ($FieldNode['type']=='select-single') {
                $field.='<label id="'.$FieldNode['id'].'-label" for="'.$FieldNode['name'].'-select">'.$FieldNode['label'].'</label>';
                $field.='<select id="'.$FieldNode['id'].'-select" name="'.$FieldNode['name'].'" required="'.$FieldNode['required'].'" autofocus="autofocus" >';
                $field.='<option value="">please select ...</option>';

                $obj=$FieldNode['options']['obj'];
                $evt=$FieldNode['options']['evt'];
                $object=new $obj();

                $options= $object->$evt($this->Conf,$this->HTTP,$obj);

		for ($i=0; $i<count($options['list']['item']); $i++) {
                     $selected='';
                     if ($options['list']['item'][$i]['id']==$FValue) {$selected=' selected="selected"';};
                     $field.='<option value="'.$options['list']['item'][$i]['id'].'"'.$selected.'>'.$options['list']['item'][$i]['name'].'</option>';
		}

                $field.='</select>';
            } else if ($FieldNode['type']=='input-textarea') {
                $field.='<label id="'.$FieldNode['id'].'-label"  for="'.$FieldNode['name'].'-input">'.$FieldNode['label'].'</label>';
           	$field.='<textarea id="'.$FieldNode['id'].'-input" name="'.$FieldNode['name'].'" placeholder="'.$FieldNode['name'].'" required="'.$FieldNode['required'].'" autofocus="autofocus" ></textarea>';
            } else {
                $field.='FIELD TYPE NOT SUPPORTED';
            }

            $field.='</li>';

        }

        return $field;
    }

}
?>