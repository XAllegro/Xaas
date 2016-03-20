<!DOCTYPE html>
<!--
To change this license header, choose License Headers in Project Properties.
To change this template file, choose Tools | Templates
and open the template in the editor.
-->
<html id="html">

    <head id="head">
        <?php require_once ('head.php');?>
    </head>
    <body>

        <div class="container">

            <form  class="form form-1-column" id="Login" name="Login" method="POST" action="XaApi.php?obj=XaUserLogin&evt=Login">

               <fieldset>
                  <legend class="LogHomePage" style="line-height:2em" >
                      <img/>
                  </legend>

                  <ul>
                      <li>
                          <label id="username-label" for="username-input">Email</label>
                          <input id="username-input" name="username" type="email" placeholder="Please insert your Email" required="required" autofocus="autofocus" />
                      </li>
                      <li>
                          <label id="password-label" for="password-input">Password</label>
                          <input id="password-input" name="password" type="password" placeholder="Please insert your Password" required="required" /><br/><br/>
                      </li>
                      <li>
                          <button type="submit">Log In !</button><br/><br/>
                      </li>
                   </ul>
               </fieldset>
            </form>
        </div>

    </body>
</html>
