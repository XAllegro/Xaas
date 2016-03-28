<?php


class XaApiTpl {

    static public final function ApplyTemplateToModel(&$Conf,&$HTTP) :string {

        $obj=$HTTP->GetHttpParam('obj');
        $evt=$HTTP->GetHttpParam('evt');
        $tpl=$HTTP->GetHttpParam('tpl');
        
        
        /*RETRIEVE THE MODEL*/        
        $object=new $obj();
        $WsData=$object->$evt($Conf,$HTTP);
        //var_dump($WsData);

        /*APPLY THE TEMPLATE*/        
        $TplClass="XaTpl".$tpl;
        $TplMethod=$tpl;

 //       echo $TplClass;
   //     echo $TplMethod;

        $Tpl=new $TplClass();
        $Content=$Tpl->$TplMethod($Conf,$HTTP,$WsData);
        return $Content;
    }
}
?>