<?php require_once ('XaPage.php');?>
<html id="html">

    <head>
         <?php require_once ('head.php');?>
    </head>
    <body>
    <div class="container">

        <form class="form form-1-column" id="Login" name="Login" method="POST" action="?obj=XaUser&amp;evt=Login">

            <fieldset>
                <legend class="LogHomePage" style="line-height:2em" >
                    <img/>
                </legend>
                <ul>
                    <li>
                            You have been successfully logged out.
                    </li>
                    <li>
                        Click <a href="index.php">here</a> to log in again.
                    </li>
                </ul>
            </fieldset>
        </form>
    </div>
        
    </body>
</html>