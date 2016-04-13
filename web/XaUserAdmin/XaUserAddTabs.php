<div class="tab">

	<input  type="radio" id="tab-1" name="tab-group-1" checked>
	<label class="style-label" for="tab-1">Roles</label>
	<div id="tab-div-1" class="tab_content">

		<?php

            $ApiParams='{"type":"WithExternalKey","XaUser_ID":"'.$RefId.'"}';
            $RbacRoleRXaUser=new XaRbacRoleRXaUser();
            $WsData=$RbacRoleRXaUser->ExecuteSync($Conf,$HTTP,"GetXmlModel","XaRbacRoleRXaUser",$ApiParams);

            $TplParams='{"obj":"XaRbacRoleRXaUser","ResponseType":"Text","WithAlert":"yes"}';
            $Tpl = new XaTplCreate();
            $Content = $Tpl->Create($Conf,$HTTP,$WsData,$TplParams);

            echo $Content;		
        ?>

	</div> 
</div>

<div class="tab">
   	<input  type="radio" id="tab-2" name="tab-group-1">
	<label class="style-label" for="tab-2">Addresses</label>
	<div id="tab-div-2" class="tab_content">
		 <?php

            $ApiParams='{"type":"WithExternalKey","XaUser_ID":"'.$RefId.'"}';
            $UserAddressGeo=new XaUserAddressGeo();
            $WsData=$UserAddressGeo->ExecuteSync($Conf,$HTTP,"GetXmlModel","XaUserAddressGeo",$ApiParams);

            $TplParams='{"obj":"XaUserAddressGeo","ResponseType":"Text","WithAlert":"yes"}';
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

        <?php

            $ApiParams='{"type":"WithExternalKey","XaUser_ID":"'.$RefId.'"}';
            $UserAddressPhone=new XaUserAddressPhone();
            $WsData=$UserAddressPhone->ExecuteSync($Conf,$HTTP,"GetXmlModel","XaUserAddressPhone",$ApiParams);

            $TplParams='{"obj":"XaUserAddressPhone","ResponseType":"Text","WithAlert":"yes"}';
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
		
		 <?php

            $ApiParams='{"type":"WithExternalKey","XaUser_ID":"'.$RefId.'"}';
            $UserAddressMail=new XaUserAddressMail();
            $WsData=$UserAddressMail->ExecuteSync($Conf,$HTTP,"GetXmlModel","XaUserAddressMail",$ApiParams);

            $TplParams='{"obj":"XaUserAddressMail","ResponseType":"Text","WithAlert":"yes"}';
            $Tpl = new XaTplCreate();
            $Content = $Tpl->Create($Conf,$HTTP,$WsData,$TplParams);

            echo $Content;
        ?>
	</div> 
</div>