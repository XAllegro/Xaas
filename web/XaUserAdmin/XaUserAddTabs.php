<div class="tab">
    <input  type="radio" id="tab-2" name="tab-group-1" checked>
    <label class="style-label" for="tab-2">Addresses</label>

    <div id="tab-div-2" class="tab_content">

            <div id="list-2"></div>

    <script>

        GeoList();

        function GeoList(){

            <?php echo "var XaUser_ID=$RefId;"?>

            Xa.Sleep(100);
            var Url='XaPageIncluded.php?obj=XaUserAddressGeo&evt=ListByUser&tpl=List';
            var ApiParams='&ApiParams={"XaUser_ID":"'+XaUser_ID+'"}';
            var TplParams='&TplParams={"obj":"XaUserAddressGeo","TplType":"ListForTab","title":"Lista Indirizzi","AfterDelete":"GeoList"}';

            var CompleteUrl=Url+ApiParams+TplParams;
            Xa.CallAction("", CompleteUrl ,{"ResponseType":"Html","TargetId":"list-2"});

        }

    </script>

    <?php

        $ApiParams='{"type":"CreateWithExternalKey","XaUser_ID":"'.$RefId.'"}';
        $UserAddressGeo=new XaUserAddressGeo();
        $WsData=$UserAddressGeo->ExecuteSync($Conf,$HTTP,"GetXmlModel","XaUserAddressGeo",$ApiParams);
        
        $TplParams='{"TplType":"CreateForGeo","obj":"XaUserAddressGeo","ResponseType":"void","PostJsFunction":"GeoList"}';
        $Tpl = new XaTplCreate();
        $Content = $Tpl->Create($Conf,$HTTP,$WsData,$TplParams);

        echo $Content;		
    ?>
    </div>
</div>

<div class="tab">

    <input  type="radio" id="tab-3" name="tab-group-1">
	<label class="style-label" for="tab-3">Phones</label>
	<div id="tab-div-3" class="tab_content">

            <div id="list-3"></div>

            <script>

                PhoneList();

                function PhoneList() {

                    <?php echo "var XaUser_ID=$RefId;"?>

                    Xa.Sleep(100);
                    var Url='XaPageIncluded.php?obj=XaUserAddressPhone&evt=ListByUser&tpl=List';
                    var ApiParams='&ApiParams={"XaUser_ID":"'+XaUser_ID+'"}';
                    var TplParams='&TplParams={"obj":"XaUserAddressPhone","TplType":"ListForTab","title":"Lista Telefoni","AfterDelete":"PhoneList"}';

                    var CompleteUrl=Url+ApiParams+TplParams;
                    Xa.CallAction("", CompleteUrl ,{"ResponseType":"Html","TargetId":"list-3"});

                }

            </script>

            <?php

                $ApiParams='{"type":"CreateWithExternalKey","XaUser_ID":"'.$RefId.'"}';
                $UserAddressPhone=new XaUserAddressPhone();
                $WsData=$UserAddressPhone->ExecuteSync($Conf,$HTTP,"GetXmlModel","XaUserAddressPhone",$ApiParams);

                $TplParams='{"TplType":"CreateForTab","obj":"XaUserAddressPhone","ResponseType":"void","PostJsFunction":"PhoneList"}';
                $Tpl = new XaTplCreate();
                $Content = $Tpl->Create($Conf,$HTTP,$WsData,$TplParams);

                echo $Content;		
            ?>

	</div>
</div>

<div class="tab">

    <input  type="radio" id="tab-4" name="tab-group-1">			
    <label class="style-label" for="tab-4">Emails</label>
    <div id="tab-div-4" class="tab_content">

    <div id="list-4"></div>

    <script>

        EmailList();

        function EmailList(){

                <?php echo "var XaUser_ID=$RefId;"?>

                Xa.Sleep(100);
                var Url='XaPageIncluded.php?obj=XaUserAddressMail&evt=ListByUser&tpl=List';
                var ApiParams='&ApiParams={"XaUser_ID":"'+XaUser_ID+'"}';
                var TplParams='&TplParams={"obj":"XaUserAddressMail","TplType":"ListForTab","title":"Lista Mail","AfterDelete":"EmailList"}';

                var CompleteUrl=Url+ApiParams+TplParams;
                Xa.CallAction("", CompleteUrl ,{"ResponseType":"Html","TargetId":"list-4"});
        }

    </script>

    <?php

        $ApiParams='{"type":"CreateWithExternalKey","XaUser_ID":"'.$RefId.'"}';
        $UserAddressMail=new XaUserAddressMail();
        $WsData=$UserAddressMail->ExecuteSync($Conf,$HTTP,"GetXmlModel","XaUserAddressMail",$ApiParams);

        $TplParams='{"TplType":"CreateForTab","obj":"XaUserAddressMail","ResponseType":"void","PostJsFunction":"EmailList"}';
        $Tpl = new XaTplCreate();
        $Content = $Tpl->Create($Conf,$HTTP,$WsData,$TplParams);

        echo $Content;
    ?>
    </div>
</div>

<div class="tab">

    <input  type="radio" id="tab-1" name="tab-group-1">
    <label class="style-label" for="tab-1">Login & Roles</label>
    <div id="tab-div-1" class="tab_content">

        <div id="list-1"></div>

        <script>

            RoleList();

            function RoleList() {

                <?php echo "var XaUser_ID=$RefId;"?>

                Xa.Sleep(100);
                var Url='XaPageIncluded.php?obj=XaRbacRoleRXaUser&evt=ListByUser&tpl=List';
                var ApiParams='&ApiParams={"XaUser_ID":"'+XaUser_ID+'"}';
                var TplParams='&TplParams={"obj":"XaRbacRoleRXaUser","TplType":"ListForTab","title":"Lista Ruoli","AfterDelete":"RoleList"}';

                var CompleteUrl=Url+ApiParams+TplParams;
                Xa.CallAction("", CompleteUrl ,{"ResponseType":"Html","TargetId":"list-1"});
            }
        </script>

        <?php

            $ApiParams='{"type":"CreateWithExternalKey","XaUser_ID":"'.$RefId.'"}';
            $RbacRoleRXaUser=new XaRbacRoleRXaUser();
            $WsData=$RbacRoleRXaUser->ExecuteSync($Conf,$HTTP,"GetXmlModel","XaRbacRoleRXaUser",$ApiParams);

            $TplParams='{"TplType":"CreateForTab","obj":"XaRbacRoleRXaUser","ResponseType":"void","PostJsFunction":"RoleList"}';
            $Tpl = new XaTplCreate();
            $Content = $Tpl->Create($Conf,$HTTP,$WsData,$TplParams);

            echo $Content;
        ?>

    </div>
</div>