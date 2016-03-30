<ul>    
    <script>
    	MenuArgsCall={
            ResponseType:"Html",
            TargetId:"content"
            };
        </script>

    <!--li><a href="#" onclick="">Applications</a></li-->
    <li><a href="#" onclick="Xa.CallAction('','XaPage.php?obj=XaUser&evt=List&tpl=List&params={%22order_by%22:%22surname%22}&TplParams={%22actions%22:%22yes%22,%22title%22:%22Lista%20Utenti%22}&lay=Included',MenuArgsCall);">Users' List</a></li>
    <li><a href="#" onclick="Xa.CallAction('','XaPage.php?obj=XaUserType&evt=List&tpl=List&params={%22order_by%22:%22name%22}&TplParams={%22title%22:%22Tipi%20Utente%22}&lay=Included',MenuArgsCall);">User's Types</a></li>
    <li><a href="#" onclick="Xa.CallAction('','List.php?obj=XaRbacRole&evt=List',MenuArgsCall);">User Roles</a></li>
    <li><a href="#" onclick="Xa.CallAction('','List.php?obj=XaOuType&evt=List',MenuArgsCall);">Ou Types</a></li>
    <!--li>Role Based Access Control</li>
    <li>Configuration</li>
    <li>Audit</li>
    <li>Queues</li>
    <li>Statistics</li>
    <li>Logs</li-->
</ul>