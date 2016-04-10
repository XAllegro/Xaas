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

            <!-- div id="context" class="context" -->
            
            <?php 
            	//XaApiTpl::ApplyTemplate($Conf,$HTTP,$WsData,$tpl,$TplParams)
                  //echo(XaApiTpl::ApplyTemplate($Conf,$HTTP,"","DropDown",""));
                  ?>
                <!--ul>
                    <li>Create User</li>
                    <li>View Roles</li>
                    <li>terzo</li>
                </ul-->
            <!-- /div -->

            <div class="detail" id="detail">
                <div class="content" id="content">
 
                    <?php

                        echo (XaApiTpl::ApplyTemplateToModel($Conf,$HTTP));
                      
                    ?>

                </div>
            </div>

        </div>
    </body>
</html>