<?php

class XaApiTpl {

    static public final function ApplyTemplateToModel(&$Conf,&$HTTP) {

        $obj=$HTTP->GetHttpParam('obj');
        $evt=$HTTP->GetHttpParam('evt');
        $tpl=$HTTP->GetHttpParam('tpl');

        /*RETRIEVE THE MODEL*/        
        $object=new $obj();
        $WsData=$object->$evt($Conf,$HTTP);

        /*APPLY THE TEMPLATE*/        
        $TplClass="XaTpl".$tpl;
        $TplMethod=$tpl;

        $Tpl=new $TplClass();
        $Content=$Tpl->$TplMethod($Conf,$HTTP,$WsData);
        return $Content;
    }
/*
    static public final function ApplyTemplateAndModel(&$Conf,&$HTTP,array &$WsData,&$Tpl) :string {

        $TplClass="XaTpl".$Tpl;
        $TplMethod=$Tpl;
    
        //echo $TplClass;
        //echo $TplMethod;
    
        $Template=new $TplClass();
        $Content=$Template->$TplMethod($Conf,$HTTP,$WsData);
        return $Content;
    }
*/
    static public final function ApplyTemplate(&$Conf,&$HTTP,$WsData,$tpl,$TplParams) {

        /*APPLY THE TEMPLATE*/
        $TplClass="XaTpl".$tpl;
        $TplMethod=$tpl;

        $Template=new $TplClass();
        $Content=$Template->$TplMethod($Conf,$HTTP,$WsData,$TplParams);
        return $Content;
    }
}
?>