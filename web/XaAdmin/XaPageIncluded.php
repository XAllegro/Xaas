<?php require_once ('XaPage.php');?>

<html id="html">

    <body>
             <?php require_once ('XaApiTpl.php');
                echo (XaApiTpl::ApplyTemplateToModel($Conf,$HTTP));      
             ?>
    </body>
</html>