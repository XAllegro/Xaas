<ul class="Toolbar">
    <li class="ToolbarSections ToolbarLeft">

        <span class="Icon IconXAllegro"></span>

        <span id="IconMyApps" class="Icon IconMyApps">
            <a href="#" onclick="ToggleMainMenu()"></a>
        </span>

        <span class="Icon IconDefaultPage">
            <a href="MyPage.php"></a>
        </span>

        <span class="Icon IconSearch">
            <a href="#"></a>
        </span>

    </li>
    <li class="ToolbarSections ToolbarRight">

       <span class="Icon IconSettings">
          <a href="#"></a>
       </span>

       <span class="Icon IconHelp">
          <a href="#"></a>
       </span>        

       <span>
           <a href="XaApi.php?obj=XaUserLogin&evt=Logout" onclick="">Logout</a>
       </span>
    </li>
</ul>

<?php

    if(array_key_exists("AppIconColor",$Conf['MyApp'])){
    
        echo '<script>document.getElementById("IconMyApps").style.color = "'.$Conf['MyApp']['AppIconColor'].'"</script>';
    }
?>