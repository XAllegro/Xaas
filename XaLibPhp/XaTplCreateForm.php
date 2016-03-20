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

    $pippo=' <form  class="form form-1-column" id="UserCreateFrm" name="UserCreateFrm" method="POST" action="XaApi.php?obj=XaUser&evt=Create">

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
/*
						$options=$this->UserTypeListAsOptions($Conf,$HTTP);
						for ($i=0; $i<count($options['list']['item']); $i++) {
							///echo('<option value="'.$options['list']['item'][$i]['id'].'">'.$options['list']['item'][$i]['name'].'</option>');
                            $pippo.='<option value="'.$options['list']['item'][$i]['id'].'">'.$options['list']['item'][$i]['name'].'</option>';
						}
*/
$pippo.='
                		          </select>
		                      </li>
                		      <li>
		                          <button type="submit">Submit</button><br/><br/>
                		      </li>
		                   </ul>
		               </fieldset>
		            </form>
';
return($pippo);
    }
}
?>