<?php

require_once('XaLibApi.php');

/**
 * Description of XaLibApi
 *
 * @author alex
 */

class XaTplUserCreateForm {

    function __construct() {
        $this->ConfFile = file_get_contents("/XAllegro/Xaas/config/XaAdmin.json");
        $this->Conf = json_decode($this->ConfFile, true);
        $this->HTTP=new XaLibHttp();
    }
    
    function GetForm(array $WsData) {

    foreach($WsData['model'] as $k=>$v) {
        $model=$k;
     }

    $form='<script>
            CreateArgsCall={
            ResponseType:"Text",
            TargetId:"XaUserId",
            CallMethod:"'.$WsData['model'][$model]['form']['method'].'",
            CallAsync:"false",
            WithLoader:"no",
            LoaderTargetID:"",
            JsEval:"yes",
            WithAlert:"no",
            AlertMessage:"",
            FormId:"'.$WsData['model'][$model]['form']['id'].'"
            };
        </script>';

    //$form.='<input id="NextId"/>' ;

    $form.='<form 
        class="'.$WsData['model'][$model]['form']['class'].'" 
        id="'.$WsData['model'][$model]['form']['id'].'" 
        name="'.$WsData['model'][$model]['form']['name'].'" 
        method="'.$WsData['model'][$model]['form']['method'].'" 
        action="javascript:Xa.CallAction(\'\',\'Create.php?obj='.$WsData['model'][$model]['form']['obj'].'&evt='.$WsData['model'][$model]['form']['evt'].'\',CreateArgsCall);"
        >

        <fieldset>
            <legend class="LogHomePage" style="line-height:2em" >
		<img/>
                '.$WsData['model'][$model]['fieldset']['legend'].'
            </legend>
            <ul>
    ';

        for($i=0; $i<count($WsData['model'][$model]['fieldset']['field']); $i++) {
            $form.= $this->BuildField($WsData['model'][$model]['fieldset']['field'][$i]);
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