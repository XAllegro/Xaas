<?php require_once ('XaPage.php');?>
<html id="html">

    <head>
        <?php require_once ('head.php');?>
        
	<style>

</style>

    </head>

    <body>

    <?php require_once ('menu.php');?>


        <header id="header">
            <?php require_once ('header.php');?>
        </header>

        <div class="explorer">


            <div class="nav">
                 <?php require_once ('nav.php');?>
            </div>

            <div id="context" class="context">
                <!--ul>
                    <li>Create User</li>
                    <li>View Roles</li>
                    <li>terzo</li>
                </ul-->
                
                
            </div>

            <div class="detail" id="detail">
                <div class="content" id="content">

                    <a href="XaPage.php?obj=XaUser&evt=GetXmlModel&tpl=Create&lay=Standalone">CREATE::::XaPage.php?obj=XaUser&evt=GetXmlModel&tpl=Create&lay=Standalone</a>
                    <br/>
                    <a href="XaPage.php?obj=XaUserType&evt=GetXmlModel&tpl=Create&lay=Standalone">CREATE::::XaPage.php?obj=XaUserType&evt=GetXmlModel&tpl=Create&lay=Standalone</a>
                    <br/>
                    <a href="XaPage.php?obj=XaUser&evt=List&tpl=List&TplParams={%22actions%22:%22yes%22}&lay=Standalone">LIST::::XaPage.php?obj=XaUser&evt=List&tpl=List&lay=Standalone</a>
                    <br/>
                    <a href="XaPage.php?obj=XaUser&evt=Read&tpl=Read&lay=Standalone&id=3">READ::::XaPage.php?obj=XaUser&evt=Read&tpl=Read&lay=Standalone&id=3</a>

                    
                </div>
            
            </div>
    
        </div>
    </body>
</html>