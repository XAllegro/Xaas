<?php require_once ('XaPage.php');?>

<?php

?>

    	<div class="tab">
    		<input  type="radio" id="tab-1" name="tab-group-1" checked onclick="
                    var UserId=document.getElementById('UserId').value;
                    if(UserId!=''){Xa.CallAction('',
                    'XaPage.php?obj=XaRbacRoleRXaUser&evt=GetXmlModel&tpl=Create&lay=Included&params={&quot;type&quot;:&quot;WithExternalKey&quot;,&quot;XaUser_ID&quot;:&quot;'+UserId+'&quot;}&TplParams={&quot;obj&quot;:&quot;XaRbacRoleRXaUser&quot;,&quot;ResponseType&quot;:&quot;Text&quot;,&quot;WithAlert&quot;:&quot;yes&quot;}',
                    {&quot;TargetId&quot;:&quot;tab-div-1&quot;,&quot;ResponseType&quot;:&quot;Html&quot;,&quot;JsEval&quot;:&quot;yes&quot;}
                    );}
    		">
    		<label class="style-label" for="tab-1">Roles</label>
    		<div id="tab-div-1" class="content"></div> 
    	</div>
    	<div class="tab">
                <input  type="radio" id="tab-2" name="tab-group-1" onclick="
                    var UserId=document.getElementById('UserId').value;
                    if(UserId!=''){Xa.CallAction('',
                    'XaPage.php?obj=XaUserAddressGeo&evt=GetXmlModel&tpl=Create&lay=Included&params={&quot;type&quot;:&quot;WithExternalKey&quot;,&quot;XaUser_ID&quot;:&quot;'+UserId+'&quot;}&TplParams={&quot;obj&quot;:&quot;XaUserAddressGeo&quot;,&quot;ResponseType&quot;:&quot;Text&quot;,&quot;WithAlert&quot;:&quot;yes&quot;}',
                    {&quot;TargetId&quot;:&quot;tab-div-2&quot;,&quot;ResponseType&quot;:&quot;Html&quot;,&quot;JsEval&quot;:&quot;yes&quot;}
                    );}
                ;">
    		<label class="style-label" for="tab-2">Addresses</label>
    		<div id="tab-div-2" class="content"></div> 
    	</div>
    	<div class="tab">
                <input  type="radio" id="tab-3" name="tab-group-1" onclick="
                    var UserId=document.getElementById('UserId').value;
                    if(UserId!=''){Xa.CallAction('',
                    'XaPage.php?obj=XaUserAddressPhone&evt=GetXmlModel&tpl=Create&lay=Included&params={&quot;type&quot;:&quot;WithExternalKey&quot;,&quot;XaUser_ID&quot;:&quot;'+UserId+'&quot;}&TplParams={&quot;obj&quot;:&quot;XaUserAddressPhone&quot;,&quot;ResponseType&quot;:&quot;Text&quot;,&quot;WithAlert&quot;:&quot;yes&quot;}',
                    {&quot;TargetId&quot;:&quot;tab-div-3&quot;,&quot;ResponseType&quot;:&quot;Html&quot;,&quot;JsEval&quot;:&quot;yes&quot;}
                    );}
                ;">
    		<label class="style-label" for="tab-3">Phones</label>
    		<div id="tab-div-3" class="content"></div> 
    	</div>
        <div class="tab">
                <input  type="radio" id="tab-4" name="tab-group-1" onclick="
                    var UserId=document.getElementById('UserId').value;
                    if(UserId!=''){Xa.CallAction('',
                    'XaPage.php?obj=XaUserAddressMail&evt=GetXmlModel&tpl=Create&lay=Included&params={&quot;type&quot;:&quot;WithExternalKey&quot;,&quot;XaUser_ID&quot;:&quot;'+UserId+'&quot;}&TplParams={&quot;obj&quot;:&quot;XaUserAddressMail&quot;,&quot;ResponseType&quot;:&quot;Text&quot;,&quot;WithAlert&quot;:&quot;yes&quot;}',
                    {&quot;TargetId&quot;:&quot;tab-div-4&quot;,&quot;ResponseType&quot;:&quot;Html&quot;,&quot;JsEval&quot;:&quot;yes&quot;}
                    );}
                ;">

    		<label class="style-label" for="tab-4">Emails</label>
    		<div id="tab-div-4" class="content"></div> 
    	</div>