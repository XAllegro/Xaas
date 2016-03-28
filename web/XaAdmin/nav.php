<ul>
    
    <script>
    MenuArgsCall={
            ResponseType:"Html",
            TargetId:"content"
            };
        </script>

    <!--li><a href="#" onclick="">Applications</a></li-->
    <li><a href="#" onclick="Xa.CallAction('','List.php?obj=XaUser&type=actions',MenuArgsCall);">Users</a></li>
    <li><a href="#" onclick="Xa.CallAction('','List.php?obj=XaUserType&evt=List',MenuArgsCall);">User Types</a></li>
    <li><a href="#" onclick="Xa.CallAction('','List.php?obj=XaRbacRole&evt=List',MenuArgsCall);">User Roles</a></li>
    <li><a href="#" onclick="Xa.CallAction('','List.php?obj=XaOuType&evt=List',MenuArgsCall);">Ou Types</a></li>
    <!--li>Role Based Access Control</li>
    <li>Configuration</li>
    <li>Audit</li>
    <li>Queues</li>
    <li>Statistics</li>
    <li>Logs</li-->
</ul>