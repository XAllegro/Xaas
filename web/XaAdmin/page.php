<html id="html">

    <head id="head">
         <?php require_once ('head.php');?>
    </head>

    <body>

        <header id="header">
            <?php require_once ('header.php');?>
        </header>
        
        <div class="container">
         <?php   
            ini_set('include_path', '/XAllegro/Xaas/XaLibPhp');
            //MODEL
            require_once('XaUser.php');
             require_once('XaUser.php');
            //VIEW
            require_once('XaTplCreateForm.php');
        
        $form= new XaTplCreateForm();
        echo $form->GetForm();
        
        ?>
        
        </div>
    </body>
</html>