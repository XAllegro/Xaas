<?php
require_once ('XaPage.php');

$obj=$HTTP->GetHttpParam('obj');

$object=new $obj();
$object->Delete($Conf,$HTTP);

?>