<?php require_once ('XaPage.php');?>
<html id="html">

    <head>
        <?php require_once ('head.php');?>
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

            <!-- div id="context" class="context"-->
                <!--ul>
                    <li>Create User</li>
                    <li>View Roles</li>
                    <li>terzo</li>
                </ul-->
            <!-- /div-->

            <div class="detail" id="detail">
                <div class="content" id="content">

                    <a href="XaPage.php?obj=XaUser&evt=GetXmlModel&tpl=Create&TplParams={%22obj%22:%22XaUser%22}&lay=Standalone">CREATE USER</a>
                    <br/>
                    <a href="XaPage.php?obj=XaUserType&evt=GetXmlModel&tpl=Create&TplParams={%22obj%22:%22XaUserType%22}&lay=Explorer">CREATE USER TYPE</a>
                    <br/>
                    <a href="XaPage.php?obj=XaUser&evt=List&tpl=List&params={%22order_by%22:%22surname%22}&TplParams={%22actions%22:%22yes%22,%22title%22:%22Lista%20Utenti%22}&lay=Standalone">LIST USER</a>
                    <br/>
                    <a href="XaPage.php?obj=XaUser&evt=Read&params={%22id%22:3}&tpl=Read&lay=Standalone&id=3">READ USER</a>

                    
                </div>
            
            </div>
    
        </div>
    </body>
</html>