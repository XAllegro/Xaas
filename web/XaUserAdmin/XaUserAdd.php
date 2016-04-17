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

			<div class="detail" id="detail">
    			<div class="content" id="content">
    
        		<?php

        		    //FIRST STEP
        		    if (!$HTTP->ExistsHttpParam("RefId")) {

        		        $XaUser=new XaUser();
        		        $WsData=$XaUser->ExecuteSync($Conf,$HTTP,'GetXmlModel','XaUser','');
        		        
        		        $Tpl = new XaTplCreate();
        		        // obj,TargetId,ResponseType belong to form action
        		        $Content = $Tpl->Create($Conf,$HTTP,$WsData,'{"obj":"XaUser","RedTo":"XaUserAdd","RedKey":"create","TargetId":"UserId","ResponseType":"Void"}');
        		        echo $Content;

                    //FURTHER STEPS
        		    } else {

        		        $RefId=$HTTP->GetHttpParam("RefId");

        		        $XaUser=new XaUser();
        		        $WsData=$XaUser->ExecuteSync($Conf,$HTTP,'Read','XaUser','{"id":'.$RefId.'}');

        		        $Tpl = new XaTplRead();
        		        $Content = $Tpl->Read($Conf,$HTTP,$WsData,'');
        		        echo $Content;
        		    }
                ?>
			
			</br></br>

                <?php
                	
                	 if ($HTTP->ExistsHttpParam("RefId")) {

                	     echo '<div class="tabs">';
                	     $RefId=$HTTP->GetHttpParam("RefId");
                		 require_once ('XaUserAddTabs.php');
                		
                		 echo "</div>";

                	 }
                ?>
        	</div>
    	</div>
	</div>
</body>
</html>