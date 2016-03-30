
<script>

function ToggleMainMenu () {

	var v=document.getElementById("myNav").style.width;

		if(!v || v==0 || v=="0%") {
			document.getElementById("myNav").style.width = "100%";
		} else {
			 document.getElementById("myNav").style.width = "0%";
		}
}

</script>

<div id="myNav" class="overlay">
 
    <!-- a href="javascript:void(0)" class="closebtn" onclick="closeNav()">X</a-->
 
 		<div class="overlay-content">
  
        	<div class="box">
                <p class="title">Configurations</p>
                <p class="IconGo">
               		<a href="?obj=XaOuUi&evt=CreateFrm"></a>
                </p>
        	</div>

        	<div class="box">
                <p class="title">Users Admin</p>
                <p class="IconGo">
                	<a href="MyPage.php"></a>
				</p>
        	</div>
 
  </div>
</div>