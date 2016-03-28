<html id="html">

    <head>
        <?php require_once ('head.php');?>
    </head>

    <body>

        <header id="header">
            <?php require_once ('header.php');?>
        </header>

             <?php require_once ('XaApiTpl.php');
                echo (XaApiTpl::ApplyTemplateToModel($Conf,$HTTP));      
             ?>

    </body>
</html>