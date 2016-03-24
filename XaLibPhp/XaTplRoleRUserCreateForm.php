<?php

require_once('XaLibApi.php');

/**
 * Description of XaLibApi
 *
 * @author alex
 */

class XaTplRoleRUserCreateForm {

    function __construct() {
        $this->ConfFile = file_get_contents("/XAllegro/Xaas/config/XaAdmin.json");
        $this->Conf = json_decode($this->ConfFile, true);
        $this->HTTP=new XaLibHttp();
    }
    
    function GetForm(array $WsData) {

    foreach($WsData['createfrm'] as $k=>$v) {
        $model=$k;
     }

    $form='<script>
            CreateArgsCall={
            ResponseType:"Html",
            TargetId:"role_box",
            CallMethod:"'.$WsData['createfrm'][$model]['form']['method'].'",
            CallAsync:"true",
            WithLoader:"no",
            LoaderTargetID:"",
            JsEval:"yes",
            WithAlert:"no",
            AlertMessage:"",
            FormId:"'.$WsData['createfrm'][$model]['form']['id'].'"
            };
        </script>';

    $form.='<form 
        class="'.$WsData['createfrm'][$model]['form']['class'].'" 
        id="'.$WsData['createfrm'][$model]['form']['id'].'" 
        name="'.$WsData['createfrm'][$model]['form']['name'].'" 
        method="'.$WsData['createfrm'][$model]['form']['method'].'" 
        action="javascript:Xa.CallAction(\'\',\'Create.php?obj='.$WsData['createfrm'][$model]['form']['obj'].'&evt='.$WsData['createfrm'][$model]['form']['evt'].'\',CreateArgsCall);"
        >

        <input id="XaUser_ID" name="XaUser_ID" value="'.$this->HTTP->GetHttpParam('XaUser_ID').'"/>

        <fieldset>
            <legend class="LogHomePage" style="line-height:2em" >
		<img/>
                '.$WsData['createfrm'][$model]['fieldset']['legend'].'
            </legend>
            <ul>
    ';

        for($i=0; $i<count($WsData['createfrm'][$model]['fieldset']['field']); $i++) {
if ($WsData['createfrm'][$model]['fieldset']['field'][$i]['id']!='XaUser_ID') {
            $form.= $this->BuildField($WsData['createfrm'][$model]['fieldset']['field'][$i]);
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

    function BuildField(array $FieldNode) {

        if ($FieldNode['create']=='yes') {

            $field='<li>';

            if ($FieldNode['type']=='input-text') {
                $field.='<label id="'.$FieldNode['id'].'-label"  for="'.$FieldNode['name'].'-input">'.$FieldNode['label'].'</label>';
           	$field.='<input id="'.$FieldNode['id'].'-input" name="'.$FieldNode['name'].'" type="text" placeholder="'.$FieldNode['name'].'" required="'.$FieldNode['required'].'" autofocus="autofocus" />';
            } else if ($FieldNode['type']=='select-single') {
                $field.='<label id="'.$FieldNode['id'].'-label" for="'.$FieldNode['name'].'-select">'.$FieldNode['label'].'</label>';
                $field.='<select id="'.$FieldNode['id'].'-select" name="'.$FieldNode['name'].'" required="'.$FieldNode['required'].'" autofocus="autofocus" >';
                $field.='<option value="" selected="selected">please select ...</option>';

                $obj=$FieldNode['options']['obj'];
                $evt=$FieldNode['options']['evt'];
                $object=new $obj();

                $options= $object->$evt($this->Conf,$this->HTTP,$obj);

		for ($i=0; $i<count($options['list']['item']); $i++) {
                     $field.='<option value="'.$options['list']['item'][$i]['id'].'">'.$options['list']['item'][$i]['name'].'</option>';
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