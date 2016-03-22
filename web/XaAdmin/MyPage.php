<?php require_once ('XaPage.php');?>

<html id="html">

    <head id="head">
        <?php require_once ('head.php');?>
        
        <script>MenuArgsCall={
            ResponseType:"Html",
            TargetId:"detail",
            CallMethod:"POST",
            CallAsync:"true",
            WithLoader:"no",
            LoaderTargetID:"",
            JsEval:"yes",
            WithAlert:"no",
            AlertMessage:""
            };
        </script>


        
        
    </head>

    <body>

        <header id="header">
            <?php require_once ('header.php');?>
        </header>
        
        <div class="explorer">

            <div class="nav">
                <ul>

                    <li><a href="#" onclick="">Applications</a></li>
                    <li><a href="#" onclick="Xa.CallAction('','ListUser.php?obj=XaUser&evt=List',MenuArgsCall);">Users</a></li>
                    <li>Role Based Access Control</li>
                    <li>Configuration</li>
                    <li>Audit</li>
                    <li>Queues</li>
                    <li>Statistics</li>
                    <li>Logs</li>
                </ul>
            </div>
            <div class="detail" id="detail">detail here</div>
    
        </div>
            <!--div class="dashboard">

                <div class="box BoxOu">
                    <p class="title">Organizational Units</p>
                    <ul>
                        <li class="IconCreate">
                            <a href="?obj=XaOuUi&evt=CreateFrm"></a>
                        </li>
                        <li class="IconExplorer">
                            <a href="?obj=XaOuUi&evt=Explorer"></a>
                        </li>
                    </ul>
                </div>

                <div class="box BoxOuType">
                    <p class="title">Organizational Units Type</p>
                    <ul>
                        <li class="IconList">
                             <a href="?obj=XaOuTypeUi&evt=List"></a>
                        </li>
                        <li class="IconCreate">
                            <a href="?obj=XaOuTypeUi&evt=CreateFrm"></a>
                        </li>
                    </ul>
                </div>

                <div class="box BoxUser">
                    <p class="title">Users &#160;</p>
                    <ul>
                        <li class="IconList">
                             <a href="?obj=XaUserUi&evt=List"></a>
                        </li>
                        <li class="IconCreate">
                            <a href="?obj=XaUserUi&evt=Add"></a>
                        </li>
                    </ul>
                </div>

                <div class="box BoxUserType">
                    <p class="title">User Types</p>
                    <ul>
                        <li class="IconList">
                             <a href="?obj=XaUserTypeUi&evt=List"></a>
                        </li>
                        <li class="IconCreate">
                            <a href="?obj=XaUserTypeUi&evt=CreateFrm"></a>
                        </li>
                    </ul>
                </div>

                <div class="box BoxRbacRole">
                    <p class="title">User Roles</p>
                    <ul>
                        <li class="IconList">
                             <a href="?obj=XaRbacRoleUi&evt=List"></a>
                        </li>
                        <li class="IconCreate">
                            <a href="?obj=XaRbacRoleUi&evt=CreateFrm"></a>
                        </li>
                    </ul>
                </div>
            </div-->
        </div>
    </body>
</html>