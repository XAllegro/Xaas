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

             <?php
                echo (XaApiTpl::ApplyTemplateToModel($Conf,$HTTP));
             ?>

    </body>
</html>