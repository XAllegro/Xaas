<?php require_once ('XaPage.php');?>

<html id="html">
	<head>
		<?php require_once ('head.php');?>
	</head>
<body>


<!-- numero dei tab
contenuto dei tab
 -->

	<input id="UserId"/>

	<div class="content">
	<?php
               $XaUser=new XaUser();
               $WsData=$XaUser->ExecuteSync($Conf,$HTTP,'GetXmlModel','XaUser','');

               $Tpl = new XaTplCreate();
               // obj,TargetId,ResponseType belong to form action
               $Content = $Tpl->Create($Conf,$HTTP,$WsData,'{"obj":"XaUser","TargetId":"UserId","ResponseType":"Text"}');
               echo $Content;
        ?>
    	</div> 

<br/><br/>

    <div class="tabs">
    	<div class="tab">
    		<input  type="radio" id="tab-1" name="tab-group-1" checked onclick="var UserId=document.getElementById('UserId').value;if(UserId!=''){Xa.CallAction('','XaPage.php?obj=XaRbacRoleRXaUser&evt=ListByUser&params={&quot;XaUser_ID&quot;:&quot;'+UserId+'&quot;}&tpl=List&lay=Included',{ResponseType:&quot;Html&quot;,TargetId:&quot;tab-div-1&quot;,JsEval:&quot;yes&quot;})};">
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
    </div>

</body>
</html>