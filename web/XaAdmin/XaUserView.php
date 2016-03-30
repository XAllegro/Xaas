<?php require_once ('XaPage.php');?>

<html id="html">
	<head>
		<?php require_once ('head.php');?>
	</head>
<body>


<!-- numero dei tab
contenuto dei tab
 -->

<?php
$id=$HTTP->GetHttpParam("id");
?>

	<div class="content">
	<?php
               $XaUser=new XaUser();
               $WsData=$XaUser->ExecuteSync($Conf,$HTTP,'Read','XaUser','{"id":"'.$id.'"}');

               $Tpl = new XaTplRead();
               $Content = $Tpl->Read($Conf,$HTTP,$WsData);
               echo $Content;
        ?>
    	</div> 

<br/><br/>

    <div class="tabs">
    	<div class="tab">
    		<input  type="radio" id="tab-1" name="tab-group-1" checked onclick="Xa.CallAction('','XaPage.php?obj=XaRbacRoleRXaUser&evt=ListByUser&params={&quot;XaUser_ID&quot;:&quot;<?php echo $id; ?>&quot;}&tpl=List&lay=Included',{ResponseType:&quot;Html&quot;,TargetId:&quot;tab-div-1&quot;,JsEval:&quot;yes&quot;});">
    		<label class="style-label" for="tab-1">Roles</label>
    		<div id="tab-div-1" class="content">
		<?php
       	           $XaRbacRoleRXaUser=new XaRbacRoleRXaUser();
                   $WsData=$XaRbacRoleRXaUser->ExecuteSync($Conf,$HTTP,'ListByUser','XaRbacRoleRXaUser','{"XaUser_ID":"'.$id.'"}');

    	           $Tpl = new XaTplList();
        	   $Content = $Tpl->List($Conf,$HTTP,$WsData);
	           echo $Content;
        	?>
                </div> 
    	</div>
    	<div class="tab">
    		<input  type="radio" id="tab-2" name="tab-group-1" onclick="Xa.CallAction('','XaPage.php?obj=XaUserAddressGeo&evt=ListByUser&params={&quot;XaUser_ID&quot;:&quot;<?php echo $id; ?>&quot;}&tpl=List&lay=Included',{ResponseType:&quot;Html&quot;,TargetId:&quot;tab-div-2&quot;,JsEval:&quot;yes&quot;});">
    		<label class="style-label" for="tab-2">Addresses</label>
    		<div id="tab-div-2" class="content"></div> 
    	</div>
    	<div class="tab">
    		<input  type="radio" id="tab-3" name="tab-group-1" onclick="Xa.CallAction('','XaPage.php?obj=XaUserAddressPhone&evt=ListByUser&params={&quot;XaUser_ID&quot;:&quot;<?php echo $id; ?>&quot;}&tpl=List&lay=Included',{ResponseType:&quot;Html&quot;,TargetId:&quot;tab-div-3&quot;,JsEval:&quot;yes&quot;});">
    		<label class="style-label" for="tab-3">Phones</label>
    		<div id="tab-div-3" class="content"></div> 
    	</div>
        <div class="tab">
    		<input  type="radio" id="tab-4" name="tab-group-1" onclick="Xa.CallAction('','XaPage.php?obj=XaUserAddressMail&evt=ListByUser&params={&quot;XaUser_ID&quot;:&quot;<?php echo $id; ?>&quot;}&tpl=List&lay=Included',{ResponseType:&quot;Html&quot;,TargetId:&quot;tab-div-4&quot;,JsEval:&quot;yes&quot;});">
    		<label class="style-label" for="tab-4">Emails</label>
    		<div id="tab-div-4" class="content"></div> 
    	</div>
    </div>

</body>
</html>