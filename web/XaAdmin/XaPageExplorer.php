<?php require_once ('XaPage.php');?>

<html id="html">

    <head>
        <?php require_once ('head.php');?>
    </head>

    <body>

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
 
                    <?php

                        echo (XaApiTpl::ApplyTemplateToModel($Conf,$HTTP));
                      
                    ?>

                    <!--div class="dropdown">

                        <button class="dropdown-button">Dropdown</button>

                        <div class="dropdown-content">
                            <a href="#">Link 1 molto molto</a>
                            <a href="#">Link 2</a>
                            <a href="#">Link 3</a>
                        </div>

                    </div-->
                </div>
            </div>

        </div>
    </body>
</html>