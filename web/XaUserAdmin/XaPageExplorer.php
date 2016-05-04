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

        <div class="explorer">

            <div class="nav">
                 <?php require_once ('nav.php');?>
            </div>


            <div class="detail" id="detail">
                <div class="content" id="content">
 
                    <?php

                        //XaPageExplorer.php?obj=XaUser&evt=List&ApiParams={"order_by":"surname"}&tpl=List&TplParams={"title":"titololista"}

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

                </div>
            </div>

        </div>
    </body>
</html>