<ul>

    <!--li><a href="#" onclick="">Applications</a></li-->
    <li><a href="#" onclick="Xa.CallAction('','XaPage.php?obj=XaUser&evt=List&tpl=List&params={%22order_by%22:%22surname%22}&TplParams={%22actions%22:%22yes%22,%22title%22:%22Lista%20Utenti%22}&lay=Included',{&quot;ResponseType&quot;:&quot;Html&quot;,&quot;TargetId&quot;:&quot;content&quot;});">Users' List</a></li>
    <li><a href="#" onclick="Xa.CallAction('','XaPage.php?obj=XaUserType&evt=List&tpl=List&params={%22order_by%22:%22name%22}&TplParams={%22title%22:%22Tipi%20Utente%22}&lay=Included',{&quot;ResponseType&quot;:&quot;Html&quot;,&quot;TargetId&quot;:&quot;content&quot;});">User's Types</a></li>
    <li><a href="#" onclick="Xa.CallAction('','List.php?obj=XaRbacRole&evt=List',{&quot;ResponseType&quot;:&quot;Html&quot;,&quot;TargetId&quot;:&quot;content&quot;});">User Roles</a></li>
    <li><a href="#" onclick="Xa.CallAction('','List.php?obj=XaOuType&evt=List',{&quot;ResponseType&quot;:&quot;Html&quot;,&quot;TargetId&quot;:&quot;content&quot;});">Ou Types</a></li>
    <li><a href="#" onclick="Xa.CallAction('','XaUserAdd.php',{&quot;ResponseType&quot;:&quot;Html&quot;,&quot;TargetId&quot;:&quot;content&quot;});">Create a User</a></li>
    
    <!--li>Role Based Access Control</li>
    <li>Configuration</li>
    <li>Audit</li>
    <li>Queues</li>
    <li>Statistics</li>
    <li>Logs</li-->
</ul>