<?php require_once ('XaPage.php');?>

<html id="html">
	<head>
		<?php require_once ('head.php');?>
	</head>
<body>

<!-- ASYNC EXAMPLE -->
<!-- script>
	var args={
		{ResponseType:&quot;Html&quot;,TargetId:&quot;prova1&quot;,JsEval:&quot;yes&quot;}
	};

	Xa.CallAction("","XaPage.php?obj=XaUser&evt=GetXmlModel&tpl=Create&lay=Included",{ResponseType:&quot;Html&quot;,TargetId:&quot;prova1&quot;,JsEval:&quot;yes&quot;});
</script-->

<!-- ASYNC EXAMPLE -->
	<script>
		var args={
			ResponseType:"Html",
			TargetId:"prova2",
			JsEval:"yes"
    	};

		Xa.CallAction("","XaPage.php?obj=XaUserType&evt=GetXmlModel&tpl=Create&lay=Included",args);
	</script>

<div>

oeimwpeoiwqpecrmwoericmqw<br/>
rcqwc<br/>
wercqwpirmc<br/>
qwerimcqw<br/>
erimcq<br/>
wcrim<br/>
qopwcimroq<br/>
wmir<br/>
qw<br/>
eimwpeoiwqpecrmwoericmqw<br/>
rcqwc<br/>
wercqwpirmc<br/>
qwerimcqw<br/>
erimcq<br/>
wcrim<br/>
qopwcimroq<br/>
wmir<br/>
qw<br/>
</div>
<br/>

    <div class="tabs">
    	<div class="tab">
    		<input onclick="Xa.CallAction('','XaPage.php?obj=XaUser&evt=GetXmlModel&tpl=Create&lay=Included',{ResponseType:&quot;Html&quot;,TargetId:&quot;prova1&quot;,JsEval:&quot;yes&quot;});" type="radio" id="tab-1" name="tab-group-1" checked>
    		<label class="style-label" for="tab-1">Tab One</label>
    		<div id="prova1" class="content"></div> 
    	</div>
    	<div class="tab">
    		<input onclick="javascript:alert('pippo')" type="radio" id="tab-2" name="tab-group-1">
    		<label class="style-label" for="tab-2">Tab Two</label>
    		<div id="prova2" class="content"></div> 
    	</div>
		<div class="tab">
    		<input type="radio" id="tab-3" name="tab-group-1">
    		<label class="style-label" for="tab-3">Tab Three</label>

 		<div class="content">
            <!-- SYNC EXAMPLE -->
    		<?php
               $XaUser=new XaUser();
               $WsData=$XaUser->Execute($Conf,$HTTP,"List","XaUser");
    
               $Tpl = new XaTplList();
               $Content = $Tpl->List($Conf,$HTTP,$WsData);
               echo $Content;
            ?>
    		</div> 
    	</div>
    </div>

</body>
</html>