<?php

require_once('XaLibApi.php');

/**
 * Description of XaLibApi
 *
 * @author alex
 */

class XaTplCreateForm {

    function __construct() {
    }
    
    //function GetForm(array &$Data,string &$Style,string &$Action,array &$OptionNames, array &$OptionsValues) {
    function GetForm() {

    $ConfFile = file_get_contents("/XAllegro/Xaas/config/XaAdmin.json");
    $Conf = json_decode($ConfFile, true);
    $HTTP=new XaLibHttp();

    $form='<script>
            UserCreateArgsCall={
            ResponseType:"Html",
            TargetId:"detail",
            CallMethod:"POST",
            CallAsync:"true",
            WithLoader:"no",
            LoaderTargetID:"",
            JsEval:"yes",
            WithAlert:"no",
            AlertMessage:"",
            FormId:"UserCreateFrm"
            };
        </script>';

    $form.='<form class="form form-1-column" id="UserCreateFrm" name="UserCreateFrm" method="POST" action="javascript:Xa.CallAction(\'\',\'XaApi.php?obj=XaUser&evt=Create\',UserCreateArgsCall);">

		               <fieldset>
                		  <legend class="LogHomePage" style="line-height:2em" >
		                      <img/>
                		  </legend>

		                  <ul>
                		      <li>
		                          <label id="name-label" for="name-input">Name</label>
                		          <input id="name-input" name="name" type="text" placeholder="name" required="required" autofocus="autofocus" />
		                      </li>
                		      <li>
		                          <label id="surname-label" for="surname-input">Name</label>
                		          <input id="surname-input" name="surname" type="text" placeholder="surname" required="required" autofocus="autofocus" />
		                      </li>
                		      <li>
		                          <label id="XaUserType_ID-label" for="XaUserType_ID-select">Name</label>
                		          <select id="XaUserType_ID-select" name="XaUserType_ID"required="required" autofocus="autofocus" >
						<option value="" selected="selected">please select ...</option>

    ';

    $usertype=new XaUserType();
    $options= $usertype->ListAsOptions($Conf,$HTTP,'XaUserType');

		for ($i=0; $i<count($options['list']['item']); $i++) {
                     $form.='<option value="'.$options['list']['item'][$i]['id'].'">'.$options['list']['item'][$i]['name'].'</option>';
		}

    $form.='
                		          </select>
		                      </li>
                		      <li>
		                          <button type="submit">Submit</button><br/><br/>
                		      </li>
		                   </ul>
		               </fieldset>
		            </form>
';
return($form);
    }
}
?>