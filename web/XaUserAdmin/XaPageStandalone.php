<?php require_once ('XaConf.php');?>

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

                //XaPageStandalone.php?obj=XaUser&evt=List&ApiParams={"order_by":"surname"}&tpl=List&TplParams={"title":"titololista"}
                $obj=$HTTP->GetHttpParam("obj");
                $evt=$HTTP->GetHttpParam("evt");
                $tpl=$HTTP->GetHttpParam("tpl");

                $ApiParams=$HTTP->GetHttpParam("ApiParams");
                $TplParams=$HTTP->GetHttpParam("TplParams");

                $Object=new $obj();
                $WsData=$Object->ExecuteSync($Conf,$HTTP,$evt,$obj,$ApiParams);

                $TemplateToApply="XaTpl".$tpl;

                $Tpl = new $TemplateToApply();
                $Content = $Tpl->$tpl($Conf,$HTTP,$WsData,$TplParams);

                echo $Content;
             ?>

    </body>
</html>