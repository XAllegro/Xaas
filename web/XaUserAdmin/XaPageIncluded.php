<?php 

require_once ('XaConf.php');

$obj=$HTTP->GetHttpParam("obj");
$evt=$HTTP->GetHttpParam("evt");
$tpl=$HTTP->GetHttpParam("tpl");

$ApiParams=$HTTP->GetHttpParam("ApiParams");
$TplParams=$HTTP->GetHttpParam("TplParams");

$Object=new $obj();
$WsData=$Object->ExecuteSync($Conf,$HTTP,$evt,$obj,$ApiParams);

$TemplateToApply="XaTpl".$tpl;

$Tpl = new $TemplateToApply();
$Content = $Tpl->$tpl($Conf,$HTTP,$WsData,$TplParams);

echo $Content;

?>